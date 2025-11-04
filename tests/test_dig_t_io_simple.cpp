#include <iostream>
#include <sstream>
#include <cassert>

// Test simplificado de operadores de E/S de dig_t
#include "../include/dig_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "=== TEST SIMPLIFICADO DE OPERADORES I/O ===" << std::endl;

    // Test básico con dig_t<10>
    using dig_type = dig_t<10>;

    // 1. Test operador de salida
    std::cout << "\n--- OPERADOR DE SALIDA (<<) ---" << std::endl;
    dig_type a(7u);
    dig_type zero = dig_type::dig_0();
    dig_type max = dig_type::dig_max();

    std::cout << "a = " << a << std::endl;
    std::cout << "zero = " << zero << std::endl;
    std::cout << "max = " << max << std::endl;

    // 2. Test formato usando stringstream
    std::ostringstream oss;
    oss << a;
    std::string output = oss.str();
    std::cout << "Formato capturado: \"" << output << "\"" << std::endl;

    // 3. Test simple de entrada (formato esperado por parser)
    std::cout << "\n--- OPERADOR DE ENTRADA (>>) ---" << std::endl;

    std::string input_format = "d#5#B10";
    std::cout << "Probando entrada: \"" << input_format << "\"" << std::endl;

    std::istringstream iss(input_format);
    dig_type parsed;

    try
    {
        iss >> parsed;
        std::cout << "✅ Parsing exitoso: valor = " << parsed.get() << std::endl;
    }
    catch (...)
    {
        std::cout << "❌ Error en parsing" << std::endl;
    }

    // 4. Test con formato de salida actual
    std::cout << "\nProbando con formato de salida: \"" << output << "\"" << std::endl;
    std::istringstream iss2(output);
    dig_type parsed2;

    try
    {
        iss2 >> parsed2;
        std::cout << "✅ Parsing exitoso con formato salida: valor = " << parsed2.get() << std::endl;
    }
    catch (...)
    {
        std::cout << "❌ Parsing falló con formato de salida" << std::endl;
    }

    std::cout << "\n🎉 TEST SIMPLIFICADO COMPLETADO" << std::endl;

    return 0;
}