#ifndef SEVERAL_VARLISTS_DEFINITION_H
#define SEVERAL_VARLISTS_DEFINITION_H

#include "memory_handler.hpp"
#include "digit_variant_t.hpp"

namespace NumRepr {
namespace MemHand {

class ullint_varlist_t: public TC_varlist_t<unsigned long long> {
public:
	bool create_var(std::string nombre,unsigned long long int valor) {
		if (!contains(nombre) && not_fully()) {
			lista.insert({nombre,valor});
			return true;
		}
		return false;
	}
};

class llint_varlist_t: public TC_varlist_t<long long> {
public:
	bool create_var(std::string nombre,long long int valor) {
		if (!contains(nombre) && not_fully()) {
			lista.insert({nombre,valor});
			return true;
		}
		return false;
	}
};

class ld_varlist_t: public TC_varlist_t<long double> {
public:
	bool create_var(std::string nombre,long double valor) {
		if (!contains(nombre) && not_fully()) {
			lista.insert({nombre,valor});
			return true;
		}
		return false;
	}
};

class digit_varlist_t: public TC_varlist_t<digit_variant> {
public:
	bool create_var(std::string nombre,unsigned long long int base,long long int valor) {
		if (!contains(nombre) && not_fully()) {
			lista.insert({nombre,make_digit_variant(base,valor)});
			return true;
		}
		return false;
	}
};

} // namespace memory_handler
} // namespace NumRepr

#endif // SEVERAL_VARLISTS_DEFINITION_H
