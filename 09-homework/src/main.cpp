#include <iostream>

#include "async.h"

int main()
{
    // PART 1
    // working with lib from 07-homework
    // std::string n; // future bulk size
    // std::getline(std::cin, n);
    // Moderator mod(std::stoi(n), std::cin);
    // mod.AddOutputFile("bulk");
    // mod.AddOutputFile("bulk");
    // mod.AddOutputStream(std::cout);
    // std::cin.clear();
    // mod.StartReading();

    // ---------------------------------------------------------------------------

    // PART 2

    std::size_t bulk = 5;
    auto h = async::connect(bulk);
    auto h2 = async::connect(bulk);
    async::receive(h, "1", 1);
    async::receive(h2, "1\n", 2);
    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);
    async::disconnect(h);
    async::disconnect(h2);

    return 0;
}
