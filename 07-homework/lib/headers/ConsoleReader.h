#pragma once

#include <iostream>

class Moderator;

class ConsoleReader
{
public:
    ConsoleReader(Moderator&, std::istream&);
    ~ConsoleReader() = default;
    
    void Start();
private:
    Moderator* modPtr;
    std::istream& inStream;
};

