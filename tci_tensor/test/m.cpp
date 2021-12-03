#include "../vec_t.h"
#include <iostream>

int main()
{
    tci::vec_t<double, 2> a1 = {-2.5, 0};
    tci::vec_t<double, 2> b1 = {0, 0.5};
    std::cout << (a1 & b1) << std::endl;

    tci::vec_t<double, 3> a2 = {-2.5, 0};
    tci::vec_t<double, 3> b2 = {0, 0.5};

    for (auto i : a2 & b2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}