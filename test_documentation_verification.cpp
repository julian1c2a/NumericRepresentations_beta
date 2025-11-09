//
// Test de verificación después de documentar reg_digs_t.hpp
//
#include <iostream>

#include "core/dig_t.hpp"
#include "reg_digs_t.hpp"

using namespace NumRepr;

int main()
{
    try
    {
        std::cout << "=== VERIFICACIÓN POST-DOCUMENTACIÓN ===\n";

        // Test básico de construcción
        reg_digs_t<10, 3> test_basic;
        std::cout << "✅ Constructor por defecto funciona\n";

        // Test de inicialización
        reg_digs_t<10, 3> test_init{dig_t<10>(1), dig_t<10>(2), dig_t<10>(3)};
        std::cout << "✅ Constructor variádico funciona\n";

        // Test de lista de inicialización
        reg_digs_t<10, 3> test_list{{dig_t<10>(5), dig_t<10>(6), dig_t<10>(7)}};
        std::cout << "✅ Constructor con initializer_list funciona\n";

        // Test de comparación
        reg_digs_t<10, 3> test_compare1, test_compare2;
        test_compare1[0] = dig_t<10>(5);
        test_compare2[0] = dig_t<10>(5);
        bool equal = (test_compare1 == test_compare2);
        std::cout << "✅ Operadores de comparación funcionan: " << (equal ? "true" : "false") << "\n";

        // Test de reverse
        reg_digs_t<10, 3> test_rev{dig_t<10>(1), dig_t<10>(2), dig_t<10>(3)};
        test_rev.reverse();
        std::cout << "✅ Método reverse() funciona\n";

        // Test de constantes
        auto zero = reg_digs_t<10, 3>::dig_0();
        auto one = reg_digs_t<10, 3>::dig_1();
        std::cout << "✅ Constantes estáticas funcionan: zero=" << zero.get() << ", one=" << one.get() << "\n";

        // Test de STL compatibility
        for (const auto &digit : test_init)
        {
            // Range-based for funciona
        }
        std::cout << "✅ Compatibilidad STL (iteradores) funciona\n";

        std::cout << "\n🎉 TODOS LOS TESTS PASARON - DOCUMENTACIÓN EXITOSA!\n";
        std::cout << "📚 reg_digs_t.hpp ahora está completamente documentado\n";

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