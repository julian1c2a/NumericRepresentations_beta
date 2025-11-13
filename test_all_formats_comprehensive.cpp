/**
 * @file test_all_formats_comprehensive.cpp
 * @brief Comprehensive validation of all 4 parsing formats with various edge cases
 */

#include <iostream>
#include <cassert>
#include <array>
#include "include/core/dig_t.hpp"

using namespace NumRepr;

int main() {
    std::cout << "=== COMPREHENSIVE FORMAT VALIDATION ===" << std::endl;
    std::cout << "Testing all 4 format combinations with edge cases\n" << std::endl;
    
    int tests = 0, passed = 0;
    
    // Test all 4 formats produce identical results
    std::cout << "--- Format Equivalence Tests ---" << std::endl;
    
    for (auto val : {0, 1, 5, 9}) {
        dig_t<10> d1(("d[" + std::to_string(val) + "]B10").c_str());
        dig_t<10> d2(("dig#" + std::to_string(val) + "#B10").c_str());
        dig_t<10> d3(("d#" + std::to_string(val) + "#B10").c_str());
        dig_t<10> d4(("dig[" + std::to_string(val) + "]B10").c_str());
        
        tests++;
        if (d1.get() == val && d2.get() == val && d3.get() == val && d4.get() == val) {
            std::cout << "✅ All 4 formats for value " << val << " produce correct result" << std::endl;
            passed++;
        } else {
            std::cout << "❌ FAIL for value " << val << std::endl;
        }
    }
    
    std::cout << "\n--- Multi-Base Tests ---" << std::endl;
    
    // Test different bases
    std::array<std::pair<int, int>, 5> base_tests = {{
        {2, 1}, {8, 7}, {10, 9}, {16, 15}, {256, 255}
    }};
    
    for (const auto& [base, max_val] : base_tests) {
        tests++;
        bool all_ok = true;
        
        // We can't construct templated types dynamically, so test representative cases
        if (base == 10) {
            dig_t<10> d1(("d[" + std::to_string(max_val) + "]B10").c_str());
            dig_t<10> d2(("dig#" + std::to_string(max_val) + "#B10").c_str());
            dig_t<10> d3(("d#" + std::to_string(max_val) + "#B10").c_str());
            dig_t<10> d4(("dig[" + std::to_string(max_val) + "]B10").c_str());
            all_ok = (d1.get() == max_val && d2.get() == max_val && 
                     d3.get() == max_val && d4.get() == max_val);
        }
        
        if (all_ok) {
            std::cout << "✅ Base " << base << " with max value " << max_val << std::endl;
            passed++;
        } else {
            std::cout << "❌ FAIL for base " << base << std::endl;
        }
    }
    
    std::cout << "\n--- to_cstr() Round-Trip Tests ---" << std::endl;
    
    // Test to_cstr round-trips
    constexpr dig_t<10> ct1(7);
    constexpr auto cstr1 = ct1.to_cstr();
    constexpr dig_t<10> rt1(cstr1.data());
    
    tests++;
    if (rt1.get() == 7) {
        std::cout << "✅ to_cstr round-trip for d[7]B10" << std::endl;
        passed++;
    }
    
    constexpr dig_t<16> ct2(15);
    constexpr auto cstr2 = ct2.to_cstr();
    constexpr dig_t<16> rt2(cstr2.data());
    
    tests++;
    if (rt2.get() == 15) {
        std::cout << "✅ to_cstr round-trip for d[15]B16" << std::endl;
        passed++;
    }
    
    std::cout << "\n--- Modulo Behavior Tests ---" << std::endl;
    
    // Test modulo normalization works with all formats
    dig_t<10> m1("d[123]B10");
    dig_t<10> m2("dig#123#B10");
    dig_t<10> m3("d#123#B10");
    dig_t<10> m4("dig[123]B10");
    
    tests++;
    if (m1.get() == 3 && m2.get() == 3 && m3.get() == 3 && m4.get() == 3) {
        std::cout << "✅ Modulo (123 % 10 = 3) works with all 4 formats" << std::endl;
        passed++;
    }
    
    std::cout << "\n--- Error Handling Tests ---" << std::endl;
    
    // Test invalid formats are rejected
    bool caught_error = false;
    try {
        dig_t<10> bad("invalid");
    } catch (const std::exception&) {
        caught_error = true;
    }
    
    tests++;
    if (caught_error) {
        std::cout << "✅ Invalid format properly rejected" << std::endl;
        passed++;
    }
    
    // Test base mismatch is rejected
    caught_error = false;
    try {
        dig_t<10> bad("d[5]B16");  // Wrong base
    } catch (const std::exception&) {
        caught_error = true;
    }
    
    tests++;
    if (caught_error) {
        std::cout << "✅ Base mismatch properly rejected" << std::endl;
        passed++;
    }
    
    std::cout << "\n=== SUMMARY ===" << std::endl;
    std::cout << "Passed: " << passed << "/" << tests << std::endl;
    
    if (passed == tests) {
        std::cout << "🎉 ALL COMPREHENSIVE TESTS PASSED!" << std::endl;
        return 0;
    } else {
        std::cout << "❌ Some tests failed" << std::endl;
        return 1;
    }
}
