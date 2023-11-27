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

    void SetTags(system_clock::time_point, size_t);
    void Print(const std::vector<std::string>&) const override;
private:
    std::string fileName;
    system_clock::time_point timeTag;
    size_t additionalTag;
};
