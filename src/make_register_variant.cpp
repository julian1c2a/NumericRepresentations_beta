#include <cstdlib>
#include <cstdint>
#include "../include/util_functs.hpp"
#include "../include/reg_digs_t.hpp"
#include "../include/register_variant_t.hpp"

namespace NumRepr {

/// PREGUNTA: PORQUÉ NO FUNCIONA ESTA FORMA DE HACER UN SWITCH/CASE
//	namespace detail {
//
//		using function_type = typename NumRepr::register_variant_t(std::int64_t);
//
//		template<std::uint64_t BASE,std::uint64_t LONGITUD>
//		using functsArray_t = typename std::array<function_type,BASE*LONGITUD>;
//
//		template<std::uint64_t BASE,std::uint64_t LONGITUD>
//		register_variant_t local_fn(std::int64_t valor)
//		{
//			return
//				register_variant_t(
//					reg_digs_t<BASE,LONGITUD>(valor)
//				)
//			;
//		}
//
//
//		template<std::uint64_t ...Ixs>
//		constexpr auto fn(std::index_sequence<Ixs...>) {
//			const functsArray_t<bvar_sz,lvar_sz> result{
//				(local_fn<(Ixs/lvar_sz)+2,util_functs::pow2ct<Ixs%lvar_sz>()>(std::int64_t)
//				...)
//			};
//			return result;
//		}
//
//		class factory_register_variant_t {
//
//			constexpr inline static
//			functsArray_t<bvar_sz,lvar_sz>
//				funct_array{
//					fn(
//						std::make_index_sequence<
//							lvar_sz*bvar_sz
//						>{}
//					)
//				}
//			;
//
//
//
//		public:
//
//			static register_variant_t operator()(
//				std::uint64_t base,
//				std::uint64_t longitud,
//				std::int64_t valor)
//			{
//				const auto objfunct{funct_array[
//						(base-2)*lvar_sz	+
//						util_functs::log2(longitud)
//					]
//				};
//				return objfunct(valor);
//			}
//		};
//	} /// END OF NAMESPACE NUMREPR::DETAIL
//
//	register_variant_t gobj_register_variant(std::uint64_t base,std::uint64_t longitud,std::int64_t valor) {
//		static typename detail::factory_register_variant_t funct{};
//		return funct(base,longitud,valor);
//	}



register_variant_t make_register_variant
	(
		std::uint64_t base , std::uint64_t longitud , std::int64_t valor
	)
{
	switch (base) {
	case 2ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<2ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<2ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<2ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<2ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<2ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<2ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<2ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<2ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 3ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<3ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<3ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<3ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<3ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<3ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<3ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<3ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<3ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 4ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<4ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<4ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<4ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<4ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<4ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<4ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<4ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<4ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 5ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<5ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<5ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<5ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<5ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<5ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<5ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<5ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<5ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 6ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<6ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<6ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<6ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<6ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<6ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<6ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<6ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<6ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 7ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<7ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<7ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<7ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<7ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<7ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<7ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<7ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<7ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 8ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<8ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<8ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<8ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<8ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<8ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<8ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<8ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<8ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 9ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<9ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<9ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<9ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<9ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<9ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<9ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<9ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<9ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 10ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<10ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<10ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<10ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<10ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<10ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<10ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<10ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<10ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 11ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<11ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<11ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<11ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<11ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<11ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<11ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<11ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<11ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 12ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<12ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<12ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<12ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<12ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<12ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<12ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<12ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<12ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 13ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<13ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<13ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<13ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<13ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<13ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<13ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<13ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<13ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 14ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<14ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<14ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<14ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<14ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<14ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<14ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<14ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<14ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 15ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<15ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<15ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<15ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<15ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<15ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<15ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<15ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<15ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 16ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<16ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<16ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<16ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<16ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<16ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<16ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<16ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<16ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 17ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<17ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<17ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<17ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<17ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<17ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<17ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<17ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<17ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 18ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<18ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<18ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<18ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<18ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<18ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<18ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<18ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<18ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 19ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<19ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<19ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<19ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<19ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<19ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<19ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<19ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<19ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 20ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<20ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<20ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<20ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<20ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<20ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<20ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<20ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<20ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 21ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<21ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<21ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<21ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<21ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<21ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<21ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<21ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<21ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 22ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<22ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<22ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<22ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<22ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<22ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<22ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<22ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<22ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 23ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<23ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<23ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<23ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<23ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<23ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<23ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<23ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<23ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 24ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<24ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<24ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<24ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<24ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<24ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<24ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<24ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<24ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 25ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<25ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<25ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<25ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<25ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<25ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<25ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<25ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<25ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 26ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<26ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<26ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<26ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<26ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<26ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<26ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<26ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<26ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 27ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<27ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<27ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<27ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<27ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<27ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<27ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<27ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<27ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 28ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<28ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<28ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<28ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<28ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<28ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<28ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<28ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<28ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 29ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<29ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<29ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<29ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<29ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<29ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<29ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<29ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<29ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 30ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<30ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<30ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<30ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<30ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<30ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<30ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<30ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<30ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 31ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<31ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<31ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<31ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<31ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<31ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<31ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<31ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<31ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 32ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<32ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<32ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<32ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<32ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<32ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<32ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<32ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<32ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 33ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<33ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<33ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<33ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<33ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<33ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<33ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<33ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<33ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 34ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<34ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<34ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<34ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<34ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<34ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<34ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<34ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<34ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 35ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<35ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<35ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<35ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<35ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<35ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<35ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<35ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<35ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 36ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<36ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<36ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<36ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<36ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<36ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<36ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<36ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<36ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 37ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<37ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<37ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<37ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<37ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<37ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<37ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<37ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<37ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 38ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<38ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<38ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<38ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<38ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<38ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<38ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<38ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<38ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 39ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<39ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<39ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<39ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<39ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<39ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<39ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<39ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<39ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 40ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<40ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<40ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<40ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<40ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<40ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<40ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<40ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<40ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 41ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<41ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<41ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<41ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<41ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<41ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<41ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<41ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<41ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 42ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<42ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<42ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<42ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<42ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<42ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<42ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<42ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<42ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 43ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<43ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<43ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<43ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<43ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<43ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<43ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<43ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<43ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 44ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<44ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<44ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<44ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<44ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<44ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<44ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<44ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<44ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 45ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<45ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<45ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<45ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<45ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<45ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<45ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<45ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<45ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 46ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<46ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<46ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<46ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<46ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<46ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<46ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<46ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<46ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 47ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<47ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<47ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<47ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<47ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<47ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<47ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<47ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<47ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 48ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<48ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<48ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<48ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<48ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<48ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<48ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<48ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<48ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 49ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<49ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<49ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<49ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<49ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<49ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<49ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<49ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<49ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 50ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<50ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<50ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<50ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<50ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<50ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<50ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<50ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<50ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 51ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<51ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<51ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<51ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<51ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<51ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<51ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<51ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<51ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 52ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<52ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<52ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<52ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<52ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<52ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<52ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<52ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<52ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 53ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<53ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<53ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<53ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<53ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<53ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<53ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<53ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<53ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 54ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<54ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<54ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<54ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<54ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<54ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<54ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<54ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<54ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 55ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<55ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<55ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<55ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<55ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<55ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<55ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<55ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<55ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 56ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<56ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<56ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<56ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<56ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<56ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<56ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<56ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<56ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 57ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<57ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<57ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<57ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<57ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<57ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<57ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<57ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<57ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 58ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<58ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<58ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<58ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<58ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<58ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<58ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<58ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<58ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 59ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<59ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<59ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<59ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<59ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<59ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<59ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<59ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<59ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 60ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<60ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<60ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<60ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<60ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<60ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<60ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<60ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<60ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 61ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<61ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<61ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<61ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<61ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<61ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<61ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<61ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<61ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 62ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<62ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<62ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<62ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<62ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<62ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<62ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<62ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<62ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 63ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<63ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<63ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<63ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<63ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<63ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<63ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<63ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<63ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 64ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<64ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<64ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<64ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<64ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<64ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<64ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<64ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<64ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	case 65ull :
		switch (longitud) {
		case 1ull : {reg_digs_t<65ull,1ull> result; result = valor; return register_variant_t{result};}
		case 2ull : {reg_digs_t<65ull,2ull> result; result = valor; return register_variant_t{result};}
		case 4ull : {reg_digs_t<65ull,4ull> result; result = valor; return register_variant_t{result};}
		case 8ull : {reg_digs_t<65ull,8ull> result; result = valor; return register_variant_t{result};}
		case 16ull : {reg_digs_t<65ull,16ull> result; result = valor; return register_variant_t{result};}
		case 32ull : {reg_digs_t<65ull,32ull> result; result = valor; return register_variant_t{result};}
		case 64ull : {reg_digs_t<65ull,64ull> result; result = valor; return register_variant_t{result};}
		case 128ull : {reg_digs_t<65ull,128ull> result; result = valor; return register_variant_t{result};}
		default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}
	default : {return register_variant_t{reg_digs_t<2ull,1ull>{}};}
	}

}

} /// END OF NAMESPACE NUMREPR IN THIS TRANSLATION UNIT
