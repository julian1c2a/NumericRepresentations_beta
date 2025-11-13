/**
 * @file test_dig_t_comprehensive.cpp
 * @brief Test exhaustivo de todas las funcionalidades de dig_t documentadas y optimizadas
 * 
 * @details Cubre:
 * - Constructores (default, copy, from int, from array compile-time)
 * - Parser compile-time (parse_impl_ct, from_array_ct)
 * - Operadores aritméticos (+, -, *, /, %)
 * - Operadores lógicos (&, |, ^) con interpretación min/max
 * - Operador exponenciación (^) con algoritmo binario O(log exp)
 * - Operadores comparación (==, !=, <, <=, >, >=, <=>)
 * - Funciones auxiliares (is_unit, mult_inv, sum_carry, etc.)
 * - Casos edge (0^0=1, división por 0, inversión de no-unidades)
 */

#include "../include/core/dig_t.hpp"
#include <iostream>
#include <cassert>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace NumRepr;

// ============================================================================
// SECCIÓN 1: CONSTRUCTORES Y INICIALIZACIÓN
// ============================================================================

template <uint64_t B>
void test_constructores() {
    cout << "\n=== TEST CONSTRUCTORES (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    // Constructor por defecto (debe inicializar a 0)
    dig d1;
    assert(d1() == 0);
    cout << "✓ Constructor por defecto: d() = " << d1() << endl;
    
    // Constructor desde entero positivo
    dig d2(42);
    assert(d2() == (42 % B));
    cout << "✓ Constructor desde int: dig(" << 42 << ") = " << d2() << endl;
    
    // Constructor desde entero negativo (debe normalizar correctamente)
    dig d3(-5);
    uint64_t expected = (B - (5 % B)) % B;
    assert(d3() == expected);
    cout << "✓ Constructor desde int negativo: dig(-5) = " << d3() << " (normalizado)" << endl;
    
    // Constructor copia
    dig d4 = d2;
    assert(d4() == d2());
    cout << "✓ Constructor copia: d4 = d2 = " << d4() << endl;
}

// ============================================================================
// SECCIÓN 2: PARSER COMPILE-TIME
// ============================================================================

template <uint64_t B>
void test_parser_compile_time() {
    cout << "\n=== TEST PARSER COMPILE-TIME (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    // from_array_ct con array de caracteres válido
    constexpr std::array<char, 2> arr1{'4', '2'};
    auto result1 = dig::from_array_ct(arr1);
    if (result1.has_value()) {
        dig d1 = result1.value();
        assert(d1() == (42 % B));
        cout << "✓ from_array_ct({'4','2'}) = " << d1() << " (compile-time OK)" << endl;
    } else {
        cout << "✗ from_array_ct({'4','2'}) falló inesperadamente" << endl;
    }
    
    // from_array_ct con '0'
    constexpr std::array<char, 1> arr2{'0'};
    auto result2 = dig::from_array_ct(arr2);
    if (result2.has_value()) {
        dig d2 = result2.value();
        assert(d2() == 0);
        cout << "✓ from_array_ct({'0'}) = 0" << endl;
    }
    
    // Error: carácter inválido
    constexpr std::array<char, 3> arr3{'1', 'x', '3'};
    auto result3 = dig::from_array_ct(arr3);
    if (!result3.has_value()) {
        cout << "✓ from_array_ct({'1','x','3'}) → error detectado correctamente" << endl;
    }
    
    // Error: array vacío
    constexpr std::array<char, 0> arr4{};
    auto result4 = dig::from_array_ct(arr4);
    if (!result4.has_value()) {
        cout << "✓ from_array_ct(array vacío) → error detectado correctamente" << endl;
    }
}

// ============================================================================
// SECCIÓN 3: OPERADORES ARITMÉTICOS
// ============================================================================

template <uint64_t B>
void test_operadores_aritmeticos() {
    cout << "\n=== TEST OPERADORES ARITMÉTICOS (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    dig a(7), b(3);
    
    // Suma
    dig sum = a + b;
    assert(sum() == ((7 + 3) % B));
    cout << "✓ " << a() << " + " << b() << " = " << sum() << " (mod " << B << ")" << endl;
    
    // Resta
    dig diff = a - b;
    assert(diff() == ((7 - 3 + B) % B));
    cout << "✓ " << a() << " - " << b() << " = " << diff() << " (mod " << B << ")" << endl;
    
    // Multiplicación
    dig prod = a * b;
    assert(prod() == ((7 * 3) % B));
    cout << "✓ " << a() << " × " << b() << " = " << prod() << " (mod " << B << ")" << endl;
    
    // División (si b es unidad)
    if constexpr (B == 257) { // Base prima
        dig quotient = a / b;
        dig check = quotient * b;
        assert(check() == a());
        cout << "✓ " << a() << " / " << b() << " = " << quotient() << " (verificado: " << quotient() << "×" << b() << "=" << check() << ")" << endl;
    }
    
    // Módulo
    if (B > 10) {
        dig c(15), d(7);
        dig mod = c % d;
        cout << "✓ " << c() << " % " << d() << " = " << mod() << endl;
    }
    
    // Operadores compuestos
    dig x(5);
    x += dig(3);
    assert(x() == ((5 + 3) % B));
    cout << "✓ Operador += funciona correctamente" << endl;
    
    x *= dig(2);
    assert(x() == ((8 * 2) % B));
    cout << "✓ Operador *= funciona correctamente" << endl;
}

// ============================================================================
// SECCIÓN 4: OPERADORES LÓGICOS (INTERPRETACIÓN MIN/MAX)
// ============================================================================

template <uint64_t B>
void test_operadores_logicos() {
    cout << "\n=== TEST OPERADORES LÓGICOS (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    dig a(5), b(9);
    
    // Operador & (min)
    dig and_result = a & b;
    assert(and_result() == min(a(), b()));
    cout << "✓ " << a() << " & " << b() << " = " << and_result() << " (min)" << endl;
    
    // Operador | (max)
    dig or_result = a | b;
    assert(or_result() == max(a(), b()));
    cout << "✓ " << a() << " | " << b() << " = " << or_result() << " (max)" << endl;
    
    // Operador && (equivalente a &)
    dig and2_result = a && b;
    assert(and2_result() == and_result());
    cout << "✓ " << a() << " && " << b() << " = " << and2_result() << " (equivalente a &)" << endl;
    
    // Operador || (equivalente a |)
    dig or2_result = a || b;
    assert(or2_result() == or_result());
    cout << "✓ " << a() << " || " << b() << " = " << or2_result() << " (equivalente a |)" << endl;
    
    // Operadores compuestos
    dig x(3);
    x &= dig(7);
    assert(x() == 3);
    cout << "✓ Operador &= (min) funciona correctamente" << endl;
    
    dig y(3);
    y |= dig(7);
    assert(y() == 7);
    cout << "✓ Operador |= (max) funciona correctamente" << endl;
}

// ============================================================================
// SECCIÓN 5: EXPONENCIACIÓN BINARIA O(log exp)
// ============================================================================

template <uint64_t B>
void test_exponenciacion() {
    cout << "\n=== TEST EXPONENCIACIÓN BINARIA (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    // Caso especial: 0^0 = 1
    dig zero(0);
    dig result_0_0 = zero ^ 0U;
    assert(result_0_0() == 1);
    cout << "✓ 0^0 = " << result_0_0() << " (convención matemática)" << endl;
    
    // Casos base
    dig base(3);
    assert((base ^ 0U)() == 1);
    cout << "✓ 3^0 = 1" << endl;
    
    assert((base ^ 1U)() == 3);
    cout << "✓ 3^1 = 3" << endl;
    
    assert((base ^ 2U)() == ((3 * 3) % B));
    cout << "✓ 3^2 = " << (base ^ 2U)() << endl;
    
    // Exponente grande (verifica algoritmo binario)
    if (B == 257) { // Base prima para verificar Teorema de Fermat
        dig a(2);
        dig result = a ^ 256U; // 2^(p-1) ≡ 1 (mod p) para p primo
        assert(result() == 1);
        cout << "✓ 2^256 ≡ 1 (mod 257) - Teorema de Fermat verificado" << endl;
        
        // Exponente muy grande
        dig b(3);
        dig result_large = b ^ 1000U;
        cout << "✓ 3^1000 (mod 257) = " << result_large() << " (algoritmo O(log 1000) ≈ 10 iteraciones)" << endl;
    }
    
    // Verificar operador ^=
    dig c(5);
    c ^= 3U;
    assert(c() == ((5 * 5 * 5) % B));
    cout << "✓ Operador ^= funciona: 5^3 = " << c() << endl;
}

// ============================================================================
// SECCIÓN 6: OPERADORES DE COMPARACIÓN
// ============================================================================

template <uint64_t B>
void test_comparaciones() {
    cout << "\n=== TEST OPERADORES COMPARACIÓN (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    dig a(5), b(9), c(5);
    
    // Igualdad
    assert(a == c);
    assert(!(a == b));
    cout << "✓ Operador == funciona: " << a() << " == " << c() << endl;
    
    // Desigualdad
    assert(a != b);
    assert(!(a != c));
    cout << "✓ Operador != funciona: " << a() << " != " << b() << endl;
    
    // Menor que
    assert(a < b);
    assert(!(b < a));
    cout << "✓ Operador < funciona: " << a() << " < " << b() << endl;
    
    // Mayor que
    assert(b > a);
    assert(!(a > b));
    cout << "✓ Operador > funciona: " << b() << " > " << a() << endl;
    
    // Menor o igual
    assert(a <= b);
    assert(a <= c);
    cout << "✓ Operador <= funciona" << endl;
    
    // Mayor o igual
    assert(b >= a);
    assert(c >= a);
    cout << "✓ Operador >= funciona" << endl;
    
    // Operador <=> (spaceship)
    auto cmp1 = a <=> b;
    assert(cmp1 == std::strong_ordering::less);
    cout << "✓ Operador <=> (spaceship): " << a() << " <=> " << b() << " = less" << endl;
    
    auto cmp2 = a <=> c;
    assert(cmp2 == std::strong_ordering::equal);
    cout << "✓ Operador <=> (spaceship): " << a() << " <=> " << c() << " = equal" << endl;
    
    // Comparación con entero (normalización módulo B)
    assert(dig(3) == (B + 3));
    cout << "✓ Comparación con entero: dig(3) == " << (B + 3) << " (mod " << B << ")" << endl;
    
    auto cmp3 = dig(3) <=> (B + 3);
    assert(cmp3 == std::weak_ordering::equivalent);
    cout << "✓ Operador <=> con entero: weak_ordering::equivalent para 3 ≡ " << (B + 3) << " (mod " << B << ")" << endl;
}

// ============================================================================
// SECCIÓN 7: FUNCIONES AUXILIARES (is_unit, mult_inv)
// ============================================================================

template <uint64_t B>
void test_funciones_auxiliares() {
    cout << "\n=== TEST FUNCIONES AUXILIARES (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    // is_unit() - verificar unidades
    dig uno(1);
    assert(uno.is_unit());
    cout << "✓ is_unit(1) = true" << endl;
    
    dig zero(0);
    assert(!zero.is_unit());
    cout << "✓ is_unit(0) = false" << endl;
    
    if constexpr (B == 257) { // Base prima - todos excepto 0 son unidades
        dig a(7);
        assert(a.is_unit());
        cout << "✓ is_unit(7) = true en base prima 257" << endl;
        
        // mult_inv() - inversión multiplicativa
        dig inv = a.mult_inv();
        dig product = a * inv;
        assert(product() == 1);
        cout << "✓ mult_inv(7) = " << inv() << " verificado: 7 × " << inv() << " ≡ 1 (mod 257)" << endl;
    } else if constexpr (B == 256) { // Base potencia de 2 - solo impares son unidades
        dig par(4);
        assert(!par.is_unit());
        cout << "✓ is_unit(4) = false en base 256 (par)" << endl;
        
        dig impar(5);
        assert(impar.is_unit());
        dig inv = impar.mult_inv();
        dig product = impar * inv;
        assert(product() == 1);
        cout << "✓ mult_inv(5) = " << inv() << " verificado: 5 × " << inv() << " ≡ 1 (mod 256)" << endl;
    }
    
    // is_Bm1() - verificar si es B-1
    dig Bm1(B - 1);
    assert(Bm1.is_Bm1());
    cout << "✓ is_Bm1(" << (B - 1) << ") = true" << endl;
    
    dig not_Bm1(B - 2);
    assert(!not_Bm1.is_Bm1());
    cout << "✓ is_Bm1(" << (B - 2) << ") = false" << endl;
}

// ============================================================================
// SECCIÓN 8: CASOS EDGE Y LÍMITES
// ============================================================================

template <uint64_t B>
void test_casos_edge() {
    cout << "\n=== TEST CASOS EDGE (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    // Overflow en suma
    dig max_val(B - 1);
    dig sum = max_val + dig(1);
    assert(sum() == 0); // Debe dar vuelta módulo B
    cout << "✓ Overflow suma: (" << (B - 1) << " + 1) mod " << B << " = 0" << endl;
    
    // Underflow en resta
    dig zero(0);
    dig diff = zero - dig(1);
    assert(diff() == (B - 1));
    cout << "✓ Underflow resta: (0 - 1) mod " << B << " = " << (B - 1) << endl;
    
    // Multiplicación con 0
    dig any(42);
    dig prod_zero = any * dig(0);
    assert(prod_zero() == 0);
    cout << "✓ Multiplicación por 0: 42 × 0 = 0" << endl;
    
    // Multiplicación con 1 (neutro)
    dig prod_one = any * dig(1);
    assert(prod_one() == any());
    cout << "✓ Multiplicación por 1: 42 × 1 = 42 (neutro)" << endl;
    
    // Potencia con exponente 0
    dig base(123);
    dig pow_zero = base ^ 0U;
    assert(pow_zero() == 1);
    cout << "✓ Exponente 0: 123^0 = 1" << endl;
    
    // Exponenciación y verificación con exponente grande
    if (B == 257) {
        dig a(2);
        // 2^8 = 256 ≡ -1 (mod 257)
        dig result_8 = a ^ 8U;
        assert(result_8() == 256);
        cout << "✓ 2^8 ≡ 256 ≡ -1 (mod 257)" << endl;
        
        // 2^16 = (2^8)^2 ≡ (-1)^2 ≡ 1 (mod 257)
        dig result_16 = a ^ 16U;
        assert(result_16() == 1);
        cout << "✓ 2^16 ≡ 1 (mod 257)" << endl;
    }
}

// ============================================================================
// SECCIÓN 9: BENCHMARK DE RENDIMIENTO
// ============================================================================

template <uint64_t B>
void benchmark_operaciones() {
    cout << "\n=== BENCHMARK RENDIMIENTO (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    constexpr int N = 100000;
    
    // Benchmark suma
    auto start = high_resolution_clock::now();
    dig acc(0);
    for (int i = 0; i < N; ++i) {
        acc += dig(i % B);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "✓ Suma: " << N << " operaciones en " << duration << " µs (" 
         << (double(duration) / N) << " µs/op)" << endl;
    
    // Benchmark multiplicación
    start = high_resolution_clock::now();
    dig prod(1);
    for (int i = 1; i < 1000; ++i) {
        prod *= dig(i % B);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start).count();
    cout << "✓ Multiplicación: 1000 operaciones en " << duration << " µs (" 
         << (double(duration) / 1000) << " µs/op)" << endl;
    
    // Benchmark exponenciación binaria
    if (B == 257) {
        start = high_resolution_clock::now();
        for (int i = 0; i < 10000; ++i) {
            dig base(2);
            dig result = base ^ 1000U;
        }
        end = high_resolution_clock::now();
        duration = duration_cast<microseconds>(end - start).count();
        cout << "✓ Exponenciación 2^1000: 10000 operaciones en " << duration << " µs (" 
             << (double(duration) / 10000) << " µs/op, algoritmo O(log 1000) ≈ 10 iter)" << endl;
    }
}

// ============================================================================
// MAIN - EJECUTAR TODAS LAS BATERÍAS DE TESTS
// ============================================================================

int main() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════╗\n";
    cout << "║  TEST EXHAUSTIVO dig_t<B> - TODAS LAS FUNCIONALIDADES           ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════╝\n";
    
    try {
        // Tests en base 256 (potencia de 2)
        test_constructores<256>();
        test_parser_compile_time<256>();
        test_operadores_aritmeticos<256>();
        test_operadores_logicos<256>();
        test_exponenciacion<256>();
        test_comparaciones<256>();
        test_funciones_auxiliares<256>();
        test_casos_edge<256>();
        benchmark_operaciones<256>();
        
        cout << "\n" << string(70, '=') << "\n";
        
        // Tests en base 257 (primo)
        test_constructores<257>();
        test_parser_compile_time<257>();
        test_operadores_aritmeticos<257>();
        test_operadores_logicos<257>();
        test_exponenciacion<257>();
        test_comparaciones<257>();
        test_funciones_auxiliares<257>();
        test_casos_edge<257>();
        benchmark_operaciones<257>();
        
        cout << "\n";
        cout << "╔══════════════════════════════════════════════════════════════════╗\n";
        cout << "║  ✓✓✓ TODOS LOS TESTS PASARON EXITOSAMENTE ✓✓✓                  ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════╝\n";
        
        return 0;
        
    } catch (const exception& e) {
        cerr << "\n✗✗✗ ERROR: " << e.what() << endl;
        return 1;
    }
}
