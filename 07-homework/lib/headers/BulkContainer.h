#pragma once

#include "Command.h"
#include "Bulk.h"

class Moderator;

class BulkContainer
{
public:
    BulkContainer(Moderator&, size_t);
    ~BulkContainer() = default;

    bool CheckBulkForOverflow();
    void AddCommand(Command);
    void ClearBulk();

    bool IsBraceOpen();
    void OpenBrace();
    void CloseBrace();

private:
    size_t braceCounter = 0;
    Bulk* bulk;
    Moderator* modPtr;
    size_t maxBulkSize;
};







































// #include <memory>
// #include <string>
// #include <Stub_command.h>
// #include <Bulk.h>

// class BULKoperator : public std::enable_shared_from_this<BULKoperator>
// {
// public:
//     BULKoperator(size_t size) : bulkSize(size) 
//     {

//     }

//     void PushNewCommand(std::string command)
//     {
//         Stub_command newCommand(command);
//         bulkList.front().PushNewCommand(newCommand);
//     }

// private:
//     void CheckForOverflow();
//     void ClearBulk();
//     void ForcedStop();
//     // {}

//     std::vector<Bulk> bulkList;
//     size_t bulkSize;
// };
