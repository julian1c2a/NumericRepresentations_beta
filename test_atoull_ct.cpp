/**
 * Test para atoull_ct() - Conversión de strings a ullint_t en tiempo de compilación
 * 
 * Verifica:
 * - Parsing correcto de valores válidos  
 * - Compile-time evaluation
 * - Equivalencia con atoull_checked() runtime
 */

#include "include/core/internal/basic_types.hpp"
#include <iostream>
#include <cassert>
#include <limits>

using namespace std;
using namespace NumRepr;

// Helper para crear string literals como template parameters (C++20 style)
template <size_t N>
struct FixedString {
    char data_[N];
    
    constexpr FixedString(const char (&str)[N]) {
        for (size_t i = 0; i < N; ++i) {
            data_[i] = str[i];
        }
    }
    
    constexpr const char* data() const { return data_; }
    constexpr size_t size() const { return N - 1; } // Sin null terminator
};

int main() {
    cout << "=== Test atoull_ct: Compile-Time String to ullint_t ===" << endl;
    
    // Test 1: Valores pequeños
    {
        constexpr auto val1 = atoull_ct<FixedString("0")>();
        constexpr auto val2 = atoull_ct<FixedString("1")>();
        constexpr auto val3 = atoull_ct<FixedString("42")>();
        constexpr auto val4 = atoull_ct<FixedString("12345")>();
        
        assert(val1 == 0);
        assert(val2 == 1);
        assert(val3 == 42);
        assert(val4 == 12345);
        
        cout << "✓ Test 1: Valores pequeños OK" << endl;
        cout << "  0 -> " << val1 << endl;
        cout << "  1 -> " << val2 << endl;
        cout << "  42 -> " << val3 << endl;
        cout << "  12345 -> " << val4 << endl;
    }
    
    // Test 2: Valores grandes
    {
        constexpr auto val_large = atoull_ct<FixedString("1234567890123456789")>();
        assert(val_large == 1234567890123456789ULL);
        
        cout << "✓ Test 2: Valor grande OK" << endl;
        cout << "  1234567890123456789 -> " << val_large << endl;
    }
    
    // Test 3: ULLONG_MAX boundary
    {
        constexpr auto max_val = atoull_ct<FixedString("18446744073709551615")>();
        constexpr ullint_t expected_max = numeric_limits<ullint_t>::max();
        
        assert(max_val == expected_max);
        assert(max_val == ULLONG_MAX);
        
        cout << "✓ Test 3: ULLONG_MAX boundary OK" << endl;
        cout << "  18446744073709551615 -> " << max_val << endl;
        cout << "  ULLONG_MAX = " << ULLONG_MAX << endl;
    }
    
    // Test 4: Equivalencia con runtime atoull_checked()
    {
        constexpr auto ct_val = atoull_ct<FixedString("9876543210")>();
        auto rt_result = atoull_checked("9876543210");
        
        assert(rt_result.has_value());
        assert(ct_val == rt_result.value());
        
        cout << "✓ Test 4: Equivalencia compile-time vs runtime OK" << endl;
        cout << "  CT: " << ct_val << " == RT: " << rt_result.value() << endl;
    }
    
    // Test 5: Ceros leading
    {
        constexpr auto val_zeros = atoull_ct<FixedString("000123")>();
        assert(val_zeros == 123);
        
        cout << "✓ Test 5: Leading zeros OK" << endl;
        cout << "  000123 -> " << val_zeros << endl;
    }
    
    // Test 6: Potencias de 10
    {
        constexpr auto val_1e9 = atoull_ct<FixedString("1000000000")>();
        constexpr auto val_1e18 = atoull_ct<FixedString("1000000000000000000")>();
        
        assert(val_1e9 == 1000000000ULL);
        assert(val_1e18 == 1000000000000000000ULL);
        
        cout << "✓ Test 6: Potencias de 10 OK" << endl;
        cout << "  10^9 -> " << val_1e9 << endl;
        cout << "  10^18 -> " << val_1e18 << endl;
    }
    
    // Test 7: Uso en constexpr contexts
    {
        constexpr auto compile_time_constant = atoull_ct<FixedString("999")>();
        constexpr ullint_t doubled = compile_time_constant * 2;
        static_assert(doubled == 1998, "Compile-time arithmetic should work");
        
        cout << "✓ Test 7: Uso en constexpr contexts OK" << endl;
        cout << "  999 * 2 = " << doubled << endl;
    }
    
    // Test 8: static_assert con valores
    {
        static_assert(atoull_ct<FixedString("100")>() == 100);
        static_assert(atoull_ct<FixedString("18446744073709551615")>() == ULLONG_MAX);
        
        cout << "✓ Test 8: static_assert validations OK" << endl;
    }
    
    cout << "\n=== TODOS LOS TESTS PASARON ===" << endl;
    
    // Tests que DEBEN fallar en compilación (comentados):
    /*
    // Overflow: ULLONG_MAX + 1
    constexpr auto overflow1 = atoull_ct<FixedString("18446744073709551616")>();
    
    // Carácter inválido
    constexpr auto invalid1 = atoull_ct<FixedString("12abc34")>();
    
    // String vacío
    constexpr auto empty = atoull_ct<FixedString("")>();
    
    // Espacios
    constexpr auto spaces = atoull_ct<FixedString(" 123")>();
    */
    
    return 0;
}
