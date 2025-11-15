#include <iostream>
#include <dig_t.hpp>

using namespace NumRepr;

int main()
{
    std::cout << "Test simple de dig_t" << std::endl;

    dig_t<10> d1(5u);
    dig_t<10> d2(3u);

    auto sum = d1 + d2;

    std::cout << "5 + 3 = " << sum.get() << std::endl;

    return 0;
}