/**
 * @file test_parse_formats.cpp
 * @brief Tests de los 4 formatos de parsing soportados
 * 
 * @details Verifica que todos los formatos funcionan correctamente:
 * - "d[N]BM" - formato corto con corchetes
 * - "d#N#BM" - formato corto con almohadillas (NUEVO)
 * - "dig#N#BM" - formato largo con almohadillas
 * - "dig[N]BM" - formato largo con corchetes (NUEVO)
 */

#include <core/dig_t.hpp>
#include <core/dig_t.hpp>
#include <iostream>
#include <cassert>

using namespace std;
using namespace NumRepr;

void test_formato_d_corchetes() {
    cout << "\n=== TEST FORMATO d[N]BM ===" << endl;
    
    try {
        auto d1 = dig_t<50>::from_cstr("d[42]B50");
            assert(d1->get() == 42);
            cout << "[OK] d[42]B50 = 42" << endl;
        
        auto d2 = dig_t<10>::from_cstr("d[0]B10");
            assert(d2->get() == 0);
            cout << "[OK] d[0]B10 = 0" << endl;
        
        auto d3 = dig_t<256>::from_cstr("d[999]B256");
            assert(d3->get() == 999 % 256);
            cout << "[OK] d[999]B256 = " << static_cast<int>(d3->get()) << " (normalizado)" << endl;
    } catch (const exception& e) {
        cerr << "❌ Error: " << e.what() << endl;
        assert(false);
    }
    
    try {
        auto d4 = dig_t<10>::from_cstr("d[5]B16");
        assert(false && "Debería haber rechazado base incorrecta");
    } catch (const std::invalid_argument&) {
        cout << "✓ d[5]B16 rechazado (base incorrecta)" << endl;
    }
}

void test_formato_d_almohadillas() {
    cout << "\n=== TEST FORMATO d#N#BM [NUEVO] ===" << endl;
    
    try {
        auto d1 = dig_t<50>::from_cstr("d#42#B50");
            assert(d1->get() == 42);
            cout << "[OK] d#42#B50 = 42" << endl;
        
        auto d2 = dig_t<10>::from_cstr("d#0#B10");
            assert(d2->get() == 0);
            cout << "[OK] d#0#B10 = 0" << endl;
        
        auto d3 = dig_t<256>::from_cstr("d#999#B256");
            assert(d3->get() == 999 % 256);
            cout << "[OK] d#999#B256 = " << static_cast<int>(d3->get()) << " (normalizado)" << endl;
    } catch (const exception& e) {
        cerr << "❌ Error: " << e.what() << endl;
        assert(false);
    }
    
    try {
        auto d4 = dig_t<10>::from_cstr("d#5#B16");
        assert(false && "Debería haber rechazado base incorrecta");
    } catch (const std::invalid_argument&) {
        cout << "✓ d#5#B16 rechazado (base incorrecta)" << endl;
    }
}

void test_formato_dig_almohadillas() {
    cout << "\n=== TEST FORMATO dig#N#BM ===" << endl;
    
    try {
        auto d1 = dig_t<50>::from_cstr("dig#42#B50");
            assert(d1->get() == 42);
            cout << "[OK] dig#42#B50 = 42" << endl;
        
        auto d2 = dig_t<10>::from_cstr("dig#0#B10");
            assert(d2->get() == 0);
            cout << "[OK] dig#0#B10 = 0" << endl;
        
        auto d3 = dig_t<256>::from_cstr("dig#999#B256");
            assert(d3->get() == 999 % 256);
            cout << "[OK] dig#999#B256 = " << static_cast<int>(d3->get()) << " (normalizado)" << endl;
    } catch (const exception& e) {
        cerr << "❌ Error: " << e.what() << endl;
        assert(false);
    }
    
    try {
        auto d4 = dig_t<10>::from_cstr("dig#5#B16");
        assert(false && "Debería haber rechazado base incorrecta");
    } catch (const std::invalid_argument&) {
        cout << "✓ dig#5#B16 rechazado (base incorrecta)" << endl;
    }
}

void test_formato_dig_corchetes() {
    cout << "\n=== TEST FORMATO dig[N]BM [NUEVO] ===" << endl;
    
    try {
        auto d1 = dig_t<50>::from_cstr("dig[42]B50");
            assert(d1->get() == 42);
            cout << "[OK] dig[42]B50 = 42" << endl;
        
        auto d2 = dig_t<10>::from_cstr("dig[0]B10");
            assert(d2->get() == 0);
            cout << "[OK] dig[0]B10 = 0" << endl;
        
        auto d3 = dig_t<256>::from_cstr("dig[999]B256");
            assert(d3->get() == 999 % 256);
            cout << "[OK] dig[999]B256 = " << static_cast<int>(d3->get()) << " (normalizado)" << endl;
    } catch (const exception& e) {
        cerr << "❌ Error: " << e.what() << endl;
        assert(false);
    }
    
    try {
        auto d4 = dig_t<10>::from_cstr("dig[5]B16");
        assert(false && "Debería haber rechazado base incorrecta");
    } catch (const std::invalid_argument&) {
        cout << "✓ dig[5]B16 rechazado (base incorrecta)" << endl;
    }
}

void test_equivalencia_formatos() {
    cout << "\n=== TEST EQUIVALENCIA ENTRE FORMATOS ===" << endl;
    
    const int test_values[] = {0, 1, 7, 15, 200};
    
    for (int num : test_values) {
        string num_str = to_string(num);
        string str_base = "B256";
        
        try {
            string str1 = "d[" + num_str + "]" + str_base;
            string str2 = "d#" + num_str + "#" + str_base;
            string str3 = "dig#" + num_str + "#" + str_base;
            string str4 = "dig[" + num_str + "]" + str_base;
            
            auto d1 = dig_t<256>::from_cstr(str1.c_str());
            auto d2 = dig_t<256>::from_cstr(str2.c_str());
            auto d3 = dig_t<256>::from_cstr(str3.c_str());
            auto d4 = dig_t<256>::from_cstr(str4.c_str());
            
            assert(d1.get() == d2.get());
            assert(d2.get() == d3.get());
            assert(d3.get() == d4.get());
            
                cout << "[OK] Todos los formatos para " << num << " -> " << static_cast<int>(d1.get()) << endl;
        } catch (const exception& e) {
            cerr << "❌ Error para " << num << ": " << e.what() << endl;
            assert(false);
        }
    }
}

void test_multiples_bases() {
    cout << "\n=== TEST EN MÚLTIPLES BASES ===" << endl;
    
    try {
        auto d1 = dig_t<2>::from_cstr("d[5]B2");
            assert(d1->get() == 1);
            cout << "[OK] Base 2: d[5]B2 = 1 (normalizado)" << endl;
        
        auto d2 = dig_t<16>::from_cstr("d#255#B16");
            assert(d2->get() == 15);
            cout << "[OK] Base 16: d#255#B16 = 15 (normalizado)" << endl;
        
        auto d3 = dig_t<256>::from_cstr("dig[1000]B256");
            assert(d3->get() == 1000 % 256);
            cout << "[OK] Base 256: dig[1000]B256 = " << static_cast<int>(d3->get()) << " (normalizado)" << endl;
        
        auto d4 = dig_t<257>::from_cstr("dig#500#B257");
            assert(d4->get() == 500 % 257);
            cout << "[OK] Base 257: dig#500#B257 = " << static_cast<int>(d4->get()) << " (normalizado)" << endl;
    } catch (const exception& e) {
        cerr << "❌ Error: " << e.what() << endl;
        assert(false);
    }
}

int main() {
    cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║      TEST DE FORMATOS DE PARSING - parse_impl                ║" << endl;
    cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;
    
    try {
        test_formato_d_corchetes();
        test_formato_d_almohadillas();
        test_formato_dig_almohadillas();
        test_formato_dig_corchetes();
        test_equivalencia_formatos();
        test_multiples_bases();
        
        cout << "\n╔═══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║  ✅✅✅ TODOS LOS TESTS PASARON EXITOSAMENTE ✅✅✅           ║" << endl;
        cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;
        
        cout << "\n📊 RESUMEN:" << endl;
        cout << "  ✅ Formato d[N]BM (corto, corchetes)" << endl;
        cout << "  ✅ Formato d#N#BM (corto, almohadillas) - NUEVO" << endl;
        cout << "  ✅ Formato dig#N#BM (largo, almohadillas)" << endl;
        cout << "  ✅ Formato dig[N]BM (largo, corchetes) - NUEVO" << endl;
        cout << "\n🎯 Total: 4 formatos soportados" << endl;
        cout << "✨ Equivalencia verificada entre todos" << endl;
        cout << "📈 Funcionamiento en múltiples bases (2, 10, 16, 256, 257)" << endl;
        
    } catch (const exception& e) {
        cerr << "\n❌ ERROR: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
