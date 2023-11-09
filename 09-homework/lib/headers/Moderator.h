#pragma once

#include <chrono>
#include <vector>
#include <thread>
#include <iostream>

#include "Command.h"
#include "CommandReceiver.h"
#include "BulkContainer.h"
#include "printers/FilePrinter.h"
#include "printers/OstreamPrinter.h"

using system_clock = std::chrono::system_clock;

class Moderator
{
public:
    Moderator(size_t);

    ~Moderator();

    void AddOutputStream(std::ostream &);
    void AddOutputFile(std::string);

    void ReadBuffer(const char *, size_t);
    void EndReceiving();

    void LogCommand(Command);
    void LogOpenBrace();
    void LogCloseBrace();

    void LogPrint(std::vector<Command>, system_clock::time_point);

private:
    void callPrint(const IPrinter *, std::vector<std::string>);

    std::vector<std::string> Split(std::string str, char d)
    {
        std::vector<std::string> r;

        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(d);
        while (stop != std::string::npos)
        {
            r.push_back(str.substr(start, stop - start));

            start = stop + 1;
            stop = str.find_first_of(d, start);
        }

        r.push_back(str.substr(start));

        return r;
    }

    
    BulkContainer *bulkContainer;
    CommandReceiver *receiver;
    std::vector<OstreamPrinter *> oPrinters;
    std::vector<FilePrinter *> fPrinters;
    size_t printCounter = 0;
};
