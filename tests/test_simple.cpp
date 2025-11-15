
#include <iostream>
#include <core/dig_t.hpp>

using namespace NumRepr;

int main() {
    std::cout << "Testing basic compilation..." << std::endl;
    
    // Test basic dig_t instantiation
    dig_t<10> d1{5};
    std::cout << "dig_t<10>: " << d1.to_string() << std::endl;
    
    return 0;
}