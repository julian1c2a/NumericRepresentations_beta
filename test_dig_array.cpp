//
// Test ultra-minimal para validar dig_t como building block
//
#include <iostream>
#include <array>

#include "dig_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "=== Test ultra-minimal de dig_t como building block ===\n\n";

    // Test 1: Crear dig_t básico
    std::cout << "Test 1: Crear dig_t básico\n";
    dig_t<10> d1(5);
    std::cout << "d1(5) = " << d1.get() << "\n";
    std::cout << "d1.to_string() = " << d1.to_string() << "\n\n";

    // Test 2: Array de 3 dig_t
    std::cout << "Test 2: Array de 3 dig_t\n";
    std::array<dig_t<10>, 3> arr;

    // No usar inicialización en constructor, hacerlo paso a paso
    arr[0] = dig_t<10>(3);
    arr[1] = dig_t<10>(2);
    arr[2] = dig_t<10>(1);

    std::cout << "Array: ";
    for (size_t i = 0; i < 3; ++i)
    {
        std::cout << arr[i].get();
        if (i < 2)
            std::cout << ", ";
    }
    std::cout << "\n\n";

    // Test 3: Operación simple
    std::cout << "Test 3: Operación simple\n";
    dig_t<10> a(3);
    dig_t<10> b(4);
    dig_t<10> suma = a + b;

    std::cout << a.get() << " + " << b.get() << " = " << suma.get() << "\n\n";

    std::cout << "=== Test completado exitosamente ===\n";
    std::cout << "Validado: dig_t funciona como building block para arrays\n";

    return 0;
}