/**
 * @file test_dig_t_only.cpp
 * @brief Test solo de dig_t.hpp para aislar problemas MSVC
 */

#include <iostream>

// Solo incluir dig_t.hpp
#include "include/dig_t.hpp"

int main()
{
    std::cout << "Test solo dig_t.hpp...\n";

    // Test básico de dig_t
    using dig_t = NumRepr::dig_t<10>;
    dig_t d1{5};
    dig_t d2{3};

    std::cout << "dig_t creado: " << d1.get() << std::endl;
    std::cout << "dig_t creado: " << d2.get() << std::endl;
    std::cout << "Test dig_t.hpp completado!\n";
    return 0;
}