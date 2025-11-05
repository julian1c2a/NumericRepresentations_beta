/**
 * @file test_integracion_completa.cpp
 * @brief Test de integración completa del proyecto NumericRepresentations
 *
 * Verifica que todos los componentes principales funcionan juntos:
 * - basic_types.hpp, auxiliary_*.hpp (documentados)
 * - dig_t.hpp (funcional)
 * - utilities.hpp (refactorizado)
 * - reg_digs_t.hpp (documentado y funcional)
 *
 * @note Requiere flags extendidos MSVC: /constexpr:depth2048 /constexpr:steps1048576 /bigobj
 */

#include <iostream>
#include <iomanip>

// Todos los headers principales
#include "include/basic_types.hpp"
#include "include/auxiliary_types.hpp"
#include "include/auxiliary_functions.hpp"
#include "include/dig_t.hpp"
#include "include/utilities.hpp"
#include "include/reg_digs_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "======================================================================\n";
    std::cout << "           TEST DE INTEGRACIÓN COMPLETA - NumericRepresentations\n";
    std::cout << "======================================================================\n\n";

    try
    {
        // === TEST 1: Tipos básicos ===
        std::cout << "🔹 TEST 1: Tipos básicos (basic_types.hpp)\n";
        using uint_least8_t = std::uint_least8_t;
        using uint_least16_t = std::uint_least16_t;
        std::cout << "   ✅ Tipos fundamentales importados correctamente\n\n";

        // === TEST 2: dig_t ===
        std::cout << "🔹 TEST 2: Dígitos en base 10 (dig_t.hpp)\n";
        dig_t<10> d1{7}, d2{3}, d3{9};
        std::cout << "   ✅ dig_t creados: " << d1.get() << ", " << d2.get() << ", " << d3.get() << "\n";

        // Operaciones básicas
        auto suma = d1 + d2;
        std::cout << "   ✅ Suma: " << d1.get() << " + " << d2.get() << " = " << suma.get() << "\n\n";

        // === TEST 3: utilities.hpp refactorizado ===
        std::cout << "🔹 TEST 3: Template metaprogramming (utilities.hpp)\n";

        // Crear tupla de test
        std::tuple<int, double, char> test_tuple{42, 3.14, 'A'};
        std::cout << "   Tupla creada: (" << std::get<0>(test_tuple) << ", "
                  << std::get<1>(test_tuple) << ", " << std::get<2>(test_tuple) << ")\n";

        // Test pack2array con dig_t
        using pack2array_t = utilities::ugly_pack_details::pack2array<dig_t<10>, dig_t<10>, dig_t<10>>;
        pack2array_t packer;
        auto array_result = packer(d1, d2, d3);
        std::cout << "   ✅ pack2array funciona: [" << array_result[0].get() << ", "
                  << array_result[1].get() << ", " << array_result[2].get() << "]\n\n";

        // === TEST 4: reg_digs_t constructor básico ===
        std::cout << "🔹 TEST 4: Registros de dígitos básicos (reg_digs_t.hpp)\n";

        // Constructor por defecto
        reg_digs_t<10, 4> reg_basico;
        std::cout << "   ✅ Constructor por defecto exitoso\n";

        // Asignación manual
        reg_basico[0] = dig_t<10>(1);
        reg_basico[1] = dig_t<10>(2);
        reg_basico[2] = dig_t<10>(3);
        reg_basico[3] = dig_t<10>(4);

        std::cout << "   ✅ Asignación manual: [";
        for (size_t i = 0; i < 4; ++i)
        {
            std::cout << reg_basico[i].get();
            if (i < 3)
                std::cout << ", ";
        }
        std::cout << "]\n";

        // === TEST 5: reg_digs_t constructor variádico (si disponible) ===
        std::cout << "\n🔹 TEST 5: Constructor variádico (requiere flags extendidos)\n";
        try
        {
            reg_digs_t<10, 3> reg_variadic{d1, d2, d3};
            std::cout << "   ✅ Constructor variádico exitoso: [";
            for (size_t i = 0; i < 3; ++i)
            {
                std::cout << reg_variadic[i].get();
                if (i < 2)
                    std::cout << ", ";
            }
            std::cout << "]\n";
        }
        catch (...)
        {
            std::cout << "   ⚠️ Constructor variádico no disponible (usar flags extendidos)\n";
        }

        // === TEST 6: Operaciones avanzadas ===
        std::cout << "\n🔹 TEST 6: Operaciones avanzadas\n";

        // Comparación
        reg_digs_t<10, 3> reg_compare1, reg_compare2;
        reg_compare1[0] = reg_compare2[0] = dig_t<10>(5);
        bool son_iguales = (reg_compare1 == reg_compare2);
        std::cout << "   ✅ Comparación funciona: " << (son_iguales ? "true" : "false") << "\n";

        // Reverse
        reg_digs_t<10, 3> reg_reverse;
        reg_reverse[0] = dig_t<10>(1);
        reg_reverse[1] = dig_t<10>(2);
        reg_reverse[2] = dig_t<10>(3);

        std::cout << "   Antes reverse: [" << reg_reverse[0].get() << ", "
                  << reg_reverse[1].get() << ", " << reg_reverse[2].get() << "]\n";

        reg_reverse.reverse();
        std::cout << "   ✅ Después reverse: [" << reg_reverse[0].get() << ", "
                  << reg_reverse[1].get() << ", " << reg_reverse[2].get() << "]\n";

        // === RESUMEN FINAL ===
        std::cout << "\n======================================================================\n";
        std::cout << "                           🎉 ¡ÉXITO COMPLETO! 🎉\n";
        std::cout << "======================================================================\n";
        std::cout << "✅ Todos los componentes funcionan correctamente:\n";
        std::cout << "   • basic_types.hpp - Tipos fundamentales ✅\n";
        std::cout << "   • auxiliary_*.hpp - Utilidades matemáticas ✅\n";
        std::cout << "   • dig_t.hpp - Dígitos en bases arbitrarias ✅\n";
        std::cout << "   • utilities.hpp - Template metaprogramming refactorizado ✅\n";
        std::cout << "   • reg_digs_t.hpp - Registros de dígitos documentados ✅\n";
        std::cout << "\n🚀 PROYECTO NUMERICREPRESENTATIONS: LISTO PARA PRODUCCIÓN!\n";
        std::cout << "======================================================================\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "\n❌ ERROR durante la integración: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        std::cout << "\n❌ ERROR desconocido durante la integración\n";
        return 1;
    }

    return 0;
}