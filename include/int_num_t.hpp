#ifndef INT_NUM_T_HPP_INCLUDED
#define INT_NUM_T_HPP_INCLUDED

#include "base_num_t.hpp"
#include "nat_num_t.hpp"
#include "int_reg_digs_t.hpp"

namespace NumRepr {

/// Sign enumeration for signed integers
enum class sign_e { vplus = 0, vminus = 1 };

/// Form enumeration
enum class forma_t { noraw, raw };


template <std::uint64_t B>
  requires(B > 1)
class int_num_t : protected base_num_t<B> {
public:
  using dig_t = dig_t<B>;
  using UINT_T = typename dig_t::UINT_T;
  using base_num_t = base_num_t<B>;
  using nat_num_t = nat_num_t<B>;
  using SIG_UINT_T = typename dig_t::SIG_UINT_T;
  using SIG_SINT_T = typename dig_t::SIG_SINT_T;

  // Iterator types
  using str_iterator = typename base_num_t::str_iterator;
  using c_str_iterator = typename base_num_t::c_str_iterator;
  using r_str_iterator = typename base_num_t::r_str_iterator;
  using cr_str_iterator = typename base_num_t::cr_str_iterator;

  // Register types for arithmetic operations
  template <std::size_t N>
  using int_reg_N_digs_t = int_reg_digs_t<B, N>;
  using int_reg_digs_t = int_reg_N_digs_t<2>;

private:
  sign_e signo;           // Sign representation
  int_reg_digs_t aux;     // Auxiliary variable for operations

public:
  /************************************/
  /*                                  */
  /*           CONSTRUCTORS           */
  /*                                  */
  /************************************/

  /// Default constructor - creates zero
  constexpr int_num_t() noexcept 
    : base_num_t{}, signo{sign_e::vplus}, aux{} {
    base_num_t &cthis = (*this);
    cthis.resize(1);
    cthis[0] = dig_t{0};
  }

  /// Copy constructor
  constexpr int_num_t(const int_num_t &other) noexcept = default;

  /// Move constructor
  constexpr int_num_t(int_num_t &&other) noexcept = default;

  /// Constructor from natural number
  constexpr int_num_t(const nat_num_t &natural) noexcept 
    : base_num_t{}, signo{sign_e::vplus}, aux{} {
    base_num_t &cthis = (*this);
    cthis.resize(natural.size());
    for (std::size_t i = 0; i < natural.size(); ++i) {
      cthis[i] = natural[i];
    }
  }

  /// Constructor from natural number with sign
  constexpr int_num_t(sign_e s, const nat_num_t &natural) noexcept 
    : base_num_t{}, signo{s}, aux{} {
    base_num_t &cthis = (*this);
    cthis.resize(natural.size());
    for (std::size_t i = 0; i < natural.size(); ++i) {
      cthis[i] = natural[i];
    }
  }

  /// Constructor from register pair
  constexpr int_num_t(const int_reg_digs_t &a) noexcept 
    : base_num_t{}, signo{sign_e::vplus}, aux{} {
    base_num_t &cthis = (*this);
    cthis.resize(2);
    cthis[0] = a[0];
    cthis[1] = a[1];
    reduce();
  }

  /// Constructor from register pair with sign
  constexpr int_num_t(sign_e s, const int_reg_digs_t &a) noexcept 
    : base_num_t{}, signo{s}, aux{} {
    base_num_t &cthis = (*this);
    cthis.resize(2);
    cthis[0] = a[0];
    cthis[1] = a[1];
    reduce();
  }

      aux += spardigs(vplus, 0, cthis[i]);

  /// Constructor from character      cthis[i] = aux.g_uds();

  constexpr int_num_t(char ch) noexcept       aux = spardigs(vplus, 0, aux.g_decs());

    : base_num_t{}, signo{sign_e::vplus}, aux{} {    }

    base_num_t &cthis = (*this);    aux = spardigs();

      }

    if (ch == '-') {

      signo = sign_e::vminus;public:

      cthis.resize(1);  inline void resize(size_t arg) {

      cthis[0] = dig_t{0};<<<<<<< HEAD

    } else if (ch == '+') {    dig_string &cthis = (*this);

      signo = sign_e::vplus;    cthis.dig_string::resize(arg);

      cthis.resize(1);    return;

      cthis[0] = dig_t{0};  }

    } else if (ch >= '0' && ch <= '9') {  inline void push_front(dig_t<B> parg) {

      UINT_T digit_val = static_cast<UINT_T>(ch - '0');    dig_string &cthis = (*this);

      if (digit_val < B) {    cthis.dig_string::push_front(parg);

        cthis.resize(1);    return;

        cthis[0] = dig_t{digit_val};  }

      } else {  inline void push_back(dig_t<B> arg) { this->dig_string_t<B>::push_back(arg); }

        cthis.resize(1);

        cthis[0] = dig_t{0};private:

      }  inline int_num &insert(size_t pos1, const dig_t<B> chardig) {

    } else {    dig_string &cthis = (*this);

      cthis.resize(1);    cthis.dig_string::insert(pos1, 1, chardig);

      cthis[0] = dig_t{0};    return (*this);

    }  }

  }  inline int_num &insert(size_t pos1, size_t n, dig_t<B> c) {

    dig_string &cthis = (*this);

  /// Constructor from integral type    cthis.dig_string::insert(pos1, n, c);

  template <type_traits::integral_c Int_t>=======

  constexpr int_num_t(Int_t value) noexcept     num_basic &cthis = (*this);

    : base_num_t{}, signo{sign_e::vplus}, aux{} {    cthis.num_basic::resize(arg);

    base_num_t &cthis = (*this);    return;

      }

    if (value == 0) {  inline void push_front(dig_t<B> parg) {

      cthis.resize(1);    num_basic &cthis = (*this);

      cthis[0] = dig_t{0};    cthis.num_basic::push_front(parg);

      return;    return;

    }  }

  inline void push_back(dig_t<B> arg) { this->num_basic_t<B>::push_back(arg); }

    // Handle sign

    if constexpr (std::is_signed_v<Int_t>) {private:

      if (value < 0) {  inline num_int &insert(size_t pos1, const dig_t<B> chardig) {

        signo = sign_e::vminus;    num_basic &cthis = (*this);

        value = -value;    cthis.num_basic::insert(pos1, 1, chardig);

      }    return (*this);

    }  }

  inline num_int &insert(size_t pos1, size_t n, dig_t<B> c) {

    // Convert to digits in base B    num_basic &cthis = (*this);

    std::vector<dig_t> digits;    cthis.num_basic::insert(pos1, n, c);

    Int_t temp = value;>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

        return (*this);

    while (temp > 0) {  }

      digits.push_back(dig_t{static_cast<UINT_T>(temp % B)});

      temp /= B;public:

    }<<<<<<< HEAD

      inline const int_num &operator&=(const int_num &arg) {

    cthis.resize(digits.size());    dig_string &cthis = (*this);

    for (std::size_t i = 0; i < digits.size(); ++i) {=======

      cthis[i] = digits[i];  inline const num_int &operator&=(const num_int &arg) {

    }    num_basic &cthis = (*this);

    reduce();>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

  }    cthis += arg;

    return (*this);

public:  }

  /************************************/

  /*                                  */private:

  /*        ASSIGNMENT OPERATORS     */  // string& erase ( size_t pos = 0, size_t n = npos );

  /*                                  */

  /************************************/<<<<<<< HEAD

  inline int_num &erase(size_t pos, size_t npos) {

  /// Copy assignment    int_num &cthis = (*this);

  constexpr int_num_t &operator=(const int_num_t &other) noexcept {=======

    if (this != &other) {  inline num_int &erase(size_t pos, size_t npos) {

      base_num_t &cthis = (*this);    num_int &cthis = (*this);

      cthis.clear();>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

      signo = other.signo;    size_t npos_2 = npos;

      aux = other.aux;    const size_t sz = size();

          if ((sz == npos) and (pos == 0)) {

      const std::size_t sz = other.size();      npos_2--;

      cthis.resize(sz);      if (signo == vplus)

      for (std::size_t k = 0; k < sz; ++k) {        cthis[sz - 1] = dig_t<B>(0);

        cthis[k] = other[k];      else

      }        cthis[sz - 1] = dig_t<B>(B - 1);

      reduce();    }

    }<<<<<<< HEAD

    return (*this);    cthis.dig_string::erase(pos, npos_2);

  }=======

    cthis.num_basic::erase(pos, npos_2);

  /// Move assignment>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

  constexpr int_num_t &operator=(int_num_t &&other) noexcept = default;    return (*this);

  }

  /// Assignment from natural number

  constexpr const int_num_t &operator=(const nat_num_t &natural) noexcept {  inline iterator erase(iterator first, iterator last) {

    base_num_t &cthis = (*this);<<<<<<< HEAD

    cthis.clear();    int_num &cthis = (*this);

    signo = sign_e::vplus;=======

    aux = int_reg_digs_t{};    num_int &cthis = (*this);

    >>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    cthis.resize(natural.size());    size_t npos = last - first;

    for (std::size_t i = 0; i < natural.size(); ++i) {    const size_t sz = size();

      cthis[i] = natural[i];    if (sz == npos) {

    }      last--;

    reduce();      cthis[sz - 1] = d_0<B>();

    return (*this);    }

  }<<<<<<< HEAD

    return dig_string::erase(first, last);

  /// Assignment from register pair  }

  constexpr const int_num_t &operator=(const int_reg_digs_t &a) noexcept {

    base_num_t &cthis = (*this);public:

    cthis.clear();  int_num() {

    signo = sign_e::vplus;    int_num &cthis = *this;

    aux = int_reg_digs_t{};    signo = vplus;

        aux = spardigs();

    cthis.resize(2);    cthis.dig_string::clear();

    cthis[0] = a[0];    cthis.dig_string::push_back(dig_t<B>(0));

    cthis[1] = a[1];  }

    reduce();

    return (*this);  int_num(const int_num &a) {

  }    int_num &cthis = *this;

=======

  /// Assignment from integral type    return num_basic::erase(first, last);

  template <type_traits::integral_c Int_t>  }

  constexpr const int_num_t &operator=(Int_t value) noexcept {

    *this = int_num_t{value};public:

    return (*this);  num_int() {

  }    num_int &cthis = *this;

    signo = vplus;

public:    aux = spardigs();

  /************************************/    cthis.num_basic::clear();

  /*                                  */    cthis.num_basic::push_back(dig_t<B>(0));

  /*        BASIC OPERATIONS          */  }

  /*                                  */

  /************************************/  num_int(const num_int &a) {

    num_int &cthis = *this;

  /// Get size>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

  constexpr std::size_t size() const noexcept {    signo = a.signo;

    const base_num_t &cthis = (*this);    aux = a.aux;

    return cthis.size();    cthis.clear();

  }    cthis.resize(a.size());

    for (usint k = 0; k < a.size(); ++k)

  /// Access operators      cthis[k] = a[k];

  constexpr dig_t operator[](std::size_t arg) const noexcept {    cthis.reduce();

    const base_num_t &cthis = (*this);  }

    return cthis[arg];

  }<<<<<<< HEAD

  int_num(const string &a) {

  constexpr dig_t &operator[](std::size_t arg) noexcept {    int_num &cthis = *this;

    base_num_t &cthis = (*this);=======

    return cthis[arg];  num_int(const string &a) {

  }    num_int &cthis = *this;

>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

  /// Get sign    signo = vplus;

  constexpr sign_e get_sign() const noexcept {    cthis.clear();

    return signo;    cthis.resize(a.size());

  }    unsigned int l = 0;

    bool Exit = false;

  /// Set sign    usint k = 0;

  constexpr void set_sign(sign_e s) noexcept {    while ((a[k] < '0') || (a[k] > (char(B - 1) + '0')))

    signo = s;      ++k;

  }    if (k >= a.size()) {

<<<<<<< HEAD

  /// Clear      int_num &cthis = *this;

  constexpr void clear() noexcept {=======

    base_num_t &cthis = (*this);      num_int &cthis = *this;

    cthis.clear();>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    cthis.resize(1);      cthis.resize(0);

    cthis[0] = dig_t{0};      Exit = true;

    signo = sign_e::vplus;    }

  }    if (!Exit) {

      for (; (k < a.size()) && (!Exit); ++k) {

  /// Push back        if ((a[k] >= '0') && (a[k] <= (char(B - 1) + '0'))) {

  constexpr void push_back(dig_t arg) noexcept {          cthis[l] = Char2Dig<B>(a[k]);

    base_num_t &cthis = (*this);          ++l;

    cthis.push_back(arg);        } else

  }          Exit = true;

      }

  /// Push front    }

  constexpr void push_front(dig_t parg) noexcept {    cthis.reduce();

    base_num_t &cthis = (*this);  }

    cthis.insert(cthis.begin(), parg);

  }<<<<<<< HEAD

  int_num(dig a0) {

private:    int_num &cthis = *this;

  /// Resize=======

  constexpr void resize(std::size_t arg) noexcept {  num_int(dig a0) {

    base_num_t &cthis = (*this);    num_int &cthis = *this;

    cthis.resize(arg);>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

  }    signo = vplus;

    cthis.clear();

  /// Two's complement conversion (conditional)    cthis.resize(1);

  constexpr void mC_B_incondicionado() noexcept {    cthis[0] = a0;

    base_num_t &cthis = (*this);  }

    

    // Complement each digit (B-1-digit)<<<<<<< HEAD

    for (std::size_t i = 0; i < cthis.size(); ++i) {  int_num(dig a1, dig a0) {

      cthis[i] = cthis[i].C_Bm1();    int_num &cthis = *this;

    }=======

      num_int(dig a1, dig a0) {

    // Add 1    num_int &cthis = *this;

    aux[0] = cthis[0];>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    aux[1] = dig_t{1};    signo = vplus;

    aux[0] += aux[1];    cthis.clear();

    cthis[0] = aux[0];    cthis.resize(2);

        cthis[0] = a0;

    dig_t carry = (aux[0]() + dig_t{1}() >= B) ? dig_t{1} : dig_t{0};    cthis[1] = a1;

        cthis.reduce();

    std::size_t i = 1;  }

    while (i < cthis.size() && carry != dig_t{0}) {

      aux[0] = cthis[i];<<<<<<< HEAD

      aux[1] = carry;  int_num(dig a2, dig a1, dig a0) {

      aux[0] += aux[1];    int_num &cthis = *this;

      cthis[i] = aux[0];=======

      carry = (aux[0]() >= B) ? dig_t{1} : dig_t{0};  num_int(dig a2, dig a1, dig a0) {

      ++i;    num_int &cthis = *this;

    }>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

        signo = vplus;

    if (carry != dig_t{0}) {    cthis.clear();

      cthis.push_back(carry);    cthis.resize(3);

    }    cthis[0] = a0;

  }    cthis[1] = a1;

    cthis[2] = a2;

public:    cthis.reduce();

  /************************************/  }

  /*                                  */

  /*        UTILITY FUNCTIONS        */<<<<<<< HEAD

  /*                                  */  int_num(const std::vector<dig> &arg) {

  /************************************/    int_num &cthis = *this;

=======

  /// Remove leading zeros  num_int(const std::vector<dig> &arg) {

  constexpr void reduce() noexcept {    num_int &cthis = *this;

    base_num_t &cthis = (*this);>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

        signo = vplus;

    // Remove leading zeros but keep at least one digit    cthis.clear();

    while (cthis.size() > 1 && cthis.back() == dig_t{0}) {    cthis.resize(arg.size());

      cthis.pop_back();    for (uint ix = 0; ix < arg.size(); ++ix)

    }      cthis[ix] = arg[ix];

        cthis.reduce();

    // Ensure we have at least one digit  }

    if (cthis.empty()) {

      cthis.resize(1);<<<<<<< HEAD

      cthis[0] = dig_t{0};  int_num(const std::list<dig> &arg) {

      signo = sign_e::vplus;    int_num &cthis = *this;

    }=======

      num_int(const std::list<dig> &arg) {

    // If the number is zero, make sure the sign is positive    num_int &cthis = *this;

    if (is_0()) {>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

      signo = sign_e::vplus;    signo = vplus;

    }    cthis.clear();

  }    typename list<dig>::iterator it = arg.begin();

    typename list<dig>::const_iterator itf = arg.end();

  /// Check if zero    for (; it != itf; ++it)

  constexpr bool is_0() const noexcept {      cthis.push_back(*it);

    const base_num_t &cthis = (*this);    cthis.reduce();

    return (cthis.size() == 1 && cthis[0] == dig_t{0});  }

  }

<<<<<<< HEAD

  /// Check if one  int_num(sign_e s, dig a0) {

  constexpr bool is_1() const noexcept {    int_num &cthis = *this;

    const base_num_t &cthis = (*this);=======

    return (signo == sign_e::vplus && cthis.size() == 1 && cthis[0] == dig_t{1});  num_int(sign_e s, dig a0) {

  }    num_int &cthis = *this;

>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

  /// Check if minus one    signo = s;

  constexpr bool is_m1() const noexcept {    aux = spardigs(vplus, 0, a0);

    const base_num_t &cthis = (*this);    cthis.clear();

    return (signo == sign_e::vminus && cthis.size() == 1 && cthis[0] == dig_t{1});    cthis.resize(1);

  }    cthis[0] = aux.g_uds();

    aux = spardigs(vplus, 0, 0);

  /// Check if positive    cthis.reduce();

  constexpr bool is_positive() const noexcept {  }

    return (signo == sign_e::vplus && !is_0());

  }<<<<<<< HEAD

  int_num(sign_e s, dig a1, dig a0) {

  /// Check if negative    int_num &cthis = *this;

  constexpr bool is_negative() const noexcept {=======

    return (signo == sign_e::vminus);  num_int(sign_e s, dig a1, dig a0) {

  }    num_int &cthis = *this;

>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

  /// Check if even    signo = s;

  constexpr bool is_even() const noexcept {    aux = spardigs(vplus, 0, 0);

    const base_num_t &cthis = (*this);    cthis.clear();

    return (cthis[0]() % 2 == 0);    cthis.resize(2);

  }    cthis[0] = a0;

    cthis[1] = a1;

  /// Check if odd    cthis.reduce();

  constexpr bool is_odd() const noexcept {  }

    return !is_even();

  }<<<<<<< HEAD

  int_num(sign_e s, dig a2, dig a1, dig a0) {

  /// Get absolute value    int_num &cthis = *this;

  constexpr nat_num_t abs() const noexcept {=======

    nat_num_t result;  num_int(sign_e s, dig a2, dig a1, dig a0) {

    const base_num_t &cthis = (*this);    num_int &cthis = *this;

    >>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    result.resize(cthis.size());    signo = s;

    for (std::size_t i = 0; i < cthis.size(); ++i) {    aux = spardigs(vplus, 0, 0);

      result[i] = cthis[i];    cthis.clear();

    }    cthis.resize(3);

    result.reduce();    cthis[0] = a0;

    return result;    cthis[1] = a1;

  }    cthis[2] = a2;

    cthis.reduce();

  /// Negate  }

  constexpr int_num_t operator-() const noexcept {

    int_num_t result = *this;<<<<<<< HEAD

    if (!result.is_0()) {  int_num(sign_e s, const std::vector<dig> &arg, forma_t argforma = noraw) {

      result.signo = (result.signo == sign_e::vplus) ? sign_e::vminus : sign_e::vplus;    int_num &cthis = *this;

    }=======

    return result;  num_int(sign_e s, const std::vector<dig> &arg, forma_t argforma = noraw) {

  }    num_int &cthis = *this;

>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

public:    signo = s;

  /************************************/    cthis.clear();

  /*                                  */    cthis.resize(arg.size());

  /*       COMPARISON OPERATORS       */    for (uint ix = 0; ix < arg.size(); ++ix) {

  /*                                  */      cthis[ix] = arg[ix];

  /************************************/    }

    if (argforma == noraw)

  constexpr bool operator==(const int_num_t &other) const noexcept {      cthis.reduce();

    if (signo != other.signo) {  }

      return false;

    }<<<<<<< HEAD

      int_num(sign_e s, const std::list<dig> &arg) {

    const base_num_t &cthis = (*this);    int_num &cthis = *this;

    const base_num_t &other_base = other;=======

      num_int(sign_e s, const std::list<dig> &arg) {

    if (cthis.size() != other_base.size()) {    num_int &cthis = *this;

      return false;>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    }    signo = s;

        cthis.clear();

    for (std::size_t i = 0; i < cthis.size(); ++i) {    cthis.resize(arg.size());

      if (cthis[i] != other_base[i]) {    typename std::list<dig>::const_iterator it = arg.begin();

        return false;    typename std::list<dig>::const_iterator it_end = arg.end();

      }    for (; it != it_end; ++it)

    }      cthis.push_front(*it);

    return true;    cthis.reduce();

  }  }



  constexpr bool operator!=(const int_num_t &other) const noexcept {<<<<<<< HEAD

    return !(*this == other);  int_num(spardigs a) {

  }    int_num &cthis = *this;

=======

  constexpr bool operator<(const int_num_t &other) const noexcept {  num_int(spardigs a) {

    // Handle different signs    num_int &cthis = *this;

    if (signo == sign_e::vminus && other.signo == sign_e::vplus) {>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

      return true;    signo = a.g_sign();

    }    cthis.clear();

    if (signo == sign_e::vplus && other.signo == sign_e::vminus) {    cthis.resize(2);

      return false;    cthis[0] = a.g_first();

    }    cthis[1] = a.g_second();

        cthis.reduce();

    // Same sign, compare magnitudes  }

    const base_num_t &cthis = (*this);

    const base_num_t &other_base = other;<<<<<<< HEAD

      int_num(pardigs a) {

    bool magnitude_less;    int_num &cthis = *this;

    if (cthis.size() != other_base.size()) {=======

      magnitude_less = (cthis.size() < other_base.size());  num_int(pardigs a) {

    } else {    num_int &cthis = *this;

      magnitude_less = false;>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

      // Compare from most significant digit    signo = vplus;

      for (std::size_t i = cthis.size(); i > 0; --i) {    cthis.clear();

        if (cthis[i-1] != other_base[i-1]) {    cthis.resize(2);

          magnitude_less = (cthis[i-1] < other_base[i-1]);    cthis[0] = a.g_first();

          break;    cthis[1] = a.g_second();

        }    cthis.reduce();

      }  }

    }

    <<<<<<< HEAD

    // If both positive, smaller magnitude means smaller number  int_num(sign_e s, pardigs a) {

    // If both negative, smaller magnitude means larger number    int_num &cthis = *this;

    return (signo == sign_e::vplus) ? magnitude_less : !magnitude_less;=======

  }  num_int(sign_e s, pardigs a) {

    num_int &cthis = *this;

  constexpr bool operator<=(const int_num_t &other) const noexcept {>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    return (*this < other) || (*this == other);    cthis.signo = s;

  }    cthis.clear();

    cthis.resize(2);

  constexpr bool operator>(const int_num_t &other) const noexcept {    cthis[0] = a.g_first();

    return !(*this <= other);    cthis[1] = a.g_second();

  }    cthis.reduce();

  }

  constexpr bool operator>=(const int_num_t &other) const noexcept {

    return !(*this < other);<<<<<<< HEAD

  }  int_num(char ch) {

    int_num &cthis = *this;

  /// Three-way comparison (C++20)=======

  constexpr std::strong_ordering operator<=>(const int_num_t &other) const noexcept {  num_int(char ch) {

    if (*this < other) return std::strong_ordering::less;    num_int &cthis = *this;

    if (*this > other) return std::strong_ordering::greater;>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    return std::strong_ordering::equal;    cthis.clear();

  }    signo = vplus;

    cthis.resize(1);

public:    cthis[0] = Char2Dig<B>(ch);

  /************************************/  }

  /*                                  */

  /*       ARITHMETIC OPERATORS       */<<<<<<< HEAD

  /*                                  */  int_num(uchint a) {

  /************************************/    int_num &cthis = *this;

=======

  /// Addition  num_int(uchint a) {

  constexpr int_num_t operator+(const int_num_t &other) const noexcept {    num_int &cthis = *this;

    int_num_t result = *this;>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    result += other;    signo = vplus;

    return result;    cthis.clear();

  }    cthis.resize(1);

    cthis[0] = UInt2Dig<B>(a);

  constexpr int_num_t &operator+=(const int_num_t &other) noexcept {  }

    // If signs are the same, add magnitudes and keep sign

    if (signo == other.signo) {<<<<<<< HEAD

      nat_num_t this_abs = abs();  template <typename Int_T> int_num(Int_T a) {

      nat_num_t other_abs = other.abs();    int_num &cthis = *this;

      this_abs += other_abs;=======

        template <typename Int_T> num_int(Int_T a) {

      // Convert back    num_int &cthis = *this;

      *this = int_num_t{signo, this_abs};>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    } else {    cthis.clear();

      // Different signs: subtract magnitudes    const ullint longitud = num_digs_max_base_B_en_Int_T<Int_T, B>();

      nat_num_t this_abs = abs();    cthis.resize(longitud);

      nat_num_t other_abs = other.abs();    uint indice = 0;

          if (a >= 0) {

      if (this_abs >= other_abs) {      for (int i = 0; i < longitud; i++)

        this_abs -= other_abs;        cthis[i] = dig(0);

        *this = int_num_t{signo, this_abs};      signo = vplus;

      } else {      ullint rem = 0, coc = a;

        other_abs -= this_abs;      while (coc >= B) {

        *this = int_num_t{other.signo, other_abs};        rem = coc % B;

      }        cthis[indice] = UInt2Dig<B>(rem);

    }        indice++;

            coc = coc / B;

    reduce();      }

    return *this;      rem = coc % B;

  }      cthis[indice] = UInt2Dig<B>(rem);

      indice++;

  /// Subtraction    } else {

  constexpr int_num_t operator-(const int_num_t &other) const noexcept {      for (int i = 0; i < longitud; i++)

    int_num_t result = *this;        cthis[i] = dig(B - 1);

    result -= other;      signo = vminus;

    return result;      long long int rem = 0, coc = -a;

  }      while (coc >= B) {

        rem = coc % B;

  constexpr int_num_t &operator-=(const int_num_t &other) noexcept {        cthis[indice] = !(Int2Dig<B>(rem));

    // Subtraction is addition with opposite sign        indice++;

    int_num_t negated_other = -other;        coc = coc / B;

    *this += negated_other;      }

    return *this;      cthis[indice] = !(Int2Dig<B>(coc));

  }      ++cthis;

      // cthis.signo = vplus;

  /// Increment operators      // cthis.reduce();

  constexpr int_num_t &operator++() noexcept {      cthis.signo = vminus;

    *this += int_num_t{1};    }

    return *this;    cthis.reduce();

  }  }



  constexpr int_num_t operator++(int) noexcept {<<<<<<< HEAD

    int_num_t temp = *this;  const int_num &operator=(const int_num &a) {

    ++(*this);    int_num &cthis = *this;

    return temp;=======

  }  const num_int &operator=(const num_int &a) {

    num_int &cthis = *this;

  /// Decrement operators>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

  constexpr int_num_t &operator--() noexcept {    signo = a.signo;

    *this -= int_num_t{1};    aux = a.aux;

    return *this;    cthis.clear();

  }    cthis.resize(a.size());

    for (usint k = 0; k < a.size(); ++k)

  constexpr int_num_t operator--(int) noexcept {      cthis[k] = a[k];

    int_num_t temp = *this;    cthis.reduce();

    --(*this);    return cthis;

    return temp;  }

  }

<<<<<<< HEAD

public:  const int_num &operator=(const num_uint<B> &a) {

  /************************************/    int_num &cthis = *this;

  /*                                  */=======

  /*          STRING CONVERSION       */  const num_int &operator=(const num_uint<B> &a) {

  /*                                  */    num_int &cthis = *this;

  /************************************/>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    signo = vplus;

  /// Convert to string in base B    aux = vplus;

  constexpr std::string to_string() const noexcept {    cthis.clear();

    const base_num_t &cthis = (*this);    cthis.resize(a.size());

        for (usint k = 0; k < a.size(); ++k)

    std::string result;      cthis[k] = a[k];

    result.reserve(cthis.size() * 3 + 10); // Rough estimate    cthis.reduce();

        return cthis;

    // Add sign  }

    if (signo == sign_e::vminus) {

      result = "int#-[";<<<<<<< HEAD

    } else {  const int_num &operator=(const pardigs_t<B> &a) {

      result = "int#+[";    int_num &cthis = *this;

    }=======

      const num_int &operator=(const pardigs_t<B> &a) {

    // Add digits from most significant to least significant    num_int &cthis = *this;

    for (std::size_t i = cthis.size(); i > 0; --i) {>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

      if (i != cthis.size()) result += ",";    signo = vplus;

      result += std::to_string(cthis[i-1]());    aux.p_sign(vplus);

    }    aux.p_decs(0);

        aux.p_uds(0);

    result += "]#B" + std::to_string(B);    cthis.clear();

    return result;    cthis.resize(2);

  }    cthis[1] = a.g_decs();

    cthis[0] = a.g_uds();

  /// Convert to decimal string (base 10 representation)    cthis.reduce();

  std::string to_decimal_string() const noexcept {    return cthis;

    if (is_0()) return "0";  }

    

    std::string result;<<<<<<< HEAD

    if (signo == sign_e::vminus) {  const int_num &operator=(const spardigs_t<B> &a) {

      result = "-";    int_num &cthis = *this;

    }=======

      const num_int &operator=(const spardigs_t<B> &a) {

    // For now, return simple representation    num_int &cthis = *this;

    result += to_string();>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    return result;    signo = a.signo;

  }    aux.p_sign(vplus);

};    aux.p_decs(0);

    aux.p_uds(0);

/************************************/    cthis.clear();

/*                                  */    cthis.resize(2);

/*        STREAM OPERATORS          */    cthis[1] = a.g_decs();

/*                                  */    cthis[0] = a.g_uds();

/************************************/    cthis.reduce();

    return cthis;

template <std::uint64_t Base>  }

  requires(Base > 1)

std::ostream &operator<<(std::ostream &os, const int_num_t<Base> &num) {<<<<<<< HEAD

  os << num.to_string();  const int_num &operator=(const dig_t<B> &a) {

  return os;    int_num &cthis = *this;

}=======

  const num_int &operator=(const dig_t<B> &a) {

} // namespace NumRepr    num_int &cthis = *this;

>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

#endif // INT_NUM_T_HPP_INCLUDED    signo = vplus;
    aux.p_sign(vplus);
    aux.p_decs(0);
    aux.p_uds(0);
    cthis.clear();
    cthis.resize(1);
    cthis[0] = a;
    return cthis;
  }

<<<<<<< HEAD
  template <typename Int_T> const int_num &operator=(Int_T a) {
    int_num &cthis = *this;
=======
  template <typename Int_T> const num_int &operator=(Int_T a) {
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    cthis.clear();
    const ullint longitud = num_digs_max_base_B_en_Int_T<Int_T, B>();
    cthis.resize(longitud);
    uint indice = 0;
    if (a >= 0) {
      for (int i = 0; i < longitud; i++)
        cthis[i] = dig(0);
      signo = vplus;
      ullint rem = 0, coc = a;
      while (coc >= B) {
        rem = coc % B;
        cthis[indice] = UInt2Dig<B>(rem);
        indice++;
        coc = coc / B;
      }
      rem = coc % B;
      cthis[indice] = UInt2Dig<B>(rem);
      indice++;
    } else {
      for (int i = 0; i < longitud; i++)
        cthis[i] = dig(B - 1);
      signo = vminus;
      long long int rem = 0, coc = -a;
      while (coc >= B) {
        rem = coc % B;
        cthis[indice] = Int2Dig<B>(rem);
        indice++;
        coc = coc / B;
      }
      cthis[indice] = Int2Dig<B>(coc);
      cthis.mC_B_incondicionado();
      cthis.signo = vplus;
      cthis.reduce();
      cthis.signo = vminus;
    }
    cthis.reduce();
    return cthis;
  }

<<<<<<< HEAD
  const int_num &operator=(const std::vector<dig> &arg) {
    int_num &cthis = *this;
=======
  const num_int &operator=(const std::vector<dig> &arg) {
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    signo = vplus;
    cthis.clear();
    cthis.resize(arg.size());
    for (uint ix = 0; ix < arg.size(); ++ix) {
      cthis[ix] = arg[ix];
    }
    cthis.reduce();
    return cthis;
  }

<<<<<<< HEAD
  const int_num &operator=(const std::list<dig> &arg) {
    int_num &cthis = *this;
=======
  const num_int &operator=(const std::list<dig> &arg) {
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    signo = vplus;
    cthis.clear();
    cthis.resize(arg.size());
    typename std::list<dig>::const_iterator it = arg.begin();
    typename std::list<dig>::const_iterator it_end = arg.end();
    for (; it != it_end; ++it)
      cthis.push_front(*it);
    cthis.reduce();
    return cthis;
  }

  /***************************************/
  /*								                         */
  /*  DIGITOS NO SIGNIFICATIVOS	 */
  /*								                         */
  /***************************************/

  usint ceros_a_la_izqda() const {
<<<<<<< HEAD
    const int_num &cthis = (*this);
=======
    const num_int &cthis = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    // digitos no significativos para números positivos
    bool Exit = false;
    int sz = 0;
    const size_t fin = this->size();
    for (int i = fin - 1; (i >= 0) and (!Exit); --i) {
      bool char_es_0 = (cthis[i] == 0);
      if (char_es_0) {
        ++sz;
      } else
        Exit = true;
    }
    return sz;
  }
  // digitos no significativos para números positivos

  usint unos_a_la_izqda() const {
<<<<<<< HEAD
    const int_num &cthis = (*this);
=======
    const num_int &cthis = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    // digitos no significativos para números negativos
    bool Exit = false;
    int sz = 0;
    const size_t fin = cthis.size();
    for (int i = fin - 1; (i >= 0) and (!Exit); --i) {
      bool char_es_max = (cthis[i] == (dig_t<B>::max_dig()));
      if (char_es_max) {
        ++sz;
      } else
        Exit = true;
    }
    return sz;
  }
  // digitos no significativos para números negativos

  size_t ceros_a_la_drcha() const {
    // const num_uint & cthis = (*this);
    bool Exit = false;
    size_t sz = 0;
    const size_t fin = this->size();
    const size_t finl = fin - 1;
    if (this->operator[](finl) == 0) {
      for (int i = finl; (i >= 0) and (!Exit); --i) {
        if (this->operator[](i) == 0)
          ++sz;
        else
          Exit = true;
      }
    }
    return sz;
  }

  size_t unos_a_la_drcha() const {
    // const num_uint & cthis = (*this);
    bool Exit = false;
    size_t sz = 0;
    const size_t fin = this->size();
    const size_t finl = fin - 1;
    if (this->operator[](finl) == 0) {
      for (int i = finl; (i >= 0) and (!Exit); --i) {
        if (this->operator[](i) == dig_t<B>::max)
          ++sz;
        else
          Exit = true;
      }
    }
    return sz;
  }

  bool filled_of_all_digits_are_Bm1() const {
<<<<<<< HEAD
    const int_num &cthis = (*this);
=======
    const num_int &cthis = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const int longitud = cthis.size();
    for (int i = 0; i < longitud; i++)
      if (cthis[i] != dig(B - 1))
        return false;
    return true;
  }

  bool filled_of_all_digits_are_0() const {
<<<<<<< HEAD
    const int_num &cthis = (*this);
=======
    const num_int &cthis = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const int longitud = cthis.size();
    for (int i = 0; i < longitud; ++i)
      if (cthis[i] != dig(0))
        return false;
    return true;
  }

  usint digs_no_significativos() const {
<<<<<<< HEAD
    const int_num &cthis = (*this);
=======
    const num_int &cthis = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    // digitos no significativos
    usint retorno;
    // if ((size()<1) and (signo==vminus)) return 0;
    if (signo == vplus) {
      retorno = cthis.ceros_a_la_izqda();
      return retorno;
    } else {
      retorno = cthis.unos_a_la_izqda();
      return retorno;
    }
  }

  usint digs_fracc_no_significativos() const {
    // const num_uint & cthis = (*this);
    // digitos no significativos
    return this->ceros_a_la_drcha();
  }
  // digitos no significativos para números positivos fraccionaria
  usint Bm1_a_la_izqda() const {
<<<<<<< HEAD
    int_num &cthis = *this;
=======
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    // digitos no significativos para números negativos
    bool Exit = false;
    usint sz = 0;
    usint k = (cthis.size() - 1);
    for (; (k > 0) and (!Exit); --k) {
      if (cthis[k] == (B - 1))
        ++sz;
      else
        Exit = true;
    }
    if ((k == 0) and (cthis[0] == (B - 1)) and (!Exit))
      ++sz;
    return sz;
  }
  // digitos no significativos para números negativo
  usint Bm1_a_la_drcha() const {
<<<<<<< HEAD
    int_num &cthis = *this;
=======
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    // digitos no significativos para números negativos fraccionarios
    const size_t fin = cthis.size();
    bool Exit = false;
    usint sz = 0;
    usint k = 0;
    for (; (k < fin) and (!Exit); ++k) {
      if (cthis[k] == (B - 1))
        ++sz;
      else
        Exit = true;
    }
    return sz;
  }

  /***********************************************/
  /*									                                */
  /*   OPERACIONES COMPARATIVAS  		*/
  /*									                                */
  /**********************************************/

<<<<<<< HEAD
  bool operator==(const int_num &arg) const {
    const int_num &cthis = *this;
=======
  bool operator==(const num_int &arg) const {
    const num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const slint thisnsz = cthis.digs_no_significativos();
    const slint thisvsz = cthis.size() - thisnsz;
    const slint argnsz = arg.digs_no_significativos();
    const slint argvsz = arg.size() - argnsz;
    if ((thisvsz > argvsz) || (thisvsz < argvsz) || (signo != arg.signo))
      return false;
    else {
      for (slint k = (thisvsz - 1); k > 0; --k) {
        if (arg[k] != cthis[k])
          return false;
      }
      if ((arg[0]) != (cthis[0]))
        return false;
      else
        return true;
    }
  }

<<<<<<< HEAD
  bool operator!=(const int_num &arg) const {
    const int_num &cthis = *this;
=======
  bool operator!=(const num_int &arg) const {
    const num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const slint thisnsz = digs_no_significativos();
    const slint thisvsz = (cthis.size()) - thisnsz;
    const slint argnsz = arg.digs_no_significativos();
    const slint argvsz = arg.size() - argnsz;
    if ((thisvsz > argvsz) || (thisvsz < argvsz) || (signo != arg.signo))
      return true;
    else {
      for (slint k = (thisvsz - 1); k > 0; --k)
        if (arg[k] != cthis[k])
          return true;
      if (arg[0] != cthis[0])
        return true;
      else
        return false;
    }
  }

<<<<<<< HEAD
  bool operator>=(const int_num &arg) const {
    const int_num &cthis = *this;
=======
  bool operator>=(const num_int &arg) const {
    const num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const slint thissz = cthis.size();
    const slint thisnsz =
        ((thissz == 1) ? 0 : (cthis.digs_no_significativos()));
    // cout << "J vale   " << cthis << endl;
    const slint thisvsz = thissz - thisnsz;
    const slint argsz = arg.size();
    const slint argnsz = ((argsz == 1) ? 0 : (arg.digs_no_significativos()));
    // cout << "I vale   " << arg << endl;
    const slint argvsz = argsz - argnsz;

    if ((signo == vplus) and (arg.signo == vminus))
      return true;
    else if ((signo == vminus) and (arg.signo == vplus))
      return false;
    else if ((signo == vminus) and (arg.signo == vminus)) {
      if (thisvsz < argvsz)
        return true;
      else if (thisvsz > argvsz)
        return false;
    } else if ((signo == vplus) and (arg.signo == vplus)) {
      if (thisvsz > argvsz)
        return true;
      else if (thisvsz < argvsz)
        return false;
    }
    for (slint k = (thisvsz - 1); k > -1; --k) {
      if ((cthis[k] > arg[k]))
        return true;
      else if ((cthis[k] < arg[k]))
        return false;
    }
    return true;
  }

<<<<<<< HEAD
  bool operator<=(const int_num &arg) const {
    const int_num &cthis = *this;
=======
  bool operator<=(const num_int &arg) const {
    const num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const slint thissz = cthis.size();
    const slint thisnsz =
        ((thissz == 1) ? 0 : (cthis.digs_no_significativos()));
    // cout << "J vale   " << cthis << endl;
    const slint thisvsz = thissz - thisnsz;
    const slint argsz = arg.size();
    const slint argnsz = ((argsz == 1) ? 0 : (arg.digs_no_significativos()));
    // cout << "I vale   " << arg << endl;
    const slint argvsz = argsz - argnsz;

    if ((signo == vplus) and (arg.signo == vminus))
      return false;
    else if ((signo == vminus) and (arg.signo == vplus))
      return true;
    else if ((signo == vminus) and (arg.signo == vminus)) {
      if (thisvsz < argvsz)
        return false;
      else if (thisvsz > argvsz)
        return true;
    } else if ((signo == vplus) and (arg.signo == vplus)) {
      if (thisvsz > argvsz)
        return false;
      else if (thisvsz < argvsz)
        return true;
    }
    for (slint k = (thisvsz - 1); k > -1; --k) {
      if ((cthis[k] > arg[k]))
        return false;
      else if ((cthis[k] < arg[k]))
        return true;
    }
    return true;
  }

<<<<<<< HEAD
  bool operator>(const int_num &arg) const {
    const int_num &cthis = *this;
=======
  bool operator>(const num_int &arg) const {
    const num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const slint thissz = cthis.size();
    const slint thisnsz =
        ((thissz == 1) ? 0 : (cthis.digs_no_significativos()));
    const slint thisvsz = thissz - thisnsz;
    const slint argsz = arg.size();
    const slint argnsz = ((argsz == 1) ? 0 : (arg.digs_no_significativos()));
    const slint argvsz = argsz - argnsz;

    if ((signo == vplus) and (arg.signo == vminus))
      return true;
    else if ((signo == vminus) and (arg.signo == vplus))
      return false;
    else if ((signo == vminus) and (arg.signo == vminus)) {
      if (thisvsz < argvsz)
        return true;
      else if (thisvsz > argvsz)
        return false;
    } else if ((signo == vplus) and (arg.signo == vplus)) {
      if (thisvsz > argvsz)
        return true;
      else if (thisvsz < argvsz)
        return false;
    }
    for (slint k = (thisvsz - 1); k > -1; --k) {
      if ((cthis[k] > arg[k]))
        return true;
      else if ((cthis[k] < arg[k]))
        return false;
    }
    return false;
  }

<<<<<<< HEAD
  bool operator<(const int_num &arg) const {
    const int_num &cthis = *this;
=======
  bool operator<(const num_int &arg) const {
    const num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const slint thissz = cthis.size();
    const slint thisnsz =
        ((thissz == 1) ? 0 : (cthis.digs_no_significativos()));
    // cout << "J vale   " << cthis << endl;
    const slint thisvsz = thissz - thisnsz;
    const slint argsz = arg.size();
    const slint argnsz = ((argsz == 1) ? 0 : (arg.digs_no_significativos()));
    // cout << "I vale   " << arg << endl;
    const slint argvsz = argsz - argnsz;

    if ((signo == vplus) and (arg.signo == vminus))
      return false;
    else if ((signo == vminus) and (arg.signo == vplus))
      return true;
    else if ((signo == vminus) and (arg.signo == vminus)) {
      if (thisvsz < argvsz)
        return false;
      else if (thisvsz > argvsz)
        return true;
    } else if ((signo == vplus) and (arg.signo == vplus)) {
      if (thisvsz > argvsz)
        return false;
      else if (thisvsz < argvsz)
        return true;
    }
    for (slint k = (thisvsz - 1); k > -1; --k) {
      if ((cthis[k] > arg[k]))
        return false;
      else if ((cthis[k] < arg[k]))
        return true;
    }
    return false;
  }

  /**********************************************/
  /*									                                */
  /*     OPERACIONES ARITMETICAS 		*/
  /* 									                                */
  /**********************************************/

<<<<<<< HEAD
  int_num operator+(const int_num &arg) const {
    const int_num &cthis = *this;
    int_num ret(cthis);
    ret.reduce();
    int_num cpy(arg);
    cpy.reduce();
    spardigs_t<B> tempt();
    spardigs_t<B> tempa();
    const int_num *po = 0;
=======
  num_int operator+(const num_int &arg) const {
    const num_int &cthis = *this;
    num_int ret(cthis);
    ret.reduce();
    num_int cpy(arg);
    cpy.reduce();
    spardigs_t<B> tempt();
    spardigs_t<B> tempa();
    const num_int *po = 0;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    usint sza = arg.size();
    usint szt = ret.size();
    p_usint pszmin = 0;
    p_usint pszmax = 0;
    if (sza <= szt) {
      pszmin = &sza;
      pszmax = &szt;
      po = &ret;
    } else {
      pszmin = &szt;
      pszmax = &sza;
      po = &cpy;
    }

    usint &szmin = *pszmin;
    usint &szmax = *pszmax;
<<<<<<< HEAD
    const int_num &obj = *po;
=======
    const num_int &obj = *po;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    usint k = 0;
    ret.aux = spardigs();
    for (; k < szmin; ++k) {
      tempt.p_uds(ret[k]);
      tempa.p_uds(arg[k]);
      tempt += tempa;
      tempt += aux;
      ret[k] = tempt.g_uds();
      ret.aux =
          spardigs(tempt.g_sign(), ((tempt.g_sign() == vplus) ? (0) : (B - 1)),
                   tempt.g_decs());
    }
    for (; k < szmax; ++k) {
      tempt.p_first(obj[k]);
      tempt += aux;
      ret[k] = tempt.g_first();
      ret.aux =
          spardigs(tempt.g_sign(), ((tempt.g_sign() == vplus) ? (0) : (B - 1)),
                   tempt.g_decs());
    }

    ret.push_back(ret.aux.g_uds());
    ret.push_back(ret.aux.g_decs());
    ret.signo = ret.aux.g_sign();
    ret.aux = spardigs();
    return ret;
  }

<<<<<<< HEAD
  int_num operator-(const int_num &arg) const {
    int_num &cthis = *this;
    int_num ret;
    int_num cpy(-arg);
=======
  num_int operator-(const num_int &arg) const {
    num_int &cthis = *this;
    num_int ret;
    num_int cpy(-arg);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    ret.reduce();
    cpy.reduce();
    spardigs tempt();
    spardigs tempa();
<<<<<<< HEAD
    const int_num *po = 0;
=======
    const num_int *po = 0;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    usint sza = arg.lst_arg.size();
    usint szt = ret.lst_arg.size();
    p_usint pszmin = 0;
    p_usint pszmax = 0;
    if (sza <= szt) {
      pszmin = &sza;
      pszmax = &szt;
      po = &ret;
    } else {
      pszmin = &szt;
      pszmax = &sza;
      po = &cpy;
    }

    usint &szmin = *pszmin;
    usint &szmax = *pszmax;
<<<<<<< HEAD
    const int_num &obj = *po;
=======
    const num_int &obj = *po;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    usint k = 0;
    ret.aux = spardigs();
    for (; k < szmin; ++k) {
      tempt.p_first(ret[k]);
      tempa.p_first(arg[k]);
      tempt += tempa;
      tempt += aux;
      ret[k] = tempt.g_first();
      ret.aux =
          spardigs(tempt.g_sign(), ((tempt.g_sign() == vplus) ? (0) : (B - 1)),
                   tempt.g_second());
    }
    for (; k < szmax; ++k) {
      tempt.p_first(obj[k]);
      tempt += aux;
      ret[k] = tempt.g_first();
      ret.aux =
          spardigs(tempt.g_sign(), ((tempt.g_sign() == vplus) ? (0) : (B - 1)),
                   tempt.g_second());
    }

    ret.lst_digs.push_back(ret.aux.g_first());
    ret.lst_digs.push_back(ret.aux.g_second());
    ret.signo = ret.aux.g_sign();
    ret.aux = spardigs();
    return ret;
  }

<<<<<<< HEAD
  // Utilizamos una funcion int_num * dig_t
  int_num operator*(const int_num &arg) const {
    int_num &cthis = *this;
    int_num sumatemp;
    int_num multtemp;
    int_num m1(cthis.abs());
    m1.reduce();
    int_num m2(arg.abs());
=======
  // Utilizamos una funcion num_int * dig_t
  num_int operator*(const num_int &arg) const {
    num_int &cthis = *this;
    num_int sumatemp;
    num_int multtemp;
    num_int m1(cthis.abs());
    m1.reduce();
    num_int m2(arg.abs());
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    m2.reduce();
    multtemp = cthis * m2[0];
    sumatemp = multtemp;
    for (usint j = 1; j < m2.size(); ++j) {
<<<<<<< HEAD
      multtemp = cthis * m2[j]; // int_num * dig_t
=======
      multtemp = cthis * m2[j]; // num_int * dig_t
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
      multtemp.insert(0, j, 0);
      sumatemp += multtemp;
    }
    if (signo != arg.signo)
      sumatemp.mC_B();
    return sumatemp;
  }

<<<<<<< HEAD
  int_num operator/(const int_num &arg) const {
    int_num &cthis = *this;
    const sign_e sgn_ndo = signo;
    const sign_e sgn_sor = arg.signo;
    int_num dvndo_int(this->abs());
    dvndo_int.reduce();
    int_num rem(dvndo_int);

    int_num dvsor_int(arg.abs());
=======
  num_int operator/(const num_int &arg) const {
    num_int &cthis = *this;
    const sign_e sgn_ndo = signo;
    const sign_e sgn_sor = arg.signo;
    num_int dvndo_int(this->abs());
    dvndo_int.reduce();
    num_int rem(dvndo_int);

    num_int dvsor_int(arg.abs());
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    dvsor_int.reduce();

    const usint cssor = dvsor_int.ceros_a_la_drcha(); // ¿?

<<<<<<< HEAD
    int_num dvndo_fra(dvndo_int.substr(0, cssor));
=======
    num_int dvndo_fra(dvndo_int.substr(0, cssor));
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    dvsor_int.lst_digs.erase(0, cssor); // division por una potencia de B

    dvsor_int.reduce();
    dvndo_int.reduce();

    dvndo_fra.reduce();

    const usint longtndo = dvndo_int.size();
    const usint longtndo2 = dvndo_fra.size();
    const usint longtsor = dvsor_int.size();
    const usint longsor = longtsor;

    // hemos dividido por los ceros del divisor (por una potencia de B)
    // tanto divisor como dividendo, obteniendo dvndo_int y dvsor_int como
    // cocientes enteros.
    div_uno(rem, dvndo_int, dvsor_int, longtndo, longsor);
    // ahora hacemos lo mismo con el cociente de las potencias de B del
    // dividendo obteniendo dvndo_fra

    /* *
        RemReal = RemObtenido*B^cssor + Dvndo_fra

        rem = rem.lst_digs.insert(0,cssor,0);
        rem += dvndo_fra;
    * */
    if (sgn_ndo != sgn_sor)
      dvndo_int.mC_B();
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    return dvndo_int;
  }

<<<<<<< HEAD
  int_num operator%(const int_num &arg) const {
    int_num &cthis = *this;
    int_num dvndo_int(this->abs());
    dvndo_int.reduce();
    int_num rem(dvndo_int);

    int_num dvsor_int(arg.abs());
=======
  num_int operator%(const num_int &arg) const {
    num_int &cthis = *this;
    num_int dvndo_int(this->abs());
    dvndo_int.reduce();
    num_int rem(dvndo_int);

    num_int dvsor_int(arg.abs());
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    dvsor_int.reduce();

    const usint cssor = dvsor_int.ceros_a_la_drcha(); // ¿?

<<<<<<< HEAD
    int_num dvndo_fra(dvndo_int.substr(0, cssor));
=======
    num_int dvndo_fra(dvndo_int.substr(0, cssor));
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    dvsor_int.lst_digs.erase(0, cssor); // division por una potencia de B

    dvsor_int.reduce();
    dvndo_int.reduce();

    dvndo_fra.reduce();

    const usint longtndo = dvndo_int.size();
    const usint longtndo2 = dvndo_fra.size();
    const usint longtsor = dvsor_int.size();
    const usint longsor = longtsor;

    // hemos dividido por los ceros del divisor (por una potencia de B)
    // tanto divisor como dividendo, obteniendo dvndo_int y dvsor_int como
    // cocientes enteros.
    div_uno(rem, dvndo_int, dvsor_int, longtndo, longsor);
    // ahora hacemos lo mismo con el cociente de las potencias de B del
    // dividendo obteniendo dvndo_fra

    /* *
        RemReal = RemObtenido*B^cssor + Dvndo_fra
    * */
    rem = rem.lst_digs.insert(0, cssor, 0);
    rem += dvndo_fra;
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    return rem;
  }

<<<<<<< HEAD
  // int_num operator + (spardigs) const;
  // int_num operator - (spardigs) const;
  // int_num operator * (spardigs) const;
  // int_num operator / (spardigs) const;
  // int_num operator % (spardigs) const;
  // int_num operator + (n2digs_t) const;
  // int_num operator - (n2digs_t) const;
  // int_num operator * (n2digs_t) const;
  // int_num operator / (n2digs_t) const;
  // int_num operator % (n2digs_t) const;
  // int_num operator + (pardigs) const;
  // int_num operator - (pardigs) const;

  int_num operator*(pardigs a) const {
    int_num &cthis = *this;
    pardigs temp;
    dig carry = 0;
    int_num ret(*this);
=======
  // num_int operator + (spardigs) const;
  // num_int operator - (spardigs) const;
  // num_int operator * (spardigs) const;
  // num_int operator / (spardigs) const;
  // num_int operator % (spardigs) const;
  // num_int operator + (n2digs_t) const;
  // num_int operator - (n2digs_t) const;
  // num_int operator * (n2digs_t) const;
  // num_int operator / (n2digs_t) const;
  // num_int operator % (n2digs_t) const;
  // num_int operator + (pardigs) const;
  // num_int operator - (pardigs) const;

  num_int operator*(pardigs a) const {
    num_int &cthis = *this;
    pardigs temp;
    dig carry = 0;
    num_int ret(*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    for (usint k = 0; k < (cthis.size() - 1); ++k) {
      temp = cthis[k] * (a.g_first());
      temp += carry;
      ret[k] = temp.g_first();
      carry = temp.g_second();
    }
    if (carry != 0)
      ret.insert((cthis.size()) - 1, 1, carry);
    ret.reduce();
    carry = 0;
    for (usint k = 0; k < ((cthis.size()) - 1); ++k) {
      temp = cthis[k] * (a.g_second());
      temp += carry;
      ret.substr(k + 1, ret.size() - 1) += temp.g_first(); // ¿?
      carry = temp.g_second();
    }
    if (carry != 0)
      ret.insert((cthis.size()) - 1, 1, carry);
    ret.reduce();

    if (signo == vminus)
      ret.mC_B();

    return ret;
  }

<<<<<<< HEAD
  //	int_num operator / (pardigs) const;
  //	int_num operator % (pardigs) const;

  int_num operator+(dig arg) const {
    int_num &cthis = *this;
    int_num ret(*this);
    ret.reduce();
    spardigs tempt();
    spardigs tempa();
    const int_num *po = 0;
=======
  //	num_int operator / (pardigs) const;
  //	num_int operator % (pardigs) const;

  num_int operator+(dig arg) const {
    num_int &cthis = *this;
    num_int ret(*this);
    ret.reduce();
    spardigs tempt();
    spardigs tempa();
    const num_int *po = 0;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const usint sza = 1;
    usint szt = ret.lst_arg.size();
    p_usint pszmin = 0;
    p_usint pszmax = 0;
    if (sza <= szt) {
      pszmin = &sza;
      pszmax = &szt;
      po = &ret;
    } else {
      pszmin = &szt;
      pszmax = &sza;
      po = &arg;
    }

    usint &szmin = *pszmin;
    usint &szmax = *pszmax;
<<<<<<< HEAD
    const int_num &obj = *po;
=======
    const num_int &obj = *po;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    usint k = 0;
    ret.aux = spardigs();
    tempt.p_first(ret[0]);
    tempa.p_first(arg);

    for (k = 1; k < szmin; ++k) {
      tempt.p_first(ret[k]);
      tempt += tempa;
      tempt += aux;
      ret[k] = tempt.g_first();
      ret.aux =
          spardigs(tempt.g_sign(), ((tempt.g_sign() == vplus) ? (0) : (B - 1)),
                   tempt.g_second());
    }
    for (; k < szmax; ++k) {
      dig D = ret[k];
      tempt.p_first(D);
      tempt += aux;
      ret[k] = tempt.g_first();
      ret.aux =
          spardigs(tempt.g_sign(), ((tempt.g_sign() == vplus) ? (0) : (B - 1)),
                   tempt.g_second());
    }

    ret.cthis.push_back(ret.aux.g_first());
    ret.cthis.push_back(ret.aux.g_second());
    ret.signo = ret.aux.g_sign();
    ret.aux = spardigs();
    return ret;
  }

<<<<<<< HEAD
  int_num operator-(dig arg) const {
    int_num &cthis = *this;
    int_num ret(*this);
=======
  num_int operator-(dig arg) const {
    num_int &cthis = *this;
    num_int ret(*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    ret.reduce();
    spardigs cpy(-arg);
    spardigs tempt();
    spardigs tempa();
    usint szt = ret.lst_arg.size();
    usint k = 0;
    ret.aux = spardigs();
    tempt.p_first(ret[0]);
    tempa.p_first(arg.g_first());
    tempt += tempa;
    ret[0] = tempt.g_first();
    tempa = spardigs(vplus, 0, tempt.g_second());
    tempt = spardigs(vplus, 0, ret[1]);
    tempt += tempa;
    ret[1] = tempt.g_first();

    for (k = 2; k < ret.lst_digs.size(); ++k) {
      tempt.p_first(ret[k]);
      tempt += aux;
      ret[k] = tempt.g_first();
      ret.aux =
          spardigs(tempt.g_sign(), ((tempt.g_sign() == vplus) ? (0) : (B - 1)),
                   tempt.g_second());
    }

    ret.lst_digs.push_back(ret.aux.g_first());
    ret.lst_digs.push_back(ret.aux.g_second());
    ret.signo = ret.aux.g_sign();
    ret.aux = spardigs();
    return ret;
  }

<<<<<<< HEAD
  int_num operator*(dig a) const {
    int_num &cthis = *this;
    pardigs temp;
    dig carry = 0;
    int_num ret(*this);
=======
  num_int operator*(dig a) const {
    num_int &cthis = *this;
    pardigs temp;
    dig carry = 0;
    num_int ret(*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    if (ret.signo == vminus)
      ret.mC_B();
    for (usint k = 0; k < (cthis.size()); ++k) {
      temp = cthis[k] * a;
      temp += carry;
      ret[k] = temp.g_first();
      carry = temp.g_second();
    }
    if (carry != 0)
      ret.insert((cthis.size()) - 1, 1, carry);
    if (ret.signo == vminus)
      ret.mC_B();
    return ret;
  }

<<<<<<< HEAD
  // int_num operator / (dig) const;
  // int_num operator % (dig) const;
=======
  // num_int operator / (dig) const;
  // num_int operator % (dig) const;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

  /********************************************/
  /*									                            */
  /*   OPERACIONES ARITMETICAS		*/
  /*	     CON ASIGNACION				        */
  /* 									                            */
  /********************************************/

<<<<<<< HEAD
  const int_num &operator+=(const int_num &arg) {
    int_num &cthis = *this;
    this->reduce();
    int_num carg(arg.reduce());
    spardigs tempt;
    spardigs tempa;
    const int_num *po = 0;
=======
  const num_int &operator+=(const num_int &arg) {
    num_int &cthis = *this;
    this->reduce();
    num_int carg(arg.reduce());
    spardigs tempt;
    spardigs tempa;
    const num_int *po = 0;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    usint sza = carg.size();
    usint szt = cthis.size();
    p_usint pszmin = 0;
    p_usint pszmax = 0;
    if (sza <= szt) {
      pszmin = &sza;
      pszmax = &szt;
      po = this;
    } else {
      pszmin = &szt;
      pszmax = &sza;
      po = &carg;
    }
<<<<<<< HEAD
    const int_num &obj = (*po);
=======
    const num_int &obj = (*po);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    tempt.p_decs(dig_t<B>(0));
    tempa.p_decs(0);
    usint &szmin = *pszmin;
    usint &szmax = *pszmax;
    usint k = 0;
    for (; k < szmin; ++k) {
      tempt.p_uds(cthis[k]);
      tempa.p_uds(carg[k]);
      tempt += tempa;
      cthis[k] = tempt.g_uds();
    }
    for (; k < szmax; ++k) {
      tempt.p_first(obj[k]);
      tempt += (obj.aux);
      cthis[k] = tempt.g_first();
    }
    aux.p_first(tempt.g_second());
    aux.p_second(0);
    this->reduce();
    return (*this);
  }

<<<<<<< HEAD
  const int_num &operator-=(const int_num &arg) {
    int_num &cthis = *this;
    this->reduce();
    int_num carg((-arg).reduce());
    spardigs tempt();
    spardigs tempa();
    const int_num *po = 0;
=======
  const num_int &operator-=(const num_int &arg) {
    num_int &cthis = *this;
    this->reduce();
    num_int carg((-arg).reduce());
    spardigs tempt();
    spardigs tempa();
    const num_int *po = 0;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    usint sza = carg.size();
    usint szt = (cthis.size());
    p_usint pszmin = 0;
    p_usint pszmax = 0;
    if (sza <= szt) {
      pszmin = &sza;
      pszmax = &szt;
      po = this;
    } else {
      pszmin = &szt;
      pszmax = &sza;
      po = &carg;
    }
<<<<<<< HEAD
    const int_num &obj = (*po);
=======
    const num_int &obj = (*po);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    tempt.p_second(0);
    tempa.p_second(0);
    usint &szmin = *pszmin;
    usint &szmax = *pszmax;
    usint k = 0;
    for (; k < szmin; ++k) {
      tempt.p_first(cthis[k]);
      tempa.p_first(carg[k]);
      tempt += tempa;
      cthis[k] = tempt.g_first();
    }
    for (; k < szmax; ++k) {
      tempt.p_first(obj.lst_digs[k]);
      tempt += (obj.aux);
      cthis[k] = tempt.g_first();
    }
    aux.p_first(tempt.g_second());
    aux.p_second(0);
    this->reduce();
    return (*this);
  }

<<<<<<< HEAD
  const int_num &operator*=(const int_num &arg) {
    int_num &cthis = *this;
    int_num multtemp;
    const sign_e sgn_ndo = signo;
    this->absp();
    this->reduce();
    int_num &m1 = (*this);
    int_num m2(arg.abs());
=======
  const num_int &operator*=(const num_int &arg) {
    num_int &cthis = *this;
    num_int multtemp;
    const sign_e sgn_ndo = signo;
    this->absp();
    this->reduce();
    num_int &m1 = (*this);
    num_int m2(arg.abs());
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    m2.reduce();

    cthis *= m2[0];
    for (usint j = 1; j < m2.size(); ++j) {
      multtemp = m1 * m2[j];
      multtemp.insert(0, j, 0);
      cthis += multtemp;
    }
    if (sgn_ndo != arg.signo)
      m1.mC_B();
    return (*this);
  }

<<<<<<< HEAD
  const int_num &operator/=(const int_num &arg) {
    int_num &cthis = *this;
    const sign_e sgn_ndo = signo;
    const sign_e sgn_sor = arg.signo;
    this->absp();
    int_num &dvndo_int = *this;
    dvndo_int.reduce();
    int_num rem(dvndo_int);

    int_num dvsor_int(arg.abs());
=======
  const num_int &operator/=(const num_int &arg) {
    num_int &cthis = *this;
    const sign_e sgn_ndo = signo;
    const sign_e sgn_sor = arg.signo;
    this->absp();
    num_int &dvndo_int = *this;
    dvndo_int.reduce();
    num_int rem(dvndo_int);

    num_int dvsor_int(arg.abs());
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    dvsor_int.reduce();

    const usint cssor = dvsor_int.ceros_a_la_drcha(); // ¿?

<<<<<<< HEAD
    int_num dvndo_fra(dvndo_int.substr(0, cssor));
=======
    num_int dvndo_fra(dvndo_int.substr(0, cssor));
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    dvsor_int.lst_digs.erase(0, cssor); // division por una potencia de B

    dvsor_int.reduce();
    dvndo_int.reduce();

    dvndo_fra.reduce();

    const usint longtndo = dvndo_int.size();
    const usint longtndo2 = dvndo_fra.size();
    const usint longtsor = dvsor_int.size();
    const usint longsor = longtsor;

    // hemos dividido por los ceros del divisor (por una potencia de B)
    // tanto divisor como dividendo, obteniendo dvndo_int y dvsor_int como
    // cocientes enteros.
    div_uno(rem, dvndo_int, dvsor_int, longtndo, longsor);
    // ahora hacemos lo mismo con el cociente de las potencias de B del
    // dividendo obteniendo dvndo_fra

    /* *
        RemReal = RemObtenido*B^cssor + Dvndo_fra

        rem = rem.lst_digs.insert(0,cssor,0);
        rem += dvndo_fra;
    * */
    if (sgn_ndo != sgn_sor)
      dvndo_int.mC_B();
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    return dvndo_int;
  }

<<<<<<< HEAD
  const int_num &operator%=(const int_num &arg) {
    int_num &cthis = *this;
    (*this).absp();
    int_num &rem = *this;
    rem.reduce();
    int_num dvndo_int(rem);

    int_num dvsor_int(arg.abs());
=======
  const num_int &operator%=(const num_int &arg) {
    num_int &cthis = *this;
    (*this).absp();
    num_int &rem = *this;
    rem.reduce();
    num_int dvndo_int(rem);

    num_int dvsor_int(arg.abs());
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    dvsor_int.reduce();

    const usint cssor = dvsor_int.ceros_a_la_drcha(); // ¿?

<<<<<<< HEAD
    int_num dvndo_fra(dvndo_int.substr(0, cssor));
=======
    num_int dvndo_fra(dvndo_int.substr(0, cssor));
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    dvsor_int.lst_digs.erase(0, cssor); // division por una potencia de B

    dvsor_int.reduce();
    dvndo_int.reduce();

    dvndo_fra.reduce();

    const usint longtndo = dvndo_int.size();
    const usint longtndo2 = dvndo_fra.size();
    const usint longtsor = dvsor_int.size();
    const usint longsor = longtsor;

    // hemos dividido por los ceros del divisor (por una potencia de B)
    // tanto divisor como dividendo, obteniendo dvndo_int y dvsor_int como
    // cocientes enteros.
    div_uno(rem, dvndo_int, dvsor_int, longtndo, longsor);
    // ahora hacemos lo mismo con el cociente de las potencias de B del
    // dividendo obteniendo dvndo_fra

    /* *
        RemReal = RemObtenido*B^cssor + Dvndo_fra
    * */

    rem = rem.lst_digs.insert(0, cssor, 0);
    rem += dvndo_fra;

    return rem;
  }

<<<<<<< HEAD
  // const int_num & operator += (spardigs);
  // const int_num & operator -= (spardigs);
  // const int_num & operator *= (spardigs);
  // const int_num & operator /= (spardigs);
  // const int_num & operator %= (spardigs);
  // const int_num & operator += (pardigs);
  // const int_num & operator -= (pardigs);

  const int_num &operator*=(pardigs a) {
    int_num &cthis = *this;
    pardigs temp;
    dig carry = 0;
    int_num &ret = (*this);
=======
  // const num_int & operator += (spardigs);
  // const num_int & operator -= (spardigs);
  // const num_int & operator *= (spardigs);
  // const num_int & operator /= (spardigs);
  // const num_int & operator %= (spardigs);
  // const num_int & operator += (pardigs);
  // const num_int & operator -= (pardigs);

  const num_int &operator*=(pardigs a) {
    num_int &cthis = *this;
    pardigs temp;
    dig carry = 0;
    num_int &ret = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    for (usint k = 0; k < cthis.size(); ++k) {
      temp = cthis[k] * (a.g_first());
      temp += carry;
      ret[k] = temp.g_first();
      carry = temp.g_second();
    }
    if (carry != 0)
      ret.insert((cthis.size()) - 1, 1, carry);
    ret.reduce();
    carry = 0;
    for (usint k = 0; k < ((cthis.size()) - 1); ++k) {
      temp = cthis[k] * (a.g_second());
      temp += carry;
      ret.substr(k + 1, ret.size() - 1) += temp.g_first(); // ¿?
      carry = temp.g_second();
    }
    if (carry != 0)
      ret.insert((cthis.size()) - 1, 1, carry);
    ret.reduce();

    if (signo == vminus)
      ret.mC_B();

    return ret;
  }

<<<<<<< HEAD
  // const int_num & operator /= (pardigs);
  // const int_num & operator %= (pardigs);

  const int_num &operator+=(dig arg) {
    int_num &cthis = *this;
=======
  // const num_int & operator /= (pardigs);
  // const num_int & operator %= (pardigs);

  const num_int &operator+=(dig arg) {
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    this->reduce();
    spardigs tempt();

    tempt.p_second(0);
    usint k = 1;
    tempt.p_first(cthis[0]);
    tempt += spardigs(arg);
    cthis[0] = tempt.g_first();
    aux = spardigs(tempt.g_second());
    for (; k < cthis.size(); ++k) {
      tempt.p_first(0);
      tempt += aux;
      cthis[k] = tempt.g_first();
      aux = spardigs(tempt.g_second());
    }
    aux.p_first(tempt.g_second());
    aux.p_second(0);
    this->reduce();
    return (*this);
  }

<<<<<<< HEAD
  const int_num &operator-=(dig arg) {
    int_num &cthis = *this;
=======
  const num_int &operator-=(dig arg) {
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    this->reduce();
    dig arg_CB = (dig(B - 1) - arg) + dig(1);
    spardigs tempt();

    tempt.p_second(0);
    usint k = 1;
    tempt.p_first(cthis[0]);
    tempt += arg_CB;
    cthis[0] = tempt.g_first();
    aux = spardigs(tempt.g_second());
    if (arg == 0)
      aux += dig(B - 1);
    for (; k < cthis.size(); ++k) {
      tempt.p_first(0);
      tempt += aux;
      cthis[k] = tempt.g_first();
      aux = spardigs(tempt.g_second());
    }
    aux.p_first(tempt.g_second());
    aux.p_second(0);
    this->reduce();
    return (*this);
  }

<<<<<<< HEAD
  const int_num &operator*=(dig arg) {
    int_num &cthis = *this;
=======
  const num_int &operator*=(dig arg) {
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    pardigs temp;
    dig carry = 0;
    sign_e sgn = this->signo;
    this->absp();
    this->reduce();
    for (usint k = 0; k < (cthis.size()); ++k) {
      temp = cthis[k] * arg;
      temp += carry;
      cthis[k] = temp.g_first();
      carry = temp.g_second();
    }
    if (carry != 0)
      insert((cthis.size()) - 1, 1, carry);
    if (sgn == vminus)
      this->mC_B();
    return (*this);
  }

<<<<<<< HEAD
  //	const int_num & operator /= (dig);
  //	const int_num & operator %= (dig);
=======
  //	const num_int & operator /= (dig);
  //	const num_int & operator %= (dig);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

  /***************************************/
  /*							                            */
  /*   COMPLEMENTO A BASE Y 	*/
  /* 		BASE MENOS 1		                */
  /*							                            */
  /**************************************/

<<<<<<< HEAD
  int_num operator-() const {
    int_num &cthis = *this;
    int_num cpy(*this);
=======
  num_int operator-() const {
    num_int &cthis = *this;
    num_int cpy(*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    cpy.reduce();
    const striterator fin = cpy.end();
    striterator it = cpy.begin();
    for (; it != fin; ++it)
      (*it) = (!(*it));

    it = cpy.begin();
    cpy.aux = (*it) + 1;
    cpy[0] = cpy.aux.g_first();
    ++it;
    if ((cpy.aux.g_second()) != spardigs()) {
      for (; it != fin; ++it) {
        cpy.aux.p_first(cpy.aux.g_second());
        cpy.aux.p_second(0);
        if (cpy.aux == spardigs())
          break;
        cpy.aux += spardigs(*it);
      }
      cpy.push_back(cpy.aux.g_first());
      cpy.push_back(cpy.aux.g_second());
    }
    cpy.signo = ((cpy.signo == vminus) ? vplus : vminus);
    cpy.aux = spardigs();
    cpy.reduce();
    return cpy;
  }

<<<<<<< HEAD
  int_num operator!() const {
    int_num &cthis = *this;
    int_num cpy(*this);
=======
  num_int operator!() const {
    num_int &cthis = *this;
    num_int cpy(*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const striterator fin = cpy.end();
    striterator it = cpy.begin();
    for (; it != fin; ++it)
      (*it) = (!(*it));
    cpy.signo = ((cpy.signo == vminus) ? vplus : vminus);
    cpy.aux = spardigs();
    cpy.reduce();
    return cpy;
  }

  /************************************/
  /*							                        */
  /*  	 MODIFICADOR		            */
  /* 	COMPLEMENTO A BASE Y 	*/
  /* 		BASE MENOS 1		            */
  /*							                        */
  /***********************************/

<<<<<<< HEAD
  const int_num &mC_B() {
    int_num &cthis = *this;
=======
  const num_int &mC_B() {
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    cthis.reduce();
    const striterator fin = cthis.end();
    striterator it = cthis.begin();
    for (; it != fin; ++it)
      (*it) = (!(*it));
    it = cthis.begin();
    aux = (*it) + 1;
    cthis[0] = aux.g_first();
    ++it;
    if ((aux.g_second()) != spardigs()) {
      for (; it != fin; ++it) {
        aux.p_first(aux.g_second());
        aux.p_second(0);
        if (aux == spardigs())
          break;
        aux += spardigs(*it);
      }
      push_back(aux.g_first());
      push_back(aux.g_second());
    }
    signo = ((signo == vminus) ? vplus : vminus);
    aux = spardigs();
    cthis.reduce();
    return cthis;
  }

<<<<<<< HEAD
  const int_num &mC_Bm1() {
    int_num &cthis = *this;
    int_num &cpy = (*this);
=======
  const num_int &mC_Bm1() {
    num_int &cthis = *this;
    num_int &cpy = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const striterator fin = cpy.end();
    striterator it = cpy.begin();
    for (; it != fin; ++it)
      (*it) = (!(*it));
    cpy.signo = ((cpy.signo == vminus) ? vplus : vminus);
    cpy.aux = spardigs();
    cpy.reduce();
    return cpy;
  }

  /******************************/
  /*							                */
  /*  	   ABSOLUTO		        */
  /*							                */
  /******************************/

<<<<<<< HEAD
  int_num abs() const {
    const int_num cthis(*this);
=======
  num_int abs() const {
    const num_int cthis(*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    cthis.reduce();
    if (signo == vminus)
      cthis.mC_B();
    cthis.reduce();
    return cthis;
  }

<<<<<<< HEAD
  const int_num &absp() {
    int_num &cthis = (*this);
=======
  const num_int &absp() {
    num_int &cthis = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    cthis.reduce();
    if (signo == vminus)
      cthis.mC_B();
    cthis.reduce();
    return cthis;
  }

  /***********************************/
  /*							                        */
  /*  DIVIDIR ENTRE BASE O 2	*/
  /*							                        */
  /***********************************/

<<<<<<< HEAD
  int_num divB() const {
    int_num cpy(*this);
=======
  num_int divB() const {
    num_int cpy(*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    cpy.reduce();
    sign_e sgn = cpy.signo;
    cpy.absp();
    cpy.cthis.erase(0, 1);
    if (sgn == vminus)
      cpy.mC_B();
    cpy.reduce();
    return cpy;
  }

  dig remB() const {
<<<<<<< HEAD
    int_num cpy(*this);
=======
    num_int cpy(*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    cpy.reduce();
    if (signo == vminus)
      return cpy.absp();
    return cpy.lst_digs[0];
  }

<<<<<<< HEAD
  const int_num &divBp() {
    int_num &cpy = (*this);
=======
  const num_int &divBp() {
    num_int &cpy = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    cpy.reduce();
    sign_e sgn = cpy.signo;
    cpy.absp();
    cpy.cthis.erase(0, 1);
    if (sgn == vminus)
      cpy.mC_B();
    cpy.reduce();
    return cpy;
  }

  dig remBp() {
<<<<<<< HEAD
    int_num &cpy = (*this);
=======
    num_int &cpy = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    cpy.reduce();
    if (signo == vminus)
      return cpy.absp();
    return cpy.lst_digs[0];
  }

<<<<<<< HEAD
  int_num div2() const {
    int_num &cthis = *this;
    const sign_e sgn = signo;
    int_num dvndo_int(cthis.abs());
    dvndo_int.reduce();
    int_num rem(dvndo_int);
    const dig dos = 2;

    int_num dvsor_int(dos);

    const usint cssor = ((B == 2) ? (1) : (0));

    int_num dvndo_fra(dvndo_int.substr(0, cssor));
=======
  num_int div2() const {
    num_int &cthis = *this;
    const sign_e sgn = signo;
    num_int dvndo_int(cthis.abs());
    dvndo_int.reduce();
    num_int rem(dvndo_int);
    const dig dos = 2;

    num_int dvsor_int(dos);

    const usint cssor = ((B == 2) ? (1) : (0));

    num_int dvndo_fra(dvndo_int.substr(0, cssor));
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    if (B == 2)
      dvsor_int[0] = 1; // division por una potencia de B

    dvndo_int.reduce();
    dvndo_fra.reduce();

    const usint longtndo = dvndo_int.size();
    const usint longtndo2 = dvndo_fra.size();
    const usint longtsor = 1;
    const usint longsor = 0;

    // hemos dividido por los ceros del divisor (por una potencia de B)
    // tanto divisor como dividendo, obteniendo dvndo_int y dvsor_int como
    // cocientes enteros.
    div_uno(rem, dvndo_int, dvsor_int, longtndo, longsor);
    // ahora hacemos lo mismo con el cociente de las potencias de B del
    // dividendo obteniendo dvndo_fra

    /* *
        RemReal = RemObtenido*B^cssor + Dvndo_fra

        rem = rem.cthis.insert(0,cssor,0);
        rem += dvndo_fra;
    * */
    if (sgn == vminus)
      dvndo_int.mC_B();
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    return dvndo_int;
  }

  dig rem2() const {
<<<<<<< HEAD
    int_num &cthis = *this;
    sign_e sgn = signo;
    int_num cpy = cthis.reduce();
=======
    num_int &cthis = *this;
    sign_e sgn = signo;
    num_int cpy = cthis.reduce();
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    cpy.absp();
    cpy.reduce();
    if (B % 2 == 1) {
      if (cpy.lst_digs.size() == 1)
        return dig::Rem2(cpy.lst_digs[0]);
      else {
        usint paridad = 0;
        for (usint k = 0; k < cpy.lst_digs.size(); ++k)
          paridad += dig::Dig2UInt(dig::Rem2(cpy.lst_digs[k]));
        paridad %= 2;
        return dig(paridad);
      }
    } else {
      return dig::Rem2(cpy.lst_digs[0]);
    }
  }

<<<<<<< HEAD
  const int_num &div2p() {
    int_num &cthis = *this;
    sign_e sgn = signo;
    cthis.absp();
    cthis.reduce();
    int_num &dvndo_int = (*this);
    int_num rem(dvndo_int);
    const dig dos = 2;

    int_num dvsor_int(dos);

    const usint cssor = ((B == 2) ? (1) : (0));

    int_num dvndo_fra(dvndo_int.substr(0, cssor));
=======
  const num_int &div2p() {
    num_int &cthis = *this;
    sign_e sgn = signo;
    cthis.absp();
    cthis.reduce();
    num_int &dvndo_int = (*this);
    num_int rem(dvndo_int);
    const dig dos = 2;

    num_int dvsor_int(dos);

    const usint cssor = ((B == 2) ? (1) : (0));

    num_int dvndo_fra(dvndo_int.substr(0, cssor));
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    if (B == 2)
      dvsor_int[0] = 1; // division por una potencia de B

    dvndo_int.reduce();
    dvndo_fra.reduce();

    const usint longtndo = dvndo_int.size();
    const usint longtndo2 = dvndo_fra.size();
    const usint longtsor = 1;
    const usint longsor = 0;

    // hemos dividido por los ceros del divisor (por una potencia de B)
    // tanto divisor como dividendo, obteniendo dvndo_int y dvsor_int como
    // cocientes enteros.
    div_uno(rem, dvndo_int, dvsor_int, longtndo, longsor);
    // ahora hacemos lo mismo con el cociente de las potencias de B del
    // dividendo obteniendo dvndo_fra

    /* *
        RemReal = RemObtenido*B^cssor + Dvndo_fra

        rem = rem.lst_digs.insert(0,cssor,0);
        rem += dvndo_fra;
    * */
    if (sgn == vminus)
      dvndo_int.mC_B();
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    return dvndo_int;
  }

  dig rem2p() {
<<<<<<< HEAD
    int_num &cthis = *this;
    sign_e sgn = signo;
    cthis.absp();
    cthis.reduce();
    int_num &cpy = (*this);
=======
    num_int &cthis = *this;
    sign_e sgn = signo;
    cthis.absp();
    cthis.reduce();
    num_int &cpy = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    if (B % 2 == 1) {
      if (cpy.size() == 1)
        return dig::Rem2(cpy.lst_digs[0]);
      else {
        usint paridad = 0;
        for (usint k = 0; k < cpy.size(); ++k)
          paridad += dig::Dig2UInt(dig::Rem2(cpy[k]));
        paridad %= 2;
        return dig(paridad);
      }
    } else {
      return dig::Rem2(cpy[0]);
    }
  }

<<<<<<< HEAD
  /*		int_num div3() const;
                  const int_num & div3p();
                  dig rem3() const;
                  const int_num & rem3p();
                  const dig rem4() const;
                  dig rem5() const;
                  dig rem6() const;
                  int_num div7 () const;
                  dig rem7 () const;
                  const int_num & div7p();
=======
  /*		num_int div3() const;
                  const num_int & div3p();
                  dig rem3() const;
                  const num_int & rem3p();
                  const dig rem4() const;
                  dig rem5() const;
                  dig rem6() const;
                  num_int div7 () const;
                  dig rem7 () const;
                  const num_int & div7p();
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
                  dig rem7p();
                  const dig rem8() const;
  */

  dig remBm1() const {
<<<<<<< HEAD
    int_num cthis(*this), suma;
=======
    num_int cthis(*this), suma;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    sign_e sgn = signo;
    cthis.abs();
    cthis.reduce();
    suma.reduce();
    suma.lst_digs.insert(0, 1, 0);
    suma.lst_digs.erase(0, (cthis.size()) - 1);
    do {
      for (usint i = 0; i < cthis.size(); ++i) {
        suma += cthis[i];
        suma.reduce();
      }
    } while (suma.size() > 1);

    if ((suma[0] == 0) || (suma[0] == (B - 1)))
      return 0;
    else
      return suma[0];
  }

  // dig	 			remBm1p()		;
<<<<<<< HEAD
  // int_num	 		divBm1() 	const;
  // const int_num	& 	divBm1p()		;
=======
  // num_int	 		divBm1() 	const;
  // const num_int	& 	divBm1p()		;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
private:
  //		inline void	div3_step(pair< n2digs_t , usint > & S) const;
  //		inline void div3p_step(pair< n2digs_t , usint > & S);
  //		inline void	div7_step(pair< n2digs_t , usint > & S) const;
  //		inline void div7p_step(pair< n2digs_t , usint > & S);

  /******************************/
  /*							                */
  /* 	  Division Generica		    */
  /*							                */
  /******************************/

<<<<<<< HEAD
  inline void div_gen_step(const int_num &dvsor, int_num &rem, int_num &coc,
                           usint &ndig) const {
    int_num &cthis = *this;
    const usint maxpos = (cthis.size()) - 1;
    const int_num &dvndo = (*this);
=======
  inline void div_gen_step(const num_int &dvsor, num_int &rem, num_int &coc,
                           usint &ndig) const {
    num_int &cthis = *this;
    const usint maxpos = (cthis.size()) - 1;
    const num_int &dvndo = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    rem.insert(0, 1, dvndo[maxpos - ndig]);
    if (rem < coc) {
      coc.insert(0, 1, 0);
    } else if (rem == coc) {
      coc.insert(0, 1, 1);
      rem.erase(0, rem.size() - 1);
      rem[0] = 0;
    } else {
      if (rem.size() > dvsor.size()) {
        pardigs dighrem = pardigs(rem[rem.size() - 1], rem[rem.size() - 2]);
        pardigs dighsor = pardigs(0, dvsor[dvsor.size() - 1]);
        pardigs &digcocprueba = dighrem;
        digcocprueba /= dighsor;
<<<<<<< HEAD
        int_num remprueba = dvsor * digcocprueba;
=======
        num_int remprueba = dvsor * digcocprueba;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
        for (dig_t<B> ix = 0; ix < pardigs(1, 0); ix += 1) {
          if (remprueba > rem) {
            --digcocprueba;
            remprueba -= dvsor;
          } else {
            rem -= remprueba;
            coc.insert(0, 1, digcocprueba);
            break;
          }
        }
      } else {
        dig_t<B> dighrem = rem[rem.size() - 1];
        dig_t<B> dighsor = dvsor[dvsor.size() - 1];
        dig_t<B> &digcocprueba = dighrem;
        digcocprueba /= dighsor;
<<<<<<< HEAD
        int_num remprueba =
=======
        num_int remprueba =
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
            dvsor * digcocprueba; // no está implementada esta función
        dig_t<B> ix = 0;
        for (; ix < pardigs(1, 0); ix += 1) {
          if (remprueba > rem) {
            --digcocprueba;
            remprueba -= dvsor;
          } else {
            rem -= remprueba;
            coc.insert(0, 1, digcocprueba);
            break;
          }
        }
      }
    }
    ++ndig;
    return;
  }

<<<<<<< HEAD
  inline void divp_gen_step(const int_num &dvsor, int_num &rem, int_num &coc,
                            usint &ndig) {
    int_num &cthis = *this;
    const usint maxpos = (cthis.size()) - 1;
    int_num &dvndo = (*this);
=======
  inline void divp_gen_step(const num_int &dvsor, num_int &rem, num_int &coc,
                            usint &ndig) {
    num_int &cthis = *this;
    const usint maxpos = (cthis.size()) - 1;
    num_int &dvndo = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    rem.insert(0, 1, dvndo[maxpos - ndig]);
    if (rem < coc) {
      coc.insert(0, 1, 0);
    } else if (rem == coc) {
      coc.insert(0, 1, 1);
      rem.erase(0, rem.size() - 1);
      rem[0] = 0;
    } else {
      if (rem.size() > dvsor.size()) {
        pardigs dighrem = pardigs(rem[rem.size() - 1], rem[rem.size() - 2]);
        const pardigs dighsor = pardigs(0, dvsor[dvsor.size() - 1]);
        pardigs &digcocprueba = dighrem;
        digcocprueba /= dighsor;
<<<<<<< HEAD
        int_num remprueba = dvsor * digcocprueba;
=======
        num_int remprueba = dvsor * digcocprueba;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
        for (dig_t<B> Id = 0; Id < pardigs(1, 0); Id += 1) {
          if (remprueba > rem) {
            --digcocprueba;
            remprueba -= dvsor;
          } else {
            rem -= remprueba;
            coc.insert(0, 1, digcocprueba);
            break;
          }
        }
      } else {
        dig_t<B> dighrem = rem[rem.size() - 1];
        const dig_t<B> dighsor = dvsor[dvsor.size() - 1];
        dig_t<B> &digcocprueba = dighrem;
        digcocprueba /= dighsor;
<<<<<<< HEAD
        int_num remprueba = dvsor * digcocprueba;
=======
        num_int remprueba = dvsor * digcocprueba;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
        for (dig_t<B> Id = 0; Id < pardigs(1, 0); Id += 1) {
          if (remprueba > rem) {
            --digcocprueba;
            remprueba -= dvsor;
          } else {
            rem -= remprueba;
            coc.insert(0, 1, digcocprueba);
            break;
          }
        }
      }
    }
    ++ndig;
    return;
  }

  /******************************/
  /*							                */
  /* 	  Division entre Uno	        */
  /*							                */
  /******************************/

<<<<<<< HEAD
  inline void div_uno(int_num &rem, int_num &dvndo, int_num &dvsor,
                      const usint long_dvndo, const usint long_dvsor) const {
    int_num &cthis = *this;
=======
  inline void div_uno(num_int &rem, num_int &dvndo, num_int &dvsor,
                      const usint long_dvndo, const usint long_dvsor) const {
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    rem = dvndo;
    if ((long_dvsor == 0) ||
        ((long_dvsor == 1) && (dvsor[0] = 0))) { // caso de division por 0
      return;
    } else if ((long_dvndo == 0) ||
               (long_dvndo < long_dvsor)) { // caso de 0 dividido por !=0 ó caso
                                            // de cociente 0
      rem = dvndo;
      dvndo.erase(0, (cthis.size()) - 1);
      dvndo[0] = 0;
      return;
      // rem=dvndo; hecho por defecto
    } else if (dvndo == dvsor) { // caso de dividir por si mismo
      dvndo.erase(0, (cthis.size()) - 1);
      dvndo[0] = 1;
      rem.erase(0, rem.size() - 1);
      rem[0] = 0;
      return;
    } else if ((long_dvsor == 1) &&
               (dvsor[0] == 1)) { // caso de dividir por potencias de B
      // dvndo;
      rem.erase(0, rem.size() - 1);
      rem[0] = 0;
    }
    /*		else if
       ((long_dvsor==1)&&((dvsor[0]==2)||(dvsor[0]==4)||(dvsor[0]==8))) {
                // caso de dividir por potencias de B multiplicadas por 2, 4 u 8
                        //dvndo;
                        switch(dvsor[0]) {
<<<<<<< HEAD
                                case 2  : rem=int_num(rem.rem2()); break;
                                case 4  : rem=int_num(rem.rem4()); break;
                                case 8  :
                                default : rem=int_num(rem.rem8());
=======
                                case 2  : rem=num_int(rem.rem2()); break;
                                case 4  : rem=num_int(rem.rem4()); break;
                                case 8  :
                                default : rem=num_int(rem.rem8());
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
                        }
                        dvndo.div2p();
                        switch(dvsor[0]) {
                                case 4:  dvndo.div2p(); break;
                                case 8:  dvndo.div2p(); dvndo.div2p();
                        }

                }
                else if ((long_dvsor==1)&&((dvsor[0]==3)||(dvsor[0]==9))) {
                // caso de dividir por potencias de B multiplicadas por 3 u 9
                        //dvndo;
                        switch(dvsor[0]) {
<<<<<<< HEAD
                                case 3  : rem=int_num(rem.rem3()); break;
                                case B-1  :
                                default : rem=int_num(rem.rem9()); break;
=======
                                case 3  : rem=num_int(rem.rem3()); break;
                                case B-1  :
                                default : rem=num_int(rem.rem9()); break;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
                        }
                        dvndo.div3p();
                        if(dvsor[0]==n) dvndo.div3p();
                }
                else if ((long_dvsor==1)&&(dvsor[0]==6)) {
                // caso de dividir por potencias de B multiplicadas por 6
                        //dvndo;
                        rem.rem6();
                        dvndo.div2p();
                        dvndo.div3p();
                }
                else if ((long_dvsor==1)&&(dvsor[0]==5)) {
                // caso de dividir por potencias de B multiplicadas por 5
                        rem.rem5();
                        if (long_dvndo > 1) {
                                dvndolst_digs.erase(0,1);
                                // Divido por B
                                dvndo *= d;
                                // y he multiplicado por 2 (*2/B ó *1/5)
                        }
                        else {
                                //dvndo;
                                //dvndolst_digs.erase(0,(cthis.size())-1);
                                switch (dvndo[0]) {
                                        case 0 :
                                        case 1 :
                                        case 2 :
                                        case 3 :
                                        case 4 :  dvndo[0] = 0; break;
                                        default : dvndo[0] = 1;
                                }
                        }
                }
                else if ((long_dvsor==1)&&(dvsor[0]==7)) {
                // caso de dividir por potencias de B multiplicadas por 7
                        //dvndo;
                        rem.rem7();
                        dvndo.div7();
                }*/
    else if ((long_dvndo == long_dvsor) && (dvndo < dvsor)) {
      rem = dvndo;
      dvndo.erase(0, (cthis.size()) - 1);
      dvndo[0] = 0;
    } else {
      // algoritmo de resta general
      // implementar div_step pasamos (resto,cociente,i,dividendo,divisor)
      // devuelve (resto,cociente,i,dividendo,divisor) se puede hacer con una
      // tupla
      // dvndo;
<<<<<<< HEAD
      int_num rem =
          (dvndo = dvndo.substr((cthis.size()) - 1 - long_dvsor, long_dvsor));
      int_num coc(0);
=======
      num_int rem =
          (dvndo = dvndo.substr((cthis.size()) - 1 - long_dvsor, long_dvsor));
      num_int coc(0);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
      usint ndig = 0;
      do {
        div_gen_step(dvsor, rem, coc, ndig);
      } while (rem >= dvsor);
      dvndo = coc;
      return;
    }
  }
  // END PRIVATE

  /****************************/
  /*							            */
  /* 	  Division Euclidea		*/
  /*							            */
  /****************************/

public:
<<<<<<< HEAD
  pair<int_num, int_num> EuclidDiv(const int_num &arg) const {
    int_num &cthis = *this;
    const sign_e sgn_ndo = signo;
    const sign_e sgn_sor = arg.signo;
    int_num dvndo_int = cthis;
    dvndo_int.absp();
    dvndo_int.reduce();
    int_num dvsor_int = arg.abs();
    dvsor_int.reduce();

    int_num rem(dvndo_int);

    const usint cssor = dvsor_int.ceros_a_la_drcha(); // ¿?

    int_num dvndo_fra(dvndo_int.substr(0, cssor));
=======
  pair<num_int, num_int> EuclidDiv(const num_int &arg) const {
    num_int &cthis = *this;
    const sign_e sgn_ndo = signo;
    const sign_e sgn_sor = arg.signo;
    num_int dvndo_int = cthis;
    dvndo_int.absp();
    dvndo_int.reduce();
    num_int dvsor_int = arg.abs();
    dvsor_int.reduce();

    num_int rem(dvndo_int);

    const usint cssor = dvsor_int.ceros_a_la_drcha(); // ¿?

    num_int dvndo_fra(dvndo_int.substr(0, cssor));
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    dvsor_int.erase(0, cssor); // division por una potencia de B

    dvsor_int.reduce();
    dvndo_int.reduce();

    dvndo_fra.reduce();

    const usint longtndo = dvndo_int.size();
    const usint longtndo2 = dvndo_fra.size();
    const usint longtsor = dvsor_int.size();
    const usint longsor = longtsor;

    // hemos dividido por los ceros del divisor (por una potencia de B)
    // tanto divisor como dividendo, obteniendo dvndo_int y dvsor_int como
    // cocientes enteros.
    div_uno(rem, dvndo_int, dvsor_int, longtndo, longsor);
    // ahora hacemos lo mismo con el cociente de las potencias de B del
    // dividendo obteniendo dvndo_fra

    /* *
        RemReal = RemObtenido*B^cssor + Dvndo_fra
     * */
    rem = rem.insert(0, cssor, 0);
    rem += dvndo_fra;

    if (sgn_ndo != sgn_sor)
      dvndo_int.mC_B();
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    return make_pair(rem, dvndo_int);
  }

<<<<<<< HEAD
  pair<int_num, const int_num &> EuclidDivP(const int_num &arg) {
    int_num &cthis = *this;
=======
  pair<num_int, const num_int &> EuclidDivP(const num_int &arg) {
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const sign_e sgn_ndo = signo;
    const sign_e sgn_sor = arg.signo;
    cthis.absp();
    cthis.reduce();
<<<<<<< HEAD
    int_num &dvndo_int = cthis;
    int_num dvsor_int = arg.abs();
    dvsor_int.reduce();

    int_num rem(dvndo_int);

    const usint cssor = dvsor_int.ceros_a_la_drcha(); // ¿?

    int_num dvndo_fra(dvndo_int.substr(0, cssor));
=======
    num_int &dvndo_int = cthis;
    num_int dvsor_int = arg.abs();
    dvsor_int.reduce();

    num_int rem(dvndo_int);

    const usint cssor = dvsor_int.ceros_a_la_drcha(); // ¿?

    num_int dvndo_fra(dvndo_int.substr(0, cssor));
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    dvsor_int.erase(0, cssor); // division por una potencia de B

    dvsor_int.reduce();
    dvndo_int.reduce();

    dvndo_fra.reduce();

    const usint longtndo = dvndo_int.size();
    const usint longtndo2 = dvndo_fra.size();
    const usint longtsor = dvsor_int.size();
    const usint longsor = longtsor;

    // hemos dividido por los ceros del divisor (por una potencia de B)
    // tanto divisor como dividendo, obteniendo dvndo_int y dvsor_int como
    // cocientes enteros.
    div_uno(rem, dvndo_int, dvsor_int, longtndo, longsor);
    // ahora hacemos lo mismo con el cociente de las potencias de B del
    // dividendo obteniendo dvndo_fra

    /* *
        RemReal = RemObtenido*B^cssor + Dvndo_fra
     * */
    rem = rem.insert(0, cssor, 0);
    rem += dvndo_fra;

    if (sgn_ndo != sgn_sor)
      dvndo_int.mC_B();
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    return make_pair(rem, dvndo_int);
  }

  /************************************/
  /*									                */
  /* 		     PRE Y POST				    */
  /*									                */
  /************************************/

public:
  /*
  const Counter& Counter::operator++()
  {
          ++itsVal;
          return *this;
  }

  const Counter Counter::operator++(int)
  {
          Counter temp(*this);
          ++itsVal;
          return temp;
  }
  */
<<<<<<< HEAD
  const int_num &operator++() {
    int_num &cthis = *this;
=======
  const num_int &operator++() {
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const size_t long_inic = cthis.size();
    if (long_inic > 1) {
      cthis.reduce();
    }
<<<<<<< HEAD
    if (cthis == int_num(vminus, dig(B - 1), dig(B - 1))) {
=======
    if (cthis == num_int(vminus, dig(B - 1), dig(B - 1))) {
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
      cthis.clear();
      cthis.resize(1);
      cthis[0] = dig(0);
      signo = vplus;
      cthis.reduce();
      return cthis;
    }
    bool es_negativo = (signo == vminus);
    signo = vplus;
    aux = spardigs(vplus, 0, 1);
    aux += spardigs(vplus, 0, cthis[0]);
    cthis[0] = aux.g_uds();
    aux.p_uds(aux.g_decs());
    aux.p_decs(0);
    bool seguir = (aux.g_uds() != dig(0));
    ullint i = 1;
    while (seguir and (i < long_inic)) {
      aux += spardigs(vplus, 0, cthis[i]);
      cthis[i] = (aux.g_uds());
      aux.p_uds(aux.g_decs());
      seguir = (aux.g_uds() != dig(0));
      aux.p_decs(0);
      ++i;
    }
    if (seguir and (i >= long_inic)) {
      cthis.resize(long_inic + 1);
      cthis[i] = aux.g_uds();
    }
    ((seguir) and (es_negativo) ? (signo = vplus) : (signo = vminus)); //
    signo = (es_negativo ? vminus : vplus);
    cthis.reduce();
    return cthis;
  }

<<<<<<< HEAD
  const int_num operator++(int) {
    int_num cpThis(*this);
    int_num &cthis = (*this);
    const size_t long_inic = cthis.size();
    if (cthis == int_num(vminus, dig(B - 1), dig(B - 1))) {
=======
  const num_int operator++(int) {
    num_int cpThis(*this);
    num_int &cthis = (*this);
    const size_t long_inic = cthis.size();
    if (cthis == num_int(vminus, dig(B - 1), dig(B - 1))) {
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
      cthis.clear();
      cthis.resize(1);
      cthis[0] = dig(0);
      signo = vplus;
      cthis.reduce();
      return cpThis;
    }
    bool es_negativo = (signo == vminus);
    signo = vplus;
    aux = spardigs(vplus, 0, 1);
    aux += spardigs(vplus, 0, cthis[0]);
    cthis[0] = aux.g_uds();
    aux.p_uds(aux.g_decs());
    aux.p_decs(0);
    bool seguir = (aux.g_uds() != dig(0));
    ullint i = 1;
    while (seguir and (i < long_inic)) {
      aux += spardigs(vplus, 0, cthis[i]);
      cthis[i] = (aux.g_uds());
      aux.p_uds(aux.g_decs());
      seguir = (aux.g_uds() != dig(0));
      aux.p_decs(0);
      ++i;
    }
    if (seguir and (i >= long_inic)) {
      cthis.resize(long_inic + 1);
      cthis[i] = aux.g_uds();
    }
    ((seguir) and (es_negativo) ? (signo = vplus) : (signo = vminus)); //
    signo = (es_negativo ? vminus : vplus);
    cthis.reduce();
    return cpThis;
  }

<<<<<<< HEAD
  const int_num &operator--() {
    int_num &cthis = *this;
    const size_t long_inic = cthis.size();
    // BEGIN TRATAMIENTO DEL 0
    if (cthis == int_num(vplus, dig(0), dig(0))) {
=======
  const num_int &operator--() {
    num_int &cthis = *this;
    const size_t long_inic = cthis.size();
    // BEGIN TRATAMIENTO DEL 0
    if (cthis == num_int(vplus, dig(0), dig(0))) {
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
      cthis.clear();
      cthis.resize(1);
      cthis[0] = dig(B - 1);
      signo = vminus;
      return cthis;
    }
    bool es_negativo = (signo == vminus);
    // END TRATAMIENTO DEL 0
    // BEGIN TRATAMIENTO DE POTENCIA DE B NEGATIVAS
    bool es_pot_de_B_neg = false;
    if (es_negativo) {
      es_pot_de_B_neg = true;
      for (slint i = 0; (i < long_inic) and es_pot_de_B_neg; ++i) {
        es_pot_de_B_neg = es_pot_de_B_neg and (cthis[i] == dig(0));
      }
    } // Hemos calculado si es potencia de 10 negativa
    if (es_pot_de_B_neg) {
      cthis.resize(long_inic + 1);
      for (slint i = 0; i < long_inic; ++i)
        cthis[i] = dig(B - 1);
      cthis[long_inic] = dig(B - 2);
      signo = vminus;
      return cthis;
    } // Vemos que -000 pasa a -8999
    // END TRATAMIENTO DE POTENCIA DE B NEGATIVAS
    signo = vplus;
    aux = spardigs(vminus, dig(B - 1), dig(B - 1));
    aux += spardigs(vplus, 0, cthis[0]);
    cthis[0] = aux.g_uds();
    aux.p_uds(aux.g_decs());
    aux.p_decs(B - 1);
    bool seguir = (aux.g_uds() != dig(0));
    ullint i = 1;
    while (seguir and (i < long_inic)) {
      aux += spardigs(vplus, 0, cthis[i]);
      cthis[i] = (aux.g_uds());
      aux.p_uds(aux.g_decs());
      seguir = (aux.g_uds() != dig(0));
      aux.p_decs(B - 1);
      ++i;
    }
    if (seguir and (i >= long_inic)) {
      cthis.resize(long_inic + 1);
      cthis[i] = aux.g_uds();
    }
    signo = (es_negativo ? vminus : vplus);
    cthis.reduce();
    return cthis;
  }

<<<<<<< HEAD
  const int_num operator--(int) {
    int_num &cthis = (*this);
    const int_num cpThis(*this);
    const size_t long_inic = cthis.size();
    // BEGIN TRATAMIENTO DEL 0
    if (cthis == int_num(vplus, dig(0), dig(0))) {
=======
  const num_int operator--(int) {
    num_int &cthis = (*this);
    const num_int cpThis(*this);
    const size_t long_inic = cthis.size();
    // BEGIN TRATAMIENTO DEL 0
    if (cthis == num_int(vplus, dig(0), dig(0))) {
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
      cthis.clear();
      cthis.resize(1);
      cthis[0] = dig(B - 1);
      signo = vminus;
      return cpThis;
    }
    bool es_negativo = (signo == vminus);
    // END TRATAMIENTO DEL 0
    // BEGIN TRATAMIENTO DE POTENCIA DE B NEGATIVAS
    bool es_pot_de_B_neg = false;
    if (es_negativo) {
      es_pot_de_B_neg = true;
      for (slint i = 0; (i < long_inic) and es_pot_de_B_neg; ++i) {
        es_pot_de_B_neg = es_pot_de_B_neg and (cthis[i] == dig(0));
      }
    } // Hemos calculado si es potencia de 10 negativa
    if (es_pot_de_B_neg) {
      cthis.resize(long_inic + 1);
      for (slint i = 0; i < long_inic; ++i)
        cthis[i] = dig(B - 1);
      cthis[long_inic] = dig(B - 2);
      signo = vminus;
      return cpThis;
    } // Vemos que -000 pasa a -8999
    // END TRATAMIENTO DE POTENCIA DE B NEGATIVAS
    signo = vplus;
    aux = spardigs(vminus, dig(B - 1), dig(B - 1));
    aux += spardigs(vplus, 0, cthis[0]);
    cthis[0] = aux.g_uds();
    aux.p_uds(aux.g_decs());
    aux.p_decs(B - 1);
    bool seguir = (aux.g_uds() != dig(0));
    ullint i = 1;
    while (seguir and (i < long_inic)) {
      aux += spardigs(vplus, 0, cthis[i]);
      cthis[i] = (aux.g_uds());
      aux.p_uds(aux.g_decs());
      seguir = (aux.g_uds() != dig(0));
      aux.p_decs(B - 1);
      ++i;
    }
    if (seguir and (i >= long_inic)) {
      cthis.resize(long_inic + 1);
      cthis[i] = aux.g_uds();
    }
    signo = (es_negativo ? vminus : vplus);
    cthis.reduce();
    return cpThis;
  }

  /******************************/
  /*							                */
  /*  	   REDUCE                  */
  /*					                        */
  /******************************/

<<<<<<< HEAD
  const int_num &reduce() {
    int_num &cthis = *this;
=======
  const num_int &reduce() {
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const usint nsz = cthis.digs_no_significativos();
    const usint longitud = cthis.size();
    if ((longitud == 1) or (longitud == 0))
      return cthis;
    const usint pos_p1 = longitud - nsz;
    return cthis.erase(pos_p1, nsz);
  }

<<<<<<< HEAD
  int_num reduce() const {
    const int_num &cthis = *this;
    int_num cpyreducida(cthis);
=======
  num_int reduce() const {
    const num_int &cthis = *this;
    num_int cpyreducida(cthis);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const usint nsz = cpyreducida.digs_no_significativos();
    const usint longitud = cpyreducida.size();
    const usint pos = longitud - nsz;
    return cpyreducida.erase(pos, nsz);
  }

<<<<<<< HEAD
  const int_num &reduce_fracc() {
    int_num &cthis = *this;
=======
  const num_int &reduce_fracc() {
    num_int &cthis = *this;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const usint nsz = cthis.digs_fracc_no_significativos() - 1;
    const usint pos = 0;
    cthis.erase(pos, nsz);
    return cthis;
  }

<<<<<<< HEAD
  int_num reduce_fracc() const {
    int_num &cthis = *this;
    int_num cpyreducida(cthis);
=======
  num_int reduce_fracc() const {
    num_int &cthis = *this;
    num_int cpyreducida(cthis);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const usint nsz = cpyreducida.digs_no_significativos() - 1;
    const usint pos = 0;
    cpyreducida.erase(pos, nsz);
    return cpyreducida;
  }

  /*********************************/
<<<<<<< HEAD
  /*							   */
  /* 	   ISTREAM Y OSTREAM	   */
  /*							   */
  /*********************************/

  template <const uchint Base>
  friend istream &operator>>(istream &is, int_num<Base> &arg) {
=======
  /*							                    */
  /* 	   ISTREAM Y OSTREAM	*/
  /*							                    */
  /*********************************/

  template <const uchint Base>
  friend istream &operator>>(istream &is, num_int<Base> &arg) {
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    enum estado_e { e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11 };
    vector<string> num(255);
    string num_sgn;
    string num_base;
    estado_e est_act = e0;
    uchint i = 0;
    char c;
    do {
      is >> c;
      switch (est_act) {
      case e0:
        if (c == 'i')
          est_act = e1;
        break;
      case e1:
        if (c == 'n')
          est_act = e2;
        else
          est_act = e0;
        break;
      case e2:
        if (c == 't')
          est_act = e3;
        else
          est_act = e0;
        break;
      case e3:
        if (c == '#')
          est_act = e4;
        else
          est_act = e0;
        break;
      case e4:
        if ((c == '1') || (c == '0') || (c == '-') || (c == '+')) {
          est_act = e5;
          num_sgn.push_back(c - '0');
        } else
          est_act = e0;
        break;
      case e5:
        if (c == ':')
          est_act = e6;
        else
          est_act = e0;
        break;
      case e6:
        if (c == ':')
          est_act = e7;
        else
          est_act = e0;
        break;
      case e7:
        if ((c <= '9') and (c >= '0')) {
          num[i].push_back(c - '0');
        } else if (c == ':') {
          ++i;
          est_act = e6;
        } else if (c == '#')
          est_act = e8;
        else
          est_act = e0;
        break;
      case e8:
        if (c == 'B')
          est_act = e9;
        else
          est_act = e0;
        break;
      case e9:
        if ((c <= '9') and (c >= '0')) {
          est_act = e10;
          num_base.push_back(c - '0');
        } else
          est_act = e0;
        break;
      case e10:
        if ((c <= '9') and (c >= '0')) {
          num_base.push_back(c - '0');
        } else
          est_act = e11;
        break;
      case e11:
        break;
      default:
        est_act = e0;
      }
      uint numero_base_recogido = 0;
      if (est_act == e11) {
        for (uint k = num_base.size(); k > 0; --k) {
          numero_base_recogido *= 10;
          numero_base_recogido += num_base[k];
        }
        numero_base_recogido *= 10;
        numero_base_recogido += num_base[0];
        if (numero_base_recogido != Base)
          est_act = e0;
      }
    } while ((est_act != e11) and (c != '\n'));
    basic_string<dig_t<Base>> digito;
    digito.resize(i + 1);
    for (uchint j = 0; j < 256; ++j) {
      digito[j] = 0;
      for (uint k = num[j].size(); k > 0; --k) {
        digito[j] *= 10;
        digito[j] += (num[j][k] - '0');
      }
      digito[j] *= 10;
      digito[j] += (num[j][0] - '0');
    }
    sign_e sgn;
    if ((num_sgn[0] == '1') || (num_sgn[0] == '-'))
      sgn = vminus;
    else
      sgn = vplus;
    arg.signo = sgn;
    arg.lst_digs = digito;
    arg.aux = spardigs_t<Base>();
    return is;
  }

  template <const uchint Base>
<<<<<<< HEAD
  friend ostream &operator<<(ostream &os, int_num<Base> arg) {
=======
  friend ostream &operator<<(ostream &os, num_int<Base> arg) {
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    const uchint sz = arg.size();
    os << "int#" << ((arg.signo == vplus) ? ('+') : ('-'));
    for (int k = sz - 1; k > -1; --k) {
      os << "::" << static_cast<usint>(arg[k]());
    }
    os << "#B" << static_cast<usint>(Base);
    return os;
  }
};

#endif // INT_NUM_T__HPP__INCLUDED
