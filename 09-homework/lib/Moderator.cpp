#include "headers/Moderator.h"

Moderator::Moderator(size_t bulkSize) : bulkContainer(new BulkContainer(*this, bulkSize)), receiver(new CommandReceiver(*this)) 
{
    AddOutputFile("bulk");
    AddOutputFile("bulk");
    AddOutputStream(std::cout);
}

Moderator::~Moderator()
{
    for (auto &printer : oPrinters)
        printer = nullptr;
    for (auto &printer : fPrinters)
        printer = nullptr;

    receiver->~CommandReceiver();
    receiver = nullptr;
    bulkContainer->~BulkContainer();
    bulkContainer = nullptr;
}

void Moderator::AddOutputStream(std::ostream& outS)
{
    oPrinters.emplace_back(new OstreamPrinter(outS));
}

void Moderator::AddOutputFile(std::string outFileName)
{
    fPrinters.emplace_back(new FilePrinter(outFileName + std::to_string(fPrinters.size())));
}

void Moderator::ReadBuffer(const char *data, size_t bufferSize)
{
    std::string userData(data);
    std::vector<std::string> receivedData = Split(userData, '\n');
        
    for (auto input : receivedData)
        if (input != "")
            receiver->Receive(input);

    receivedData.clear();
    (void)bufferSize;
}

void Moderator::EndReceiving()
{
    if (!bulkContainer->IsBraceOpen())
        bulkContainer->ClearBulk();

    this->~Moderator();
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
    printCounter++;
    std::vector<std::string> commandsNamesList;
    for (auto &command : commandsList)
        commandsNamesList.push_back(command.GetCommandName());

    for (auto &oPrinter : oPrinters)
    {
        std::thread log(&Moderator::callPrint, this, std::ref(oPrinter), commandsNamesList);
        log.join();
    }

    for (auto &fPrinter : fPrinters)
    {
        fPrinter->SetTags(bulkCreationTime, printCounter);
        std::thread file(&Moderator::callPrint, this, std::ref(fPrinter), commandsNamesList);
        file.join();
    }
}

void Moderator::callPrint(const IPrinter* printer, std::vector<std::string> msg)
{
    printer->Print(msg);
}
