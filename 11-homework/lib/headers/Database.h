#pragma once

#include <map>
#include <optional>
#include <shared_mutex>
#include <string>

#include "Message.h"

class Database
{
public:
    static Database* GetInstance();

    Message Insert(const std::string&, int, std::string);

    Message Truncate(const std::string&);

    class SymmetricDifference
    {
    public:
        std::size_t Size() const;

        class Iterator
        {
        public:
            struct Value
            {
                int id;
                const std::optional<std::string>& first;
                const std::optional<std::string>& second;
            };

            Value operator*() const;
            Iterator& operator++();
            bool operator==(const Iterator&) const;
            bool operator!=(const Iterator&) const;

        private:
            friend class SymmetricDifference;
            using map_iter = std::map<int, std::pair<std::optional<std::string>, std::optional<std::string>>>::const_iterator;

            Iterator(const SymmetricDifference*, map_iter);

            const SymmetricDifference* instance;
            map_iter iterator;
        };

        Iterator begin() const;
        Iterator end() const;

    private:
        friend class Database;

        SymmetricDifference() = default;

        std::map<int, std::pair<std::optional<std::string>, std::optional<std::string>>> data;
    };

    class Intersection
    {
    public:
        std::size_t Size() const;

        class Iterator
        {
        public:
            struct Value
            {
                int id;
                const std::string& first;
                const std::string& second;
            };

            Value operator*() const;
            Iterator& operator++();
            bool operator==(const Iterator&) const;
            bool operator!=(const Iterator&) const;

        private:
            friend class Intersection;
            using map_iter = std::map<int, std::pair<std::string, std::string>>::const_iterator;

            Iterator(const Intersection*, map_iter);

            const Intersection* instance;
            map_iter iterator;
        };

        Iterator begin() const;
        Iterator end() const;

    private:
        friend class Database;

        std::map<int, std::pair<std::string, std::string>> data;
    };

    std::pair<Message, SymmetricDifference>
    symmetricDifference(const std::string&, const std::string&) const;

    std::pair<Message, Intersection>
    intersection(const std::string&, const std::string&) const;

private:
    Database();

    using Table = std::map<int, std::string>;
    mutable std::shared_mutex mutex;

    std::map<std::string, Table> tables;
};
