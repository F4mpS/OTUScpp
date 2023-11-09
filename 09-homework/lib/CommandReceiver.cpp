#include "headers/Moderator.h"
#include "headers/CommandReceiver.h"
#include "headers/Command.h"


CommandReceiver::CommandReceiver(Moderator &mod) : modPtr(&mod) {}

CommandReceiver::~CommandReceiver()
{
    modPtr = nullptr;
}

void CommandReceiver::Receive(std::string command)
{
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (command == "{")
    {
        std::cout << command << std::endl;
        modPtr->LogOpenBrace();
    }
    else if (command == "}")
    {
        std::cout << command << std::endl;
        modPtr->LogCloseBrace();
    }
    else if (command == "EOF")
    {
        std::cout << command << std::endl;
        modPtr->EndReceiving();
    }
    else
    {
        std::cout << command << std::endl;
        Command stubCommand(command);
        modPtr->LogCommand(stubCommand);
    }
}
