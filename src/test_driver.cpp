
#include "../include/testunit.hpp"
#include <clocale>
#include <windows.h>

namespace NumRepr { /// BEGIN OF NAMESPACE NUMREPR

namespace testing { /// BEGIN OF NAMESPACE TESTING

constexpr ullint_t B1{10u};
constexpr size_t L1{3};
//--------------------------
constexpr ullint_t B2{2u};
constexpr size_t L2{13};
//--------------------------
constexpr ullint_t B3{23u};
constexpr size_t L3{3};
//--------------------------
constexpr ullint_t B4{5u};
constexpr size_t L4{7};
//--------------------------
constexpr ullint_t B5{3u};
constexpr size_t L5{10};
//--------------------------
constexpr ullint_t B6{12u};
constexpr size_t L6{4};
//--------------------------
constexpr ullint_t B7{8u};
constexpr size_t L7{6};
//--------------------------
constexpr ullint_t B8{16u};
constexpr size_t L8{4};

using rd_1_t [[maybe_unused]] = reg_digs_t<B1, L1>;
using dig1_t [[maybe_unused]] = dig_t<B1>;
using rd_2_t [[maybe_unused]] = reg_digs_t<B2, L2>;
using dig2_t [[maybe_unused]] = dig_t<B2>;
using rd_3_t [[maybe_unused]] = reg_digs_t<B3, L3>;
using dig3_t [[maybe_unused]] = dig_t<B3>;
using rd_4_t [[maybe_unused]] = reg_digs_t<B4, L4>;
using dig4_t [[maybe_unused]] = dig_t<B4>;
using rd_5_t [[maybe_unused]] = reg_digs_t<B5, L5>;
using dig5_t [[maybe_unused]] = dig_t<B5>;
using rd_6_t [[maybe_unused]] = reg_digs_t<B6, L6>;
using dig6_t [[maybe_unused]] = dig_t<B6>;
using rd_7_t [[maybe_unused]] = reg_digs_t<B7, L7>;
using dig7_t [[maybe_unused]] = dig_t<B7>;
using rd_8_t [[maybe_unused]] = reg_digs_t<B8, L8>;
using dig8_t [[maybe_unused]] = dig_t<B8>;

[[maybe_unused]] constexpr auto B2L_1{Base_pow_to_Size<B1, L1>()};
[[maybe_unused]] constexpr auto B2L_2{Base_pow_to_Size<B2, L2>()};
[[maybe_unused]] constexpr auto B2L_3{Base_pow_to_Size<B3, L3>()};
[[maybe_unused]] constexpr auto B2L_4{Base_pow_to_Size<B4, L4>()};
[[maybe_unused]] constexpr auto B2L_5{Base_pow_to_Size<B5, L5>()};
[[maybe_unused]] constexpr auto B2L_6{Base_pow_to_Size<B6, L6>()};
[[maybe_unused]] constexpr auto B2L_7{Base_pow_to_Size<B7, L7>()};
[[maybe_unused]] constexpr auto B2L_8{Base_pow_to_Size<B8, L8>()};

void show_test_convert_to_int_driver() {
  int a{-1}, b{-1}, c{-1}, d{-1}, e{-1}, f{-1}, g{-1}, h{-1};
  std::setlocale(LC_ALL,"es_ES");
  SetConsoleCP(1252);
  SetConsoleOutputCP(1252);

  std::wcout << L"show_test_convert_to_int<Bn,Ln>(); \n";

  std::wcout
  << L"Si quieres que corra la opción B == " << B1 << L",L == " << L1 << L" pulsa (1) \n"
  << L"Si quieres que corra la opción B == " << B2 << L",L == " << L2 << L" pulsa (2) \n"
  << L"Si quieres que corra la opción B == " << B3 << L",L == " << L3 << L" pulsa (3) \n"
  << L"Si quieres que corra la opción B == " << B4 << L",L == " << L4 << L" pulsa (4) \n"
  << L"Si quieres que corra la opción B == " << B5 << L",L == " << L5 << L" pulsa (5) \n"
  << L"Si quieres que corra la opción B == " << B6 << L",L == " << L6 << L" pulsa (6) \n"
  << L"Si quieres que corra la opción B == " << B7 << L",L == " << L7 << L" pulsa (7) \n"
  << L"Si quieres que corra la opción B == " << B8 << L",L == " << L8 << L" pulsa (8) \n"
  << L"Si quieres que corra varias opciones pulsa los números "
  << L"correspondientes separados por espacios \n"
  << L"Si quieres que salte este test al completo pulsa (0) \n";

  std::cin >> a >> b >> c >> d >> e >> f >> g >> h;
  if ((a != 0) && (b != 0) && (c != 0) && (d != 0) && (e != 0) && (f != 0) &&
      (g != 0) && (h != 0)) {
    if ((a == 1) || (b == 1) || (c == 1) || (d == 1) || (e == 1) || (f == 1) ||
        (g == 1) || (h == 1))
      testing::reg_digs::show_test_convert_to_int<B1, L1>();
    if ((a == 2) || (b == 2) || (c == 2) || (d == 2) || (e == 2) || (f == 2) ||
        (g == 2) || (h == 2))
      testing::reg_digs::show_test_convert_to_int<B2, L2>();
    if ((a == 3) || (b == 3) || (c == 3) || (d == 3) || (e == 3) || (f == 3) ||
        (g == 3) || (h == 3))
      testing::reg_digs::show_test_convert_to_int<B3, L3>();
    if ((a == 4) || (b == 4) || (c == 4) || (d == 4) || (e == 4) || (f == 4) ||
        (g == 4) || (h == 4))
      testing::reg_digs::show_test_convert_to_int<B4, L4>();
    if ((a == 5) || (b == 5) || (c == 5) || (d == 5) || (e == 5) || (f == 5) ||
        (g == 5) || (h == 5))
      testing::reg_digs::show_test_convert_to_int<B5, L5>();
    if ((a == 6) || (b == 6) || (c == 6) || (d == 6) || (e == 6) || (f == 6) ||
        (g == 6) || (h == 6))
      testing::reg_digs::show_test_convert_to_int<B6, L6>();
    if ((a == 7) || (b == 7) || (c == 7) || (d == 7) || (e == 7) || (f == 7) ||
        (g == 7) || (h == 7))
      testing::reg_digs::show_test_convert_to_int<B7, L7>();
    if ((a == 8) || (b == 8) || (c == 8) || (d == 8) || (e == 8) || (f == 8) ||
        (g == 8) || (h == 8))
      testing::reg_digs::show_test_convert_to_int<B8, L8>();
  }
  return;
}

} /// END OF NAMESPACE TESTING

} /// END OF NAMESPACE NUMREPR
