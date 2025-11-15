/**
 * @file test_from_functions_check.cpp
 * @brief Test de compilación para verificar from_string y from_cstr con std::expected
 */

#include "dig_t.hpp"
#include <iostream>
#include <cassert>

int main() {
    using namespace NumRepr;
    
    std::cout << "=== TEST DE FUNCIONES from_* CON std::expected ===" << std::endl;
    
    // Test from_string
    {
        std::cout << "\n--- from_string() ---" << std::endl;
        std::string valid_str = "d[5]B10";
        auto result = dig_t<10>::from_string(valid_str);
        
        if (result) {
            std::cout << "✅ Parsing exitoso: " << result->get() << std::endl;
            assert(result->get() == 5);
        } else {
            std::cout << "❌ Error de parsing" << std::endl;
            return 1;
        }
        
        std::string invalid_str = "invalid";
        auto result2 = dig_t<10>::from_string(invalid_str);
        if (!result2) {
            std::cout << "✅ Error detectado correctamente en string inválido" << std::endl;
        } else {
            std::cout << "❌ Debería haber detectado error" << std::endl;
            return 1;
        }
    }
    
    // Test from_cstr
    {
        std::cout << "\n--- from_cstr() ---" << std::endl;
        const char* valid_cstr = "dig#7#B16";
        auto result = dig_t<16>::from_cstr(valid_cstr);
        
        if (result) {
            std::cout << "✅ Parsing exitoso: " << result->get() << std::endl;
            assert(result->get() == 7);
        } else {
            std::cout << "❌ Error de parsing" << std::endl;
            return 1;
        }
        
        const char* nullptr_test = nullptr;
        auto result2 = dig_t<16>::from_cstr(nullptr_test);
        if (!result2) {
            std::cout << "✅ nullptr detectado correctamente" << std::endl;
        } else {
            std::cout << "❌ Debería haber detectado nullptr" << std::endl;
            return 1;
        }
    }
    
    // Test from_array_ct
    {
        std::cout << "\n--- from_array_ct() ---" << std::endl;
        constexpr auto result = dig_t<10>::from_array_ct<std::array{'d', '[', '9', ']', 'B', '1', '0'}>();
        
        static_assert(result.has_value(), "Should parse successfully at compile time");
        static_assert(result->get() == 9, "Should parse to value 9");
        
        std::cout << "✅ Parsing compile-time exitoso: " << result->get() << std::endl;
    }
    
    // Test constructores noexcept
    {
        std::cout << "\n--- Constructores noexcept ---" << std::endl;
        
        // Constructor desde string inválido no lanza, construye dig_t(0)
        dig_t<10> d1("invalid_format");
        std::cout << "Constructor con formato inválido: d1 = " << d1.get() << " (debe ser 0)" << std::endl;
        assert(d1.get() == 0);
        
        // Constructor desde nullptr no lanza, construye dig_t(0)
        const char* null_ptr = nullptr;
        dig_t<10> d2(null_ptr);
        std::cout << "Constructor con nullptr: d2 = " << d2.get() << " (debe ser 0)" << std::endl;
        assert(d2.get() == 0);
        
        // Constructor desde formato válido
        dig_t<10> d3("d[7]B10");
        std::cout << "Constructor con formato válido: d3 = " << d3.get() << " (debe ser 7)" << std::endl;
        assert(d3.get() == 7);
        
        std::cout << "✅ Constructores noexcept funcionan correctamente" << std::endl;
    }
    
    std::cout << "\n✅ TODOS LOS TESTS PASARON" << std::endl;
    return 0;
}
