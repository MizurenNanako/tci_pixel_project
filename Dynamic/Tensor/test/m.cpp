#include "../vec_t.h"
#include <iostream>
#include <algorithm>

int main()
{
    tci::vec_t<double> a = {-2.5, 2, 3};
    tci::vec_t<double> b = a;
    tci::vec_t<double> c = a;
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