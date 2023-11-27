#pragma once

#include <string>
#include <memory>
#include <mutex>

class Moderator;

class CommandReceiver
{
public:
    CommandReceiver(Moderator&);
    ~CommandReceiver();
    
    void Receive(std::string);
private:
    Moderator* modPtr;
    std::mutex mutex;
};
