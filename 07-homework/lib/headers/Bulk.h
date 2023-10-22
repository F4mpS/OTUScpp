#pragma once

#include <vector>

#include "Command.h"

class Bulk
{
public:
    Bulk(size_t);
    ~Bulk() = default;

    std::vector<Command> GetCommandsList();
    size_t GetSize();
    void ClearCommandList();
    void AddCommand(Command);
private:
    std::vector<Command> commadsList;
};
































// #include <interfaces/ICommand.h>

// class Bulk
// {
// public:
//     void PushNewCommand(ICommand newCommand)
//     {
//         commands.push_back(newCommand);
//     }

//     size_t GetBulkSize()
//     {
//         return commands.size();
//     }

//     std::vector<std::string> GetCommandsList()
//     {
//         std::vector<std::string> commandsList;
//         for (auto comm : commands)
//             commandsList.push_back(comm.GetCommand);
//         return commandsList;
//     } 
// private:
//     std::vector<ICommand> commands;
// };

