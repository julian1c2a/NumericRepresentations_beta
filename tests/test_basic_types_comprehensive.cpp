
#include <catch_amalgamated.hpp>
#include <core/internal/basic_types.hpp>
#include <array>
#include <type_traits>

// test_basic_types_comprehensive.cpp
// Test integral para core/internal/basic_types.hpp
// Framework: Catch2 + integración CTest

TEST_CASE("basic_types: typedefs y tipos fundamentales", "[basic_types]") {
    // Verifica typedefs y tipos básicos
    STATIC_REQUIRE(std::is_same_v<NumRepr::schint_t, signed char>);
    STATIC_REQUIRE(std::is_same_v<NumRepr::ssint_t, signed short int>);
    STATIC_REQUIRE(std::is_same_v<NumRepr::sint_t, signed int>);
    STATIC_REQUIRE(std::is_same_v<NumRepr::slint_t, signed long int>);
    STATIC_REQUIRE(std::is_same_v<NumRepr::sllint_t, signed long long int>);
    STATIC_REQUIRE(std::is_same_v<NumRepr::uchint_t, unsigned char>);
    STATIC_REQUIRE(std::is_same_v<NumRepr::usint_t, unsigned short int>);
    STATIC_REQUIRE(std::is_same_v<NumRepr::uint_t, unsigned int>);
    STATIC_REQUIRE(std::is_same_v<NumRepr::ulint_t, unsigned long int>);
    STATIC_REQUIRE(std::is_same_v<NumRepr::ullint_t, unsigned long long int>);
    STATIC_REQUIRE(std::is_same_v<NumRepr::intmax_t, std::intmax_t>);
    STATIC_REQUIRE(std::is_same_v<NumRepr::uintmax_t, std::uintmax_t>);
}

// Fin de test_basic_types_comprehensive.cpp
