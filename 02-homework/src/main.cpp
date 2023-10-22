#include <iostream>

#include "utilities/split.h"
#include "utilities/sort.h"
#include "utilities/filter.h"

#include "ip.h"

int main()
{
    try
    {
        std::vector<my::ip_adress> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> ip_line = my::Split(line, '\t');
            ip_pool.push_back(my::SplitToIp(my::Split(ip_line.at(0), '.')));
        }

        // my::LexicographicallySort(ip_pool);

        for (my::ip_adress& ip : ip_pool)
            my::PrintIp(ip);

        // for(my::ip_adress& ip : my::Filter_1(ip_pool))
        //     my::PrintIp(ip);

        // for(my::ip_adress& ip : my::Filter_46_70(ip_pool))
        //     my::PrintIp(ip);

        // for(my::ip_adress& ip : my::Filter_any46(ip_pool))
        //     my::PrintIp(ip);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
