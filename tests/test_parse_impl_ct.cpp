/**
 * @file test_parse_impl_ct.cpp
 * @brief Test de parse_impl_ct y from_array_ct con std::expected
 * @details Demuestra el parsing compile-time sin excepciones usando std::array
 */

#include <iostream>
#include <array>
#include <expected>
#include "dig_t.hpp"

using namespace NumRepr;

int main() {
    std::cout << "=== Test de parse_impl_ct y from_array_ct ===" << std::endl;
    std::cout << std::endl;

    // ========================================================================
    // TEST 1: Parsing exitoso formato "d[N]BM"
    // ========================================================================
    std::cout << "1. Parsing exitoso: formato d[5]B10" << std::endl;
    {
        constexpr std::array<char, 7> str = {'d', '[', '5', ']', 'B', '1', '0'};
        constexpr auto result = dig_t<10>::parse_impl_ct(str);
        
        static_assert(result.has_value(), "parse_impl_ct debe tener éxito");
        static_assert(*result == 5, "Valor parseado debe ser 5");
        
        if (result) {
            std::cout << "   ✓ Valor parseado: " << static_cast<int>(*result) << std::endl;
        } else {
            std::cout << "   ✗ Error inesperado" << std::endl;
            return 1;
        }
    }

    // ========================================================================
    // TEST 2: Parsing exitoso formato "dig#N#BM"
    // ========================================================================
    std::cout << "2. Parsing exitoso: formato dig#23#B10" << std::endl;
    {
        constexpr std::array<char, 10> str = {'d', 'i', 'g', '#', '2', '3', '#', 'B', '1', '0'};
        constexpr auto result = dig_t<10>::parse_impl_ct(str);
        
        // 23 mod 10 = 3
        static_assert(result.has_value(), "parse_impl_ct debe tener éxito");
        static_assert(*result == 3, "Valor debe normalizarse: 23 mod 10 = 3");
        
        if (result) {
            std::cout << "   ✓ Valor parseado (23 mod 10): " << static_cast<int>(*result) << std::endl;
        } else {
            std::cout << "   ✗ Error inesperado" << std::endl;
            return 1;
        }
    }

    // ========================================================================
    // TEST 3: Error - prefijo inválido
    // ========================================================================
    std::cout << "3. Error esperado: prefijo inválido 'x[5]B10'" << std::endl;
    {
        constexpr std::array<char, 7> str = {'x', '[', '5', ']', 'B', '1', '0'};
        constexpr auto result = dig_t<10>::parse_impl_ct(str);
        
        static_assert(!result.has_value(), "Debe fallar con prefijo inválido");
        static_assert(result.error() == parse_error_t::invalid_prefix, 
                      "Error debe ser invalid_prefix");
        
        if (!result) {
            std::cout << "   ✓ Error detectado correctamente: invalid_prefix" << std::endl;
        } else {
            std::cout << "   ✗ Debería haber fallado" << std::endl;
            return 1;
        }
    }

    // ========================================================================
    // TEST 4: Error - base no coincide
    // ========================================================================
    std::cout << "4. Error esperado: base mismatch 'd[5]B16' para dig_t<10>" << std::endl;
    {
        constexpr std::array<char, 7> str = {'d', '[', '5', ']', 'B', '1', '6'};
        constexpr auto result = dig_t<10>::parse_impl_ct(str);
        
        static_assert(!result.has_value(), "Debe fallar con base incorrecta");
        static_assert(result.error() == parse_error_t::base_mismatch,
                      "Error debe ser base_mismatch");
        
        if (!result) {
            std::cout << "   ✓ Error detectado correctamente: base_mismatch" << std::endl;
        } else {
            std::cout << "   ✗ Debería haber fallado" << std::endl;
            return 1;
        }
    }

    // ========================================================================
    // TEST 5: Error - dígito inválido
    // ========================================================================
    std::cout << "5. Error esperado: dígito no numérico 'd[5a]B10'" << std::endl;
    {
        constexpr std::array<char, 8> str = {'d', '[', '5', 'a', ']', 'B', '1', '0'};
        constexpr auto result = dig_t<10>::parse_impl_ct(str);
        
        static_assert(!result.has_value(), "Debe fallar con carácter no numérico");
        static_assert(result.error() == parse_error_t::invalid_digit,
                      "Error debe ser invalid_digit");
        
        if (!result) {
            std::cout << "   ✓ Error detectado correctamente: invalid_digit" << std::endl;
        } else {
            std::cout << "   ✗ Debería haber fallado" << std::endl;
            return 1;
        }
    }

    // ========================================================================
    // TEST 6: from_array_ct - parsing exitoso con factory
    // ========================================================================
    std::cout << "6. from_array_ct: creando dig_t desde array" << std::endl;
    {
        constexpr std::array<char, 7> str = {'d', '[', '7', ']', 'B', '1', '0'};
        constexpr auto result = dig_t<10>::from_array_ct(str);
        
        static_assert(result.has_value(), "from_array_ct debe tener éxito");
        static_assert(result->get() == 7, "Valor debe ser 7");
        
        if (result) {
            std::cout << "   ✓ dig_t creado exitosamente: valor = " 
                      << static_cast<int>(result->get()) << std::endl;
        } else {
            std::cout << "   ✗ Error inesperado" << std::endl;
            return 1;
        }
    }

    // ========================================================================
    // TEST 7: from_array_ct - manejo de error sin excepciones
    // ========================================================================
    std::cout << "7. from_array_ct: error sin excepciones" << std::endl;
    {
        constexpr std::array<char, 7> str = {'d', '[', '5', ']', 'B', '9', '9'};
        constexpr auto result = dig_t<10>::from_array_ct(str);
        
        static_assert(!result.has_value(), "Debe fallar con base incorrecta");
        
        if (!result) {
            std::cout << "   ✓ Error manejado sin excepciones" << std::endl;
        } else {
            std::cout << "   ✗ Debería haber fallado" << std::endl;
            return 1;
        }
    }

    // ========================================================================
    // TEST 8: Base grande (256)
    // ========================================================================
    std::cout << "8. Parsing con base 256: dig#255#B256" << std::endl;
    {
        constexpr std::array<char, 12> str = 
            {'d', 'i', 'g', '#', '2', '5', '5', '#', 'B', '2', '5', '6'};
        constexpr auto result = dig_t<256>::parse_impl_ct(str);
        
        static_assert(result.has_value(), "parse_impl_ct debe tener éxito");
        static_assert(*result == 255, "Valor debe ser 255");
        
        if (result) {
            std::cout << "   ✓ Valor parseado: " << static_cast<int>(*result) << std::endl;
        } else {
            std::cout << "   ✗ Error inesperado" << std::endl;
            return 1;
        }
    }

    std::cout << std::endl;
    std::cout << "=== ✓ Todos los tests pasaron exitosamente ===" << std::endl;
    return 0;
}
