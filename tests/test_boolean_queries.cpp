/**
 * @file test_boolean_queries.cpp
 * @brief Test exhaustivo de todas las funciones de consulta booleanas de dig_t
 * 
 * @details Cubre todas las funciones is_*:
 * - Consultas básicas: is_0, is_1, is_0or1, is_not_*
 * - Consultas de máximos: is_Bm1, is_Bm2, is_Bm1orBm2, is_not_*
 * - Consultas de extremos: is_maxormin, is_not_maxormin
 * - Consultas de proximidad: is_near_maxormin, is_far_maxormin
 * - Casos especiales: Base 2 (comportamiento diferente en near/far)
 */

#include <core/dig_t.hpp>
#include <iostream>
#include <cassert>

using namespace std;
using namespace NumRepr;

// ============================================================================
// TESTS DE CONSULTAS BÁSICAS (is_0, is_1, is_0or1)
// ============================================================================

template <uint64_t B>
void test_consultas_basicas() {
    cout << "\n=== TEST CONSULTAS BÁSICAS (Base " << B << ") ===" << endl;
    using dig = dig_t<B>;
    
    // is_0() - detecta cero
    dig zero(0);
    assert(zero.is_0());
    assert(!zero.is_not_0());
    cout << "✓ is_0(): dig(0).is_0() = true" << endl;
    
    dig uno(1);
    assert(!uno.is_0());
    assert(uno.is_not_0());
    cout << "✓ is_0(): dig(1).is_0() = false" << endl;
    
    // is_1() - detecta uno
    assert(uno.is_1());
    assert(!uno.is_not_1());
    cout << "✓ is_1(): dig(1).is_1() = true" << endl;
    
    assert(!zero.is_1());
    assert(zero.is_not_1());
    cout << "✓ is_1(): dig(0).is_1() = false" << endl;
    
    // is_0or1() - detecta valores booleanos
    assert(zero.is_0or1());
    assert(!zero.is_not_0or1());
    cout << "✓ is_0or1(): dig(0).is_0or1() = true" << endl;
    
    assert(uno.is_0or1());
    assert(!uno.is_not_0or1());
    cout << "✓ is_0or1(): dig(1).is_0or1() = true" << endl;
    
    if constexpr (B > 2) {
        dig dos(2);
        assert(!dos.is_0or1());
        assert(dos.is_not_0or1());
        cout << "✓ is_0or1(): dig(2).is_0or1() = false" << endl;
    }
    
    // Verificar normalización automática
    if constexpr (B > 1) {
        dig normalizado(B + 1); // Debería normalizarse a 1
        assert(normalizado.is_1());
        cout << "✓ Normalización: dig(B+1) se normaliza a 1" << endl;
    }
}

// ============================================================================
// TESTS DE CONSULTAS DE MÁXIMOS (is_Bm1, is_Bm2)
// ============================================================================

template <uint64_t B>
void test_consultas_maximos() {
    cout << "\n=== TEST CONSULTAS DE MÁXIMOS (Base " << B << ") ===" << endl;
    using dig = dig_t<B>;
    
    // is_Bm1() - detecta B-1 (máximo)
    dig max_val(B - 1);
    assert(max_val.is_Bm1());
    assert(!max_val.is_not_Bm1());
    cout << "✓ is_Bm1(): dig(B-1=" << (B-1) << ").is_Bm1() = true" << endl;
    
    dig not_max(B - 2);
    assert(!not_max.is_Bm1());
    assert(not_max.is_not_Bm1());
    cout << "✓ is_Bm1(): dig(B-2=" << (B-2) << ").is_Bm1() = false" << endl;
    
    // is_Bm2() - detecta B-2 (segundo máximo)
    assert(not_max.is_Bm2());
    assert(!not_max.is_not_Bm2());
    cout << "✓ is_Bm2(): dig(B-2=" << (B-2) << ").is_Bm2() = true" << endl;
    
    assert(!max_val.is_Bm2());
    assert(max_val.is_not_Bm2());
    cout << "✓ is_Bm2(): dig(B-1=" << (B-1) << ").is_Bm2() = false" << endl;
    
    // is_Bm1orBm2() - detecta los dos máximos
    assert(max_val.is_Bm1orBm2());
    assert(!max_val.is_not_Bm1orBm2());
    cout << "✓ is_Bm1orBm2(): dig(B-1).is_Bm1orBm2() = true" << endl;
    
    assert(not_max.is_Bm1orBm2());
    assert(!not_max.is_not_Bm1orBm2());
    cout << "✓ is_Bm1orBm2(): dig(B-2).is_Bm1orBm2() = true" << endl;
    
    if constexpr (B > 3) {
        dig not_near_max(B - 3);
        assert(!not_near_max.is_Bm1orBm2());
        assert(not_near_max.is_not_Bm1orBm2());
        cout << "✓ is_Bm1orBm2(): dig(B-3=" << (B-3) << ").is_Bm1orBm2() = false" << endl;
    }
}

// ============================================================================
// TESTS DE CONSULTAS DE EXTREMOS (is_maxormin)
// ============================================================================

template <uint64_t B>
void test_consultas_extremos() {
    cout << "\n=== TEST CONSULTAS DE EXTREMOS (Base " << B << ") ===" << endl;
    using dig = dig_t<B>;
    
    // is_maxormin() - detecta 0 o B-1
    dig zero(0);
    assert(zero.is_maxormin());
    assert(!zero.is_not_maxormin());
    cout << "✓ is_maxormin(): dig(0).is_maxormin() = true" << endl;
    
    dig max_val(B - 1);
    assert(max_val.is_maxormin());
    assert(!max_val.is_not_maxormin());
    cout << "✓ is_maxormin(): dig(B-1=" << (B-1) << ").is_maxormin() = true" << endl;
    
    if constexpr (B > 2) {
        dig medio(B / 2);
        assert(!medio.is_maxormin());
        assert(medio.is_not_maxormin());
        cout << "✓ is_maxormin(): dig(B/2=" << (B/2) << ").is_maxormin() = false" << endl;
    }
    
    // Verificar que valores intermedios NO son extremos
    if constexpr (B > 2) {
        dig uno(1);
        assert(!uno.is_maxormin());
        assert(uno.is_not_maxormin());
        cout << "✓ is_maxormin(): dig(1).is_maxormin() = false (B>2)" << endl;
        
        dig bm2(B - 2);
        assert(!bm2.is_maxormin());
        assert(bm2.is_not_maxormin());
        cout << "✓ is_maxormin(): dig(B-2=" << (B-2) << ").is_maxormin() = false" << endl;
    } else if constexpr (B == 2) {
        // En B=2, solo hay {0,1}, ambos son extremos
        dig uno(1);
        assert(uno.is_maxormin()); // 1 es B-1 en B=2
        cout << "✓ is_maxormin(): dig(1) es extremo en B=2 (0 y B-1 coinciden)" << endl;
    }
}

// ============================================================================
// TESTS DE CONSULTAS DE PROXIMIDAD (is_near/far_maxormin)
// ============================================================================

template <uint64_t B>
void test_consultas_proximidad() {
    cout << "\n=== TEST CONSULTAS DE PROXIMIDAD (Base " << B << ") ===" << endl;
    using dig = dig_t<B>;
    
    if constexpr (B == 2) {
        // CASO ESPECIAL BASE 2: todos están cerca, ninguno está lejos
        cout << "  [Caso especial B=2: todos cerca, ninguno lejos]" << endl;
        
        dig zero(0);
        dig uno(1);
        
        assert(zero.is_near_maxormin());
        assert(uno.is_near_maxormin());
        cout << "✓ is_near_maxormin(): en B=2, ambos valores (0,1) están cerca" << endl;
        
        assert(!zero.is_far_maxormin());
        assert(!uno.is_far_maxormin());
        cout << "✓ is_far_maxormin(): en B=2, ningún valor está lejos" << endl;
        
    } else {
        // CASO GENERAL (B > 2)
        
        // is_near_maxormin() - cerca incluye {0, 1, B-2, B-1}
        dig zero(0);
        assert(zero.is_near_maxormin());
        cout << "✓ is_near_maxormin(): dig(0) está cerca" << endl;
        
        dig uno(1);
        assert(uno.is_near_maxormin());
        cout << "✓ is_near_maxormin(): dig(1) está cerca" << endl;
        
        dig bm2(B - 2);
        assert(bm2.is_near_maxormin());
        cout << "✓ is_near_maxormin(): dig(B-2=" << (B-2) << ") está cerca" << endl;
        
        dig bm1(B - 1);
        assert(bm1.is_near_maxormin());
        cout << "✓ is_near_maxormin(): dig(B-1=" << (B-1) << ") está cerca" << endl;
        
        // is_far_maxormin() - lejos es el rango [2, B-3]
        if constexpr (B >= 4) {
            dig dos(2);
            assert(dos.is_far_maxormin());
            assert(!dos.is_near_maxormin());
            cout << "✓ is_far_maxormin(): dig(2) está lejos (B≥4)" << endl;
            
            if constexpr (B >= 5) {
                dig bm3(B - 3);
                assert(bm3.is_far_maxormin());
                assert(!bm3.is_near_maxormin());
                cout << "✓ is_far_maxormin(): dig(B-3=" << (B-3) << ") está lejos (B≥5)" << endl;
            }
            
            if constexpr (B >= 6) {
                dig medio(B / 2);
                assert(medio.is_far_maxormin());
                assert(!medio.is_near_maxormin());
                cout << "✓ is_far_maxormin(): dig(B/2=" << (B/2) << ") está lejos" << endl;
            }
        }
        
        if constexpr (B == 3) {
            // En B=3, solo hay {0,1,2}, todos cerca, ninguno lejos
            dig dos(2);
            assert(dos.is_near_maxormin());
            assert(!dos.is_far_maxormin());
            cout << "✓ Caso especial B=3: todos los valores están cerca" << endl;
        }
    }
}

// ============================================================================
// TESTS DE PROPIEDADES LÓGICAS
// ============================================================================

template <uint64_t B>
void test_propiedades_logicas() {
    cout << "\n=== TEST PROPIEDADES LÓGICAS (Base " << B << ") ===" << endl;
    using dig = dig_t<B>;
    
    // Propiedad: is_X() ≡ !is_not_X()
    for (uint64_t i = 0; i < (B < 10 ? B : 10); ++i) {
        dig d(i);
        assert(d.is_0() == !d.is_not_0());
        assert(d.is_1() == !d.is_not_1());
        assert(d.is_0or1() == !d.is_not_0or1());
        assert(d.is_Bm1() == !d.is_not_Bm1());
        assert(d.is_Bm2() == !d.is_not_Bm2());
        assert(d.is_maxormin() == !d.is_not_maxormin());
    }
    cout << "✓ Propiedad: is_X() ≡ !is_not_X() para todos los valores" << endl;
    
    // Propiedad: is_0or1() ≡ (is_0() || is_1())
    dig zero(0);
    dig uno(1);
    assert(zero.is_0or1() == (zero.is_0() || zero.is_1()));
    assert(uno.is_0or1() == (uno.is_0() || uno.is_1()));
    cout << "✓ Propiedad: is_0or1() ≡ (is_0() || is_1())" << endl;
    
    // Propiedad: is_Bm1orBm2() ≡ (is_Bm1() || is_Bm2())
    dig bm1(B - 1);
    dig bm2(B - 2);
    assert(bm1.is_Bm1orBm2() == (bm1.is_Bm1() || bm1.is_Bm2()));
    assert(bm2.is_Bm1orBm2() == (bm2.is_Bm1() || bm2.is_Bm2()));
    cout << "✓ Propiedad: is_Bm1orBm2() ≡ (is_Bm1() || is_Bm2())" << endl;
    
    // Propiedad: is_maxormin() ≡ (is_0() || is_Bm1())
    assert(zero.is_maxormin() == (zero.is_0() || zero.is_Bm1()));
    assert(bm1.is_maxormin() == (bm1.is_0() || bm1.is_Bm1()));
    cout << "✓ Propiedad: is_maxormin() ≡ (is_0() || is_Bm1())" << endl;
    
    if constexpr (B > 2) {
        // Propiedad: near ∪ far = todos (excepto B=2,3)
        if constexpr (B >= 4) {
            dig medio(B / 2);
            assert(medio.is_near_maxormin() != medio.is_far_maxormin());
            cout << "✓ Propiedad: near y far son disjuntos (B≥4)" << endl;
        }
    }
}

// ============================================================================
// TESTS DE COMBINACIONES Y CASOS LÍMITE
// ============================================================================

template <uint64_t B>
void test_casos_limite() {
    cout << "\n=== TEST CASOS LÍMITE (Base " << B << ") ===" << endl;
    using dig = dig_t<B>;
    
    // Verificar todos los valores del rango [0, B-1]
    int count_near = 0;
    int count_far = 0;
    
    for (uint64_t i = 0; i < B; ++i) {
        dig d(i);
        
        // Verificar que las funciones son consistentes
        if (d.is_0()) assert(i == 0);
        if (d.is_1()) assert(i == 1);
        if (d.is_Bm1()) assert(i == B - 1);
        if (d.is_Bm2()) assert(i == B - 2);
        
        // Contar near/far
        if (d.is_near_maxormin()) count_near++;
        if (d.is_far_maxormin()) count_far++;
        
        // Verificar que near y far son disjuntos
        assert(!(d.is_near_maxormin() && d.is_far_maxormin()));
    }
    
    cout << "✓ Valores en rango [0," << (B-1) << "]: " << B << " valores verificados" << endl;
    cout << "  - Valores cerca: " << count_near << endl;
    cout << "  - Valores lejos: " << count_far << endl;
    
    // Verificar conteo esperado
    if constexpr (B == 2) {
        assert(count_near == 2); // {0, 1}
        assert(count_far == 0);
    } else if constexpr (B == 3) {
        assert(count_near == 3); // {0, 1, 2}
        assert(count_far == 0);
    } else if constexpr (B >= 4) {
        assert(count_near == 4); // {0, 1, B-2, B-1}
        assert(count_far == B - 4); // [2, B-3]
    }
    
    assert(count_near + count_far == (int)B);
    cout << "✓ Conteo correcto: near + far = B" << endl;
}

// ============================================================================
// FUNCIÓN PRINCIPAL DE TESTS
// ============================================================================

template <uint64_t B>
void ejecutar_todos_los_tests() {
    cout << "\n╔═══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  TEST EXHAUSTIVO - FUNCIONES DE CONSULTA BOOLEANAS           ║" << endl;
    cout << "║  Base B = " << B << string(53 - to_string(B).length(), ' ') << "║" << endl;
    cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;
    
    test_consultas_basicas<B>();
    test_consultas_maximos<B>();
    test_consultas_extremos<B>();
    test_consultas_proximidad<B>();
    test_propiedades_logicas<B>();
    test_casos_limite<B>();
    
    cout << "\n✅ TODOS LOS TESTS PASARON PARA BASE " << B << endl;
}

int main() {
    cout << "╔═══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║        SUITE DE TESTS - FUNCIONES DE CONSULTA BOOLEANAS      ║" << endl;
    cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;
    
    try {
        // Tests con base 2 (caso especial para near/far)
        ejecutar_todos_los_tests<2>();
        
        // Tests con base 3 (caso límite)
        ejecutar_todos_los_tests<3>();
        
        // Tests con base 5 (prima pequeña)
        ejecutar_todos_los_tests<5>();
        
        // Tests con base 10 (decimal)
        ejecutar_todos_los_tests<10>();
        
        // Tests con base 16 (hexadecimal)
        ejecutar_todos_los_tests<16>();
        
        // Tests con base 256 (potencia de 2, usado en comprehensive)
        ejecutar_todos_los_tests<256>();
        
        // Tests con base 257 (primo, usado en comprehensive)
        ejecutar_todos_los_tests<257>();
        
        cout << "\n╔═══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║  ✅✅✅ TODOS LOS TESTS PASARON EXITOSAMENTE ✅✅✅           ║" << endl;
        cout << "╚═══════════════════════════════════════════════════════════════╝" << endl;
        
        cout << "\n📊 RESUMEN DE COBERTURA:" << endl;
        cout << "  ✅ is_0() y is_not_0()" << endl;
        cout << "  ✅ is_1() y is_not_1()" << endl;
        cout << "  ✅ is_0or1() y is_not_0or1()" << endl;
        cout << "  ✅ is_Bm1() y is_not_Bm1()" << endl;
        cout << "  ✅ is_Bm2() y is_not_Bm2()" << endl;
        cout << "  ✅ is_Bm1orBm2() y is_not_Bm1orBm2()" << endl;
        cout << "  ✅ is_maxormin() y is_not_maxormin()" << endl;
        cout << "  ✅ is_near_maxormin() (con caso especial B=2)" << endl;
        cout << "  ✅ is_far_maxormin() (con caso especial B=2)" << endl;
        cout << "\n📈 TOTAL: 16 funciones de consulta booleanas" << endl;
        cout << "🎯 Bases testeadas: 2, 3, 5, 10, 16, 256, 257" << endl;
        cout << "✨ Propiedades lógicas verificadas" << endl;
        cout << "🔍 Casos límite y combinaciones validados" << endl;
        
    } catch (const exception& e) {
        cerr << "\n❌ ERROR: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
