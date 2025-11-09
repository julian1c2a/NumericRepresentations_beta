#include <iostream>
#include "core/dig_t.hpp"

using namespace NumRepr;

int main()
{
    std::cout << "=== Debug Large Numbers Test ===" << std::endl;

    // Test with large numbers (should modulo)
    dig_t<10> large_strict("d[999999]B10");
    dig_t<10> large_legacy("dig#999999#B10");

    std::cout << "large_strict value: " << (int)large_strict.get() << std::endl;
    std::cout << "large_legacy value: " << (int)large_legacy.get() << std::endl;
    std::cout << "999999 % 10 = " << (999999 % 10) << std::endl;

    // Test what they should be
    std::cout << "Expected: 9, Got strict: " << (int)large_strict.get() << ", legacy: " << (int)large_legacy.get() << std::endl;

    return 0;
}