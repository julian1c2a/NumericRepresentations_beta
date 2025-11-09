/**
 * @file test_dig_t_with_utilities.cpp
 * @brief Test de dig_t.hpp + utilities.hpp para aislar problema MSVC
 */

#include <iostream>

// Incluir ambos archivos problemáticos
#include "include/dig_t.hpp"
#include "include/utilities.hpp"

int main()
{
    std::cout << "Test dig_t.hpp + utilities.hpp...\n";

    // Test básico de dig_t
    using dig_t = NumRepr::dig_t<10>;

    dig_t d1{5};
    dig_t d2{3};

    std::cout << "dig_t creado: " << d1.get() << std::endl;
    std::cout << "dig_t creado: " << d2.get() << std::endl;

    // Test básico de utilities (sin reg_digs_t)
    std::tuple<int, int, int> test_tuple{10, 20, 30};

    std::cout << "Tuple creada con elementos: " << std::get<0>(test_tuple)
              << ", " << std::get<1>(test_tuple) << ", " << std::get<2>(test_tuple) << std::endl;

    std::cout << "Test dig_t + utilities completado!\n";
    return 0;
}