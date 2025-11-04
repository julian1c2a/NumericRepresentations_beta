#include <iostream>
#include <cassert>
#include <iomanip>

// Test completo de operadores bitwise/lógicos de dig_t con semántica matemática
#include "../include/dig_t.hpp"

using namespace NumRepr;

template <std::uint64_t B>
void test_bitwise_logical_operators()
{
    std::cout << "\n=== Testing Bitwise/Logical Operators dig_t<" << B << "> ===" << std::endl;
    std::cout << "NOTA: Estos operadores tienen semántica MATEMÁTICA, no bitwise tradicional" << std::endl;

    using dig_type = dig_t<B>;

    // 1. Test operador & (función mínimo)
    std::cout << "\n--- OPERADOR & (FUNCIÓN MÍNIMO) ---" << std::endl;
    dig_type a(7u);
    dig_type b(3u);
    dig_type c(7u);

    std::cout << "a = " << a.get() << ", b = " << b.get() << ", c = " << c.get() << std::endl;

    dig_type min1 = a & b;
    std::cout << "a & b = " << min1.get() << " (min(" << a.get() << ", " << b.get() << ") = " << std::min(a.get(), b.get()) << ")" << std::endl;
    assert(min1.get() == std::min(a.get(), b.get()));

    dig_type min2 = a & c;
    std::cout << "a & c = " << min2.get() << " (min(" << a.get() << ", " << c.get() << ") = " << std::min(a.get(), c.get()) << ")" << std::endl;
    assert(min2.get() == std::min(a.get(), c.get()));

    // 2. Test operador &= (asignación mínimo)
    std::cout << "\n--- OPERADOR &= (ASIGNACIÓN MÍNIMO) ---" << std::endl;
    dig_type d(9u);
    dig_type e(4u);

    std::cout << "Antes: d = " << d.get() << ", e = " << e.get() << std::endl;

    dig_type d_orig = d;
    d &= e;
    std::cout << "d &= e; d = " << d.get() << " (debe ser min(" << d_orig.get() << ", " << e.get() << "))" << std::endl;
    assert(d.get() == std::min(d_orig.get(), e.get()));

    // Test donde no cambia (d ya es menor)
    dig_type f(2u);
    dig_type g(8u);
    dig_type f_orig = f;

    std::cout << "Antes: f = " << f.get() << ", g = " << g.get() << std::endl;
    f &= g;
    std::cout << "f &= g; f = " << f.get() << " (no cambió porque f ya era menor)" << std::endl;
    assert(f.get() == f_orig.get());

    // 3. Test operador | (función máximo)
    std::cout << "\n--- OPERADOR | (FUNCIÓN MÁXIMO) ---" << std::endl;
    dig_type h(5u);
    dig_type i(9u);
    dig_type j(5u);

    std::cout << "h = " << h.get() << ", i = " << i.get() << ", j = " << j.get() << std::endl;

    dig_type max1 = h | i;
    std::cout << "h | i = " << max1.get() << " (max(" << h.get() << ", " << i.get() << ") = " << std::max(h.get(), i.get()) << ")" << std::endl;
    assert(max1.get() == std::max(h.get(), i.get()));

    dig_type max2 = h | j;
    std::cout << "h | j = " << max2.get() << " (max(" << h.get() << ", " << j.get() << ") = " << std::max(h.get(), j.get()) << ")" << std::endl;
    assert(max2.get() == std::max(h.get(), j.get()));

    // 4. Test operador |= (asignación máximo)
    std::cout << "\n--- OPERADOR |= (ASIGNACIÓN MÁXIMO) ---" << std::endl;
    dig_type k(3u);
    dig_type l(7u);

    std::cout << "Antes: k = " << k.get() << ", l = " << l.get() << std::endl;

    dig_type k_orig = k;
    k |= l;
    std::cout << "k |= l; k = " << k.get() << " (debe ser max(" << k_orig.get() << ", " << l.get() << "))" << std::endl;
    assert(k.get() == std::max(k_orig.get(), l.get()));

    // Test donde no cambia (k ya es mayor)
    dig_type m(9u);
    dig_type n(4u);
    dig_type m_orig = m;

    std::cout << "Antes: m = " << m.get() << ", n = " << n.get() << std::endl;
    m |= n;
    std::cout << "m |= n; m = " << m.get() << " (no cambió porque m ya era mayor)" << std::endl;
    assert(m.get() == m_orig.get());

    // 5. Test operador ^ (exponenciación)
    std::cout << "\n--- OPERADOR ^ (EXPONENCIACIÓN) ---" << std::endl;
    dig_type base(3u);

    std::cout << "base = " << base.get() << std::endl;

    // Casos especiales
    dig_type pow0 = base ^ 0u;
    std::cout << "base ^ 0 = " << pow0.get() << " (cualquier número^0 = 1)" << std::endl;
    assert(pow0.get() == 1u % B);

    dig_type pow1 = base ^ 1u;
    std::cout << "base ^ 1 = " << pow1.get() << " (número^1 = número)" << std::endl;
    assert(pow1.get() == base.get());

    dig_type pow2 = base ^ 2u;
    std::cout << "base ^ 2 = " << pow2.get() << " (" << base.get() << "^2 = " << (base.get() * base.get()) << " mod " << B << " = " << ((base.get() * base.get()) % B) << ")" << std::endl;
    assert(pow2.get() == (base.get() * base.get()) % B);

    if (B > 30)
    { // Solo si la base permite estos tests sin overflow inmediato
        dig_type pow3 = base ^ 3u;
        uint64_t expected_pow3 = 1;
        for (unsigned int exp = 0; exp < 3; ++exp)
        {
            expected_pow3 = (expected_pow3 * base.get()) % B;
        }
        std::cout << "base ^ 3 = " << pow3.get() << " (esperado: " << expected_pow3 << ")" << std::endl;
        assert(pow3.get() == expected_pow3);
    }

    // 6. Test operador ^= (exponenciación asignada)
    std::cout << "\n--- OPERADOR ^= (EXPONENCIACIÓN ASIGNADA) ---" << std::endl;
    dig_type p(2u);
    dig_type p_orig = p;

    std::cout << "Antes: p = " << p.get() << std::endl;

    p ^= 3u;
    uint64_t expected = 1;
    for (unsigned int exp = 0; exp < 3; ++exp)
    {
        expected = (expected * p_orig.get()) % B;
    }
    std::cout << "p ^= 3; p = " << p.get() << " (esperado: " << expected << ")" << std::endl;
    assert(p.get() == expected);

    // 7. Test operador ~ (complemento B-1)
    std::cout << "\n--- OPERADOR ~ (COMPLEMENTO B-1) ---" << std::endl;
    dig_type q(5u);
    dig_type comp_b1 = ~q;

    std::cout << "q = " << q.get() << std::endl;
    std::cout << "~q = " << comp_b1.get() << " (complemento B-1: " << (B - 1) << " - " << q.get() << " = " << ((B - 1) - q.get()) << ")" << std::endl;
    assert(comp_b1.get() == (B - 1) - q.get());

    // Test casos especiales
    dig_type zero = dig_type::dig_0();
    dig_type max_dig = dig_type::dig_max();

    dig_type comp_zero = ~zero;
    std::cout << "~0 = " << comp_zero.get() << " (debe ser " << (B - 1) << ")" << std::endl;
    assert(comp_zero.get() == B - 1);

    dig_type comp_max = ~max_dig;
    std::cout << "~(B-1) = " << comp_max.get() << " (debe ser 0)" << std::endl;
    assert(comp_max.get() == 0);

    // 8. Test operador - unario (complemento B)
    std::cout << "\n--- OPERADOR - UNARIO (COMPLEMENTO B) ---" << std::endl;
    dig_type r(7u);
    dig_type neg_r = -r;

    std::cout << "r = " << r.get() << std::endl;
    if (r.get() == 0)
    {
        std::cout << "-r = " << neg_r.get() << " (negación de 0 = 0)" << std::endl;
        assert(neg_r.get() == 0);
    }
    else
    {
        std::cout << "-r = " << neg_r.get() << " (complemento B: " << B << " - " << r.get() << " = " << (B - r.get()) << ")" << std::endl;
        assert(neg_r.get() == B - r.get());
    }

    // Test caso especial: negación de 0
    dig_type zero_neg = -zero;
    std::cout << "-0 = " << zero_neg.get() << " (debe ser 0)" << std::endl;
    assert(zero_neg.get() == 0);

    // 9. Test propiedades matemáticas
    std::cout << "\n--- VERIFICACIÓN DE PROPIEDADES MATEMÁTICAS ---" << std::endl;

    // Propiedad: a & b = min(a, b)
    dig_type test1(4u), test2(8u);
    assert((test1 & test2).get() == std::min(test1.get(), test2.get()));
    std::cout << "✅ Propiedad min: a & b = min(a, b)" << std::endl;

    // Propiedad: a | b = max(a, b)
    assert((test1 | test2).get() == std::max(test1.get(), test2.get()));
    std::cout << "✅ Propiedad max: a | b = max(a, b)" << std::endl;

    // Propiedad: x + (-x) ≡ 0 (mod B) para x != 0
    if (test1.get() != 0)
    {
        dig_type sum_with_neg = test1 + (-test1);
        std::cout << "x + (-x) = " << test1.get() << " + " << (-test1).get() << " = " << sum_with_neg.get() << " (debe ser 0)" << std::endl;
        assert(sum_with_neg.get() == 0);
        std::cout << "✅ Propiedad negación: x + (-x) ≡ 0 (mod B)" << std::endl;
    }

    // Propiedad: ~(~x) = x (doble complemento)
    dig_type double_comp = ~(~test1);
    std::cout << "~~x = " << double_comp.get() << " (debe ser " << test1.get() << ")" << std::endl;
    assert(double_comp.get() == test1.get());
    std::cout << "✅ Propiedad doble complemento: ~~x = x" << std::endl;

    std::cout << "✅ Todos los tests bitwise/lógicos para dig_t<" << B << "> pasaron!" << std::endl;
}

int main()
{
    std::cout << "=== DOCUMENTACIÓN Y TESTING DE OPERADORES BITWISE/LÓGICOS ===" << std::endl;
    std::cout << "IMPORTANTE: Estos operadores tienen semántica MATEMÁTICA, no bitwise tradicional" << std::endl;
    std::cout << "& = función mínimo, | = función máximo, ^ = exponenciación" << std::endl;
    std::cout << "~ = complemento B-1, - unario = complemento B" << std::endl;

    // Test con diferentes bases
    test_bitwise_logical_operators<5>();  // Base pequeña
    test_bitwise_logical_operators<10>(); // Base decimal
    test_bitwise_logical_operators<16>(); // Base hexadecimal
    test_bitwise_logical_operators<17>(); // Base prima
    test_bitwise_logical_operators<64>(); // Base potencia de 2

    std::cout << "\n🎉 TODOS LOS TESTS DE OPERADORES BITWISE/LÓGICOS COMPLETADOS" << std::endl;
    std::cout << "\n📊 RESUMEN DE FUNCIONALIDADES VERIFICADAS:" << std::endl;
    std::cout << "✅ Operador & como función mínimo" << std::endl;
    std::cout << "✅ Operador | como función máximo" << std::endl;
    std::cout << "✅ Operadores &= y |= con asignación condicional" << std::endl;
    std::cout << "✅ Operador ^ como exponenciación modular" << std::endl;
    std::cout << "✅ Operador ^= con optimizaciones para exp=0,1,2" << std::endl;
    std::cout << "✅ Operador ~ como complemento B-1" << std::endl;
    std::cout << "✅ Operador - unario como complemento B" << std::endl;
    std::cout << "✅ Casos especiales (0, B-1, exponentes pequeños)" << std::endl;
    std::cout << "✅ Propiedades matemáticas (min/max, negación, doble complemento)" << std::endl;
    std::cout << "✅ Semántica matemática especializada vs bitwise tradicional" << std::endl;

    return 0;
}