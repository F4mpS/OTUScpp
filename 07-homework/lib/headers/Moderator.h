#pragma once

#include "Command.h"
#include "ConsoleReader.h"
#include "ConsolePrinter.h"
#include "BulkContainer.h"

class Moderator
{
public:
    Moderator(size_t, std::istream&, std::ostream&);

    ~Moderator() = default;

    void StartReading();
    void EndReading();

    void LogCommand(Command);
    void LogOpenBrace();
    void LogCloseBrace();

    void LogPrint(std::vector<Command>);
private:
    ConsoleReader* input;
    ConsolePrinter* output;
    BulkContainer* bulkContainer;
};

