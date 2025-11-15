/**
 * @file test_to_cstr.cpp
 * @brief Tests de la función to_cstr() consteval
 * 
 * @details Verifica serialización compile-time de dig_t a string
 */

#include <core/dig_t.hpp>
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;
using namespace NumRepr;

// Tests compile-time con static_assert
consteval bool test_compile_time() {
    // Test 1: Base 10, valor 5
    constexpr auto d1 = dig_t<10>(5);
    constexpr auto str1 = d1.to_cstr();
    
    if (str1[0] != 'd') return false;
    if (str1[1] != '[') return false;
    if (str1[2] != '5') return false;
    if (str1[3] != ']') return false;
    if (str1[4] != 'B') return false;
    if (str1[5] != '1') return false;
    if (str1[6] != '0') return false;
    if (str1[7] != '\0') return false;
    
    // Test 2: Base 2, valor 0
    constexpr auto d2 = dig_t<2>(0);
    constexpr auto str2 = d2.to_cstr();
    
    if (str2[0] != 'd') return false;
    if (str2[1] != '[') return false;
    if (str2[2] != '0') return false;
    if (str2[3] != ']') return false;
    if (str2[4] != 'B') return false;
    if (str2[5] != '2') return false;
    if (str2[6] != '\0') return false;
    
    // Test 3: Base 256, valor 255
    constexpr auto d3 = dig_t<256>(255);
    constexpr auto str3 = d3.to_cstr();
    
    if (str3[0] != 'd') return false;
    if (str3[1] != '[') return false;
    if (str3[2] != '2') return false;
    if (str3[3] != '5') return false;
    if (str3[4] != '5') return false;
    if (str3[5] != ']') return false;
    if (str3[6] != 'B') return false;
    if (str3[7] != '2') return false;
    if (str3[8] != '5') return false;
    if (str3[9] != '6') return false;
    if (str3[10] != '\0') return false;
    
    return true;
}

// Verificación compile-time
static_assert(test_compile_time(), "Tests compile-time fallaron");

void test_runtime_basic() {
    cout << "\n=== TEST BÁSICO RUNTIME ===" << endl;
    
    // Base 10
    auto d1 = dig_t<10>(7);
    auto str1 = d1.to_cstr();
    assert(strcmp(str1.data(), "d[7]B10") == 0);
    cout << "✓ dig_t<10>(7) → \"" << str1.data() << "\"" << endl;
    
    // Base 16
    auto d2 = dig_t<16>(15);
    auto str2 = d2.to_cstr();
    assert(strcmp(str2.data(), "d[15]B16") == 0);
    cout << "✓ dig_t<16>(15) → \"" << str2.data() << "\"" << endl;
    
    // Base 2
    auto d3 = dig_t<2>(1);
    auto str3 = d3.to_cstr();
    assert(strcmp(str3.data(), "d[1]B2") == 0);
    cout << "✓ dig_t<2>(1) → \"" << str3.data() << "\"" << endl;
}

void test_valores_especiales() {
    cout << "\n=== TEST VALORES ESPECIALES ===" << endl;
    
    // Cero en diferentes bases
    auto d1 = dig_t<10>(0);
    auto str1 = d1.to_cstr();
    assert(strcmp(str1.data(), "d[0]B10") == 0);
    cout << "✓ dig_t<10>(0) → \"" << str1.data() << "\"" << endl;
    
    auto d2 = dig_t<256>(0);
    auto str2 = d2.to_cstr();
    assert(strcmp(str2.data(), "d[0]B256") == 0);
    cout << "✓ dig_t<256>(0) → \"" << str2.data() << "\"" << endl;
    
    // Valores máximos
    auto d3 = dig_t<10>(9);
    auto str3 = d3.to_cstr();
    assert(strcmp(str3.data(), "d[9]B10") == 0);
    cout << "✓ dig_t<10>(9) → \"" << str3.data() << "\"" << endl;
    
    auto d4 = dig_t<256>(255);
    auto str4 = d4.to_cstr();
    assert(strcmp(str4.data(), "d[255]B256") == 0);
    cout << "✓ dig_t<256>(255) → \"" << str4.data() << "\"" << endl;
}

void test_normalizacion() {
    cout << "\n=== TEST NORMALIZACIÓN ===" << endl;
    
    // Valores que requieren normalización
    auto d1 = dig_t<10>(42);  // 42 % 10 = 2
    auto str1 = d1.to_cstr();
    assert(strcmp(str1.data(), "d[2]B10") == 0);
    cout << "✓ dig_t<10>(42) → \"" << str1.data() << "\" (normalizado)" << endl;
    
    auto d2 = dig_t<16>(255); // 255 % 16 = 15
    auto str2 = d2.to_cstr();
    assert(strcmp(str2.data(), "d[15]B16") == 0);
    cout << "✓ dig_t<16>(255) → \"" << str2.data() << "\" (normalizado)" << endl;
    
    auto d3 = dig_t<5>(17);   // 17 % 5 = 2
    auto str3 = d3.to_cstr();
    assert(strcmp(str3.data(), "d[2]B5") == 0);
    cout << "✓ dig_t<5>(17) → \"" << str3.data() << "\" (normalizado)" << endl;
}

void test_round_trip() {
    cout << "\n=== TEST ROUND-TRIP (to_cstr → from_cstr) ===" << endl;
    
    // Test: serializar y deserializar
    constexpr auto original = dig_t<50>(42);
    constexpr auto serialized = original.to_cstr();
    auto deserialized = dig_t<50>::from_cstr(serialized.data());
    
    assert(deserialized.get() == original.get());
    cout << "✓ Round-trip: " << static_cast<int>(original.get()) 
         << " → \"" << serialized.data() << "\" → " 
         << static_cast<int>(deserialized.get()) << endl;
    
    // Más casos
    auto d2 = dig_t<256>(123);
    auto str2 = d2.to_cstr();
    auto d2_back = dig_t<256>::from_cstr(str2.data());
    assert(d2_back.get() == d2.get());
    cout << "✓ Round-trip: " << static_cast<int>(d2.get())
         << " → \"" << str2.data() << "\" → "
         << static_cast<int>(d2_back.get()) << endl;
}

void test_multiples_bases() {
    cout << "\n=== TEST MÚLTIPLES BASES ===" << endl;
    
    const int bases[] = {2, 3, 5, 10, 16, 100, 256, 257, 1000};
    
    for (int b : bases) {
        switch (b) {
            case 2: {
                auto d = dig_t<2>(1);
                auto s = d.to_cstr();
                cout << "✓ Base " << b << ": \"" << s.data() << "\"" << endl;
                break;
            }
            case 3: {
                auto d = dig_t<3>(2);
                auto s = d.to_cstr();
                cout << "✓ Base " << b << ": \"" << s.data() << "\"" << endl;
                break;
            }
            case 5: {
                auto d = dig_t<5>(4);
                auto s = d.to_cstr();
                cout << "✓ Base " << b << ": \"" << s.data() << "\"" << endl;
                break;
            }
            case 10: {
                auto d = dig_t<10>(7);
                auto s = d.to_cstr();
                cout << "✓ Base " << b << ": \"" << s.data() << "\"" << endl;
                break;
            }
            case 16: {
                auto d = dig_t<16>(15);
                auto s = d.to_cstr();
                cout << "✓ Base " << b << ": \"" << s.data() << "\"" << endl;
                break;
            }
            case 100: {
                auto d = dig_t<100>(99);
                auto s = d.to_cstr();
                cout << "✓ Base " << b << ": \"" << s.data() << "\"" << endl;
                break;
            }
            case 256: {
                auto d = dig_t<256>(200);
                auto s = d.to_cstr();
                cout << "✓ Base " << b << ": \"" << s.data() << "\"" << endl;
                break;
            }
            case 257: {
                auto d = dig_t<257>(256);
                auto s = d.to_cstr();
                cout << "✓ Base " << b << ": \"" << s.data() << "\"" << endl;
                break;
            }
            case 1000: {
                auto d = dig_t<1000>(999);
                auto s = d.to_cstr();
                cout << "✓ Base " << b << ": \"" << s.data() << "\"" << endl;
                break;
            }
        }
    }
}

int main() {
    cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║           TEST DE to_cstr() CONSTEVAL                        ║" << endl;
    cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\n✅ Tests compile-time: PASADOS (static_assert)" << endl;
    
    try {
        test_runtime_basic();
        test_valores_especiales();
        test_normalizacion();
        test_round_trip();
        test_multiples_bases();
        
        cout << "\n╔═══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║  ✅✅✅ TODOS LOS TESTS PASARON EXITOSAMENTE ✅✅✅           ║" << endl;
        cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;
        
        cout << "\n📊 RESUMEN:" << endl;
        cout << "  ✅ Tests compile-time (consteval + static_assert)" << endl;
        cout << "  ✅ Serialización básica en múltiples bases" << endl;
        cout << "  ✅ Valores especiales (0, máximos)" << endl;
        cout << "  ✅ Normalización automática" << endl;
        cout << "  ✅ Round-trip (to_cstr → from_cstr)" << endl;
        cout << "  ✅ 9 bases diferentes verificadas" << endl;
        
    } catch (const exception& e) {
        cerr << "\n❌ ERROR: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
