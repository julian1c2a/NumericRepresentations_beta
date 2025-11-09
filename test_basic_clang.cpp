#include <iostream>
#include "core/dig_t.hpp"

int main()
{
    std::cout << "Testing basic dig_t..." << std::endl;

    NumRepr::dig_t<10> d(5);
    std::cout << "d(5): " << d << std::endl;

    std::cout << "Test completado!" << std::endl;
    return 0;
}