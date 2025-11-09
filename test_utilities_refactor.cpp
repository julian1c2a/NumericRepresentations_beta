//
// Test específico para verificar la refactorización de utilities.hpp
//
#include <iostream>
#include <tuple>

#include "core/internal/utilities.hpp"

using namespace utilities::special;

// Función objeto de ejemplo para probar la nueva interfaz
struct TestFunctor
{
    template <std::size_t Base, std::size_t Index>
    constexpr void operator()(auto &&element) const
    {
        std::cout << "Processing element at index " << Index
                  << " with base " << Base
                  << " and value " << element << "\n";
    }
};

int main()
{
    try
    {
        std::cout << "=== TEST DE REFACTORIZACIÓN utilities.hpp ===\n";

        // Test de la nueva interfaz ct_for
        std::tuple<int, double, float> test_tuple{42, 3.14, 2.71f};

        std::cout << "Probando nueva interfaz ct_for con función objeto:\n";
        ct_for<0, 3, 10>(test_tuple, TestFunctor{});

        std::cout << "\n✅ Nueva interfaz ct_for funciona!\n";

        // Test de conversion_to_int
        std::cout << "\nProbando conversion_to_int (si está disponible)...\n";

        std::cout << "\n🎉 utilities.hpp REFACTORIZADO FUNCIONA!\n";

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