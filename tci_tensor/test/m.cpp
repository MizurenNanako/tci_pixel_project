#include "../vec_t.cpp"
#include <iostream>

int main()
{
    tci::vec_t<int, 5> a = {1, 2, 3, 4, 5, 6};
    for (auto i : a * 2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}