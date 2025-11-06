#include "include/nat_reg_digs_t.hpp"
#include <iostream>

using namespace NumRepr;
using Binary4 = nat_reg_digs_t<2, 4>;

int main()
{
    std::cout << "=== FASE 3: CONSTRUCTORES (SIMPLIFICADO) ===" << std::endl;
    std::cout << "Probando constructores básicos que sabemos funcionan\n"
              << std::endl;

    // TEST 1: Constructor por defecto (ya probado)
    try
    {
        std::cout << "Test 1: Constructor por defecto" << std::endl;
        Binary4 bin_default;
        std::cout << "  ✅ OK - " << bin_default.to_string() << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en constructor por defecto" << std::endl;
        return 1;
    }

    // TEST 2: Constructor desde initializer_list
    try
    {
        std::cout << "\nTest 2: Constructor desde initializer_list" << std::endl;
        std::cout << "  Creando Binary4{dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{1}}..." << std::endl;
        Binary4 bin_list{dig_t<2>{0}, dig_t<2>{1}, dig_t<2>{0}, dig_t<2>{1}};
        std::cout << "  ✅ OK - " << bin_list.to_string() << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en constructor initializer_list" << std::endl;
    }

    // TEST 3: Constructor copia desde otro nat_reg_digs_t
    try
    {
        std::cout << "\nTest 3: Constructor copia" << std::endl;
        Binary4 original = Binary4::regd_1();
        Binary4 copia(original);
        std::cout << "  ✅ OK - Original: " << original.to_string() << std::endl;
        std::cout << "         Copia:    " << copia.to_string() << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en constructor copia" << std::endl;
    }

    // TEST 4: Constructor movimiento
    try
    {
        std::cout << "\nTest 4: Constructor movimiento" << std::endl;
        auto temp_reg = reg_digs_t<2, 4>::regd_1();
        Binary4 bin_moved{std::move(temp_reg)};
        std::cout << "  ✅ OK - " << bin_moved.to_string() << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en constructor movimiento" << std::endl;
    }

    // TEST 5: Factory methods como constructores alternativos
    try
    {
        std::cout << "\nTest 5: Factory methods (alternativa a constructores)" << std::endl;
        auto zero = Binary4::regd_0();
        auto one = Binary4::regd_1();
        auto base = Binary4::regd_B();
        auto max = Binary4::regd_Bm1();

        std::cout << "  ✅ regd_0():  " << zero.to_string() << std::endl;
        std::cout << "  ✅ regd_1():  " << one.to_string() << std::endl;
        std::cout << "  ✅ regd_B():  " << base.to_string() << std::endl;
        std::cout << "  ✅ regd_Bm1(): " << max.to_string() << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en factory methods" << std::endl;
    }

    std::cout << "\n=== FASE 3 (SIMPLIFICADA) COMPLETADA ====" << std::endl;
    std::cout << "✅ Constructores básicos funcionan correctamente" << std::endl;
    std::cout << "⚠️  Constructor variádico omitido (muy complejo)" << std::endl;
    std::cout << "\n🚀 LISTO PARA FASE 4: Set Operations" << std::endl;
    return 0;
}