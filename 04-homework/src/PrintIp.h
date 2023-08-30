#pragma once

#include <iostream>
#include <type_traits>
#include <string>
#include <iterator>
#include <cstdint>

#include "Meta.h"
#include "PrintTuple.h"

template <typename Integer, typename Fake = typename std::enable_if<std::is_integral<Integer>::value, void>::type>
void print_ip(Integer ip, std::ostream &s = std::cout)
{
    for (long long i = sizeof(ip) - 1; i >= 0; i--)
    {
        if (i == 0)
            s << (size_t)(std::byte)(ip >> 0);
        else
            s << (size_t)(std::byte)(ip >> (i * 8)) << ".";
    }

    s << std::endl;
}

template <typename String, typename Fake = typename std::enable_if<my::is_string<String>::value, void>::type>
void print_ip(const String &ip, std::ostream &s = std::cout, Fake * = nullptr)
{
    s << ip << std::endl;
}

template <typename Container, typename Fake = typename std::enable_if<(my::has_iterator<Container> && !my::is_string<Container>::value), void>::type>
void print_ip(const Container &ip, std::ostream &s = std::cout)
{
    const char *dot = ".";
    std::copy(ip.begin(), std::prev(ip.end()), std::ostream_iterator<typename Container::value_type>(s, dot));
    s << *ip.rbegin() << std::endl;
}

template <typename Tuple, typename Fake = typename std::enable_if<(!my::has_iterator<Tuple> && !std::is_integral<Tuple>::value), void>::type>
/*typename Fake = typename std::enable_if<my::valid_tuple<Tuple>::value, void>::type*/
void print_ip(const Tuple &t, Tuple * = nullptr)
{
    my::PrintTuple(t);
}
