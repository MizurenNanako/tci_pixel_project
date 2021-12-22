#include "../mat_t.h"
#include <iostream>

template <typename T>
void pv(tci::vec_t<T> &q, const char str[])
{
    std::cout << str << '\t';
    for (auto i : q)
    {
        std::cout << i << '\t';
    }
    std::cout << std::endl;
}

template <typename T>
void pm(tci::mat_t<T> &q, const char str[])
{
    std::cout << str << '\n';
    for (auto i : q)
    {
        pv(i, str);
        // std::cout << str << std::endl;
    }
    std::cout << std::endl;
}

template <typename T>
void p(const T &q, const char str[])
{
    std::cout << str << '\t';
    std::cout << q << '\t';
    std::cout << std::endl;
}

int main()
{
    tci::mat_t<int> m{5, 8};
    for (auto &v : m)
    {
        static int i = 0;
        for (auto &t : v)
        {
            t = i++;
        }
    }
    pm(m, "mat m");
    return 0;
}