#pragma once

#include <chrono>
#include <fstream> 
#include <sstream>

#include "../../interfaces/IPrinter.h"

using system_clock = std::chrono::system_clock;

class FilePrinter : public IPrinter
{
public:
    FilePrinter() = delete;
    FilePrinter(std::string);
    ~FilePrinter() = default;

    void Print(const std::vector<std::string>&) const override;
    void SetTimeTag(system_clock::time_point);
private:
    std::string fileName;
    system_clock::time_point timeTag;
};
