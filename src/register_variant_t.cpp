
#include <variant>
#include <array>
#include "../include/reg_digs_t.hpp"
#include "../include/digit_variant_t.hpp"
#include "../include/register_variant_t.hpp"

namespace NumRepr {

/// COMIENZO DE ESTE CPP (IMPLEMENTACIONES)

	constexpr register_variant_t::UINT_T register_variant_t::gbase() const noexcept {
  		const auto indice{this->index()};
  		return ((indice/lvar_sz)+2ull);
  	}

	constexpr register_variant_t::UINT_T register_variant_t::glong() const noexcept {
  		const auto indice{this->index()};
  		const auto pow2result{indice%lvar_sz};
  		const auto result{util_functs::log2(pow2result)};
  		return result;
  	}

  	constexpr digit_variant register_variant_t::dig_0(std::uint64_t base) const noexcept {
  		return make_digit_variant(base,0);
  	}

  	constexpr digit_variant register_variant_t::dig_0() const noexcept {
  		return make_digit_variant(gbase(),0);
  	}

  	constexpr digit_variant register_variant_t::dig_1(std::uint64_t base) const noexcept {
  		return make_digit_variant(base,1);
  	}

  	constexpr digit_variant register_variant_t::dig_1() const noexcept {
  		return make_digit_variant(gbase(),1);
  	}

  	constexpr digit_variant register_variant_t::dig_Bm1(std::uint64_t base) const noexcept {
  		return make_digit_variant(base,base-1);
  	}

  	constexpr digit_variant register_variant_t::dig_Bm1() const noexcept {
  		return make_digit_variant(gbase(),gbase()-1);
  	}

  	constexpr digit_variant register_variant_t::dig_Bm2(std::uint64_t base) const noexcept {
  		return make_digit_variant(base,base-2);
  	}

  	constexpr digit_variant register_variant_t::dig_Bm2() const noexcept {
  		return make_digit_variant(gbase(),gbase()-2);
  	}

	constexpr register_variant_t register_variant_t::regd_0() const noexcept {
		return make_register_variant(gbase(),glong(),0);
	}

  	constexpr register_variant_t register_variant_t::regd_1() const noexcept {
		return make_register_variant(gbase(),glong(),1);
	}

	constexpr register_variant_t register_variant_t::regd_Bm1() const noexcept {
		return make_register_variant(gbase(),glong(),gbase()-1);
	}

  	constexpr register_variant_t register_variant_t::regd_B() const noexcept {
		return make_register_variant(gbase(),glong(),gbase());
	}

  	constexpr register_variant_t register_variant_t::regd_Bp1() const noexcept {
		return make_register_variant(gbase(),glong(),gbase()+1);
	}

  	template<std::uint64_t n>
  	constexpr register_variant_t register_variant_t::regd_pow_n_B() const noexcept {
  		register_variant_t result;
		const auto fn =
			[&result]<std::uint64_t B,std::uint64_t L>(
				const reg_digs_t<B,L>& arg
			)
				-> register_variant_t
			{
				result = reg_digs_t<B,L>::template regd_pow_n_B<n>();
				return result;
			}
		;
		return std::visit(fn,*this);
	}

	template<std::uint64_t n>
  	constexpr register_variant_t register_variant_t::regd_pow_n_B_m1() const noexcept {
  		register_variant_t result;
		const auto fn =
			[&result]<std::uint64_t B,std::uint64_t L>(
				const reg_digs_t<B,L>& arg
			)
				-> register_variant_t
			{
				result = reg_digs_t<B,L>::template regd_pow_n_Bm1<n>();
				return result;
			}
		;
		return std::visit(fn,*this);
	}

  /// <summary>
  /// En heredamos como clase derivada de base_t == std::array<B,L>
  /// Tenemos todos los métodos de la STL
  /// </summary>

  constexpr decltype(auto) register_variant_t::begin()         noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(reg_digs_t<B,L>& arg)
  			-> decltype(auto)
  		{
  			return (arg.begin());
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr decltype(auto) register_variant_t::cbegin()  const noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(const reg_digs_t<B,L>& arg)
  			-> decltype(auto)
  		{
  			return (arg.cbegin());
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr decltype(auto) register_variant_t::end() noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(reg_digs_t<B,L>& arg)
  			-> decltype(auto)
  		{
  			return (arg.end());
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr decltype(auto) register_variant_t::cend() const noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(const reg_digs_t<B,L>& arg)
  			-> decltype(auto)
  		{
  			return (arg.cend());
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr decltype(auto) register_variant_t::rbegin()        noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(reg_digs_t<B,L>& arg)
  			-> decltype(auto)
  		{
  			return (arg.rbegin());
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr decltype(auto) register_variant_t::crbegin() const noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(const reg_digs_t<B,L>& arg)
  			-> decltype(auto)
  		{
  			return (arg.crbegin());
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr decltype(auto) register_variant_t::rend() noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(reg_digs_t<B,L>& arg)
  			-> decltype(auto)
  		{
  			return (arg.rend());
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr decltype(auto) register_variant_t::crend()   const noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(const reg_digs_t<B,L>& arg)
  			-> decltype(auto)
  		{
  			return (arg.crend());
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr std::size_t register_variant_t::size() const noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(const reg_digs_t<B,L>& arg)
  			-> std::size_t
  		{
  			return (arg.size());
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr std::size_t register_variant_t::max_size() const noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(const reg_digs_t<B,L>& arg)
  			-> std::size_t
  		{
  			return (arg.max_size());
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr bool register_variant_t::empty() const noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(const reg_digs_t<B,L>& arg)
  			-> bool
  		{
  			return (arg.empty());
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr digit_variant& register_variant_t::front() noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(reg_digs_t<B,L>& este)
  			-> digit_variant&
  		{
  			auto& result{este.front()};
  			return result;
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr digit_variant const& register_variant_t::front() const noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(const reg_digs_t<B,L>& este)
  			-> digit_variant&
  		{
  			const auto& result{este.front()};
  			return result;
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr digit_variant& register_variant_t::back() noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(reg_digs_t<B,L>& este)
  			-> digit_variant&
  		{
  			auto& result{este.back()};
  			return result;
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr digit_variant const& register_variant_t::back() const noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(const reg_digs_t<B,L>& este)
  			-> digit_variant&
  		{
  			const auto& result{este.back};
  			return result;
  		}
	;
	return std::visit(fn,*this);
  }

  constexpr void register_variant_t::fill(const digit_variant& value) noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L,std::uint64_t R>(
			reg_digs_t<B,L>& este , const dig_t<R>& otro
		)
		{
			if constexpr (B == R) {
				este.fill(otro);
			}
		}
	;
	std::visit(fn,*this,value);
  }

  constexpr void register_variant_t::swap(register_variant_t& other) noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L,std::uint64_t R, std::uint64_t N> (
			reg_digs_t<B,L>& left , reg_digs_t<R,N>& right
		) {
			if constexpr ((B == R) && (L == N)) {
				left.swap(right);
			}
		}
	;
	std::visit(fn,*this,other);
  }

  constexpr void register_variant_t::reverse() noexcept  {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L> (reg_digs_t<B,L>& left)
  		{ left.reverse(); }
	;
	std::visit(fn,*this);
  }

  /// <summary>
  ///
  ///
  ///
  ///    Constructores de register_variant_t
  ///
  ///
  ///
  /// </summary>


  /// <summary>
  /// Constructor por defecto (rellena de digit_variant(0) todo el array)
  /// </summary>
//  template<std::size_t B,std::size_t N>
//  constexpr register_variant_t::register_variant_t() noexcept :
//  	register_variant(reg_digs_t<B,N>::regd_base_0())
//  {}

//  MEJOR HACERLO CON MAKE_REGISTER_VARIANT
//  constexpr register_variant_t::register_variant_t(std::uint64_t B,std::uint64_t L) noexcept :
//  	register_variant(make_register_variant(B,L,0))
//  {}

  /// <summary>
  /// Constructor por argumentos tipo dig_t: deduce el tipo
  /// </summary>
//  template <std::size_t B,typename... Ts>
//    requires(std::is_same_v<Ts, dig_t<B>> &&  ...)
//  constexpr register_variant_t(const Ts& ...args) noexcept
//      : register_variant(reg_digs_t<B,sizeof...(Ts)>::base_t{(utilities::ugly_pack_details::pack2array<const Ts& ...>{})(args...)}) {}

  /// CONSTRUCTOR COPIA DESDE EL TIPO BASE
//  template<std::size_t B,std::size_t N>
//  constexpr register_variant_t::register_variant_t(const reg_digs_t<B,N>& rarg) noexcept : register_variant{rarg} {}

  /// CONSTRUCTOR MOVIMIENTO DESDE EL TIPO BASE
//  template<std::size_t B,std::size_t N>
//  constexpr register_variant_t::register_variant_t(reg_digs_t<B,N>&& rarg) noexcept
//      : register_variant{std::move(rarg)} {}

  /// <summary>
  /// Constructor por Copia/Movimiento desde una
  /// sucesión variadica de dígitos dig_t
  /// </summary>

  /// <summary>
  /// Constructor copia desde un array cualquiera de dígitos dig_t
  /// (usando copy_arg_N<N>)
  /// </summary>
//  template <std::size_t B,std::size_t N>
//  constexpr register_variant_t::register_variant_t(const reg_digs_t<B,N>& arg) noexcept
//      : register_variant{copy_arg_N<B,N>(arg)} {}

  /// <summary>
  /// Constructor por movimiento desde un array cualquiera de dígitos dig_t
  /// (usando move_arg_N<N>)
  /// </summary>
//  template <std::size_t B,std::size_t N>
//  constexpr register_variant_t::register_variant_t(reg_digs_t<B,N>&& arg) noexcept
//      : register_variant{std::move(move_arg_N<B,N>(std::move(arg)))} {}

  /// <summary="Constructor copia desde una sucesión de objetos enteros
  /// variádica, normalizándolos">
  /// </summary>

//  template <std::size_t B,std::size_t L,type_traits::integral_c... Ints_type>
//    requires((sizeof...(Ints_type)) == L)
//  constexpr register_variant_t::register_variant_t(Ints_type... dig_pow_i) noexcept
//      : register_variant(reg_digs_t<B,L>((normalize<Ints_type...>((dig_t<B>(dig_pow_i))()...)).reverse())) {}

  /// <summary>
  /// Sobrecarga del operador copia
  /// </summary>

  /// OPERACION ASIGNACION POR COPIA REFERENCIA
  /// CONST _NO_ COPIABLE DESDE REG_N_DIGS_T EN LA IZQUIERDA
//  template <std::size_t B,std::size_t N>
//  constexpr const register_variant_t&
//  register_variant_t::operator=(const reg_digs_t<B,N>& arg) noexcept {
//  	(*this) = arg;
//  	return (*this);
//  }

  /// OPERACION ASIGNACION POR COPIA REFERENCIA
  /// DESDE REG_N_DIGS_T EN LA IZQUIERDA
//  template <std::size_t B,std::size_t N>
//  constexpr register_variant_t&
//  register_variant_t::operator=(reg_digs_t<B,N>& arg) noexcept {
//  	(*this) = arg;
//  	return (*this);
//  }

  /// OPERACION ASIGNACION POR MOVIMIENTO
  /// DESDE REGS_N_DIGS_T EN LA QUE NO SE PUEDE COPIAR
//  template <std::size_t B,std::size_t N>
//  constexpr const register_variant_t&
//  register_variant_t::operator=(reg_digs_t<B,N>&& arg) noexcept {
//  	(*this) = std::move(arg);
//  	return (*this);
//  }

  /// OPERACION COPIA DESDE UN DIGITO (CONVERSION)
  constexpr register_variant_t&
  register_variant_t::operator=(const digit_variant& arg) noexcept {
  	const auto prefn = [this]<std::uint64_t B>(const dig_t<B> & otroarg) {
  		if (B != gbase())
  			*this = make_register_variant(B,glong(),0);
		else
			this->set_0();
  	};
  	std::visit(prefn,arg);
  	const auto fn = [&arg]<std::uint64_t B,std::uint64_t L>(reg_digs_t<B,L>& este,const dig_t<B>& otro) {
  		este[0] = otro;
  	};
  	std::visit(fn,*this,arg);
  	return (*this);
  }

  /// OPERACION COPIA DESDE UN ENTERO (CONVERSION A LA BASE B)
  /// A UN REG_DIGS_T
  template <type_traits::integral_c Int_Type>
  constexpr const register_variant_t&
  register_variant_t::operator=(Int_Type arg) noexcept {
  	const auto fn =
  		[arg]<std::uint64_t B,std::uint64_t L>(reg_digs_t<B,L>& left)
  			-> const register_variant_t&
  		{
  			left = arg;
  			return (left);
  		}
  	;
  	return std::visit(fn,*this);
  }

  ///
  ///       Algunas Conversiones
  ///

  /// PUEDE SER QUE NO QUEPA EN EL TIPO ENTERO
  template <type_traits::integral_c Int_Type>
  constexpr explicit
  register_variant_t::operator Int_Type() const noexcept {
  	const auto fn =
  		[]<std::uint64_t B,std::uint64_t L>(const reg_digs_t<B,L>& arg)
  			-> Int_Type
  		{
  			return static_cast<Int_Type>(arg);
  		}
	;
	return std::visit(fn,*this);
  }

  ///< summary="Sobrecarga del digit_variant operator[](std::size_t)
  ///< const"></summary>
  /// HEREDADA DE LA CLASE STD::ARRAY DE LA STL
  constexpr digit_variant operator[](std::size_t ix) const noexcept;

  ///< summary="Sobrecarga del digit_variant operator[](std::size_t)"></summary>
  /// HEREDADA DE LA CLASE STD::ARRAY DE LA STL
  constexpr digit_variant& operator[](std::size_t ix) noexcept;

  ///< summary="Sobrecarga del digit_variant operator[](std::size_t)
  ///< const"></summary>
  constexpr auto register_variant_t::operator()(std::size_t ix) const noexcept {
  	const auto fn =
  		[ix]<std::uint64_t B,std::uint64_t L>(const reg_digs_t<B,L>& arg)
  			-> auto
		{
			return digit_variant(arg[ix]);
		}
  	;
  	return std::visit(fn,*this);
  }

  ///< summary>
  /// Funciones que ponen a constantes (constexpr) los objetos base_t
  ///</summary>
  ///< typeparam name="std::size_t"></typeparam>
  ///< nontypeparam name="N"></nontypeparam>
  ///< param name="this"></param>
  ///< returns name="void"></returns>

  constexpr void register_variant_t::set_0()               		noexcept;

  constexpr void register_variant_t::set_1()               		noexcept;

  constexpr void register_variant_t::set_Bm1()             		noexcept;
  template<std::size_t B>
  constexpr void register_variant_t::set_dig(dig_t<B> d)      	noexcept;
  template<std::size_t B>
  constexpr void register_variant_t::set_fill_dig(dig_t<B> d) 	noexcept;

  constexpr void register_variant_t::set_fill_1()          		noexcept;

  constexpr void register_variant_t::set_fill_Bm1()        		noexcept;

  ///< summary>
  ///"Funciones que ponen a constantes(constexpr) los objetos un subintervalo
  /// o subrango de base_t cualquiera"
  ///</summary>
  ///< typeparam name="std::size_t"></typeparam>
  ///< nontypeparam name="N_i"></nontypeparam>
  ///< nontypeparam name="N_pf"></nontypeparam>
  ///< param name="this"></param>
  ///< returns name="void"></returns>

  /// OPERACION DE PONER A VALOR DIG_0 DEL ARRAY
  /// DESDE [N_0 , N_1) EN BASE_N_T<N>
  template <std::size_t N_i, std::size_t N_pf> // i  es inicio
                                     // pf es pasado el final STL
    requires((N_i < N_pf) && (N_pf <= L))
  constexpr void register_variant_t::set_interval_0() noexcept;

  /// OPERACION DE PONER A VALOR DIG_Bm1 DEL ARRAY
  ///	DESDE [N_0 , N_1) EN BASE_N_T<N>
  template <std::size_t N, std::size_t N_i, std::size_t N_pf> // i  es inicio
                                               // pf es pasado el final
    requires((N_i < N_pf) && (N_pf <= L))
  constexpr void register_variant_t::set_interval_Bm1() noexcept;

  /// OPERACION DE PONER A VALOR DIG DEL ARRAY
  ///	DESDE [N_0 , N_1) EN BASE_T
  template <std::size_t N_i, std::size_t N_pf> // i  es inicio
                                     // pf es pasado el final
    requires((N_i < N_pf) && (N_pf <= L))
  constexpr void register_variant_t::set_interval_dig(dig_t dig) noexcept;

  ///< summary="Funciones comparativas con constantes tipo constexpr"></summary>
  ///< param name="this"></param>
  ///< returns="bool"></returns>

//  constexpr bool register_variant_t::is_0() const noexcept;
//
//  constexpr bool register_variant_t::is_1() const noexcept;
//
//  constexpr bool register_variant_t::is_Bm1() const noexcept;
//
//  constexpr bool register_variant_t::is_B() const noexcept;
//
//  constexpr bool register_variant_t::register_variant_t::is_Bp1() const noexcept;
//
//  template <std::size_t n>
//  constexpr bool register_variant_t::is_B_pow_m1() const noexcept;
//
//  template <std::size_t n>
//  constexpr bool register_variant_t::is_B_pow() const noexcept;
//
//  constexpr bool register_variant_t::is_any_B_pow() const noexcept;
//
//  constexpr bool register_variant_t::is_filled_of_1() const noexcept;
//
//  constexpr bool register_variant_t::is_filled_of_Bm1() const noexcept;
//  template<std::size_t B>
//  constexpr bool register_variant_t::is_filled_of(dig_t<B> d) const noexcept;
//
//  ///		STATIC FUNCTIONS :  CONCATENATE REGISTERS AND DIGITS
//  /// 		reg_digs_t<1>		cat(dig_t)
//  /// 		reg_digs_t<1+1>		cat(dig_t,dig_t)
//  /// 		reg_digs_t			cat(reg_digs_t)
//  ///   <M> reg_N_digs_t<L+M>	cat(reg_digs_t,reg_N_digs_t<M>)
//  /// 		reg_N_digs_t<L+1>	cat(reg_digs_t,dig_t)
//  /// 		reg_N_digs_t<1+L>	cat(dig_t,reg_digs_t)
//  /// 		reg_N_digs_t<sizeof...(dig_pack)>
//  ///							cat(dig_t ... dig_pack) VARIADIC PACK
//
//  /// STATIC REG_DIGS_T CAT(REG_DIGS_T)
//  constexpr
//  register_variant_t register_variant_t::cat(const register_variant_t& arg) const noexcept;
//
//  /// STATIC <M> REG_N_DIGS_T<L+M> CAT(REG_DIGS_T,REG_N_DIGS_T<M>)
//  constexpr register_variant_t
//  register_variant_t::cat(const register_variant_t& larg, const register_variant_t& rarg) const noexcept;
//
//  /// STATIC REG_N_DIGS_T<1+1> CAT(DIG_T,DIG_T)
//  template<std::size_t B>
//  constexpr register_variant_t register_variant_t::cat(dig_t<B> larg, dig_t<B> rarg) const noexcept;
//
//  /// STATIC REG_N_DIGS_T<SIZEOF...(DIG_PACK)>
//  /// CAT(DIG_T,DIG_T ... DIG_PACK) VARIADIC
//  template <std::size_t B, typename T0, typename... Ts>
//    requires(((std::is_same_v<Ts, dig_t<B>>)&& ...) && (std::is_same_v<T0, dig_t<B>>))
//  constexpr register_variant_t register_variant_t::cat(
//      T0 dig0, Ts... dig_pack) noexcept;
//
//  /// STATIC REG_N_DIGS_T<L+1+(SIZEOF...(DIG_PACK))>
//  /// CAT(REG_DIGS_T,DIG_T,DIG_T ... DIG_PACK) VARIADIC
//  template <std::size_t B,typename T, typename... Ts>
//    requires(((std::is_same_v<Ts, dig_t<B>>)&& ...) && (std::is_same_v<T, dig_t<B>>))
//  constexpr
//  register_variant_t cat(reg_digs_t larg, T dig, Ts... dig_pack) noexcept;
//
//  /// STATIC REG_N_DIGS_T<L+1+(SIZEOF...(DIG_PACK))>
//  /// CAT(DIG_T,DIG_T ... DIG_PACK,REG_DIGS_T) VARIADIC
//  template <std::size_t B,typename T, typename... Ts>
//    requires(((std::is_same_v<Ts, dig_t<B>>)&& ...) && (std::is_same_v<T, dig_t<B>>))
//  constexpr register_variant_t cat(
//      T dig, Ts... dig_pack, reg_digs_t rarg) noexcept {
//    return cat(cat(dig, dig_pack...), rarg);
//  }
//
//  /// STATIC REG_N_DIGS_T<SIZE_T N,SIZE_T ... N_PACK>
//  /// CAT(
//  ///           REG_N_DIGS_T<N> LARG,
//  ///			REG_N_DIGS_T<N_PACK> ... RARG_PACK
//  /// ) VARIADIC PACK
//  template <std::size_t N, std::size_t... N_pack>
//    requires((N > 0) && ((N_pack > 0)&&  ...))
//  static constexpr register_variant_t register_variant_t::cat(
//      register_variant_t<N> larg, register_variant_t<N_pack>... rarg_pack) noexcept {
//    return cat(larg, rarg_pack...);
//  }
//
//  /// TAKE A SUBREGISTER OF A REGISTER OF DIGITS
//  template <std::size_t ibegin, std::size_t iend>
//    requires((iend <= L) && (ibegin < L) && (ibegin != iend))
//  constexpr register_variant_t  register_variant_t::subregister() const noexcept;
//
//  /// OPERADORES ARITMETICOS
//  ///	C_B()  C_Bm1()
//  ///	mC_B() mC_Bm1()
//  ///	operator~() operator-()
//
//  constexpr const register_variant_t& register_variant_t::mC_Bm1() noexcept;
//
//  constexpr const register_variant_t& register_variant_t::mC_B() noexcept;
//
//  constexpr register_variant_t register_variant_t::C_Bm1() const noexcept;
//
//  constexpr register_variant_t register_variant_t::C_B() const noexcept;
//
//  /// A partir de aquí no he hecho las sustituciones de
//  /// const reg_digs_t&  cthis{*this}; / reg_digs_t&  cthis{*this}; / reg_digs_t
//  /// cthis{*this}; Por las correspondientes funciones cr_cthis() / r_cthis() /
//  /// cp_cthis()
//
//  constexpr register_variant_t register_variant_t::operator~() const noexcept;
//
//  constexpr register_variant_t register_variant_t::operator-() const noexcept;
//
//public:
//  /// OPERATORS >> >>= << <<= REM_B^n M_REM_B^n MER_B_N M_MER_B_N
//
//  /// MULTIPLY BY THE BASE B (10) << <<=
//  /// DIVIDE BY THE BASE B (10)	  >> >>=
//  /// REMAINDER BY THE BASE B (10) REM_B_N M_REM_B_N
//  /// MULTIPLICATIVE CARRY BY THE BASE B (10) MER_B_N M_MER_B_N
//  constexpr register_variant_t register_variant_t::operator<<(std::size_t n) const noexcept;
//
//  constexpr const register_variant_t& register_variant_t::operator<<=(std::size_t n) noexcept;
//
//  constexpr const register_variant_t& register_variant_t::operator>>=(std::size_t n) noexcept;
//
//  constexpr register_variant_t register_variant_t::operator>>(std::size_t n) const noexcept;
//
//  constexpr register_variant_t register_variant_t::rem_B(std::size_t n) const noexcept;
//
//  constexpr const register_variant_t& register_variant_t::m_rem_B(std::size_t n) noexcept;
//
//  constexpr register_variant_t register_variant_t::mer_B(std::size_t n) const noexcept;
//
//  constexpr const register_variant_t& register_variant_t::m_mer_B(std::size_t n) noexcept;
//
//  /// OPERATOR BIT A BIT BITWISE | |= & &=
//
//  constexpr const register_variant_t& register_variant_t::operator|=(const register_variant_t& rarg) const noexcept;
//
//  constexpr register_variant_t register_variant_t::operator|(const register_variant_t& rarg) const noexcept;
//
//  constexpr const register_variant_t& register_variant_t::operator&=(const register_variant_t& rarg) noexcept;
//
//  constexpr register_variant_t register_variant_t::operator&(const register_variant_t& rarg) noexcept;
//
//  //  PRIVATE
//  /// NOS DEVUELVE EL ÍNDICE DEL DÍGITO NO 0 DE POTENCIA DE B MAS GRANDE
//  /// NOS DEVUELVE 0 SI ES UN DÍGITO NO 0
//  /// NOS DEVUELVE -1 SI ES EL DÍGITO 0
//  /// CUALQUIER OTRO CASO NOS DARÁ MAYOR QUE 0
//  constexpr std::int64_t register_variant_t::index_of_MSDig() const noexcept;
//
//  ///
//  ///
//  /// SOBRECARGA DE LOS OPERADORES DE COMPARACION Y ORDEN
//  ///
//  ///
//
//  /// COMPARACIONES ENTRE BASE_T Y DIG_T EN FORMA BASE_T @ DIG_T
//  template<std::size_t B>
//  constexpr bool register_variant_t::operator==(const dig_t<B>& rarg) const noexcept;
//  template<std::size_t B>
//  constexpr bool register_variant_t::operator!=(const dig_t<B>& rarg) const noexcept;
//  template<std::size_t B>
//  constexpr bool register_variant_t::operator>(const dig_t<B>& rarg) const noexcept;
//  template<std::size_t B>
//  constexpr bool register_variant_t::operator<(const dig_t<B>& rarg) const noexcept;
//  template<std::size_t B>
//  constexpr bool register_variant_t::operator>=(const dig_t<B>& rarg) const noexcept;
//  template<std::size_t B>
//  constexpr bool register_variant_t::operator<=(const dig_t<B>& rarg) const noexcept;
//
//  /// COMPARACIONES ENTRE REG_DIGS_T Y REG_N_DIGS_T
//  ///	HETEROGENEOS EN GENERAL
//  ///	EN FORMA REG_DIGS_T @ REG_N_DIGS_T<M>
//  template <std::size_t B,std::size_t M>
//  constexpr bool register_variant_t::operator==(const reg_digs_t<B,M>& rarg) const noexcept;
//
//  template <std::size_t B,std::size_t M>
//  constexpr bool register_variant_t::operator!=(const reg_digs_t<B,M>& rarg) const noexcept;
//
//  template <std::size_t B,std::size_t M>
//  constexpr bool register_variant_t::operator>(const reg_digs_t<B,M>& rarg) const noexcept;
//
//  template <std::size_t B,std::size_t M>
//  constexpr bool register_variant_t::operator<(const reg_digs_t<B,M>& rarg) const noexcept;
//
//  template <std::size_t B,std::size_t M>
//  constexpr bool register_variant_t::operator>=(const reg_digs_t<B.M>& rarg) const noexcept;
//
//  template <std::size_t B,std::size_t M>
//  constexpr bool register_variant_t::operator<=(const reg_digs_t<B,M>& rarg) const noexcept;
//
//  /// OPERADOR COMPARACION SPACESHIP C++20
//
//  template <std::size_t B,std::size_t M>
//  constexpr std::strong_ordering
//  register_variant_t::operator<=>(const reg_digs_t<B,M>& arg) const noexcept;
//
//  /// OPERADOR COMPARACION SPACESHIP C++20
//  template<std::size_t B>
//  constexpr std::weak_ordering
//  register_variant_t::operator<=>(const dig_t<B>& arg) const noexcept;
//
//  std::string register_variant_t::to_string() const noexcept;

/************************************/
/*                                  */
/*         ISTREAM Y OSTREAM        */
/*                                  */
/************************************/

//std::istream &operator>>(std::istream &,register_variant_t&);

//std::ostream &operator<<(std::ostream &,const register_variant_t&);

} // END OF NAMESPACE NUMREPR IN THIS TRANSLATION UNIT


