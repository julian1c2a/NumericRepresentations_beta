#include <iostream>

// Test minimal para debug GCC
#include "../include/dig_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "=== TEST MINIMAL GCC DEBUG ===" << std::endl;

    // Test muy básico
    dig_t<10> a(5u);
    dig_t<10> b(3u);

    std::cout << "a = " << a.get() << std::endl;
    std::cout << "b = " << b.get() << std::endl;

    dig_t<10> c = a + b;
    std::cout << "a + b = " << c.get() << std::endl;

    std::cout << "✅ Test básico completado" << std::endl;

    return 0;
}