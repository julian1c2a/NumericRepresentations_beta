// test_core_internal_comprehensive.cpp
// Test integral para core/internal/*.hpp (basic_types, auxiliary_functions, pack2array, etc.)
// Framework: Catch2 + integración CTest




#include <catch_amalgamated.hpp>
#include <core/internal/basic_types.hpp>
#include <core/internal/auxiliary_functions.hpp>
#include <array>
#include <type_traits>
#include <string>



TEST_CASE("core/internal: typedefs y tipos básicos", "[core_internal][basic_types]") {
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









// Pruebas de enums y funciones inline
TEST_CASE("core/internal: enums y funciones inline", "[core_internal][basic_types]") {
    using NumRepr::sign_funct_e;
    STATIC_REQUIRE(static_cast<int>(sign_funct_e::vminus) == -1);
    STATIC_REQUIRE(static_cast<int>(sign_funct_e::vzero) == 0);
    STATIC_REQUIRE(static_cast<int>(sign_funct_e::vplus) == 1);
    STATIC_REQUIRE(NumRepr::to_int(sign_funct_e::vminus) == -1);
    STATIC_REQUIRE(NumRepr::to_int(sign_funct_e::vzero) == 0);
    STATIC_REQUIRE(NumRepr::to_int(sign_funct_e::vplus) == 1);
    STATIC_REQUIRE(NumRepr::is_positive(sign_funct_e::vplus));
    STATIC_REQUIRE(!NumRepr::is_positive(sign_funct_e::vminus));
    STATIC_REQUIRE(!NumRepr::is_positive(sign_funct_e::vzero));
    STATIC_REQUIRE(NumRepr::is_negative(sign_funct_e::vminus));
    STATIC_REQUIRE(!NumRepr::is_negative(sign_funct_e::vplus));
    STATIC_REQUIRE(!NumRepr::is_negative(sign_funct_e::vzero));
    STATIC_REQUIRE(NumRepr::is_zero(sign_funct_e::vzero));
    STATIC_REQUIRE(!NumRepr::is_zero(sign_funct_e::vplus));
    STATIC_REQUIRE(!NumRepr::is_zero(sign_funct_e::vminus));
    STATIC_REQUIRE(NumRepr::opposite_sign(sign_funct_e::vplus) == sign_funct_e::vminus);
    STATIC_REQUIRE(NumRepr::opposite_sign(sign_funct_e::vminus) == sign_funct_e::vplus);
    STATIC_REQUIRE(NumRepr::opposite_sign(sign_funct_e::vzero) == sign_funct_e::vzero);
}
// Fin de test_core_internal_comprehensive.cpp
