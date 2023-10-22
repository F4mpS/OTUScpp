#include "ICommand.h"

ICommand::ICommand(std::string command) : commandName(command) {}

std::string ICommand::GetCommandName() const
{
    return commandName;
}