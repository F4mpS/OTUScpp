#include "../headers/BulkContainer.h"
#include "../headers/Moderator.h"

BulkContainer::BulkContainer(Moderator& mod, size_t maxBulkSize) : modPtr(&mod), maxBulkSize(maxBulkSize), bulk(new Bulk(maxBulkSize))
{}

BulkContainer::~BulkContainer()
{
    modPtr = nullptr;
    bulk->~Bulk();
    bulk = nullptr;
}

bool BulkContainer::CheckBulkForOverflow()
{
    return bulk->GetSize() >= maxBulkSize;
}

void BulkContainer::AddCommand(Command command)
{
    if (braceCounter == 0)
    {
        bulk->AddCommand(command);
        if (CheckBulkForOverflow())
            ClearBulk();
    }
    else
    {
        bulk->AddCommand(command);
    }
}

void BulkContainer::ClearBulk()
{
    if (bulk->GetSize() != 0)
    {
        modPtr->LogPrint(bulk->GetCommandsList(), bulk->GetCreationTime());
        bulk->ClearCommandList();
    }
}

bool BulkContainer::IsBraceOpen()
{
    return !(braceCounter == 0);
}

void BulkContainer::OpenBrace()
{
    braceCounter++;
}

void BulkContainer::CloseBrace()
{
    braceCounter--;
}
