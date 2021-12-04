#include "../vec_t.h"
#include <iostream>

int main()
{
    tci::vec_t<double, 2> a1 = {-2.5, 2};
    tci::vec_t<double, 3> b1 = {1, 0.5, 5};
    tci::vec_t<double, 2> a2 = {1, 2};
    tci::vec_t<double, 3> b2 = {1, -1.5, 0};
    for (auto i : a1 + b1)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << (a1 & a2) << std::endl;
    for (auto i : b1 & b2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}