#pragma once

#include <iostream>
#include <type_traits>
#include <string>
#include <iterator>
#include <cstdint>

#include "Meta.h"
#include "PrintTuple.h"

namespace my
{

    /**
     * @brief Template function for printing IP from integrals.
     * @brief Called if T is integral.
     * @tparam Integer integral number type, representing IP
     * @tparam Fake implements the SFINAE rule
     * @param[in] ip IP address to be printed
     * @param[in] s output stream where to print IP address
     * @brief Printing **ip** to **s** like: *byte_n.---byte_2.---byte_1*, **n** = Container.size().
     */
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

    /**
     * @brief Template function for printing IP from string.
     * @brief Called if T is string.
     * @tparam String string type, representing IP
     * @tparam Fake implements SFINAE rule
     * @param[in] ip IP address to be printed
     * @param[in] s output stream where to print IP address
     * @brief Printing **ip** to **s** as a string.
     */
    template <typename String, typename Fake = typename std::enable_if<my::is_string<String>::value, void>::type>
    void print_ip(const String &ip, std::ostream &s = std::cout, Fake * = nullptr)
    {
        s << ip << std::endl;
    }

    /**
     * @brief Template function for printing IP from containers.
     * @brief Called if T is iterable container.
     * @tparam Container container type, that contains iterator implemenrtation (`except std::string`)
     * @tparam Fake implements SFINAE rule
     * @param[in] ip IP address to be printed
     * @param[in] s output stream where to print IP address
     * @brief Printing **ip** to **s** like: *elem_1.elem_2.---elem_n*, **n** = Container.size().
     */
    template <typename Container, typename Fake = typename std::enable_if<(my::has_iterator<Container> && !my::is_string<Container>::value), void>::type>
    void print_ip(const Container &ip, std::ostream &s = std::cout)
    {
        const char *dot = ".";
        std::copy(ip.begin(), std::prev(ip.end()), std::ostream_iterator<typename Container::value_type>(s, dot));
        s << *ip.rbegin() << std::endl;
    }

    /**
     * @brief Template function for printing IP from tuples
     * @brief Called if T is not iterable container (tuple).
     * @tparam Tuple any type, that doesn't contain iterator implemenrtation (`except integrals`)
     * @tparam Fake implements SFINAE rule
     * @param[in] t tuple
     * @param[in] s output stream where to print IP address
     * @brief Printing **ip** to **s** like: *elem_1.elem_2.---elem_n*, **n** = size of tuple.
     * @todo Implement SFINAE rule to check if a tuple is valid
     */
    template <typename Tuple, typename Fake = typename std::enable_if<(!my::has_iterator<Tuple> && !std::is_integral<Tuple>::value), void>::type>
    /*typename Fake = typename std::enable_if<my::valid_tuple<Tuple>::value, void>::type*/
    void print_ip(const Tuple &t, Tuple * = nullptr)
    {
        my::PrintTuple(t);
    }
} // namespace my
