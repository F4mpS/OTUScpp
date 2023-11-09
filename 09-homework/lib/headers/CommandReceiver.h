#pragma once

#include <string>

class Moderator;

class CommandReceiver
{
public:
    CommandReceiver(Moderator&);
    ~CommandReceiver();
    
    void Receive(std::string);
private:
    Moderator* modPtr;
};
