#pragma once

#include <iostream>
#include <type_traits>
#include <string>

namespace my
{
    template <typename T>
    struct is_string
    {
        static constexpr bool value = false;
    };

    template <>
    struct is_string<std::string>
    {
        static constexpr bool value = true;
    };

    template <typename T>
    concept has_iterator = requires { typename T::iterator; };

    // template <typename... Args>
    // struct valid_tuple
    // {
    //     static constexpr bool value = true;
    // };

    // template <typename T>
    // struct valid_tuple<T>
    // {
    //     static constexpr bool value = true;
    // };

    // template <typename T, typename U, typename... Args>
    // struct valid_tuple
    // {
    //     static constexpr bool value = std::is_same<T, U> ? valid_tuple<U, Args...>::value : false;
    // };
} // namespace my