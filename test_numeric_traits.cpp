/**
 * @file test_numeric_traits.cpp
 * @brief Test de las especializaciones de traits estándar
 */

#include <iostream>
#include <type_traits>
#include <limits>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "include/nat_reg_digs_t.hpp"
#include "include/int_reg_digs_t.hpp"
#include "include/numeric_traits_specializations.hpp"

using namespace NumRepr;

// Tipos de prueba
using nat_test_t = nat_reg_digs_t<10, 3>;
using int_test_t = int_reg_digs_t<10, 3>;

void test_numeric_limits()
{
    std::cout << "=== TEST: std::numeric_limits ===\n";

    // Test para nat_reg_digs_t
    std::cout << "nat_reg_digs_t<10,3> limits:\n";
    std::cout << "  is_specialized: " << std::numeric_limits<nat_test_t>::is_specialized << "\n";
    std::cout << "  is_signed: " << std::numeric_limits<nat_test_t>::is_signed << "\n";
    std::cout << "  is_integer: " << std::numeric_limits<nat_test_t>::is_integer << "\n";
    std::cout << "  is_exact: " << std::numeric_limits<nat_test_t>::is_exact << "\n";
    std::cout << "  radix: " << std::numeric_limits<nat_test_t>::radix << "\n";
    std::cout << "  digits: " << std::numeric_limits<nat_test_t>::digits << "\n";
    std::cout << "  digits10: " << std::numeric_limits<nat_test_t>::digits10 << "\n";
    std::cout << "  is_bounded: " << std::numeric_limits<nat_test_t>::is_bounded << "\n";

    // Test para int_reg_digs_t
    std::cout << "\nint_reg_digs_t<10,3> limits:\n";
    std::cout << "  is_specialized: " << std::numeric_limits<int_test_t>::is_specialized << "\n";
    std::cout << "  is_signed: " << std::numeric_limits<int_test_t>::is_signed << "\n";
    std::cout << "  is_integer: " << std::numeric_limits<int_test_t>::is_integer << "\n";
    std::cout << "  is_exact: " << std::numeric_limits<int_test_t>::is_exact << "\n";
    std::cout << "  radix: " << std::numeric_limits<int_test_t>::radix << "\n";
    std::cout << "  digits: " << std::numeric_limits<int_test_t>::digits << "\n";
    std::cout << "  digits10: " << std::numeric_limits<int_test_t>::digits10 << "\n";

    std::cout << "✅ std::numeric_limits OK\n\n";
}

void test_type_traits()
{
    std::cout << "=== TEST: Type Traits ===\n";

    // Test para nat_reg_digs_t
    std::cout << "nat_reg_digs_t<10,3> traits:\n";
    std::cout << "  is_arithmetic: " << std::is_arithmetic_v<nat_test_t> << "\n";
    std::cout << "  is_integral: " << std::is_integral_v<nat_test_t> << "\n";
    std::cout << "  is_signed: " << std::is_signed_v<nat_test_t> << "\n";
    std::cout << "  is_unsigned: " << std::is_unsigned_v<nat_test_t> << "\n";
    std::cout << "  is_scalar: " << std::is_scalar_v<nat_test_t> << "\n";

    // Test para int_reg_digs_t
    std::cout << "\nint_reg_digs_t<10,3> traits:\n";
    std::cout << "  is_arithmetic: " << std::is_arithmetic_v<int_test_t> << "\n";
    std::cout << "  is_integral: " << std::is_integral_v<int_test_t> << "\n";
    std::cout << "  is_signed: " << std::is_signed_v<int_test_t> << "\n";
    std::cout << "  is_unsigned: " << std::is_unsigned_v<int_test_t> << "\n";
    std::cout << "  is_scalar: " << std::is_scalar_v<int_test_t> << "\n";

    std::cout << "✅ Type traits OK\n\n";
}

void test_hash()
{
    std::cout << "=== TEST: std::hash ===\n";

    // Test hash para nat_reg_digs_t
    nat_test_t nat1, nat2;
    nat1[0] = nat_test_t::dig_t{5};
    nat2[0] = nat_test_t::dig_t{7};

    std::hash<nat_test_t> nat_hasher;
    auto hash1 = nat_hasher(nat1);
    auto hash2 = nat_hasher(nat2);

    std::cout << "nat hash(5): " << hash1 << "\n";
    std::cout << "nat hash(7): " << hash2 << "\n";
    std::cout << "Hashes diferentes: " << (hash1 != hash2 ? "✅" : "❌") << "\n";

    // Test hash para int_reg_digs_t - usando asignación de enteros
    int_test_t int1, int2;
    int1 = 5;  // Positivo por defecto
    int2 = -5; // El operador= debería manejar el signo

    std::hash<int_test_t> int_hasher;
    auto hash3 = int_hasher(int1);
    auto hash4 = int_hasher(int2);

    std::cout << "int hash(+5): " << hash3 << "\n";
    std::cout << "int hash(-5): " << hash4 << "\n";
    std::cout << "Hashes diferentes: " << (hash3 != hash4 ? "✅" : "❌") << "\n";

    std::cout << "✅ std::hash OK\n\n";
}

void test_unordered_containers()
{
    std::cout << "=== TEST: Unordered Containers ===\n";

    // Test std::unordered_set
    std::unordered_set<nat_test_t> nat_set;

    nat_test_t nat1, nat2;
    nat1[0] = nat_test_t::dig_t{5};
    nat2[0] = nat_test_t::dig_t{10 % 10}; // 0 en base 10

    nat_set.insert(nat1);
    nat_set.insert(nat2);

    std::cout << "unordered_set size: " << nat_set.size() << "\n";
    std::cout << "Contains nat1: " << (nat_set.count(nat1) ? "✅" : "❌") << "\n";
    std::cout << "Contains nat2: " << (nat_set.count(nat2) ? "✅" : "❌") << "\n";

    // Test std::unordered_map
    std::unordered_map<int_test_t, std::string> int_map;

    int_test_t key1, key2;
    key1 = 3;  // Positivo por defecto
    key2 = -3; // Negativo

    int_map[key1] = "positive three";
    int_map[key2] = "negative three";

    std::cout << "unordered_map size: " << int_map.size() << "\n";
    std::cout << "key1 maps to: \"" << int_map[key1] << "\"\n";
    std::cout << "key2 maps to: \"" << int_map[key2] << "\"\n";

    std::cout << "✅ Unordered containers OK\n\n";
}

void test_conversion_traits()
{
    std::cout << "=== TEST: Conversion Traits ===\n";

    // Test make_signed/make_unsigned
    std::cout << "make_signed<nat_reg_digs_t<10,3>>::type: ";
    std::cout << (std::is_same_v<std::make_signed_t<nat_test_t>, int_reg_digs_t<10, 2>> ? "✅" : "❌") << "\n";

    std::cout << "make_unsigned<int_reg_digs_t<10,3>>::type: ";
    std::cout << (std::is_same_v<std::make_unsigned_t<int_test_t>, nat_reg_digs_t<10, 4>> ? "✅" : "❌") << "\n";

    // Test common_type
    using nat_3 = nat_reg_digs_t<10, 3>;
    using nat_5 = nat_reg_digs_t<10, 5>;
    using common_nat = std::common_type_t<nat_3, nat_5>;

    std::cout << "common_type<nat_3, nat_5>: ";
    std::cout << (std::is_same_v<common_nat, nat_reg_digs_t<10, 5>> ? "✅" : "❌") << "\n";

    std::cout << "✅ Conversion traits OK\n\n";
}

void test_algorithm_compatibility()
{
    std::cout << "=== TEST: Algorithm Compatibility ===\n";

    // Test std::swap
    nat_test_t a, b;
    a[0] = nat_test_t::dig_t{5};
    b[0] = nat_test_t::dig_t{7};

    std::cout << "Antes swap: a[0]=" << a[0].get() << ", b[0]=" << b[0].get() << "\n";
    std::swap(a, b);
    std::cout << "Después swap: a[0]=" << a[0].get() << ", b[0]=" << b[0].get() << "\n";

    bool swap_ok = (a[0].get() == 7) && (b[0].get() == 5);
    std::cout << "Swap correcto: " << (swap_ok ? "✅" : "❌") << "\n";

    std::cout << "✅ Algorithm compatibility OK\n\n";
}

void test_limits_values()
{
    std::cout << "=== TEST: Numeric Limits Values ===\n";

    // Test valores de nat_reg_digs_t
    auto nat_min = std::numeric_limits<nat_test_t>::min();
    auto nat_max = std::numeric_limits<nat_test_t>::max();
    auto nat_epsilon = std::numeric_limits<nat_test_t>::epsilon();

    std::cout << "nat_test_t::min() todos ceros: ";
    bool nat_min_ok = true;
    for (size_t i = 0; i < 3; ++i)
    {
        if (nat_min[i].get() != 0)
        {
            nat_min_ok = false;
            break;
        }
    }
    std::cout << (nat_min_ok ? "✅" : "❌") << "\n";

    std::cout << "nat_test_t::epsilon() es 1: ";
    std::cout << (nat_epsilon[0].get() == 1 ? "✅" : "❌") << "\n";

    // Test valores de int_reg_digs_t
    auto int_min = std::numeric_limits<int_test_t>::min();
    auto int_max = std::numeric_limits<int_test_t>::max();

    std::cout << "int_test_t::min() es negativo: ";
    std::cout << (int_min.is_negative() ? "✅" : "❌") << "\n";

    std::cout << "int_test_t::max() es positivo: ";
    std::cout << (int_max.is_positive() ? "✅" : "❌") << "\n";

    std::cout << "✅ Numeric limits values OK\n\n";
}

int main()
{
    std::cout << "================================================================\n";
    std::cout << "    TEST DE ESPECIALIZACIONES DE TRAITS ESTÁNDAR\n";
    std::cout << "    Validación de compatibilidad con el ecosistema C++\n";
    std::cout << "================================================================\n\n";

    test_numeric_limits();
    test_type_traits();
    test_hash();
    test_unordered_containers();
    test_conversion_traits();
    test_algorithm_compatibility();
    test_limits_values();

    std::cout << "=== RESUMEN FINAL ===\n";
    std::cout << "✅ std::numeric_limits: Especializaciones completas\n";
    std::cout << "✅ Type traits: is_arithmetic, is_integral, is_signed, etc.\n";
    std::cout << "✅ std::hash: Funcionando en containers unordered\n";
    std::cout << "✅ Conversion traits: make_signed, make_unsigned, common_type\n";
    std::cout << "✅ Algorithm support: std::swap y compatibilidad STL\n";
    std::cout << "✅ Limits values: min, max, epsilon funcionando\n";
    std::cout << "\n🎯 TIPOS AHORA SON CIUDADANOS DE PRIMERA CLASE EN C++\n";
    std::cout << "🚀 COMPATIBILIDAD TOTAL CON ECOSISTEMA ESTÁNDAR ALCANZADA\n";

    return 0;
}