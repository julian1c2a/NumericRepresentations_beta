#ifndef AUXILIARY_FUNCTIONS_HPP_INCLUDED
#define AUXILIARY_FUNCTIONS_HPP_INCLUDED

#include "core/internal/auxiliary_functions.hpp"

// Top-level compatibility wrapper.
// The real implementations live in include/core/internal/auxiliary_functions.hpp
// Keep the old API names available by forwarding to the new implementations.

namespace NumRepr {
  namespace auxiliary_functions {

    constexpr inline
    std::uint64_t integer_power(std::uint64_t base, std::uint32_t exponent) noexcept {
      return NumRepr::auxiliary_functions::int_pow(base, exponent);
    }

    // count_digits functions are provided by the internal header; expose them
    // via the same namespace by inclusion above. No extra definitions needed.

  } // namespace auxiliary_functions
} // namespace NumRepr

#endif // AUXILIARY_FUNCTIONS_HPP_INCLUDED
