#include "filter.h"

namespace my
{
    std::vector<my::ip_adress> Filter_1(const std::vector<my::ip_adress>& ip_pool)
    {
        std::vector<my::ip_adress> r;

        for (my::ip_adress ip : ip_pool)
            if (ip.n1 == 1)
                r.push_back(ip);

        return r;
    }

    std::vector<my::ip_adress> Filter_46_70(const std::vector<my::ip_adress>& ip_pool)
    {
        std::vector<my::ip_adress> r;

        for (my::ip_adress ip : ip_pool)
            if (ip.n1 == 46 && ip.n2 == 70)
                r.push_back(ip);

        return r;
    }

    std::vector<my::ip_adress> Filter_any46(const std::vector<my::ip_adress>& ip_pool)
    {
        std::vector<my::ip_adress> r;

        for (my::ip_adress ip : ip_pool)
            if (ip.n1 == 46 || ip.n2 == 46 || ip.n3 == 46 || ip.n4 == 46)
                r.push_back(ip);

        return r;
    }
}