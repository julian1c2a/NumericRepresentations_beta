#include <iostream>
#include <cassert>

// Test simple para dig_t
#include <core/dig_t.hpp>

using namespace NumRepr;

int main()
{
    std::cout << "=== TEST SIMPLE dig_t ===" << std::endl;

    // Test básico con base 10
    dig_t<10> d1; // Constructor por defecto
    std::cout << "dig_t<10> por defecto: " << d1.get() << std::endl;

    dig_t<10> d2(static_cast<unsigned int>(5)); // Constructor con valor
    std::cout << "dig_t<10> con valor 5: " << d2.get() << std::endl;

    std::cout << "✅ Test simple completado" << std::endl;
    return 0;
}