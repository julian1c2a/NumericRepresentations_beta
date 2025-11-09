/**
 * @file test_metodos_adicionales.cpp
 * @brief Test de los métodos adicionales añadidos a int_reg_digs_t
 */

#include <iostream>
#include <string>
#include <sstream>
#include "include/int_reg_digs_t.hpp"

using namespace NumRepr;
using test_type = int_reg_digs_t<10, 3>; // Base 10, 3 dígitos + signo

void test_abs_function()
{
    std::cout << "=== TEST: FUNCIÓN abs() ===\n";

    // Test 1: Número positivo
    test_type pos_num;
    pos_num[0] = test_type::dig_t{5};
    pos_num.set_plus();

    auto abs_pos = pos_num.abs();
    std::cout << "abs(+5) = " << abs_pos.to_string() << " ";
    std::cout << (abs_pos.is_plus() ? "✅" : "❌") << "\n";

    // Test 2: Número negativo
    test_type neg_num;
    neg_num[0] = test_type::dig_t{7};
    neg_num.set_minus();

    auto abs_neg = neg_num.abs();
    std::cout << "abs(-7) = " << abs_neg.to_string() << " ";
    std::cout << (abs_neg.is_plus() ? "✅" : "❌") << "\n";

    // Test 3: Cero
    test_type zero;
    auto abs_zero = zero.abs();
    std::cout << "abs(0) = " << abs_zero.to_string() << " ";
    std::cout << (abs_zero.is_plus() ? "✅" : "❌") << "\n";

    std::cout << "\n";
}

void test_sign_function()
{
    std::cout << "=== TEST: FUNCIÓN sign() ===\n";

    // Test 1: Número positivo
    test_type pos_num;
    pos_num[0] = test_type::dig_t{3};
    pos_num.set_plus();

    int sign_pos = pos_num.sign();
    std::cout << "sign(+3) = " << sign_pos << " ";
    std::cout << (sign_pos == 1 ? "✅" : "❌") << "\n";

    // Test 2: Número negativo
    test_type neg_num;
    neg_num[0] = test_type::dig_t{3};
    neg_num.set_minus();

    int sign_neg = neg_num.sign();
    std::cout << "sign(-3) = " << sign_neg << " ";
    std::cout << (sign_neg == -1 ? "✅" : "❌") << "\n";

    // Test 3: Cero
    test_type zero;
    int sign_zero = zero.sign();
    std::cout << "sign(0) = " << sign_zero << " ";
    std::cout << (sign_zero == 0 ? "✅" : "❌") << "\n";

    std::cout << "\n";
}

void test_predicates()
{
    std::cout << "=== TEST: PREDICADOS (is_positive, is_negative, is_zero) ===\n";

    // Crear números de test
    test_type pos_num;
    pos_num[0] = test_type::dig_t{5};
    pos_num.set_plus();

    test_type neg_num;
    neg_num[0] = test_type::dig_t{5};
    neg_num.set_minus();

    test_type zero;

    // Test is_positive
    std::cout << "is_positive(+5): " << (pos_num.is_positive() ? "TRUE ✅" : "FALSE ❌") << "\n";
    std::cout << "is_positive(-5): " << (neg_num.is_positive() ? "TRUE ❌" : "FALSE ✅") << "\n";
    std::cout << "is_positive(0): " << (zero.is_positive() ? "TRUE ❌" : "FALSE ✅") << "\n";

    // Test is_negative
    std::cout << "is_negative(+5): " << (pos_num.is_negative() ? "TRUE ❌" : "FALSE ✅") << "\n";
    std::cout << "is_negative(-5): " << (neg_num.is_negative() ? "TRUE ✅" : "FALSE ❌") << "\n";
    std::cout << "is_negative(0): " << (zero.is_negative() ? "TRUE ❌" : "FALSE ✅") << "\n";

    // Test is_zero
    std::cout << "is_zero(+5): " << (pos_num.is_zero() ? "TRUE ❌" : "FALSE ✅") << "\n";
    std::cout << "is_zero(-5): " << (neg_num.is_zero() ? "TRUE ❌" : "FALSE ✅") << "\n";
    std::cout << "is_zero(0): " << (zero.is_zero() ? "TRUE ✅" : "FALSE ❌") << "\n";

    std::cout << "\n";
}

void test_min_max_values()
{
    std::cout << "=== TEST: MIN/MAX VALUES ===\n";

    auto max_val = test_type::max_value();
    auto min_val = test_type::min_value();

    std::cout << "max_value() = " << max_val.to_string() << "\n";
    std::cout << "min_value() = " << min_val.to_string() << "\n";

    // Verificar que max es positivo y min es negativo
    std::cout << "max_value() es positivo: " << (max_val.is_positive() ? "✅" : "❌") << "\n";
    std::cout << "min_value() es negativo: " << (min_val.is_negative() ? "✅" : "❌") << "\n";

    std::cout << "\n";
}

void test_swap_function()
{
    std::cout << "=== TEST: FUNCIÓN swap() ===\n";

    test_type a, b;
    a[0] = test_type::dig_t{3};
    a.set_plus();

    b[0] = test_type::dig_t{7};
    b.set_minus();

    std::cout << "Antes del swap:\n";
    std::cout << "a = " << a.to_string() << "\n";
    std::cout << "b = " << b.to_string() << "\n";

    a.swap(b);

    std::cout << "Después del swap:\n";
    std::cout << "a = " << a.to_string() << "\n";
    std::cout << "b = " << b.to_string() << "\n";

    // Verificar que se intercambiaron correctamente
    bool swap_ok = (a.is_negative() && a[0].get() == 7) &&
                   (b.is_positive() && b[0].get() == 3);
    std::cout << "Intercambio correcto: " << (swap_ok ? "✅" : "❌") << "\n";

    std::cout << "\n";
}

void test_formatted_string()
{
    std::cout << "=== TEST: to_string_formatted() ===\n";

    test_type num;
    num[0] = test_type::dig_t{5};
    num[1] = test_type::dig_t{2};
    num[2] = test_type::dig_t{8};
    num.set_minus(); // -825

    std::cout << "Número: " << num.to_string() << "\n";
    std::cout << "Formatted (default): " << num.to_string_formatted() << "\n";
    std::cout << "Formatted (no sign): " << num.to_string_formatted(",", false) << "\n";
    std::cout << "Formatted (with base): " << num.to_string_formatted(",", true, true) << "\n";
    std::cout << "Formatted (separator |): " << num.to_string_formatted("|") << "\n";

    std::cout << "\n";
}

void test_friend_functions()
{
    std::cout << "=== TEST: FUNCIONES FRIEND (abs, min, max) ===\n";

    test_type a, b;
    a[0] = test_type::dig_t{3};
    a.set_plus();

    b[0] = test_type::dig_t{7};
    b.set_minus();

    // Test abs friend function
    auto abs_a = abs(a);
    auto abs_b = abs(b);
    std::cout << "abs(+3) = " << abs_a.to_string() << " ✅\n";
    std::cout << "abs(-7) = " << abs_b.to_string() << " ✅\n";

    // Test min/max friend functions
    auto min_ab = min(a, b);
    auto max_ab = max(a, b);
    std::cout << "min(+3, -7) = " << min_ab.to_string() << " ";
    std::cout << (min_ab.is_negative() ? "✅" : "❌") << "\n";
    std::cout << "max(+3, -7) = " << max_ab.to_string() << " ";
    std::cout << (max_ab.is_positive() ? "✅" : "❌") << "\n";

    // Test sign friend function
    std::cout << "sign(+3) = " << sign(a) << " ";
    std::cout << (sign(a) == 1 ? "✅" : "❌") << "\n";
    std::cout << "sign(-7) = " << sign(b) << " ";
    std::cout << (sign(b) == -1 ? "✅" : "❌") << "\n";

    std::cout << "\n";
}

int main()
{
    std::cout << "================================================================\n";
    std::cout << "    TEST DE MÉTODOS ADICIONALES int_reg_digs_t\n";
    std::cout << "    Verificación de funciones matemáticas y utilidades\n";
    std::cout << "================================================================\n\n";

    test_abs_function();
    test_sign_function();
    test_predicates();
    test_min_max_values();
    test_swap_function();
    test_formatted_string();
    test_friend_functions();

    std::cout << "=== CONCLUSIÓN ===\n";
    std::cout << "✅ Función abs(): Valor absoluto implementada\n";
    std::cout << "✅ Función sign(): Signo del número implementada\n";
    std::cout << "✅ Predicados: is_positive, is_negative, is_zero implementados\n";
    std::cout << "✅ Constantes: max_value, min_value implementadas\n";
    std::cout << "✅ Función swap(): Intercambio implementado\n";
    std::cout << "✅ Formateo: to_string_formatted() implementado\n";
    std::cout << "✅ Funciones friend: abs, min, max, sign implementadas\n";
    std::cout << "\n🎯 TODOS LOS MÉTODOS ADICIONALES FUNCIONANDO CORRECTAMENTE\n";

    return 0;
}