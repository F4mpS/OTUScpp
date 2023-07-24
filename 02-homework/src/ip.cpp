#include "ip.h"

namespace my
{
    my::ip_adress SplitToIp(const std::vector<std::string> &str)
    {
        my::ip_adress r;
        try
        {
            if (str.size() != 4)
            {
                throw("Incorrect IPv4 adress!!!");
            }

            uint8_t *rFirst = &r.n1;
            
            for (int i = 0; i < 4; i++)
            {
                *(rFirst + i) = static_cast<uint8_t>(std::stoi(str.at(i)));
            }
            rFirst = nullptr;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        return r;
    }

    void PrintIp(const my::ip_adress& ip)
    {
        std::cout << static_cast<int>(ip.n1) << '.'
                  << static_cast<int>(ip.n2) << '.'
                  << static_cast<int>(ip.n3) << '.'
                  << static_cast<int>(ip.n4) << std::endl;
    }

    bool CompareIp(const my::ip_adress& rhv, const my::ip_adress& lhv)
    {
        return std::tie(rhv.n1, rhv.n2, rhv.n3, rhv.n4) == std::tie(lhv.n1, lhv.n2, lhv.n3, lhv.n4);
    }
}
