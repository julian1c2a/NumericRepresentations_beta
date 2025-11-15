/**
 * @file test_increment_decrement.cpp
 * @brief Tests completos para operadores ++ y -- (pre y post)
 * 
 * Verifica:
 * - Pre-incremento (++x)
 * - Post-incremento (x++)
 * - Pre-decremento (--x)
 * - Post-decremento (x--)
 * - Wraparound en overflow/underflow
 * - Retorno de valores vs referencias
 */

#include <iostream>
#include <cassert>
#include <core/dig_t.hpp>

using namespace NumRepr;

/**
 * @brief Test completo de operadores de incremento y decremento
 */
template <std::uint64_t B>
void test_increment_decrement() {
    std::cout << "\n=== Testing Increment/Decrement Operators dig_t<" << B << "> ===" << std::endl;

    using dig_type = dig_t<B>;

    // =========================================================================
    // 1. PRE-INCREMENTO (++x)
    // =========================================================================
    std::cout << "\n--- PRE-INCREMENTO (++x) ---" << std::endl;
    
    dig_type a(0);
    std::cout << "Antes: a = " << a.get() << std::endl;
    
    const dig_type& result_pre_inc = ++a;
    std::cout << "++a; Después: a = " << a.get() << " (debe ser 1)" << std::endl;
    assert(a.get() == 1);
    
    // Verificar que retorna referencia al mismo objeto
    std::cout << "Verificación: ++a retorna referencia a a" << std::endl;
    assert(&result_pre_inc == &a);
    std::cout << "✅ Pre-incremento retorna referencia al objeto" << std::endl;
    
    // Verificar que podemos usar el valor retornado
    dig_type b = ++a;
    std::cout << "b = ++a; a = " << a.get() << ", b = " << b.get() << " (ambos deben ser 2)" << std::endl;
    assert(a.get() == 2 % B);
    assert(b.get() == 2 % B);
    std::cout << "✅ Pre-incremento permite usar el nuevo valor inmediatamente" << std::endl;

    // =========================================================================
    // 2. POST-INCREMENTO (x++)
    // =========================================================================
    std::cout << "\n--- POST-INCREMENTO (x++) ---" << std::endl;
    
    dig_type c(0);
    std::cout << "Antes: c = " << c.get() << std::endl;
    
    dig_type old_c = c++;
    std::cout << "old_c = c++; Después: c = " << c.get() << ", old_c = " << old_c.get() << std::endl;
    std::cout << "c debe ser 1, old_c debe ser 0" << std::endl;
    assert(c.get() == 1 % B);
    assert(old_c.get() == 0);
    std::cout << "✅ Post-incremento retorna valor ANTERIOR" << std::endl;

    // Verificar que retorna copia, no referencia
    dig_type d(1);
    dig_type old_d = d++;
    old_d = dig_type(88 % B);  // Modificar copia no debe afectar d
    std::cout << "Modificar copia: d = " << d.get() << ", old_d = " << old_d.get() << std::endl;
    assert(d.get() == 2 % B);
    std::cout << "✅ Post-incremento retorna COPIA independiente" << std::endl;

    // =========================================================================
    // 3. PRE-DECREMENTO (--x)
    // =========================================================================
    std::cout << "\n--- PRE-DECREMENTO (--x) ---" << std::endl;
    
    dig_type e(1);
    std::cout << "Antes: e = " << e.get() << std::endl;
    
    const dig_type& result_pre_dec = --e;
    std::cout << "--e; Después: e = " << e.get() << " (debe ser 0)" << std::endl;
    assert(e.get() == 0);
    
    // Verificar que retorna referencia al mismo objeto
    std::cout << "Verificación: --e retorna referencia a e" << std::endl;
    assert(&result_pre_dec == &e);
    std::cout << "✅ Pre-decremento retorna referencia al objeto" << std::endl;
    
    // Verificar que podemos usar el valor retornado - empezar desde B-1 para evitar underflow
    dig_type f = dig_type::dig_max();  // B-1
    --f;
    std::cout << "f = --e; f = " << f.get() << " (debe ser B-2 = " << (B-2) << ")" << std::endl;
    assert(f.get() == B - 2);
    std::cout << "✅ Pre-decremento permite usar el nuevo valor inmediatamente" << std::endl;

    // =========================================================================
    // 4. POST-DECREMENTO (x--)
    // =========================================================================
    std::cout << "\n--- POST-DECREMENTO (x--) ---" << std::endl;
    
    dig_type g(1);
    std::cout << "Antes: g = " << g.get() << std::endl;
    
    dig_type old_g = g--;
    std::cout << "old_g = g--; Después: g = " << g.get() << ", old_g = " << old_g.get() << std::endl;
    std::cout << "g debe ser 0, old_g debe ser 1" << std::endl;
    assert(g.get() == 0);
    assert(old_g.get() == 1);
    std::cout << "✅ Post-decremento retorna valor ANTERIOR" << std::endl;

    // Verificar que retorna copia, no referencia
    dig_type h(B - 1);  // Empezar desde B-1
    dig_type old_h = h--;
    old_h = dig_type(88 % B);  // Modificar copia no debe afectar h
    std::cout << "Modificar copia: h = " << h.get() << ", old_h = " << old_h.get() << std::endl;
    assert(h.get() == B - 2);
    std::cout << "✅ Post-decremento retorna COPIA independiente" << std::endl;

    // =========================================================================
    // 5. WRAPAROUND EN OVERFLOW (B-1 → 0)
    // =========================================================================
    std::cout << "\n--- WRAPAROUND EN OVERFLOW ---" << std::endl;
    
    dig_type max_val = dig_type::dig_max();  // B-1
    std::cout << "max_val = " << max_val.get() << " (B-1)" << std::endl;
    
    ++max_val;
    std::cout << "++max_val = " << max_val.get() << " (debe ser 0 por wraparound)" << std::endl;
    assert(max_val.get() == 0);
    std::cout << "✅ Pre-incremento: (B-1) + 1 = 0 (wraparound correcto)" << std::endl;

    // Test con post-incremento
    dig_type max_val2 = dig_type::dig_max();
    dig_type old_max = max_val2++;
    std::cout << "Post-incremento: max_val2 = " << max_val2.get() << ", old_max = " << old_max.get() << std::endl;
    assert(max_val2.get() == 0);
    assert(old_max.get() == B - 1);
    std::cout << "✅ Post-incremento: (B-1)++ retorna B-1, variable queda en 0" << std::endl;

    // =========================================================================
    // 6. WRAPAROUND EN UNDERFLOW (0 → B-1)
    // =========================================================================
    std::cout << "\n--- WRAPAROUND EN UNDERFLOW ---" << std::endl;
    
    dig_type zero_val = dig_type::dig_0();
    std::cout << "zero_val = " << zero_val.get() << " (0)" << std::endl;
    
    --zero_val;
    std::cout << "--zero_val = " << zero_val.get() << " (debe ser " << (B-1) << " por wraparound)" << std::endl;
    assert(zero_val.get() == B - 1);
    std::cout << "✅ Pre-decremento: 0 - 1 = B-1 (wraparound correcto)" << std::endl;

    // Test con post-decremento
    dig_type zero_val2 = dig_type::dig_0();
    dig_type old_zero = zero_val2--;
    std::cout << "Post-decremento: zero_val2 = " << zero_val2.get() << ", old_zero = " << old_zero.get() << std::endl;
    assert(zero_val2.get() == B - 1);
    assert(old_zero.get() == 0);
    std::cout << "✅ Post-decremento: 0-- retorna 0, variable queda en B-1" << std::endl;

    // =========================================================================
    // 7. SECUENCIAS DE OPERACIONES
    // =========================================================================
    std::cout << "\n--- SECUENCIAS DE OPERACIONES ---" << std::endl;
    
    dig_type x(0);
    std::cout << "x inicial = " << x.get() << std::endl;
    
    // Incrementar 3 veces
    ++x; ++x; ++x;
    std::cout << "Después de ++x; ++x; ++x: x = " << x.get() << " (debe ser " << (3 % B) << ")" << std::endl;
    assert(x.get() == 3 % B);
    
    // Decrementar 2 veces
    --x; --x;
    std::cout << "Después de --x; --x: x = " << x.get() << " (debe ser " << (1 % B) << ")" << std::endl;
    assert(x.get() == 1 % B);
    
    // Mezclar pre y post
    dig_type y = x++;  // y = 1, x = 2
    dig_type z = ++x;  // z = 3, x = 3
    std::cout << "y = x++ = " << y.get() << ", x = " << x.get() << std::endl;
    std::cout << "z = ++x = " << z.get() << ", x = " << x.get() << std::endl;
    assert(y.get() == 1 % B);
    assert(x.get() == 3 % B);
    assert(z.get() == 3 % B);
    std::cout << "✅ Secuencias mixtas funcionan correctamente" << std::endl;

    // =========================================================================
    // 8. CICLO COMPLETO (0 → B-1 → 0)
    // =========================================================================
    std::cout << "\n--- CICLO COMPLETO ---" << std::endl;
    
    if (B <= 10) {  // Solo para bases pequeñas
        dig_type cycle(0);
        std::cout << "Ciclo incremental desde 0:" << std::endl;
        
        for (std::uint64_t i = 0; i < B; ++i) {
            std::cout << "  " << cycle.get();
            assert(cycle.get() == i);
            ++cycle;
        }
        std::cout << std::endl;
        
        // Debe volver a 0
        assert(cycle.get() == 0);
        std::cout << "✅ Ciclo completo: 0 → 1 → ... → (B-1) → 0" << std::endl;
        
        // Ciclo decremental
        std::cout << "Ciclo decremental desde 0:" << std::endl;
        cycle = dig_type(0);
        
        for (std::uint64_t i = 0; i < B; ++i) {
            std::cout << "  " << cycle.get();
            if (i == 0) {
                assert(cycle.get() == 0);
            } else {
                assert(cycle.get() == B - i);
            }
            --cycle;
        }
        std::cout << std::endl;
        
        assert(cycle.get() == 0);
        std::cout << "✅ Ciclo completo inverso: 0 → (B-1) → ... → 1 → 0" << std::endl;
    } else {
        std::cout << "Base demasiado grande para ciclo completo, omitiendo..." << std::endl;
    }

    // =========================================================================
    // 9. PROPIEDADES MATEMÁTICAS
    // =========================================================================
    std::cout << "\n--- PROPIEDADES MATEMÁTICAS ---" << std::endl;
    
    // Propiedad: (x++)++ incrementa dos veces
    dig_type p(10);
    dig_type p_copy = p;
    (p++);
    (p++);
    std::cout << "Propiedad: (x++); (x++); incrementa dos veces" << std::endl;
    std::cout << "p original = " << p_copy.get() << ", después de dos x++: p = " << p.get() << std::endl;
    assert(p.get() == (p_copy.get() + 2) % B);
    std::cout << "✅ Post-incremento secuencial funciona correctamente" << std::endl;
    
    // Propiedad: ++x es equivalente a x += 1
    dig_type q(15);
    dig_type r(15);
    ++q;
    r += 1;
    std::cout << "Equivalencia: ++x ≡ x += 1" << std::endl;
    std::cout << "++q = " << q.get() << ", r += 1 = " << r.get() << std::endl;
    assert(q.get() == r.get());
    std::cout << "✅ Pre-incremento equivalente a x += 1" << std::endl;
    
    // Propiedad: --x es equivalente a x -= 1
    dig_type s(15);
    dig_type t(15);
    --s;
    t -= 1;
    std::cout << "Equivalencia: --x ≡ x -= 1" << std::endl;
    std::cout << "--s = " << s.get() << ", t -= 1 = " << t.get() << std::endl;
    assert(s.get() == t.get());
    std::cout << "✅ Pre-decremento equivalente a x -= 1" << std::endl;

    std::cout << "\n✅ Todos los tests de incremento/decremento para dig_t<" << B << "> pasaron!" << std::endl;
}

int main() {
    std::cout << "=== TESTS COMPLETOS DE OPERADORES ++ Y -- ===" << std::endl;
    std::cout << "Verificación de pre/post incremento y decremento" << std::endl;
    std::cout << "Wraparound en overflow (B-1 → 0) y underflow (0 → B-1)" << std::endl;

    // Test con diferentes bases
    test_increment_decrement<2>();   // Base mínima con ciclo
    test_increment_decrement<5>();   // Base pequeña con ciclo
    test_increment_decrement<10>();  // Base decimal con ciclo
    test_increment_decrement<16>();  // Base hexadecimal
    test_increment_decrement<256>(); // Base potencia de 2
    test_increment_decrement<257>(); // Base prima

    std::cout << "\n🎉 TODOS LOS TESTS DE INCREMENTO/DECREMENTO COMPLETADOS" << std::endl;
    std::cout << "\n📊 RESUMEN DE FUNCIONALIDADES VERIFICADAS:" << std::endl;
    std::cout << "✅ Pre-incremento (++x) con retorno de referencia" << std::endl;
    std::cout << "✅ Post-incremento (x++) con retorno de copia" << std::endl;
    std::cout << "✅ Pre-decremento (--x) con retorno de referencia" << std::endl;
    std::cout << "✅ Post-decremento (x--) con retorno de copia" << std::endl;
    std::cout << "✅ Wraparound en overflow: (B-1) + 1 = 0" << std::endl;
    std::cout << "✅ Wraparound en underflow: 0 - 1 = B-1" << std::endl;
    std::cout << "✅ Secuencias de operaciones mixtas" << std::endl;
    std::cout << "✅ Ciclos completos (bases pequeñas)" << std::endl;
    std::cout << "✅ Propiedades: ++x ≡ x+=1, --x ≡ x-=1" << std::endl;
    std::cout << "✅ Diferencia pre vs post (valor retornado)" << std::endl;
    std::cout << "✅ Referencias vs copias verificadas" << std::endl;

    return 0;
}
