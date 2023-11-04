#pragma once

#include <vector>
#include <chrono>

#include "Command.h"

using system_clock = std::chrono::system_clock;

class Bulk
{
public:
    Bulk(size_t);
    ~Bulk() = default;

    std::vector<Command> GetCommandsList();
    size_t GetSize();
    system_clock::time_point GetCreationTime();

    void ClearCommandList();
    void AddCommand(Command);
private:
    std::vector<Command> commadsList;
    system_clock::time_point creationTime;
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

