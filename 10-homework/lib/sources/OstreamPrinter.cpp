#include "../headers/printers/OstreamPrinter.h"

OstreamPrinter::OstreamPrinter(std::ostream& outS) : output(outS) {}

void OstreamPrinter::Print(const std::vector<std::string>& commandsNamesList) const
{
    output << "bulk: ";
    for (size_t i = 0; i < commandsNamesList.size(); i++)
    {
        if (i == 0)
            output << commandsNamesList[i];
        else 
            output << ", " + commandsNamesList[i];
    }
    output << "\n";
}