#include <iostream>

#include "../lib/headers/Moderator.h"

int main()
{
    std::string n; // future bulk size
    std::getline(std::cin, n);
    Moderator mod(std::stoi(n), std::cin);
    mod.AddOutputFile("bulk");
    mod.AddOutputStream(std::cout);
    std::cin.clear();
    mod.StartReading();
    return 0;
}
