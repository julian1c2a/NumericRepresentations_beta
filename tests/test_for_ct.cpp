/**
 * @file test_for_ct.cpp
 * @brief Tests para for_ct - Compile-time for loop con MSVC compatibility
 * 
 * Valida:
 * - Iteración sobre tuplas en compile-time
 * - Compatibilidad con MSVC (sin template template parameters)
 * - Function object approach con operador template
 * - Diferentes tipos de elementos en tupla
 * - Parámetro Base configurable
 */

#define CATCH_CONFIG_MAIN
#include "../tmp/Catch2/extras/catch_amalgamated.hpp"
#include "core/internal/auxiliary_functions.hpp"

#include <tuple>
#include <vector>
#include <string>

using namespace NumRepr::auxiliary_functions::special;

// =============================================================================
// FUNCTORS DE TEST
// =============================================================================

/**
 * @brief Functor que acumula valores en un vector
 */
struct AccumulatorFunctor {
    std::vector<int>& results;
    
    explicit AccumulatorFunctor(std::vector<int>& r) : results(r) {}
    
    template<std::size_t Base, std::size_t Index>
    void operator()(auto&& element) const {
        results.push_back(element * Base + Index);
    }
};

/**
 * @brief Functor que cuenta llamadas
 */
struct CounterFunctor {
    int& count;
    
    explicit CounterFunctor(int& c) : count(c) {}
    
    template<std::size_t Base, std::size_t Index>
    void operator()(auto&& element) const {
        count++;
    }
};

/**
 * @brief Functor que verifica índices secuenciales
 */
struct IndexVerifierFunctor {
    std::vector<std::size_t>& indices;
    
    explicit IndexVerifierFunctor(std::vector<std::size_t>& idx) : indices(idx) {}
    
    template<std::size_t Base, std::size_t Index>
    void operator()(auto&& element) const {
        indices.push_back(Index);
    }
};

/**
 * @brief Functor simple que suma elementos
 */
struct SimpleSumFunctor {
    int& sum;
    
    explicit SimpleSumFunctor(int& s) : sum(s) {}
    
    template<std::size_t Base, std::size_t Index>
    void operator()(auto&& element) const {
        sum += element;
    }
};

/**
 * @brief Functor que convierte tupla de dígitos a número
 * Usado para casos prácticos de conversión digit-to-int
 */
struct DigitToIntFunctor {
    std::uint64_t& accumulator;
    std::uint64_t base;
    
    DigitToIntFunctor(std::uint64_t& acc, std::uint64_t b) 
        : accumulator(acc), base(b) {}
    
    template<std::size_t Base, std::size_t Index>
    void operator()(auto&& digit) const {
        // Acumula: acc = acc * base + digit
        accumulator = accumulator * base + static_cast<std::uint64_t>(digit);
    }
};

// =============================================================================
// TESTS
// =============================================================================

TEST_CASE("for_ct - Iteracion basica sobre tupla homogenea", "[for_ct][compile_time]") {
    std::tuple<int, int, int> test_tuple{10, 20, 30};
    std::vector<int> results;
    
    SECTION("Procesar todos los elementos con Base=1") {
        for_ct<0, 3, 1>(test_tuple, AccumulatorFunctor{results});
        
        REQUIRE(results.size() == 3);
        REQUIRE(results[0] == 10 * 1 + 0); // 10
        REQUIRE(results[1] == 20 * 1 + 1); // 21
        REQUIRE(results[2] == 30 * 1 + 2); // 32
    }
    
    SECTION("Procesar con Base=10") {
        for_ct<0, 3, 10>(test_tuple, AccumulatorFunctor{results});
        
        REQUIRE(results.size() == 3);
        REQUIRE(results[0] == 10 * 10 + 0); // 100
        REQUIRE(results[1] == 20 * 10 + 1); // 201
        REQUIRE(results[2] == 30 * 10 + 2); // 302
    }
}

TEST_CASE("for_ct - Rango parcial de iteracion", "[for_ct][range]") {
    std::tuple<int, int, int, int, int> test_tuple{1, 2, 3, 4, 5};
    std::vector<int> results;
    
    SECTION("Iterar solo elementos 1-3 (indices 1,2)") {
        for_ct<1, 3, 1>(test_tuple, AccumulatorFunctor{results});
        
        REQUIRE(results.size() == 2);
        REQUIRE(results[0] == 2 * 1 + 1); // 3
        REQUIRE(results[1] == 3 * 1 + 2); // 5
    }
    
    SECTION("Iterar solo primer elemento") {
        for_ct<0, 1, 1>(test_tuple, AccumulatorFunctor{results});
        
        REQUIRE(results.size() == 1);
        REQUIRE(results[0] == 1 * 1 + 0); // 1
    }
    
    SECTION("Iterar ultimos dos elementos") {
        for_ct<3, 5, 1>(test_tuple, AccumulatorFunctor{results});
        
        REQUIRE(results.size() == 2);
        REQUIRE(results[0] == 4 * 1 + 3); // 7
        REQUIRE(results[1] == 5 * 1 + 4); // 9
    }
}

TEST_CASE("for_ct - Contar llamadas al functor", "[for_ct][count]") {
    std::tuple<int, int, int, int> test_tuple{1, 2, 3, 4};
    int call_count = 0;
    
    for_ct<0, 4, 1>(test_tuple, CounterFunctor{call_count});
    
    REQUIRE(call_count == 4);
}

TEST_CASE("for_ct - Verificar indices secuenciales", "[for_ct][indices]") {
    std::tuple<int, int, int, int, int> test_tuple{10, 20, 30, 40, 50};
    std::vector<std::size_t> indices;
    
    for_ct<0, 5, 1>(test_tuple, IndexVerifierFunctor{indices});
    
    REQUIRE(indices.size() == 5);
    REQUIRE(indices[0] == 0);
    REQUIRE(indices[1] == 1);
    REQUIRE(indices[2] == 2);
    REQUIRE(indices[3] == 3);
    REQUIRE(indices[4] == 4);
}

TEST_CASE("for_ct - Tupla con tipos heterogeneos", "[for_ct][heterogeneous]") {
    std::tuple<int, double, long> test_tuple{42, 3.14, 100L};
    int call_count = 0;
    
    for_ct<0, 3, 1>(test_tuple, CounterFunctor{call_count});
    
    REQUIRE(call_count == 3);
}

TEST_CASE("for_ct - Base como parametro de calculo", "[for_ct][base_param]") {
    std::tuple<int, int, int> test_tuple{1, 2, 3};
    
    SECTION("Base = 2 (binario)") {
        std::vector<int> results;
        for_ct<0, 3, 2>(test_tuple, AccumulatorFunctor{results});
        
        REQUIRE(results[0] == 1 * 2 + 0); // 2
        REQUIRE(results[1] == 2 * 2 + 1); // 5
        REQUIRE(results[2] == 3 * 2 + 2); // 8
    }
    
    SECTION("Base = 16 (hexadecimal)") {
        std::vector<int> results;
        for_ct<0, 3, 16>(test_tuple, AccumulatorFunctor{results});
        
        REQUIRE(results[0] == 1 * 16 + 0); // 16
        REQUIRE(results[1] == 2 * 16 + 1); // 33
        REQUIRE(results[2] == 3 * 16 + 2); // 50
    }
    
    SECTION("Base = 256") {
        std::vector<int> results;
        for_ct<0, 3, 256>(test_tuple, AccumulatorFunctor{results});
        
        REQUIRE(results[0] == 1 * 256 + 0); // 256
        REQUIRE(results[1] == 2 * 256 + 1); // 513
        REQUIRE(results[2] == 3 * 256 + 2); // 770
    }
}

TEST_CASE("for_ct - Tupla vacia (compilacion pero sin ejecucion)", "[for_ct][edge_case]") {
    std::tuple<int> test_tuple{42};
    int call_count = 0;
    
    // Rango vacio: start == end
    for_ct<0, 0, 1>(test_tuple, CounterFunctor{call_count});
    
    REQUIRE(call_count == 0); // No debe llamarse nunca
}

TEST_CASE("for_ct - Tupla grande", "[for_ct][large]") {
    std::tuple<int, int, int, int, int, int, int, int, int, int> 
        test_tuple{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    int call_count = 0;
    for_ct<0, 10, 1>(test_tuple, CounterFunctor{call_count});
    
    REQUIRE(call_count == 10);
}

TEST_CASE("for_ct - Functor constexpr compatible", "[for_ct][constexpr]") {
    // Verifica que for_ct puede usarse con functors simples
    constexpr std::tuple<int, int, int> test_tuple{1, 2, 3};
    
    // Usa functor en lugar de lambda (MSVC no permite template parameters en lambdas locales)
    int sum = 0;
    for_ct<0, 3, 1>(test_tuple, SimpleSumFunctor{sum});
    
    REQUIRE(sum == 6); // 1 + 2 + 3
}

// =============================================================================
// TEST DE USO PRACTICO - CONVERSION DE TUPLA A NUMERO
// =============================================================================

TEST_CASE("for_ct - Caso practico: convertir tupla de digitos a numero", "[for_ct][practical]") {
    /**
     * Simula conversion de registro de digitos a entero
     * Similar a conversion_to_int pero usando for_ct
     */
    
    SECTION("Base 10: {1,2,3} -> 123") {
        std::tuple<int, int, int> digits{1, 2, 3};
        std::uint64_t result = 0;
        
        for_ct<0, 3, 10>(digits, DigitToIntFunctor{result, 10});
        
        REQUIRE(result == 123);
    }
    
    SECTION("Base 2: {1,0,1,1} -> 11 (binario 1011)") {
        std::tuple<int, int, int, int> digits{1, 0, 1, 1};
        std::uint64_t result = 0;
        
        for_ct<0, 4, 2>(digits, DigitToIntFunctor{result, 2});
        
        REQUIRE(result == 11); // 1*8 + 0*4 + 1*2 + 1*1
    }
    
    SECTION("Base 16: {15,10,12} -> 4012 (FAC en hex)") {
        std::tuple<int, int, int> digits{15, 10, 12};
        std::uint64_t result = 0;
        
        for_ct<0, 3, 16>(digits, DigitToIntFunctor{result, 16});
        
        REQUIRE(result == 4012); // 15*256 + 10*16 + 12
    }
}
