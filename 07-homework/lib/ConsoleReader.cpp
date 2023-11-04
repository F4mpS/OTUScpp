#include <string>

#include "headers/ConsoleReader.h"
#include "headers/Moderator.h"
#include "headers/Command.h"

ConsoleReader::ConsoleReader(Moderator& mod, std::istream& inS) : modPtr(&mod), inStream(inS) {}

void ConsoleReader::Start()
{
    std::string command;
    while(std::getline(inStream, command))
    {
        if (command == "{")
        {
            modPtr->LogOpenBrace();
        }
        else if (command == "}")
        {
            modPtr->LogCloseBrace();
        }
        else if (command == "EOF")
        {
            modPtr->EndReading();
            break;
        }
        else
        {
            Command stubCommand(command);
            modPtr->LogCommand(stubCommand);
        }  
    }
}