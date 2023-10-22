#include "headers/ConsolePrinter.h"

#include <string>

ConsolePrinter::ConsolePrinter(std::ostream& outS) : outStream(outS) {}

void ConsolePrinter::Print(std::string commandName)
{
    outStream << commandName;
}