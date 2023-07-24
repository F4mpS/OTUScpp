#include "sort.h"

namespace my
{
    void LexicographicallySort(std::vector<my::ip_adress> &ip_pool)
    {
        std::sort(ip_pool.begin(), ip_pool.end(), [](my::ip_adress &rhv, my::ip_adress &lhv)
                  { return std::tie(rhv.n1, rhv.n2, rhv.n3, rhv.n4) > std::tie(lhv.n1, lhv.n2, lhv.n3, lhv.n4); });
    }
}
