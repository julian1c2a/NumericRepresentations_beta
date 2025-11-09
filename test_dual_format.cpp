#include <iostream>
#include <sstream>
#include <cassert>
#include "core/dig_t.hpp"

using namespace NumRepr;

int main()
{
    // Test formato estricto d[n]B
    constexpr dig_t<10> d1("d[7]B10");
    static_assert(d1.get() == 7, "Error en parsing formato estricto");

    // Test formato legacy dig#n#B
    dig_t<10> d2("dig#5#B10");
    assert(d2.get() == 5);

    // Test parsing con módulo
    dig_t<10> d3("d[127]B10");
    assert(d3.get() == 7); // 127 % 10 = 7

    // Test salida
    std::cout << "d1: " << d1 << std::endl;
    std::cout << "d2: " << d2 << std::endl;
    std::cout << "d3: " << d3 << std::endl;

    // Test entrada desde stream
    std::istringstream iss1("d[8]B10");
    dig_t<10> d4;
    iss1 >> d4;
    assert(d4.get() == 8);
    std::cout << "d4 (from stream d[8]B10): " << d4 << std::endl;

    std::istringstream iss2("dig#9#B10");
    dig_t<10> d5;
    iss2 >> d5;
    assert(d5.get() == 9);
    std::cout << "d5 (from stream dig#9#B10): " << d5 << std::endl;

    std::cout << "Todos los tests pasaron correctamente!" << std::endl;
    return 0;
}