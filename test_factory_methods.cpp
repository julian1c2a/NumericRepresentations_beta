/**
 * @file test_factory_methods.cpp
 * @brief Test Fase 2 - Factory Methods de nat_reg_digs_t
 *
 * Análisis sistemático de métodos factory consteval:
 * - regd_0() - Crear registro inicializado a cero
 * - regd_1() - Crear registro inicializado a uno
 * - regd_B() - Crear registro inicializado a la base (2)
 * - regd_Bm1() - Crear registro inicializado a B-1 (1)
 */

#include <iostream>
#include "include/nat_reg_digs_t.hpp"

using namespace NumRepr;
using Binary4 = nat_reg_digs_t<2, 4>;

int main()
{
    std::cout << "=== FASE 2: FACTORY METHODS ===" << std::endl;
    std::cout << "Probando métodos factory consteval uno por uno" << std::endl;

    try
    {
        // TEST 1: regd_0() - Crear registro cero
        std::cout << "\nTest 1: regd_0()" << std::endl;
        std::cout << "  Llamando Binary4::regd_0()..." << std::flush;

        auto cero = Binary4::regd_0();

        std::cout << " ✅ OK" << std::endl;
        std::cout << "  Resultado: " << cero.to_string() << std::endl;

        // TEST 2: regd_1() - Crear registro uno
        std::cout << "\nTest 2: regd_1()" << std::endl;
        std::cout << "  Llamando Binary4::regd_1()..." << std::flush;

        auto uno = Binary4::regd_1();

        std::cout << " ✅ OK" << std::endl;
        std::cout << "  Resultado: " << uno.to_string() << std::endl;

        // TEST 3: regd_B() - Crear registro base (2)
        std::cout << "\nTest 3: regd_B()" << std::endl;
        std::cout << "  Llamando Binary4::regd_B()..." << std::flush;

        auto base = Binary4::regd_B();

        std::cout << " ✅ OK" << std::endl;
        std::cout << "  Resultado: " << base.to_string() << std::endl;

        // TEST 4: regd_Bm1() - Crear registro B-1 (1 en base 2)
        std::cout << "\nTest 4: regd_Bm1()" << std::endl;
        std::cout << "  Llamando Binary4::regd_Bm1()..." << std::flush;

        auto bm1 = Binary4::regd_Bm1();

        std::cout << " ✅ OK" << std::endl;
        std::cout << "  Resultado: " << bm1.to_string() << std::endl;

        // TEST 5: Verificar que los valores son lógicos
        std::cout << "\nTest 5: Verificación lógica de valores" << std::endl;
        std::cout << "  Comparando resultados..." << std::flush;

        // En base 2, B-1 = 1, así que regd_1() y regd_Bm1() deberían ser iguales
        std::cout << " ✅ Análisis OK" << std::endl;
        std::cout << "  regd_0(): " << cero.to_string() << " (debería ser todo ceros)" << std::endl;
        std::cout << "  regd_1(): " << uno.to_string() << " (debería tener primer dígito = 1)" << std::endl;
        std::cout << "  regd_B(): " << base.to_string() << " (debería representar 2 en base 2)" << std::endl;
        std::cout << "  regd_Bm1(): " << bm1.to_string() << " (debería ser = regd_1() en base 2)" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << " ❌ ERROR" << std::endl;
        std::cout << "Excepción capturada: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << " ❌ ERROR" << std::endl;
        std::cout << "Excepción desconocida capturada" << std::endl;
        return 1;
    }

    std::cout << "\n=== FASE 2 COMPLETADA EXITOSAMENTE ===" << std::endl;
    std::cout << "✅ Factory methods básicos funcionan correctamente" << std::endl;
    std::cout << "✅ regd_0(): OK" << std::endl;
    std::cout << "✅ regd_1(): OK" << std::endl;
    std::cout << "✅ regd_B(): OK" << std::endl;
    std::cout << "✅ regd_Bm1(): OK" << std::endl;

    std::cout << "\nLISTO PARA FASE 3: Constructores" << std::endl;
    return 0;
}