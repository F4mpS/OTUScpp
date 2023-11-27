#include "../headers/Moderator.h"
#include "../headers/CommandReceiver.h"
#include "../headers/Command.h"

CommandReceiver::CommandReceiver(Moderator &mod) : modPtr(&mod) {}

CommandReceiver::~CommandReceiver()
{
    modPtr = nullptr;
}

void CommandReceiver::Receive(std::string command)
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
        modPtr->EndReceiving();
    }
    else
    {
        Command stubCommand(command);
        modPtr->LogCommand(stubCommand);
    }
}
