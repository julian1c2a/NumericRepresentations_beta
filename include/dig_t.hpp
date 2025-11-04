#ifndef DIG_T_HPP_INCLUDED
#define DIG_T_HPP_INCLUDED

#include <array>
#include <string>

#include "basic_types.hpp"
#include "auxiliary_types.hpp"
#include "auxiliary_functions.hpp"

namespace NumRepr
{

  using type_traits::maxbase;
  using type_traits::sig_SInt_for_UInt_t;
  using type_traits::sig_UInt_for_UInt_t;
  using type_traits::sqrt_max;
  using type_traits::suitable_base;
  using type_traits::uint_type_for_radix_c;
  ///< WRAPPER PARA UN TIPO uint_t QUE UNSIGNED_INTEGRAL_T<uint_t>
  ///< SE SOBRECARGAN LOS OPERADORES ARITMETICOS PARA ARITMETICA MODULAR
  ///< DIG_T = SUMA Y MULTIPLICACION CIRCULAR (MODULAR CON MOD B)
  template <std::uint64_t B>
    requires(B > 1)
  struct dig_t
  {
    /// GENERACIÓN DEL TIPO QUE CONTENDRÁ EL DÍGITO CON ENTERO SIN SIGNO
    using uint_t = typename type_traits::TypeFromIntNumber_t<static_cast<uint64_t>(B)>;

  private:
    uint_t m_d;

  public:
    // sig_uint_t(uchint) -> usint
    using sig_uint_t = typename type_traits::sig_UInt_for_UInt_t<uint_t>;
    // sig_sint_t(uchint) -> ssint
    using sig_sint_t = typename type_traits::sig_SInt_for_UInt_t<uint_t>;

    using uintspair = std::array<uint_t, 2>;
    using digspair = std::array<dig_t, 2>;
    using uintspairlist = std::array<uintspair, B>;
    using uintspairtbl = std::array<uintspairlist, B>;

    ///< BEGIN : CONSTRUCCION DE LAS TABLAS DE MULTIPLICAR
    ///<         ESTATICAS PARA TODA LA CLASE
    /// ¡¡¡¡ no usado aún !!!!
    template <uint_t n, uint_t m>
      requires((n < B) && (m < B))
    static consteval uintspair mult() noexcept
    {
      if constexpr (B > type_traits::sqrt_max<uint_t>())
      {
        constexpr sig_uint_t sup_n{n};
        constexpr sig_uint_t sup_m{m};
        constexpr sig_uint_t result{sup_n * sup_m};
        constexpr uint_t ret_1{result / B}; // "DECENAS"
        constexpr uint_t ret_0{result % B}; // "UNIDADES"
        constexpr uintspair ret{ret_1, ret_0};
        return ret;
      }
      else
      {
        constexpr uint_t result{n * m};
        constexpr uint_t ret_1{result / B}; // "DECENAS"
        constexpr uint_t ret_0{result % B}; // "UNIDADES"
        constexpr uintspair ret{ret_1, ret_0};
        return ret;
      }
    }
    /// PARA B=3 2*2									      1       COMIENZAN POR 2
    /// B-2
    /// PARA B=4 2*2 2*3 3*4							  3       COMIENZAN POR 2 B-2, 3
    /// B-3
    /// PARA B=5 2*2 2*3 2*4 3*3 3*4 4*4		6       COMIENZAN POR 2 B-2, 3 B-3, 4
    /// B-4 PARA B=6 2*2 2*3 2*4 2*5 3*3 3*4 3*5 4*4 4*5 5*5
    ///                                    10       COMIENZAN POR 2 B-2, 3 B-3, 4 B-4, 5 B-5
    /// PARA B=r 2*2 2*(2+1) ... 2*(r-1)		r-1  r
    ///                                     COMIENZAN POR 2 B-2, 3 B-3, 4 B-4, 5 B-1, ... , r-1 B-r+1
    ///			                   3*3		 ... 3*(r-1) r-2
    ///						                     ...
    ///			                (r-1)*(r-1)... r-(r-1)
    ///													_______
    ///							           (r-2)r-(r-1)*r/2 + 1
    ///                     =  [2(r-2)-((r-2)+1)]r/2 + 1
    ///							        =  ((r-3)r + 2)/2
    ///                     =	 (r^2 - 3r + 2) / 2
    ///                     =  a r^2 + b r + c
    ///							   				------------------
    ///													1 = a  9 + b 3 + c
    ///													3 = a 16 + b 4 + c
    ///													6 = a 25 + b 5 + c
    ///													------------------
    ///													1 = a  9 + b 3 + c
    ///  												2 = a  7 + b 1
    ///													------------------
    ///													5 = a 16 + b 2
    ///													------------------
    ///													1 = a  9 + b 3 + c
    ///													2 = a  7 + b
    ///                         1 = a  2
    ///													------------------
    ///													c = 2/2
    ///                         b = -3/2
    ///                         a =  1/2
    ///													------------------
    ///													SIZE = (B^2 - 3B + 2)/2 	2+3+4+...+B-1 = 1+2+3+4+...+B-1 - 1 =
    ///                         = (B-1)B/2 - 2(B-1)/2   = (B^2 - B - 2B +2)/2 =  (B^2-3B+2)/2
    ///
    /// FALTARIA HACERLAS SOLO PARA BASES MAYORES QUE 2
    /// CODE NEW USING TYPES :
    /// using pair_map = std::pair<uintspair,uintspair>;
    /// CODE MULTTABLE:
    ///		static consteval std::array<pair_map,(B^2 - 3B + 2)/2>
    /// multtable{make_multtables()};
    /// CODE FOR MAKE_MULTTABLES():
    ///		static consteval
    ///		std::array<pair_map,(B^2 - 3B + 2)/2> make_multtables() noexcept
    ///{ 			std::array<pair_map,(B^2 - 3B + 2)/2>	ret;
    ///			/// ESTO QUE SIGUE HABRIA QUE HACERLO POR UNROOLING LOOP EN
    /// COMPILE TIME
    ///			/// YA QUE IDX E IDY NO SON CONSTANTES EN TIEMPO DE
    /// COMPILACION
    ///			///	LO MEJOR ES HACERLO EN UNA CLASE TEMPLATE POR
    /// RECURSION 			for(size_t idx{2} ; idx < B ; ++idx) { 				for(size_t idy{idx} ; idy
    ///< B ; ++idy) { 					make_pair(make_array(idx,idy),mult<idx,idy>());
    ///				}
    ///			}
    ///		}

  public:
    constexpr explicit operator uint_t() const noexcept { return m_d; }

    constexpr uint_t get() const noexcept { return (m_d); }

    constexpr explicit operator sig_uint_t() const noexcept
    {
      return static_cast<sig_uint_t>(m_d);
    }

    constexpr explicit operator sig_sint_t() const noexcept
    {
      return static_cast<sig_sint_t>(m_d);
    }
    /// dig_t<10> a{3};
    /// a()->3 (como uint)
    constexpr uint_t operator()() const noexcept { return (m_d); }
    /// dig_t<10> digito{4};
    /// digito() devuelve un 4 de tipo uchint

    constexpr void set_0() noexcept { m_d = 0; }
    constexpr void set_1() noexcept { m_d = 1; }
    constexpr void set_Bm1() noexcept { m_d = B - 1; }
    constexpr void set_Bm2() noexcept { m_d = B - 2; }
    constexpr void set_dig(dig_t d) noexcept { m_d = d.m_d; }
    constexpr void set_dig(uint_t di) noexcept { m_d = di % B; }

  public:
    ////////////////////////////////////////////////////////////////////////////
    consteval static bool is_prime() noexcept
    {
      return auxiliary_functions::is_prime(static_cast<std::size_t>(B));
    }
    ////////////////////////////////////////////////////////////////////////////
    consteval static dig_t dig_max() noexcept { return dig_t(B - 1u); };
    consteval static dig_t dig_submax() noexcept { return dig_t(B - 2u); }
    consteval static dig_t dig_Bm1() noexcept { return dig_t(B - 1u); }
    consteval static dig_t dig_Bm2() noexcept { return dig_t(B - 2u); }
    consteval static dig_t dig_0() noexcept { return dig_t(); }
    consteval static dig_t dig_1() noexcept { return dig_t(1u); }
    ////////////////////////////////////////////////////////////////////////////
    consteval static uint_t ui_max() noexcept { return uint_t(B - 1u); }
    consteval static uint_t ui_submax() noexcept { return uint_t(B - 2u); }
    consteval static uint_t ui_Bm1() noexcept { return uint_t(B - 1u); }
    consteval static uint_t ui_Bm2() noexcept { return uint_t(B - 2u); }
    consteval static uint_t ui_0() noexcept { return uint_t(0u); }
    consteval static uint_t ui_1() noexcept { return uint_t(1u); }
    ////////////////////////////////////////////////////////////////////////////
    consteval static sig_uint_t sui_B() noexcept
    {
      return static_cast<sig_uint_t>(B);
    }
    consteval static sig_uint_t sui_max() noexcept
    {
      return static_cast<sig_uint_t>(B - 1u);
    }
    consteval static sig_uint_t sui_submax() noexcept
    {
      return static_cast<sig_uint_t>(B - 2u);
    }
    consteval static sig_uint_t sui_0() noexcept
    {
      return static_cast<sig_uint_t>(0u);
    }
    consteval static sig_uint_t sui_1() noexcept
    {
      return static_cast<sig_uint_t>(1u);
    }
    ////////////////////////////////////////////////////////////////////////////
    consteval static sig_sint_t ssi_B() noexcept
    {
      return static_cast<sig_sint_t>(B);
    }
    consteval static sig_sint_t ssi_max() noexcept
    {
      return static_cast<sig_sint_t>(B - 1u);
    }
    consteval static sig_sint_t ssi_submax() noexcept
    {
      return static_cast<sig_sint_t>(B - 2u);
    }
    consteval static sig_sint_t ssi_0() noexcept
    {
      return static_cast<sig_sint_t>(0u);
    }
    consteval static sig_sint_t ssi_1() noexcept
    {
      return static_cast<sig_sint_t>(1u);
    }
    ////////////////////////////////////////////////////////////////////////////

  public:
    /************************************/
    /*								  */
    /*	CONSTRUIR DIGITO			  */
    /*								  */
    /************************************/

    ///< CONSTRUCTORES
    ///< CONSTRUCTOR POR DEFECTO
    consteval inline dig_t() noexcept : m_d(0u) {}

  private:
    ///< NORMALIZA ES UNA FUNCION QUE BASICAMENTE SI ENTRA 1524 DEVUELVE 1524%B
    ///< TENIENDO EN CUENTA TIPOS Y SIGNOS
    template <type_traits::integral_c Int_t>
    constexpr static inline uint_t normaliza(Int_t arg) noexcept
    {
      if constexpr (std::is_same_v<Int_t, uint_t>)
      {
        return (arg % B);
      }
      else if constexpr (std::is_signed_v<Int_t>)
      {
        if constexpr (type_traits::maxbase<Int_t>() >=
                      type_traits::maxbase<sig_sint_t>())
        {
          constexpr Int_t sint_0{0}; // ssi_0()
          constexpr Int_t sint_B{B}; // ssi_B()
          Int_t cparg{arg};
          if (arg < sint_0)
          {
            Int_t coc{(-arg) / sint_B};
            coc *= sint_B;
            cparg += coc;
            if (cparg < 0)
              cparg += sint_B;
            if (cparg >= sint_B)
              cparg -= sint_B;
          }
          else
          {
            cparg %= sint_B;
          }
          return static_cast<uint_t>(cparg);
        }
        else
        {
          constexpr sig_sint_t sint_0{0};
          constexpr sig_sint_t sint_B{B};
          sig_sint_t cparg{arg};
          if (arg < sint_0)
          {
            sig_sint_t coc{(-arg) / sint_B};
            coc *= sint_B;
            cparg += coc;
            if (cparg < 0)
              cparg += sint_B;
            if (cparg >= sint_B)
              cparg -= sint_B;
          }
          else
          {
            cparg %= sint_B;
          }
          return static_cast<uint_t>(cparg);
        }
      }
      else
      {
        if constexpr (maxbase<Int_t>() < maxbase<uint_t>())
        {
          constexpr sig_uint_t uint_B{B};
          sig_uint_t cparg{arg};
          if (arg >= uint_B)
          {
            cparg %= uint_B;
          }
          return static_cast<uint_t>(cparg);
        }
        else
        {
          constexpr Int_t uint_B{B};
          Int_t cparg{arg};
          if (arg >= uint_B)
          {
            cparg %= uint_B;
          }
          return static_cast<uint_t>(cparg);
        }
      }
    }

  public:
    /// CONSTRUCTOR A PARTIR DE UN ENTERO ARG
    /// ARG EQUIV ARG+Z*B DONDE Z ES UN ENTERO
    /// EN m_d SOLO QUEREMOS QUE HAYA UN NUMERO ENTRE 0 Y B-1 INCLUSIVES
    template <type_traits::integral_c Int_t>
    constexpr dig_t(Int_t arg) noexcept : m_d(normaliza<Int_t>(arg)) {}

    /// CONSTRUCTOR COPIA POR REFERENCIA
    constexpr dig_t(const dig_t &) noexcept = default;
    /// CONSTRUCTOR POR MOVIMIENTO
    constexpr dig_t(dig_t &&) noexcept = default;

    /// PODEMOS PASAR ARGUMENTOS POR COPIA, REFERENCIA (PUNTEROS) Y MOVIMIENTO
    /// COPIA 		: COPIA EL ARGUMENTO LITERALMENTE PARA PASARLO: EL ORIGINAL
    /// INTACTO REFERENCIA: COPIA LA DIRECCION DEL ARGUMENTO
    ///             (SI ES CONST EL COMPILADOR NO TE DEJA COMPILAR SI LO CAMBIAS)
    /// MOVIMIENTO: SI EL ARGUMETO NO SE VA A UTILIZAR MAS SE LE PASA LA PROPIEDAD
    /// A LA FUNCION

    /************************************/
    /*								  */
    /*	OPERADORES DE ASIGNACION	  */
    /*								  */
    /************************************/

    /// SOBRECARGA DEL OPERATOR=() MEDIANTE REFERENCIA CTE DESDE UN INT_T
    template <type_traits::integral_c Int_t>
    constexpr const dig_t &operator=(const Int_t &a) noexcept
    {
      if constexpr (std::is_same_v<Int_t, uint_t>)
      {
        if (&a != &m_d)
        {
          m_d = normaliza<Int_t>(a);
        }
      }
      else
      {
        m_d = normaliza<Int_t>(a);
      }
      return (*this);
    }
    /// SOBRECARGA DEL OPERATOR=() MEDIANTE REFERENCIA CTE DESDE UN DIG_T
    constexpr dig_t &operator=(const dig_t &) noexcept = default;
    /// SOBRECARGA DEL OPERATOR=() MEDIANTE MOVIMIENTO DESDE UN DIG_T
    constexpr dig_t &operator=(dig_t &&) noexcept = default;
    /// a y b son digitos;
    /// a = std::move(b);
    /// a es identico a b; en b puede no queda nada;

    ///*************************************///
    ///< SENTIDO DE LA DIVISION DE DIGITOS >///
    ///*************************************///

    constexpr bool is_unit() const noexcept
    { // FROM FINITE RINGS

      ///******************************************///
      ///< Es B COPRIMO con m_d ?                 >///
      ///< Es max_comun_divisor(B,m_d)==1 ? 		>///
      ///******************************************///

      if constexpr (is_prime())
      {
        if (!is_0())
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        if (is_1())
          return true;
        else if (std::gcd(B, m_d) != ui_1())
          return false;
        else
          return true;
      }
    }

    constexpr bool is_0_divisor() const noexcept
    { // FROM FINITE RINGS

      ///******************************************///
      ///< Es B NO ES COPRIMO con m_d ?			>///
      ///< Es max_comun_divisor(B,m_d)!=1 ?       >///
      ///******************************************///

      if constexpr (is_prime())
      {
        if (is_0())
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        if (is_0())
          return true;
        else if (std::gcd(B, m_d) != ui_1())
          return true;
        else
          return false;
      }
    }

    constexpr dig_t mult_inv() const noexcept
    { // FROM FINITE RINGS

      if (is_unit())
      {
        if (is_1())
          return dig_1();
        else if (is_Bm1())
          return dig_max();
        else
        {
          for (dig_t index(2); !is_Bm1(); ++index)
            if (index.is_unit())
            {
              if (((*this) * index).is_1())
                return index;
            }
          return dig_0(); /// NUNCA DEBERIA LLEGAR AQUI
                          /// SOLO PARA EVITAR EL WARNING
        }
      }
      else
        return dig_0();
    }

    /**************************************/
    /*									*/
    /*	FUNCIONES PARA CONOCER EL CARRY	*/
    /*									*/
    /**************************************/

    constexpr static dig_t sum_carry(dig_t arg_1, dig_t arg_2) noexcept
    {

      if constexpr (B <= type_traits::middle_max<uint_t>())
      {
        if constexpr ((B % 2) == 0)
        {
          constexpr uint_t Bdiv2{B / 2};
          if ((arg_1() < Bdiv2) && (arg_2() < Bdiv2))
          {
            return dig_0();
          }
          else if ((arg_1() >= Bdiv2) && (arg_2() >= Bdiv2))
          {
            return dig_1();
          }
          else if (arg_1() >= B - arg_2())
          {
            return dig_1();
          }
          else
          {
            return dig_0();
          }
        }
        else
        {
          constexpr uint_t Bdiv2_1{B / 2};
          constexpr uint_t Bdiv2_2{(B / 2) + 1};
          if (((arg_1() < Bdiv2_1) && (arg_2() < Bdiv2_2)) ||
              ((arg_1() < Bdiv2_2) && (arg_2() < Bdiv2_1)))
          {
            return dig_0();
          }
          else if (((arg_1() >= Bdiv2_1) && (arg_2() >= Bdiv2_2)) ||
                   ((arg_1() >= Bdiv2_2) && (arg_2() >= Bdiv2_1)))
          {
            return dig_1();
          }
          else if (arg_1() >= B - arg_2())
          {
            return dig_1();
          }
          else
          {
            return dig_0();
          }
        }
      }
      else
      {
        if constexpr ((B % 2) == 0)
        {
          constexpr sig_uint_t Bdiv2{B / 2};
          if ((arg_1() < Bdiv2) && (arg_2() < Bdiv2))
          {
            return dig_0();
          }
          else if ((arg_1() >= Bdiv2) && (arg_2() >= Bdiv2))
          {
            return dig_1();
          }
          else if (arg_1() >= B - arg_2())
          {
            return dig_1();
          }
          else
          {
            return dig_0();
          }
        }
        else
        {
          constexpr sig_uint_t Bdiv2_1{B / 2};
          constexpr sig_uint_t Bdiv2_2{(B / 2) + 1};
          if (((arg_1() < Bdiv2_1) && (arg_2() < Bdiv2_2)) ||
              ((arg_1() < Bdiv2_2) && (arg_2() < Bdiv2_1)))
          {
            return dig_0();
          }
          else if (((arg_1() >= Bdiv2_1) && (arg_2() >= Bdiv2_2)) ||
                   ((arg_1() >= Bdiv2_2) && (arg_2() >= Bdiv2_1)))
          {
            return dig_1();
          }
          else if (arg_1() >= B - arg_2())
          {
            return dig_1();
          }
          else
          {
            return dig_0();
          }
        }
      }
    }

    /************************************/
    /*								  */
    /*	OPERADORES & &= | |=    	  */
    /*  FUNCIONAN COMO MAX Y MIN		  */
    /*								  */
    /************************************/

    /// DEVOLVER EL MENOR: ANDBITWISE
    /// NO TIENE POSIBILIDAD DE ERROR
    constexpr dig_t operator&(const dig_t &arg) const noexcept
    {
      return (((*this) <= arg) ? (*this) : arg);
    }

    /// DEVOLVER EL MENOR HABIENDOLO ASIGNADO ANDBITWISE AND ASSIGN
    /// NO TIENE POSIBILIDAD DE ERROR
    constexpr const dig_t &operator&=(dig_t arg) noexcept
    {
      if (arg < (*this))
        (*this) = arg;
      return (*this);
    }

    /// DEVOLVER EL MAYOR ORBITWISE
    /// NO TIENE POSIBILIDAD DE ERROR
    constexpr dig_t operator|(const dig_t &arg) const noexcept
    {
      return (((*this) >= arg) ? (*this) : arg);
    }

    /// DEVOLVER EL MAYOR HABIENDOLO ASIGNADO ORBITWISE AND ASSIGN
    /// NO TIENE POSIBILIDAD DE ERROR
    constexpr const dig_t &operator|=(dig_t arg) noexcept
    {
      if (arg > (*this))
        (*this) = arg;
      return (*this);
    }

    /******************************************************/
    /*													*/
    /*	OPERADORES *^n *^=n                             */
    /*  FUNCIONAN COMO Power(*,n) y n = Power(*,n)		*/
    /*	DONDE n ES NATURAL                              */
    /*													*/
    /******************************************************/

    template <type_traits::unsigned_integral_c UIntType>
    constexpr const dig_t &operator^=(UIntType exp) noexcept
    {
      dig_t &cthis{*this};
      if (exp == 0)
      {
        cthis = dig_1();
        return (cthis);
      }
      else if (exp == 1)
      {
        return (cthis);
      }
      else if (exp == 2)
      {
        cthis *= cthis;
        return (cthis);
      }
      else
      {
        const dig_t vthis{*this};
        cthis *= vthis;
        for (UIntType ix{2}; ix < exp; ++ix)
        {
          cthis *= vthis;
        }
        return (cthis);
      }
    }

    template <type_traits::unsigned_integral_c UIntType>
    constexpr dig_t operator^(UIntType exp) const noexcept
    {
      dig_t cpthis{*this};
      cpthis ^= exp;
      return cpthis;
    }

    /****************************************/
    /*				               		  */
    /* OPERADORES COMPARACION				  */
    /*				                	  */
    /****************************************/

    constexpr bool operator==(dig_t a) const noexcept
    {
      return ((a.m_d == m_d) ? true : false);
    }
    constexpr bool operator!=(dig_t a) const noexcept
    {
      return ((a.m_d != m_d) ? true : false);
    }
    constexpr bool operator>=(dig_t a) const noexcept
    {
      return ((a.m_d <= m_d) ? true : false);
    }
    constexpr bool operator>(dig_t a) const noexcept
    {
      return ((a.m_d < m_d) ? true : false);
    }
    constexpr bool operator<=(dig_t a) const noexcept
    {
      return ((a.m_d >= m_d) ? true : false);
    }
    constexpr bool operator<(dig_t a) const noexcept
    {
      return ((a.m_d > m_d) ? true : false);
    }
    /// SI COMPARAMOS O HACEMOS UNA OPERACION CON UN INT_T SIEMPRE SERA
    /// DIG_T @ INT_T -> DIG_T Y NUNCA INT_T @ DIG_T -> ANY_TYPE
    /// METODO PROPIO DE C++20
    constexpr std::strong_ordering operator<=>(dig_t rhs) const noexcept
    {
      const auto lhs_d{m_d};
      const auto rhs_d{rhs.m_d};
      return ((lhs_d < rhs_d) ? std::strong_ordering::less
                              : ((lhs_d > rhs_d) ? std::strong_ordering::greater
                                                 : std::strong_ordering::equal));
    }

    template <type_traits::integral_c Int_t>
    constexpr bool operator==(Int_t rhs) noexcept
    {
      const dig_t &lhs{*this};
      return ((lhs.m_d == normaliza<Int_t>(rhs)) ? true : false);
    }
    /// METODO PROPIO DE C++20
    /// ESTABLECEMOS UN ORDEN PARCIAL SOBRE LOS ENTEROS SI a b EN Z
    /// ESTANDO EN ESTE AMBITO DE BASE B SI a mod B = b mod B
    template <type_traits::integral_c Int_t>
    constexpr std::weak_ordering operator<=>(Int_t rhs) const noexcept
    {
      const dig_t &lhs{*this};
      const uint_t rhs_B{normaliza<Int_t>(rhs)};
      return ((lhs() < rhs_B)   ? std::weak_ordering::less
              : (lhs() > rhs_B) ? std::weak_ordering::greater
                                : std::weak_ordering::equivalent);
    }

    /********************************************/
    /*				    					  */
    /*   ARITMETICOS CON ASIGNACION     		  */
    /*				    					  */
    /********************************************/

    constexpr const dig_t &operator+=(dig_t arg) noexcept
    {
      dig_t &cthis{*this};
      if constexpr (B < type_traits::middle_max<uint_t>())
      {
        m_d += arg.m_d;
        if (m_d >= B)
          m_d -= B;
        return (cthis);
      }
      else
      {
        sig_uint_t tmp{m_d};
        tmp += (arg.m_d);
        if (tmp >= B)
          tmp -= B;
        m_d = static_cast<uint_t>(tmp);
        return (cthis);
      }
    }

    template <type_traits::integral_c Int_t>
    constexpr const dig_t &operator+=(Int_t arg) noexcept
    {
      if constexpr (B >= type_traits::middle_max<uint_t>())
      {
        const sig_uint_t arg1{normaliza<Int_t>(arg)};
        sig_uint_t arg2{m_d};
        arg2 += arg1;
        if (arg2 >= static_cast<Int_t>(B))
          arg2 -= static_cast<Int_t>(B);
        m_d = static_cast<uint_t>(arg2);
        return (*this);
      }
      else
      {
        const uint_t arg1{normaliza<Int_t>(arg)};
        uint_t arg2{m_d};
        arg2 += arg1;
        if (arg2 >= static_cast<Int_t>(B))
          arg2 -= static_cast<Int_t>(B);
        m_d = static_cast<uint_t>(arg2);
        return (*this);
      }
    }

    constexpr const dig_t &operator-=(dig_t arg) noexcept
    {
      sig_sint_t cp_dm{m_d};
      cp_dm -= arg.m_d;
      if (cp_dm < 0)
        cp_dm += ssi_B();
      m_d = cp_dm;
      return (*this);
    }

    template <type_traits::integral_c Int_t>
    constexpr const dig_t &operator-=(Int_t arg) noexcept
    {
      sig_sint_t tmp{normaliza<Int_t>(arg)};
      sig_sint_t este{m_d};
      este -= tmp;
      if (este < static_cast<sig_sint_t>(0))
        este += ssi_B();
      m_d = este;
      return (*this);
    }

    constexpr const dig_t &operator*=(dig_t arg) noexcept
    {
      if constexpr (B < type_traits::sqrt_max<uint_t>())
      {
        m_d *= arg.m_d;
        m_d %= B;
        return (*this);
      }
      else
      {
        sig_uint_t tmp{m_d};
        tmp *= arg.m_d;
        tmp %= static_cast<sig_uint_t>(B);
        m_d = static_cast<uint_t>(tmp);
        return (*this);
      }
    }

    template <type_traits::integral_c Int_t>
    constexpr const dig_t &operator*=(Int_t arg) noexcept
    {
      const Int_t tmp{normaliza<Int_t>(arg)};
      if constexpr (std::is_signed_v<Int_t>)
      {
        if constexpr (sizeof(Int_t) > sizeof(uint_t))
        {
          using SIG2_SINT_T = type_traits::sig_SInt_for_SInt_t<Int_t>;
          const SIG2_SINT_T norm_arg{tmp};
          SIG2_SINT_T este{m_d};
          este *= norm_arg;
          este %= static_cast<SIG2_SINT_T>(B);
          m_d = static_cast<uint_t>(este);
          return (*this);
        }
        else
        {
          const sig_sint_t norm_arg{tmp};
          sig_sint_t este{m_d};
          este *= norm_arg;
          este %= static_cast<sig_sint_t>(B);
          m_d = static_cast<uint_t>(este);
          return (*this);
        }
      }
      else
      {
        if constexpr (sizeof(Int_t) > sizeof(uint_t))
        {
          using SIG2_UINT_T = type_traits::sig_UInt_for_UInt_t<Int_t>;
          const SIG2_UINT_T norm_arg{tmp};
          SIG2_UINT_T este{m_d};
          este *= norm_arg;
          este %= static_cast<SIG2_UINT_T>(B);
          m_d = static_cast<uint_t>(este);
          return (*this);
        }
        else
        {
          const sig_uint_t norm_arg{tmp};
          sig_uint_t este{m_d};
          este *= norm_arg;
          este %= static_cast<sig_uint_t>(B);
          m_d = static_cast<uint_t>(este);
          return (*this);
        }
      }
    }

    constexpr const dig_t &operator/=(dig_t arg) noexcept
    {
      if (arg.m_d != ui_0())
        m_d /= arg.m_d;
      return (*this);
    }

    template <type_traits::integral_c Int_t>
    constexpr const dig_t &operator/=(Int_t arg) noexcept
    {
      uint_t cparg{normaliza<Int_t>(arg)};
      dig_t tmp{cparg};
      if (tmp != dig_0())
        (*this) /= tmp;
      return (*this);
    }

    constexpr const dig_t &operator%=(dig_t arg) noexcept
    {
      if (arg.m_d != ui_0())
        m_d %= arg.m_d;
      return (*this);
    }

    template <type_traits::integral_c Int_t>
    constexpr const dig_t &
    operator%=(Int_t arg) noexcept
    {
      dig_t cparg{normaliza<Int_t>(arg)};
      if (cparg != dig_0())
        (*this) %= cparg;
      return (*this);
    }
    /// Tengo serias dudas que la division y el resto euclideo tengan cabida
    /// entre los operadores aritmeticos de un tipo dig_t
    /// DUDA SATISFECHA: TIENEN CABIDA PORQUE EL INVERSO MULTIPLICATIVO ETC.
    /// SOLO NOS SIRVE SI ESTUVIERAMOS CONSTRUYENDO NUMEROS DE UN ANILLO FINITO

    /********************************/
    /*			     			  */
    /* 		  PRE Y POST 		  */
    /*			CIRCULARES		  */
    /*							  */
    /********************************/

    constexpr const dig_t &operator++() noexcept
    {
      (m_d < ui_max()) ? (++m_d) : (m_d = ui_0());
      return (*this);
    }

    constexpr dig_t operator++(int) noexcept
    {
      dig_t ret(*this);
      ++(*this);
      return ret;
    }

    constexpr const dig_t &operator--() noexcept
    {
      if (m_d > ui_0())
      {
        --m_d;
      }
      else
      {
        m_d = ui_max();
      }
      return (*this);
    }

    constexpr dig_t operator--(int) noexcept
    {
      dig_t ret(*this);
      --(*this);
      return ret;
    }

    /****************************************/
    /*									  */
    /*    OPERADORES ARITMETICOS   		  */
    /*									  */
    /****************************************/

    constexpr dig_t operator+(dig_t arg) const noexcept
    {
      dig_t ret(*this);
      ret += arg;
      return ret;
    }

    constexpr dig_t operator-(dig_t arg) const noexcept
    {
      dig_t ret(*this);
      ret -= arg;
      return ret;
    }

    constexpr dig_t operator*(dig_t arg) const noexcept
    {
      dig_t ret(*this);
      ret *= arg;
      return ret;
    }

    constexpr dig_t operator/(dig_t arg) const noexcept
    {
      dig_t ret(*this);
      ret /= arg;
      return ret;
    }

    constexpr dig_t operator%(dig_t arg) const noexcept
    {
      dig_t ret(*this);
      ret %= arg;
      return ret;
    }

    template <type_traits::integral_c Int_type>
    constexpr dig_t operator+(Int_type arg) const noexcept
    {
      dig_t ret(*this);
      ret += normaliza<Int_type>(arg);
      return ret;
    }

    template <type_traits::integral_c Int_type>
    constexpr dig_t operator-(Int_type arg) const noexcept
    {
      dig_t ret(*this);
      const dig_t tmp(normaliza<Int_type>(arg));
      ret -= tmp;
      return ret;
    }

    template <type_traits::integral_c Int_type>
    constexpr dig_t operator*(Int_type arg) const noexcept
    {
      dig_t ret(*this);
      const dig_t tmp(normaliza<Int_type>(arg));
      ret *= tmp;
      return ret;
    }

    template <type_traits::integral_c Int_type>
    constexpr dig_t operator/(Int_type arg) const noexcept
    {
      dig_t ret(*this);
      const dig_t cparg(normaliza<Int_type>(arg));
      if (cparg != dig_0())
        ret /= cparg;
      return ret;
    }

    template <type_traits::integral_c Int_type>
    constexpr dig_t operator%(Int_type arg) const noexcept
    {
      dig_t ret(*this);
      const dig_t cparg(normaliza<Int_type>(arg));
      if (cparg != dig_0())
        ret %= cparg;
      return ret;
    }

    /****************************************/
    /*									  */
    /*	     COMPLEMENTO BASE 			  */
    /*	      Y BASE MENOS 1			  */
    /*									  */
    /****************************************/

    /// EN BASE B, B-1-m_d ES EL COMPL_Bm1(m_d)
    constexpr

        dig_t
        operator~() const noexcept
    {
      return dig_t(ui_max() - m_d);
    }

    /// EN BASE B, B-m_d ES EL COMPL_B(m_d)
    constexpr dig_t operator-() const noexcept
    {
      return dig_t((m_d == 0) ? 0 : (B - m_d));
    }

    constexpr /// "C_Bm1" es identico a "operator!()"
        dig_t C_Bm1() const noexcept
    {
      return dig_t(ui_max() - m_d);
    }

    constexpr /// "C_B" es identico a "operator-()"
        dig_t C_B() const noexcept
    {
      return dig_t((m_d == 0) ? 0 : (B - m_d));
    }

    /****************************************************/
    /*				    							  */
    /*    MODIFICADORES COMPLEMENTO	    			  */
    /*				    							  */
    /****************************************************/

    constexpr const dig_t &mC_Bm1() noexcept
    {
      m_d = (ui_max() - m_d);
      return (*this);
    }

    constexpr const dig_t &mC_B() noexcept
    {
      (m_d == 0) ? (m_d) : (m_d = (B - m_d));
      return (*this);
    }

    /// dig_t<uchint,7> a,b,c;
    /// a = 5;
    /// b = 2;
    /// c = 0;
    /// !a == 1 is TRUE  a.C_Bm1() == 1 is TRUE
    /// !b == 4 is TRUE  b.C_Bm1() == 4 is TRUE
    /// !c == 6 is TRUE  c.C_Bm1() == 6 is TRUE
    /// -a == 2 is TRUE  a.C_B() == 2 is TRUE
    /// -b == 5 is TRUE  b.C_B() == 5 is TRUE
    /// -c == 0 is TRUE  c.C_B() == 0 is TRUE
    ///  a.mC_Bm1() == 1 is TRUE  a == 1 is TRUE
    ///  b.mC_Bm1() == 4 is TRUE  b == 4 is TRUE
    ///  c.mC_Bm1() == 6 is TRUE  c == 6 is TRUE
    ///  a.mC_B() 	== 2 is TRUE  a	== 2 is TRUE
    ///  b.mC_B() 	== 5 is TRUE  b	== 5 is TRUE
    ///  c.mC_B() 	== 0 is TRUE  c	== 0 is TRUE

    /**********************************/
    /*                            	*/
    /*   	NULO Y MAXIMO         	  	*/
    /*                            	*/
    /**********************************/

    constexpr bool is_0() const noexcept { return (m_d == ui_0()); }

    constexpr bool is_1() const noexcept { return (m_d == ui_1()); }

    constexpr bool is_0or1() const noexcept
    {
      return ((m_d == ui_0()) || (m_d == ui_1()));
    }

    constexpr bool is_not_1() const noexcept { return (m_d != ui_1()); }

    constexpr bool is_not_0() const noexcept { return (m_d != ui_0()); }

    constexpr bool is_not_0or1() const noexcept { return (!is_0or1()); }

    constexpr bool is_Bm1() const noexcept { return (m_d == ui_Bm1()); }

    constexpr bool is_not_Bm1() const noexcept
    {
      return (m_d != ui_Bm1());
    }

    constexpr bool is_Bm1orBm2() const noexcept
    {
      return (is_Bm1() || is_Bm2());
    }

    constexpr bool is_not_Bm1orBm2() const noexcept
    {
      return (is_not_Bm1() && is_not_Bm2());
    }

    constexpr bool is_Bm2() const noexcept { return (m_d == ui_Bm2()); }

    constexpr bool is_not_Bm2() const noexcept
    {
      return (m_d != ui_Bm2());
    }

    constexpr bool is_not_maxormin() const noexcept
    {
      return (is_not_0() && is_not_Bm1());
    }

    constexpr bool is_maxormin() const noexcept
    {
      return (is_0() || is_Bm1());
    }

    constexpr bool is_far_maxormin() const noexcept
    {
      if constexpr (B == 2u)
      {
        return false;
      }
      else
      {
        return (is_not_0() && is_not_Bm1() && is_not_1() && is_not_Bm2());
      }
    }

    constexpr bool is_near_maxormin() const noexcept
    {
      if constexpr (B == 2u)
      {
        return true;
      }
      else
      {
        return (is_0() || is_Bm1() || is_1() || is_Bm2());
      }
    }

    /**********************************/
    /*		    	                */
    /* 	     VARIOS CASTS	        */
    /*						        */
    /**********************************/

    /// TIENE QUE DEVOLVER STD::STRING
  private:
    std::string num_to_string() const noexcept
    {
      const std::int64_t data_member = static_cast<std::int64_t>(this->m_d);
      std::ostringstream fmtr_obj;
      fmtr_obj << data_member;
      const std::string ret{fmtr_obj.str()};
      return ret;
    }

    std::string radix_str() const noexcept
    {
      constexpr std::int64_t radix = static_cast<std::int64_t>(B);
      std::ostringstream fmtr_obj;
      fmtr_obj << radix;
      const std::string ret{static_cast<std::string>("B") + static_cast<std::string>(fmtr_obj.str())};
      return ret;
    }

  public:
    constexpr std::uint64_t radix() const { return B; }

    constexpr std::string to_string() const noexcept
    {
      const std::string num{this->num_to_string()};
      const std::string ret{"dig#" + num + "#" + radix_str()};
      return ret;
    }
  };

  /************************************/
  /*                                  */
  /*         ISTREAM Y OSTREAM        */
  /*                                  */
  /************************************/

  template <std::uint64_t Base>
    requires(Base > 1)
  std::istream &operator>>(std::istream &is, dig_t<Base> &arg)
  {
    // Usar tipos directamente sin alias locales para evitar problemas de acceso dependiente
    enum class estado_e
    {
      e0,
      e1,
      e2,
      e3,
      e4,
      e5,
      e6,
      e7,
      e8
    };

    std::string sds;
    std::string num_dig;
    std::string num_base;

    estado_e est_act = estado_e::e0;
    typename dig_t<Base>::sig_uint_t indice{0};
    typename dig_t<Base>::sig_uint_t numero_base_recogido{0};
    uint_t numero{0};

    char c;
    is >> sds;
    do
    {
      c = sds[indice];
      switch (est_act)
      {
      case estado_e::e0:
        if (c == 'd')
        {
          est_act = estado_e::e1;
        }
        break;
      case estado_e::e1:
        if (c == '#')
        {
          est_act = estado_e::e2;
        }
        else
        {
          est_act = estado_e::e0;
        }
        break;
      case estado_e::e2:
        if ((c <= '9') and (c >= '0'))
        {
          est_act = estado_e::e3;
          num_dig.push_back(c - '0');
        }
        else
        {
          est_act = estado_e::e0;
          num_dig.clear();
        }
        break;
      case estado_e::e3:
        if ((c <= '9') and (c >= '0'))
          num_dig.push_back(c - '0');
        else if (c == '#')
          est_act = estado_e::e4;
        else
        {
          est_act = estado_e::e0;
          num_dig.clear();
        }
        break;
      case estado_e::e4:
        if (c == 'B')
          est_act = estado_e::e5;
        else
        {
          est_act = estado_e::e0;
          num_dig.clear();
        }
        break;
      case estado_e::e5:
        if ((c <= '9') and (c >= '0'))
        {
          est_act = estado_e::e6;
          num_base.push_back(c - '0');
        }
        else
        {
          est_act = estado_e::e0;
          num_dig.clear();
          num_base.clear();
        }
        break;
      case estado_e::e6:
        if ((c <= '9') and (c >= '0'))
          num_base.push_back(c - '0');
        else if ((c == ' ') || (c == '\0'))
          est_act = estado_e::e7;
        break;
      case estado_e::e7:
        if ((c != ' ') || (c != '\0'))
        {
          est_act = estado_e::e0;
          num_dig.clear();
          num_base.clear();
        }
        break;
      case estado_e::e8:
      default:
        break;
      }
      ++indice;
      if (est_act == estado_e::e7)
      {
        for (std::size_t k = 0; k < num_base.size(); ++k)
        {
          numero_base_recogido *= 10;
          numero_base_recogido += num_base[k];
        }
        if (numero_base_recogido != Base)
        {
          est_act = estado_e::e0;
          num_dig.clear();
          num_base.clear();
        }
        else
          est_act = estado_e::e8;
      }
    } while (est_act != estado_e::e8);

    for (std::size_t k = 0; k < num_dig.size(); ++k)
    {
      numero *= 10;
      numero += num_dig[k];
    }
    numero %= Base;
    arg = dig_t<Base>(numero);
    return is;
  }

  template <std::uint64_t Base>
    requires(Base > 1)
  std::ostream &operator<<(std::ostream &os, dig_t<Base> arg)
  {
    os << "d[" << static_cast<std::int64_t>(arg())
       << "]B" << static_cast<std::int64_t>(Base);
    return os;
  }

} // namespace NumRepr
#endif // DIG_T__HPP___INCLUDED
