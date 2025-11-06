#include "include/nat_reg_digs_t.hpp"
#include <iostream>

using namespace NumRepr;
using Binary4 = nat_reg_digs_t<2, 4>;

int main()
{
    std::cout << "=== FASE 3: CONSTRUCTORES ===" << std::endl;
    std::cout << "Probando constructores de nat_reg_digs_t uno por uno\n"
              << std::endl;

    // TEST 1: Constructor por defecto (ya sabemos que funciona)
    try
    {
        std::cout << "Test 1: Constructor por defecto" << std::endl;
        Binary4 bin_default;
        std::cout << "  Creando Binary4 bin_default... ✅ OK" << std::endl;
        std::cout << "  Resultado: " << bin_default.to_string() << std::endl;
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
        std::cout << "  ✅ OK" << std::endl;
        std::cout << "  Resultado: " << bin_list.to_string() << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en constructor initializer_list" << std::endl;
        // No retornamos, continuamos con otros tests
    }

    // TEST 3: Constructor variádico
    try
    {
        std::cout << "\nTest 3: Constructor variádico" << std::endl;
        std::cout << "  Creando Binary4 desde argumentos separados..." << std::endl;
        auto dig0 = dig_t<2>{0};
        auto dig1 = dig_t<2>{1};
        auto dig2 = dig_t<2>{0};
        auto dig3 = dig_t<2>{1};
        Binary4 bin_variadic(dig0, dig1, dig2, dig3);
        std::cout << "  ✅ OK" << std::endl;
        std::cout << "  Resultado: " << bin_variadic.to_string() << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en constructor variádico" << std::endl;
    }

    // TEST 4: Constructor variádico con 4 argumentos (L=4)
    try
    {
        std::cout << "\nTest 4: Constructor variádico con 4 argumentos" << std::endl;
        std::cout << "  Probando Binary4(0, 1, 0, 1)..." << std::endl;
        Binary4 bin_variadic_ints(0, 1, 0, 1);
        std::cout << "  ✅ OK" << std::endl;
        std::cout << "  Resultado: " << bin_variadic_ints.to_string() << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en constructor variádico con enteros" << std::endl;
    }

    // TEST 5: Constructor copia desde otro nat_reg_digs_t
    try
    {
        std::cout << "\nTest 5: Constructor copia" << std::endl;
        Binary4 original = Binary4::regd_1();
        Binary4 copia(original);
        std::cout << "  ✅ OK" << std::endl;
        std::cout << "  Original: " << original.to_string() << std::endl;
        std::cout << "  Copia:    " << copia.to_string() << std::endl;
    }
    catch (...)
    {
        std::cout << "  ❌ Error en constructor copia" << std::endl;
    }

    std::cout << "\n=== FASE 3 COMPLETADA ===" << std::endl;
    std::cout << "Análisis de constructores terminado" << std::endl;
    return 0;
}