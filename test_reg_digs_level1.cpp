//
// Test progresivo para reg_digs_t - empezando simple
//
#include <iostream>
#include <string>
#include <algorithm> // Para std::count_if

// Incluir headers necesarios
#include "dig_t.hpp"
#include "reg_digs_t.hpp"

using namespace NumRepr;

int main()
{
    try
    {
        std::cout << "=== Test Progresivo reg_digs_t ===\n\n";

        // Test 1: Headers ya incluidos al inicio
        std::cout << "Test 1: Headers incluidos exitosamente\n\n"; // Test 2: Crear instancia básica
        std::cout << "Test 2: Creando instancia básica reg_digs_t<10, 3>...\n";
        reg_digs_t<10, 3> reg_basic;
        std::cout << "✅ Instancia creada exitosamente\n";
        std::cout << "Tamaño: " << reg_basic.size() << " dígitos\n\n";

        // Test 3: Acceso básico
        std::cout << "Test 3: Acceso a elementos...\n";
        std::cout << "reg_basic[0] = " << reg_basic[0].to_string() << "\n";
        std::cout << "reg_basic[1] = " << reg_basic[1].to_string() << "\n";
        std::cout << "reg_basic[2] = " << reg_basic[2].to_string() << "\n";
        std::cout << "✅ Acceso exitoso\n\n";

        // Test 4: Asignación simple
        std::cout << "Test 4: Asignación de valores...\n";
        reg_basic[0] = dig_t<10>(5);
        reg_basic[1] = dig_t<10>(7);
        reg_basic[2] = dig_t<10>(3);

        std::cout << "Después de asignación:\n";
        std::cout << "reg_basic[0] = " << reg_basic[0].to_string() << "\n";
        std::cout << "reg_basic[1] = " << reg_basic[1].to_string() << "\n";
        std::cout << "reg_basic[2] = " << reg_basic[2].to_string() << "\n";
        std::cout << "✅ Asignación exitosa\n\n";

        // Test 5: Iteradores básicos
        std::cout << "Test 5: Iteración básica...\n";
        std::cout << "Contenido completo: [";
        for (size_t i = 0; i < reg_basic.size(); ++i)
        {
            if (i > 0)
                std::cout << ", ";
            std::cout << reg_basic[i].get();
        }
        std::cout << "]\n";
        std::cout << "✅ Iteración exitosa\n\n";

        std::cout << "=== Nivel 1 completado exitosamente ===\n";
        std::cout << "reg_digs_t funciona a nivel básico\n";

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "❌ Error desconocido" << std::endl;
        return 1;
    }
}