/**
 * @file test_reg_digs_msvc.cpp
 * @brief Test mínimo de reg_digs_t.hpp para identificar problema MSVC específico
 */

#include <iostream>
#include <array>

// Incluir solo lo mínimo necesario
#include "include/basic_types.hpp"
#include "include/dig_t.hpp"

// Test directo sin utilities.hpp
int main()
{
    std::cout << "Test mínimo reg_digs_t sin utilities...\n";

    // Test básico de dig_t
    using dig_t = numeric_representations_ns::dig_t<10>;
    constexpr dig_t d1{5};
    constexpr dig_t d2{3};

    std::cout << "dig_t creado: " << static_cast<unsigned>(d1) << std::endl;
    std::cout << "dig_t creado: " << static_cast<unsigned>(d2) << std::endl;

    std::cout << "Test básico completado!\n";
    return 0;
}