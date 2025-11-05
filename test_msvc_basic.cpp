//
// Test simple para MSVC - sin usar utilities.hpp avanzado
//
#include <iostream>

// Solo incluir los tipos básicos, no reg_digs_t completo
#include "basic_types.hpp"

using namespace NumRepr;

int main()
{
    try
    {
        std::cout << "=== TEST BÁSICO PARA MSVC ===\n";

        // Test de tipos básicos
        uint_t test_uint = 42;
        sint_t test_sint = -42;

        std::cout << "✅ Tipos básicos funcionan: uint=" << test_uint << ", sint=" << test_sint << "\n";

        // Test de tipos 64-bit
        uint64_t test_64 = 1234567890ULL;
        std::cout << "✅ Tipos 64-bit funcionan: " << test_64 << "\n";

        std::cout << "\n🎉 TEST BÁSICO MSVC EXITOSO!\n";

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "❌ Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "❌ Error desconocido" << std::endl;
        return 1;
    }
}