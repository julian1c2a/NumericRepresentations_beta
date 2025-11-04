#include <iostream>
#include <limits>
#include "dig_t.hpp"

using namespace NumRepr;

int main()
{
    // Investigar el overflow en parsing
    using base10_sig_uint = dig_t<10>::sig_uint_t;

    std::cout << "=== Investigación del Parsing Issue ===" << std::endl;
    std::cout << "sig_uint_t size: " << sizeof(base10_sig_uint) * 8 << " bits" << std::endl;
    std::cout << "sig_uint_t max: " << std::numeric_limits<base10_sig_uint>::max() << std::endl;

    unsigned long long test_number = 999999999999999ULL;
    std::cout << "Número a parsear: " << test_number << std::endl;
    std::cout << "Esperado (% 10): " << (test_number % 10) << std::endl;

    // Simular el algoritmo de parsing manualmente
    std::string num_str = "999999999999999";
    base10_sig_uint numero = 0;
    bool overflow_detected = false;

    std::cout << "\n=== Simulando parsing paso a paso ===" << std::endl;
    for (char c : num_str)
    {
        base10_sig_uint old_numero = numero;
        numero = numero * 10 + (c - '0');

        // Detectar overflow
        if (numero < old_numero)
        {
            overflow_detected = true;
            std::cout << "¡OVERFLOW detectado en carácter '" << c << "'!" << std::endl;
            std::cout << "  Antes: " << old_numero << std::endl;
            std::cout << "  Después: " << numero << std::endl;
            break;
        }

        std::cout << "Carácter '" << c << "': numero = " << numero << std::endl;
    }

    if (!overflow_detected)
    {
        std::cout << "No hubo overflow. Resultado: " << numero << std::endl;
        std::cout << "Modulo 10: " << (numero % 10) << std::endl;
    }

    // Test con el parser real
    std::cout << "\n=== Test con parser real ===" << std::endl;
    try
    {
        dig_t<10> parsed("d[999999999999999]B10");
        std::cout << "Parser resultado: " << parsed.get() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Probar con números más pequeños
    std::cout << "\n=== Tests con números progresivamente más grandes ===" << std::endl;
    std::vector<std::string> test_numbers = {
        "999",
        "999999",
        "999999999",
        "999999999999",
        "999999999999999"};

    for (const auto &num : test_numbers)
    {
        try
        {
            dig_t<10> parsed("d[" + num + "]B10");
            unsigned long long expected = std::stoull(num) % 10;
            std::cout << "Número " << num << ": parsed=" << parsed.get()
                      << ", esperado=" << expected
                      << " " << (parsed.get() == expected ? "✅" : "❌") << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "Número " << num << ": ERROR - " << e.what() << std::endl;
        }
    }

    return 0;
}