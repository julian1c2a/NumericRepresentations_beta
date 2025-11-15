// tests/test_stress_make_digit.cpp
// Pruebas de estrés para dig_t: valores y bases extremas
// Autor: julian1c2a / GitHub Copilot
// Fecha: 14/11/2025

#include <cassert>
#include <string>
#include <iostream>
#include <core/dig_t.hpp>


using namespace std;
using namespace NumRepr;

// Test para base mínima (2)
void test_base_min() {
    constexpr int base = 2;
    auto d0 = make_digit<base>(0);
    auto d1 = make_digit<base>(1);
    assert(d0 && d1);
    assert(d0.get() == 0);
    assert(d1.get() == 1);
    // Prueba de overflow
    auto d2 = make_digit<base>(2);
    assert(!d2);
}

// Test para base máxima (36)
void test_base_max() {
    constexpr int base = 36;
    auto d10 = make_digit<base>(10);
    auto d35 = make_digit<base>(35);
    assert(d10 && d35);
    assert(d10.get() == 10);
    assert(d35.get() == 35);
    // Prueba de overflow
    auto d36 = make_digit<base>(36);
    assert(!d36);
}

// Test para valores límite en base 10
void test_base10_limits() {
    constexpr int base = 10;
    auto d0 = make_digit<base>(0);
    auto d9 = make_digit<base>(9);
    assert(d0 && d9);
    assert(d0.get() == 0);
    assert(d9.get() == 9);
    auto d10 = make_digit<base>(10);
    assert(!d10);
}

// Test para strings y arrays grandes
void test_large_string_array() {
    constexpr int base = 16;
    std::string s = "F";
    auto d = make_digit<base>(s);
    assert(d && d->get() == 15);
    char arr[] = {'1','4','\0'};
    auto d2 = make_digit<base>(arr);
    assert(d2 && d2->get() == 14);
}

int main() {
    test_base_min();
    test_base_max();
    test_base10_limits();
    test_large_string_array();
    cout << "Pruebas de estrés de dig_t PASARON" << endl;
    return 0;
}
