#include "headers/printers/FilePrinter.h"

FilePrinter::FilePrinter(std::string fileName) : fileName(fileName) {}

void FilePrinter::SetTimeTag(system_clock::time_point newTimeTag)
{
    timeTag = newTimeTag;
}

void FilePrinter::Print(const std::vector<std::string>& commandsNamesList) const
{
    std::time_t t = std::chrono::system_clock::to_time_t(timeTag);
    std::stringstream ss;
    ss << t;
    std::string strTimeTag = ss.str();
    
    std::ofstream outFile(fileName + strTimeTag + ".log");

    for (auto &command : commandsNamesList)
        outFile << command << ' ';
    outFile << std::endl;

    outFile.close();
}
