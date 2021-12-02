#include "../vec_t.cpp"
#include <iostream>

int main()
{
    tci::vec_t<double, 2> a = {-2.5, 0};
    tci::vec_t<double, 2> b = {0, 0.5};
    std::cout << (a & b) << std::endl;
    /*
    for (auto i : a & b)
    {
        std::cout << i << " ";
    }
    */
    std::cout << std::endl;
}