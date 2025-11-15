/**
 * @file test_make_digit.cpp
 * @brief Tests para las funciones libres make_digit()
 */

#include "dig_t.hpp"
#include <iostream>
#include <cassert>

using namespace NumRepr;

int main() {
    std::cout << "=== TEST DE FUNCIONES make_digit() ===" << std::endl;
    
    // =========================================================================
    // 1. make_digit<Base, Arr>() - Array como template parameter
    // =========================================================================
    {
        std::cout << "\n--- make_digit<Base, Arr>() con array compile-time ---" << std::endl;
        
        auto d1 = make_digit<10, std::array{'d','[','5',']','B','1','0'}>();
        assert(d1.has_value() && "Should parse successfully");
        assert(d1->get() == 5 && "Value should be 5");
        
        std::cout << "✅ make_digit<10, array>() = " << d1->get() << std::endl;
        
        auto d2 = make_digit<16, std::array{'d','i','g','#','1','5','#','B','1','6'}>();
        assert(d2.has_value() && "Should parse value 15");
        assert(d2->get() == 15 && "Value should be 15 (0xF in hex)");
        
        std::cout << "✅ make_digit<16, array>() = " << d2->get() << " (0xF)" << std::endl;
        
        // Test con error: base incorrecta
        auto d3 = make_digit<10, std::array{'d','[','5',']','B','1','6'}>();
        assert(!d3.has_value() && "Should fail: base mismatch");
        
        std::cout << "✅ make_digit con base incorrecta detectado" << std::endl;
    }
    
    // =========================================================================
    // 2. make_digit<Base>(std::string) - Runtime
    // =========================================================================
    {
        std::cout << "\n--- make_digit<Base>(string) runtime ---" << std::endl;
        
        // Base 10: dígito 5 es válido (0-9)
        std::string str1 = "d[5]B10";
        auto d1 = make_digit<10>(str1);
        assert(d1.has_value());
        assert(d1->get() == 5);
        
        std::cout << "✅ make_digit<10>(\"d[5]B10\") = " << d1->get() << std::endl;
        
        std::string str2 = "dig#255#B256";
        auto d2 = make_digit<256>(str2);
        assert(d2.has_value());
        assert(d2->get() == 255);
        
        std::cout << "✅ make_digit<256>(\"dig#255#B256\") = " 
                  << static_cast<int>(d2->get()) << std::endl;
        
        // Test con error
        std::string invalid = "invalid_format";
        auto d3 = make_digit<10>(invalid);
        assert(!d3.has_value());
        
        std::cout << "✅ make_digit con formato inválido detectado" << std::endl;
    }
    
    // =========================================================================
    // 3. make_digit<Base>(const char*) - Runtime
    // =========================================================================
    {
        std::cout << "\n--- make_digit<Base>(const char*) ---" << std::endl;
        
        // Runtime
        const char* cstr1 = "d[7]B16";
        auto d1 = make_digit<16>(cstr1);
        assert(d1.has_value());
        assert(d1->get() == 7);
        
        std::cout << "✅ make_digit<16>(\"d[7]B16\") = " << d1->get() << std::endl;
        
        // También runtime con string literal - Base 100 permite dígitos 0-99
        auto d2 = make_digit<100>("d[99]B100");
        assert(d2.has_value() && "Should parse");
        assert(d2->get() == 99 && "Value should be 99");
        
        std::cout << "✅ make_digit<100>(\"d[99]B100\") = " << static_cast<int>(d2->get()) << std::endl;
        
        // Test con nullptr
        const char* null_ptr = nullptr;
        auto d3 = make_digit<10>(null_ptr);
        assert(!d3.has_value());
        
        std::cout << "✅ make_digit con nullptr detectado" << std::endl;
    }
    
    // =========================================================================
    // 4. Comparación con métodos estáticos de dig_t
    // =========================================================================
    {
        std::cout << "\n--- Equivalencia con dig_t<Base>::from_* ---" << std::endl;
        
        // make_digit vs from_string
        std::string str = "d[123]B256";
        auto m1 = make_digit<256>(str);
        auto f1 = dig_t<256>::from_string(str);
        
        assert(m1.has_value() == f1.has_value());
        if (m1.has_value()) {
            assert(m1->get() == f1->get());
            std::cout << "✅ make_digit<256>(str) ≡ dig_t<256>::from_string(str)" << std::endl;
        }
        
        // make_digit vs from_cstr
        const char* cstr = "d[77]B10";
        auto m2 = make_digit<10>(cstr);
        auto f2 = dig_t<10>::from_cstr(cstr);
        
        assert(m2.has_value() == f2.has_value());
        if (m2.has_value()) {
            assert(m2->get() == f2->get());
            std::cout << "✅ make_digit<10>(cstr) ≡ dig_t<10>::from_cstr(cstr)" << std::endl;
        }
        
        // make_digit vs from_array_ct
        auto m3 = make_digit<16, std::array{'d','[','A',']','B','1','6'}>();
        auto f3 = dig_t<16>::from_array_ct<std::array{'d','[','A',']','B','1','6'}>();
        
        assert(m3.has_value() == f3.has_value());
        assert(m3->get() == f3->get());
        
        std::cout << "✅ make_digit<16, arr>() ≡ dig_t<16>::from_array_ct<arr>()" << std::endl;
    }
    
    // =========================================================================
    // 5. Uso práctico: parsing de input de usuario
    // =========================================================================
    {
        std::cout << "\n--- Caso de uso práctico ---" << std::endl;
        
        // Simular input de usuario (en producción vendría de std::cin)
        std::string user_input = "d[100]B10";
        
        auto digit = make_digit<10>(user_input);
        
        if (digit) {
            std::cout << "Usuario ingresó dígito válido: " << digit->get() 
                      << " en base 10" << std::endl;
            
            // Usar el dígito
            auto result = *digit + dig_t<10>(50);
            std::cout << "100 + 50 = " << result.get() << " (mod 10) = " 
                      << result.get() << std::endl;
            
            std::cout << "✅ Caso de uso práctico funcionando" << std::endl;
        } else {
            std::cout << "❌ Error: input inválido" << std::endl;
            return 1;
        }
    }
    
    // =========================================================================
    // 6. make_digit<Base>(valor_entero) - Creación directa desde entero
    // =========================================================================
    {
        std::cout << "\n--- make_digit<Base>(entero) ---" << std::endl;
        
        // Valores válidos (dentro del rango 0 a Base-1)
        auto d1 = make_digit<10>(5);
        assert(d1.get() == 5);
        std::cout << "✅ make_digit<10>(5) = " << d1.get() << std::endl;
        
        auto d2 = make_digit<16>(15);
        assert(d2.get() == 15);
        std::cout << "✅ make_digit<16>(15) = " << d2.get() << " (0xF)" << std::endl;
        
        auto d3 = make_digit<256>(255u);
        assert(d3.get() == 255);
        std::cout << "✅ make_digit<256>(255) = " << static_cast<int>(d3.get()) << std::endl;
        
        // Valores que necesitan normalización (fuera del rango)
        auto d4 = make_digit<10>(42);   // 42 % 10 = 2
        assert(d4.get() == 2);
        std::cout << "✅ make_digit<10>(42) = " << d4.get() << " (normalizado: 42 % 10)" << std::endl;
        
        auto d5 = make_digit<16>(100);  // 100 % 16 = 4
        assert(d5.get() == 4);
        std::cout << "✅ make_digit<16>(100) = " << d5.get() << " (normalizado: 100 % 16)" << std::endl;
        
        // Con diferentes tipos enteros
        auto d6 = make_digit<100>(static_cast<uint8_t>(99));
        assert(d6.get() == 99);
        std::cout << "✅ make_digit<100>(uint8_t{99}) = " << static_cast<int>(d6.get()) << std::endl;
        
        auto d7 = make_digit<2>(1u);
        assert(d7.get() == 1);
        std::cout << "✅ make_digit<2>(1) = " << static_cast<int>(d7.get()) << std::endl;
    }
    
    std::cout << "\n✅ TODOS LOS TESTS DE make_digit() PASARON" << std::endl;
    return 0;
}
