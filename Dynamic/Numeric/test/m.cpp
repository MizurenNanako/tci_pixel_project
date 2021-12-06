#include "../rational.h"

int main()
{
    ration_t a{3, 4}, b{};
    std::cout << a << std::endl;
    std::cout << (a ^ 40) << std::endl;
    return 0;
}