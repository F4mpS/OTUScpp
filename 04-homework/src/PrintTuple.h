#pragma once

#include <iostream>

namespace my
{
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

    template <std::ostream &stream, typename Tuple, std::size_t... index>
    void PrintTupleCycle(const Tuple &t, std::index_sequence<index...>)
    {
        (PrintTupleElement<stream, index>(std::get<index>(t)), ...);
    }

    template <std::ostream &stream = std::cout, typename Tuple, std::size_t tuple_size = std::tuple_size_v<Tuple>>
    void PrintTuple(const Tuple &t)
    {
        PrintTupleCycle<stream>(t, std::make_index_sequence<tuple_size>{});
    }
} // namespace my