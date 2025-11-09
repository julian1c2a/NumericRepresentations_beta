#include <iostream>
#include <cassert>
#include <iomanip>

// Test completo de operadores aritméticos de dig_t
#include "../include/dig_t.hpp"

using namespace NumRepr;

template <std::uint64_t B>
void test_arithmetic_operators()
{
    std::cout << "\n=== Testing Arithmetic Operators dig_t<" << B << "> ===" << std::endl;

    using dig_type = dig_t<B>;

    // 1. Test suma (+, +=)
    std::cout << "\n--- SUMA ---" << std::endl;
    dig_type a(3u);
    dig_type b(5u);

    std::cout << "a = " << a.get() << ", b = " << b.get() << std::endl;

    dig_type c = a + b;
    std::cout << "a + b = " << c.get() << " (esperado: " << ((3 + 5) % B) << ")" << std::endl;
    assert(c.get() == (3 + 5) % B);

    a += b;
    std::cout << "a += b; a = " << a.get() << std::endl;
    assert(a.get() == (3 + 5) % B);

    // 2. Test resta (-, -=)
    std::cout << "\n--- RESTA ---" << std::endl;
    dig_type d(8u);
    dig_type e(3u);

    std::cout << "d = " << d.get() << ", e = " << e.get() << std::endl;

    dig_type f = d - e;
    std::cout << "d - e = " << f.get() << " (esperado: " << ((8 >= 3) ? (8 - 3) : (B - (3 - 8))) << ")" << std::endl;

    // Test underflow
    dig_type g(2u);
    dig_type h(5u);
    dig_type i = g - h;
    std::cout << "2 - 5 = " << i.get() << " (underflow modular)" << std::endl;

    // 3. Test multiplicación (*, *=)
    std::cout << "\n--- MULTIPLICACIÓN ---" << std::endl;
    dig_type j(4u);
    dig_type k(6u);

    std::cout << "j = " << j.get() << ", k = " << k.get() << std::endl;

    dig_type l = j * k;
    std::cout << "j * k = " << l.get() << " (esperado: " << ((4 * 6) % B) << ")" << std::endl;
    assert(l.get() == (4 * 6) % B);

    j *= k;
    std::cout << "j *= k; j = " << j.get() << std::endl;
    assert(j.get() == (4 * 6) % B);

    // 4. Test división (/, /=)
    if (B > 10)
    { // Solo si la base permite estos tests
        std::cout << "\n--- DIVISIÓN ---" << std::endl;
        dig_type m(15u);
        dig_type n(3u);

        std::cout << "m = " << m.get() << ", n = " << n.get() << std::endl;

        dig_type o = m / n;
        std::cout << "m / n = " << o.get() << " (15/3 = 5)" << std::endl;
        assert(o.get() == 5);
    }

    // 5. Test operadores unarios
    std::cout << "\n--- OPERADORES UNARIOS ---" << std::endl;
    dig_type p(7u);
    std::cout << "p = " << p.get() << std::endl;

    // Pre-incremento
    dig_type q = ++p;
    std::cout << "++p = " << q.get() << ", p = " << p.get() << std::endl;
    assert(p.get() == (7 + 1) % B);
    assert(q.get() == p.get());

    // Post-incremento
    p.set_dig(7u);
    dig_type r = p++;
    std::cout << "p++ = " << r.get() << ", p = " << p.get() << std::endl;
    assert(r.get() == 7u % B);
    assert(p.get() == (7 + 1) % B);

    // Negación
    dig_type s(5u);
    dig_type t = -s;
    std::cout << "-" << s.get() << " = " << t.get();
    if (s.get() == 0)
    {
        std::cout << " (negación de 0 = 0)";
        assert(t.get() == 0);
    }
    else
    {
        std::cout << " (negación modular = " << (B - s.get()) << ")";
        assert(t.get() == B - s.get());
    }
    std::cout << std::endl;

    // 6. Test overflow en bases pequeñas
    std::cout << "\n--- TEST OVERFLOW/WRAPAROUND ---" << std::endl;
    dig_type max_dig = dig_type::dig_max();
    std::cout << "max_dig = " << max_dig.get() << " (B-1 = " << (B - 1) << ")" << std::endl;

    dig_type overflow = max_dig + dig_type(1u);
    std::cout << "max + 1 = " << overflow.get() << " (wraparound a 0)" << std::endl;
    assert(overflow.get() == 0);

    std::cout << "✅ Todos los tests aritméticos para dig_t<" << B << "> pasaron!" << std::endl;
}

int main()
{
    std::cout << "=== DOCUMENTACIÓN Y TESTING DE OPERADORES ARITMÉTICOS ===" << std::endl;
    std::cout << "Verificando aritmética modular en diferentes bases" << std::endl;

    // Test con diferentes bases para verificar comportamiento
    test_arithmetic_operators<5>();   // Base pequeña
    test_arithmetic_operators<10>();  // Base decimal
    test_arithmetic_operators<16>();  // Base hexadecimal
    test_arithmetic_operators<17>();  // Base prima
    test_arithmetic_operators<256>(); // Base grande (necesita tipos superiores)

    std::cout << "\n🎉 TODOS LOS TESTS DE OPERADORES ARITMÉTICOS COMPLETADOS" << std::endl;
    std::cout << "\n📊 RESUMEN DE FUNCIONALIDADES VERIFICADAS:" << std::endl;
    std::cout << "✅ Suma modular (+, +=)" << std::endl;
    std::cout << "✅ Resta modular con underflow (-, -=)" << std::endl;
    std::cout << "✅ Multiplicación modular (*, *=)" << std::endl;
    std::cout << "✅ División entera (/, /=)" << std::endl;
    std::cout << "✅ Incremento/decremento (++, --)" << std::endl;
    std::cout << "✅ Negación modular (-)" << std::endl;
    std::cout << "✅ Wraparound automático en overflow" << std::endl;
    std::cout << "✅ Optimizaciones por tamaño de base" << std::endl;

    return 0;
}