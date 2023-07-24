#ifndef IP_H
#define IP_H

#include <iostream>
#include <vector>
#include <string> 
#include <cstdint>
#include <tuple>

namespace my 
{
    struct ip_adress
    {
        uint8_t n1;
        uint8_t n2;
        uint8_t n3;
        uint8_t n4;
    };

    my::ip_adress SplitToIp(const std::vector<std::string>&);
    void PrintIp(const my::ip_adress&);
    bool CompareIp(const my::ip_adress&, const my::ip_adress&);
}

#endif
