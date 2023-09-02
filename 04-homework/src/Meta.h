#pragma once

#include <iostream>
#include <type_traits>
#include <string>

namespace my
{
    /**
     * @brief Checks at compile-time that T is **string**.
     * @tparam T Some variable
     * @brief value is **false** if T **isn't string**
     *
     * @code
     *  template <typename T>
        struct is_string
        {
            static constexpr bool value = false;
        };
     * @endcode
     *
     */
    template <typename T>
    struct is_string
    {
        static constexpr bool value = false;
    };

    /**
     * @brief Checks at compile-time that T is **string**.
     * @tparam std::string
     * @brief value is **true** if T **is string**
     *
     * @code
     *  template <>
        struct is_string<std::string>
        {
            static constexpr bool value = true;
        };
     * @endcode
     *
     */
    template <>
    struct is_string<std::string>
    {
        static constexpr bool value = true;
    };

    /**
     * @brief Checks at compile-time that T contains an **iterator**.
     *
     * @tparam T Some kind of data structure
     *
     * @return If T contains an iterator **true**, otherwise **false**
     */
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