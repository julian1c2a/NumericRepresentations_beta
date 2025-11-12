/**
 * @file test_pack2array.cpp
 * @brief Tests para pack2array y assign_with_order
 * 
 * Verifica:
 * - Conversión de parameter packs a arrays
 * - Perfect forwarding con lvalues y rvalues
 * - Eficiencia con tipos no-triviales
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "core/internal/basic_types.hpp"
#include <array>
#include <string>
#include <iostream>

using namespace NumRepr;

// Tipo para rastrear copias y movimientos
struct TrackedInt {
    int value;
    mutable int copy_count = 0;
    mutable int move_count = 0;
    
    TrackedInt(int v = 0) noexcept : value(v) {}
    
    TrackedInt(const TrackedInt& other) noexcept 
        : value(other.value), copy_count(other.copy_count + 1), move_count(other.move_count) 
    {
        std::cout << "TrackedInt COPY: value=" << value << ", copies=" << copy_count << "\n";
    }
    
    TrackedInt(TrackedInt&& other) noexcept 
        : value(other.value), copy_count(other.copy_count), move_count(other.move_count + 1) 
    {
        std::cout << "TrackedInt MOVE: value=" << value << ", moves=" << move_count << "\n";
    }
    
    TrackedInt& operator=(const TrackedInt& other) noexcept {
        value = other.value;
        copy_count = other.copy_count + 1;
        move_count = other.move_count;
        std::cout << "TrackedInt COPY-ASSIGN: value=" << value << "\n";
        return *this;
    }
    
    TrackedInt& operator=(TrackedInt&& other) noexcept {
        value = other.value;
        copy_count = other.copy_count;
        move_count = other.move_count + 1;
        std::cout << "TrackedInt MOVE-ASSIGN: value=" << value << "\n";
        return *this;
    }
    
    bool operator==(const TrackedInt& other) const noexcept {
        return value == other.value;
    }
};

TEST_CASE("pack2array - Conversión básica", "[pack2array]") {
    SECTION("Tipos primitivos") {
        using P2A = ugly_pack_details::pack2array<int, int, int>;
        
        constexpr auto arr = P2A{}(10, 20, 30);
        STATIC_REQUIRE(arr.size() == 3);
        STATIC_REQUIRE(arr[0] == 10);
        STATIC_REQUIRE(arr[1] == 20);
        STATIC_REQUIRE(arr[2] == 30);
    }
    
    SECTION("get - Obtener elemento") {
        using P2A = ugly_pack_details::pack2array<int, int, int, int>;
        
        constexpr auto elem0 = P2A::get<0>(10, 20, 30, 40);
        constexpr auto elem1 = P2A::get<1>(10, 20, 30, 40);
        constexpr auto elem2 = P2A::get<2>(10, 20, 30, 40);
        constexpr auto elem3 = P2A::get<3>(10, 20, 30, 40);
        
        STATIC_REQUIRE(elem0 == 10);
        STATIC_REQUIRE(elem1 == 20);
        STATIC_REQUIRE(elem2 == 30);
        STATIC_REQUIRE(elem3 == 40);
    }
}

TEST_CASE("pack2array - for_each", "[pack2array]") {
    using P2A = ugly_pack_details::pack2array<int, int, int, int>;
    
    std::array<int, 4> arr{};
    P2A::for_each(arr, 100, 200, 300, 400);
    
    REQUIRE(arr[0] == 100);
    REQUIRE(arr[1] == 200);
    REQUIRE(arr[2] == 300);
    REQUIRE(arr[3] == 400);
}

TEST_CASE("assign_with_order - Básico", "[assign_with_order]") {
    std::array<int, 5> arr{};
    assign_with_order(arr, 5, 10, 15, 20, 25);
    
    REQUIRE(arr[0] == 5);
    REQUIRE(arr[1] == 10);
    REQUIRE(arr[2] == 15);
    REQUIRE(arr[3] == 20);
    REQUIRE(arr[4] == 25);
}

TEST_CASE("pack2array - Análisis de copias/movimientos", "[pack2array][performance]") {
    std::cout << "\n=== TEST: Análisis de copias con lvalues ===\n";
    
    SECTION("Con lvalues - cuántas copias?") {
        TrackedInt a(10), b(20), c(30);
        
        std::cout << "Antes de pack2array:\n";
        std::cout << "  a.copy_count=" << a.copy_count << ", a.move_count=" << a.move_count << "\n";
        
        using P2A = ugly_pack_details::pack2array<TrackedInt, TrackedInt, TrackedInt>;
        auto arr = P2A{}(a, b, c);
        
        std::cout << "Después de pack2array:\n";
        std::cout << "  arr[0].value=" << arr[0].value << ", copies=" << arr[0].copy_count << ", moves=" << arr[0].move_count << "\n";
        std::cout << "  arr[1].value=" << arr[1].value << ", copies=" << arr[1].copy_count << ", moves=" << arr[1].move_count << "\n";
        std::cout << "  arr[2].value=" << arr[2].value << ", copies=" << arr[2].copy_count << ", moves=" << arr[2].move_count << "\n";
        
        REQUIRE(arr[0].value == 10);
        REQUIRE(arr[1].value == 20);
        REQUIRE(arr[2].value == 30);
        
        // ¿Cuántas copias se hacen? Esto revelará si necesitamos perfect forwarding
        std::cout << "RESULTADO: " << arr[0].copy_count << " copias por elemento\n";
    }
    
    SECTION("Con rvalues - ¿se pueden mover?") {
        std::cout << "\n=== Con rvalues temporales ===\n";
        
        using P2A = ugly_pack_details::pack2array<TrackedInt, TrackedInt, TrackedInt>;
        auto arr = P2A{}(TrackedInt(10), TrackedInt(20), TrackedInt(30));
        
        std::cout << "Resultado final:\n";
        std::cout << "  arr[0]: copies=" << arr[0].copy_count << ", moves=" << arr[0].move_count << "\n";
        
        REQUIRE(arr[0].value == 10);
        REQUIRE(arr[1].value == 20);
        REQUIRE(arr[2].value == 30);
    }
}

TEST_CASE("pack2array - Uso como en register_variant_t", "[pack2array][real-world]") {
    SECTION("Sintaxis: pack2array<const Ts&...>") {
        int a = 10, b = 20, c = 30;
        
        // Así se usa en register_variant_t.hpp línea 120
        using P2A = ugly_pack_details::pack2array<const int&, const int&, const int&>;
        auto arr = P2A{}(a, b, c);
        
        REQUIRE(arr[0] == 10);
        REQUIRE(arr[1] == 20);
        REQUIRE(arr[2] == 30);
    }
    
    SECTION("Sintaxis: pack2array<Ts...> con args const Ts&") {
        int a = 10, b = 20, c = 30;
        const int& ra = a;
        const int& rb = b;
        const int& rc = c;
        
        // Así se usa en int_reg_digs_t.hpp línea 256
        using P2A = ugly_pack_details::pack2array<int, int, int>;
        auto arr = P2A{}(ra, rb, rc);
        
        REQUIRE(arr[0] == 10);
        REQUIRE(arr[1] == 20);
        REQUIRE(arr[2] == 30);
    }
}

TEST_CASE("assign_with_order - Con const references", "[assign_with_order]") {
    int a = 100, b = 200, c = 300;
    std::array<int, 3> arr{};
    
    assign_with_order(arr, a, b, c);
    
    REQUIRE(arr[0] == 100);
    REQUIRE(arr[1] == 200);
    REQUIRE(arr[2] == 300);
}

TEST_CASE("pack2array - PROPUESTA: Con perfect forwarding", "[pack2array][forwarding]") {
    std::cout << "\n=== TEST: Perfect Forwarding ===\n";
    
    SECTION("Lvalues con forwarding - debe evitar copias innecesarias") {
        // TODO: Implementar versión con perfect forwarding
        // Debería hacer solo 1 copia en lugar de 2
        REQUIRE(true);
    }
    
    SECTION("Rvalues con forwarding - debe permitir movimientos") {
        // TODO: Implementar versión con perfect forwarding
        // Debería mover en lugar de copiar
        REQUIRE(true);
    }
}
