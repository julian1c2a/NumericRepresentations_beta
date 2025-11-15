// test_auxiliary_functions_comprehensive.cpp
// Test integral para core/internal/auxiliary_functions.hpp
// Framework: Catch2 + integración CTest


#include <catch_amalgamated.hpp>
#include <core/internal/basic_types.hpp>
#include <core/internal/auxiliary_functions.hpp>
#include <type_traits>
#include <string>

TEST_CASE("auxiliary_functions: min/max básicos", "[auxiliary_functions]") {
    REQUIRE(std::min(3, 7) == 3);
    REQUIRE(std::max(3, 7) == 7);
    REQUIRE(std::min(-5, -2) == -5);
    REQUIRE(std::max(-5, -2) == -2);
}

TEST_CASE("auxiliary_functions: clamp y abs", "[auxiliary_functions]") {
    REQUIRE(std::clamp(5, 1, 10) == 5);
    REQUIRE(std::clamp(-1, 0, 10) == 0);
    REQUIRE(std::clamp(15, 0, 10) == 10);
    REQUIRE(std::abs(-7) == 7);
    REQUIRE(std::abs(7) == 7);
}

TEST_CASE("auxiliary_functions: sign y swap", "[auxiliary_functions]") {
    auto sign = [](int x) { return (x > 0) - (x < 0); };
    REQUIRE(sign(-5) == -1);
    REQUIRE(sign(0) == 0);
    REQUIRE(sign(8) == 1);
    int a = 1, b = 2;
    std::swap(a, b);
    REQUIRE(a == 2);
    REQUIRE(b == 1);
}

TEST_CASE("auxiliary_functions: to_string y from_string", "[auxiliary_functions]") {
    REQUIRE(std::to_string(42) == std::string("42"));
    int x = std::stoi("123");
    REQUIRE(x == 123);
    double d = std::stod("3.14");
    REQUIRE(d == Catch::Approx(3.14));
}

// Fin de test_auxiliary_functions_comprehensive.cpp
