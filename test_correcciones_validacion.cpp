/**
 * @file test_correcciones_validacion.cpp
 * @brief Tests de validación para las correcciones críticas aplicadas
 *
 * Verificación de que las correcciones de operadores de comparación
 * y normalización funcionan correctamente.
 */

#include "int_reg_digs_t.hpp"
#include <iostream>
#include <cassert>

using namespace NumRepr;

// Template de prueba: base 2, 3 dígitos + 1 signo = 4 total
using test_int_t = int_reg_digs_t<2, 3>;

void test_comparison_operators_negatives()
{
    std::cout << "=== TEST: Operadores de Comparación con Números Negativos ===\n";

    // Crear números de prueba usando factory methods
    auto neg_five = test_int_t::sregd_m1().operator*(5);  // -5
    auto neg_three = test_int_t::sregd_m1().operator*(3); // -3
    auto neg_one = test_int_t::sregd_m1();                // -1
    auto pos_two = test_int_t::sregd_1().operator*(2);    // +2
    auto pos_five = test_int_t::sregd_1().operator*(5);   // +5

    std::cout << "Números de prueba creados:\n";
    std::cout << "neg_five (debería ser -5)\n";
    std::cout << "neg_three (debería ser -3)\n";
    std::cout << "neg_one (debería ser -1)\n";
    std::cout << "pos_two (debería ser +2)\n";
    std::cout << "pos_five (debería ser +5)\n\n";

    std::cout << "TEST 1: Operador < con números negativos del mismo signo\n";
    std::cout << "-5 < -3 debería ser TRUE:\n";
    bool result1 = neg_five < neg_three;
    std::cout << "Resultado: " << (result1 ? "TRUE" : "FALSE");
    std::cout << " " << (result1 ? "✅ CORRECTO" : "❌ INCORRECTO") << "\n\n";

    std::cout << "-3 < -1 debería ser TRUE:\n";
    bool result2 = neg_three < neg_one;
    std::cout << "Resultado: " << (result2 ? "TRUE" : "FALSE");
    std::cout << " " << (result2 ? "✅ CORRECTO" : "❌ INCORRECTO") << "\n\n";

    std::cout << "TEST 2: Operador > con números negativos del mismo signo\n";
    std::cout << "-1 > -3 debería ser TRUE:\n";
    bool result3 = neg_one > neg_three;
    std::cout << "Resultado: " << (result3 ? "TRUE" : "FALSE");
    std::cout << " " << (result3 ? "✅ CORRECTO" : "❌ INCORRECTO") << "\n\n";

    std::cout << "-3 > -5 debería ser TRUE:\n";
    bool result4 = neg_three > neg_five;
    std::cout << "Resultado: " << (result4 ? "TRUE" : "FALSE");
    std::cout << " " << (result4 ? "✅ CORRECTO" : "❌ INCORRECTO") << "\n\n";

    std::cout << "TEST 3: Operadores mixtos (negativo vs positivo)\n";
    std::cout << "-1 < +2 debería ser TRUE:\n";
    bool result5 = neg_one < pos_two;
    std::cout << "Resultado: " << (result5 ? "TRUE" : "FALSE");
    std::cout << " " << (result5 ? "✅ CORRECTO" : "❌ INCORRECTO") << "\n\n";

    std::cout << "+5 > -5 debería ser TRUE:\n";
    bool result6 = pos_five > neg_five;
    std::cout << "Resultado: " << (result6 ? "TRUE" : "FALSE");
    std::cout << " " << (result6 ? "✅ CORRECTO" : "❌ INCORRECTO") << "\n\n";

    std::cout << "TEST 4: Operadores positivos del mismo signo\n";
    std::cout << "+2 < +5 debería ser TRUE:\n";
    bool result7 = pos_two < pos_five;
    std::cout << "Resultado: " << (result7 ? "TRUE" : "FALSE");
    std::cout << " " << (result7 ? "✅ CORRECTO" : "❌ INCORRECTO") << "\n\n";

    std::cout << "+5 > +2 debería ser TRUE:\n";
    bool result8 = pos_five > pos_two;
    std::cout << "Resultado: " << (result8 ? "TRUE" : "FALSE");
    std::cout << " " << (result8 ? "✅ CORRECTO" : "❌ INCORRECTO") << "\n\n";
}

void test_normalization_initializer_list()
{
    std::cout << "=== TEST: Normalización en Constructor initializer_list ===\n";

    // Probar constructor con initializer_list
    std::cout << "Creando número con initializer_list {0, 1, 1, 1}:\n";
    test_int_t num_init{0, 1, 1, 1}; // LSB primero, MSB último

    std::cout << "Verificando que se aplicó normalize_sign()...\n";
    std::cout << "Estado del bit de signo: " << (num_init.is_minus() ? "NEGATIVO" : "POSITIVO") << "\n";

    // También probar con constructor variadic
    std::cout << "\nCreando número con constructor variadic (0, 1, 1, 1):\n";
    test_int_t num_variadic(0, 1, 1, 1);

    std::cout << "Verificando que se aplicó normalize_sign()...\n";
    std::cout << "Estado del bit de signo: " << (num_variadic.is_minus() ? "NEGATIVO" : "POSITIVO") << "\n";

    std::cout << "Comparando ambos constructores:\n";
    bool same = num_init == num_variadic;
    std::cout << "¿Son iguales? " << (same ? "SÍ" : "NO");
    std::cout << " " << (same ? "✅ CONSISTENTES" : "❌ INCONSISTENTES") << "\n\n";
}

void test_assignment_operators_normalization()
{
    std::cout << "=== TEST: Normalización en Operadores de Asignación ===\n";

    auto num1 = test_int_t::sregd_1().operator*(3); // +3
    auto num2 = test_int_t::sregd_1().operator*(2); // +2

    std::cout << "Números iniciales: num1=+3, num2=+2\n";

    std::cout << "\nTEST: operator+=\n";
    std::cout << "num1 += 5 (debería dar +8 y normalizar):\n";
    num1 += 5;
    std::cout << "Estado después de +=: " << (num1.is_minus() ? "NEGATIVO" : "POSITIVO") << "\n";

    std::cout << "\nTEST: operator-=\n";
    std::cout << "num2 -= 4 (debería dar -2 y normalizar):\n";
    num2 -= 4;
    std::cout << "Estado después de -=: " << (num2.is_minus() ? "NEGATIVO" : "POSITIVO") << "\n";

    std::cout << "\nTEST: operator*=\n";
    auto num3 = test_int_t::sregd_m1(); // -1
    std::cout << "num3 = -1, luego num3 *= 3 (debería dar -3 y normalizar):\n";
    num3 *= 3;
    std::cout << "Estado después de *=: " << (num3.is_minus() ? "NEGATIVO" : "POSITIVO") << "\n\n";
}

void test_spaceship_operator()
{
    std::cout << "=== TEST: Operador Spaceship (<=>) ===\n";

    auto neg_five = test_int_t::sregd_m1().operator*(5);  // -5
    auto neg_three = test_int_t::sregd_m1().operator*(3); // -3
    auto pos_two = test_int_t::sregd_1().operator*(2);    // +2

    std::cout << "TEST 1: -5 <=> -3 (debería ser less):\n";
    auto result1 = neg_five <=> neg_three;
    std::cout << "Resultado: ";
    if (result1 == std::strong_ordering::less)
        std::cout << "LESS ✅ CORRECTO\n";
    else if (result1 == std::strong_ordering::greater)
        std::cout << "GREATER ❌ INCORRECTO\n";
    else
        std::cout << "EQUAL ❌ INCORRECTO\n";

    std::cout << "\nTEST 2: -3 <=> +2 (debería ser less):\n";
    auto result2 = neg_three <=> pos_two;
    std::cout << "Resultado: ";
    if (result2 == std::strong_ordering::less)
        std::cout << "LESS ✅ CORRECTO\n";
    else if (result2 == std::strong_ordering::greater)
        std::cout << "GREATER ❌ INCORRECTO\n";
    else
        std::cout << "EQUAL ❌ INCORRECTO\n";

    std::cout << "\nTEST 3: +2 <=> -3 (debería ser greater):\n";
    auto result3 = pos_two <=> neg_three;
    std::cout << "Resultado: ";
    if (result3 == std::strong_ordering::greater)
        std::cout << "GREATER ✅ CORRECTO\n";
    else if (result3 == std::strong_ordering::less)
        std::cout << "LESS ❌ INCORRECTO\n";
    else
        std::cout << "EQUAL ❌ INCORRECTO\n\n";
}

int main()
{
    std::cout << "=== TESTS DE VALIDACIÓN DE CORRECCIONES CRÍTICAS ===\n";
    std::cout << "Template: int_reg_digs_t<2,3> (base=2, dígitos=3)\n";
    std::cout << "Rango: -8 a +7\n\n";

    try
    {
        test_comparison_operators_negatives();
        test_normalization_initializer_list();
        test_assignment_operators_normalization();
        test_spaceship_operator();

        std::cout << "=== RESUMEN ===\n";
        std::cout << "✅ Tests completados\n";
        std::cout << "🔍 Revisar outputs para verificar correcciones\n";
        std::cout << "🎯 Las correcciones aplicadas fueron:\n";
        std::cout << "   1. Operadores <, <=, >, >= → Invierte comparación magnitudes para negativos\n";
        std::cout << "   2. Constructor initializer_list → Agregado normalize_sign()\n";
        std::cout << "   3. Operadores -=, *= → Agregado normalize_sign()\n";
        std::cout << "   4. Operador spaceship <=> → Corregida lógica y sintaxis\n\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "❌ ERROR durante tests: " << e.what() << "\n";
        return 1;
    }

    return 0;
}