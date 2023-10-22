#include <iostream>

#include "../lib/headers/Moderator.h"

int main()
{
    std::string n;
    std::getline(std::cin, n);
    Moderator mod(std::stoi(n), std::cin, std::cout);
    std::cin.clear();
    mod.StartReading();

    return 0;
}
