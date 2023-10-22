#include "headers/Moderator.h"

Moderator::Moderator(size_t bulkSize, std::istream& inS = std::cin, std::ostream& outS = std::cout) :
    input(new ConsoleReader(*this, inS)), 
    output(new ConsolePrinter(outS)),
    bulkContainer(new BulkContainer(*this, bulkSize))
{}

void Moderator::StartReading()
{
    input->Start();
}

void Moderator::EndReading()
{
    if (!bulkContainer->IsBraceOpen())
        bulkContainer->ClearBulk();
}

void Moderator::LogCommand(Command command)
{
    bulkContainer->AddCommand(command);
}

void Moderator::LogOpenBrace()
{
    if (!bulkContainer->IsBraceOpen())
        bulkContainer->ClearBulk();

    bulkContainer->OpenBrace();
}

void Moderator::LogCloseBrace()
{
    bulkContainer->CloseBrace();
    if (!bulkContainer->IsBraceOpen())
        bulkContainer->ClearBulk();
}

void Moderator::LogPrint(std::vector<Command> commandsList)
{
    output->Print("bulk: ");
    for (size_t i = 0; i < commandsList.size(); i++)
    {
        if (i == 0)
            output->Print(commandsList[i].GetCommandName());
        else 
            output->Print(", " + commandsList[i].GetCommandName());
    }
    output->Print("\n");
}
