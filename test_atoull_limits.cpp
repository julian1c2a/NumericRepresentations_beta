#include "include/core/internal/basic_types.hpp"
#include <iostream>
#include <cassert>
#include <limits>

using namespace NumRepr::type_traits;

int main() {
    std::cout << "=== PRUEBA DE LÍMITES: atoull y atoull_checked ===\n\n";
    
    // Límite máximo de uint64_t
    constexpr auto UINT64_MAX_STR = "18446744073709551615";
    constexpr auto UINT64_MAX_VAL = std::numeric_limits<uint64_t>::max();
    
    std::cout << "1. LÍMITE MÁXIMO (UINT64_MAX):\n";
    std::cout << "   Valor: " << UINT64_MAX_STR << "\n";
    
    // Test atoull_checked con valor máximo válido
    auto result_max = atoull_checked(UINT64_MAX_STR);
    assert(result_max.has_value());
    assert(*result_max == UINT64_MAX_VAL);
    std::cout << "   ✓ atoull_checked: OK (valor = " << *result_max << ")\n";
    
    // Test atoull sin validación
    constexpr auto test_max = atoull(UINT64_MAX_STR);
    assert(test_max == UINT64_MAX_VAL);
    std::cout << "   ✓ atoull: OK (valor = " << test_max << ")\n\n";
    
    // Overflow: UINT64_MAX + 1
    std::cout << "2. OVERFLOW (UINT64_MAX + 1):\n";
    auto result_overflow = atoull_checked("18446744073709551616");
    assert(!result_overflow);
    assert(result_overflow.error() == atoull_err_t::overflow);
    std::cout << "   ✓ atoull_checked detecta overflow correctamente\n\n";
    
    // Overflow: valor muy grande
    std::cout << "3. OVERFLOW (valor muy grande):\n";
    auto result_big = atoull_checked("99999999999999999999");
    assert(!result_big);
    assert(result_big.error() == atoull_err_t::overflow);
    std::cout << "   ✓ atoull_checked detecta overflow en valor grande\n\n";
    
    // Caracteres no válidos
    std::cout << "4. CARACTERES NO VÁLIDOS:\n";
    auto result_invalid = atoull_checked("123abc");
    assert(!result_invalid);
    assert(result_invalid.error() == atoull_err_t::no_digit);
    std::cout << "   ✓ atoull_checked detecta caracteres no numéricos\n\n";
    
    // String vacío
    std::cout << "5. STRING VACÍO:\n";
    auto result_empty = atoull_checked("");
    assert(!result_empty);
    assert(result_empty.error() == atoull_err_t::empty_str);
    std::cout << "   ✓ atoull_checked detecta string vacío\n\n";
    
    // nullptr
    std::cout << "6. NULLPTR:\n";
    auto result_null = atoull_checked(nullptr);
    assert(!result_null);
    assert(result_null.error() == atoull_err_t::empty_str);
    std::cout << "   ✓ atoull_checked detecta nullptr\n\n";
    
    // atoull_consume con texto embebido
    std::cout << "7. atoull_consume CON TEXTO EMBEBIDO:\n";
    auto result_consume = atoull_consume("12345abc");
    assert(result_consume.has_value());
    auto [val, consumed] = *result_consume;
    assert(val == 12345);
    assert(consumed == 5);
    std::cout << "   ✓ Parseó: 12345 (consumió 5 caracteres)\n";
    std::cout << "   ✓ Resto: \"" << ("12345abc" + consumed) << "\"\n\n";
    
    // atoull_consume que empieza con no-dígito
    std::cout << "8. atoull_consume CON NO-DÍGITO AL INICIO:\n";
    auto result_nodigi = atoull_consume("abc123");
    assert(!result_nodigi);
    assert(result_nodigi.error() == atoull_err_t::no_digit);
    std::cout << "   ✓ Detecta no-dígito al inicio\n\n";
    
    // Valores constexpr en compile-time
    std::cout << "9. EVALUACIÓN EN COMPILE-TIME:\n";
    constexpr auto ct1 = atoull("12345");
    constexpr auto ct2 = atoull("99999");
    static_assert(ct1 == 12345, "Compile-time check failed");
    static_assert(ct2 == 99999, "Compile-time check failed");
    std::cout << "   ✓ atoull evaluable en compile-time\n";
    std::cout << "   ✓ ct1 = " << ct1 << ", ct2 = " << ct2 << "\n\n";
    
    // Test con string_view
    std::cout << "10. TEST CON string_view:\n";
    std::string_view sv = "67890";
    auto result_sv = atoull_checked(sv);
    assert(result_sv.has_value());
    assert(*result_sv == 67890);
    std::cout << "   ✓ atoull_checked(string_view): " << *result_sv << "\n";
    
    constexpr auto ct_sv = atoull(std::string_view("54321"));
    static_assert(ct_sv == 54321);
    std::cout << "   ✓ atoull(string_view) constexpr: " << ct_sv << "\n\n";
    
    std::cout << "=== TODAS LAS PRUEBAS PASARON ===\n";
    std::cout << "\nRESUMEN DE LÍMITES:\n";
    std::cout << "  • Rango válido: [0, " << UINT64_MAX_VAL << "]\n";
    std::cout << "  • Máximo dígitos: 20 (para UINT64_MAX)\n";
    std::cout << "  • Detección de overflow: SÍ (en versiones _checked)\n";
    std::cout << "  • Validación de entrada: SÍ (en versiones _checked)\n";
    std::cout << "  • Evaluación compile-time: SÍ (versiones sin _checked)\n";
    
    return 0;
}
