#pragma once 

#include <vector>
#include <string>

class IPrinter
{
public:
    virtual ~IPrinter() = default;
    virtual void Print(const std::vector<std::string>&) const = 0;
};
