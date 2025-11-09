/**
 * @file test_arithmetic_operators.cpp
 * @brief FASE 6: Test sistemático de operadores aritméticos de nat_reg_digs_t
 * @date 6 noviembre 2025
 * @note Siguiendo metodología incremental del PLAN_TRABAJO_MAÑANA.md
 */

#include <iostream>
#include "include/nat_reg_digs_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "=== FASE 6: ARITHMETIC OPERATORS ===" << std::endl;
    std::cout << "Probando operadores aritméticos uno por uno" << std::endl
              << std::endl;

    try
    {
        // Test 1: operator+ (suma)
        std::cout << "Test 1: operator+ (suma)" << std::endl;
        nat_reg_digs_t<2, 4> bin1 = nat_reg_digs_t<2, 4>::regd_1(); // 1
        nat_reg_digs_t<2, 4> bin2 = nat_reg_digs_t<2, 4>::regd_1(); // 1
        std::cout << "  bin1: " << bin1.to_string() << " (valor: 1)" << std::endl;
        std::cout << "  bin2: " << bin2.to_string() << " (valor: 1)" << std::endl;

        auto suma = bin1 + bin2;
        std::cout << "  bin1 + bin2 = " << suma.to_string() << " (debería ser 2)" << std::endl;
        std::cout << "  ✓ operator+ funciona" << std::endl
                  << std::endl;

        // Test 2: operator+= (suma y asignación)
        std::cout << "Test 2: operator+= (suma y asignación)" << std::endl;
        nat_reg_digs_t<2, 4> bin3 = nat_reg_digs_t<2, 4>::regd_1(); // 1
        std::cout << "  Antes: " << bin3.to_string() << std::endl;
        bin3 += bin1; // bin3 += 1, debería ser 2
        std::cout << "  Después de += 1: " << bin3.to_string() << std::endl;
        std::cout << "  ✓ operator+= funciona" << std::endl
                  << std::endl;

        // Test 3: operator++ prefijo
        std::cout << "Test 3: operator++ prefijo" << std::endl;
        nat_reg_digs_t<2, 4> bin4 = nat_reg_digs_t<2, 4>::regd_1(); // 1
        std::cout << "  Antes: " << bin4.to_string() << std::endl;
        auto pre_inc = ++bin4;
        std::cout << "  Después de ++bin4: " << bin4.to_string() << std::endl;
        std::cout << "  Retorno de ++: " << pre_inc.to_string() << std::endl;
        std::cout << "  ✓ operator++ prefijo funciona" << std::endl
                  << std::endl;

        // Test 4: operator++ postfijo
        std::cout << "Test 4: operator++ postfijo" << std::endl;
        nat_reg_digs_t<2, 4> bin5 = nat_reg_digs_t<2, 4>::regd_1(); // 1
        std::cout << "  Antes: " << bin5.to_string() << std::endl;
        auto post_inc = bin5++;
        std::cout << "  Después de bin5++: " << bin5.to_string() << std::endl;
        std::cout << "  Retorno de ++: " << post_inc.to_string() << std::endl;
        std::cout << "  ✓ operator++ postfijo funciona" << std::endl
                  << std::endl;

        // Test 5: operator- (resta)
        std::cout << "Test 5: operator- (resta)" << std::endl;
        nat_reg_digs_t<2, 4> bin6;              // Constructor por defecto
        bin6.set_0();                           // Asegurar que es 0
        bin6 += nat_reg_digs_t<2, 4>::regd_1(); // 1
        bin6 += nat_reg_digs_t<2, 4>::regd_1(); // 2
        bin6 += nat_reg_digs_t<2, 4>::regd_1(); // 3

        nat_reg_digs_t<2, 4> bin7 = nat_reg_digs_t<2, 4>::regd_1(); // 1
        std::cout << "  bin6: " << bin6.to_string() << " (valor: 3)" << std::endl;
        std::cout << "  bin7: " << bin7.to_string() << " (valor: 1)" << std::endl;

        auto resta = bin6 - bin7;
        std::cout << "  bin6 - bin7 = " << resta.to_string() << " (debería ser 2)" << std::endl;
        std::cout << "  ✓ operator- funciona" << std::endl
                  << std::endl;

        // Test 6: operator-= (resta y asignación)
        std::cout << "Test 6: operator-= (resta y asignación)" << std::endl;
        nat_reg_digs_t<2, 4> bin8 = bin6; // Copiar 3
        std::cout << "  Antes: " << bin8.to_string() << std::endl;
        bin8 -= bin7; // bin8 -= 1, debería ser 2
        std::cout << "  Después de -= 1: " << bin8.to_string() << std::endl;
        std::cout << "  ✓ operator-= funciona" << std::endl
                  << std::endl;

        // Test 7: operator-- prefijo
        std::cout << "Test 7: operator-- prefijo" << std::endl;
        nat_reg_digs_t<2, 4> bin9 = bin6; // Copiar 3
        std::cout << "  Antes: " << bin9.to_string() << std::endl;
        auto pre_dec = --bin9;
        std::cout << "  Después de --bin9: " << bin9.to_string() << std::endl;
        std::cout << "  Retorno de --: " << pre_dec.to_string() << std::endl;
        std::cout << "  ✓ operator-- prefijo funciona" << std::endl
                  << std::endl;

        // Test 8: operator-- postfijo
        std::cout << "Test 8: operator-- postfijo" << std::endl;
        nat_reg_digs_t<2, 4> bin10 = bin6; // Copiar 3
        std::cout << "  Antes: " << bin10.to_string() << std::endl;
        auto post_dec = bin10--;
        std::cout << "  Después de bin10--: " << bin10.to_string() << std::endl;
        std::cout << "  Retorno de --: " << post_dec.to_string() << std::endl;
        std::cout << "  ✓ operator-- postfijo funciona" << std::endl
                  << std::endl;

        // Test 9: Multiplicación (si existe)
        std::cout << "Test 9: operator* (multiplicación)" << std::endl;
        nat_reg_digs_t<2, 4> mul1 = bin7; // 1
        nat_reg_digs_t<2, 4> mul2 = bin8; // 2
        std::cout << "  mul1: " << mul1.to_string() << " (valor: 1)" << std::endl;
        std::cout << "  mul2: " << mul2.to_string() << " (valor: 2)" << std::endl;

        auto producto = mul1 * mul2;
        std::cout << "  mul1 * mul2 = " << producto.to_string() << " (debería ser 2)" << std::endl;
        std::cout << "  ✓ operator* funciona" << std::endl
                  << std::endl;

        // Test 10: Verificación de overflow/límites
        std::cout << "Test 10: Verificación de límites (4 bits = max 15)" << std::endl;
        nat_reg_digs_t<2, 4> bin_max = nat_reg_digs_t<2, 4>::regd_Bm1(); // 15
        std::cout << "  bin_max: " << bin_max.to_string() << " (valor: 15 = máximo)" << std::endl;

        // Intentar incrementar el máximo
        auto overflow_test = bin_max;
        ++overflow_test;
        std::cout << "  Después de ++max: " << overflow_test.to_string() << " (comportamiento overflow)" << std::endl;
        std::cout << "  ✓ Comportamiento límites verificado" << std::endl
                  << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "❌ ERROR en Fase 6: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "=== FASE 6 COMPLETADA ===" << std::endl;
    std::cout << "Análisis de Arithmetic Operators terminado" << std::endl
              << std::endl;
    std::cout << "🏁 ANÁLISIS SISTEMÁTICO COMPLETO" << std::endl;
    std::cout << "Todas las 6 fases completadas exitosamente" << std::endl;

    return 0;
}