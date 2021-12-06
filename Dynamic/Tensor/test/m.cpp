#include "../vec_t.h"
#include <iostream>
#include <algorithm>

void p(const tci::vec_t<double> &q, const char str[])
{
    std::cout << str << '\t';
    for (auto i : q)
    {
        std::cout << i << '\t';
    }
    std::cout << std::endl;
}

int main()
{
    tci::vec_t<double> a = {-2.5, 2, 3};
    tci::vec_t<double> b = {1, 2, 3, 8, 9};
    p(a, "a");
    p(b, "b");
    p(a + b, "a+b");
    p(b - a, "b-a");
    p(a * b, "a*b");
    p(a + 1.0, "a+1");
    std::cout << std::endl;
}