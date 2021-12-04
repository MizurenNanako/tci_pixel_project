#include "../vec_t.h"
#include <iostream>
#include <algorithm>

int main()
{
    tci::vec_t<double, 3> a = {-2.5, 2, 3};
    tci::vec_t<double, 4> b = a;
    tci::vec_t<double, 2> c = a;
    for (auto i : b)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (auto i : c)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}