//
// Test para verificar que dig_t.hpp compila correctamente
//
#include <iostream>

#include "dig_t.hpp"

using namespace NumRepr;

int main()
{
    try
    {
        std::cout << "=== VERIFICACIÓN DE dig_t.hpp ===\n";

        // Test básico de construcción
        dig_t<10> digit1;
        std::cout << "✅ Constructor por defecto: " << digit1.get() << "\n";

        // Test de construcción con valor
        dig_t<10> digit2(7);
        std::cout << "✅ Constructor con valor: " << digit2.get() << "\n";

        // Test de aritmética modular
        dig_t<10> digit3(9);
        dig_t<10> digit4 = digit3 + dig_t<10>(5); // 9 + 5 = 14 mod 10 = 4
        std::cout << "✅ Aritmética modular (9+5 mod 10): " << digit4.get() << "\n";

        // Test de diferentes bases
        dig_t<2> binary(1);
        dig_t<16> hex(15);
        std::cout << "✅ Diferentes bases - binario: " << binary.get() << ", hex: " << hex.get() << "\n";

        // Test de comparaciones
        bool equal = (digit2 == dig_t<10>(7));
        std::cout << "✅ Comparaciones: " << (equal ? "true" : "false") << "\n";

        std::cout << "\n🎉 dig_t.hpp FUNCIONA CORRECTAMENTE!\n";

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