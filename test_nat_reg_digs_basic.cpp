/**
 * @file test_nat_reg_digs_basic.cpp
 * @brief Prueba básica de documentación de nat_reg_digs_t.hpp
 *
 * Este archivo verifica que la documentación añadida a nat_reg_digs_t.hpp
 * funciona correctamente con el sistema de compilación.
 */

#include <iostream>
#include "include/nat_reg_digs_t.hpp"
#include "core/dig_t_display_helpers.hpp" // Para solucionar problemas de uint8_t

using namespace NumRepr;

int main()
{
    std::cout << "=== Test nat_reg_digs_t Documentation ===" << std::endl;

    // Test constructor básico
    std::cout << "\n--- Basic Constructor ---" << std::endl;
    nat_reg_digs_t<10, 4> num1;
    std::cout << "Default constructor: " << num1.to_string() << std::endl;

    // Test constructor desde lista de inicialización
    std::cout << "\n--- Constructor from initializer list ---" << std::endl;
    nat_reg_digs_t<10, 4> num2{{dig_t<10>{5}, dig_t<10>{6}, dig_t<10>{7}, dig_t<10>{8}}};
    std::cout << "From initializer list: " << num2.to_string() << std::endl;

    // Test constructor variádico con dig_t
    std::cout << "\n--- Variadic Constructor ---" << std::endl;
    nat_reg_digs_t<10, 4> num3{dig_t<10>{1}, dig_t<10>{2}, dig_t<10>{3}, dig_t<10>{4}};
    std::cout << "Variadic construction: " << num3.to_string() << std::endl;

    // Test operaciones básicas
    std::cout << "\n--- Basic Operations ---" << std::endl;
    auto sum = num2 + num3;
    std::cout << "Addition result: " << sum.to_string() << std::endl;

    // Test con base pequeña para mostrar helpers de uint8_t
    std::cout << "\n--- Small base test (uint8_t case) ---" << std::endl;
    nat_reg_digs_t<5, 3> small_base{dig_t<5>{4}, dig_t<5>{4}, dig_t<5>{4}};
    std::cout << "Base 5 number: " << small_base.to_string() << std::endl;

    // Test de conversión simple
    std::cout << "\n--- Type conversions ---" << std::endl;
    nat_reg_digs_t<10, 4> converted;
    converted = dig_t<10>{7}; // Asignación desde dígito
    std::cout << "From single digit: " << converted.to_string() << std::endl;

    std::cout << "\n=== Basic documentation test completed ===" << std::endl;
    return 0;
}