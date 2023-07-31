#include "sort.h"

namespace my
{
    void LexicographicallySort(std::vector<my::ip_adress> &ip_pool)
    {
        std::sort(ip_pool.begin(), ip_pool.end(), [](my::ip_adress &rhv, my::ip_adress &lhv)
                  { return rhv > lhv; });
    }
}
