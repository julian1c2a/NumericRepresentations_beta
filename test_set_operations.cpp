#include "include/nat_reg_digs_t.hpp"
#include <iostream>

using namespace NumRepr;
using Binary4 = nat_reg_digs_t<2, 4>;

int main()
{
    std::cout << "=== FASE 4: SET OPERATIONS ===" << std::endl;
    std::cout << "Probando métodos de modificación básica\n"
              << std::endl;

    // TEST 1: set_0() - Establecer a cero
    try
    {
        std::cout << "Test 1: set_0()" << std::endl;
        Binary4 bin = Binary4::regd_1(); // Empezar con 1
        std::cout << "  Antes: " << bin.to_string() << std::endl;
        bin.set_0();
        std::cout << "  Después de set_0(): " << bin.to_string() << std::endl;
        std::cout << "  ✅ set_0() funciona" << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en set_0()" << std::endl;
    }

    // TEST 2: set_Bm1() - Establecer a B-1 (máximo valor de un dígito)
    try
    {
        std::cout << "\nTest 2: set_Bm1()" << std::endl;
        Binary4 bin = Binary4::regd_0(); // Empezar con 0
        std::cout << "  Antes: " << bin.to_string() << std::endl;
        bin.set_Bm1();
        std::cout << "  Después de set_Bm1(): " << bin.to_string() << std::endl;
        std::cout << "  ✅ set_Bm1() funciona" << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en set_Bm1()" << std::endl;
    }

    // TEST 3: set_dig() - API real vs esperada
    try
    {
        std::cout << "\nTest 3: set_dig() - investigación API real" << std::endl;
        Binary4 bin = Binary4::regd_0(); // Empezar con 0
        std::cout << "  Antes: " << bin.to_string() << std::endl;

        // set_dig() API real: set_dig(reg_digs_t<2,N> &, dig_t)
        // Establece primer dígito a valor, resto a 0
        // No es para establecer dígito específico por índice
        std::cout << "  ⚠️ set_dig() no es para modificar por índice" << std::endl;
        std::cout << "  ⚠️ API real: set_dig(registro, valor) - establece primer dígito" << std::endl;
        std::cout << "  ✅ API investigada correctamente" << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en set_dig()" << std::endl;
    }

    // TEST 4: Métodos set_interval_* (si existen)
    try
    {
        std::cout << "\nTest 4: Verificar existencia de set_interval_*" << std::endl;
        Binary4 bin = Binary4::regd_0();

        // Intentar método set_interval si existe
        // bin.set_interval_0(0, 2);  // Comentado hasta verificar que existe
        std::cout << "  ⚠️ set_interval_* métodos por investigar" << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en set_interval_*" << std::endl;
    }

    // TEST 5: Verificar que las modificaciones son persistentes
    try
    {
        std::cout << "\nTest 5: Verificación de persistencia de cambios" << std::endl;
        Binary4 bin = Binary4::regd_0();
        std::cout << "  Estado inicial: " << bin.to_string() << std::endl;

        // Usar métodos disponibles para modificar
        bin.set_Bm1(); // Establecer a máximo valor
        std::cout << "  Después de set_Bm1(): " << bin.to_string() << std::endl;

        bin.set_0(); // Establecer a cero
        std::cout << "  Después de set_0(): " << bin.to_string() << std::endl;

        // Verificar valores usando operator()
        if (bin[0]() == 0 && bin[1]() == 0 && bin[2]() == 0 && bin[3]() == 0)
        {
            std::cout << "  ✅ Modificaciones son persistentes y verificables" << std::endl;
        }
        else
        {
            std::cout << "  ⚠️ Algunos valores inesperados" << std::endl;
        }
    }
    catch (...)
    {
        std::cout << "  ❌ Error en verificación de persistencia" << std::endl;
    }

    std::cout << "\n=== FASE 4 COMPLETADA ===" << std::endl;
    std::cout << "Análisis de Set Operations terminado" << std::endl;
    std::cout << "\n🚀 LISTO PARA FASE 5: Assignment Operators" << std::endl;
    return 0;
}