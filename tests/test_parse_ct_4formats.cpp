/**
 * @file test_parse_ct_4formats.cpp
 * @brief Test de parse_impl_ct con los 4 formatos: d[N]BM, d#N#BM, dig#N#BM, dig[N]BM
 *
 * OBJETIVO: Verificar que parse_impl_ct soporta los 4 formatos correctamente
 */

#include <core/dig_t.hpp>
#include <iostream>

using namespace std;
using namespace NumRepr;

void test_format_1_brackets_short() {
    cout << "Testing Format 1: d[N]BM (short + brackets)...\n";
    
    dig_t<10> d1("d[5]B10");
    if (d1.get() != 5) throw runtime_error("d[5]B10 failed");
    cout << "  ✓ d[5]B10 = " << static_cast<int>(d1.get()) << "\n";
    
    dig_t<16> d2("d[15]B16");
    if (d2.get() != 15) throw runtime_error("d[15]B16 failed");
    cout << "  ✓ d[15]B16 = " << static_cast<int>(d2.get()) << "\n";
    
    dig_t<256> d3("d[255]B256");
    if (d3.get() != 255) throw runtime_error("d[255]B256 failed");
    cout << "  ✓ d[255]B256 = " << static_cast<int>(d3.get()) << "\n";
    
    cout << "  ✅ Format 1: PASSED\n\n";
}

void test_format_2_hashes_short() {
    cout << "Testing Format 2: d#N#BM (short + hashes) [NEW]...\n";
    
    dig_t<10> d1("d#5#B10");
    if (d1.get() != 5) throw runtime_error("d#5#B10 failed");
    cout << "  ✓ d#5#B10 = " << static_cast<int>(d1.get()) << "\n";
    
    dig_t<16> d2("d#15#B16");
    if (d2.get() != 15) throw runtime_error("d#15#B16 failed");
    cout << "  ✓ d#15#B16 = " << static_cast<int>(d2.get()) << "\n";
    
    dig_t<256> d3("d#255#B256");
    if (d3.get() != 255) throw runtime_error("d#255#B256 failed");
    cout << "  ✓ d#255#B256 = " << static_cast<int>(d3.get()) << "\n";
    
    cout << "  ✅ Format 2: PASSED\n\n";
}

void test_format_3_hashes_long() {
    cout << "Testing Format 3: dig#N#BM (long + hashes)...\n";
    
    dig_t<10> d1("dig#5#B10");
    if (d1.get() != 5) throw runtime_error("dig#5#B10 failed");
    cout << "  ✓ dig#5#B10 = " << static_cast<int>(d1.get()) << "\n";
    
    dig_t<16> d2("dig#15#B16");
    if (d2.get() != 15) throw runtime_error("dig#15#B16 failed");
    cout << "  ✓ dig#15#B16 = " << static_cast<int>(d2.get()) << "\n";
    
    dig_t<256> d3("dig#255#B256");
    if (d3.get() != 255) throw runtime_error("dig#255#B256 failed");
    cout << "  ✓ dig#255#B256 = " << static_cast<int>(d3.get()) << "\n";
    
    cout << "  ✅ Format 3: PASSED\n\n";
}

void test_format_4_brackets_long() {
    cout << "Testing Format 4: dig[N]BM (long + brackets) [NEW]...\n";
    
    dig_t<10> d1("dig[5]B10");
    if (d1.get() != 5) throw runtime_error("dig[5]B10 failed");
    cout << "  ✓ dig[5]B10 = " << static_cast<int>(d1.get()) << "\n";
    
    dig_t<16> d2("dig[15]B16");
    if (d2.get() != 15) throw runtime_error("dig[15]B16 failed");
    cout << "  ✓ dig[15]B16 = " << static_cast<int>(d2.get()) << "\n";
    
    dig_t<256> d3("dig[255]B256");
    if (d3.get() != 255) throw runtime_error("dig[255]B256 failed");
    cout << "  ✓ dig[255]B256 = " << static_cast<int>(d3.get()) << "\n";
    
    cout << "  ✅ Format 4: PASSED\n\n";
}

void test_equivalence() {
    cout << "Testing format equivalence...\n";
    
    dig_t<10> d1("d[7]B10");
    dig_t<10> d2("d#7#B10");
    dig_t<10> d3("dig#7#B10");
    dig_t<10> d4("dig[7]B10");
    
    if (d1.get() != 7 || d2.get() != 7 || d3.get() != 7 || d4.get() != 7) {
        throw runtime_error("Formats produced different values");
    }
    
    cout << "  ✓ All 4 formats produce same value: 7\n";
    cout << "  ✅ Equivalence: PASSED\n\n";
}

void test_normalization() {
    cout << "Testing automatic normalization...\n";
    
    dig_t<10> d1("d[42]B10");
    if (d1.get() != 2) {  // 42 % 10 = 2
        throw runtime_error("Normalization failed for d[42]B10");
    }
    cout << "  ✓ d[42]B10 normalized to " << static_cast<int>(d1.get()) << "\n";
    
    dig_t<16> d2("d#100#B16");
    if (d2.get() != 4) {  // 100 % 16 = 4
        throw runtime_error("Normalization failed for d#100#B16");
    }
    cout << "  ✓ d#100#B16 normalized to " << static_cast<int>(d2.get()) << "\n";
    
    cout << "  ✅ Normalization: PASSED\n\n";
}

int main() {
    try {
        cout << "========================================\n";
        cout << "TEST: parse_impl_ct - 4 FORMATS\n";
        cout << "========================================\n\n";
        
        test_format_1_brackets_short();
        test_format_2_hashes_short();
        test_format_3_hashes_long();
        test_format_4_brackets_long();
        test_equivalence();
        test_normalization();
        
        cout << "========================================\n";
        cout << "✅✅✅ ALL TESTS PASSED ✅✅✅\n";
        cout << "========================================\n";
        cout << "\nSUMMARY:\n";
        cout << "  Format 1 (d[N]BM):   ✅ WORKING\n";
        cout << "  Format 2 (d#N#BM):   ✅ WORKING (NEW)\n";
        cout << "  Format 3 (dig#N#BM): ✅ WORKING\n";
        cout << "  Format 4 (dig[N]BM): ✅ WORKING (NEW)\n";
        
        return 0;
    }
    catch (const exception& e) {
        cerr << "❌ TEST FAILED: " << e.what() << endl;
        return 1;
    }
}
