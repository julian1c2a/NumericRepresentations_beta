/**
 * @file test_minimal_reg_digs.cpp
 * @brief Test mínimo solo incluyendo reg_digs_t.hpp
 */

#include <iostream>

// Solo incluir reg_digs_t.hpp para encontrar el problema exacto
#include "include/reg_digs_t.hpp"

int main()
{
    std::cout << "Test mínimo reg_digs_t.hpp...\n";

    // No instanciar nada, solo probar la inclusión
    std::cout << "Inclusión de reg_digs_t.hpp exitosa!\n";
    return 0;
}