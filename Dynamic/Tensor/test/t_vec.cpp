#include "../vec_t.h"
#include <iostream>
#include <algorithm>

template <typename T>
void p(const tci::vec_t<T> &q, const char str[])
{
    std::cout << str << '\t';
    for (auto i : q)
    {
        std::cout << i << '\t';
    }
    std::cout << std::endl;
}

template <typename T>
void pp(const T &q, const char str[])
{
    std::cout << str << '\t';
    std::cout << q << '\t';
    std::cout << std::endl;
}

int main()
{
    tci::vec_t<double> a = {1, 2, 3, -3, 4};
    tci::vec_t<double> b = {1, 2, 3, 8, 9};
    p(a, "a");
    p(b, "b");
    std::cout << std::endl;
}