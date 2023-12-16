#define _ENFORCE_MATCHING_ALLOCATORS 0
#define _SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING

#include <iostream>
#include <map>
#include <memory>
#include <cassert>
#include <new>
#include <array>

#include "Allocator.h"
#include "List.h"

std::size_t Factorial(std::size_t n)
{
    if (n == 0)
        return 1;
    return n * Factorial(n - 1);
}

template <typename Allocator>
void FillMap(std::map<int, int, std::less<int>, Allocator> &map)
{
    for (size_t i = 0; i < 10; i++)
        map.emplace(i, Factorial(i));
}

template<typename Allocator>
void FillList(my::List<int, Allocator> &List)
{
    for (size_t i = 0; i < 10; i++)
        List.Push(Factorial(i));
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& stream, const std::pair<T, U>& pair)
{
    stream << pair.first << ' ' << pair.second;
    return stream;
}

template <typename Container>
void Print(Container &container)
{
    for (auto &e : container)
        std::cout << e << std::endl;
}

int main()
{
    std::map<int, int> mapStdAllocator; // work
    FillMap(mapStdAllocator); // work

    std::map<int, int, std::less<int>, my::Allocator<std::pair<int, int>, 10>> mapMyAllocator; // work
    FillMap(mapMyAllocator);
    
    std::cout << "START" << std::endl;
    Print(mapStdAllocator); // work
    Print(mapMyAllocator); // work
    std::cout << "END" << std::endl << std::endl;

    my::List<int> myListStdAllocator; // work
    FillList(myListStdAllocator); // work

    my::List<int, my::Allocator<int, 10>> myListMyAllocator; // work
    FillList(myListMyAllocator); // work
    
    std::cout << "START" << std::endl;
    Print(myListStdAllocator); // work
    Print(myListMyAllocator); // work
    std::cout << "END" << std::endl << std::endl;


    return 0;
}