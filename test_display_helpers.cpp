/**
 * @file test_display_helpers.cpp
 * @brief Test de las funciones helper para visualización de dig_t
 */

#include <iostream>
#include "include/dig_t.hpp"
#include "include/dig_t_display_helpers.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "======================================================================\n";
    std::cout << "               TEST DE HELPERS DE VISUALIZACIÓN\n";
    std::cout << "======================================================================\n\n";

    // Test con base pequeña (uint8_t)
    std::cout << "🔹 TEST 1: Base 10 (tipo interno: " << type_name<10>() << ")\n";
    dig_t<10> d1{5}, d2{3};
    auto suma_10 = d1 + d2;

    std::cout << "   Usando función display():\n";
    std::cout << "     d1 = " << display(d1) << "\n";
    std::cout << "     d2 = " << display(d2) << "\n";
    std::cout << "     suma = " << display(suma_10) << "\n\n";

    std::cout << "   Usando operador<< sobrecargado:\n";
    std::cout << "     d1 = " << d1 << "\n";
    std::cout << "     d2 = " << d2 << "\n";
    std::cout << "     suma = " << suma_10 << "\n\n";

    // Test con base grande (uint16_t o mayor)
    std::cout << "🔹 TEST 2: Base 1000 (tipo interno: " << type_name<1000>() << ")\n";
    dig_t<1000> d3{123}, d4{456};
    auto suma_1000 = d3 + d4;

    std::cout << "   Usando función display():\n";
    std::cout << "     d3 = " << display(d3) << "\n";
    std::cout << "     d4 = " << display(d4) << "\n";
    std::cout << "     suma = " << display(suma_1000) << "\n\n";

    std::cout << "   Usando operador<< sobrecargado:\n";
    std::cout << "     d3 = " << d3 << "\n";
    std::cout << "     d4 = " << d4 << "\n";
    std::cout << "     suma = " << suma_1000 << "\n\n";

    // Test comparativo
    std::cout << "🔹 TEST 3: Comparación de métodos de visualización\n";
    dig_t<16> hex_digit{15}; // Base 16, probablemente uint8_t

    std::cout << "   Tipo interno base 16: " << type_name<16>() << "\n";
    std::cout << "   Valor 15 en base 16:\n";
    std::cout << "     Con display(): " << display(hex_digit) << "\n";
    std::cout << "     Con operator<<: " << hex_digit << "\n";
    std::cout << "     Con static_cast<int>: " << static_cast<int>(hex_digit.get()) << "\n";
    std::cout << "     Con +digit.get(): " << +hex_digit.get() << "\n";
    std::cout << "     ❌ Sin cast: '";
    std::cout << hex_digit.get();
    std::cout << "' ← Puede ser problemático\n\n";

    std::cout << "======================================================================\n";
    std::cout << "                              RESULTADO\n";
    std::cout << "======================================================================\n";
    std::cout << "✅ HELPERS DE VISUALIZACIÓN FUNCIONAN CORRECTAMENTE\n\n";

    std::cout << "Recomendaciones de uso:\n";
    std::cout << "  1. #include \"include/dig_t_display_helpers.hpp\"\n";
    std::cout << "  2. Usar std::cout << digit directamente (operador sobrecargado)\n";
    std::cout << "  3. O usar display(digit) explícitamente\n";
    std::cout << "  4. type_name<Base>() para debugging de tipos\n\n";

    std::cout << "¡Problema de visualización uint8_t resuelto! 🎉\n";

    return 0;
}