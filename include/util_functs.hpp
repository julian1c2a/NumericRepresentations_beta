#ifndef UTIL_FUNCTS_HPP_INCLUDED
#define UTIL_FUNCTS_HPP_INCLUDED

#include <cstdlib>
#include <cstdint>

namespace util_functs {

template<std::uint64_t>
consteval std::uint64_t pow2ct();
template<std::uint64_t>
consteval std::uint64_t log2ct();

constexpr std::uint64_t pow2(std::uint64_t);
constexpr std::uint64_t log2(std::uint64_t);

template<std::uint64_t n>
consteval std::uint64_t pow2ct() {
	if constexpr (n == 0) {
		return 1ull;
	}
	else if constexpr (n == 1) {
		return 2ull;
	}
	else {
		return (2ull*pow2ct<n-1ull>());
	}
}

constexpr std::uint64_t pow2(std::uint64_t n) {
	if (n == 0) {
		return 1ull;
	}
	else if (n == 1) {
		return 2ull;
	}
	else {
		return (2ull*pow2(n-1ull));
	}
}

template<std::uint64_t n>
  requires (n>0)
consteval std::uint64_t log2ct() {
	if constexpr (n == 1) {
		return 0ull;
	}
	else if constexpr (n == 2) {
		return 1ull;
	}
	else if constexpr (n <= 4) {
		return 2ull;
	}
	else if constexpr (n <= 8) {
		return 3ull;
	}
	else if constexpr (n <= 16) {
		return 4ull;
	}
	else if constexpr (n <= 32) {
		return 5ull;
	}
	else if constexpr (n <= 64) {
		return 6ull;
	}
	else if constexpr (n <= 128) {
		return 7ull;
	}
	else if constexpr (n <= 256) {
		return 8ull;
	}
	else if constexpr (n <= 512) {
		return 9ull;
	}
	else if constexpr (n <= 1024) {
		return 10ull;
	}
	else if constexpr (n <= 2048) {
		return 11ull;
	}
	else if constexpr (n <= 4096) {
		return 12ull;
	}
	else if constexpr (n <= 8192) {
		return 13ull;
	}
	else if constexpr (n <= 16384) {
		return 14ull;
	}
	else if constexpr (n <= 32768) {
		return 15ull;
	}
	else if constexpr (n <= 65536) {
		return 16ull;
	}
	else {
		return (1+log2ct<n/2>());
	}
}

constexpr std::uint64_t log2(std::uint64_t n) {
	if (n <= 1) {
		return 0ull;
	}
	else if (n <= 2) {
		return 1ull;
	}
	else if (n <= 4) {
		return 2ull;
	}
	else if (n <= 8) {
		return 3ull;
	}
	else if (n <= 16) {
		return 4ull;
	}
	else if (n <= 32) {
		return 5ull;
	}
	else if (n <= 64) {
		return 6ull;
	}
	else if (n <= 128) {
		return 7ull;
	}
	else if (n <= 256) {
		return 8ull;
	}
	else if (n <= 512) {
		return 9ull;
	}
	else if (n <= 1024) {
		return 10ull;
	}
	else if (n <= 2048) {
		return 11ull;
	}
	else if (n <= 4096) {
		return 12ull;
	}
	else if (n <= 8192) {
		return 13ull;
	}
	else if (n <= 16384) {
		return 14ull;
	}
	else if (n <= 32768) {
		return 15ull;
	}
	else if (n <= 65536) {
		return 16ull;
	}
	else {
		return (1+log2(n/2));
	}
}

}/// END OF NAMESPACE UTIL_FUNCTS

#endif // UTIL_FUNCTS_HPP_INCLUDED
