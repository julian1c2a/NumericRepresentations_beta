/**
 * @file test_uint8_display_issue.cpp
 * @brief Test para demostrar el problema de visualización con uint8_t
 *
 * Cuando dig_t usa uint8_t internamente, std::cout interpreta los valores
 * como caracteres ASCII en lugar de números, causando problemas de visualización.
 */

#include <iostream>
#include <iomanip>
#include <type_traits>

#include "include/dig_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "======================================================================\n";
    std::cout << "           PROBLEMA DE VISUALIZACIÓN uint8_t EN dig_t\n";
    std::cout << "======================================================================\n\n";

    // Test con base pequeña que usa uint8_t
    std::cout << "🔍 TEST 1: Base 10 (probablemente uint8_t)\n";
    dig_t<10> d1{5}, d2{3};

    // Mostrar tipo interno
    using uint_t_10 = decltype(d1)::uint_t;
    std::cout << "   Tipo interno: " << typeid(uint_t_10).name();
    if (std::is_same_v<uint_t_10, uint8_t>)
    {
        std::cout << " (uint8_t - PROBLEMÁTICO para cout)\n";
    }
    else
    {
        std::cout << " (NO es uint8_t)\n";
    }

    std::cout << "   Valores creados: d1=" << static_cast<int>(d1.get())
              << ", d2=" << static_cast<int>(d2.get()) << "\n";

    auto suma = d1 + d2;
    std::cout << "   Suma con static_cast<int>: " << static_cast<int>(suma.get()) << "\n";

    std::cout << "   ❌ Suma SIN cast: '";
    std::cout << suma.get(); // Esto puede mostrar carácter extraño o nada
    std::cout << "' ← Puede ser carácter ASCII en lugar de número\n\n";

    // Test con base más grande que usa uint16_t o mayor
    std::cout << "🔍 TEST 2: Base 1000 (probablemente uint16_t o mayor)\n";
    dig_t<1000> d3{123}, d4{456};

    using uint_t_1000 = decltype(d3)::uint_t;
    std::cout << "   Tipo interno: " << typeid(uint_t_1000).name();
    if (std::is_same_v<uint_t_1000, uint8_t>)
    {
        std::cout << " (uint8_t - PROBLEMÁTICO)\n";
    }
    else
    {
        std::cout << " (NO es uint8_t - OK para cout)\n";
    }

    auto suma_grande = d3 + d4;
    std::cout << "   Suma directa: " << suma_grande.get() << "\n";
    std::cout << "   Suma con cast: " << static_cast<int>(suma_grande.get()) << "\n\n";

    std::cout << "======================================================================\n";
    std::cout << "                           CONCLUSIÓN\n";
    std::cout << "======================================================================\n";
    std::cout << "⚠️ PROBLEMA IDENTIFICADO:\n";
    std::cout << "   • Cuando dig_t usa uint8_t internamente (bases pequeñas)\n";
    std::cout << "   • std::cout interpreta el valor como carácter ASCII\n";
    std::cout << "   • Los números pueden no verse o verse como símbolos extraños\n\n";

    std::cout << "✅ SOLUCIONES:\n";
    std::cout << "   1. Usar static_cast<int>(dig.get()) para mostrar números\n";
    std::cout << "   2. Usar static_cast<unsigned>(dig.get()) para valores sin signo\n";
    std::cout << "   3. Crear función helper para visualización\n\n";

    std::cout << "📝 RECOMENDACIÓN:\n";
    std::cout << "   Actualizar ejemplos de documentación para incluir cast apropiado\n";

    return 0;
}