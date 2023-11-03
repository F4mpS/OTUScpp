#pragma once

#include <cstddef>
#include <boost/crc.hpp>

struct CRC32
{
    std::size_t operator()(void *data, std::size_t length)
    {
        boost::crc_32_type result;
        result.process_bytes(data, length);
        return result.checksum();
    }
};
