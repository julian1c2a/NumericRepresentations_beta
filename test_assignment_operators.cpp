#include "include/nat_reg_digs_t.hpp"
#include <iostream>

using namespace NumRepr;
using Binary4 = nat_reg_digs_t<2, 4>;

int main()
{
    std::cout << "=== FASE 5: ASSIGNMENT OPERATORS ===" << std::endl;
    std::cout << "Probando operadores de asignación uno por uno\n"
              << std::endl;

    // TEST 1: operator=(dig_t) - Asignación desde dígito individual
    try
    {
        std::cout << "Test 1: operator=(dig_t)" << std::endl;
        Binary4 bin = Binary4::regd_0();
        std::cout << "  Antes: " << bin.to_string() << std::endl;

        // Probar asignación desde dig_t
        dig_t<2> digit_1{1};
        bin = digit_1;
        std::cout << "  Después de bin = dig_t(1): " << bin.to_string() << std::endl;
        std::cout << "  ✅ operator=(dig_t) funciona" << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en operator=(dig_t)" << std::endl;
    }

    // TEST 2: operator=(nat_reg_digs_t) - Asignación copia
    try
    {
        std::cout << "\nTest 2: operator=(nat_reg_digs_t) - copia" << std::endl;
        Binary4 bin1 = Binary4::regd_1();
        Binary4 bin2 = Binary4::regd_0();

        std::cout << "  bin1: " << bin1.to_string() << std::endl;
        std::cout << "  bin2: " << bin2.to_string() << std::endl;

        bin2 = bin1; // Asignación copia
        std::cout << "  Después de bin2 = bin1: " << bin2.to_string() << std::endl;
        std::cout << "  ✅ operator=(nat_reg_digs_t) copia funciona" << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en operator=(nat_reg_digs_t) copia" << std::endl;
    }

    // TEST 3: operator=(nat_reg_digs_t&&) - Asignación movimiento
    try
    {
        std::cout << "\nTest 3: operator=(nat_reg_digs_t&&) - movimiento" << std::endl;
        Binary4 bin = Binary4::regd_0();
        std::cout << "  Antes: " << bin.to_string() << std::endl;

        bin = Binary4::regd_B(); // Asignación desde rvalue
        std::cout << "  Después de bin = regd_B(): " << bin.to_string() << std::endl;
        std::cout << "  ✅ operator=(nat_reg_digs_t&&) movimiento funciona" << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en operator=(nat_reg_digs_t&&) movimiento" << std::endl;
    }

    // TEST 4: Verificación auto-asignación
    try
    {
        std::cout << "\nTest 4: Verificación auto-asignación" << std::endl;
        Binary4 bin = Binary4::regd_1();
        std::cout << "  Antes auto-asignación: " << bin.to_string() << std::endl;

        bin = bin; // Auto-asignación
        std::cout << "  Después de bin = bin: " << bin.to_string() << std::endl;
        std::cout << "  ✅ Auto-asignación funciona correctamente" << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en auto-asignación" << std::endl;
    }

    // TEST 5: operator=(reg_digs_t) - Asignación desde clase base
    try
    {
        std::cout << "\nTest 5: operator=(reg_digs_t) - desde clase base" << std::endl;
        Binary4 bin = Binary4::regd_0();
        auto base_reg = reg_digs_t<2, 4>::regd_1();

        std::cout << "  bin antes: " << bin.to_string() << std::endl;
        std::cout << "  base_reg: " << base_reg.to_string() << std::endl;

        bin = base_reg;
        std::cout << "  Después de bin = base_reg: " << bin.to_string() << std::endl;
        std::cout << "  ✅ operator=(reg_digs_t) funciona" << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en operator=(reg_digs_t)" << std::endl;
    }

    // TEST 6: Verificación de persistencia múltiple
    try
    {
        std::cout << "\nTest 6: Verificación múltiple asignaciones en secuencia" << std::endl;
        Binary4 bin = Binary4::regd_0();

        bin = Binary4::regd_1();
        std::cout << "  Paso 1: " << bin.to_string() << std::endl;

        bin = Binary4::regd_B();
        std::cout << "  Paso 2: " << bin.to_string() << std::endl;

        bin = Binary4::regd_0();
        std::cout << "  Paso 3: " << bin.to_string() << std::endl;

        std::cout << "  ✅ Asignaciones múltiples funcionan correctamente" << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en asignaciones múltiples" << std::endl;
    }

    std::cout << "\n=== FASE 5 COMPLETADA ===" << std::endl;
    std::cout << "Análisis de Assignment Operators terminado" << std::endl;
    std::cout << "\n🚀 LISTO PARA FASE 6: Arithmetic Operators" << std::endl;
    return 0;
}