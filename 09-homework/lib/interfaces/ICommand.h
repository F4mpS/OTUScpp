#pragma once

#include <string>

class ICommand
{
public:
    ICommand(std::string command);
    virtual ~ICommand() = default;

    virtual void Execute() = 0;

    virtual std::string GetCommandName() const final;

private:
    std::string commandName;
};