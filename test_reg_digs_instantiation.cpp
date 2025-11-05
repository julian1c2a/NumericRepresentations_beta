/**
 * @file test_reg_digs_instantiation.cpp
 * @brief Test gradual de instanciación de reg_digs_t para encontrar problema MSVC
 */

#include <iostream>

// Usar rutas correctas
#include "include/dig_t.hpp"
#include "include/reg_digs_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "Test gradual de reg_digs_t...\n";

    std::cout << "1. Test tipos básicos...\n";
    using dig_t_10 = dig_t<10>;
    using reg_digs_3_10 = reg_digs_t<10, 3>;
    std::cout << "   ✅ Tipos definidos\n";

    std::cout << "2. Test constructor por defecto...\n";
    reg_digs_3_10 test_default;
    std::cout << "   ✅ Constructor por defecto\n";

    std::cout << "3. Test acceso básico...\n";
    test_default[0] = dig_t_10(5);
    std::cout << "   ✅ Asignación a elemento [0]\n";

    std::cout << "4. Test lectura...\n";
    auto valor = test_default[0].get();
    std::cout << "   ✅ Lectura: " << valor << "\n";

    std::cout << "Test reg_digs_t básico completado!\n";
    return 0;
}