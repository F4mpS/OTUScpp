#pragma once 

#include <iostream>

class ConsolePrinter
{
public:
    ConsolePrinter(std::ostream&);
    ~ConsolePrinter() = default;

    void Print(std::string);
private:
    std::ostream& outStream;
};
