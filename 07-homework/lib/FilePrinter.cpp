#include "headers/printers/FilePrinter.h"

FilePrinter::FilePrinter(std::string fileName) : fileName(fileName) {}

void FilePrinter::SetTimeTag(system_clock::time_point newTimeTag)
{
    timeTag = newTimeTag;
}

void FilePrinter::Print(const std::vector<std::string>& commandsNamesList) const
{
    std::string strTimeTag = fmt::print("{:%Y%m%d%H%M%OS}", timeTag);
    std::fstream outFile(fileName + strTimeTag + ".log");

    for (auto &command : commandsNamesList)
        outFile << command << ' ';
    outFile << std::endl;
}
