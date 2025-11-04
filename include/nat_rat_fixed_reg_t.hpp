#ifndef NAT_RAT_FIXED_REG_T_HPP_INCLUDED
#define NAT_RAT_FIXED_REG_T_HPP_INCLUDED

#include "nat_reg_digs_t.hpp"
#include "utilities.hpp"

namespace NumRepr {

using type_traits::suitable_base;
using type_traits::uint_type_for_radix_c;

template <std::uint64_t B, std::size_t LE, std::size_t LF>
  requires((B > 1) &&  (LE+LF > 0))
struct nat_rat_fixed_reg_t : public nat_reg_digs_t<B, LE+LF> {
  static constexpr std::size_t L = LE + LF;
  using dig_t = dig_t<B>;
  using UINT_T = dig_t::UINT_T;
  using SIG_UINT_T = typename type_traits::sig_UInt_for_UInt_t<UINT_T>;
  using SIG_SINT_T = typename type_traits::sig_SInt_for_UInt_t<UINT_T>;

  ///  [[0][1][2][3][4][5][6][7]]
  ///  [0] unidades [1] decenas [2] centenas [3] miles ...
  ///  [[-4][-3][-2][-1][0][1][2][3]]
  ///  [0] unidades [-1] décimas
  ///  base_t == base_fract_t.cat(base_ent_t) es el orden correcto
  ///  Los índices irían de [-LF,-1].[0,LE[


  template <std::size_t N>
    requires(N > 0)
  using base_N_t 		= nat_reg_digs_t<B, N>;
  using base_ent_t 	    = base_N_t<LE>;
  using base_fra_t 	    = base_N_t<LF>;
  using base_t 			= base_N_t<L>;

  template <std::size_t NE,std::size_t NF>
    requires(NE+NF > 0)
  using nrat_EF_reg_t = nat_rat_fixed_reg_t<B, NE , NF>;

  using nrat_reg_t = nrat_EF_reg_t<B, LE , LF>;
  using dig_t::dig_0();
  using dig_t::dig_1();
  using dig_t::dig_Bm2();
  using dig_t::dig_Bm1();
public:

  /// FUNCIONES INMEDIATAS QUE NOS DAN CONSTANTES DEL TIPO DE LA ACTUAL CLASE
  /// SE HACE CREANDO UNA VARIABLE RVALUE TEMPORAL CON LA FUNCIÓN HOMOLOGA PARA
  /// BASE_T
  static consteval nrat_reg_t regd_0() noexcept {
	return nrat_reg_t{base_t::regd_0()};
  }

  static consteval nrat_reg_t regd_1() noexcept {
	return nrat_reg_t{base_fra_t::regd_0().cat(base_ent_t::regd_1())};
  }

  static consteval nrat_reg_t regd_Bm1() noexcept {
	return nrat_reg_t{base_fra_t::regd_().cat(base_ent_t::regd_Bm1())};
  }

  static consteval nrat_reg_t regd_B() noexcept {
	return nrat_reg_t{base_fra_t::regd_0().cat(base_ent_t::regd_B())};
  }

  /// SOLO POTENCIAS POSITIVAS
  template <std::size_t n>
    requires(n < L)
  static consteval nrat_reg_t regd_pow_n_B() noexcept {
    return nrat_reg_t{base_t::regd_pow_n_B()};
  }

  /// SOLO POTENCIAS POSITIVAS
  template <std::size_t n>
    requires(n < L)
  static consteval nrat_reg_t regd_pow_n_B_m1() noexcept {
    return nrat_reg_t{base_t::regd_pow_n_B_m1()};
  }

  /// MíNIMA CANTIDAD DISPONIBLE DISTINTA DE 0
  static consteval nrat_reg_t regd_epsilon() noexcept {
  	if constexpr (LF > 0) {
			return nrat_reg_t{base_fra_t::regd_1().cat(base_ent_t::regd_1())};
  	} else {
			return nrat_reg_t{base_ent_t::regd_1()};
  	}
  }

  /************************************/
  /*	    						  */
  /*    CONSTRUIR NUMERO			  */
  /*					    		  */
  /************************************/

public:
  /// RANGO DE DÍGITOS DE PARTE ENTERA: 0 .. E-1     ->  0 .. E-1 -> [ 0,   NE)
  /// RANGO DE DÍGITOS DE PARTE FRACCI: E .. E+F-1   ->  E .. N-1 -> [NE,NF+NE)

  /// CONSTRUCTOR POR DEFECTO
  consteval inline nrat_reg_t() noexcept : base_t{dig_t::dig_0()} {}

  /// EL CONSTRUCTOR POR INICIALIZADOR DE LISTA
  /// CONSTATA EL PUNTO DECIMAL POR ELIGIENDO PRIMERO
  /// LA PARTE ENTERA Y DESPUÉS LA DECIMAL
  /// CONSTRUCTOR POR LISTA DE DIGITOS
  template<std::size_t NE, std::size_t NF>
  constexpr inline nrat_reg_t(
    const std::initializer_list<dig_t>& arg) noexcept
    : base_t{copy_arg_N<NE,NF>()
			  base_fra_t{base_t{arg}.subrepr<0,LF>()}.cat(
				base_ent_t{base_t{arg}.subrepr<LF,LF+LE>()}
			  )
			} {}

  /// ESTE CONSTRUCTOR VARIÁDICO POR LISTA DE ENTEROS O DIG_T
  /// CONSTATA EL PUNTO DECIMAL POR ELIGIENDO PRIMERO
  /// LA PARTE ENTERA Y DESPUÉS LA DECIMAL
  /// CONSTRUCTOR POR ARGUMENTOS DIGITOS SIN LIMITE: DEDUCE EL TIPO
  template <typename ...Ts>
    requires(std::is_same_v<Ts, dig_t> &&  ...)
  constexpr inline nrat_reg_t(const Ts& ...args) noexcept
      : base_t{
				base_fra_t{base_t(arg...).subrepr<0,LF>()}.cat(
					base_ent_t{base_t(arg...).subrepr<LF,LF+LE>()}
				)
			} {}

private:

  inline constexpr const base_t* const const_base_this() const noexcept {
    return static_cast<const base_t* const>(this);
  } // warning : qualifiers ignored on function return type

  inline constexpr base_t base_cpy_cthis() const noexcept {
    return base_t(*const_base_this());
  }

  inline constexpr const base_t& base_const_ref_cthis() const noexcept {
    return (*const_base_this());
  }

  inline constexpr const dig_t& const_by_index(std::size_t ix) const noexcept {
    return (base_const_ref_cthis()[ix]);
  }

  inline constexpr dig_t cpy_by_index(std::size_t ix) const noexcept {
    return dig_t(base_const_ref_cthis()[ix]);
  }

private:

  inline constexpr base_t* const base_this() noexcept {
    return static_cast<base_t *const>(this);
  } // warning : qualifiers ignored on function return type

  inline constexpr base_t& base_ref_cthis() noexcept { return (*base_this); }

  inline constexpr dig_t& by_index(std::size_t ix) noexcept {
    return (base_ref_cthis()[ix]);
  }

public:

  /// EL ÍNDICE -LF REPRESENTA EL LSB DECIMAL Y EL LF+LE-1 EL MSB ENTERO
  ///         EPSILON                              B^(LE-1)
  /// EL ÍNDICE  -1 REPRESENTA EL MSB DECIMAL Y EL       0 EL LSB ENTERO
  ///          -0.1B                                   1

  dig_t& operator[](std::int32_t ix) noexcept {
  	return  by_index(ix+LF);
  }

  const dig_t& operator[](std::int32_t ix) const noexcept {
  	return const_by_index(ix+LF);
  }

private:

  /// BEGIN : CONSTRUCTOR COPIA/MOVIMIENTO DESDE UN ARRAY DE DIGITOS
  ///
  /// FROM STD::INITIALIZER_LIST
  template <std::size_t NE,std::size_t NF>
    requires(NE+NF > 0)
  constexpr inline void copy_arg_N(
	const std::initializer_list& argf,const std::initializer_list& argi
  ) noexcept {
	base_N_t<NF> fracarg(argf);
	base_N_t<NE> intarg(argi);

	///  0             LF-1 LF            LF+LE-1
    ///                    UD
    ///  0 1 2 3 4 5 6 7 F| 8 9 A B C D E F E<= NRAT_REG_T<8,8>
    ///  0             NF-1 NF            NF+NE-1
    ///       {0 1 2 3 4}f|{0 1 2 3 4 5 6 7}e
    /// {7 6 5 4 3 2 1 0}e|{7 6 5 4 3 2 1 0}f <= forma en que aparece

    constexpr auto ZE{std::min(NE, LE)};
    if constexpr (ZE == LE) {
      for (std::size_t ix{0}; ix < ZE; ++ix)
        by_index(ix+LF) = intarg[ix];
    } else {
      for (std::size_t ix{0}; ix < ZE; ++ix)
        by_index(ix+LF) = intarg[ix];
      for (std::size_t ix{ZE}; ix < std::max(NE, LE); ++ix)
        by_index(ix+LF) = dig_0();
    }

    constexpr auto ZF{std::min(NF, LF)};
    if constexpr (ZF == LF) {

      for (std::ssize_t ix{ZF-1},std::ssize_t idx{LF-1} ;
           (ix > -1) && (idx > -1) 						;
           --ix,--idx
	  ) by_index(idx) = fracarg[ix];

    } else {

      for (std::ssize_t ix{ZF-1},std::ssize_t idx{LF-1} ;
           (ix > -1) && (idx > -1) 						;
           --ix,--idx
	  ) by_index(idx) = fracarg[ix];

      for (std::size_t ix{0}; ix < std::max(NF, LF); ++ix)
        by_index(ix) = dig_0();
    }
  }

  template <std::size_t N>
    requires(N > 0)
  constexpr inline void copy_arg_N(
	const std::initializer_list& arg
  ) noexcept {

	base_N_t<N> intarg(argi);
    constexpr auto ZE{std::min(N, LE)};
    if constexpr (ZE == LE) {
      for (std::size_t ix{0}; ix < ZE; ++ix)
        by_index(ix+LF) = intarg[ix];
    } else {
      for (std::size_t ix{0}; ix < ZE; ++ix)
        by_index(ix+LF) = intarg[ix];
	  constexpr auto WE{std::max(N, LE)};
      for (std::size_t ix{ZE}; ix < WE; ++ix)
        by_index(ix+LF) = dig_0();
    }
	for (std::size_t ix{0}; ix < LF ; ++ix)
		by_index(ix) = dig_0();
  }

  /// FUNCIÓN DELEGADA PARA COPIA DE UN ARRAY DEL MISMO TAMAÑO
  /// O UN TAMAÑO CUALQUIERA "NE+NF"
  template <std::size_t NE,std::size_t NF>
    requires(NE+NF > 0)
  constexpr inline void copy_arg_N(
	const base_N_t<NE>& intcarg,
	const base_N_t<NF>& fracarg
  ) noexcept {
    ///< Z < W or Z == W

    constexpr auto ZE{std::min(NE, LE)};
    if constexpr (ZE == LE) {
      for (std::size_t ix{0}; ix < ZE; ++ix)
        by_index(ix+LF) = intarg[ix];
    } else {
      for (std::size_t ix{0}; ix < ZE; ++ix)
        by_index(ix+LF) = intarg[ix];
	  constexpr auto WE{std::max(NE, LE)};
      for (std::size_t ix{ZE}; ix < WE; ++ix)
        by_index(ix+LF) = dig_t::dig_0();
    }

    constexpr auto ZF{std::min(NF, LF)};
    if constexpr (ZF == LF) {
      for (std::size_t ix{0}; ix < ZF; ++ix)
        by_index(ix) = fracarg[ix];
    } else {
      for (std::size_t ix{0}; ix < ZF; ++ix)
        by_index(ix) = fracarg[ix];
	  constexpr auto WF{std::max(NF, LF)};
      for (std::size_t ix{ZF}; ix < WF; ++ix)
        by_index(ix) = dig_t::dig_0();
    }
  }

  /// FUNCIÓN DELEGADA PARA COPIA DE UN ARRAY NATURAL DEL MISMO TAMAÑO
  /// O UN TAMAÑO CUALQUIERA "N==NE" : SOLO SE COPIA LA PARTE ENTERA
  template <std::size_t N>
    requires(N > 0)
  constexpr inline void copy_arg_N(
	const base_N_t<N>& arg
  ) noexcept {
    ///< Z < W or Z == W

    constexpr auto Z{std::min(N, LE)};
    if constexpr (Z == LE) {
      for (std::size_t ix{0}; ix < Z; ++ix)
        by_index(ix+LF) = arg[ix];
    } else {
      for (std::size_t ix{0}; ix < Z; ++ix)
        by_index(ix+LF) = arg[ix];
	  constexpr auto W{std::max(N, LE)};
      for (std::size_t ix{Z}; ix < W; ++ix)
        by_index(ix+LF) = dig_0();
    }
    /// PONE LA PARTE FRACCIONARIA A 0
	for (std::size_t ix{0}; ix < LF+1; ++ix)
      by_index(ix) = dig_0();
  }

  /// FUNCIÓN DELEGADA PARA MOVER DE UN ARRAY DEL MISMO TAMAÑO
  /// O UN TAMAÑO CUALQUIERA "NE+NF"
  template <std::size_t NE,std::size_t NF>
    requires(NE+NF > 0)
  constexpr inline void copy_arg_N(
	base_N_t<NE>&& intcarg, base_N_t<NF>&& fracarg
  ) noexcept {

    constexpr auto ZE{std::min(NE, LE)};
    if constexpr (ZE == LE) {
      for (std::size_t ix{0}; ix < ZE; ++ix)
        by_index(ix+LF) = std::move(intarg[ix]);
    } else { /// WE == LE
      for (std::size_t ix{0}; ix < ZE; ++ix)
        by_index(ix+LF) = std::move(intarg[ix]);
	  constexpr auto WE{std::max(NE, LE)};
      for (std::size_t ix{ZE}; ix < WE; ++ix)
        by_index(ix+LF) = dig_t::dig_0();
    }

    constexpr auto ZF{std::min(NF, LF)};
    if constexpr (ZF == LF) {
      for (std::size_t ix{0}; ix < ZF; ++ix)
        by_index(ix) = std::move(fracarg[ix]);
    } else { /// WF == LF
      for (std::size_t ix{0}; ix < ZF; ++ix)
        by_index(ix) = std::move(fracarg[ix]);
	  constexpr auto WF{std::max(NF, LF)};
      for (std::size_t ix{ZF}; ix < WF; ++ix)
        by_index(ix) = dig_t::dig_0();
    }
  }
  	constexpr auto Z{std::min(N, LE)};
    if constexpr (Z == LE) {
      for (std::size_t ix{0}; ix < Z; ++ix)
        by_index(ix+LF) = arg[ix];
    } else {
      for (std::size_t ix{0}; ix < Z; ++ix)
        by_index(ix+LF) = arg[ix];
	  constexpr auto W{std::max(N, LE)};
      for (std::size_t ix{Z}; ix < W; ++ix)
        by_index(ix+LF) = dig_0();
    }
	for (std::size_t ix{0}; ix < LF+1; ++ix)
      by_index(ix) = dig_0();
  }

  /// FUNCIÓN DELEGADA PARA MOVER DE UN ARRAY DEL MISMO TAMAÑO
  /// O UN TAMAÑO CUALQUIERA "N" : SOLO RELLENA LA PARTE ENTERA
  template <std::size_t N>
    requires(N > 0)
  constexpr inline void move_arg_N(base_N_t<N>&& arg) noexcept {
    ///< Z < W or Z == W
    constexpr auto Z{std::min(N, LE)};
    if constexpr (Z == LE) {
      for (std::size_t ix{0}; ix < Z; ++ix)
        by_index(ix+LF) = std::move(arg[ix]);
    } else { /// W == LE
      for (std::size_t ix{0}; ix < Z; ++ix)
        by_index(ix+LF) = std::move(arg[ix]);
	  constexpr auto W{std::max(N, LE)};
      for (std::size_t ix{Z}; ix < W; ++ix)
        by_index(ix+LF) = std::move(dig_0());
    }
    for (std::size_t ix{0}; ix < LF+1; ++ix)
      by_index(ix) = std::move(dig_0());
  }

public:

  /// CONSTRUCTOR COPIA DESDE UN ARRAY DE DIGITOS
  /// DEBERÍA ENCARGARSE SOLO DE LA PARTE POSITIVA ???
  template <std::size_t N>
    requires(N > 0)
  constexpr inline nrat_reg_t(const base_N_t<N>& arg) noexcept
    : base_t{copy_arg_N<N>(arg)} {}

  template <std::size_t NE,std::size_t NF>
    requires(NE+NF > 0)
  constexpr inline nrat_reg_t(const nrat_reg_t<NE,NF>& arg) noexcept
    : base_t{copy_arg_N<NE,NF>(arg.subrepr<0,NF>(),arg.subrepr<NF,NE+NF>())} {}

  /// CONSTRUCTOR COPIA DESDE DOS ARRAYS DE DIGITOS
  template <std::size_t NE,std::size_t NF>
    requires(NE+NF > 0)
  constexpr inline nrat_reg_t(
	const base_N_t<NE>& intarg,
	const base_N_t<NF>& fracarg
  ) noexcept
    : base_t{copy_arg_N<NE,NF>(intarg,fracarg)} {}

  /// CONSTRUCTOR MOVIMIENTO DESDE UN ARRAY DE DIGITOS
  template <std::size_t NE,std::size_t NF>
    requires(NE+NF > 0)
  constexpr inline natreg_digs_t(base_N_t<NE>&& intarg,base_N_t<NF>&& fracarg) noexcept
    : base_t{move_arg_N<NE,NF>(std::move(intarg),std::move(fracarg))} {}

  /// CONSTRUCTOR MOVIMIENTO DESDE DOS ARRAYS DE DIGITOS
  /// DEBERÍA ENCARGARSE SOLO DE LA PARTE POSITIVA ???
  template <std::size_t N>
    requires(N > 0)
  constexpr inline natreg_digs_t(base_N_t<N>&& arg) noexcept
    : base_t{move_arg_N<N>(std::move(arg))} {}

  template <std::size_t NE,std::size_t NF>
    requires(NE+NF > 0)
  constexpr inline nrat_reg_t(nrat_reg_t<NE,NF>&& arg) noexcept
    : base_t{move_arg_N<NE,NF>(
		std::move(arg.subrepr<0,NF>()),
		std::move(arg.subrepr<NF,NE+NF>())
	  )} {}

  /// END   : CONSTRUCTOR COPIA/MOVIMIENTO DESDE UN ARRAY DE DIGITOS

public:

  /// CONSTRUCTOR COPIA DESDE ARGUMENTOS ENTEROS SIN LIMITE : DEDUCE EL TIPO
  template <std::size_t NE,std::size_t NF,type_traits::integral_c... Ints_type>
  constexpr inline nrat_reg_t(Ints_type... dig_pow_i) noexcept
    : base_t{
    	move_arg_N<NE,NF>(
		  std::move(normalize<Ints_type...>(dig_pow_i...).subrepr<0,NF>()),
		  std::move(normalize<Ints_type...>(dig_pow_i...).subrepr<NF,NE+NF>()),
	  	)
	  } {}

  /// CONSTRUCTOR COPIA POR REFERENCIA CONSTANTE
  template <std::size_t NE,std::size_t NF> requires(NE+NF > 0)
  constexpr inline nrat_reg_t(const nrat_EF_reg_t<NE,NF>& arg) noexcept
    : base_t{
    	copy_arg_N<NE,NF>(
		  arg.base_const_ref_cthis().subrepr<0,NF>,
		  arg.base_const_ref_cthis().subrepr<NF,NE+NF>
        )
	  } {}

  /// CONSTRUCTOR POR MOVIMIENTO
  template <std::size_t NE,std::size_t NF> requires(NE+NF > 0)
  constexpr inline nrat_reg_t(nrat_EF_reg_t<NE,NF>&& arg) noexcept
    : base_t{
    	move_arg_N<NE,NF>(
		  arg.base_const_ref_cthis().subrepr<0,NF>,
		  arg.base_const_ref_cthis().subrepr<NF,NE+NF>
        )
      } {}

  /// OPERACIÓN ASIGNACIÓN POR COPIA REFERENCIA CONST _NO_ COPIABLE DESDE
  /// BASE_N_T
  template <std::size_t N> requires(N > 0)
  constexpr inline
  const nrat_reg_t& operator=(const base_N_t<N>& arg) noexcept {
    if (base_this() != &arg)
      copy_arg_N<N>(arg);
    return (*this);
  }

  /// OPERACIÓN ASIGNACIÓN POR COPIA REFERENCIA DESDE BASE_N_T
  template <std::size_t N> requires(N > 0)
  constexpr inline
  nrat_reg_t& operator=(base_N_t<N>& arg) noexcept {
    if (const_base_this() != &arg)
      copy_arg_N<N>(arg);
    return (*this);
  }

  /// OPERACIÓN ASIGNACIÓN POR COPIA MOVIMIENTO DESDE BASE_N_T
  template <std::size_t N> requires(N > 0)
  constexpr inline
  nrat_reg_t& operator=(base_N_t<N>&& arg) noexcept {
    if (const_base_this() != &arg)
      move_arg_N<N>(std::move(arg));
    return (*this);
  }

  /// OPERACIÓN ASIGNACIÓN POR COPIA REFERENCIA EN LA QUE SE PUEDE COPIAR
  template <std::size_t NE, std::size_t NF> requires(NE+NF > 0)
  constexpr inline
  nrat_reg_t& operator=(const nrat_EF_reg_t<NE,NF>& arg) noexcept {
    if (this != &arg)
      copy_arg_N<NE,NF>(arg);
    return (*this);
  }

  /// OPERACIÓN ASIGNACIÓN POR MOVIMIENTO
  template <std::size_t NE, std::size_t NF> requires(NE+NF > 0)
  constexpr inline
  nrat_reg_t& operator=(nrat_reg_t<NE,NF>&& arg) noexcept {
    if (this != &arg)
      move_arg_N<NE,NF>(std::move(arg));
    return (*this);
  }

  /// OPERACIÓN ASIGNACIÓN POR COPIA EN LA QUE  _NO_  SE PUEDE COPIAR
  template <std::size_t NE, std::size_t NF> requires(NE+NF > 0)
  constexpr inline
  const nrat_reg_t& operator=(const nrat_EF_reg_t<NE,NF>& arg) noexcept {
    if (this != &arg)
      copy_arg_N<NE,NF>(arg);
    return (*this);
  }

private:

  template <std::size_t NE, std::size_t NF> requires(NE+NF > 0)
  static constexpr inline
  void set_0(base_N_t<NE+NF>& arg) noexcept {
    for (dig_t& dig : arg)
      dig = dig_t::dig_0();
  }

  template <std::size_t NE, std::size_t NF> requires(NE+NF > 0)
  static constexpr inline
  void set_1(base_N_t<NE,NF>& arg) noexcept {
    set_0(arg);
	arg[NF].set_1();
  }

  template <std::size_t NE , std::size_t NF> requires(NE+NF > 0)
  static constexpr inline
  void set_Bm1(base_N_t<NE+NF>& arg) noexcept {
    set_0(arg);
	arg[NF].set_Bm1();
  }

  template <std::size_t NE , std::size_t NF> requires(NE+NF > 0)
  static constexpr inline
  void set_dig(base_N_t<NE+NF>& larg, dig_t d) noexcept {
    set_0(arg);
	arg[NF] = d;
  }

  template <std::size_t N> requires(N > 0)
  static constexpr inline void set_fill_dig(
	  base_N_t<N>& larg , dig_t d
    ) noexcept {
    for (auto& elem : larg)
      elem = d;
  }

  template <std::size_t N> requires(N > 0)
  static constexpr inline
  void set_fill_1(base_N_t<N>& larg) noexcept {
    for (auto& elem : larg)
      elem.set_1();
  }

  template <std::size_t N> requires(N > 0)
  static constexpr inline
  void set_fill_Bm1(base_N_t<N>& larg) noexcept {
    for (auto& elem : larg)
      elem.set_Bm1();
  }

  /// TODO 06:21:21:04:2023

  /// OPERACIÓN DE PONER A VALOR DIG_0 DEL ARRAY
  ///	DESDE [N_0 , N_1) EN BASE_N_T<N>
  template <std::size_t N, std::size_t N_i, std::size_t N_pf> // i es inicio
                                               // pf es pasado el final
    requires((N_i < N_pf) && (N_pf <= N) && (N > 0))
  static constexpr inline void set_interval_0(base_N_t<N>& larg) noexcept {
    for (std::size_t ix{N_i}; ix < N_pf; ++ix)
      larg[ix] = dig_t::dig_0();
  }

  /// OPERACIÓN DE PONER A VALOR DIG_Bm1 DEL ARRAY
  ///	DESDE [N_0 , N_1) EN BASE_N_T<N>
  template <std::size_t N, std::size_t N_i, std::size_t N_pf> // i es inicio
                                               // pf es pasado el final
    requires((N_i < N_pf) && (N_pf <= N) && (N > 0))
  static constexpr inline void set_interval_Bm1(base_N_t<N>& larg) noexcept {
    for (std::size_t ix{N_i}; ix < N_pf; ++ix)
      larg[ix] = dig_t::dig_Bm1();
  }

  /// OPERACIÓN DE PONER A VALOR DIG DEL ARRAY
  ///	DESDE [N_0 , N_1) EN BASE_N_T<N>
  template <std::size_t N, std::size_t N_i, std::size_t N_pf> // i es inicio
                                               // pf es pasado el final
    requires((N_i < N_pf) && (N_pf <= N) && (N > 0))
  static constexpr inline void set_interval_dig(base_N_t<N>& larg,
                                                dig_t dig) noexcept {
    for (std::size_t ix{N_i}; ix < N_pf; ++ix)
      larg[ix] = dig;
  }

  /// OPERACIÓN DE PONER A VALOR DIG_0 DEL ARRAY
  ///	DESDE [N_0 , N_1) EN BASE_T
  /// ESPECIALIZACIÓN PARA N==L
  template <std::size_t N_i, std::size_t N_pf> // i es inicio
                                     // pf es pasado el final
    requires((N_i < N_pf) && (N_pf <= L))
  static constexpr inline void set_interval_0(base_t& larg) noexcept {
    for (std::size_t ix{N_i}; ix < N_pf; ++ix)
      larg[ix] = dig_t::dig_0();
  }

  /// OPERACIÓN DE PONER A VALOR DIG_Bm1 DEL ARRAY
  ///	DESDE [N_0 , N_1) EN BASE_T
  /// ESPECIALIZACIÓN PARA N==L
  template <std::size_t N_i, std::size_t N_pf> // i es inicio
                                     // pf es pasado el final
    requires((N_i < N_pf) && (N_pf <= L))
  static constexpr inline void set_interval_Bm1(base_t& larg) noexcept {
    for (std::size_t ix{N_i}; ix < N_pf; ++ix)
      larg[ix] = dig_t::dig_Bm1();
  }

  /// OPERACIÓN DE PONER A VALOR DIG DEL ARRAY
  ///	DESDE [N_0 , N_1) EN BASE_T
  /// ESPECIALIZACIÓN PARA N==L
  template <std::size_t N_i, std::size_t N_pf> // i es inicio
                                     // pf es pasado el final
    requires((N_i < N_pf) && (N_pf <= L))
  static constexpr inline void set_interval_dig(
		base_t& larg, dig_t dig) noexcept
  {
    for (std::size_t ix{N_i}; ix < N_pf; ++ix)
      larg[ix] = dig;
  }

public:
  /// OPERACIÓN DE LIMPIEZA A CERO DEL NRAT_REG_T
  constexpr inline void set_0() noexcept { set_0(base_ref_cthis()); }

  /// OPERACIÓN DE LIMPIEZA A B-1 DEL NRAT_REG_T
  constexpr inline void set_Bm1() noexcept { set_Bm1(base_ref_cthis()); }

  /// OPERACIÓN DE LIMPIEZA A VALOR DIG_T DEL NRAT_REG_T
  constexpr inline void set_dig(dig_t arg) noexcept {
    set_dig(base_ref_cthis(), arg);
  }

  /// OPERACIÓN DE PONER A VALOR DIG_0 EN [N_0 , N_1) DE NRAT_REG_T
  template <std::size_t N_i, std::size_t N_pf> // i es inicio
                                     // pf es pasado el final
    requires((N_i < N_pf) && (N_pf <= L))
  constexpr inline void set_interval_0() noexcept {
    set_interval_0<N_i, N_pf>(base_ref_cthis());
  }
  /// OPERACIÓN DE PONER A VALOR DIG_Bm1 EN [N_0 , N_1) DE NRAT_REG_T
  template <std::size_t N_i, std::size_t N_pf> // i es inicio
                                     // pf es pasado el final
    requires((N_i < N_pf) && (N_pf <= L))
  constexpr inline void set_interval_Bm1() noexcept {
    set_interval_Bm1<N_i, N_pf>(base_ref_cthis());
  }
  /// OPERACIÓN DE PONER A VALOR DIG EN [N_0 , N_1) DE NRAT_REG_T
  template <std::size_t N_i, std::size_t N_pf> // i es inicio
                                     // pf es pasado el final
    requires((N_i < N_pf) && (N_pf <= L))
  constexpr inline void set_interval_dig(dig_t dig) noexcept {
    set_interval_0<N_i, N_pf>(base_ref_cthis(), dig);
  }

  /// OPERACIÓN COPIA DESDE UN DIGITO (CONVERSIÓN)
  constexpr inline nat_reg_digs_t& operator=(const dig_t& arg) noexcept {
    if (&const_by_index(0) != &arg) {
      set_0();
      by_index(0) = arg;
    }
    return (*this);
  }

private:

  /// OPERACIÓN COPIA DESDE UN ENTERO (CONVERSIÓN A LA BASE B) A UN BASE_T
  template <type_traits::integral_c Int_Type>
  static constexpr
  inline const base_t& assign(base_t& larg, Int_Type arg) noexcept {
    using type_traits::maxbase;
    constexpr sint64_t B_128t_v{static_cast<sint64_t>(B)};
    constexpr bool puede_multiplicarse{(maxbase<sint64_t>() / B_128t_v) > 0};
    if ((&larg) != (&arg)) {
      sint64_t creg_g{static_cast<sint64_t>(arg)};
      sint64_t BasePowIx{B_128t_v};
      for (std::size_t k{1u}; k < L; ++k) {
        if constexpr (puede_multiplicarse)
          BasePowIx *= B_128t_v;
        else
          break;
      }
      while (creg_g < 0) {
        creg_g += BasePowIx;
      }
      for (std::size_t k{0u}; k < L; ++k) {
        larg[k] = dig_t(creg_g % B_128t_v);
        creg_g /= B_128t_v;
      }
    }
    return (larg);
  }

public:
  /// NAT_REG_N_T<L+M> NAT_REG_T::CAT(NAT_REG_N_T<M>)
  /// NAT_REG_N_T<L+M> NAT_REG_T::CAT_INV(NAT_REG_N_T<M>)
  /// NAT_REG_N_T<L+1> NAT_REG_T::CAT(DIG_T)
  /// NAT_REG_N_T<L+1> NAT_REG_T::CAT_INV(DIG_T)

  /// SUBREPR => SUB REPRESENTACION
  /// ¿HAY QUE QUITARLAS POR QUE ESTÁN POR HERENCIA O REFORMARLAS POR EL SIGNO?
  template <std::size_t N>
    requires(N > 0)
  constexpr inline nat_reg_N_digs_t<N + L> cat(
      const nat_reg_N_digs_t<N>& arg) const noexcept {
    return (concat<L, N>(base_cpy_cthis(), arg));
  }

  constexpr inline nat_reg_N_digs_t<L + 1> cat(dig_t arg) const noexcept {
    return (concat<L>(base_cpy_cthis(), arg));
  }

  template <std::size_t N>
    requires(N > 0)
  constexpr inline nat_reg_N_digs_t<N + L> cat_inv(
      const nat_reg_N_digs_t<N>& arg) const noexcept {
    return (concat<N, L>(arg, base_cpy_cthis()));
  }

  constexpr inline nat_reg_N_digs_t<L + 1> cat_inv(dig_t arg) const noexcept {
    return (concat<L>(arg, base_cpy_cthis()));
  }

  template <std::size_t ibegin, std::size_t iend>
    requires((iend <= L) && (ibegin < iend))
  constexpr inline nat_reg_N_digs_t<iend - ibegin> subrepr() const noexcept {
    return subregister<L, ibegin, iend>(base_cpy_cthis());
  }

  /****************************************/
  /*							      	  */
  /*       Algunas Conversiones    		  */
  /*							      	  */
  /****************************************/

  template <type_traits::integral_c Int_Type>
  constexpr inline explicit operator Int_Type() const noexcept {
    using type_traits::maxbase;
    uint64_t retInt{0};
    uint64_t BasePowIx{1};
    for (std::size_t k{0}; k < L; ++k) {
      retInt += const_by_index(k) * BasePowIx;
      BasePowIx *= B;
      if(
		(k + 1 < L) &&
		(
		  maxbase<Int_Type>() < retInt+(const_by_index(k+1)*BasePowIx)
		)
	    ) {
        return retInt;
      }
    }
    return retInt;
  }

public:
  /****************************************************/
  /*							    				  */
  /* OPERADORES COMPARATIVOS                          */
  /*							    				  */
  /****************************************************/

  /// OPERADOR COMPARACIÓN SPACESHIP C++20
  template <std::size_t N>
    requires(N > 0)
  constexpr inline
  std::strong_ordering
  operator<=>(const nat_reg_N_digs_t<N>& arg) const noexcept {
    return (base_const_ref_cthis() <=> arg.base_const_ref_cthis());
  }

  /// OPERADOR COMPARACIÓN SPACESHIP C++20
  template <std::size_t N>
    requires(N > 0)
  constexpr inline std::weak_ordering
  operator<=>(const base_N_t<N>& arg) const noexcept {
    return (base_const_ref_cthis() <=> arg);
  }

  /// OPERADOR COMPARACIÓN SPACESHIP C++20
  constexpr inline std::weak_ordering
  operator<=>(const dig_t& arg) const noexcept {
    return (base_const_ref_cthis() <=> arg);
  }

  /********************************/
  /*							  */
  /* 		  PRIMER DIGITO	 	  */
  /*		  SEGUNDO DIGITO	  */
  /*							  */
  /********************************/

  inline constexpr dig_t operator[](std::size_t idx) const noexcept {
    return (cpy_by_index(idx));
  }

  inline constexpr dig_t& operator[](std::size_t idx) noexcept {
    return (by_index(idx));
  }

  template <type_traits::integral_c Int_Type = UINT_T>
  inline constexpr Int_Type operator()(std::size_t idx) const noexcept {
    return static_cast<Int_Type>(cpy_by_index(idx)());
  }

  /****************************/
  /*						  */
  /* OPERADORES ARITMÉTICOS	  */
  /*	POSTINCREMENTO ++(int)*/
  /*	PREINCREMENTO ++()	  */
  /*	POSTDECREMENTO --(int)*/
  /*	PREDECREMENTO ++()	  */
  /*                          */
  /****************************/

public:

  constexpr inline const nat_reg_digs_t& operator++() noexcept {
    return (m_incr(*this));
  }

  constexpr inline const nat_reg_digs_t& operator++(int) noexcept {
    auto cp_this{*this};
    ++(*this);
    return cp_this;
  }

  constexpr inline const nat_reg_digs_t& operator--() noexcept {
    return (m_decr(*this));
  }

  constexpr inline const nat_reg_digs_t& operator--(int) noexcept {
    auto cp_this{*this};
    --(*this);
    return cp_this;
  }


  /******************************/
  /*							*/
  /*    OPERADORES ARITMETICOS	*/
  /*	 C_B()  C_Bm1()  		*/
  /*	mC_B() mC_Bm1()		    */
  /*	operator!() operator-() */
  /*                            */
  /******************************/

  /// HEREDADO DE REG_DIGS_T
  //
  ///	const nat_reg_digs_t&  mC_B() noexcept
  //
  ///	const nat_reg_digs_t&  mC_Bm1() noexcept
  //
  ///	nat_reg_digs_t C_Bm1() const noexcept
  //
  ///	nat_reg_digs_t C_B() const noexcept
  //
  ///	nat_reg_digs_t operator~() const noexcept
  //
  ///	nat_reg_digs_t operator-() const noexcept

  /// BEGIN : OPERATORS >> >>= << <<= REM_B^n M_REM_B^n MER_B_N M_MER_B_N

  /// MULTIPLY BY THE BASE B (10) << <<=
  /// DIVIDE BY THE BASE B (10)	  >> >>=
  /// REMAINDER BY THE BASE B (10) REM_B_N M_REM_B_N
  /// MULTIPLICATIVE CARRY BY THE BASE B (10) MER_B_N M_MER_B_N

  ///  HEREDADO DE REG_DIGS_T
  ///  nat_reg_digs_t operator<<(std::size_t n) const noexcept
  //
  ///  const nat_reg_digs_t& operator<<=(std::size_t n) noexcept
  //
  ///  nat_reg_digs_t operator>>(std::size_t n) const noexcept
  //
  ///  const nat_reg_digs_t& operator>>=(std::size_t n) noexcept
  //
  ///  nat_reg_digs_t rem_B(std::size_t n) const noexcept
  //
  ///  const nat_reg_digs_t& m_rem_B(std::size_t n) noexcept
  //
  ///  nat_reg_digs_t mer_B(std::size_t n) const noexcept
  //
  ///  const nat_reg_digs_t& m_mer_B(std::size_t n) noexcept

  /// END   : OPERATORS >> >>= << <<= REM_B^n M_REM_B^n MER_B_N M_MER_B_N

  /// BEGIN : OPERATORS | & |= &=

  ///  HEREDADO DE REG_DIGS_T
  ///  const nat_reg_digs_t& operator|=(const nat_reg_digs_t& arg) noexcept
  //
  ///  nat_reg_digs_t operator|(const nat_reg_digs_t& arg) noexcept
  //
  ///  const nat_reg_digs_t& operator&=(const nat_reg_digs_t& arg) noexcept
  //
  ///  nat_reg_digs_t operator&(const nat_reg_digs_t& arg) noexcept

  /// END   : OPERATORS | & |= &=

  /*****************************************/
  /* OPERADORES ARITMETICOS BASICOS		   */
  /*	    nat_reg_digs_t  @  dig_t       */
  /*      nat_reg_digs_t  @= dig_t         */
  /*      nat_reg_digs_t  @  10B^n         */
  /*      nat_reg_digs_t  @= 10B^n         */
  /*****************************************/

  /******************************************/
  /*								   		*/
  /*  ARITMETICOS CON ASIGNACIÓN			*/
  /*		nat_reg_digs_t @= dig_t			*/
  /*                                        */
  /******************************************/

  /// OPERACIONES BINARIAS CON/SIN TIPO RESULTADO
  /// OPERACIONES BINARIAS SIN REPORTE DE ERROR O CARRY
  /// 	     BASE_T @ DIG_T
  /// OPERATOR BASE_T += DIG_T CON NOMBRE M_ADDITION

public:

  constexpr inline
  const nat_reg_digs_t& operator+=(dig_t rarg) noexcept {
    m_incr_by_digit(*this, rarg);
    return (*this);
  }

  constexpr inline
  const nat_reg_digs_t& operator-=(dig_t rarg) noexcept {
    m_decr_by_digit(*this, rarg);
    return (*this);
  }

  constexpr inline
  const nat_reg_digs_t& operator*=(dig_t rarg) noexcept {
    m_mult(*this,rarg);
    return (*this);
  }

  constexpr inline
  const nat_reg_digs_t& operator/=(dig_t rarg) noexcept {
    nat_reg_N_digs_t<1u> registro_1_digito{rarg};
    auto result{fediv(*this,registro_1_digito)};
    (*this)=std::get<0>(result);
    return (*this);
  }

  constexpr inline
  const nat_reg_digs_t& operator%=(dig_t rarg) noexcept {
    nat_reg_N_digs_t<1u> registro_1_digito{rarg};
    auto result{fediv(*this,registro_1_digito)};
    (*this)=std::get<1>(result);
    return (*this);
  }

  constexpr inline
  nat_reg_digs_t operator+(dig_t rarg) const noexcept {
    return std::get<0>(nat_reg_digs_t{sum(*this, rarg)});
  }

  constexpr inline
  nat_reg_digs_t operator-(dig_t rarg) const noexcept {
    return std::get<0>(nat_reg_digs_t{subtract(*this, rarg)});
  }

  constexpr inline
  nat_reg_digs_t operator*(dig_t rarg) const noexcept {
    return std::get<0>(nat_reg_digs_t{mult(*this, rarg)});
  }

  constexpr inline
  nat_reg_digs_t operator/(dig_t rarg) const noexcept {
    nat_reg_digs_t cpy_cthis{*this};
    cpy_cthis /= rarg;
    return std::move(cpy_cthis);
  }

  constexpr inline
  nat_reg_digs_t operator%(dig_t rarg) const noexcept {
    nat_reg_digs_t cpy_cthis{*this};
    cpy_cthis %= rarg;
    return std::move(cpy_cthis);
  }

  /// OPERACIONES BINARIAS HOMÓLOGAS A LAS ANTERIORES
  /// QUE REPORTAN ERROR DE DIV BY 0, CARRY/BORROW ...
  /// 	     M_OP BASE_T DIG_T
  /// OPERATOR M_OP BASE_T DIG_T CON NOMBRE M_ADDITION

  /// RETORNA EL CARRY Y EL RESULTADO EN *THIS
  /// MEJOR QUE OPERATOR+=
  constexpr inline
  dig_t m_addition(dig_t rarg) noexcept {
    return m_incr_by_digit(*this, rarg);
  }

  /// RETORNA EL BORROW Y EL RESULTADO EN *THIS
  /// MEJOR QUE OPERATOR-=
  constexpr inline
  dig_t m_subtract(dig_t rarg) noexcept {
    return m_decr_by_digit(*this, rarg);
  }

  /// RETORNA EL CARRY Y EL RESULTADO EN *THIS
  /// MEJOR QUE OPERATOR*=
  constexpr inline
  dig_t m_multiplication(dig_t rarg) noexcept {
    return m_mult(*this, rarg);
  }

  /// RETORNA EL CARRY Y EL RESULTADO EN *THIS
  /// MEJOR QUE OPERATOR*=
  constexpr inline
  auto fediv(dig_t rarg) const noexcept {
    return m_mult(*this, rarg);
  }

  /// MEJOR QUE /= Y %= ES FEDIV QUE NO TIENE
  /// PARALELO APROPIADO CON M_DIVISION O M_RESTO_DE_DIV
  /// SE EXPONDRÁ CON LAS OPERACIONES ENTRE EL MISMO TIPO
  /// NAT_REG_DIGS_T

  /****************************************/
  /*									  */
  /* OPERADORES ARITMETICOS               */
  /* nat_reg_digs_t @ nat_reg_digs_t	  */
  /*                            		  */
  /****************************************/


  constexpr inline
  const nat_reg_digs_t& operator+=(const nat_reg_digs_t& rarg) noexcept {
    m_incr(*this, rarg);
    return (*this);
  }

  constexpr inline
  const nat_reg_digs_t& operator-=(const nat_reg_digs_t& rarg) noexcept {
    m_decr(*this, rarg);
    return (*this);
  }

  constexpr inline
  const nat_reg_digs_t& operator*=(const nat_reg_digs_t& rarg) noexcept {
    m_mult(*this,rarg);
    return (*this);
  }

  constexpr inline
  const nat_reg_digs_t& operator/=(const nat_reg_digs_t& rarg) noexcept {
    nat_reg_digs_t right{rarg};
    auto result{fediv(*this,right)};
    (*this)=std::get<0>(result);
    return (*this);
  }

  constexpr inline
  const nat_reg_digs_t& operator%=(const nat_reg_digs_t& rarg) noexcept {
    nat_reg_digs_t right{rarg};
    auto result{fediv(*this,right)};
    (*this)=std::get<1>(result);
    return (*this);
  }

  constexpr inline
  nat_reg_digs_t operator+(const nat_reg_digs_t& rarg) const noexcept {
    return std::get<0>(nat_reg_digs_t{sum(*this, rarg)});
  }

  constexpr inline
  nat_reg_digs_t operator-(const nat_reg_digs_t& rarg) const noexcept {
    return std::get<0>(nat_reg_digs_t{subtract(*this, rarg)});
  }

  constexpr inline
  nat_reg_digs_t operator*(const nat_reg_digs_t& rarg) const noexcept {
    return std::get<0>(nat_reg_digs_t{mult(*this, rarg)});
  }

  constexpr inline
  nat_reg_digs_t operator/(const nat_reg_digs_t& rarg) const noexcept {
    nat_reg_digs_t cpy_cthis{*this};
    cpy_cthis /= rarg;
    return std::move(cpy_cthis);
  }

  constexpr inline
  nat_reg_digs_t operator%(const nat_reg_digs_t& rarg) const noexcept {
    nat_reg_digs_t cpy_cthis{*this};
    cpy_cthis %= rarg;
    return std::move(cpy_cthis);
  }

  /// OPERACIONES BINARIAS HOMÓLOGAS A LAS ANTERIORES
  /// QUE REPORTAN ERROR DE DIV BY 0, CARRY/BORROW ...
  /// 	     M_OP BASE_T DIG_T
  /// OPERATOR M_OP BASE_T DIG_T CON NOMBRE M_ADDITION

  /// RETORNA EL CARRY Y EL RESULTADO EN *THIS
  /// MEJOR QUE OPERATOR+=
  constexpr inline
  dig_t m_addition(const nat_reg_digs_t& rarg) noexcept {
    return m_sum(*this, rarg);
  }

  /// RETORNA EL BORROW Y EL RESULTADO EN *THIS
  /// MEJOR QUE OPERATOR-=
  constexpr inline
  dig_t m_subtract(const nat_reg_digs_t& rarg) noexcept {
    return m_subtract(*this, rarg);
  }

  /// RETORNA EL CARRY Y EL RESULTADO EN *THIS
  /// MEJOR QUE OPERATOR*=
  constexpr inline
  nat_reg_digs_t m_multiplication(const nat_reg_digs_t& rarg) noexcept {
    return m_mult(*this, rarg);
  }

  /// MEJOR QUE /= Y %= ES FEDIV QUE NO TIENE
  /// PARALELO APROPIADO CON M_DIVISION O M_RESTO_DE_DIV

  constexpr inline
  auto fediv(const nat_reg_digs_t& rarg) const noexcept {
    return fediv(*this,rarg);
  }

};

/****************************/
/*							*/
/* 	   ISTREAM Y OSTREAM	*/
/*							*/
/****************************/


/// VERSION CON TRATAMIENTO DE ERRORES EN RUNTIME
template <std::uint64_t Base,std::size_t Length>
  requires((Base > 1) && (Length > 0))
std::istream& operator>>(std::istream& is,
                         nat_reg_digs_t<Base, Length>& arg) {
  enum estado_e {
    e0ini,
    e1r,
    e1e,
    e1g,
    e1sep,
    e1d,
    e1i,
    e2g,
    e2start,
    e2dig,
    e2dp,
    e2end,
    e2B,
    e3dig,
    e0fin
  };
  /// STRING RECOGIDO DESDE LA ENTRADA ESTANDAR CIN
  std::string sds;
  /// TIPOS A SER UTILIZADOS EN LA FUNCIÓN: NOMBRE DE TIPOS CORTOS
  using inttype = typename type_traits::sig_UInt_for_UInt_t<Int_Type>;
  using dig_t = dig_t<Int_Type, Base>;
  using nat_reg_digs_t = nat_reg_digs_t<Int_Type, Base, Length>;
  /// INDICE QUE RECORRE EL STRING RECOGIDO DE ENTRADA
  std::size_t indice{0};
  /// VARIABLES PARA ACCIONES EN LOS ESTADOS
  Int_Type digito{0};
  std::size_t longitud{0};
  inttype numero_base_recogido{0};
  /// VARIABLE DE RETORNO (BINDED TO THE ARG BY REFERENCE)
  nat_reg_digs_t& numero_ret{arg};
  /// ESTADO ACTUAL
  estado_e est_act = e0ini;
  /// CARACTER QUE GUARDARA EL INDICADO POR EL INDICE DEL STRING RECOGIDO DESDE
  /// CIN
  char c{'\0'};
  /// RECOGEMOS DESDE LA ENTRADA EL STRING CON LA INFORMACION CODIFICADA
  is >> sds;
  /// MAQUINA DE ESTADOS FINITOS QUE HACE EL PARSE() DE LA ENTRADA
  do {
    c = sds[indice];
    switch (est_act) {
    case e0ini: {
      if (c == 'r') {
        est_act = e1r;
      } else {
        est_act = e0ini;
      }
    } break;
    case e1r: {
      {
        if (c == 'e') {
          est_act = e1e;
        } else {
          est_act = e0ini;
        }
      }
    } break;
    case e1e: {
      if (c == 'g') {
        est_act = e1g;
      } else {
        est_act = e0ini;
      }
    } break;
    case e1g: {
      if (c == '_') {
        est_act = e1sep;
      } else {
        est_act = e0ini;
      }
    } break;
    case e1sep: {
      if (c == 'd') {
        est_act = e1d;
      } else {
        est_act = e0ini;
      }
    } break;
    case e1d: {
      if (c == 'i') {
        est_act = e1i;
      } else {
        est_act = e0ini;
      }
    } break;
    case e1i: {
      if (c == 'g') {
        est_act = e2g;
      } else {
        est_act = e0ini;
      }
    } break;
    case e2g: {
      if (c == '#') {
        est_act = e2start;
      } else {
        est_act = e0ini;
      }
    } break;
    case e2start: {
      if (((c >= '0') && (c <= '9')) && (std::abs(c - '0') < Base)) {
        est_act = e2dig;
        digito = (c - '0');
        longitud = 0;
        numero_base_recogido = 0;
        numero_ret = nat_reg_digs_t::regd_0();
      } else {
        est_act = e0ini;
        digito = 0;
        longitud = 0;
        numero_base_recogido = 0;
        numero_ret = nat_reg_digs_t::regd_0();
      }
    } break;
    case e2dig: {
      const bool dig_c{(c >= '0') && (c <= '9')};
      const bool dig_lt_Base{digito < Base};
      const bool c_es_dig_B{dig_c && dig_lt_Base};
      const bool dig_B_cdl{c_es_dig_B && (longitud < Length - 1)};
      const bool tt_dig_B_cdl{(c == ':') && dig_lt_Base &&
                              (longitud < Length - 1)};
      const bool tf_dig_B_cdl{(c == '#') && dig_lt_Base &&
                              (longitud == Length - 1)};
      if (dig_B_cdl) {
        digito *= 10;
        digito += (c - '0');
        est_act = e2dig;
      } else if (tt_dig_B_cdl) {
        est_act = e2dp;
      } else if (tf_dig_B_cdl) {
        est_act = e2end;
      } else {
        est_act = e0ini;
        digito = 0;
        longitud = 0;
        numero_base_recogido = 0;
        numero_ret = nat_reg_digs_t::regd_0();
      }
    } break;
    case e2dp: {
      const bool dig_c{(c >= '0') && (c <= '9')};
      const bool c_es_dig_B{(std::abs(c - '0') < Base) && (digito < Base)};
      const bool dig_B_cdl{dig_c && c_es_dig_B && (longitud < Length - 1)};
      const bool rdig_B_cdl{dig_c && c_es_dig_B && dig_B_cdl};
      if (rdig_B_cdl) {
        est_act = e2dig;
        numero_ret[Length - 1 - longitud] = dig_t(digito);
        ++longitud;
        digito = c - '0';
      } else {
        est_act = e0ini;
        digito = 0;
        longitud = 0;
        numero_base_recogido = 0;
        indice = 0;
        numero_ret = nat_reg_digs_t::regd_0();
      }
    } break;
    case e2end: {
      const bool c_es_sepfin{c == 'B'};
      const bool d_es_digB{digito < Base};
      const bool l_coincide{longitud == Length - 1}; // llega al cero ?
      const bool rdigB_cdl{c_es_sepfin && d_es_digB && l_coincide};
      if (rdigB_cdl) {
        est_act = e2B;
        numero_ret[Length - 1 - longitud] = dig_t(digito);
        digito = 0;
        longitud = 0;
      } else {
        est_act = e0ini;
        indice = 0;
        digito = 0;
        longitud = 0;
        numero_ret = nat_reg_digs_t::regd_0();
      }
    } break;
    case e2B: {
      if ((c >= '0') && (c <= '9')) {
        est_act = e3dig;
        numero_base_recogido = c - '0';
        digito = 0;
      } else {
        est_act = e0ini;
        digito = 0;
        longitud = 0;
        numero_base_recogido = 0;
        numero_ret = nat_reg_digs_t::regd_0();
      }
    } break;
    case e3dig: {
      const bool espacio_c{c < 16};
      const bool digito_c{(c >= '0') && (c <= '9')};
      const bool num_base_lt_Base{numero_base_recogido < Base};
      const bool num_base_eq_Base{numero_base_recogido == Base};
      if (digito_c && num_base_lt_Base) {
        est_act = e3dig;
        numero_base_recogido *= 10;
        numero_base_recogido += (c - '0');
      } else if (espacio_c && num_base_eq_Base) {
        numero_base_recogido *= 10;
        numero_base_recogido += (c - '0');
        est_act = e0fin;
        numero_base_recogido = 0;
      } else {
        est_act = e0ini;
        numero_base_recogido = 0;
      }
    } break;
    case e0fin: {
      est_act = e0fin;
    }
    }
    ++indice;
  } while (est_act != e0fin);

  return (is);
}

template <type_traits::uint_type_for_radix_c Int_Type, Int_Type Base,
          std::size_t Long>
  requires(type_traits::suitable_base<Int_Type, Base>())
std::ostream& operator<<(std::ostream& os,
                         const nat_reg_digs_t<Int_Type, Base, Long>& arg) {
  using inttype = typename type_traits::sig_UInt_for_UInt_t<Int_Type>;
  os << "reg_dig#";
  for (int32_t ix{Long - 1}; ix > 0; --ix) {
    os << static_cast<inttype>(arg(ix));
    os << ':';
  }
  os << static_cast<inttype>(arg(0));
  os << "#B";
  os << static_cast<inttype>(Base);
  return (os);
}

} // namespace NumRepr
#endif // NAT_RAT_FIXED_REG_T_HPP_INCLUDED
