#include "headers/Bulk.h"

Bulk::Bulk(size_t bulkSize)
{
    commadsList.reserve(bulkSize);
}

std::vector<Command> Bulk::GetCommandsList()
{
    return commadsList;
}

size_t Bulk::GetSize()
{
    return commadsList.size();
}

void Bulk::ClearCommandList()
{
    commadsList.clear();
}

void Bulk::AddCommand(Command command)
{
    if (commadsList.size() == 0)
        creationTime = system_clock::now();
    commadsList.push_back(command);
}
