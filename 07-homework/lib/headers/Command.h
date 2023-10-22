#pragma once

#include "../interfaces/ICommand.h"

class Command : public ICommand
{
public:
    using ICommand::ICommand;

    void Execute() override;
    virtual ~Command() = default;
};