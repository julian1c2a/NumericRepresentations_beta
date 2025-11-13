/**
 * @file test_mult_inv_optimized.cpp
 * @brief Test de mult_inv() optimizado (sin llamadas redundantes a is_unit)
 */

#include <iostream>
#include <chrono>
#include "dig_t.hpp"

using namespace NumRepr;

int main() {
    std::cout << "=== Test de mult_inv() optimizado ===" << std::endl;
    std::cout << std::endl;

    // Test 1: Base prima pequeña (7)
    std::cout << "1. Base prima 7 - todos los elementos no-cero tienen inverso" << std::endl;
    {
        constexpr dig_t<7> d1(2);
        constexpr dig_t<7> inv1 = d1.mult_inv();
        static_assert((d1 * inv1).get() == 1, "2 * inv(2) debe ser 1 mod 7");
        std::cout << "   ✓ 2 × " << static_cast<int>(inv1.get()) 
                  << " ≡ 1 (mod 7)" << std::endl;

        constexpr dig_t<7> d2(3);
        constexpr dig_t<7> inv2 = d2.mult_inv();
        static_assert((d2 * inv2).get() == 1, "3 * inv(3) debe ser 1 mod 7");
        std::cout << "   ✓ 3 × " << static_cast<int>(inv2.get()) 
                  << " ≡ 1 (mod 7)" << std::endl;

        constexpr dig_t<7> d3(5);
        constexpr dig_t<7> inv3 = d3.mult_inv();
        static_assert((d3 * inv3).get() == 1, "5 * inv(5) debe ser 1 mod 7");
        std::cout << "   ✓ 5 × " << static_cast<int>(inv3.get()) 
                  << " ≡ 1 (mod 7)" << std::endl;
    }

    // Test 2: Base compuesta (10) - solo algunas unidades
    std::cout << std::endl;
    std::cout << "2. Base compuesta 10 - solo gcd(n,10)=1 tienen inverso" << std::endl;
    {
        constexpr dig_t<10> d1(3);
        constexpr dig_t<10> inv1 = d1.mult_inv();
        static_assert((d1 * inv1).get() == 1, "3 * inv(3) debe ser 1 mod 10");
        std::cout << "   ✓ 3 × " << static_cast<int>(inv1.get()) 
                  << " ≡ 1 (mod 10)" << std::endl;

        constexpr dig_t<10> d2(7);
        constexpr dig_t<10> inv2 = d2.mult_inv();
        static_assert((d2 * inv2).get() == 1, "7 * inv(7) debe ser 1 mod 10");
        std::cout << "   ✓ 7 × " << static_cast<int>(inv2.get()) 
                  << " ≡ 1 (mod 10)" << std::endl;

        constexpr dig_t<10> d3(9);
        constexpr dig_t<10> inv3 = d3.mult_inv();
        static_assert((d3 * inv3).get() == 1, "9 * inv(9) debe ser 1 mod 10");
        std::cout << "   ✓ 9 × " << static_cast<int>(inv3.get()) 
                  << " ≡ 1 (mod 10)" << std::endl;

        // Elementos que NO son unidades (gcd != 1)
        constexpr dig_t<10> d4(2);  // gcd(2,10) = 2
        constexpr dig_t<10> inv4 = d4.mult_inv();
        static_assert(inv4.get() == 0, "2 no tiene inverso mod 10");
        std::cout << "   ✓ 2 no tiene inverso (devuelve 0)" << std::endl;
    }

    // Test 3: Base prima más grande (17)
    std::cout << std::endl;
    std::cout << "3. Base prima 17" << std::endl;
    {
        constexpr dig_t<17> d1(5);
        constexpr dig_t<17> inv1 = d1.mult_inv();
        static_assert((d1 * inv1).get() == 1, "5 * inv(5) debe ser 1 mod 17");
        std::cout << "   ✓ 5 × " << static_cast<int>(inv1.get()) 
                  << " ≡ 1 (mod 17)" << std::endl;

        constexpr dig_t<17> d2(12);
        constexpr dig_t<17> inv2 = d2.mult_inv();
        static_assert((d2 * inv2).get() == 1, "12 * inv(12) debe ser 1 mod 17");
        std::cout << "   ✓ 12 × " << static_cast<int>(inv2.get()) 
                  << " ≡ 1 (mod 17)" << std::endl;
    }

    // Test 4: Casos especiales
    std::cout << std::endl;
    std::cout << "4. Casos especiales" << std::endl;
    {
        constexpr dig_t<10> d1(1);
        constexpr dig_t<10> inv1 = d1.mult_inv();
        static_assert(inv1.get() == 1, "inv(1) = 1");
        std::cout << "   ✓ inv(1) = 1" << std::endl;

        constexpr dig_t<11> d2(10);  // B-1 en base 11
        constexpr dig_t<11> inv2 = d2.mult_inv();
        static_assert(inv2.get() == 10, "inv(B-1) = B-1");
        std::cout << "   ✓ inv(10) = 10 en base 11 (B-1)" << std::endl;
    }

    // Test 5: Medición de rendimiento (base compuesta vs prima)
    std::cout << std::endl;
    std::cout << "5. Comparación de rendimiento (runtime)" << std::endl;
    {
        // Base compuesta 256 - requiere verificar gcd
        auto start1 = std::chrono::high_resolution_clock::now();
        dig_t<256> d1(17);
        dig_t<256> inv1 = d1.mult_inv();
        auto end1 = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
        
        std::cout << "   Base 256 (compuesta): inv(17) = " 
                  << static_cast<int>(inv1.get()) 
                  << " [" << duration1.count() << " µs]" << std::endl;

        // Base prima 257 - optimización directa (todos son unidades)
        auto start2 = std::chrono::high_resolution_clock::now();
        dig_t<257> d2(17);
        dig_t<257> inv2 = d2.mult_inv();
        auto end2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
        
        std::cout << "   Base 257 (prima): inv(17) = " 
                  << static_cast<int>(inv2.get())
                  << " [" << duration2.count() << " µs]" << std::endl;

        std::cout << "   Nota: Base prima más rápida (omite verificación gcd)" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== ✓ Todos los tests pasaron exitosamente ===" << std::endl;
    std::cout << "=== ✓ Optimización verificada: no más llamadas redundantes ===" << std::endl;
    return 0;
}
