#include <sstream>
#include <iostream>

#include "../headers/Command.h"

std::string toString(const Message& message)
{
    switch (message.GetCode())
    {
    case Message::Code::OK:
        return "OK";
    case Message::Code::ERROR:
        return std::string{"ERR "} + message.GetCodeStr();
    }
}

std::string Insert(const std::string& table, int index, const std::string& data)
{
    return toString(Database::GetInstance()->Insert(table, index, data));
}

std::string Truncate(const std::string& table)
{
    return toString(Database::GetInstance()->Truncate(table));
}

std::string Intersection()
{
    auto [message, inter] = Database::GetInstance()->intersection("A", "B");
    switch (message.GetCode())
    {
    case Message::Code::OK:
    {
        std::string ans;
        for (const auto& [id, value1, value2] : inter)
            ans += std::to_string(id) + "," + value1 + "," + value2 + "\n";
        ans += toString(message);
        return ans;
    }
    case Message::Code::ERROR:
    {
        return toString(message);
    }
    }
}

std::string symmetricDifference()
{
    auto [message, diff] = Database::GetInstance()->symmetricDifference("A", "B");
    switch (message.GetCode())
    {
    case Message::Code::OK:
    {
        std::string ans;
        for (const auto& [id, value1, value2] : diff)
            ans += std::to_string(id) + "," + value1.value_or("") + "," + value2.value_or("") + "\n";
        ans += toString(message);
        return ans;
    }
    case Message::Code::ERROR:
    {
        return toString(message);
    }
    }
}

std::string SendCommand(const std::string& command)
{
    std::string tag, remaining;
    std::istringstream stream(command);
    stream >> tag;
    std::string invalidArgs_ErrorMsg = toString(Message{Message::Code::ERROR, std::string{"Invalid arguments for command "} + tag});
    std::string tooManyArgs_ErrorMsg = toString(Message{Message::Code::ERROR, std::string{"Too many arguments in command "} + command});
    if (tag == "INSERT")
    {
        std::string table;
        stream >> table;
        if (!stream)
            return invalidArgs_ErrorMsg;

        int id;
        stream >> id;
        if (!stream)
            return invalidArgs_ErrorMsg;

        std::string data;
        stream >> data;
        if (!stream)
            return invalidArgs_ErrorMsg;

        stream >> remaining;
        if (stream)
            return tooManyArgs_ErrorMsg;

        return Insert(table, id, data);
    }
    else if (tag == "TRUNCATE")
    {
        std::string table;
        stream >> table;
        if (!stream)
            return invalidArgs_ErrorMsg;

        stream >> remaining;
        if (stream)
            return tooManyArgs_ErrorMsg;

        return Truncate(table);
    }
    else if (tag == "INTERSECTION")
    {
        stream >> remaining;
        if (stream)
            return tooManyArgs_ErrorMsg;

        return Intersection();
    }
    else if (tag == "SYMMETRIC_DIFFERENCE")
    {
        stream >> remaining;
        if (stream)
            return tooManyArgs_ErrorMsg;

        return symmetricDifference();
    }
    return toString(Message{Message::Code::ERROR, std::string{"Unknown command tag "} + tag});
}
