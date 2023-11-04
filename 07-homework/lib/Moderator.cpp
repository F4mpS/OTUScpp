#include "headers/Moderator.h"

Moderator::Moderator(size_t bulkSize, std::istream& inS = std::cin) :
    input(new ConsoleReader(*this, inS)),
    bulkContainer(new BulkContainer(*this, bulkSize))
{}

void Moderator::AddOutputStream(std::ostream& outS)
{
    oPrinters.emplace_back(new OstreamPrinter(outS));
}

void Moderator::AddOutputFile(std::string outFileName)
{
    fPrinters.emplace_back(new FilePrinter(outFileName));
}

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

void Moderator::LogPrint(std::vector<Command> commandsList, system_clock::time_point bulkCreationTime)
{
    // commandsList -> std::vector<std::string> commandsNames
    // rfor(FilePrinters)
    //      Print(commandsNames)
    // rfor(StreamPrinters)
    //      Print(commandsNames)
    std::vector<std::string> commandsNamesList;
    for (auto &command : commandsList)
        commandsNamesList.push_back(command.GetCommandName());
    
    for (auto &oPrinter : oPrinters)
        oPrinter->Print(commandsNamesList);
    for (auto &fPrinter : fPrinters)
    {
        fPrinter->SetTimeTag(bulkCreationTime); // std::format("{:%Y%m%d%H%M%OS}", std::chrono::system_clock::now())
        fPrinter->Print(commandsNamesList);
    }
    

//     output->Print("bulk: ");
//     for (size_t i = 0; i < commandsList.size(); i++)
//     {
//         if (i == 0)
//             output->Print(commandsList[i].GetCommandName());
//         else 
//             output->Print(", " + commandsList[i].GetCommandName());
//     }
//     output->Print("\n");
}
