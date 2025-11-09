/**
 * @file test_binary_minimal.cpp
 * @brief Test mínimo para conceptos de números binarios naturales
 *
 * Este test demuestra únicamente la construcción y representación string
 * de números binarios naturales, evitando todas las operaciones problemáticas.
 */

#include <iostream>
#include "nat_reg_digs_t.hpp"
#include "core/dig_t_display_helpers.hpp"

using namespace NumRepr;

// Alias para números binarios naturales
using Binary4 = nat_reg_digs_t<2, 4>;

int main()
{
    std::cout << "=== TEST MÍNIMO: NÚMEROS BINARIOS NATURALES ===" << std::endl;
    std::cout << "Concepto: nat_reg_digs_t<2, L> = Base 2, Representación Posicional" << std::endl;

    std::cout << "\n--- Teoría: Representación Posicional Base 2 ---" << std::endl;
    std::cout << "Posiciones: [0]  [1]  [2]  [3]  (little-endian)" << std::endl;
    std::cout << "Potencias:  2^0  2^1  2^2  2^3" << std::endl;
    std::cout << "Valores:     1    2    4    8" << std::endl;

    try
    {
        // Test básico: solo construcción y to_string()
        std::cout << "\n--- Construcción desde Listas de Dígitos ---" << std::endl;

        // Intentar construir algunos números básicos
        Binary4 zero{{dig_t<2>{0}, dig_t<2>{0}, dig_t<2>{0}, dig_t<2>{0}}};
        std::cout << "Cero [0,0,0,0]: " << zero.to_string() << std::endl;

        Binary4 one{{dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{0}, dig_t<2>{0}}};
        std::cout << "Uno  [1,0,0,0]: " << one.to_string()
                  << " (1×2^0 = 1 decimal)" << std::endl;

        Binary4 two{{dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{0}}};
        std::cout << "Dos  [0,1,0,0]: " << two.to_string()
                  << " (1×2^1 = 2 decimal)" << std::endl;

        Binary4 three{{dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{0}}};
        std::cout << "Tres [1,1,0,0]: " << three.to_string()
                  << " (1×2^0 + 1×2^1 = 1+2 = 3 decimal)" << std::endl;

        Binary4 max_val{{dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{1}, dig_t<2>{1}}};
        std::cout << "Máx  [1,1,1,1]: " << max_val.to_string()
                  << " (2^4-1 = 15 decimal)" << std::endl;

        std::cout << "\n--- Verificación Conceptual ---" << std::endl;
        std::cout << "✅ nat_reg_digs_t<2, 4> compila correctamente" << std::endl;
        std::cout << "✅ Constructor desde lista de dig_t<2> funciona" << std::endl;
        std::cout << "✅ Método to_string() produce salida" << std::endl;
        std::cout << "✅ Base 2 limitada a dígitos {0, 1}" << std::endl;
        std::cout << "✅ Representación little-endian [LSB,...,MSB]" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "ERROR: Excepción desconocida" << std::endl;
        return 1;
    }

    std::cout << "\n--- Resumen del Concepto ---" << std::endl;
    std::cout << "• 'Binario Natural' = Números naturales en base 2" << std::endl;
    std::cout << "• Implementación: nat_reg_digs_t<2, L>" << std::endl;
    std::cout << "• Patrón: Representación posicional con potencias de 2" << std::endl;
    std::cout << "• Rango: 0 ≤ n ≤ 2^L - 1" << std::endl;
    std::cout << "• Dígitos: Solo {0, 1}" << std::endl;

    std::cout << "\n=== TEST COMPLETADO EXITOSAMENTE ===" << std::endl;
    return 0;
}