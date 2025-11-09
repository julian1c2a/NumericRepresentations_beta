#ifndef UTIL_FUNCTS_HPP_INCLUDED
#define UTIL_FUNCTS_HPP_INCLUDED

#include "core/internal/auxiliary_functions.hpp"

// Lightweight compatibility wrapper that forwards to the new
// NumRepr::auxiliary_functions::int_* implementations. This keeps the
// `util_functs` API working while allowing the real implementations to
// live in the centralized internal header.

namespace util_functs {

template<std::uint64_t N>
consteval std::uint64_t pow2ct() noexcept { return NumRepr::auxiliary_functions::int_pow2ct<N>(); }

template<std::uint64_t N>
consteval std::uint64_t log2ct() noexcept { return NumRepr::auxiliary_functions::int_log2ct<N>(); }

constexpr std::uint64_t pow2(std::uint64_t n) noexcept { return NumRepr::auxiliary_functions::int_pow2(n); }

constexpr std::uint64_t log2(std::uint64_t n) noexcept { return NumRepr::auxiliary_functions::int_log2(n); }

} // namespace util_functs

#endif // UTIL_FUNCTS_HPP_INCLUDED
