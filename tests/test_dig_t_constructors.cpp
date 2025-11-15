#include <iostream>
#include <cassert>
#include <type_traits>

// Test que documenta y verifica constructores y métodos básicos de dig_t
#include <core/dig_t.hpp>

using namespace NumRepr;

template <std::uint64_t B>
void test_dig_t_basic_functionality()
{
    std::cout << "\n=== Testing dig_t<" << B << "> Basic Functionality ===" << std::endl;

    // 1. Verificar tipos generados
    using dig_type = dig_t<B>;
    using uint_type = typename dig_type::uint_t;
    using sig_uint_type = typename dig_type::sig_uint_t;
    using sig_sint_type = typename dig_type::sig_sint_t;

    std::cout << "Base B = " << B << std::endl;
    std::cout << "uint_t size: " << sizeof(uint_type) << " bytes" << std::endl;
    std::cout << "sig_uint_t size: " << sizeof(sig_uint_type) << " bytes" << std::endl;
    std::cout << "sig_sint_t size: " << sizeof(sig_sint_type) << " bytes" << std::endl;

    // 2. Constructor por defecto
    dig_type d1; // Debería inicializar a 0
    std::cout << "Constructor por defecto: d1 = " << d1.get() << std::endl;
    assert(d1.get() == 0);

    // 3. Constructor con valor entero
    dig_type d2(static_cast<std::uint32_t>(5));
    std::cout << "Constructor con valor 5: d2 = " << d2.get() << std::endl;
    if (B > 5)
    {
        assert(d2.get() == 5);
    }
    else
    {
        assert(d2.get() == 5 % B);
        std::cout << "Valor ajustado por módulo: " << 5 << " % " << B << " = " << d2.get() << std::endl;
    }

    // 4. Métodos set
    dig_type d3;
    d3.set_0();
    assert(d3.get() == 0);
    std::cout << "set_0(): " << d3.get() << std::endl;

    d3.set_1();
    assert(d3.get() == 1);
    std::cout << "set_1(): " << d3.get() << std::endl;

    d3.set_Bm1();
    assert(d3.get() == B - 1);
    std::cout << "set_Bm1(): " << d3.get() << " (B-1)" << std::endl;

    if (B > 2)
    {
        d3.set_Bm2();
        assert(d3.get() == B - 2);
        std::cout << "set_Bm2(): " << d3.get() << " (B-2)" << std::endl;
    }

    // 5. Factory methods
    auto zero = dig_type::dig_0();
    auto one = dig_type::dig_1();
    auto max_dig = dig_type::dig_max();

    assert(zero.get() == 0);
    assert(one.get() == 1);
    assert(max_dig.get() == B - 1);

    std::cout << "Factory methods - dig_0(): " << zero.get()
              << ", dig_1(): " << one.get()
              << ", dig_max(): " << max_dig.get() << std::endl;

    // 6. Conversiones explícitas
    dig_type d4(B - 1);
    uint_type extracted = static_cast<uint_type>(d4);
    assert(extracted == B - 1);
    std::cout << "Conversión explícita a uint_t: " << extracted << std::endl;

    // 7. Operador función
    assert(d4() == B - 1);
    std::cout << "Operador función d4(): " << d4() << std::endl;

    // 8. set_dig con diferentes tipos
    dig_type d5;
    d5.set_dig(d4); // Copiar desde otro dig_t
    assert(d5.get() == d4.get());
    std::cout << "set_dig(dig_t): " << d5.get() << std::endl;

    d5.set_dig(uint_type(3)); // Asignar desde uint_t
    if (B > 3)
    {
        assert(d5.get() == 3);
    }
    else
    {
        assert(d5.get() == 3 % B);
    }
    std::cout << "set_dig(uint_t): " << d5.get() << std::endl;

    // 9. Propiedades matemáticas
    bool is_prime_base = dig_type::is_prime();
    std::cout << "Base " << B << " es primo: " << (is_prime_base ? "SÍ" : "NO") << std::endl;

    std::cout << "✅ Todos los tests básicos para dig_t<" << B << "> pasaron!" << std::endl;
}

int main()
{
    std::cout << "=== DOCUMENTACIÓN Y TESTING DE dig_t.hpp ===" << std::endl;
    std::cout << "Verificando constructores y métodos básicos" << std::endl;

    // Test con diferentes bases
    test_dig_t_basic_functionality<2>();   // Base binaria
    test_dig_t_basic_functionality<8>();   // Base octal
    test_dig_t_basic_functionality<10>();  // Base decimal
    test_dig_t_basic_functionality<16>();  // Base hexadecimal
    test_dig_t_basic_functionality<17>();  // Base prima
    test_dig_t_basic_functionality<256>(); // Base grande

    std::cout << "\n🎉 TODOS LOS TESTS DE CONSTRUCTORES Y MÉTODOS BÁSICOS COMPLETADOS" << std::endl;
    return 0;
}