#pragma once

#include <chrono>
#include <vector>

#include "Command.h"
#include "ConsoleReader.h"
#include "BulkContainer.h"
#include "printers/FilePrinter.h"
#include "printers/OstreamPrinter.h"

using system_clock = std::chrono::system_clock;

class Moderator
{
public:
    Moderator(size_t, std::istream&);

    ~Moderator() = default;

    void AddOutputStream(std::ostream&);
    void AddOutputFile(std::string);

    void StartReading();
    void EndReading();

    void LogCommand(Command);
    void LogOpenBrace();
    void LogCloseBrace();

    void LogPrint(std::vector<Command>, system_clock::time_point);
private:
    std::vector<OstreamPrinter*> oPrinters;
    std::vector<FilePrinter*> fPrinters;
    ConsoleReader* input;
    BulkContainer* bulkContainer;
};

