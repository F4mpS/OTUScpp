#include "../headers/Database.h"

#include <stdexcept>
#include <tuple>

Database::Database()
{
    tables.emplace("A", Table{});
    tables.emplace("B", Table{});
}

Database* Database::GetInstance()
{
    static Database instance;
    return &instance;
}

Message Database::Insert(const std::string& tableName, int id, std::string data)
{
    std::lock_guard lock(mutex);
    try
    {
        auto tableIter = tables.find(tableName);
        
        if (tableIter == tables.end())
            return Message{Message::Code::ERROR, std::string{"No such table "} + tableName};

        Table& table = tableIter->second;
        if (table.find(id) != table.end())
            return Message{Message::Code::ERROR, std::string{"duplicate "} + std::to_string(id)};

        table.emplace(id, std::move(data));
        return Message{Message::Code::OK, ""};
    }
    catch (const std::exception&)
    {
        return Message{Message::Code::ERROR, "Unknown error"};
    }
}

Message Database::Truncate(const std::string& table)
{
    std::lock_guard lock(mutex);
    try
    {
        auto tableIter = tables.find(table);
        if (tableIter == tables.end())
            return Message{Message::Code::ERROR, std::string{"No such table "} + table};

        tableIter->second = {};
        return Message{Message::Code::OK, ""};
    }
    catch (...)
    {
        return Message{Message::Code::ERROR, "Unknown error"};
    }
}

std::pair<Message, Database::SymmetricDifference>
Database::symmetricDifference(const std::string& tableName1, const std::string& tableName2) const
{
    std::shared_lock lock(mutex);
    try
    {
        auto tableIter1 = tables.find(tableName1);
        if (tableIter1 == tables.end())
            return {Message{Message::Code::ERROR, std::string{"No such table "} + tableName1}, {}};

        auto tableIter2 = tables.find(tableName2);
        if (tableIter2 == tables.end())
            return {Message{Message::Code::ERROR, std::string{"No such table "} + tableName2}, {}};

        const Table& table1 = tableIter1->second;
        const Table& table2 = tableIter2->second;

        SymmetricDifference diff;
        for (const auto& [index, data] : table1)
            if (table2.find(index) == table2.end())
                diff.data.emplace(index, std::pair{data, std::nullopt});
        for (const auto& [index, data] : table2)
            if (table1.find(index) == table1.end())
                diff.data.emplace(index, std::pair{std::nullopt, data});

        return {Message{Message::Code::OK, ""}, diff};
    }
    catch (...)
    {
        return {Message{Message::Code::ERROR, "Unknown error"}, {}};
    }
}

std::size_t Database::SymmetricDifference::Size () const
{
    return data.size();
}

Database::SymmetricDifference::Iterator Database::SymmetricDifference::begin() const
{
    return Iterator(this, data.begin());
}

Database::SymmetricDifference::Iterator Database::SymmetricDifference::end() const
{
    return Iterator(this, data.end());
}

Database::SymmetricDifference::Iterator::Iterator(const SymmetricDifference* instance, map_iter iterator)
    : instance(instance)
    , iterator(iterator)
{
}

Database::SymmetricDifference::Iterator::Value Database::SymmetricDifference::Iterator::operator*() const
{
    return Value{iterator->first, iterator->second.first, iterator->second.second};
}

bool Database::SymmetricDifference::Iterator::operator==(const Iterator &other) const
{
    return (std::tie(instance, iterator) ==
            std::tie(other.instance, other.iterator));
}

bool Database::SymmetricDifference::Iterator::operator!=(const Iterator &other) const
{
    return !(*this == other);
}

Database::SymmetricDifference::Iterator& Database::SymmetricDifference::Iterator::operator++()
{
    ++iterator;
    return *this;
}

std::pair<Message, Database::Intersection>
Database::intersection(const std::string& tableName1, const std::string& tableName2) const
{
    std::shared_lock lock(mutex);
    try
    {
        auto tableIter1 = tables.find(tableName1);
        if (tableIter1 == tables.end())
            return {Message{Message::Code::ERROR, std::string{"No such table "} + tableName1}, {}};

        auto tableIter2 = tables.find(tableName2);
        if (tableIter2 == tables.end())
            return {Message{Message::Code::ERROR, std::string{"No such table "} + tableName2}, {}};

        const Table *table1, *table2;

        bool need_swap;
        if (tableIter1->second.size() < tableIter2->second.size())
        {
            table1 = &tableIter1->second;
            table2 = &tableIter2->second;
            need_swap = false;
        }
        else
        {
            table1 = &tableIter2->second;
            table2 = &tableIter1->second;
            need_swap = true;
        }

        Intersection intersection;
        for (const auto& [index1, data1] : *table1)
        {
            auto it2 = table2->find(index1);
            if (it2 != table2->end())
            {
                if (!need_swap)
                    intersection.data.emplace(index1, std::pair<std::string, std::string>{data1, it2->second});
                else
                    intersection.data.emplace(index1, std::pair<std::string, std::string>{it2->second, data1});
            }
        }

        return {Message{Message::Code::OK, ""}, intersection};
    }
    catch (...)
    {
        return {Message{Message::Code::ERROR, "Unknown error"}, {}};
    }
}

std::size_t Database::Intersection::Size() const
{
    return data.size();
}

Database::Intersection::Iterator Database::Intersection::begin() const
{
    return Iterator(this, data.begin());
}

Database::Intersection::Iterator Database::Intersection::end() const
{
    return Iterator(this, data.end());
}

Database::Intersection::Iterator::Iterator(const Intersection* instance, map_iter iterator)
    : instance(instance)
    , iterator(iterator)
{
}

Database::Intersection::Iterator::Value Database::Intersection::Iterator::operator*() const
{
    return Value{iterator->first, iterator->second.first, iterator->second.second};
}

bool Database::Intersection::Iterator::operator==(const Iterator &other) const
{
    return (std::tie(instance, iterator) ==
            std::tie(other.instance, other.iterator));
}

bool Database::Intersection::Iterator::operator!=(const Iterator &other) const
{
    return !(*this == other);
}

Database::Intersection::Iterator& Database::Intersection::Iterator::operator++()
{
    ++iterator;
    return *this;
}
