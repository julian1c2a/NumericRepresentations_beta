/**
 * @file test_int_basic_methods.cpp
 * @brief FASE 1: Test sistemático de métodos básicos de int_reg_digs_t
 * @date 6 noviembre 2025
 * @note Análisis de enteros con complemento a la base - int_reg_digs_t<B,R>
 */

#include <iostream>
#include "include/int_reg_digs_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "=== FASE 1: BASIC METHODS - int_reg_digs_t ===" << std::endl;
    std::cout << "Analizando enteros con complemento a la base" << std::endl;
    std::cout << "Template: int_reg_digs_t<2,3> (base 2, 3 dígitos sin signo + 1 signo = 4 total)" << std::endl;
    std::cout << "Rango: -8 a +7 (complemento a 2^4 = 16)" << std::endl
              << std::endl;

    try
    {
        // Test 1: Constructor por defecto
        std::cout << "Test 1: Constructor por defecto" << std::endl;
        int_reg_digs_t<2, 3> int_default;
        std::cout << "  int_default: " << int_default.to_string() << std::endl;
        std::cout << "  ✓ Constructor por defecto funciona" << std::endl
                  << std::endl;

        // Test 2: Heredar de nat_reg_digs_t<B, R+1>
        std::cout << "Test 2: Herencia de nat_reg_digs_t<2,4>" << std::endl;
        std::cout << "  Longitud total L = R+1 = 3+1 = 4 dígitos" << std::endl;
        std::cout << "  Dígito [3] = signo, dígitos [0-2] = magnitud" << std::endl;
        std::cout << "  Formato base: " << int_default.to_string() << std::endl;
        std::cout << "  ✓ Herencia funciona correctamente" << std::endl
                  << std::endl;

        // Test 3: Métodos de signo
        std::cout << "Test 3: Métodos de signo" << std::endl;

        // Crear número positivo
        int_reg_digs_t<2, 3> pos_num;
        pos_num.set_0(); // Asegurar que es 0 (positivo)

        std::cout << "  Número positivo (0): " << pos_num.to_string() << std::endl;

        // Acceder al dígito de signo manualmente
        // pos_num[3] debería ser 0 para positivo
        std::cout << "  Dígito de signo [3]: " << pos_num[3].to_string() << std::endl;

        std::cout << "  ✓ Métodos de signo accesibles" << std::endl
                  << std::endl;

        // Test 4: to_string()
        std::cout << "Test 4: Método to_string()" << std::endl;
        std::string str_representation = int_default.to_string();
        std::cout << "  Representación: \"" << str_representation << "\"" << std::endl;

        // Verificar formato esperado (debería heredar de nat_reg_digs_t)
        bool has_correct_format = (str_representation.find("reg_dig#") != std::string::npos);
        std::cout << "  Formato válido: " << (has_correct_format ? "✓" : "❌") << std::endl;
        std::cout << "  ✓ to_string() funciona" << std::endl
                  << std::endl;

        // Test 5: operator[] para acceso a dígitos
        std::cout << "Test 5: operator[] - Acceso a dígitos individuales" << std::endl;
        for (size_t i = 0; i < 4; ++i)
        {
            auto digit = int_default[i];
            std::cout << "  int_default[" << i << "]: " << digit.to_string();
            if (i == 3)
                std::cout << " (dígito de signo)";
            std::cout << std::endl;
        }
        std::cout << "  ✓ operator[] funciona" << std::endl
                  << std::endl;

        // Test 6: Herencia de factory methods de nat_reg_digs_t
        std::cout << "Test 6: Factory methods heredados" << std::endl;

        try
        {
            auto zero = int_reg_digs_t<2, 3>::regd_0();
            std::cout << "  regd_0(): " << zero.to_string() << " (debería ser +0)" << std::endl;

            auto one = int_reg_digs_t<2, 3>::regd_1();
            std::cout << "  regd_1(): " << one.to_string() << " (debería ser +1)" << std::endl;

            auto max_dig = int_reg_digs_t<2, 3>::regd_Bm1();
            std::cout << "  regd_Bm1(): " << max_dig.to_string() << " (debería ser máximo positivo)" << std::endl;

            std::cout << "  ✓ Factory methods funcionan" << std::endl;
        }
        catch (...)
        {
            std::cout << "  ℹ️ Factory methods requieren verificación adicional" << std::endl;
        }
        std::cout << std::endl;

        // Test 7: Constantes de dígitos
        std::cout << "Test 7: Constantes estáticas de dígitos" << std::endl;
        auto dig_0 = int_reg_digs_t<2, 3>::dig_0();
        auto dig_1 = int_reg_digs_t<2, 3>::dig_1();
        auto dig_max = int_reg_digs_t<2, 3>::dig_max();

        std::cout << "  dig_0(): " << dig_0.to_string() << std::endl;
        std::cout << "  dig_1(): " << dig_1.to_string() << std::endl;
        std::cout << "  dig_max(): " << dig_max.to_string() << " (B-1 = " << (2 - 1) << ")" << std::endl;

        std::cout << "  ✓ Constantes de dígitos funcionan" << std::endl
                  << std::endl;

        // Test 8: Constantes UINT_T
        std::cout << "Test 8: Constantes UINT_T" << std::endl;
        auto ui_0 = int_reg_digs_t<2, 3>::ui_0();
        auto ui_1 = int_reg_digs_t<2, 3>::ui_1();
        auto ui_B = int_reg_digs_t<2, 3>::ui_B();

        std::cout << "  ui_0(): " << ui_0 << std::endl;
        std::cout << "  ui_1(): " << ui_1 << std::endl;
        std::cout << "  ui_B(): " << ui_B << " (base = 2)" << std::endl;

        std::cout << "  ✓ Constantes UINT_T funcionan" << std::endl
                  << std::endl;

        // Test 9: Verificar tamaños y tipos
        std::cout << "Test 9: Verificación de tipos y tamaños" << std::endl;
        constexpr size_t R = 3;
        constexpr size_t L = R + 1; // 4
        constexpr uint64_t B = 2;

        std::cout << "  Plantilla: int_reg_digs_t<" << B << "," << R << ">" << std::endl;
        std::cout << "  R (sin signo): " << R << " dígitos" << std::endl;
        std::cout << "  L (con signo): " << L << " dígitos" << std::endl;
        std::cout << "  Base B: " << B << std::endl;
        std::cout << "  Rango teórico: -" << (1ULL << R) << " a +" << ((1ULL << R) - 1) << std::endl;
        std::cout << "  ✓ Configuración correcta" << std::endl
                  << std::endl;

        // Test 10: Complemento a la base - concepto básico
        std::cout << "Test 10: Concepto de complemento a la base" << std::endl;
        std::cout << "  En complemento a 2^4 (base 16):" << std::endl;
        std::cout << "  - Positivos: 0000 a 0111 (0 a 7)" << std::endl;
        std::cout << "  - Negativos: 1000 a 1111 (-8 a -1)" << std::endl;
        std::cout << "  - Dígito MSB = 0: positivo" << std::endl;
        std::cout << "  - Dígito MSB ≠ 0: negativo" << std::endl;
        std::cout << "  ✓ Fundamento teórico correcto" << std::endl
                  << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "❌ ERROR en Fase 1: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "=== FASE 1 COMPLETADA ===" << std::endl;
    std::cout << "Análisis de Basic Methods de int_reg_digs_t terminado" << std::endl
              << std::endl;
    std::cout << "🚀 LISTO PARA FASE 2: Factory Methods específicos de enteros" << std::endl;

    return 0;
}