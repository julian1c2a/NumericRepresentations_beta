#ifndef NAT_NUM_T_HPP_INCLUDED#ifndef NAT_NUM_T_HPP_INCLUDED#ifndef NAT_NUM_T_HPP_INCLUDED

#define NAT_NUM_T_HPP_INCLUDED

#define NAT_NUM_T_HPP_INCLUDED#define NAT_NUM_T_HPP_INCLUDED

#include "base_num_t.hpp"

#include "nat_reg_digs_t.hpp"#include "base_num_t.hpp"#include "base_num_t.hpp"



namespace NumRepr {#include "nat_reg_digs_t.hpp"#include "nat_reg_digs_t.hpp"



template <std::uint64_t B>namespace NumRepr {namespace NumRepr {

  requires(B > 1)

class nat_num_t : public base_num_t<B> {

public:template <std::uint64_t B>template <std::uint64_t B>

  using dig_t = dig_t<B>;

  using UINT_T = typename dig_t::UINT_T;  requires(B > 1)  requires(B > 1)

  using base_num_t = base_num_t<B>;

  using SIG_UINT_T = typename dig_t::SIG_UINT_T;class nat_num_t : public base_num_t<B> {class nat_num_t : public base_num_t<B> {

  using SIG_SINT_T = typename dig_t::SIG_SINT_T;

public:public:

  // Iterator types from base class

  using str_iterator = typename base_num_t::str_iterator;  using dig_t = dig_t<B>;

  using c_str_iterator = typename base_num_t::c_str_iterator;

  using r_str_iterator = typename base_num_t::r_str_iterator;  using UINT_T = typename dig_t::UINT_T;

  using cr_str_iterator = typename base_num_t::cr_str_iterator;

    using base_num_t = base_num_t<B>;

  // Register types for arithmetic operations

  template <std::size_t N>  using SIG_UINT_T = typename dig_t::SIG_UINT_T;

  using nat_reg_N_digs_t = nat_reg_digs_t<B, N>;

  using nat_reg_digs_t = nat_reg_N_digs_t<2>;  using SIG_SINT_T = typename dig_t::SIG_SINT_T;



private:

  nat_reg_digs_t aux; // Auxiliary variable for operations

  // Iterator types from base class  // Iterator types from base class

public:

  /************************************/  using str_iterator = typename base_num_t::str_iterator;

  /*                                  */

  /*           CONSTRUCTORS           */  using const_str_iterator = typename base_num_t::const_str_iterator;

  /*                                  */

  /************************************/  using c_str_iterator = typename base_num_t::c_str_iterator;



  /// Default constructor - creates zero  using r_str_iterator = typename base_num_t::r_str_iterator;

  constexpr nat_num_t() noexcept {

    base_num_t &cthis = (*this);  using cr_str_iterator = typename base_num_t::cr_str_iterator;  

    aux = nat_reg_digs_t{};  

    cthis.resize(1);  // Register types for arithmetic operations  // Register types for arithmetic operations

    cthis[0] = dig_t{0};

  }  template <std::size_t N>  template <std::size_t N>



  /// Copy constructor  using nat_reg_N_digs_t = nat_reg_digs_t<B, N>;  

  constexpr nat_num_t(const nat_num_t &other) noexcept = default;  

  using nat_reg_digs_t = nat_reg_N_digs_t<2>;

  /// Move constructor

  constexpr nat_num_t(nat_num_t &&other) noexcept = default;private:



  /// Constructor from register pair  nat_reg_digs_t aux; // Auxiliary variable for operations  nat_reg_digs_t aux;

  constexpr nat_num_t(const nat_reg_digs_t &a) noexcept {

    base_num_t &cthis = (*this);

    aux = nat_reg_digs_t{};

    cthis.resize(2);public:  /****************************/

    cthis[0] = a[0];

    cthis[1] = a[1];  /************************************/  /*						              */

    reduce();

  }  /*                                  */  /*		CONSTRUCTORES	        */



  /// Constructor from single digit  /*           CONSTRUCTORS           */  /*						              */

  template <type_traits::integral_c Int_t>

  constexpr nat_num_t(Int_t value) noexcept {  /*                                  */  /****************************/

    base_num_t &cthis = (*this);

    aux = nat_reg_digs_t{};  /************************************/public:

    

    if (value == 0) {  inline size_t size() const {

      cthis.resize(1);

      cthis[0] = dig_t{0};  /// Default constructor - creates zero    const dig_string_t &cthis = (*this);

      return;

    }  constexpr nat_num_t() noexcept {    return cthis.dig_string_t::size();



    // Convert integer to digits in base B    base_num_t &cthis = (*this);  }

    std::vector<dig_t> digits;

    Int_t temp = (value < 0) ? -value : value;    aux = nat_reg_digs_t{};

    

    while (temp > 0) {    cthis.resize(1);private:

      digits.push_back(dig_t{static_cast<UINT_T>(temp % B)});

      temp /= B;    cthis[0] = dig_t{0};  inline void resize(size_t arg) {

    }

      }    dig_string_t &cthis = (*this);

    cthis.resize(digits.size());

    for (std::size_t i = 0; i < digits.size(); ++i) {    cthis.dig_string_t::resize(arg);

      cthis[i] = digits[i];

    }  /// Copy constructor    return;

    reduce();

  }  constexpr nat_num_t(const nat_num_t &other) noexcept = default;  }



  /// Constructor from character

  constexpr nat_num_t(char ch) noexcept {

    base_num_t &cthis = (*this);  /// Move constructorpublic:

    cthis.clear();

    aux = nat_reg_digs_t{};  constexpr nat_num_t(nat_num_t &&other) noexcept = default;  inline void push_front(dig_t parg) {

    cthis.resize(1);

        dig_string_t &cthis = (*this);

    if (ch >= '0' && ch <= '9') {

      UINT_T digit_val = static_cast<UINT_T>(ch - '0');  /// Constructor from register pair    cthis.dig_string_t::push_front(parg);

      if (digit_val < B) {

        cthis[0] = dig_t{digit_val};  constexpr nat_num_t(const nat_reg_digs_t &a) noexcept {    return;

      } else {

        cthis[0] = dig_t{0};    base_num_t &cthis = (*this);  }

      }

    } else {    aux = nat_reg_digs_t{};

      cthis[0] = dig_t{0};

    }    cthis.resize(2);private:

  }

    cthis[0] = a[0];  inline nat_num_t &insert(size_t pos1, const dig_t chardig) {

  /// Constructor from two digits

  constexpr nat_num_t(const dig_t &a1, const dig_t &a0) noexcept {    cthis[1] = a[1];    dig_string_t &cthis = (*this);

    base_num_t &cthis = (*this);

    aux = nat_reg_digs_t{};    reduce();    cthis.dig_string_t::insert(pos1, 1, chardig);

    cthis.clear();

    cthis.resize(2);  }    return (*this);

    cthis[0] = a1;  // Most significant digit first (little-endian storage)

    cthis[1] = a0;  // Least significant digit  }

    reduce();

  }  /// Constructor from single digit  inline nat_num_t &insert(size_t pos1, size_t n, dig_t c) {



  /// Constructor from three digits  template <type_traits::integral_c Int_t>    dig_string_t &cthis = (*this);

  constexpr nat_num_t(const dig_t &a2, const dig_t &a1, const dig_t &a0) noexcept {

    base_num_t &cthis = (*this);  constexpr nat_num_t(Int_t value) noexcept {    cthis.dig_string_t::insert(pos1, n, c);

    aux = nat_reg_digs_t{};

    cthis.clear();    base_num_t &cthis = (*this);    return (*this);

    cthis.resize(3);

    cthis[0] = a2;  // Most significant    aux = nat_reg_digs_t{};  }

    cthis[1] = a1;  // Middle

    cthis[2] = a0;  // Least significant    

    reduce();

  }    if (value == 0) {  inline const nat_num_t &operator&=(const nat_num_t &arg) {



  /************************************/      cthis.resize(1);    dig_string_t &cthis = (*this);

  /*                                  */

  /*        ASSIGNMENT OPERATORS     */      cthis[0] = dig_t{0};    cthis.dig_string_t::operator+=(arg);

  /*                                  */

  /************************************/      return;    return (*this);



  /// Copy assignment    }  }

  constexpr nat_num_t &operator=(const nat_num_t &other) noexcept {

    if (this != &other) {

      base_num_t &cthis = (*this);

      cthis.clear();    // Convert integer to digits in base B  // string& erase ( size_t pos = 0, size_t n = npos );

      aux = other.aux;

      const std::size_t sz = other.size();    std::vector<dig_t> digits;

      cthis.resize(sz);

      for (std::size_t k = 0; k < sz; ++k) {    Int_t temp = (value < 0) ? -value : value;  inline nat_num_t &erase(size_t pos, size_t npos) {

        cthis[k] = other[k];

      }        nat_num_t &cthis = (*this);

      reduce();

    }    while (temp > 0) {    size_t npos_2 = npos;

    return (*this);

  }      digits.push_back(dig_t{static_cast<UINT_T>(temp % B)});    const size_t sz = size();



  /// Move assignment      temp /= B;    if ((sz == npos) and (pos == 0)) {

  constexpr nat_num_t &operator=(nat_num_t &&other) noexcept = default;

    }      npos_2--;

  /// Assignment from register pair

  constexpr const nat_num_t &operator=(const nat_reg_digs_t &a) noexcept {          operator[](sz - 1) = dig_t(0);

    base_num_t &cthis = (*this);

    cthis.clear();    cthis.resize(digits.size());    }

    aux = nat_reg_digs_t{};

    cthis.resize(2);    for (std::size_t i = 0; i < digits.size(); ++i) {    cthis.dig_string_t::erase(pos, npos_2);

    cthis[0] = a[0];

    cthis[1] = a[1];      cthis[i] = digits[i];    return (*this);

    reduce();

    return (*this);    }  }

  }

    reduce();

  /// Assignment from single digit

  constexpr const nat_num_t &operator=(const dig_t &a0) noexcept {  }  inline iterator erase(iterator first, iterator last) {

    base_num_t &cthis = (*this);

    aux = nat_reg_digs_t{};    size_t npos = last - first;

    cthis.clear();

    cthis.resize(1);  /************************************/    const size_t sz = size();

    cthis[0] = a0;

    return (*this);  /*                                  */    if (sz == npos) {

  }

  /*        ASSIGNMENT OPERATORS     */      last--;

  /// Assignment from integral type

  template <type_traits::integral_c Int_t>  /*                                  */      operator[](sz - 1) = d_0<B>();

  constexpr const nat_num_t &operator=(Int_t value) noexcept {

    *this = nat_num_t{value};  /************************************/    }

    return (*this);

  }    return dig_string_t::erase(first, last);



public:  /// Copy assignment  }

  /************************************/

  /*                                  */  constexpr nat_num_t &operator=(const nat_num_t &other) noexcept {

  /*        BASIC OPERATIONS          */

  /*                                  */    if (this != &other) {public:

  /************************************/

      base_num_t &cthis = (*this);

  /// Get size

  constexpr std::size_t size() const noexcept {      cthis.clear();  inline dig_t operator[](uint arg) const {

    const base_num_t &cthis = (*this);

    return cthis.size();      aux = other.aux;    const nat_num_t &cthis = (*this);

  }

      const std::size_t sz = other.size();    return cthis.dig_string_t::operator[](arg);

  /// Access operators

  constexpr dig_t operator[](std::size_t arg) const noexcept {      cthis.resize(sz);  }

    const base_num_t &cthis = (*this);

    return cthis[arg];      for (std::size_t k = 0; k < sz; ++k) {  inline dig_t &operator[](uint arg) {

  }

        cthis[k] = other[k];    dig_string_t &cthis = (*this);

  constexpr dig_t &operator[](std::size_t arg) noexcept {

    base_num_t &cthis = (*this);      }    return cthis.dig_string_t::operator[](arg);

    return cthis[arg];

  }      reduce();  }



  /// Clear    }

  constexpr void clear() noexcept {

    base_num_t &cthis = (*this);    return (*this);  inline void clear() {

    cthis.clear();

    cthis.resize(1);  }    dig_string_t &cthis = (*this);

    cthis[0] = dig_t{0};

  }    cthis.dig_string_t::clear();



  /// Push back  /// Move assignment  }

  constexpr void push_back(dig_t arg) noexcept {

    base_num_t &cthis = (*this);  constexpr nat_num_t &operator=(nat_num_t &&other) noexcept = default;

    cthis.push_back(arg);

  }    return base_num_t::erase(first, last);



  /// Push front (insert at beginning)  /// Assignment from register pair  }

  constexpr void push_front(dig_t parg) noexcept {

    base_num_t &cthis = (*this);  constexpr const nat_num_t &operator=(const nat_reg_digs_t &a) noexcept {

    cthis.insert(cthis.begin(), parg);

  }    base_num_t &cthis = (*this);public:



  /// Iterators    cthis.clear();  inline dig_t operator[](std::size_t arg) const {

  constexpr str_iterator begin() noexcept {

    base_num_t &cthis = (*this);    aux = nat_reg_digs_t{};    const base_num_t &cthis = (*this);

    return cthis.begin();

  }    cthis.resize(2);    return cthis.base_num_t::operator[](arg);



  constexpr c_str_iterator end() const noexcept {    cthis[0] = a[0];  }

    const base_num_t &cthis = (*this);

    return cthis.end();    cthis[1] = a[1];  inline dig_t &operator[](std::size_t arg) {

  }

    reduce();    base_num_t &cthis = (*this);

  constexpr c_str_iterator begin() const noexcept {

    const base_num_t &cthis = (*this);    return (*this);    return cthis.base_num_t::operator[](arg);

    return cthis.begin();

  }  }  }



  constexpr str_iterator end() noexcept {

    base_num_t &cthis = (*this);

    return cthis.end();public:  inline void clear() {

  }

  /************************************/    base_num_t &cthis = (*this);

private:

  /// Resize  /*                                  */    cthis.base_num_t::clear();

  constexpr void resize(std::size_t arg) noexcept {

    base_num_t &cthis = (*this);  /*        BASIC OPERATIONS          */  }

    cthis.resize(arg);

  }  /*                                  */



  /// Insert  /************************************/  inline void push_back(dig_t arg) {

  constexpr nat_num_t &insert(std::size_t pos1, const dig_t chardig) noexcept {

    base_num_t &cthis = (*this);    base_num_t &cthis = (*this);

    cthis.insert(cthis.begin() + pos1, chardig);

    return (*this);  /// Get size    cthis.base_num_t::push_back(arg);

  }

  constexpr std::size_t size() const noexcept {  }

  constexpr nat_num_t &insert(std::size_t pos1, std::size_t n, dig_t c) noexcept {

    base_num_t &cthis = (*this);    const base_num_t &cthis = (*this);

    cthis.insert(cthis.begin() + pos1, n, c);

    return (*this);    return cthis.size();  inline typename base_num_t::str_iterator begin() {

  }

  }    base_num_t &cthis = (*this);

  /// Erase

  constexpr nat_num_t &erase(std::size_t pos, std::size_t npos) noexcept {    return cthis.base_num_t::begin();

    base_num_t &cthis = (*this);

    const std::size_t sz = size();  /// Access operators  }

    if ((sz == npos) && (pos == 0)) {

      // Special case: erasing everything, leave one zero digit  constexpr dig_t operator[](std::size_t arg) const noexcept {

      cthis.clear();

      cthis.resize(1);    const base_num_t &cthis = (*this);  inline typename base_num_t::c_str_iterator end() const {

      cthis[0] = dig_t{0};

    } else {    return cthis[arg];    const base_num_t &cthis = (*this);

      auto it_begin = cthis.begin() + pos;

      auto it_end = (pos + npos < sz) ? it_begin + npos : cthis.end();  }    return cthis.base_num_t::end();

      cthis.erase(it_begin, it_end);

    }  }

    return (*this);

  }  constexpr dig_t &operator[](std::size_t arg) noexcept {  }



  constexpr str_iterator erase(str_iterator first, str_iterator last) noexcept {    base_num_t &cthis = (*this);

    base_num_t &cthis = (*this);

    const std::size_t npos = std::distance(first, last);    return cthis[arg];public:

    const std::size_t sz = size();

      }

    if (sz == npos) {

      // Erasing everything, leave one zero  nat_num_t() {

      cthis.clear();

      cthis.resize(1);  /// Clear    nat_num_t &cthis = (*this);

      cthis[0] = dig_t{0};

      return cthis.begin();  constexpr void clear() noexcept {    aux = pardigs();

    }

        base_num_t &cthis = (*this);    cthis.resize(1);

    return cthis.erase(first, last);

  }    cthis.clear();    cthis[0] = dig(0);



public:    cthis.resize(1);  }

  /************************************/

  /*                                  */    cthis[0] = dig_t{0};

  /*        UTILITY FUNCTIONS        */

  /*                                  */  }  const nat_num_t &operator=(const nat_num_t &a) {

  /************************************/

    nat_num_t &cthis = (*this);

  /// Remove leading zeros

  constexpr void reduce() noexcept {  /// Push back    cthis.clear();

    base_num_t &cthis = (*this);

      constexpr void push_back(dig_t arg) noexcept {    aux = a.aux;

    // Remove leading zeros but keep at least one digit

    while (cthis.size() > 1 && cthis.back() == dig_t{0}) {    base_num_t &cthis = (*this);    const int sz = a.size();

      cthis.pop_back();

    }    cthis.push_back(arg);    cthis.resize(sz);

    

    // Ensure we have at least one digit  }    for (int k = 0; k < sz; ++k) {

    if (cthis.empty()) {

      cthis.resize(1);      cthis[k] = a[k];

      cthis[0] = dig_t{0};

    }  /// Push front (insert at beginning)    }

  }

  constexpr void push_front(dig_t parg) noexcept {    cthis.reduce();

  /// Check if zero

  constexpr bool is_0() const noexcept {    base_num_t &cthis = (*this);    return cthis;

    const base_num_t &cthis = (*this);

    return (cthis.size() == 1 && cthis[0] == dig_t{0});    cthis.insert(cthis.begin(), parg);  }

  }

  }

  /// Check if one

  constexpr bool is_1() const noexcept {  nat_num_t &operator=(nat_num_t &a) {

    const base_num_t &cthis = (*this);

    return (cthis.size() == 1 && cthis[0] == dig_t{1});  /// Iterators    nat_num_t &cthis = (*this);

  }

  constexpr str_iterator begin() noexcept {    aux = a.aux;

  /// Check if even

  constexpr bool is_even() const noexcept {    base_num_t &cthis = (*this);    const int sz = a.size();

    const base_num_t &cthis = (*this);

    return (cthis[0]() % 2 == 0);    return cthis.begin();    cthis.clear();

  }

  }    cthis.resize(sz);

  /// Check if odd

  constexpr bool is_odd() const noexcept {    for (int k = 0; k < sz; ++k) {

    return !is_even();

  }  constexpr c_str_iterator end() const noexcept {      cthis[k] = a[k];



public:    const base_num_t &cthis = (*this);    }

  /************************************/

  /*                                  */    return cthis.end();    cthis.reduce();

  /*       COMPARISON OPERATORS       */

  /*                                  */  }    return cthis;

  /************************************/

  }

  constexpr bool operator==(const nat_num_t &other) const noexcept {

    const base_num_t &cthis = (*this);  constexpr c_str_iterator begin() const noexcept {

    const base_num_t &other_base = other;

        const base_num_t &cthis = (*this);  nat_num_t(const nat_num_t &a) {

    if (cthis.size() != other_base.size()) {

      return false;    return cthis.begin();    nat_num_t &cthis = (*this);

    }

      }    aux = a.aux;

    for (std::size_t i = 0; i < cthis.size(); ++i) {

      if (cthis[i] != other_base[i]) {    cthis.clear();

        return false;

      }  constexpr str_iterator end() noexcept {    cthis.resize(a.size());

    }

    return true;    base_num_t &cthis = (*this);    for (usint k = 0; k < a.size(); ++k)

  }

    return cthis.end();      cthis[k] = a[k];

  constexpr bool operator!=(const nat_num_t &other) const noexcept {

    return !(*this == other);  }    cthis.reduce();

  }

  }

  constexpr bool operator<(const nat_num_t &other) const noexcept {

    const base_num_t &cthis = (*this);private:

    const base_num_t &other_base = other;

      /// Resize  nat_num_t(const string &a) {

    if (cthis.size() != other_base.size()) {

      return cthis.size() < other_base.size();  constexpr void resize(std::size_t arg) noexcept {    nat_num_t &cthis = (*this);

    }

        base_num_t &cthis = (*this);    cthis.clear();

    // Compare from most significant digit

    for (std::size_t i = cthis.size(); i > 0; --i) {    cthis.resize(arg);    basic_stringstream<char> in;

      if (cthis[i-1] != other_base[i-1]) {

        return cthis[i-1] < other_base[i-1];  }    in.clear();

      }

    }    in << a;

    return false; // Equal

  }  /// Insert    in >> (*this);



  constexpr bool operator<=(const nat_num_t &other) const noexcept {  constexpr nat_num_t &insert(std::size_t pos1, const dig_t chardig) noexcept {    return;

    return (*this < other) || (*this == other);

  }    base_num_t &cthis = (*this);  }



  constexpr bool operator>(const nat_num_t &other) const noexcept {    cthis.insert(cthis.begin() + pos1, chardig);

    return !(*this <= other);

  }    return (*this);  const nat_num_t &operator=(const string &a) {



  constexpr bool operator>=(const nat_num_t &other) const noexcept {  }    nat_num_t &cthis = (*this);

    return !(*this < other);

  }    cthis.clear();



  /// Three-way comparison (C++20)  constexpr nat_num_t &insert(std::size_t pos1, std::size_t n, dig_t c) noexcept {    basic_stringstream<char> in;

  constexpr std::strong_ordering operator<=>(const nat_num_t &other) const noexcept {

    if (*this < other) return std::strong_ordering::less;    base_num_t &cthis = (*this);    in.clear();

    if (*this > other) return std::strong_ordering::greater;

    return std::strong_ordering::equal;    cthis.insert(cthis.begin() + pos1, n, c);    in << a;

  }

    return (*this);    in >> cthis;

public:

  /************************************/  }    return cthis;

  /*                                  */

  /*       ARITHMETIC OPERATORS       */  }

  /*                                  */

  /************************************/  /// Erase



  /// Addition  constexpr nat_num_t &erase(std::size_t pos, std::size_t npos) noexcept {  operator string() const {

  constexpr nat_num_t operator+(const nat_num_t &other) const noexcept {

    nat_num_t result = *this;    base_num_t &cthis = (*this);

    result += other;

    return result;    const std::size_t sz = size();    const nat_num_t &cthis = (*this);

  }

    if ((sz == npos) && (pos == 0)) {    string ret;

  constexpr nat_num_t &operator+=(const nat_num_t &other) noexcept {

    base_num_t &cthis = (*this);      // Special case: erasing everything, leave one zero digit    basic_stringstream<char> sal_aux;

    const base_num_t &other_base = other;

          cthis.clear();    sal_aux << cthis;

    const std::size_t max_size = std::max(cthis.size(), other_base.size());

    cthis.resize(max_size + 1); // Extra space for potential carry      cthis.resize(1);    sal_aux >> ret;

    

    dig_t carry{0};      cthis[0] = dig_t{0};    return ret;

    for (std::size_t i = 0; i < max_size; ++i) {

      dig_t a = (i < size()) ? cthis[i] : dig_t{0};    } else {  }

      dig_t b = (i < other_base.size()) ? other_base[i] : dig_t{0};

            auto it_begin = cthis.begin() + pos;

      // Use auxiliary register for addition

      aux[0] = a;      auto it_end = (pos + npos < sz) ? it_begin + npos : cthis.end();  nat_num_t(dig a0) {

      aux[1] = carry;

      aux[0] += aux[1]; // Add carry first      cthis.erase(it_begin, it_end);    nat_num_t &cthis = (*this);

      

      carry = (aux[0]() + b() >= B) ? dig_t{1} : dig_t{0};    }    aux = pardigs();

      cthis[i] = aux[0] + b; // This will automatically mod B

    }    return (*this);    cthis.clear();

    

    if (carry != dig_t{0}) {  }    cthis.resize(1);

      cthis[max_size] = carry;

    } else {    cthis[0] = a0;

      cthis.resize(max_size);

    }  constexpr str_iterator erase(str_iterator first, str_iterator last) noexcept {  }

    

    reduce();    base_num_t &cthis = (*this);

    return *this;

  }    const std::size_t npos = std::distance(first, last);  const nat_num_t &operator=(const dig &a0) {



  /// Subtraction (assumes this >= other for natural numbers)    const std::size_t sz = size();    nat_num_t &cthis = (*this);

  constexpr nat_num_t operator-(const nat_num_t &other) const noexcept {

    nat_num_t result = *this;        aux = pardigs();

    result -= other;

    return result;    if (sz == npos) {    cthis.clear();

  }

      // Erasing everything, leave one zero    cthis.resize(1);

  constexpr nat_num_t &operator-=(const nat_num_t &other) noexcept {

    base_num_t &cthis = (*this);      cthis.clear();    cthis[0] = a0;

    const base_num_t &other_base = other;

          cthis.resize(1);    return cthis;

    // Natural number subtraction: assume this >= other

    if (*this < other) {      cthis[0] = dig_t{0};  }

      // Result would be negative, set to zero

      clear();      return cthis.begin();

      return *this;

    }    }  nat_num_t(const dig &a1, const dig &a0) {

    

    dig_t borrow{0};        nat_num_t &cthis = (*this);

    for (std::size_t i = 0; i < cthis.size(); ++i) {

      dig_t a = cthis[i];    return cthis.erase(first, last);    aux = pardigs();

      dig_t b = (i < other_base.size()) ? other_base[i] : dig_t{0};

        }    cthis.clear();

      // Use auxiliary register for subtraction

      aux[0] = a;    cthis.resize(2);

      aux[1] = borrow;

      public:    cthis[1] = a0;

      if (aux[0] >= aux[1]) {

        aux[0] -= aux[1];  /************************************/    cthis[0] = a1;

        borrow = dig_t{0};

      } else {  /*                                  */    cthis.reduce();

        aux[0] += dig_t{B - aux[1]()};

        borrow = dig_t{1};  /*        UTILITY FUNCTIONS        */  }

      }

        /*                                  */

      if (aux[0] >= b) {

        cthis[i] = aux[0] - b;  /************************************/  nat_num_t(const dig &a2, const dig &a1, const dig &a0) {

      } else {

        cthis[i] = aux[0] + dig_t{B} - b;    nat_num_t &cthis = (*this);

        borrow = dig_t{1};

      }  /// Remove leading zeros    aux = pardigs();

    }

      constexpr void reduce() noexcept {    cthis.clear();

    reduce();

    return *this;    base_num_t &cthis = (*this);    cthis.resize(3);

  }

        cthis[2] = a0;

  /// Increment operators

  constexpr nat_num_t &operator++() noexcept {    // Remove leading zeros but keep at least one digit    cthis[1] = a1;

    *this += nat_num_t{1};

    return *this;    while (cthis.size() > 1 && cthis.back() == dig_t{0}) {    cthis[0] = a2;

  }

      cthis.pop_back();    cthis.reduce();

  constexpr nat_num_t operator++(int) noexcept {

    nat_num_t temp = *this;    }  }

    ++(*this);

    return temp;    

  }

    // Ensure we have at least one digit  nat_num_t(const vector<dig> &arg) {

  /// Decrement operators

  constexpr nat_num_t &operator--() noexcept {    if (cthis.empty()) {    nat_num_t &cthis = (*this);

    if (!is_0()) {

      *this -= nat_num_t{1};      cthis.resize(1);    aux = pardigs();

    }

    return *this;      cthis[0] = dig_t{0};    cthis.clear();

  }

    }    for (int ix = 0; ix < arg.size(); ++ix)

  constexpr nat_num_t operator--(int) noexcept {

    nat_num_t temp = *this;  }      cthis.push_back(arg[ix]);

    --(*this);

    return temp;    cthis.reduce();

  }

  /// Check if zero  }

  /// Addition with single digit

  constexpr nat_num_t operator+(const dig_t &arg) const noexcept {  constexpr bool is_0() const noexcept {

    nat_num_t result = *this;

    result += arg;    const base_num_t &cthis = (*this);  const nat_num_t &operator=(const vector<dig> &arg) {

    return result;

  }    return (cthis.size() == 1 && cthis[0] == dig_t{0});    nat_num_t &cthis = (*this);



  constexpr nat_num_t &operator+=(const dig_t &arg) noexcept {  }    aux = pardigs();

    base_num_t &cthis = (*this);

    reduce();    cthis.clear();

    dig_t carry{0};

      /// Check if one    for (int ix = 0; ix < arg.size(); ++ix)

    std::size_t k = cthis.size();

    aux[0] = cthis[k - 1];  constexpr bool is_1() const noexcept {      cthis.push_back(arg[ix]);

    aux[1] = arg;

    aux[0] += aux[1];    const base_num_t &cthis = (*this);    cthis.reduce();

    cthis[k - 1] = aux[0];

    carry = (aux[0]() >= B) ? dig_t{1} : dig_t{0};    return (cthis.size() == 1 && cthis[0] == dig_t{1});    return cthis;

    --k;

      }  }

    for (; k > 0; --k) {

      aux[0] = carry;

      aux[1] = cthis[k - 1];

      aux[0] += aux[1];  /// Check if even  operator vector<dig>() const {

      cthis[k - 1] = aux[0];

      carry = (aux[0]() >= B) ? dig_t{1} : dig_t{0};  constexpr bool is_even() const noexcept {    const nat_num_t &cthis = (*this);

    }

    const base_num_t &cthis = (*this);    const usint sz = (cthis.reduce()).size();

    if (carry != dig_t{0}) {

      push_front(carry);    return (cthis[0]() % 2 == 0);    const usint pos_max = sz - 1;

    }

    reduce();  }    vector<dig> ret(sz);

    return *this;

  }    for (int ix = 0; ix < sz; ++ix)



public:  /// Check if odd      ret[pos_max - ix] = cthis[ix];

  /************************************/

  /*                                  */  constexpr bool is_odd() const noexcept {    return ret;

  /*          STRING CONVERSION       */

  /*                                  */    return !is_even();  }

  /************************************/

  }

  /// Convert to string in base B

  constexpr std::string to_string() const noexcept {  nat_num_t(const pardigs &a) {

    const base_num_t &cthis = (*this);

    public:    nat_num_t &cthis = (*this);

    std::string result;

    result.reserve(cthis.size() * 3); // Rough estimate  /************************************/    aux = pardigs();

    

    // Add digits from most significant to least significant  /*                                  */    cthis.clear();

    for (std::size_t i = cthis.size(); i > 0; --i) {

      if (!result.empty()) result += ",";  /*       COMPARISON OPERATORS       */    cthis.resize(2);

      result += std::to_string(cthis[i-1]());

    }  /*                                  */    cthis[0] = a.g_first();

    

    return "nat#[" + result + "]#B" + std::to_string(B);  /************************************/    cthis[1] = a.g_second();

  }

    cthis.reduce();

  /// Convert to decimal string (base 10 representation of the number)

  std::string to_decimal_string() const noexcept {  constexpr bool operator==(const nat_num_t &other) const noexcept {  }

    if (is_0()) return "0";

        const base_num_t &cthis = (*this);

    // For now, return simple representation

    return to_string();    const base_num_t &other_base = other;  const nat_num_t &operator=(const pardigs &a) {

  }

        const nat_num_t &cthis = (*this);

  /// Conversion to integral types

  constexpr operator UINT_T() const noexcept {    if (cthis.size() != other_base.size()) {    aux = pardigs();

    const base_num_t &cthis = (*this);

    const std::size_t sz = size();      return false;    cthis.clear();

    UINT_T ret = 0;

        }    cthis.resize(2);

    // Convert from most significant to least significant

    for (std::size_t i = 0; i < sz && i < sizeof(UINT_T); ++i) {        cthis[0] = a.g_first();

      ret *= B;

      ret += cthis[sz - 1 - i]();    for (std::size_t i = 0; i < cthis.size(); ++i) {    cthis[1] = a.g_second();

    }

    return ret;      if (cthis[i] != other_base[i]) {    cthis.reduce();

  }

};        return false;    return cthis;



/************************************/      }  }

/*                                  */

/*        STREAM OPERATORS          */    }

/*                                  */

/************************************/    return true;  nat_num_t(const n2digs &a) {



template <std::uint64_t Base>  }    nat_num_t &cthis = (*this);

  requires(Base > 1)

std::ostream &operator<<(std::ostream &os, const nat_num_t<Base> &num) {    aux = pardigs();

  os << num.to_string();

  return os;  constexpr bool operator!=(const nat_num_t &other) const noexcept {    cthis.clear();

}

    return !(*this == other);    cthis.resize(2);

} // namespace NumRepr

  }    cthis[0] = a.first();

#endif // NAT_NUM_T_HPP_INCLUDED
    cthis[1] = a.second();

  constexpr bool operator<(const nat_num_t &other) const noexcept {    cthis.reduce();

    const base_num_t &cthis = (*this);  }

    const base_num_t &other_base = other;

      const nat_num_t &operator=(const n2digs &a) {

    if (cthis.size() != other_base.size()) {    const nat_num_t &cthis = (*this);

      return cthis.size() < other_base.size();    aux = pardigs();

    }    cthis.clear();

        cthis.resize(2);

    // Compare from most significant digit    cthis[0] = a.first();

    for (std::size_t i = cthis.size(); i > 0; --i) {    cthis[1] = a.second();

      if (cthis[i-1] != other_base[i-1]) {    cthis.reduce();

        return cthis[i-1] < other_base[i-1];    return cthis;

      }  }

    }

    return false; // Equal  nat_num_t(char ch) {

  }    nat_num_t &cthis = (*this);

    cthis.clear();

  constexpr bool operator<=(const nat_num_t &other) const noexcept {    aux = pardigs();

    return (*this < other) || (*this == other);    cthis.resize(1);

  }    cthis[0] = dig_t(static_cast<uchint>(ch - '0'));

  }

  constexpr bool operator>(const nat_num_t &other) const noexcept {

    return !(*this <= other);  const nat_num_t &operator=(char ch) {

  }    nat_num_t &cthis = (*this);

    cthis.clear();

  constexpr bool operator>=(const nat_num_t &other) const noexcept {    aux = pardigs();

    return !(*this < other);    cthis.resize(1);

  }    cthis[0] = dig_t(static_cast<uchint>(ch - '0'));

    return cthis;

  /// Three-way comparison (C++20)  }

  constexpr std::strong_ordering operator<=>(const nat_num_t &other) const noexcept {

    if (*this < other) return std::strong_ordering::less;  nat_num_t(uchint a) {

    if (*this > other) return std::strong_ordering::greater;    nat_num_t &cthis = (*this);

    return std::strong_ordering::equal;    aux = pardigs();

  }    cthis.clear();

    cthis.resize(1);

public:    cthis[0] = UInt2Dig<B>(a);

  /************************************/  }

  /*                                  */

  /*       ARITHMETIC OPERATORS       */  const nat_num_t &operator=(uchint a) {

  /*                                  */    nat_num_t &cthis = (*this);

  /************************************/    aux = pardigs();

    cthis.clear();

  /// Addition    cthis.resize(1);

  constexpr nat_num_t operator+(const nat_num_t &other) const noexcept {    cthis[0] = UInt2Dig<B>(a);

    nat_num_t result = *this;    return cthis;

    result += other;  }

    return result;

  }  nat_num_t(usint a) {

    nat_num_t &cthis = (*this);

  constexpr nat_num_t &operator+=(const nat_num_t &other) noexcept {<<<<<<< HEAD

    base_num_t &cthis = (*this);    dig_string_t<B> temp;

    const base_num_t &other_base = other;=======

        base_num_t<B> temp;

    const std::size_t max_size = std::max(cthis.size(), other_base.size());>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    cthis.resize(max_size + 1); // Extra space for potential carry    cthis.clear();

        // cthis.resize(pot_max_base_B_en_Int_T<usint,B>().first);

    dig_t carry{0};    aux = pardigs();

    for (std::size_t i = 0; i < max_size; ++i) {    usint rem = 0, coc = a;

      dig_t a = (i < size()) ? cthis[i] : dig_t{0};    while (coc >= B) {

      dig_t b = (i < other_base.size()) ? other_base[i] : dig_t{0};      rem = coc % B;

            cthis.push_front(UInt2Dig<B>(rem));

      // Use auxiliary register for addition      coc = coc / B;

      aux[0] = a;    }

      aux[1] = carry;    rem = coc % B;

      aux[0] += aux[1]; // Add carry first    cthis.push_front(UInt2Dig<B>(rem));

        }

      carry = (aux[0]() + b() >= B) ? dig_t{1} : dig_t{0};

      cthis[i] = aux[0] + b; // This will automatically mod B  const nat_num_t &operator=(usint a) {

    }    nat_num_t &cthis = (*this);

    <<<<<<< HEAD

    if (carry != dig_t{0}) {    dig_string_t<B> temp;

      cthis[max_size] = carry;=======

    } else {    base_num_t<B> temp;

      cthis.resize(max_size);>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e

    }    cthis.clear();

        // cthis.resize(pot_max_base_B_en_Int_T<usint,B>());

    reduce();    aux = pardigs();

    return *this;    usint rem = 0, coc = a;

  }    while (coc >= B) {

      rem = coc % B;

  /// Subtraction (assumes this >= other for natural numbers)      cthis.push_front(UInt2Dig<B>(rem));

  constexpr nat_num_t operator-(const nat_num_t &other) const noexcept {      coc = coc / B;

    nat_num_t result = *this;    }

    result -= other;    rem = coc % B;

    return result;    cthis.push_front(UInt2Dig<B>(rem));

  }    return cthis;

  }

  constexpr nat_num_t &operator-=(const nat_num_t &other) noexcept {

    base_num_t &cthis = (*this);  nat_num_t(uint a) {

    const base_num_t &other_base = other;    nat_num_t &cthis = (*this);

        cthis.clear();

    // Natural number subtraction: assume this >= other    // const ullint tsz = pot_max_base_B_en_Int_T<uint,B>();

    if (*this < other) {    // cout << tsz << " digitos base 10 en un uint " << endl;

      // Result would be negative, set to zero    // cthis.resize(tsz);

      clear();    aux = pardigs();

      return *this;    uint rem = 0, coc = a;

    }    while (coc >= B) {

          rem = coc % B;

    dig_t borrow{0};      cthis.push_front(UInt2Dig<B>(rem));

    for (std::size_t i = 0; i < cthis.size(); ++i) {      coc = coc / B;

      dig_t a = cthis[i];    }

      dig_t b = (i < other_base.size()) ? other_base[i] : dig_t{0};    rem = coc % B;

          cthis.push_front(UInt2Dig<B>(rem));

      // Use auxiliary register for subtraction  }

      aux[0] = a;

      aux[1] = borrow;  const nat_num_t &operator=(uint a) {

          nat_num_t &cthis = (*this);

      if (aux[0] >= aux[1]) {    cthis.clear();

        aux[0] -= aux[1];    // cthis.resize(pot_max_base_B_en_Int_T<uint,B>());

        borrow = dig_t{0};    aux = pardigs();

      } else {    uint rem = 0, coc = a;

        aux[0] += dig_t{B - aux[1]()};    while (coc >= B) {

        borrow = dig_t{1};      rem = coc % B;

      }      cthis.push_front(UInt2Dig<B>(rem));

            coc = coc / B;

      if (aux[0] >= b) {    }

        cthis[i] = aux[0] - b;    rem = coc % B;

      } else {    cthis.push_front(UInt2Dig<B>(rem));

        cthis[i] = aux[0] + dig_t{B} - b;    return cthis;

        borrow = dig_t{1};  }

      }

    }  nat_num_t(ulint a) {

        nat_num_t &cthis = (*this);

    reduce();    aux = pardigs();

    return *this;    cthis.clear();

  }    // cthis.resize(pot_max_base_B_en_Int_T<ulint,B>().second);

    ulint rem = 0, coc = a;

  /// Increment operators    while (coc >= B) {

  constexpr nat_num_t &operator++() noexcept {      rem = coc % B;

    *this += nat_num_t{1};      cthis.push_front(UInt2Dig<B>(rem));

    return *this;      coc = coc / B;

  }    }

    rem = coc % B;

  constexpr nat_num_t operator++(int) noexcept {    cthis.push_front(UInt2Dig<B>(rem));

    nat_num_t temp = *this;  }

    ++(*this);

    return temp;  const nat_num_t &operator=(ulint a) {

  }    nat_num_t &cthis = (*this);

    aux = pardigs();

  /// Decrement operators    cthis.clear();

  constexpr nat_num_t &operator--() noexcept {    // cthis.resize(pot_max_base_B_en_Int_T<ulint,B>());

    if (!is_0()) {    ulint rem = 0, coc = a;

      *this -= nat_num_t{1};    while (coc >= B) {

    }      rem = coc % B;

    return *this;      cthis.push_front(UInt2Dig<B>(rem));

  }      coc = coc / B;

    }

  constexpr nat_num_t operator--(int) noexcept {    rem = coc % B;

    nat_num_t temp = *this;    cthis.push_front(UInt2Dig<B>(rem));

    --(*this);    return cthis;

    return temp;  }

  }

  nat_num_t(ullint a) {

public:    nat_num_t &cthis = (*this);

  /************************************/    aux = pardigs();

  /*                                  */    cthis.clear();

  /*          STRING CONVERSION       */    // cthis.resize(pot_max_base_B_en_Int_T<ullint,B>().second);

  /*                                  */    ullint rem = 0, coc = a;

  /************************************/    while (coc >= B) {

      rem = coc % B;

  /// Convert to string in base B      cthis.push_front(UInt2Dig<B>(rem));

  constexpr std::string to_string() const noexcept {      coc = coc / B;

    const base_num_t &cthis = (*this);    }

        rem = coc % B;

    std::string result;    cthis.push_front(UInt2Dig<B>(rem));

    result.reserve(cthis.size() * 3); // Rough estimate  }

    

    // Add digits from most significant to least significant  const nat_num_t &operator=(ullint a) {

    for (std::size_t i = cthis.size(); i > 0; --i) {    nat_num_t &cthis = (*this);

      if (!result.empty()) result += ",";    aux = pardigs();

      result += std::to_string(cthis[i-1]());    cthis.clear();

    }    // cthis.resize(pot_max_base_B_en_Int_T<ullint,B>());

        ullint rem = 0, coc = a;

    return "nat#[" + result + "]#B" + std::to_string(B);    while (coc >= B) {

  }      rem = coc % B;

      cthis.push_front(UInt2Dig<B>(rem));

  /// Convert to decimal string (base 10 representation of the number)      coc = coc / B;

  std::string to_decimal_string() const noexcept {    }

    if (is_0()) return "0";    rem = coc % B;

        cthis.push_front(UInt2Dig<B>(rem));

    // For now, return simple representation    return cthis;

    return to_string();  }

  }

};  operator uint() const {

    const nat_num_t &cthis = (*this);

/************************************/    const uint sz = (cthis.reduce()).size();

/*                                  */    const uint pos_max = sz - 1;

/*        STREAM OPERATORS          */    const uint nds = num_digs_max_base_B_en_Int_T<uint, B>();

/*                                  */    // cout << nds << endl;

/************************************/    uchint ret = 0;

    for (uint il = 0; (il < sz) and (il < nds); ++il) {

template <std::uint64_t Base>      ret *= B;

  requires(Base > 1)      ret += cthis[sz - nds + il].Dig2UInt();

std::ostream &operator<<(std::ostream &os, const nat_num_t<Base> &num) {    }

  os << num.to_string();    return ret;

  return os;  }

}

  operator usint() const {

} // namespace NumRepr    const nat_num_t &cthis = (*this);

    const uint sz = (cthis.reduce()).size();

#endif // NAT_NUM_T_HPP_INCLUDED    const uint pos_max = sz - 1;
    const uint nds = num_digs_max_base_B_en_Int_T<usint, B>();
    // cout << nds << endl;
    uchint ret = 0;
    for (uint il = 0; (il < sz) and (il < nds); ++il) {
      ret *= ullint(B);
      ret += cthis[sz - nds + il].Dig2UInt();
    }
    return ret;
  }

  operator uchint() const {
    const nat_num_t &cthis = (*this);
    const uint sz = (cthis.reduce()).size();
    const uint pos_max = sz - 1;
    const uint nds = num_digs_max_base_B_en_Int_T<uchint, B>();
    // cout << nds << endl;
    uchint ret = 0;
    for (uint il = 0; (il < sz) and (il < nds); ++il) {
      ret *= B;
      ret += cthis[sz - nds + il].Dig2UInt();
    }
    return ret;
  }

  operator ulint() const {
    const nat_num_t &cthis = (*this);
    const uint sz = (cthis.reduce()).size();
    const uint pos_max = sz - 1;
    const uint nds = num_digs_max_base_B_en_Int_T<ulint, B>();
    // cout << nds << endl;
    uchint ret = 0;
    for (uint il = 0; (il < sz) and (il < nds); ++il) {
      ret *= B;
      ret += cthis[sz - nds + il].Dig2UInt();
    }
    return ret;
  }

  operator ullint() const {
    const nat_num_t &cthis = (*this);
    const uint sz = (cthis.reduce()).size();
    const uint pos_max = sz - 1;
    const uint nds = num_digs_max_base_B_en_Int_T<ullint, B>();
    // cout << nds << endl;
    uchint ret = 0;
    for (uint il = 0; (il < sz) and (il < nds); ++il) {
      ret *= B;
      ret += cthis[sz - nds + il].Dig2UInt();
    }
    return ret;
  }

  nat_num_t &operator=(dig a0) {
    nat_num_t &cthis = (*this);
    aux = pardigs();
    cthis.clear();
    cthis.resize(1);
    cthis[0] = a0;
    return cthis;
  }

  /*********************************/
  /*							   */
  /*  DIGITOS NO SIGNIFICATIVOS	   */
  /*							   */
  /*********************************/

  usint ceros_a_la_izqda() const {
    const nat_num_t &cthis = (*this);
    // digitos no significativos para números positivos
    bool Exit = false;
    int sz = 0;
    const size_t fin = cthis.size();
    for (uint i = 0; (i < fin) and (!Exit); ++i) {
      if (cthis[i] == 0)
        ++sz;
      else
        Exit = true;
    }
    return sz;
  }
  // digitos no significativos para números positivos
  size_t ceros_a_la_drcha() const {
    const nat_num_t &cthis = (*this);
    bool Exit = false;
    size_t sz = 0;
    const size_t fin = cthis.size();
    const size_t finl = fin - 1;
    if (cthis[finl] == 0) {
      for (int i = finl; (i >= 0) and (!Exit); --i) {
        if (cthis[i] == 0)
          ++sz;
        else
          Exit = true;
      }
    }
    return sz;
  }

  usint digs_no_significativos() const {
    const nat_num_t &cthis = (*this);
    // digitos no significativos
    return ceros_a_la_izqda();
  }
  usint digs_fracc_no_significativos() const {
    const nat_num_t &cthis = (*this);
    // digitos no significativos
    return ceros_a_la_drcha();
  }

  /************************************/
  /*								  */
  /*   OPERACIONES COMPARATIVAS  	  */
  /*								  */
  /************************************/

  bool operator==(const nat_num_t &arg) const {
    const nat_num_t &cthis = (*this);
    const usint thisnsz = ceros_a_la_izqda();
    const usint thisvsz = cthis.size() - thisnsz;
    const usint argnsz = arg.ceros_a_la_izqda();
    const usint argvsz = arg.size() - argnsz;
    if ((thisvsz > argvsz) || (thisvsz < argvsz))
      return false;
    else {
      for (slint k = (thisvsz - 1); k >= 0; --k)
        if (arg[k] != cthis[k])
          return false;
      return true;
    }
  }

  bool operator!=(const nat_num_t &arg) const {
    const nat_num_t &cthis = (*this);
    const usint thisnsz = ceros_a_la_izqda();
    const usint thisvsz = (cthis.size()) - thisnsz;
    const usint argnsz = arg.ceros_a_la_izqda();
    const usint argvsz = arg.size() - argnsz;
    if ((thisvsz > argvsz) || (thisvsz < argvsz))
      return true;
    else {
      for (slint k = (thisvsz - 1); k >= 0; --k)
        if (arg[k] != cthis[k])
          return true;
      return false;
    }
  }

  bool operator>=(const nat_num_t &arg) const {
    const nat_num_t &cthis = (*this);
    const usint thisnsz = ceros_a_la_izqda();
    const usint thisvsz = (cthis.size()) - thisnsz;
    const usint argnsz = arg.ceros_a_la_izqda();
    const usint argvsz = arg.size() - argnsz;

    if (thisvsz > argvsz)
      return true;
    else if (thisvsz < argvsz)
      return false;

    for (usint k = 0; k < thisvsz; ++k) {
      if ((cthis[k] > arg[k]))
        return true;
      else if ((cthis[k] < arg[k]))
        return false;
    }
    return false;
  }

  bool operator<=(const nat_num_t &arg) const {
    const nat_num_t &cthis = (*this);
    const usint thisnsz = ceros_a_la_izqda();
    const usint thisvsz = (cthis.size()) - thisnsz;
    const usint argnsz = arg.ceros_a_la_izqda();
    const usint argvsz = arg.size() - argnsz;
    if (thisvsz < argvsz)
      return true;
    else if (thisvsz > argvsz)
      return false;
    for (usint k = 0; k < thisvsz; ++k) {
      if ((cthis[k] < arg[k]))
        return true;
      else if ((cthis[k] > arg[k]))
        return false;
    }
    return false;
  }

  bool operator>(const nat_num_t &arg) const {
    const nat_num_t &cthis = (*this);
    const usint thisnsz = ceros_a_la_izqda();
    const usint thisvsz = (cthis.size()) - thisnsz;
    const usint argnsz = arg.ceros_a_la_izqda();
    const usint argvsz = arg.size() - argnsz;
    if (thisvsz > argvsz)
      return true;
    else if (thisvsz < argvsz)
      return false;

    for (usint k = 0; k < thisvsz; ++k) {
      if ((cthis[k] > arg[k]))
        return true;
      else if ((cthis[k] < arg[k]))
        return false;
    }
    return false;
  }

  bool operator<(const nat_num_t &arg) const {
    const nat_num_t &cthis = (*this);
    const usint thisnsz = ceros_a_la_izqda();
    const usint thisvsz = (cthis.size()) - thisnsz;
    const usint argnsz = arg.ceros_a_la_izqda();
    const usint argvsz = arg.size() - argnsz;

    if (thisvsz < argvsz)
      return true;
    else if (thisvsz > argvsz)
      return false;
    for (usint k = 0; k < thisvsz; ++k) {
      if ((cthis[k] < arg[k]))
        return true;
      else if ((cthis[k] > arg[k]))
        return false;
    }
    return false;
  }

  /************************************/
  /*								  */
  /*     OPERACIONES ARITMETICAS 	  */
  /* 								  */
  /************************************/

  nat_num_t operator+(const nat_num_t &arg) const {

    const nat_num_t &cthis = (*this);
    pardigs_t<B> tempt;
    const bool cthis_is_max = (cthis >= arg);
    nat_num_t<B> cpyarg(arg);
    nat_num_t<B> cpythis(cthis);
    cpythis.reduce();
    cpyarg.reduce();
    nat_num_t<B> *pmax = ((cthis_is_max) ? (&cpythis) : (&cpyarg));
    nat_num_t<B> &max = (*pmax);
    nat_num_t<B> *pmin = ((cthis_is_max) ? (&cpyarg) : (&cpythis));
    nat_num_t<B> &min = (*pmin);

    dig carry(0);

    int M = (max.size()) - 1;
    int m = (min.size()) - 1;
    for (; !(m < 0); --M, --m) {
      tempt.p_uds(max[M]);
      tempt.p_decs(dig_t(0));
      tempt += min[m];
      tempt += carry;
      carry = tempt.g_decs();
      max[M] = tempt.g_uds();
    }
    for (; !(M < 0); --M) {
      tempt.p_uds(max[M]);
      tempt.p_decs(dig_t(0));
      tempt += carry;
      carry = tempt.g_decs();
      max[M] = tempt.g_uds();
    }

    if (carry != dig(0)) {
      max.push_front(carry);
    }

    max.aux = pardigs();
    return max;
  }

  nat_num_t operator-(const nat_num_t &arg) const {
    nat_num_t ret(*this);
    ret.reduce();
    const size_t szret = ret.size();
    nat_num_t cpy(arg.minus(ret.size()));
    ret += cpy;
    if (ret.size() > szret) {
      ret.erase(0, 1);
    }
    ret.reduce();
    return ret;
  }

  // Utilizamos una funcion nat_num_t * dig_t
  nat_num_t operator*(const nat_num_t &arg) const {
    const nat_num_t &cthis = (*this);
    cthis.reduce();
    nat_num_t multtemp;
    nat_num_t sumatemp;
    nat_num_t cadena_de_ceros;
    const int argsz = arg.size();
    const int argmsb = argsz - 2;

    multtemp = cthis * arg[argsz - 1];
    sumatemp += multtemp;

    for (int j = argmsb; j >= 0; --j) {
      multtemp = cthis * arg[j];
      multtemp &= cadena_de_ceros;
      sumatemp += multtemp;
      cadena_de_ceros.push_back(dig(0));
    }

    return sumatemp;
  }

  nat_num_t operator/(const nat_num_t &arg) const {
    const nat_num_t &cthis = (*this);
    nat_num_t dvndo_int(cthis); // Siempre será positivo
    dvndo_int.reduce();
    nat_num_t rem(dvndo_int);
    rem.reduce();
    nat_num_t dvsor_int(arg); // Siempre será positivo
    dvsor_int.reduce();

    const usint cssor =
        dvsor_int
            .ceros_a_la_drcha(); // ceros que tienen valor y por los que dividir
    // divisor y dividendo
    nat_num_t dvndo_fra(dvndo_int);

    if (dvndo_int.size() >= dvsor_int.size()) {
      dvndo_fra.erase(0, dvndo_int.size() - cssor);
      if (dvndo_int != nat_num_t(dig(0))) {
        dvndo_int.erase(dvndo_int.size() - cssor,
                        cssor); // division por una potencia de B, /B^cssor
      }
      dvndo_int.reduce();
      if (dvsor_int != nat_num_t(dig(0))) {
        dvsor_int.erase(dvsor_int.size() - cssor,
                        cssor); // division por una potencia de B  /B^cssor
      }
      nat_num_t dvsor_fra(dvsor_int);
      dvsor_fra.erase(0, dvsor_int.size() - cssor);
      dvsor_int.reduce();
    } else {
      dvndo_int = nat_num_t(dig(0));
      return dvndo_int;
    }
    // dvndo_fra.reduce();//dvndo_fra.reduce_fra() HAY QUE HACERLO
    const int szndo = dvndo_int.size();
    const int lsb_ndo = szndo - 1;
    const int msb_ndo = 0;
    const int szsor = dvsor_int.size();
    const int lsb_sor = szsor - 1;
    const int msb_sor = 0;

    // hemos dividido por los ceros del divisor (por una potencia de B)
    // tanto divisor como dividendo, obteniendo dvndo_int y dvsor_int como
    // cocientes enteros.
    div_uno(rem, dvndo_int, dvsor_int, szndo, szsor);
    // ahora hacemos lo mismo con el cociente de las potencias de B del
    // dividendo obteniendo dvndo_fra

    /* *
            RemReal = RemObtenido*(B^cssor) + Dvndo_fra

            rem = rem.insert(rem.size()-1,cssor,0);
            rem += dvndo_fra;
    * */
    //////////if (sgn_ndo!=sgn_sor) dvndo_int.mC_B();
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    return dvndo_int;
  }

  nat_num_t operator%(const nat_num_t &arg) const {
    const nat_num_t &cthis = (*this);
    nat_num_t dvndo_int(cthis); // Siempre será positivo
    dvndo_int.reduce();
    nat_num_t rem(dvndo_int);
    rem.reduce();
    nat_num_t dvsor_int(arg); // Siempre será positivo
    dvsor_int.reduce();
    dvndo_int /= dvsor_int;
    dvndo_int *= dvsor_int;
    rem -= dvndo_int;
    return rem;
  }

  nat_num_t operator*(pardigs a) const {
    const nat_num_t &cthis = (*this);
    pardigs temp;
    dig carry = 0;
    nat_num_t ret(*this);
    for (ssint k = (cthis.size() - 1); k >= 0; --k) {
      temp = (pardigs(cthis[k])) * (pardigs(a.g_first()));
      temp += carry;
      ret[k] = temp.g_first();
      carry = temp.g_second();
    }
    if (carry != 0)
      ret.insert(0, carry);
    ret.reduce();
    carry = 0;
    nat_num_t ret2(ret);
    for (ssint k = ((cthis.size()) - 1); k >= 0; --k) {
      temp = pardigs(cthis[k]) * pardigs(a.g_second());
      temp += carry;
      ret2.erase(0, k - 1);
      ret2 += temp.g_first(); // ¿?
      carry = temp.g_second();
    }
    ret += ret2;
    if (carry != 0)
      ret.insert(0, carry);
    ret.reduce();

    return ret;
  }

  //	nat_num_t operator / (pardigs) const;
  //	nat_num_t operator % (pardigs) const;

  nat_num_t operator+(dig arg) const {
    nat_num_t ret(*this);
    ret.reduce();
    pardigs tempt;
    const usint szt = ret.size();
    ssint k = szt - 1;
    dig carry;

    tempt.p_uds(ret[k]);
    tempt += arg;
    ret[k] = tempt.g_uds();
    carry = tempt.g_decs();
    tempt.p_decs(dig(0));

    if (szt >= 1) {
      for (k = szt - 2; k >= 0; --k) {
        tempt.p_uds(ret[k]);
        tempt += carry;
        ret[k] = tempt.g_uds();
        carry = tempt.g_decs();
        tempt.p_decs(dig(0));
      }
    }

    ret.push_front(carry);
    ret.aux = pardigs();
    ret.reduce();
    return ret;
  }

  nat_num_t operator-(dig arg) const {
    nat_num_t ret(*this);
    ret.reduce();
    if (arg == dig(0))
      return ret;
    nat_num_t cpy(nat_num_t(arg).minus(ret.size()));
    pardigs tempt;
    pardigs tempa;
    sint szt = ret.size();
    sint k = szt - 1;
    tempt.p_uds(ret[k]);
    tempt.p_decs(dig(0));
    tempa.p_uds(cpy[k]);
    tempa.p_decs(dig(0));
    tempt += tempa;
    ret[k] = tempt.g_uds();
    dig carry(tempt.g_decs());
    --k;
    for (; k >= 0; --k) {
      tempt.p_uds(ret[k]);
      tempt += cpy[k];
      tempt += carry;
      carry = tempt.g_decs();
      ret[k] = tempt.g_uds();
    }

    ret.reduce();
    ret.aux = pardigs();
    return ret;
  }

  nat_num_t operator*(dig a) const {
    const nat_num_t &cthis = (*this);
    pardigs temp;
    dig carry = 0;
    const int sz = cthis.size();
    const int lsb = sz - 1;
    nat_num_t ret(*this);
    for (int k = lsb; k >= 0; --k) {
      temp = pardigs(dig(0), cthis[k]) * a;
      temp += carry;
      ret[k] = temp.g_uds();
      carry = temp.g_decs();
    }
    if (carry != 0) {
      ret.push_front(carry);
    }
    ret.reduce();
    return ret;
  }

  /************************************/
  /*									*/
  /*   OPERACIONES ARITMETICAS		*/
  /*	     CON ASIGNACION				*/
  /* 									*/
  /************************************/

  const nat_num_t &operator+=(const nat_num_t &arg) {
    nat_num_t &cthis = (*this);
    cthis.reduce();
    pardigs_t<B> tempt;
    const bool cthis_is_max = (cthis >= arg);
    nat_num_t<B> cpyarg(arg);
    cpyarg.reduce();
    nat_num_t<B> *pmax = ((cthis_is_max) ? (&cthis) : (&cpyarg));
    nat_num_t<B> &max = (*pmax);
    nat_num_t<B> *pmin = ((cthis_is_max) ? (&cpyarg) : (&cthis));
    nat_num_t<B> &min = (*pmin);

    dig carry(0);

    int M = (max.size()) - 1;
    int m = (min.size()) - 1;
    cthis.aux = pardigs();
    for (; !(m < 0); --M, --m) {
      tempt.p_uds(max[M]);
      tempt.p_decs(dig_t(0));
      tempt += min[m];
      tempt += carry;
      carry = tempt.g_decs();
      max[M] = tempt.g_uds();
    }
    for (; !(M < 0); --M) {
      tempt.p_uds(max[M]);
      tempt.p_decs(dig_t(0));
      tempt += carry;
      carry = tempt.g_decs();
      max[M] = tempt.g_uds();
    }

    if (carry != dig(0)) {
      max.push_front(carry);
    }

    if ((&cthis) != (&max)) {
      cthis = (max.reduce());
    } else {
      cthis.reduce();
    }
    cthis.aux = pardigs();
    return cthis;
  }

  const nat_num_t &operator-=(const nat_num_t &arg) {
    nat_num_t &ret = (*this);
    ret.reduce();
    const size_t szret = ret.size();
    nat_num_t cpy(arg.minus(ret.size()));
    // cpy.reduce();
    ret += cpy;
    if (ret.size() > szret) {
      ret.erase(0, 1);
    }
    ret.reduce();
    return ret;
  }

  const nat_num_t &operator*=(const nat_num_t &arg) {
    nat_num_t &cthis = (*this);
    cthis.reduce();
    nat_num_t multtemp;
    nat_num_t sumatemp;
    nat_num_t cadena_de_ceros;
    const int argsz = arg.size();
    const int argmsb = argsz - 2;

    multtemp = cthis * arg[argsz - 1];
    sumatemp += multtemp;

    for (int j = argmsb; j >= 0; --j) {
      multtemp = cthis * arg[j];
      multtemp &= cadena_de_ceros;
      sumatemp += multtemp;
      cadena_de_ceros.push_back(dig(0));
    }
    cthis = sumatemp;
    return cthis;
  }

  inline nat_num_t substr(size_t pos, size_t n) const {
<<<<<<< HEAD
    const dig_string_t &cthis = (*this);
=======
    const base_num_t &cthis = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    cthis.nbstr::substr(pos, n);
    return (*this);
  }

  const nat_num_t &operator/=(const nat_num_t &arg) {
    nat_num_t &cthis = (*this);
    nat_num_t dvndo_int(*this); // Siempre será positivo
    dvndo_int.reduce();
    nat_num_t rem(dvndo_int);
    rem.reduce();
    nat_num_t dvsor_int(arg); // Siempre será positivo
    dvsor_int.reduce();

    const usint cssor =
        dvsor_int
            .ceros_a_la_drcha(); // ceros que tienen valor y por los que dividir
    // divisor y dividendo
    nat_num_t dvndo_fra(dvndo_int);

    if (dvndo_int.size() >= dvsor_int.size()) {
      dvndo_fra.erase(0, dvndo_int.size() - cssor);
      if (dvndo_int != nat_num_t(dig(0))) {
        dvndo_int.erase(dvndo_int.size() - cssor,
                        cssor); // division por una potencia de B, /B^cssor
      }
      dvndo_int.reduce();
      if (dvsor_int != nat_num_t(dig(0))) {
        dvsor_int.erase(dvsor_int.size() - cssor,
                        cssor); // division por una potencia de B  /B^cssor
      }
      nat_num_t dvsor_fra(dvsor_int);
      dvsor_fra.erase(0, dvsor_int.size() - cssor);
      dvsor_int.reduce();
    } else {
      dvndo_int = nat_num_t(dig(0));
      cthis = dvndo_int;
      return cthis;
    }
    // dvndo_fra.reduce();//dvndo_fra.reduce_fra() HAY QUE HACERLO
    const int szndo = dvndo_int.size();
    const int lsb_ndo = szndo - 1;
    const int msb_ndo = 0;
    const int szsor = dvsor_int.size();
    const int lsb_sor = szsor - 1;
    const int msb_sor = 0;

    // hemos dividido por los ceros del divisor (por una potencia de B)
    // tanto divisor como dividendo, obteniendo dvndo_int y dvsor_int como
    // cocientes enteros.
    div_uno(rem, dvndo_int, dvsor_int, szndo, szsor);
    // ahora hacemos lo mismo con el cociente de las potencias de B del
    // dividendo obteniendo dvndo_fra

    /* *
            RemReal = RemObtenido*(B^cssor) + Dvndo_fra

            rem = rem.insert(rem.size()-1,cssor,0);
            rem += dvndo_fra;
    * */
    //////////if (sgn_ndo!=sgn_sor) dvndo_int.mC_B();
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    cthis = dvndo_int;
    return cthis;
  }

  const nat_num_t &operator%=(const nat_num_t &arg) {
    nat_num_t &cthis = (*this);
    nat_num_t dvndo_int(cthis); // Siempre será positivo
    dvndo_int.reduce();
    nat_num_t rem(dvndo_int);
    rem.reduce();
    nat_num_t dvsor_int(arg); // Siempre será positivo
    dvsor_int.reduce();
    dvndo_int /= dvsor_int;
    dvndo_int *= dvsor_int;
    rem -= dvndo_int;
    cthis = rem;
    return cthis;
  }

  const nat_num_t &operator*=(pardigs a) {
    nat_num_t cthis = (*this);
    nat_num_t &ret = (*this);
    ret *= a.g_uds();
    cthis.push_back(dig(0));
    ret += cthis * a.g_decs();
    ret.reduce();
    return ret;
  }

  const nat_num_t &operator+=(dig arg) {
    nat_num_t &cthis = (*this);
    cthis.reduce();
    dig carry(0);
    pardigs tempt;

    int k = cthis.size();
    tempt.p_uds(cthis[k - 1]);
    tempt += arg;
    cthis[k - 1] = tempt.g_uds();
    carry = tempt.g_decs();
    --k;
    for (; k > 0; --k) {
      tempt = pardigs();
      tempt += carry;
      tempt += cthis[k - 1];
      cthis[k - 1] = tempt.g_uds();
      carry = tempt.g_decs();
    }

    if (carry != dig(0))
      cthis.push_front(carry);
    cthis.reduce();
    return cthis;
  }

  const nat_num_t &operator-=(dig arg) {
    nat_num_t &cthis = (*this);
    cthis.reduce();
    if (arg == dig(0))
      return cthis;
    nat_num_t cpy(nat_num_t(arg).minus(cthis.size()));
    pardigs tempt;
    pardigs tempa;
    sint szt = cthis.size();
    sint k = szt - 1;
    tempt.p_uds(cthis[k]);
    tempt.p_decs(dig(0));
    tempa.p_uds(cpy[k]);
    tempa.p_decs(dig(0));
    tempt += tempa;
    cthis[k] = tempt.g_uds();
    dig carry(tempt.g_decs());
    --k;
    for (; k >= 0; --k) {
      tempt.p_uds(cthis[k]);
      tempt += cpy[k];
      tempt += carry;
      carry = tempt.g_decs();
      cthis[k] = tempt.g_uds();
    }

    cthis.reduce();
    cthis.aux = pardigs();
    return cthis;
  }

  const nat_num_t &operator*=(dig arg) {
    nat_num_t &cthis = (*this);
    pardigs temp;
    dig carry = 0;
    cthis.reduce();
    for (ssint k = ((cthis.size()) - 1); k >= 0; --k) {
      temp.p_uds(cthis[k]);
      temp *= arg;
      temp += carry;
      cthis[k] = temp.g_uds();
      carry = temp.g_decs();
      temp.p_decs(dig(0));
    }
    if (carry != 0)
      push_front(carry);
    cthis.reduce();
    return cthis;
  }

  /****************************/
  /*							*/
  /*	COMPLEMENTO A BASE Y	*/
  /*		BASE MENOS 1		*/
  /*							*/
  /****************************/

  nat_num_t operator-() const {
    nat_num_t cpy(*this);
    cpy.reduce();
    crstriterator start = cpy.rend();
    rstriterator it = cpy.rbegin();
    for (; it != start; ++it) {
      (*it) = (!(*it));
    }
    cpy.reduce();
    it = cpy.rbegin();
    cpy.aux.p_uds(*it);
    cpy.aux.p_decs(dig());
    cpy.aux += pd_1<B>();
    (*it) = cpy.aux.g_uds();
    ++it;
    if ((cpy.aux.g_decs()) != dig(0)) {
      for (; it != start; ++it) {
        cpy.aux.p_uds(cpy.aux.g_decs());
        cpy.aux.p_decs(0);

        if (cpy.aux == pardigs())
          break;
        cpy.aux += pardigs(*it);
        (*it) = cpy.aux.g_uds();
      }
      cpy.push_front(cpy.aux.g_uds());
      cpy.push_front(cpy.aux.g_decs());
    }

    cpy.aux = pardigs();
    cpy.reduce();
    return cpy;
  }

  nat_num_t minus(size_t sz) const {
    nat_num_t cpy(*this);
    cpy.reduce();
    if (cpy.size() < sz) {
      const int tm = sz - cpy.size();
      for (int i = 0; i < tm; ++i) {
        cpy.push_front(dig(0));
      }
    } else if (cpy.size() > sz) {
      cpy.erase(0, 1);
    }
    crstriterator start = cpy.rend();
    rstriterator it = cpy.rbegin();
    for (; it != start; ++it) {
      (*it) = (!(*it));
    }
    it = cpy.rbegin();
    cpy.aux.p_uds(*it);
    cpy.aux.p_decs(dig(0));
    cpy.aux += pd_1<B>();
    (*it) = cpy.aux.g_uds();
    ++it;
    if ((cpy.aux.g_decs()) != dig(0)) {
      for (; it != start; ++it) {
        cpy.aux.p_uds(cpy.aux.g_decs());
        cpy.aux.p_decs(0);

        if (cpy.aux == pardigs())
          break;
        cpy.aux += pardigs(*it);
        (*it) = cpy.aux.g_uds();
      }
      cpy.push_front(cpy.aux.g_uds());
      cpy.push_front(cpy.aux.g_decs());
    }

    cpy.aux = pardigs();
    if (cpy.size() < sz) {
      const int tm = sz - cpy.size();
      for (int i = 0; i < tm; ++i) {
        cpy.push_front(dig(B - 1));
      }
    } else if (cpy.size() > sz) {
      cpy.erase(0, 1);
    }
    // cpy.reduce();
    return cpy;
  }

  nat_num_t operator!() const {
    nat_num_t cpy(*this);
    const striterator fin = cpy.end();
    striterator it = cpy.begin();
    for (; it != fin; ++it)
      (*it) = (!(*it));
    cpy.aux = pardigs();
    cpy.reduce();
    return cpy;
  }

  /****************************/
  /*							*/
  /*		 MODIFICADOR		*/
  /*	COMPLEMENTO A BASE Y 	*/
  /*		BASE MENOS 1		*/
  /*							*/
  /****************************/

  const nat_num_t &mC_B() {
    nat_num_t &cpy = (*this);
    cpy.reduce();
    crstriterator start = cpy.rend();
    rstriterator it = cpy.rbegin();
    for (; it != start; ++it) {
      (*it) = (!(*it));
    }
    cpy.reduce();
    it = cpy.rbegin();
    cpy.aux.p_uds(*it);
    cpy.aux.p_decs(dig());
    cpy.aux += pd_1<B>();
    (*it) = cpy.aux.g_uds();
    ++it;
    if ((cpy.aux.g_decs()) != dig(0)) {
      for (; it != start; ++it) {
        cpy.aux.p_uds(cpy.aux.g_decs());
        cpy.aux.p_decs(0);

        if (cpy.aux == pardigs())
          break;
        cpy.aux += pardigs(*it);
        (*it) = cpy.aux.g_uds();
      }
      cpy.push_front(cpy.aux.g_uds());
      cpy.push_front(cpy.aux.g_decs());
    }

    cpy.aux = pardigs();
    cpy.reduce();
    return cpy;
  }

  const nat_num_t &mC_Bm1() {
    nat_num_t &cpy = (*this);
    const striterator fin = cpy.end();
    striterator it = cpy.begin();
    for (; it != fin; ++it)
      (*it) = (!(*it));
    cpy.aux = pardigs();
    cpy.reduce();
    return cpy;
  }

  /****************************/
  /*							*/
  /*  	   ABSOLUTO			*/
  /*							*/
  /****************************/

  inline nat_num_t abs() const { return (*this); }

  inline const nat_num_t &m_abs() {
    nat_num_t &cthis = (*this);
    return cthis;
  }

  /****************************/
  /*							*/
  /*	DIVIDIR ENTRE BASE o 2	*/
  /*							*/
  /****************************/

  nat_num_t divB() const {
    nat_num_t cpy(*this);
    cpy.reduce();
    cpy.m_abs();
    cpy.cthis.erase(0, 1);
    cpy.reduce();
    return cpy;
  }

  dig remB() const {
    nat_num_t cpy(*this);
    cpy.reduce();
    return cpy[0];
  }

  const nat_num_t &m_divB() {
    nat_num_t &cpy = (*this);
    cpy.reduce();
    cpy.cthis.erase(0, 1);
    cpy.reduce();
    return cpy;
  }

  dig m_remB() {
    nat_num_t &cpy = (*this);
    cpy.reduce();
    return cpy[0];
  }

  nat_num_t div2() const {
    nat_num_t &cthis = (*this);
    nat_num_t dvndo_int(cthis.abs());
    dvndo_int.reduce();
    nat_num_t rem(dvndo_int);
    const dig dos = 2;

    nat_num_t dvsor_int(dos);

    const usint cssor = ((B == 2) ? (1) : (0));

    nat_num_t dvndo_fra(dvndo_int.substr(0, cssor));
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
    /////////////////if (sgn==vminus) dvndo_int.mC_B();
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    return dvndo_int;
  }

  dig rem2() const {
    nat_num_t &cthis = (*this);
    nat_num_t cpy = cthis.reduce();
    cpy.reduce();
    if (B % 2 == 1) {
      if (cpy.size() == 1)
        return dig::Rem2(cpy[0]);
      else {
        usint paridad = 0;
        for (usint k = 0; k < cpy.size(); ++k)
          paridad += dig::Dig2UInt(dig::Rem2(cpy[k]));
        paridad %= 2;
        return dig(paridad);
      }
    } else {
      return Rem2<B>(cpy[0]);
    }
  }

  const nat_num_t &m_div2() {
    nat_num_t &cthis = (*this);
    cthis.reduce();
    nat_num_t &dvndo_int = (*this);
    nat_num_t rem(dvndo_int);
    const dig dos = 2;

    nat_num_t dvsor_int(dos);

    const usint cssor = ((B == 2) ? (1) : (0));

    nat_num_t dvndo_fra(dvndo_int.substr(0, cssor));
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

            rem = rem.insert(0,cssor,0);
            rem += dvndo_fra;
    * */
    /////////////////if (sgn==vminus) dvndo_int.mC_B();
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    return dvndo_int;
  }

  dig m_rem2() {
    nat_num_t &cthis = (*this);
    cthis.reduce();
    nat_num_t &cpy = (*this);
    if (B % 2 == 1) {
      if (cpy.size() == 1)
        return dig::Rem2(cpy[0]);
      else {
        usint paridad = 0;
        for (usint k = 0; k < cpy.size(); ++k)
          paridad += dig::Dig2UInt(dig::Rem2(cpy[k]));
        paridad %= 2;
        return dig(paridad);
      }
    } else {
      return Rem2<B>(cpy[0]);
    }
  }

  dig remBm1() const {
    nat_num_t cthis(*this), suma;
    cthis.abs();
    cthis.reduce();
    suma.reduce();
    suma.insert(0, 1, 0);
    suma.erase(0, (cthis.size()) - 1);
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
  // nat_num_t	 		divBm1() 	const;
  // const nat_num_t	& 	divBm1p()		;

private:
  //		inline void	div3_step(pair< n2digs_t , usint > & S) const;
  //		inline void div3p_step(pair< n2digs_t , usint > & S);
  //		inline void	div7_step(pair< n2digs_t , usint > & S) const;
  //		inline void div7p_step(pair< n2digs_t , usint > & S);
public:
  inline pardigs g_aux() const {
<<<<<<< HEAD
    dig_string_t &cthis = (*this);
=======
    base_num_t &cthis = (*this);
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
    return cthis.aux;
  }
  inline void p_aux(pardigs arg) {
    aux = arg;
    return;
  }

private:
  /****************************/
  /*							*/
  /*		Division Generica	*/
  /*							*/
  /****************************/

  inline void div_gen_step(const nat_num_t &dvsor, nat_num_t &rem,
                           nat_num_t &coc, usint &ndig) const {
    const nat_num_t &cthis = (*this);
    const int szsor = dvsor.size();
    const int maxpossor = szsor - 1;
    const int szndo = cthis.size();
    const int maxposndo = szndo - 1;
    const nat_num_t &dvndo = cthis;
    const uint szrem = rem.size();
    if (ndig == 0)
      ndig = szrem;
    if (rem < dvsor) {
      coc.push_back(dig(0));
      coc.reduce();
    } else if (rem == dvsor) {
      coc.push_back(dig(1));
      coc.reduce();
      rem.erase(0, rem.size() - 1);
      rem[0] = dig(0);
    } else {
      pardigs dighrem;
      if (szrem > szsor)
        dighrem = pardigs(rem[0], rem[1]);
      else
        dighrem = pardigs(dig(0), rem[0]);
      pardigs dighsor = pardigs(dig(0), dvsor[0]);
      pardigs &digcocprueba = dighrem;
      digcocprueba /= dighsor;
      if (digcocprueba > pd_Bm1<B>()) {
        digcocprueba = pd_Bm1<B>();
      }
      nat_num_t remprueba(dvsor);
      remprueba *= digcocprueba;
      for (pardigs ix(0, 0); ix < pardigs(1, 0); ix += pardigs(0, 1)) {
        if (remprueba > rem) {
          --digcocprueba;
          remprueba -= dvsor;
        } else {
          rem -= remprueba;
          coc.push_back(digcocprueba.g_uds()); // g_first, g_second ??
          coc.reduce();
          break;
        }
      }
    }
    if (dvndo.size() > ndig) {
      rem.push_back(dvndo[ndig]);
    }
    rem.reduce();
    ++ndig;
    return;
  }

  /************************************/
  /*							        */
  /*		Un Paso de Division Simple	*/
  /*							        */
  /************************************/
public:
  inline bool es_cero() const {
    bool escero = (size() == 0);
    if (escero)
      return true;
    escero = (size() == 1) and (operator[](0) == dig_t(0));
    if (escero)
      return true;
    return false;
  }

  inline bool no_es_cero() const {
    bool noescero = (size() > 1);
    if (noescero)
      return true;
    noescero = (size() == 1) and (operator[](0) != dig_t(0));
    if (noescero)
      return true;
    return false;
  }

private:
  inline void div_uno(nat_num_t &rem, nat_num_t &dvndo, nat_num_t &dvsor,
                      const usint szndo, const usint szsor) const {
    const nat_num_t &cthis = (*this);
    rem = dvndo;
    if (dvsor.es_cero()) { // caso de division por 0
      return;
    } else if ((dvndo.es_cero()) or
               (szndo <
                szsor)) { // caso de 0 dividido por !=0 ó caso de cociente 0
      rem = dvndo;
      dvndo.erase(0, (cthis.size()) - 2);
      dvndo[0] = dig(0);
      return;
      // rem=dvndo; hecho por defecto
    } else if (dvndo == dvsor) { // caso de dividir por si mismo
      dvndo.clear();
      rem.clear();
      dvndo.push_front(dig(1));
      rem.push_front(dig(0));
      return;
    } else if ((szsor == 1) &&
               (dvsor[0] == 1)) { // caso de dividir por potencias de B (1)
      // dvndo;
      if (rem.size() > 1) {
        rem.erase(0, rem.size() - 2);
      }
      rem[0] = dig(0);
      return;
    } else if ((szndo == szsor) && (dvndo < dvsor)) {
      rem = dvndo;
      dvndo.clear();
      dvndo.push_front(dig(0));
      return;
    } else {
      // ((long_dvndo > long_dvsor) or (dvndo > dvsor))
      // algoritmo de resta general
      // implementar div_step pasamos (resto,cociente,i,dividendo,divisor)
      // devuelve (resto,cociente,i,dividendo,divisor) se puede hacer con una
      // tupla dvndo;
      rem = dvndo;
      rem.reduce();
      rem.erase(szsor, szndo - szsor);
      nat_num_t coc(dig(0));
      usint ndig = 0;
      do {
        div_gen_step(dvsor, rem, coc, ndig);
      } while (ndig <= szndo);
      dvndo = coc;
      return;
    }
  }
  // END PRIVATE

  /****************************/
  /*							*/
  /*		Division Euclidea	*/
  /*							*/
  /****************************/

public:
  pair<nat_num_t, nat_num_t> EuclidDiv(const nat_num_t &arg) const {
    const nat_num_t &cthis = (*this);
    /////////////////const sign_e sgn_ndo = signo;
    /////////////////const sign_e sgn_sor = arg.signo;
    nat_num_t dvndo_int = cthis;
    dvndo_int.reduce();
    nat_num_t dvsor_int = arg.abs();
    dvsor_int.reduce();

    nat_num_t rem(dvndo_int);

    const usint cssor = dvsor_int.ceros_a_la_drcha(); // ¿?

    nat_num_t dvndo_fra(dvndo_int.substr(0, cssor));
    dvsor_int.erase(0, cssor); // division por una potencia de B

    dvsor_int.reduce();
    dvndo_fra.reduce_fracc(); // reduce 0s a la derecha

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

    //////////////////if (sgn_ndo != sgn_sor) dvndo_int.mC_B();
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    return make_pair(rem, dvndo_int);
  }

  pair<nat_num_t, const nat_num_t &> m_EuclidDiv(const nat_num_t &arg) {
    const nat_num_t &cthis = (*this);
    //////////////onst sign_e sgn_ndo = signo;
    //////////////const sign_e sgn_sor = arg.signo;
    cthis.absp();
    cthis.reduce();
    nat_num_t &dvndo_int = cthis;
    nat_num_t dvsor_int = arg.abs();
    dvsor_int.reduce();

    nat_num_t rem(dvndo_int);

    const usint cssor = dvsor_int.ceros_a_la_drcha(); // ¿?

    nat_num_t dvndo_fra(dvndo_int.substr(0, cssor));
    dvsor_int.erase(0, cssor); // division por una potencia de B

    dvsor_int.reduce();
    dvndo_int.reduce();

    dvndo_fra.reduce_fracc();

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

    /////////////////if (sgn_ndo != sgn_sor) dvndo_int.mC_B();
    // rehacer el resto tomando en cuenta los ceros quitados
    // acomodar el formato al signo de la operacion
    // determinar el signo de la operacion
    return make_pair(rem, dvndo_int);
  }

  /************************************/
  /*																	*/
  /*			PRE Y POST
   */
  /*																	*/
  /************************************/

public:
  const nat_num_t &operator++() {
    nat_num_t &cthis = (*this);
    cthis += dig(1);
    return cthis;
  }

  nat_num_t operator++(int) {
    nat_num_t cpThis(*this);
    nat_num_t &cthis = (*this);
    cpThis += dig(1);
    cthis = cpThis;
    return cpThis;
  }

  const nat_num_t &operator--() {
    nat_num_t &cthis = (*this);
    cthis -= dig(1);
    return cthis;
  }

  nat_num_t operator--(int) {
    nat_num_t cpThis(*this);
    nat_num_t &cthis = (*this);
    cpThis -= dig(1);
    cthis = cpThis;
    return cpThis;
  }
  /****************************/
  /*							*/
  /*			REDUCE			*/
  /*							*/
  /****************************/

  inline const nat_num_t &reduce() {
    nat_num_t &cthis = (*this);
    if (cthis.size() == 0) {
      cthis = nat_num_t(dig(0));
      return cthis;
    } else if (cthis.size() == 1)
      return cthis;
    else {
      const usint nsz = digs_no_significativos();
      if (nsz == 0)
        return cthis;
      else {
        const usint pos = 0;
        if (nsz > 0)
          cthis.erase(pos, nsz);
        return cthis;
      }
    }
  }

  inline nat_num_t reduce() const {
    const nat_num_t &cthis = (*this);
    nat_num_t cpyreducida(cthis);
    if (cpyreducida.size() == 0) {
      cpyreducida = nat_num_t(dig(0));
      return cpyreducida;
    } else if (cpyreducida.size() == 1)
      return cpyreducida;
    else {
      const usint nsz = cpyreducida.digs_no_significativos();
      if (nsz == 0)
        return cpyreducida;
      else {
        const usint pos = 0;
        if (nsz > 0)
          cpyreducida.erase(pos, nsz);
        return cpyreducida;
      }
    }
  }

  inline const nat_num_t &reduce_fracc() {
    nat_num_t &cthis = (*this);
    if (cthis.size() == 0) {
      cthis = nat_num_t(dig(0));
      return cthis;
    } else if (cthis.size() == 1)
      return cthis;
    else {
      const usint nsz = digs_fracc_no_significativos();
      if (nsz == 0)
        return cthis;
      else {
        const usint pos = 0;
        cthis.erase(pos, nsz);
        return cthis;
      }
    }
  }

  inline nat_num_t reduce_fracc() const {
    const nat_num_t &cthis = (*this);
    nat_num_t cpyreducida(cthis);
    if (cpyreducida.size() == 0) {
      cpyreducida = nat_num_t(dig(0));
      return cpyreducida;
    } else if (cpyreducida.size() == 1)
      return cpyreducida;
    else {
      const usint nsz = cpyreducida.digs_fracc_no_significativos();
      if (nsz == 0)
        return cpyreducida;
      else {
        const usint pos = 0;
        cpyreducida.erase(pos, nsz);
        return cpyreducida;
      }
    }
  }
};

/****************************/
/*							*/
/*		ISTREAM Y OSTREAM	*/
/*							*/
/****************************/

// uint#:dig:dig:#B
template <const uchint Base>
istream &operator>>(istream &is, nat_num_t<Base> &arg) {
  enum estado_e { e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13 };
  vector<string> num(255);
  string sds;
  string num_digint;
  string num_base;
  usint numero_base_recogido = 0;
  usint ind_sds = 0;
  usint digint = 0;
  usint ind_num = 0;
  estado_e est_act = e0;
  char c;
  is >> sds;
  do {
    c = sds[ind_sds];
    switch (est_act) {
    case e0: {
      num_digint.clear();
      num_base.clear();
      numero_base_recogido = 0;
      digint = 0;
      ind_num = 0;
    }
      if (c == 'u')
        est_act = e1;
      break;

    case e1:
      if (c == 'i')
        est_act = e2;
      else
        est_act = e0;
      break;

    case e2:
      if (c == 'n')
        est_act = e3;
      else
        est_act = e0;
      break;

    case e3:
      if (c == 't')
        est_act = e4;
      else
        est_act = e0;
      break;

    case e4:
      if (c == '#')
        est_act = e5;
      else
        est_act = e0;
      break;

    case e5:
      if ((c >= '1') and (c <= '9')) {
        num[ind_num].push_back(c - '0');
        est_act = e6;
      } else
        est_act = e0;
      break;
    case e6:
      if ((c >= '0') and (c <= '9')) {
        num[ind_num].push_back(c - '0');
      } else if (c == ':') {
        est_act = e7;
        ++ind_num;
      } else if (c == '#') {
        est_act = e8;
        ++ind_num;
      } else
        est_act = e0;
      break;
    case e7:
      if ((c >= '0') and (c <= '9')) {
        est_act = e6;
        num[ind_num].push_back(c - '0');
      } else
        est_act = e0;
      break;
    case e8:
      if (c == 'B') {
        est_act = e9;
      } else
        est_act = e0;
      break;
    case e9:
      if ((c <= '9') and (c >= '2')) {
        est_act = e10;
        num_base.push_back(c - '0');
      } else if (c == '1') {
        est_act = e11;
        num_base.push_back(1);
      } else if (c == ' ' || c == '\0')
        est_act = e12;
      else
        est_act = e0;
      break;
    case e10:
      if ((c <= '9') and (c >= '0'))
        num_base.push_back(c - '0');
      else if (c == ' ' || c == '\0')
        est_act = e12;
      else
        est_act = e0;
      break;
    case e11:
      if ((c <= '9') and (c >= '0')) {
        est_act = e9;
        num_base.push_back(c - '0');
      } else if (c == ' ' || c == '\0')
        est_act = e12;
      else
        est_act = e0;
      break;
    case e12:
      for (uint k = 0; k < num_base.size(); ++k) {
        numero_base_recogido *= 10;
        numero_base_recogido += num_base[k];
      }
      if (numero_base_recogido != Base)
        est_act = e0;
      else
        est_act = e13;
    case e13:
      break;
    default:
      est_act = e0;
    }
    ++ind_sds;
  } while ((est_act != e13) and (c != '\0'));

  arg.clear();
  uchint numero;
  for (uchint j = 0; j < ind_num; ++j) {
    numero = 0;
    for (uint k = 0; k < num[j].size(); ++k) {
      numero *= 10;
      numero += num[j][k];
    }
    arg.push_back(dig_t<Base>(numero));
  }
  arg.p_aux(pardigs_t<Base>());
  return is;
}

template <const uchint Base>
ostream &operator<<(ostream &os, const nat_num_t<Base> &arg) {
  usint sz = arg.size();
  os << "uint#";
  for (int k = 0; k < sz; ++k) {
    if (k == 0)
      os << arg[k].Dig2Int();
    else
      os << ":" << arg[k].Dig2Int();
  }
  os << "#B" << static_cast<int>(Base);
  return os;
}

#endif // NAT_NUM_T__HPP__INCLUDED
