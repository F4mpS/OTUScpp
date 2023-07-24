#ifndef FILTER_H
#define FILTER_H

#include <vector>

#include "../ip.h"

namespace my
{
    std::vector<my::ip_adress> Filter_1(const std::vector<my::ip_adress>&);
    std::vector<my::ip_adress> Filter_46_70(const std::vector<my::ip_adress>&);
    std::vector<my::ip_adress> Filter_any46(const std::vector<my::ip_adress>&);
}

#endif