#include <iostream>
#include "core/dig_t.hpp"

using namespace NumRepr;

int main()
{
    // Verificar qué pasa con el número gigantesco
    unsigned long long huge = 999999999999999ULL;
    unsigned long long expected = huge % 10;

    std::cout << "Número gigantesco: " << huge << std::endl;
    std::cout << "Esperado (huge % 10): " << expected << std::endl;

    try
    {
        dig_t<10> parsed("d[999999999999999]B10");
        std::cout << "Parsing resultado: " << parsed.get() << std::endl;
        std::cout << "¿Son iguales? " << (parsed.get() == expected ? "SÍ" : "NO") << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error en parsing: " << e.what() << std::endl;
    }

    return 0;
}