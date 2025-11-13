/**
 * @file test_parsing_serialization_improvements.cpp
 * @brief Test suite for dig_t parsing and serialization improvements
 * 
 * Tests the improvements described in TODO at lines 980-1003 of dig_t.hpp:
 * 1. to_cstr consteval function for compile-time C-string serialization
 * 2. Complete parser support for all 4 format combinations
 * 
 * Format specification:
 *   format ::= prefix separators number "B" base
 *   prefix ::= "d" | "dig"
 *   separators ::= "[" ... "]" | "#" ... "#"
 * 
 * All 4 combinations:
 *   - "d[N]BM"     (strict format - currently supported)
 *   - "dig#N#BM"   (legacy format - currently supported)
 *   - "d#N#BM"     (prefix d with # separators - NEEDS IMPLEMENTATION)
 *   - "dig[N]BM"   (prefix dig with [ ] separators - NEEDS IMPLEMENTATION)
 */

#include <iostream>
#include <cassert>
#include <cstring>
#include <sstream>
#include "include/core/dig_t.hpp"

using namespace NumRepr;

// Test counter
int test_count = 0;
int passed_tests = 0;

void test_case(const std::string& name, bool condition) {
    test_count++;
    std::cout << "[" << test_count << "] " << name << ": ";
    if (condition) {
        std::cout << "✅ PASS" << std::endl;
        passed_tests++;
    } else {
        std::cout << "❌ FAIL" << std::endl;
    }
}

void test_existing_parser_formats() {
    std::cout << "\n=== EXISTING PARSER FORMATS (Should Pass) ===" << std::endl;
    
    // Test 1: Strict format "d[N]BM"
    dig_t<10> d1("d[7]B10");
    test_case("Parse d[7]B10", d1.get() == 7);
    
    // Test 2: Legacy format "dig#N#BM"
    dig_t<10> d2("dig#7#B10");
    test_case("Parse dig#7#B10", d2.get() == 7);
    
    // Test 3: Different bases
    dig_t<16> d3("d[15]B16");
    test_case("Parse d[15]B16 (hex)", d3.get() == 15);
    
    dig_t<16> d4("dig#15#B16");
    test_case("Parse dig#15#B16 (hex)", d4.get() == 15);
    
    // Test 4: Modulo behavior
    dig_t<10> d5("d[23]B10");
    test_case("Parse d[23]B10 with modulo", d5.get() == 3);
    
    dig_t<10> d6("dig#23#B10");
    test_case("Parse dig#23#B10 with modulo", d6.get() == 3);
}

void test_new_parser_formats() {
    std::cout << "\n=== NEW PARSER FORMATS (Needs Implementation) ===" << std::endl;
    
    try {
        // Test 7: New format "d#N#BM"
        dig_t<10> d7("d#7#B10");
        test_case("Parse d#7#B10 (new format)", d7.get() == 7);
    } catch (const std::exception& e) {
        std::cout << "[EXPECTED FAIL] d#7#B10 not yet implemented: " << e.what() << std::endl;
        test_case("Parse d#7#B10 (new format)", false);
    }
    
    try {
        // Test 8: New format "dig[N]BM"
        dig_t<10> d8("dig[7]B10");
        test_case("Parse dig[7]B10 (new format)", d8.get() == 7);
    } catch (const std::exception& e) {
        std::cout << "[EXPECTED FAIL] dig[7]B10 not yet implemented: " << e.what() << std::endl;
        test_case("Parse dig[7]B10 (new format)", false);
    }
    
    try {
        // Test 9: All 4 formats with same value
        dig_t<16> d9a("d[15]B16");
        dig_t<16> d9b("dig#15#B16");
        dig_t<16> d9c("d#15#B16");
        dig_t<16> d9d("dig[15]B16");
        test_case("All 4 formats produce same result", 
                  d9a.get() == d9b.get() && 
                  d9b.get() == d9c.get() && 
                  d9c.get() == d9d.get());
    } catch (const std::exception& e) {
        std::cout << "[EXPECTED FAIL] Not all formats implemented: " << e.what() << std::endl;
        test_case("All 4 formats produce same result", false);
    }
}

void test_constexpr_parsing() {
    std::cout << "\n=== CONSTEXPR PARSING ===" << std::endl;
    
    // Test 10: Compile-time parsing with existing formats
    constexpr dig_t<10> ct1("d[5]B10");
    test_case("Constexpr d[5]B10", ct1.get() == 5);
    
    constexpr dig_t<16> ct2("d[10]B16");
    test_case("Constexpr d[10]B16", ct2.get() == 10);
    
    // Test with different bases at compile time
    constexpr dig_t<2> ct_bin("d[1]B2");
    test_case("Constexpr binary d[1]B2", ct_bin.get() == 1);
}

void test_to_cstr_function() {
    std::cout << "\n=== TO_CSTR CONSTEVAL FUNCTION (Needs Implementation) ===" << std::endl;
    
    // Note: to_cstr doesn't exist yet, this is what we want to test after implementation
    std::cout << "[INFO] to_cstr() function needs to be implemented" << std::endl;
    std::cout << "       Expected signature: static consteval const char* to_cstr() const;" << std::endl;
    std::cout << "       Expected output format: \"d[N]BM\" where N=value, M=base" << std::endl;
    
    // When implemented, tests should look like:
    /*
    constexpr dig_t<10> d(7);
    constexpr auto str = d.to_cstr();
    test_case("to_cstr() returns correct format", std::strcmp(str, "d[7]B10") == 0);
    
    // Verify it's compile-time evaluable
    constexpr dig_t<16> hex(15);
    constexpr auto hex_str = hex.to_cstr();
    test_case("to_cstr() works at compile time", std::strcmp(hex_str, "d[15]B16") == 0);
    
    // Test round-trip: to_cstr -> from_cstr
    constexpr dig_t<10> original(8);
    constexpr auto cstr = original.to_cstr();
    constexpr dig_t<10> restored(cstr);
    test_case("Round-trip to_cstr -> from_cstr", original.get() == restored.get());
    */
    
    test_case("to_cstr() implemented", false); // Will pass when implemented
}

void test_existing_to_string() {
    std::cout << "\n=== EXISTING TO_STRING (Should Pass) ===" << std::endl;
    
    dig_t<10> d1(7);
    std::string str1 = d1.to_string();
    test_case("to_string() returns string", !str1.empty());
    test_case("to_string() has correct format prefix", str1.find("d[") == 0);
    test_case("to_string() has correct format suffix", str1.find("]B10") != std::string::npos);
    
    dig_t<16> d2(15);
    std::string str2 = d2.to_string();
    test_case("to_string() works for base 16", str2.find("B16") != std::string::npos);
}

void test_error_handling() {
    std::cout << "\n=== ERROR HANDLING ===" << std::endl;
    
    // Test invalid format
    try {
        dig_t<10> bad("invalid");
        test_case("Reject invalid format", false);
    } catch (const std::exception&) {
        test_case("Reject invalid format", true);
    }
    
    // Test wrong base
    try {
        dig_t<10> wrong_base("d[5]B16");
        test_case("Reject wrong base", false);
    } catch (const std::exception&) {
        test_case("Reject wrong base", true);
    }
    
    // Test missing parts
    try {
        dig_t<10> incomplete("d[5]");
        test_case("Reject incomplete format", false);
    } catch (const std::exception&) {
        test_case("Reject incomplete format", true);
    }
}

void test_stream_operations() {
    std::cout << "\n=== STREAM OPERATIONS ===" << std::endl;
    
    // Test output stream
    dig_t<10> d1(7);
    std::ostringstream oss;
    oss << d1;
    std::string output = oss.str();
    test_case("operator<< produces output", !output.empty());
    test_case("operator<< uses strict format", output.find("d[7]B10") != std::string::npos);
    
    // Test input stream with strict format
    std::istringstream iss1("d[5]B10");
    dig_t<10> d2;
    iss1 >> d2;
    test_case("operator>> reads strict format", d2.get() == 5);
    
    // Test input stream with legacy format
    std::istringstream iss2("dig#5#B10");
    dig_t<10> d3;
    iss2 >> d3;
    test_case("operator>> reads legacy format", d3.get() == 5);
}

void test_multi_base_compatibility() {
    std::cout << "\n=== MULTI-BASE COMPATIBILITY ===" << std::endl;
    
    // Test various bases with both formats
    dig_t<2> bin1("d[1]B2");
    dig_t<2> bin2("dig#1#B2");
    test_case("Base 2: both formats", bin1.get() == bin2.get());
    
    dig_t<8> oct1("d[7]B8");
    dig_t<8> oct2("dig#7#B8");
    test_case("Base 8: both formats", oct1.get() == oct2.get());
    
    dig_t<16> hex1("d[15]B16");
    dig_t<16> hex2("dig#15#B16");
    test_case("Base 16: both formats", hex1.get() == hex2.get());
    
    dig_t<256> large1("d[255]B256");
    dig_t<256> large2("dig#255#B256");
    test_case("Base 256: both formats", large1.get() == large2.get());
}

void print_summary() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "TEST SUMMARY" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "Total tests: " << test_count << std::endl;
    std::cout << "Passed: " << passed_tests << " ✅" << std::endl;
    std::cout << "Failed: " << (test_count - passed_tests) << " ❌" << std::endl;
    
    if (passed_tests == test_count) {
        std::cout << "\n🎉 ALL TESTS PASSED! 🎉" << std::endl;
    } else {
        std::cout << "\n⚠️  Some tests failed (expected during development)" << std::endl;
    }
    std::cout << std::string(60, '=') << std::endl;
}

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "  dig_t PARSING & SERIALIZATION IMPROVEMENTS TEST" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "\nTesting TODO items from dig_t.hpp lines 980-1003\n" << std::endl;
    
    test_existing_parser_formats();
    test_new_parser_formats();
    test_constexpr_parsing();
    test_to_cstr_function();
    test_existing_to_string();
    test_error_handling();
    test_stream_operations();
    test_multi_base_compatibility();
    
    print_summary();
    
    return (passed_tests == test_count) ? 0 : 1;
}
