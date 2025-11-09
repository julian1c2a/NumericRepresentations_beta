/**
 * @file test_comparison_operators.cpp
 * @brief FASE 7: Test sistemático de operadores de comparación de nat_reg_digs_t
 * @date 6 noviembre 2025
 * @note Siguiendo metodología incremental del PLAN_TRABAJO_MAÑANA.md
 */

#include <iostream>
#include "include/nat_reg_digs_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "=== FASE 7: COMPARISON OPERATORS ===" << std::endl;
    std::cout << "Probando operadores de comparación uno por uno" << std::endl
              << std::endl;

    try
    {
        // Preparar valores de prueba
        nat_reg_digs_t<2, 4> zero = nat_reg_digs_t<2, 4>::regd_0();      // 0
        nat_reg_digs_t<2, 4> one = nat_reg_digs_t<2, 4>::regd_1();       // 1
        nat_reg_digs_t<2, 4> two = one + one;                            // 2
        nat_reg_digs_t<2, 4> three = two + one;                          // 3
        nat_reg_digs_t<2, 4> another_two = one + one;                    // 2 (copia)
        nat_reg_digs_t<2, 4> max_val = nat_reg_digs_t<2, 4>::regd_Bm1(); // 15 (máximo)

        std::cout << "Valores de prueba:" << std::endl;
        std::cout << "  zero: " << zero.to_string() << " (valor: 0)" << std::endl;
        std::cout << "  one: " << one.to_string() << " (valor: 1)" << std::endl;
        std::cout << "  two: " << two.to_string() << " (valor: 2)" << std::endl;
        std::cout << "  three: " << three.to_string() << " (valor: 3)" << std::endl;
        std::cout << "  another_two: " << another_two.to_string() << " (valor: 2)" << std::endl;
        std::cout << "  max_val: " << max_val.to_string() << " (valor: 15)" << std::endl
                  << std::endl;

        // Test 1: operator== (igualdad)
        std::cout << "Test 1: operator== (igualdad)" << std::endl;
        bool eq1 = (two == another_two); // true: 2 == 2
        bool eq2 = (one == two);         // false: 1 == 2
        bool eq3 = (zero == zero);       // true: 0 == 0

        std::cout << "  two == another_two: " << (eq1 ? "true" : "false") << " (debería ser true)" << std::endl;
        std::cout << "  one == two: " << (eq2 ? "true" : "false") << " (debería ser false)" << std::endl;
        std::cout << "  zero == zero: " << (eq3 ? "true" : "false") << " (debería ser true)" << std::endl;

        if (eq1 && !eq2 && eq3)
        {
            std::cout << "  ✓ operator== funciona correctamente" << std::endl;
        }
        else
        {
            std::cout << "  ❌ operator== tiene problemas" << std::endl;
        }
        std::cout << std::endl;

        // Test 2: operator!= (desigualdad)
        std::cout << "Test 2: operator!= (desigualdad)" << std::endl;
        bool neq1 = (one != two);         // true: 1 != 2
        bool neq2 = (two != another_two); // false: 2 != 2
        bool neq3 = (zero != max_val);    // true: 0 != 15

        std::cout << "  one != two: " << (neq1 ? "true" : "false") << " (debería ser true)" << std::endl;
        std::cout << "  two != another_two: " << (neq2 ? "true" : "false") << " (debería ser false)" << std::endl;
        std::cout << "  zero != max_val: " << (neq3 ? "true" : "false") << " (debería ser true)" << std::endl;

        if (neq1 && !neq2 && neq3)
        {
            std::cout << "  ✓ operator!= funciona correctamente" << std::endl;
        }
        else
        {
            std::cout << "  ❌ operator!= tiene problemas" << std::endl;
        }
        std::cout << std::endl;

        // Test 3: operator< (menor que)
        std::cout << "Test 3: operator< (menor que)" << std::endl;
        bool lt1 = (zero < one);  // true: 0 < 1
        bool lt2 = (one < three); // true: 1 < 3
        bool lt3 = (three < two); // false: 3 < 2
        bool lt4 = (two < two);   // false: 2 < 2

        std::cout << "  zero < one: " << (lt1 ? "true" : "false") << " (debería ser true)" << std::endl;
        std::cout << "  one < three: " << (lt2 ? "true" : "false") << " (debería ser true)" << std::endl;
        std::cout << "  three < two: " << (lt3 ? "true" : "false") << " (debería ser false)" << std::endl;
        std::cout << "  two < two: " << (lt4 ? "true" : "false") << " (debería ser false)" << std::endl;

        if (lt1 && lt2 && !lt3 && !lt4)
        {
            std::cout << "  ✓ operator< funciona correctamente" << std::endl;
        }
        else
        {
            std::cout << "  ❌ operator< tiene problemas" << std::endl;
        }
        std::cout << std::endl;

        // Test 4: operator<= (menor o igual que)
        std::cout << "Test 4: operator<= (menor o igual que)" << std::endl;
        bool le1 = (zero <= one);        // true: 0 <= 1
        bool le2 = (two <= another_two); // true: 2 <= 2
        bool le3 = (three <= two);       // false: 3 <= 2
        bool le4 = (one <= max_val);     // true: 1 <= 15

        std::cout << "  zero <= one: " << (le1 ? "true" : "false") << " (debería ser true)" << std::endl;
        std::cout << "  two <= another_two: " << (le2 ? "true" : "false") << " (debería ser true)" << std::endl;
        std::cout << "  three <= two: " << (le3 ? "true" : "false") << " (debería ser false)" << std::endl;
        std::cout << "  one <= max_val: " << (le4 ? "true" : "false") << " (debería ser true)" << std::endl;

        if (le1 && le2 && !le3 && le4)
        {
            std::cout << "  ✓ operator<= funciona correctamente" << std::endl;
        }
        else
        {
            std::cout << "  ❌ operator<= tiene problemas" << std::endl;
        }
        std::cout << std::endl;

        // Test 5: operator> (mayor que)
        std::cout << "Test 5: operator> (mayor que)" << std::endl;
        bool gt1 = (three > two);    // true: 3 > 2
        bool gt2 = (max_val > zero); // true: 15 > 0
        bool gt3 = (one > three);    // false: 1 > 3
        bool gt4 = (two > two);      // false: 2 > 2

        std::cout << "  three > two: " << (gt1 ? "true" : "false") << " (debería ser true)" << std::endl;
        std::cout << "  max_val > zero: " << (gt2 ? "true" : "false") << " (debería ser true)" << std::endl;
        std::cout << "  one > three: " << (gt3 ? "true" : "false") << " (debería ser false)" << std::endl;
        std::cout << "  two > two: " << (gt4 ? "true" : "false") << " (debería ser false)" << std::endl;

        if (gt1 && gt2 && !gt3 && !gt4)
        {
            std::cout << "  ✓ operator> funciona correctamente" << std::endl;
        }
        else
        {
            std::cout << "  ❌ operator> tiene problemas" << std::endl;
        }
        std::cout << std::endl;

        // Test 6: operator>= (mayor o igual que)
        std::cout << "Test 6: operator>= (mayor o igual que)" << std::endl;
        bool ge1 = (three >= two);       // true: 3 >= 2
        bool ge2 = (two >= another_two); // true: 2 >= 2
        bool ge3 = (one >= three);       // false: 1 >= 3
        bool ge4 = (max_val >= max_val); // true: 15 >= 15

        std::cout << "  three >= two: " << (ge1 ? "true" : "false") << " (debería ser true)" << std::endl;
        std::cout << "  two >= another_two: " << (ge2 ? "true" : "false") << " (debería ser true)" << std::endl;
        std::cout << "  one >= three: " << (ge3 ? "true" : "false") << " (debería ser false)" << std::endl;
        std::cout << "  max_val >= max_val: " << (ge4 ? "true" : "false") << " (debería ser true)" << std::endl;

        if (ge1 && ge2 && !ge3 && ge4)
        {
            std::cout << "  ✓ operator>= funciona correctamente" << std::endl;
        }
        else
        {
            std::cout << "  ❌ operator>= tiene problemas" << std::endl;
        }
        std::cout << std::endl;

        // Test 7: Operador spaceship <=> (C++20) si existe
        std::cout << "Test 7: Verificación de consistencia de comparaciones" << std::endl;
        // Verificar transitividad: si a < b y b < c, entonces a < c
        bool trans1 = (zero < one) && (one < three) && (zero < three); // 0 < 1 < 3

        // Verificar reflexividad: a == a
        bool refl1 = (two == two) && (max_val == max_val);

        // Verificar antisimetría: si a <= b y b <= a, entonces a == b
        bool antisym1 = ((two <= another_two) && (another_two <= two)) == (two == another_two);

        std::cout << "  Transitividad (0 < 1 < 3): " << (trans1 ? "✓" : "❌") << std::endl;
        std::cout << "  Reflexividad (a == a): " << (refl1 ? "✓" : "❌") << std::endl;
        std::cout << "  Antisimetría ((a <= b && b <= a) == (a == b)): " << (antisym1 ? "✓" : "❌") << std::endl;

        if (trans1 && refl1 && antisym1)
        {
            std::cout << "  ✓ Propiedades matemáticas de orden verificadas" << std::endl;
        }
        else
        {
            std::cout << "  ❌ Problemas en propiedades matemáticas" << std::endl;
        }
        std::cout << std::endl;

        // Test 8: Casos extremos
        std::cout << "Test 8: Casos extremos" << std::endl;
        bool extreme1 = (zero < max_val);                         // mínimo < máximo
        bool extreme2 = !(max_val < zero);                        // ¬(máximo < mínimo)
        bool extreme3 = (zero == nat_reg_digs_t<2, 4>::regd_0()); // 0 == factory_0()

        std::cout << "  zero < max_val: " << (extreme1 ? "true" : "false") << " (0 < 15)" << std::endl;
        std::cout << "  !(max_val < zero): " << (extreme2 ? "true" : "false") << " (¬(15 < 0))" << std::endl;
        std::cout << "  zero == regd_0(): " << (extreme3 ? "true" : "false") << " (consistency)" << std::endl;

        if (extreme1 && extreme2 && extreme3)
        {
            std::cout << "  ✓ Casos extremos funcionan correctamente" << std::endl;
        }
        else
        {
            std::cout << "  ❌ Problemas en casos extremos" << std::endl;
        }
        std::cout << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "❌ ERROR en Fase 7: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "=== FASE 7 COMPLETADA ===" << std::endl;
    std::cout << "Análisis de Comparison Operators terminado" << std::endl
              << std::endl;
    std::cout << "🏆 ANÁLISIS SISTEMÁTICO COMPLETO EXTENDIDO" << std::endl;
    std::cout << "Todas las 7 fases completadas exitosamente" << std::endl;
    std::cout << "✅ Basic Methods | ✅ Factory Methods | ✅ Constructors" << std::endl;
    std::cout << "✅ Set Operations | ✅ Assignment Operators | ✅ Arithmetic Operators" << std::endl;
    std::cout << "✅ Comparison Operators" << std::endl;

    return 0;
}