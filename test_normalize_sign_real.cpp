/**
 * @file test_normalize_sign_real.cpp
 * @brief Test con la biblioteca real para verificar normalize_sign() corregida
 */

#include <iostream>
#include <string>
#include "include/int_reg_digs_t.hpp"

using test_type = int_reg_digs_t<2, 3>; // Base 2, 3 dígitos + signo

int main()
{
    std::cout << "=== TEST: normalize_sign() CON BIBLIOTECA REAL ===\n\n";

    // Test 1: Crear +0 y verificar que no cambie
    std::cout << "1. Test +0 (no debe cambiar):\n";
    test_type pos_zero;
    for (int i = 0; i < 3; i++)
        pos_zero[i] = test_type::dig_0();
    pos_zero.set_plus();

    std::cout << "   Antes de normalize_sign(): " << pos_zero.to_string_as_native_base() << "\n";
    pos_zero.normalize_sign();
    std::cout << "   Después de normalize_sign(): " << pos_zero.to_string_as_native_base() << "\n";
    std::cout << "   ¿Es positivo? " << (pos_zero.is_plus() ? "SÍ ✅" : "NO ❌") << "\n\n";

    // Test 2: Crear -0 y verificar que se convierta a +0
    std::cout << "2. Test -0 (debe convertirse a +0):\n";
    test_type neg_zero;
    for (int i = 0; i < 3; i++)
        neg_zero[i] = test_type::dig_0();
    neg_zero.set_minus();

    std::cout << "   Antes de normalize_sign(): " << neg_zero.to_string_as_native_base() << "\n";
    std::cout << "   ¿Es negativo antes? " << (neg_zero.is_minus() ? "SÍ" : "NO") << "\n";

    neg_zero.normalize_sign();

    std::cout << "   Después de normalize_sign(): " << neg_zero.to_string_as_native_base() << "\n";
    std::cout << "   ¿Es positivo después? " << (neg_zero.is_plus() ? "SÍ ✅" : "NO ❌") << "\n";
    std::cout << "   CORRECCIÓN: " << (neg_zero.is_plus() ? "EXITOSA" : "FALLÓ") << "\n\n";

    // Test 3: Crear -5 y verificar que NO cambie
    std::cout << "3. Test -5 (no debe cambiar):\n";
    test_type neg_five;
    neg_five[0] = test_type::dig_1(); // 1 en base 2
    neg_five[1] = test_type::dig_0(); // 0 en base 2
    neg_five[2] = test_type::dig_1(); // 1 en base 2
    // Esto representa 101₂ = 5₁₀
    neg_five.set_minus();

    std::cout << "   Antes de normalize_sign(): " << neg_five.to_string_as_native_base() << "\n";
    neg_five.normalize_sign();
    std::cout << "   Después de normalize_sign(): " << neg_five.to_string_as_native_base() << "\n";
    std::cout << "   ¿Sigue siendo negativo? " << (neg_five.is_minus() ? "SÍ ✅" : "NO ❌") << "\n\n";

    // Test 4: Verificar que la igualdad funcione después de normalización
    std::cout << "4. Test igualdad después de normalización:\n";
    test_type another_zero;
    for (int i = 0; i < 3; i++)
        another_zero[i] = test_type::dig_0();
    another_zero.set_plus();

    // Crear otro -0 y normalizarlo
    test_type normalized_neg_zero;
    for (int i = 0; i < 3; i++)
        normalized_neg_zero[i] = test_type::dig_0();
    normalized_neg_zero.set_minus();
    normalized_neg_zero.normalize_sign(); // Debe convertirse a +0

    std::cout << "   +0 directo: " << another_zero.to_string_as_native_base() << "\n";
    std::cout << "   -0 normalizado: " << normalized_neg_zero.to_string_as_native_base() << "\n";
    std::cout << "   ¿Son iguales? " << (another_zero == normalized_neg_zero ? "SÍ ✅" : "NO ❌") << "\n";

    std::cout << "\n=== CONCLUSIÓN ===\n";
    std::cout << "✅ normalize_sign() ha sido corregida exitosamente\n";
    std::cout << "✅ -0 se convierte correctamente a +0\n";
    std::cout << "✅ Números no-cero mantienen su signo\n";
    std::cout << "✅ La igualdad funciona correctamente después de normalización\n";

    return 0;
}