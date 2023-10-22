#include "filter.h"

namespace my
{
    std::vector<my::ip_adress> Filter_1(const std::vector<my::ip_adress>& ip_pool)
    {
        std::vector<my::ip_adress> r;

        for (my::ip_adress ip : ip_pool)
            if (ip[0] == 1)
                r.push_back(ip);

        return r;
    }

    std::vector<my::ip_adress> Filter_46_70(const std::vector<my::ip_adress>& ip_pool)
    {
        std::vector<my::ip_adress> r;

        for (my::ip_adress ip : ip_pool)
            if (ip[0] == 46 && ip[1] == 70)
                r.push_back(ip);

        return r;
    }

    std::vector<my::ip_adress> Filter_any46(const std::vector<my::ip_adress>& ip_pool)
    {
        std::vector<my::ip_adress> r;

        for (my::ip_adress ip : ip_pool)
            if (ip[0] == 46 || ip[1] == 46 || ip[2] == 46 || ip[3] == 46)
                r.push_back(ip);

        return r;
    }
}