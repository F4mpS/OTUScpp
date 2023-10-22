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

