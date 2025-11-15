/**
 * @file test_parse_pure_ct.cpp
 * @brief Tests para versiones consteval puras con recursión
 * 
 * Valida parse_prefix_fsm_ct, parse_number_fsm_ct, parse_base_fsm_ct
 * y parse_impl_pure_ct
 */

#include <iostream>
#include <array>
#include <core/dig_t.hpp>

using namespace NumRepr;

// ============================================================================
// TESTS DE parse_impl_pure_ct
// ============================================================================

/**
 * @brief Test formato 1: "d[N]BM"
 */
consteval bool test_pure_ct_format_1() {
    using dig10 = dig_t<10>;
    
    // "d[0]B10"
    constexpr std::array<char, 7> str1 = {'d', '[', '0', ']', 'B', '1', '0'};
    constexpr auto result1 = dig10::parse_impl_pure_ct(str1, 10);
    if (!result1 || *result1 != 0) return false;
    
    // "d[5]B10"
    constexpr std::array<char, 7> str2 = {'d', '[', '5', ']', 'B', '1', '0'};
    constexpr auto result2 = dig10::parse_impl_pure_ct(str2, 10);
    if (!result2 || *result2 != 5) return false;
    
    // "d[9]B10"
    constexpr std::array<char, 7> str3 = {'d', '[', '9', ']', 'B', '1', '0'};
    constexpr auto result3 = dig10::parse_impl_pure_ct(str3, 10);
    if (!result3 || *result3 != 9) return false;
    
    // "d[15]B10" → normaliza a 5
    constexpr std::array<char, 8> str4 = {'d', '[', '1', '5', ']', 'B', '1', '0'};
    constexpr auto result4 = dig10::parse_impl_pure_ct(str4, 10);
    if (!result4 || *result4 != 5) return false;
    
    return true;
}

/**
 * @brief Test formato 2: "d#N#BM"
 */
consteval bool test_pure_ct_format_2() {
    using dig10 = dig_t<10>;
    
    // "d#7#B10"
    constexpr std::array<char, 7> str1 = {'d', '#', '7', '#', 'B', '1', '0'};
    constexpr auto result1 = dig10::parse_impl_pure_ct(str1, 10);
    if (!result1 || *result1 != 7) return false;
    
    // "d#42#B10" → normaliza a 2
    constexpr std::array<char, 8> str2 = {'d', '#', '4', '2', '#', 'B', '1', '0'};
    constexpr auto result2 = dig10::parse_impl_pure_ct(str2, 10);
    if (!result2 || *result2 != 2) return false;
    
    return true;
}

/**
 * @brief Test formato 3: "dig#N#BM"
 */
consteval bool test_pure_ct_format_3() {
    using dig16 = dig_t<16>;
    
    // "dig#10#B16"
    constexpr std::array<char, 10> str1 = {'d', 'i', 'g', '#', '1', '0', '#', 'B', '1', '6'};
    constexpr auto result1 = dig16::parse_impl_pure_ct(str1, 16);
    if (!result1 || *result1 != 10) return false;
    
    // "dig#255#B16" → normaliza a 15 (255 % 16)
    constexpr std::array<char, 11> str2 = {'d', 'i', 'g', '#', '2', '5', '5', '#', 'B', '1', '6'};
    constexpr auto result2 = dig16::parse_impl_pure_ct(str2, 16);
    if (!result2 || *result2 != 15) return false;
    
    return true;
}

/**
 * @brief Test formato 4: "dig[N]BM"
 */
consteval bool test_pure_ct_format_4() {
    using dig256 = dig_t<256>;
    
    // "dig[100]B256"
    constexpr std::array<char, 12> str1 = {'d', 'i', 'g', '[', '1', '0', '0', ']', 'B', '2', '5', '6'};
    constexpr auto result1 = dig256::parse_impl_pure_ct(str1, 256);
    if (!result1 || *result1 != 100) return false;
    
    // "dig[999]B256" → normaliza a 231 (999 % 256)
    constexpr std::array<char, 12> str2 = {'d', 'i', 'g', '[', '9', '9', '9', ']', 'B', '2', '5', '6'};
    constexpr auto result2 = dig256::parse_impl_pure_ct(str2, 256);
    if (!result2 || *result2 != 231) return false;
    
    return true;
}

/**
 * @brief Test equivalencia entre formatos
 */
consteval bool test_pure_ct_equivalence() {
    using dig10 = dig_t<10>;
    
    // "d[7]B10"
    constexpr std::array<char, 7> fmt1 = {'d', '[', '7', ']', 'B', '1', '0'};
    constexpr auto r1 = dig10::parse_impl_pure_ct(fmt1, 10);
    
    // "d#7#B10"
    constexpr std::array<char, 7> fmt2 = {'d', '#', '7', '#', 'B', '1', '0'};
    constexpr auto r2 = dig10::parse_impl_pure_ct(fmt2, 10);
    
    // "dig#7#B10"
    constexpr std::array<char, 9> fmt3 = {'d', 'i', 'g', '#', '7', '#', 'B', '1', '0'};
    constexpr auto r3 = dig10::parse_impl_pure_ct(fmt3, 10);
    
    // "dig[7]B10"
    constexpr std::array<char, 9> fmt4 = {'d', 'i', 'g', '[', '7', ']', 'B', '1', '0'};
    constexpr auto r4 = dig10::parse_impl_pure_ct(fmt4, 10);
    
    // Todos deben dar 7
    if (!r1 || *r1 != 7) return false;
    if (!r2 || *r2 != 7) return false;
    if (!r3 || *r3 != 7) return false;
    if (!r4 || *r4 != 7) return false;
    
    return true;
}

/**
 * @brief Test normalización automática
 */
consteval bool test_pure_ct_normalization() {
    using dig10 = dig_t<10>;
    
    // Valores que requieren normalización
    constexpr std::array<char, 8> str1 = {'d', '[', '1', '0', ']', 'B', '1', '0'};  // 10 % 10 = 0
    constexpr auto r1 = dig10::parse_impl_pure_ct(str1, 10);
    if (!r1 || *r1 != 0) return false;
    
    constexpr std::array<char, 8> str2 = {'d', '[', '2', '3', ']', 'B', '1', '0'};  // 23 % 10 = 3
    constexpr auto r2 = dig10::parse_impl_pure_ct(str2, 10);
    if (!r2 || *r2 != 3) return false;
    
    constexpr std::array<char, 9> str3 = {'d', '[', '1', '0', '0', ']', 'B', '1', '0'};  // 100 % 10 = 0
    constexpr auto r3 = dig10::parse_impl_pure_ct(str3, 10);
    if (!r3 || *r3 != 0) return false;
    
    return true;
}

/**
 * @brief Test errores en parse_impl_pure_ct
 */
consteval bool test_pure_ct_errors() {
    using dig10 = dig_t<10>;
    
    // String muy corto
    constexpr std::array<char, 3> str1 = {'d', '[', ']'};
    constexpr auto r1 = dig10::parse_impl_pure_ct(str1, 10);
    if (r1.has_value()) return false;  // Debe fallar
    
    // Base incorrecta: "d[5]B16" pero esperamos B10
    constexpr std::array<char, 7> str2 = {'d', '[', '5', ']', 'B', '1', '6'};
    constexpr auto r2 = dig10::parse_impl_pure_ct(str2, 10);
    if (r2.has_value()) return false;  // Debe fallar (base mismatch)
    
    // Prefijo inválido: "x[5]B10"
    constexpr std::array<char, 7> str3 = {'x', '[', '5', ']', 'B', '1', '0'};
    constexpr auto r3 = dig10::parse_impl_pure_ct(str3, 10);
    if (r3.has_value()) return false;  // Debe fallar
    
    return true;
}

// ============================================================================
// TESTS DE FSMs INDIVIDUALES
// ============================================================================

/**
 * @brief Test parse_prefix_fsm_ct
 */
consteval bool test_prefix_fsm_ct() {
    using dig10 = dig_t<10>;
    
    // "d[5]B10"
    constexpr std::array<char, 7> str1 = {'d', '[', '5', ']', 'B', '1', '0'};
    constexpr auto r1 = dig10::parse_prefix_fsm_ct(str1, 7);
    if (!r1 || r1->delimiter_open != '[' || r1->delimiter_close != ']' || r1->next_pos != 2) {
        return false;
    }
    
    // "d#7#B10"
    constexpr std::array<char, 7> str2 = {'d', '#', '7', '#', 'B', '1', '0'};
    constexpr auto r2 = dig10::parse_prefix_fsm_ct(str2, 7);
    if (!r2 || r2->delimiter_open != '#' || r2->delimiter_close != '#' || r2->next_pos != 2) {
        return false;
    }
    
    // "dig#3#B10"
    constexpr std::array<char, 9> str3 = {'d', 'i', 'g', '#', '3', '#', 'B', '1', '0'};
    constexpr auto r3 = dig10::parse_prefix_fsm_ct(str3, 9);
    if (!r3 || r3->delimiter_open != '#' || r3->delimiter_close != '#' || r3->next_pos != 4) {
        return false;
    }
    
    // "dig[8]B10"
    constexpr std::array<char, 9> str4 = {'d', 'i', 'g', '[', '8', ']', 'B', '1', '0'};
    constexpr auto r4 = dig10::parse_prefix_fsm_ct(str4, 9);
    if (!r4 || r4->delimiter_open != '[' || r4->delimiter_close != ']' || r4->next_pos != 4) {
        return false;
    }
    
    return true;
}

/**
 * @brief Test parse_number_fsm_ct
 */
consteval bool test_number_fsm_ct() {
    using dig10 = dig_t<10>;
    
    // "[42]" → parsear desde pos 0, delim_close = ']'
    constexpr std::array<char, 4> str1 = {'4', '2', ']', 'X'};
    constexpr auto r1 = dig10::parse_number_fsm_ct(str1, 4, 0, ']');
    if (!r1 || r1->value != 42 || r1->next_pos != 3) return false;
    
    // "#255#" → parsear desde pos 0, delim_close = '#'
    constexpr std::array<char, 5> str2 = {'2', '5', '5', '#', 'X'};
    constexpr auto r2 = dig10::parse_number_fsm_ct(str2, 5, 0, '#');
    if (!r2 || r2->value != 255 || r2->next_pos != 4) return false;
    
    return true;
}

/**
 * @brief Test parse_base_fsm_ct
 */
consteval bool test_base_fsm_ct() {
    using dig10 = dig_t<10>;
    
    // "B10"
    constexpr std::array<char, 3> str1 = {'B', '1', '0'};
    constexpr auto r1 = dig10::parse_base_fsm_ct(str1, 3, 0, 10);
    if (!r1 || r1->base_value != 10) return false;
    
    // "B256"
    constexpr std::array<char, 4> str2 = {'B', '2', '5', '6'};
    constexpr auto r2 = dig10::parse_base_fsm_ct(str2, 4, 0, 256);
    if (!r2 || r2->base_value != 256) return false;
    
    // Base mismatch: "B16" pero esperamos 10
    constexpr std::array<char, 3> str3 = {'B', '1', '6'};
    constexpr auto r3 = dig10::parse_base_fsm_ct(str3, 3, 0, 10);
    if (r3.has_value()) return false;  // Debe fallar
    
    return true;
}

// ============================================================================
// RUNNER
// ============================================================================

int main() {
    std::cout << "=== Tests de parse_impl_pure_ct (consteval) ===" << std::endl;
    
    // Tests de parse_impl_pure_ct
    static_assert(test_pure_ct_format_1(), "FAIL: test_pure_ct_format_1");
    std::cout << "✓ test_pure_ct_format_1" << std::endl;
    
    static_assert(test_pure_ct_format_2(), "FAIL: test_pure_ct_format_2");
    std::cout << "✓ test_pure_ct_format_2" << std::endl;
    
    static_assert(test_pure_ct_format_3(), "FAIL: test_pure_ct_format_3");
    std::cout << "✓ test_pure_ct_format_3" << std::endl;
    
    static_assert(test_pure_ct_format_4(), "FAIL: test_pure_ct_format_4");
    std::cout << "✓ test_pure_ct_format_4" << std::endl;
    
    static_assert(test_pure_ct_equivalence(), "FAIL: test_pure_ct_equivalence");
    std::cout << "✓ test_pure_ct_equivalence" << std::endl;
    
    static_assert(test_pure_ct_normalization(), "FAIL: test_pure_ct_normalization");
    std::cout << "✓ test_pure_ct_normalization" << std::endl;
    
    static_assert(test_pure_ct_errors(), "FAIL: test_pure_ct_errors");
    std::cout << "✓ test_pure_ct_errors" << std::endl;
    
    std::cout << "\n=== Tests de FSMs consteval individuales ===" << std::endl;
    
    static_assert(test_prefix_fsm_ct(), "FAIL: test_prefix_fsm_ct");
    std::cout << "✓ test_prefix_fsm_ct" << std::endl;
    
    static_assert(test_number_fsm_ct(), "FAIL: test_number_fsm_ct");
    std::cout << "✓ test_number_fsm_ct" << std::endl;
    
    static_assert(test_base_fsm_ct(), "FAIL: test_base_fsm_ct");
    std::cout << "✓ test_base_fsm_ct" << std::endl;
    
    std::cout << "\n=== TODOS LOS TESTS PASARON ===" << std::endl;
    return 0;
}
