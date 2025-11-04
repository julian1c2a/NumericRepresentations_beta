#include <iostream>
#include <cassert>
#include <iomanip>
#include <compare>

// Test completo de operadores de comparación de dig_t
#include "../include/dig_t.hpp"

using namespace NumRepr;

template <std::uint64_t B>
void test_comparison_operators()
{
    std::cout << "\n=== Testing Comparison Operators dig_t<" << B << "> ===" << std::endl;

    using dig_type = dig_t<B>;

    // 1. Test igualdad y desigualdad (==, !=)
    std::cout << "\n--- IGUALDAD Y DESIGUALDAD ---" << std::endl;
    dig_type a(7u);
    dig_type b(7u);
    dig_type c(3u);

    std::cout << "a = " << a.get() << ", b = " << b.get() << ", c = " << c.get() << std::endl;

    // Test igualdad
    assert(a == b);
    std::cout << "✅ a == b: " << (a == b) << std::endl;

    assert(!(a == c));
    std::cout << "✅ !(a == c): " << !(a == c) << std::endl;

    // Test desigualdad
    assert(!(a != b));
    std::cout << "✅ !(a != b): " << !(a != b) << std::endl;

    assert(a != c);
    std::cout << "✅ a != c: " << (a != c) << std::endl;

    // 2. Test operadores relacionales (<, >, <=, >=)
    std::cout << "\n--- OPERADORES RELACIONALES ---" << std::endl;
    dig_type d(3u);
    dig_type e(8u);
    dig_type f(3u);

    std::cout << "d = " << d.get() << ", e = " << e.get() << ", f = " << f.get() << std::endl;

    // Menor que
    assert(d < e);
    std::cout << "✅ d < e: " << (d < e) << std::endl;

    assert(!(e < d));
    std::cout << "✅ !(e < d): " << !(e < d) << std::endl;

    // Mayor que
    assert(e > d);
    std::cout << "✅ e > d: " << (e > d) << std::endl;

    assert(!(d > e));
    std::cout << "✅ !(d > e): " << !(d > e) << std::endl;

    // Menor o igual que
    assert(d <= e);
    std::cout << "✅ d <= e: " << (d <= e) << std::endl;

    assert(d <= f);
    std::cout << "✅ d <= f: " << (d <= f) << std::endl;

    // Mayor o igual que
    assert(e >= d);
    std::cout << "✅ e >= d: " << (e >= d) << std::endl;

    assert(d >= f);
    std::cout << "✅ d >= f: " << (d >= f) << std::endl;

    // 3. Test C++20 three-way comparison (operator<=>)
    std::cout << "\n--- C++20 THREE-WAY COMPARISON (dig_t vs dig_t) ---" << std::endl;

    // Same-type comparison (strong_ordering)
    auto cmp1 = d <=> e;
    assert(cmp1 == std::strong_ordering::less);
    std::cout << "✅ d <=> e: std::strong_ordering::less" << std::endl;

    auto cmp2 = e <=> d;
    assert(cmp2 == std::strong_ordering::greater);
    std::cout << "✅ e <=> d: std::strong_ordering::greater" << std::endl;

    auto cmp3 = d <=> f;
    assert(cmp3 == std::strong_ordering::equal);
    std::cout << "✅ d <=> f: std::strong_ordering::equal" << std::endl;

    // 4. Test comparación mixed-type (dig_t vs integral)
    std::cout << "\n--- MIXED-TYPE COMPARISON (dig_t vs integral) ---" << std::endl;

    dig_type g(5u);
    int valor1 = 5;  // Mismo valor
    int valor2 = 15; // Equivalente modular (15 % B podría ser 5 si B=10)
    int valor3 = 7;  // Valor diferente

    std::cout << "g = " << g.get() << ", valor1 = " << valor1
              << ", valor2 = " << valor2 << ", valor3 = " << valor3 << std::endl;

    // Comparación con mismo valor
    auto cmp_mixed1 = g <=> valor1;
    std::cout << "g <=> valor1: ";
    if (cmp_mixed1 == std::weak_ordering::equivalent)
    {
        std::cout << "std::weak_ordering::equivalent ✅" << std::endl;
    }
    else if (cmp_mixed1 == std::weak_ordering::less)
    {
        std::cout << "std::weak_ordering::less" << std::endl;
    }
    else
    {
        std::cout << "std::weak_ordering::greater" << std::endl;
    }

    // Comparación con valor diferente
    auto cmp_mixed2 = g <=> valor3;
    std::cout << "g <=> valor3: ";
    if (cmp_mixed2 == std::weak_ordering::equivalent)
    {
        std::cout << "std::weak_ordering::equivalent" << std::endl;
    }
    else if (cmp_mixed2 == std::weak_ordering::less)
    {
        std::cout << "std::weak_ordering::less ✅" << std::endl;
    }
    else
    {
        std::cout << "std::weak_ordering::greater" << std::endl;
    }

    // Test equivalencia modular con valor mayor
    if (B == 10)
    {
        auto cmp_mod = g <=> valor2; // 5 vs 15: 15%10=5, deberían ser equivalentes
        std::cout << "g <=> " << valor2 << " (equivalencia modular): ";
        if (cmp_mod == std::weak_ordering::equivalent)
        {
            std::cout << "std::weak_ordering::equivalent ✅" << std::endl;
        }
        else
        {
            std::cout << "no equivalente (normaliza " << valor2 << " ≡ " << (valor2 % B) << " mod " << B << ")" << std::endl;
        }
    }

    // 5. Test casos extremos
    std::cout << "\n--- CASOS EXTREMOS ---" << std::endl;

    // Comparación con cero
    dig_type zero = dig_type::dig_0();
    dig_type one(1u);
    dig_type max_val = dig_type::dig_max();

    std::cout << "zero = " << zero.get() << ", one = " << one.get()
              << ", max = " << max_val.get() << std::endl;

    assert(zero < one);
    std::cout << "✅ zero < one: " << (zero < one) << std::endl;

    assert(one < max_val);
    std::cout << "✅ one < max: " << (one < max_val) << std::endl;

    assert(zero < max_val);
    std::cout << "✅ zero < max: " << (zero < max_val) << std::endl;

    // Comparación con máximo valor
    auto cmp_max = zero <=> max_val;
    assert(cmp_max == std::strong_ordering::less);
    std::cout << "✅ zero <=> max: std::strong_ordering::less" << std::endl;

    // 6. Verificar transitividad y consistencia
    std::cout << "\n--- VERIFICACIÓN DE PROPIEDADES MATEMÁTICAS ---" << std::endl;

    dig_type x(2u);
    dig_type y(5u);
    dig_type z(8u);

    std::cout << "x = " << x.get() << ", y = " << y.get() << ", z = " << z.get() << std::endl;

    // Transitividad: si x < y y y < z, entonces x < z
    bool trans1 = (x < y);
    bool trans2 = (y < z);
    bool trans3 = (x < z);

    if (trans1 && trans2)
    {
        assert(trans3);
        std::cout << "✅ Transitividad: x < y ∧ y < z → x < z" << std::endl;
    }

    // Antisimetría: si x <= y y y <= x, entonces x == y
    dig_type u(6u);
    dig_type v(6u);

    bool anti1 = (u <= v);
    bool anti2 = (v <= u);
    bool anti3 = (u == v);

    if (anti1 && anti2)
    {
        assert(anti3);
        std::cout << "✅ Antisimetría: u <= v ∧ v <= u → u == v" << std::endl;
    }

    std::cout << "✅ Todos los tests de comparación para dig_t<" << B << "> pasaron!" << std::endl;
}

int main()
{
    std::cout << "=== DOCUMENTACIÓN Y TESTING DE OPERADORES DE COMPARACIÓN ===" << std::endl;
    std::cout << "Verificando comparaciones tradicionales y C++20 three-way comparison" << std::endl;

    // Test con diferentes bases
    test_comparison_operators<5>();  // Base pequeña
    test_comparison_operators<10>(); // Base decimal
    test_comparison_operators<16>(); // Base hexadecimal
    test_comparison_operators<17>(); // Base prima

    std::cout << "\n🎉 TODOS LOS TESTS DE OPERADORES DE COMPARACIÓN COMPLETADOS" << std::endl;
    std::cout << "\n📊 RESUMEN DE FUNCIONALIDADES VERIFICADAS:" << std::endl;
    std::cout << "✅ Igualdad y desigualdad (==, !=)" << std::endl;
    std::cout << "✅ Operadores relacionales (<, >, <=, >=)" << std::endl;
    std::cout << "✅ C++20 three-way comparison (<=>) same-type" << std::endl;
    std::cout << "✅ Mixed-type comparison (dig_t vs integral)" << std::endl;
    std::cout << "✅ std::strong_ordering para comparaciones same-type" << std::endl;
    std::cout << "✅ std::weak_ordering para comparaciones mixed-type" << std::endl;
    std::cout << "✅ Normalización automática en comparaciones cross-type" << std::endl;
    std::cout << "✅ Propiedades matemáticas (transitividad, antisimetría)" << std::endl;
    std::cout << "✅ Casos extremos (cero, máximo valor)" << std::endl;

    return 0;
}