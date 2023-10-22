#pragma once

#include <iostream>

namespace my
{
    /**
     * @brief Template function for printing tuple.
     * @tparam stream output stream where to print tuple
     * @tparam index tuple element index
     * @tparam T tuple element type
     * @param[in] value elem[**index**] of the tuple
     * @brief Puts **value** into **stream**
     */
    template <std::ostream &stream, std::size_t index, typename T>
    void PrintTupleElement(const T &value)
    {
        if constexpr (!index)
        {
            stream << value;
        }
        else
        {
            stream << '.' << value;
        }
    }

    /**
     * @brief Template *gasket for printing tuple.
     * @tparam stream output stream where to print tuple
     * @tparam Tuple tuple
     * @tparam index contains index sequence of tuple
     * @param[in] t tuple
     * @brief Printing **tuple** to **stream** like: *elem_1.elem_2.---elem_n*, **n** = tuple_size.
     * @brief The function contains a second parameter, *std::index_sequence<index...>*, that allows you to pass user's output stream.
     * 
     * @post *gasket because it's not a full function that prints a tuple. This is a chain of three functions that together implement true tuple printing.
     */
    template <std::ostream &stream, typename Tuple, std::size_t... index>
    void PrintTupleCycle(const Tuple &t, std::index_sequence<index...>)
    {
        (PrintTupleElement<stream, index>(std::get<index>(t)), ...);
    }

    /**
     * @brief Template *gasket for printing tuple.
     * @tparam stream output stream where to print tuple (`default: std::cout`)
     * @tparam Tuple tuple
     * @tparam tuple_size gets size of Tuple at compile-time
     * @param[in] t tuple
     * @brief Printing **tuple** to **stream** like: *elem_1.elem_2.---elem_n*, **n** = tuple_size.
     *
     * @post *gasket because it's not a full function that prints a tuple. This is a chain of three functions that together implement true tuple printing.
     */
    template <std::ostream &stream = std::cout, typename Tuple, std::size_t tuple_size = std::tuple_size_v<Tuple>>
    void PrintTuple(const Tuple &t)
    {
        PrintTupleCycle<stream>(t, std::make_index_sequence<tuple_size>{});
    }
} // namespace my