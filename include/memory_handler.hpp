#ifndef MEMORY_HANDLER_HPP_INCLUDED
#define MEMORY_HANDLER_HPP_INCLUDED


#include <variant>
#include <string>
#include <ostream>
#include <map>
#include <set>


#include "../include/int_reg_digs_t.hpp"
#include "../include/digit_variant_t.hpp"
#include "../include/variant_types.hpp"

namespace NumRepr {

namespace MemHand {

template<class Variant_t>
class TC_varlist_t {

	using key_t = typename std::string;
	using value_t = Variant_t;
	using node_t = typename std::pair<key_t,value_t>;
	using varlist_t = typename std::map<key_t,value_t>;

protected :

	const std::size_t max_size = 64ull;
	varlist_t lista{};
	static constexpr value_t default_value = Variant_t();

public:

	TC_varlist_t() = default;
	TC_varlist_t(const TC_varlist_t &) = delete;
	TC_varlist_t(TC_varlist_t &&) = delete;
	TC_varlist_t& operator=(const TC_varlist_t&) = delete;
	TC_varlist_t& operator=(TC_varlist_t&&) = delete;

	const varlist_t& getLista() const {
		return (lista);
	}
};


namespace memory_handler {

class dig_var_list {

	using key_t = std::string;
	using value_t = NumRepr::digit_variant;
	using node_t = typename std::pair<key_t,value_t>;
	using varlist_t = typename std::map<key_t,value_t>;

	const std::size_t max_size = 64;
	varlist_t lista{};
	inline static const value_t default_value = dig_t<2>::dig_0();

public:

	dig_var_list() = default;
	dig_var_list(const dig_var_list &) = delete;
	dig_var_list(dig_var_list &&) = delete;
	dig_var_list& operator=(const dig_var_list&) = delete;
	dig_var_list& operator=(dig_var_list&&) = delete;


	std::size_t size() const {
		return lista.size();
	}

	bool contains(std::string nombre) const {
		return lista.contains(nombre);
	}

	bool not_fully() const {
		return (lista.size() < max_size);
	}

	bool create_var(std::string nombre,value_t valor=default_value) {
		if (!contains(nombre) && not_fully()) {
			lista.insert({nombre,valor});
			return true;
		}
		return false;
	}

	bool operator()(std::string nombre,value_t valor) {
		if (contains(nombre)) {
			lista[nombre] = valor;
			return true;
		}
		else if (not_fully()) {
			lista.insert({nombre,valor});
			return true;
		}
		else
			return false;
	}

	auto operator()(std::string nombre) const {
		if (contains(nombre)) {
			return (lista.at(nombre));
		}
		else {
			return (default_value);
		}
	}

	bool erase_var(std::string nombre) {
		if (contains(nombre)) {
			lista.erase(nombre);
			return true;
		}
		return false;
	}

};

bool create_var(
	dig_var_list& cont,std::string nombre,
	std::uint64_t radix,std::uint64_t intvalue
);

std::string to_string(
	const dig_var_list& cont,std::string nombre
);

//std::ostream& operator<<(
//	std::ostream& os,const std::pair<const dig_var_list&,const std::string>& obj
//);

bool suma_y_asigna(
	dig_var_list& cont,std::string nombre,std::string otronombre
);

template<std::uint64_t base>
using bool_funct_dig = bool (dig_t<base>::*)();
template<std::uint64_t base>
using dig_funct_dig = dig_t<base> (dig_t<base>::*)();
template<std::uint64_t base>
using uint_funct_dig = dig_t<base>::UINT_T (dig_t<base>::*)();

//decltype(auto) func_variant(bool_funct_dig<base> func , genRadixDig_t arg );
//template<std::uint64_t base>
//  requires ((base > 1ULL) && (base < 255ULL))
//decltype(auto) func_variant(dig_funct_dig<base> func , genRadixDig_t arg );
//template<std::uint64_t base>
//  requires ((base > 1ULL) && (base < 255ULL))
//decltype(auto) func_variant(uint_funct_dig<base> func , genRadixDig_t arg );

} // namespace memory_handler
} // namespace NumRepr
#endif // MEMORY_HANDLER_HPP_INCLUDED
