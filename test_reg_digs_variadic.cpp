/**
 * @file test_reg_digs_variadic.cpp
 * @brief Test específico del constructor variádico de reg_digs_t
 */

#include <iostream>

// Usar rutas correctas
#include "include/dig_t.hpp"
#include "include/reg_digs_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "Test constructor variádico de reg_digs_t...\n";

    std::cout << "1. Test dig_t individuales...\n";
    dig_t<10> d1{1}, d2{2}, d3{3};
    std::cout << "   ✅ dig_t creados: " << d1.get() << ", " << d2.get() << ", " << d3.get() << "\n";

    std::cout << "2. Test constructor variádico (requiere flags extendidos)...\n";
    // ESTE CONSTRUCTOR REQUIERE: /constexpr:depth2048 /constexpr:steps1048576 /bigobj
    reg_digs_t<10, 3> test_variadic{d1, d2, d3};
    std::cout << "   ✅ Constructor variádico exitoso\n";

    std::cout << "3. Test lectura del resultado...\n";
    std::cout << "   Valores: " << test_variadic[0].get() << ", "
              << test_variadic[1].get() << ", "
              << test_variadic[2].get() << "\n";

    std::cout << "Test constructor variádico completado!\n";
    return 0;
}