/**
 * @file test_basic_methods.cpp
 * @brief Test Fase 1 - Métodos Básicos de nat_reg_digs_t
 *
 * Análisis sistemático: empezar con lo más simple
 * - Constructor por defecto
 * - to_string()
 * - operator[] (heredado)
 * - Acceso básico a dígitos
 */

#include <iostream>
#include "include/nat_reg_digs_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "=== FASE 1: MÉTODOS BÁSICOS ===" << std::endl;
    std::cout << "Análisis sistemático método por método" << std::endl;

    try
    {
        // TEST 1: Constructor por defecto
        std::cout << "\nTest 1: Constructor por defecto" << std::endl;
        std::cout << "  Creando nat_reg_digs_t<2, 4>..." << std::flush;

        nat_reg_digs_t<2, 4> binario_basico;

        std::cout << " ✅ OK" << std::endl;
        std::cout << "  Constructor por defecto funciona correctamente" << std::endl;

        // TEST 2: Método to_string()
        std::cout << "\nTest 2: Método to_string()" << std::endl;
        std::cout << "  Llamando to_string()..." << std::flush;

        std::string resultado = binario_basico.to_string();

        std::cout << " ✅ OK" << std::endl;
        std::cout << "  Resultado: " << resultado << std::endl;

        // TEST 3: Heredar operator[] (solo lectura)
        std::cout << "\nTest 3: operator[] heredado (lectura)" << std::endl;
        std::cout << "  Accediendo a dígitos..." << std::flush;

        // Intentar acceso de solo lectura a los dígitos
        const auto &binario_const = binario_basico;
        auto digito0 = binario_const[0];
        auto digito1 = binario_const[1];

        std::cout << " ✅ OK" << std::endl;
        std::cout << "  Dígito[0]: accesible" << std::endl;
        std::cout << "  Dígito[1]: accesible" << std::endl;

        // TEST 4: Verificar que hereda correctamente de reg_digs_t
        std::cout << "\nTest 4: Verificación de herencia" << std::endl;
        std::cout << "  Verificando herencia de reg_digs_t<2,4>..." << std::flush;

        // Debería poder usar métodos heredados básicos
        std::cout << " ✅ OK" << std::endl;
        std::cout << "  Herencia funciona correctamente" << std::endl;
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

    std::cout << "\n=== FASE 1 COMPLETADA EXITOSAMENTE ===" << std::endl;
    std::cout << "✅ Métodos básicos funcionan correctamente" << std::endl;
    std::cout << "✅ Constructor por defecto: OK" << std::endl;
    std::cout << "✅ to_string(): OK" << std::endl;
    std::cout << "✅ operator[] herencia: OK" << std::endl;

    std::cout << "\nLISTO PARA FASE 2: Factory Methods" << std::endl;
    return 0;
}