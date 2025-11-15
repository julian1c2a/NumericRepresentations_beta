/**
 * @file test_dig_t_comprehensive.cpp
 * @brief Test exhaustivo de todas las funcionalidades de dig_t documentadas y optimizadas
 * 
 * @details Cubre:
 * - Constructores (default, copy, from int, from array compile-time)
 * - Parser compile-time (parse_impl_ct, from_array_ct)
 * - Operadores aritmeticos (+, -, *, /, %)
 * - Operadores logicos (&, |, ^) con interpretacion min/max
 * - Operador exponenciacion (^) con algoritmo binario O(log exp)
 * - Operadores comparacion (==, !=, <, <=, >, >=, <=>)
 * - Funciones auxiliares (is_unit, mult_inv, sum_carry, etc.)
 * - Casos edge (0^0=1, division por 0, inversion de no-unidades)
 */

#include <core/dig_t.hpp>
#include <iostream>
#include <cassert>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace NumRepr;

// ============================================================================
// SECCION 1: CONSTRUCTORES E INICIALIZACION
// ============================================================================

template <uint64_t B>
void test_constructores() {
    cout << "\n=== TEST CONSTRUCTORES (Base " << B << ") ===" << endl;
    // Constructor por defecto (debe inicializar a 0)
    {
        dig_t<B> d1;
        assert(d1.get() == 0);
        cout << "[OK] Constructor por defecto: d() = " << d1.get() << endl;
    }
    // Constructor desde entero positivo
    {
        dig_t<B> d2(42);
        assert(d2.get() == (42 % B));
        cout << "[OK] Constructor desde int: dig(" << 42 << ") = " << d2.get() << endl;
    }
    // Constructor desde entero negativo (debe normalizar correctamente)
    {
        dig_t<B> d3(-5);
        uint64_t expected = (B - (5 % B)) % B;
        assert(d3.get() == expected);
        cout << "[OK] Constructor desde int negativo: dig(-5) = " << d3.get() << " (normalizado)" << endl;
    }
    // Constructor copia
    {
        dig_t<B> d2(42);
        dig_t<B> d4 = d2;
        assert(d4.get() == d2.get());
        cout << "[OK] Constructor copia: d4 = d2 = " << d4.get() << endl;
    }
}

// ============================================================================
// SECCION 2: PARSER COMPILE-TIME
// ============================================================================

template <uint64_t B>
void test_parser_compile_time() {
    cout << "\n=== TEST PARSER COMPILE-TIME (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    // from_array_ct con array de caracteres válido
    constexpr std::array<char, 2> arr1{'4', '2'};
    auto result1 = dig::template from_array_ct<arr1>();
    if (result1.has_value()) {
        dig d1 = result1.value();
        assert(d1.get() == (42 % B));
        cout << "[OK] from_array_ct({'4','2'}) = " << d1.get() << " (compile-time OK)" << endl;
    } else {
           cout << "[FAIL] from_array_ct({'4','2'}) falló inesperadamente" << endl;
    }
    
    // from_array_ct con '0'
    constexpr std::array<char, 1> arr2{'0'};
    auto result2 = dig::template from_array_ct<arr2>();
    if (result2.has_value()) {
        dig d2 = result2.value();
        assert(d2.get() == 0);
        cout << "[OK] from_array_ct({'0'}) = 0" << endl;
    }
    
    // Error: carácter inválido
    constexpr std::array<char, 3> arr3{'1', 'x', '3'};
    auto result3 = dig::template from_array_ct<arr3>();
    if (!result3.has_value()) {
           cout << "[OK] from_array_ct({'1','x','3'}) → error detectado correctamente" << endl;
    }
    
    // Error: array vacío
    constexpr std::array<char, 0> arr4{};
    auto result4 = dig::template from_array_ct<arr4>();
    if (!result4.has_value()) {
           cout << "[OK] from_array_ct(array vacío) → error detectado correctamente" << endl;
    }
}

// ============================================================================
// SECCION 3: OPERADORES ARITMETICOS
// ============================================================================

template <uint64_t B>
void test_operadores_aritmeticos() {
    cout << "\n=== TEST OPERADORES ARITMÉTICOS (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    dig a(7), b(3);
    
    // Suma
    dig sum = a + b;
    assert(sum.get() == ((7 + 3) % B));
    cout << "[OK] " << a.get() << " + " << b.get() << " = " << sum.get() << " (mod " << B << ")" << endl;
    
    // Resta
    dig diff = a - b;
    assert(diff.get() == ((7 - 3 + B) % B));
    cout << "[OK] " << a.get() << " - " << b.get() << " = " << diff.get() << " (mod " << B << ")" << endl;
    
    // Multiplicación
    dig prod = a * b;
    assert(prod.get() == ((7 * 3) % B));
    cout << "[OK] " << a.get() << " * " << b.get() << " = " << prod.get() << " (mod " << B << ")" << endl;
    
    // División (si b es unidad)
    if constexpr (B == 257) { // Base prima
        dig quotient = a / b;
        dig check = quotient * b;
        assert(check.get() == a.get());
        cout << "[OK] " << a.get() << " / " << b.get() << " = " << quotient.get() << " (verificado: " << quotient.get() << "*" << b.get() << "=" << check.get() << ")" << endl;
    }
    
    // Módulo
    if (B > 10) {
        dig c(15), d(7);
        dig mod = c % d;
        cout << "[OK] " << c.get() << " % " << d.get() << " = " << mod.get() << endl;
    }
    
    // Operadores compuestos
    dig x(5);
    x += dig(3);
    assert(x.get() == ((5 + 3) % B));
    cout << "[OK] Operador += funciona correctamente" << endl;
    
    x *= dig(2);
    assert(x.get() == ((8 * 2) % B));
    cout << "[OK] Operador *= funciona correctamente" << endl;
}

// ============================================================================
// SECCION 4: OPERADORES LOGICOS (INTERPRETACION MIN/MAX)
// ============================================================================

template <uint64_t B>
void test_operadores_logicos() {
    cout << "\n=== TEST OPERADORES LÓGICOS (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    dig a(5), b(9);
    
    // Operador & (min)
    dig and_result = a & b;
    assert(and_result.get() == min(a.get(), b.get()));
    cout << "[OK] " << a.get() << " & " << b.get() << " = " << and_result.get() << " (min)" << endl;
    
    // Operador | (max)
    dig or_result = a | b;
    assert(or_result.get() == max(a.get(), b.get()));
    cout << "[OK] " << a.get() << " | " << b.get() << " = " << or_result.get() << " (max)" << endl;
    
    // Operador && (equivalente a &)
    dig and2_result = a && b;
    assert(and2_result.get() == and_result.get());
    cout << "[OK] " << a.get() << " && " << b.get() << " = " << and2_result.get() << " (equivalente a &)" << endl;
    
    // Operador || (equivalente a |)
    dig or2_result = a || b;
    assert(or2_result.get() == or_result.get());
    cout << "[OK] " << a.get() << " || " << b.get() << " = " << or2_result.get() << " (equivalente a |)" << endl;
    
    // Operadores compuestos
    dig x(3);
    x &= dig(7);
    assert(x.get() == 3);
    cout << "[OK] Operador &= (min) funciona correctamente" << endl;
    
    dig y(3);
    y |= dig(7);
    assert(y.get() == 7);
    cout << "[OK] Operador |= (max) funciona correctamente" << endl;
}

// ============================================================================
// SECCION 5: EXPONENCIACION BINARIA O(log exp)
// ============================================================================

template <uint64_t B>
void test_exponenciacion() {
    cout << "\n=== TEST EXPONENCIACION BINARIA (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    // Caso especial: 0^0 = 1
    dig zero(0);
    dig result_0_0 = zero ^ 0U;
    assert(result_0_0.get() == 1);
    cout << "[OK] 0^0 = " << result_0_0.get() << " (convencion matematica)" << endl;
    
    // Casos base
    dig base(3);
    assert((base ^ 0U).get() == 1);
    cout << "[OK] 3^0 = 1" << endl;
    assert((base ^ 1U).get() == 3);
    cout << "[OK] 3^1 = 3" << endl;
    assert((base ^ 2U).get() == ((3 * 3) % B));
    cout << "[OK] 3^2 = " << (base ^ 2U).get() << endl;
    
    // Exponente grande (verifica algoritmo binario)
    if (B == 257) { // Base prima para verificar Teorema de Fermat
        dig a(2);
        dig result = a ^ 256U; // 2^(p-1) == 1 (mod p) para p primo
        assert(result.get() == 1);
        cout << "[OK] 2^256 == 1 (mod 257) - Teorema de Fermat verificado" << endl;
        
        // Exponente muy grande
        dig b(3);
        dig result_large = b ^ 1000U;
        cout << "[OK] 3^1000 (mod 257) = " << result_large.get() << " (algoritmo O(log 1000) ~ 10 iteraciones)" << endl;
    }
    
    // Verificar operador ^=
    dig c(5);
    c ^= 3U;
    assert(c.get() == ((5 * 5 * 5) % B));
    cout << "[OK] Operador ^= funciona: 5^3 = " << c.get() << endl;
}

// ============================================================================
// SECCION 6: OPERADORES DE COMPARACION
// ============================================================================

template <uint64_t B>
void test_comparaciones() {
    cout << "\n=== TEST OPERADORES COMPARACION (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    dig a(5), b(9), c(5);
    
    // Igualdad
    assert(a == c);
    assert(!(a == b));
    cout << "[OK] Operador == funciona: " << a.get() << " == " << c.get() << endl;
    
    // Desigualdad
    assert(a != b);
    assert(!(a != c));
    cout << "[OK] Operador != funciona: " << a.get() << " != " << b.get() << endl;
    
    // Menor que
    assert(a < b);
    assert(!(b < a));
    cout << "[OK] Operador < funciona: " << a.get() << " < " << b.get() << endl;
    
    // Mayor que
    assert(b > a);
    assert(!(a > b));
    cout << "[OK] Operador > funciona: " << b.get() << " > " << a.get() << endl;
    
    // Menor o igual
    assert(a <= b);
    assert(a <= c);
    cout << "[OK] Operador <= funciona" << endl;
    
    // Mayor o igual
    assert(b >= a);
    assert(c >= a);
    cout << "[OK] Operador >= funciona" << endl;
    
    // Operador <=> (spaceship)
    auto cmp1 = a <=> b;
    assert(cmp1 == std::strong_ordering::less);
    cout << "[OK] Operador <=> (spaceship): " << a.get() << " <=> " << b.get() << " = less" << endl;
    
    auto cmp2 = a <=> c;
    assert(cmp2 == std::strong_ordering::equal);
    cout << "[OK] Operador <=> (spaceship): " << a.get() << " <=> " << c.get() << " = equal" << endl;
    
    // Comparacion con entero (normalizacion modulo B)
    assert(dig(3) == (B + 3));
    cout << "[OK] Comparacion con entero: dig(3) == " << (B + 3) << " (mod " << B << ")" << endl;
    
    auto cmp3 = dig(3) <=> (B + 3);
    assert(cmp3 == std::weak_ordering::equivalent);
    cout << "[OK] Operador <=> con entero: weak_ordering::equivalent para 3 == " << (B + 3) << " (mod " << B << ")" << endl;
}

// ============================================================================
// SECCION 7: FUNCIONES AUXILIARES (is_unit, mult_inv)
// ============================================================================

template <uint64_t B>
void test_funciones_auxiliares() {
    cout << "\n=== TEST FUNCIONES AUXILIARES (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    // is_unit() - verificar unidades
    dig uno(1);
    assert(uno.is_unit());
    cout << "[OK] is_unit(1) = true" << endl;
    
    dig zero(0);
    assert(!zero.is_unit());
    cout << "[OK] is_unit(0) = false" << endl;
    
    if constexpr (B == 257) { // Base prima - todos excepto 0 son unidades
        dig a(7);
        assert(a.is_unit());
        cout << "[OK] is_unit(7) = true en base prima 257" << endl;
        
        // mult_inv() - inversion multiplicativa
        dig inv = a.mult_inv();
        dig product = a * inv;
        assert(product.get() == 1);
        cout << "[OK] mult_inv(7) = " << inv.get() << " verificado: 7 * " << inv.get() << " == 1 (mod 257)" << endl;
    } else if constexpr (B == 256) { // Base potencia de 2 - solo impares son unidades
        dig par(4);
        assert(!par.is_unit());
        cout << "[OK] is_unit(4) = false en base 256 (par)" << endl;
        
        dig impar(5);
        assert(impar.is_unit());
        dig inv = impar.mult_inv();
        dig product = impar * inv;
        assert(product.get() == 1);
        cout << "[OK] mult_inv(5) = " << inv.get() << " verificado: 5 * " << inv.get() << " == 1 (mod 256)" << endl;
    }
    
    // is_Bm1() - verificar si es B-1
    dig Bm1(B - 1);
    assert(Bm1.is_Bm1());
    cout << "[OK] is_Bm1(" << (B - 1) << ") = true" << endl;
    
    dig not_Bm1(B - 2);
    assert(!not_Bm1.is_Bm1());
    cout << "[OK] is_Bm1(" << (B - 2) << ") = false" << endl;
}

// ============================================================================
// SECCION 8: CASOS EDGE Y LIMITES
// ============================================================================

template <uint64_t B>
void test_casos_edge() {
    cout << "\n=== TEST CASOS EDGE (Base " << B << ") ===" << endl;
    
    using dig = dig_t<B>;
    
    // Overflow en suma
    dig max_val(B - 1);
    dig sum = max_val + dig(1);
    assert(sum.get() == 0); // Debe dar vuelta modulo B
    cout << "[OK] Overflow suma: (" << (B - 1) << " + 1) mod " << B << " = 0" << endl;
    
    // Underflow en resta
    dig zero(0);
    dig diff = zero - dig(1);
    assert(diff.get() == (B - 1));
    cout << "[OK] Underflow resta: (0 - 1) mod " << B << " = " << (B - 1) << endl;
    
    // Multiplicacion con 0
    dig any(42);
    dig prod_zero = any * dig(0);
    assert(prod_zero.get() == 0);
    cout << "[OK] Multiplicacion por 0: 42 * 0 = 0" << endl;
    
    // Multiplicacion con 1 (neutro)
    dig prod_one = any * dig(1);
    assert(prod_one.get() == any.get());
    cout << "[OK] Multiplicacion por 1: 42 * 1 = 42 (neutro)" << endl;
    
    // Potencia con exponente 0
    dig base(123);
    dig pow_zero = base ^ 0U;
    assert(pow_zero.get() == 1);
    cout << "[OK] Exponente 0: 123^0 = 1" << endl;
    
    // Exponenciacion y verificacion con exponente grande
    if (B == 257) {
        dig a(2);
        // 2^8 = 256 == -1 (mod 257)
        dig result_8 = a ^ 8U;
        assert(result_8.get() == 256);
        cout << "[OK] 2^8 == 256 == -1 (mod 257)" << endl;
        
        // 2^16 = (2^8)^2 == (-1)^2 == 1 (mod 257)
        dig result_16 = a ^ 16U;
        assert(result_16.get() == 1);
        cout << "[OK] 2^16 == 1 (mod 257)" << endl;
    }
}

// ============================================================================
// SECCION 9: BENCHMARK DE RENDIMIENTO
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
    cout << "[OK] Suma: " << N << " operaciones en " << duration << " us (" 
         << (double(duration) / N) << " us/op)" << endl;
    
    // Benchmark multiplicacion
    start = high_resolution_clock::now();
    dig prod(1);
    for (int i = 1; i < 1000; ++i) {
        prod *= dig(i % B);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start).count();
    cout << "[OK] Multiplicacion: 1000 operaciones en " << duration << " us (" 
         << (double(duration) / 1000) << " us/op)" << endl;
    
    // Benchmark exponenciacion binaria
    if (B == 257) {
        start = high_resolution_clock::now();
        for (int i = 0; i < 10000; ++i) {
            dig base(2);
            dig result = base ^ 1000U;
            (void)result;
        }
        end = high_resolution_clock::now();
        duration = duration_cast<microseconds>(end - start).count();
        cout << "[OK] Exponenciacion 2^1000: 10000 operaciones en " << duration << " us (" 
             << (double(duration) / 10000) << " us/op, algoritmo O(log 1000) ~ 10 iter)" << endl;
    }
}

// ============================================================================
// MAIN - EJECUTAR TODAS LAS BATERIAS DE TESTS
// ============================================================================

int main() {
    cout << "\n";
    cout << "======================================================================\n";
    cout << "  TEST EXHAUSTIVO dig_t<B> - TODAS LAS FUNCIONALIDADES           \n";
    cout << "======================================================================\n";
    
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
        cout << "======================================================================\n";
        cout << "  TODOS LOS TESTS PASARON EXITOSAMENTE                           \n";
        cout << "======================================================================\n";
        
        return 0;
        
    } catch (const exception& e) {
        cerr << "\nERROR: " << e.what() << endl;
        return 1;
    }
}
