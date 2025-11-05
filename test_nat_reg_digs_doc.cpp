/**
 * @file test_nat_reg_digs_doc.cpp
 * @brief Prueba de documentación de nat_reg_digs_t.hpp
 *
 * Este archivo verifica que la documentación añadida a nat_reg_digs_t.hpp
 * funciona correctamente con el sistema de compilación y no introduce errores.
 */

#include <iostream>
#include "include/nat_reg_digs_t.hpp"
#include "include/dig_t_display_helpers.hpp" // Para solucionar problemas de uint8_t

using namespace NumRepr;

int main()
{
    std::cout << "=== Test nat_reg_digs_t Documentation ===" << std::endl;

    // Test constructores factory
    std::cout << "\n--- Factory Methods ---" << std::endl;
    auto zero = nat_reg_digs_t<10, 4>::regd_0();
    auto one = nat_reg_digs_t<10, 4>::regd_1();
    auto base = nat_reg_digs_t<10, 4>::regd_B();

    std::cout << "zero: " << zero.to_string() << std::endl;
    std::cout << "one: " << one.to_string() << std::endl;
    std::cout << "base (10): " << base.to_string() << std::endl;

    // Test constructores desde enteros
    std::cout << "\n--- Constructor from integers ---" << std::endl;
    nat_reg_digs_t<10, 4> num1{1, 2, 3, 4}; // {1, 2, 3, 4} -> 4321 en base 10
    nat_reg_digs_t<10, 4> num2{9, 9, 9, 9}; // {9, 9, 9, 9} -> 9999 en base 10

    std::cout << "num1 {1,2,3,4}: " << num1.to_string() << std::endl;
    std::cout << "num2 {9,9,9,9}: " << num2.to_string() << std::endl;

    // Test constructor desde lista de inicialización
    std::cout << "\n--- Constructor from initializer list ---" << std::endl;
    nat_reg_digs_t<10, 4> num3{{5, 6, 7, 8}};
    std::cout << "num3 {{5,6,7,8}}: " << num3.to_string() << std::endl;

    // Test operaciones básicas
    std::cout << "\n--- Basic Operations ---" << std::endl;
    auto sum = num1 + num2;
    std::cout << "num1 + num2: " << sum.to_string() << std::endl;

    // Test con base pequeña para mostrar helpers de uint8_t
    std::cout << "\n--- uint8_t base test (base 5) ---" << std::endl;
    nat_reg_digs_t<5, 3> small_base{4, 4, 4}; // máximo en base 5
    std::cout << "base 5 number {4,4,4}: " << small_base.to_string() << std::endl;

    // Acceso a dígitos individuales con display helpers
    std::cout << "Individual digits: ";
    for (size_t i = 0; i < 3; ++i)
    {
        auto digit = small_base.const_by_index(i);
        std::cout << "[" << i << "]=" << display(digit) << " ";
    }
    std::cout << std::endl;

    // Test rango máximo
    std::cout << "\n--- Range test ---" << std::endl;
    auto max_val = nat_reg_digs_t<10, 2>::regd_pow_n_B_m1<2>(); // 10^2 - 1 = 99
    std::cout << "Max for base 10, length 2: " << max_val.to_string() << std::endl;

    std::cout << "\n=== All tests completed successfully ===" << std::endl;
    return 0;
}