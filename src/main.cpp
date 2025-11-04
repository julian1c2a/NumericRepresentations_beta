#include <clocale>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include "../include/dig_t.hpp"
#include "../include/digit_variant_t.hpp"
//#include "../include/testunit.hpp"
#include "../include/memory_handler.hpp"
//#include "../include/register_variant_t.hpp"



using namespace std::literals;
//using digit_variant = typename NumRepr::digit_variant;
using digit_varlist_t = typename NumRepr::MemHand::digit_varlist_t;
using ullint_varlist_t = typename NumRepr::MemHand::ullint_varlist_t;
using llint_varlist_t = typename NumRepr::MemHand::llint_varlist_t;
using ld_varlist_t = typename NumRepr::MemHand::ld_varlist_t;

//using NumRepr::register_variant_t;
//#include "../include/testunit.hpp"
//#include "../include/memory_handler.hpp"
#include "../include/variant_types.hpp"


using namespace std::literals;
//using genRadixDig_t = typename NumRepr::memory_handler::genRadixDig_t;

/// PARA CUANDO LOS *.O SEAN DEMASIADO GRANDES:
///    -Wa,-??? (archivos grandes de ensamblador)
///    --param ggc-min-expand=0 --param ggc-min-heapsize=4096

//template<std::uint64_t IX>
//using dig_t = typename NumRepr::dig_t<IX>;
//
//using dig2_t  = dig_t<2>;
//using dig10_t = dig_t<10>;
//using digF_t  = dig_t<16>;
//using dig60_t = dig_t<60>;
//using digPI_t = dig_t<180>;
//using digFA_t = dig_t<210>;
//using digFF_t = dig_t<255>;

//using typename NumRepr::digit_variant;
=======
template<std::uint64_t IX>
using dig_t = typename NumRepr::dig_t<IX>;

using dig2_t  = dig_t<2>;
using dig10_t = dig_t<10>;
using digF_t  = dig_t<16>;
using dig60_t = dig_t<60>;
using digPI_t = dig_t<180>;
using digFA_t = dig_t<210>;
using digFF_t = dig_t<255>;

using NumRepr::memory_handler::varRadixDig_t;
//using dig_var_list = typename NumRepr::memory_handler::dig_var_list;
//using int_var_list = typename NumRepr::memory_handler::int_var_list;
//using nat_var_list = typename NumRepr::memory_handler::nat_var_list;

int main() {
  //  COMIENZO PARA PONER ESPAÑOL EN CONSOLA
  //
  std::setlocale(LC_ALL,"es_ES");  	// Cambiar locale - Suficiente para máquinas Linux
  SetConsoleCP(1252);         		// Cambiar STDIN -  Para máquinas Windows
  SetConsoleOutputCP(1252);   		// Cambiar STDOUT - Para máquinas Windows
  //
  // FINAL PARA PONER ESPAÑOL EN CONSOLA
  //register_variant_t regvariant{NumRepr::make_register_variant(10,16,237)};
  //register_variant_t regvariant_2{NumRepr::getobject_register_variant(10,16,237)};
  ////////////////////////////////////////////////////////
  ullint_varlist_t ull_vlst;
  ull_vlst.create_var("A"s,13);
  std::cout << ull_vlst("A"s) << '\n';
  ////////////////////////////////////////////////////////
  llint_varlist_t ll_vlst;
  ll_vlst.create_var("B"s,-2356);
  std::cout << ll_vlst("B"s) << '\n';
  ////////////////////////////////////////////////////////
  ld_varlist_t ld_vlst;
  ld_vlst.create_var("C"s,-2356.3459890L);
  std::cout << ld_vlst("C"s) << '\n';
  ////////////////////////////////////////////////////////
  digit_varlist_t dig_vlst;
  dig_vlst.create_var("D"s,41,-34);
  std::cout << dig_vlst("D"s) << '\n';
  ////////////////////////////////////////////////////////

/*
  digit_variant A{dig_t<10>{0}};
  //std::cout << std::visit(varRadixDig_t::preincr(),A) << std::endl;
=======
  std::setlocale(LC_ALL,"es_ES");  // Cambiar locale - Suficiente para máquinas Linux
  SetConsoleCP(1252);         // Cambiar STDIN -  Para máquinas Windows
  SetConsoleOutputCP(1252);   // Cambiar STDOUT - Para máquinas Windows
  //
  // FINAL PARA PONER ESPAÑOL EN CONSOLA

  varRadixDig_t A{dig_t<10>{0}};
  std::cout << std::visit(varRadixDig_t::preincr(),A) << std::endl;
>>>>>>> 1e470d87efdd6e85008cd373a077b8ffc6dcf33e
  std::cout <<   A << std::endl;
  std::cout << ++A << std::endl;
  std::cout << ++A << std::endl;
  std::cout << ++A << std::endl;
  std::cout << ++A << std::endl;
  std::cout << ++A << std::endl;
  std::cout << ++A << std::endl;
  std::cout << ++A << std::endl;
  std::cout << ++A << std::endl;
  std::cout << ++A << std::endl;
  std::cout << ++A << std::endl;
  std::cout << ++A << std::endl;
  digit_variant B{dig_t<23>{0}};
  varRadixDig_t B{dig_t<23>{0}};
  std::cout <<   B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << ++B << std::endl;
  std::cout << --A << std::endl;
  std::cout << --A << std::endl;
  std::cout << --A << std::endl;
  std::cout << --A << std::endl;
  std::cout << --A << std::endl;
  std::cout << --A << std::endl;
  std::cout << --A << std::endl;
  std::cout << --A << std::endl;
  std::cout << --A << std::endl;
  std::cout << --A << std::endl;
  std::cout << --A << std::endl;
  std::cout << --A << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << --B << std::endl;
  std::cout << A++ << std::endl;
  std::cout << A++ << std::endl;
  std::cout << A++ << std::endl;
  std::cout << A++ << std::endl;
  std::cout << A++ << std::endl;
  std::cout << A++ << std::endl;
  std::cout << A++ << std::endl;
  std::cout << A++ << std::endl;
  std::cout << A++ << std::endl;
  std::cout << A++ << std::endl;
  std::cout << A++ << std::endl;
  std::cout << A++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << B++ << std::endl;
  std::cout << A-- << std::endl;
  std::cout << A-- << std::endl;
  std::cout << A-- << std::endl;
  std::cout << A-- << std::endl;
  std::cout << A-- << std::endl;
  std::cout << A-- << std::endl;
  std::cout << A-- << std::endl;
  std::cout << A-- << std::endl;
  std::cout << A-- << std::endl;
  std::cout << A-- << std::endl;
  std::cout << A-- << std::endl;
  std::cout << A-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
  std::cout << B-- << std::endl;
*/


//std::cout << --A << std::endl;std::cout << --A << std::endl;  dig_var_list varlist;
//std::cout << --A << std::endl;std::cout << --A << std::endl;  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//std::cout << --A << std::endl;std::cout << --A << std::endl;  std::cout << '\n';
//std::cout << --A << std::endl;std::cout << --A << std::endl;  create_var(varlist,"A",10,7);
//std::cout << --A << std::endl;std::cout << --A << std::endl;  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//std::cout << --A << std::endl;std::cout << --A << std::endl;  std::cout << '\n';
//std::cout << --A << std::endl;std::cout << --A << std::endl;  create_var(varlist,"B",10,6);
//std::cout << --A << std::endl;std::cout << --A << std::endl;  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//std::cout << --A << std::endl;std::cout << --A << std::endl;  std::cout << '\n';
//std::cout << --A << std::endl;std::cout << --A << std::endl;  create_var(varlist,"C",10,0);
//std::cout << --A << std::endl;std::cout << --B << std::endl;  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << " Creación de variables con valores explícitos o por defecto [BASE 10]:\n "s;
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << "Variable A : "s << std::get<10>(varlist("A")) << std::endl;
//std::cout << --B << std::endl;std::cout << --B << std::endl;  //std::cout << " get_radix_of_type me devuelve : " << get_radix_of_type(varlist("A")) << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << " std::variant::index me devuelve : " << varlist("A").index() << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << "Variable B : "s << std::get<10>(varlist("B")) << std::endl;
//std::cout << --B << std::endl;std::cout << --B << std::endl;  //std::cout << " get_radix_of_type me devuelve : " << get_radix_of_type(varlist("B")) << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << " std::variant::index me devuelve : " << varlist("B").index() << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << "Variable C : "s << std::get<10>(varlist("C")) << std::endl;
//std::cout << --B << std::endl;std::cout << --B << std::endl;  //std::cout << " get_radix_of_type me devuelve : " << get_radix_of_type(varlist("C")) << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << " std::variant::index me devuelve : " << varlist("C").index() << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  create_var(varlist,"E",63,7);
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  create_var(varlist,"F",63,6);
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  create_var(varlist,"G",63,0);
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//std::cout << --B << std::endl;std::cout << --B << std::endl;  std::cout << '\n';
//std::cout << --B << std::endl;  std::cout << " Creación de variables con valores explícitos o por defecto [BASE 255]:\n "s;
//  std::cout << '\n';
//  std::cout << "Variable E : "s << std::get<63>(varlist("E")) << std::endl;
//  //std::cout << " get_radix_of_type me devuelve : " << get_radix_of_type(varlist("E")) << '\n';
//  std::cout << " std::variant::index me devuelve : " << varlist("E").index() << '\n';
//  std::cout << '\n';
//  std::cout << "Variable F : "s << std::get<63>(varlist("F")) << std::endl;
//  //std::cout << " get_radix_of_type me devuelve : " << get_radix_of_type(varlist("F")) << '\n';
//  std::cout << " std::variant::index me devuelve : " << varlist("F").index() << '\n';
//  std::cout << '\n';
//  std::cout << "Variable G : "s << std::get<63>(varlist("G")) << std::endl;
//  //std::cout << " get_radix_of_type me devuelve : " << get_radix_of_type(varlist("G")) << '\n';
//  std::cout << " std::variant::index me devuelve : " << varlist("G").index() << '\n';
//  std::cout << '\n';
//  std::cout << '\n';
//  std::cout << " Asignación de variables con operaciones de otras variables:\n "s;
//  create_var(varlist,"H",60,20);
//  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//  std::cout << '\n';
//  create_var(varlist,"I",60,36);
//  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//  std::cout << '\n';
//  create_var(varlist,"J",60,209);
//  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//  std::cout << '\n';
//  std::cout << " Creación de variables con valores explícitos o por defecto [BASE 210]:\n "s;
//  std::cout << '\n';
//  std::cout << "Variable H : "s << std::get<60>(varlist("H")) << std::endl;
//  //std::cout << " get_radix_of_type me devuelve : " << get_radix_of_type(varlist("H")) << '\n';
//  std::cout << " std::variant::index me devuelve : " << varlist("H").index() << '\n';
//  std::cout << '\n';
//  std::cout << "Variable I : "s << std::get<60>(varlist("I")) << std::endl;
//  //std::cout << " get_radix_of_type me devuelve : " << get_radix_of_type(varlist("I")) << '\n';
//  std::cout << " std::variant::index me devuelve : " << varlist("I").index() << '\n';
//  std::cout << '\n';
//  std::cout << "Variable J : "s << std::get<60>(varlist("J")) << std::endl;
//  //std::cout << " get_radix_of_type me devuelve : " << get_radix_of_type(varlist("J")) << '\n';
//  std::cout << " std::variant::index me devuelve : " << varlist("J").index() << '\n';
//  std::cout << '\n';
//  std::cout << '\n';
//  varlist.erase_var("A");
//  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//  std::cout << '\n';
//  varlist.erase_var("B");
//  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//  std::cout << '\n';
//  varlist.erase_var("C");
//  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//  std::cout << '\n';
//  varlist.erase_var("E");
//  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//  std::cout << '\n';
//  varlist.erase_var("F");
//  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//  std::cout << '\n';
//  varlist.erase_var("G");
//  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//  std::cout << '\n';
//  varlist.erase_var("H");
//  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//  std::cout << '\n';
//  varlist.erase_var("I");
//  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//  std::cout << '\n';
//  varlist.erase_var("J");
//  std::cout << "varlist.size() == "  << varlist.size() << '\n';
//  std::cout << '\n';
//
//  std::cout << " Asignación de variables con operaciones de otras variables:\n "s;
//  std::cout << std::make_pair(std::ref(varlist),"A") << " += " << std::make_pair(varlist,"B") << '\n';
//  bool hecho{suma_y_asigna(std::ref(varlist),"A","B")};
//  if (hecho)
//  	std::cout << std::make_pair(std::ref(varlist),"A") << '\n';
//  else
//  	std::cout << "Algo ha ido mal.\n";

//  {
//  std::ofstream file("variant.txt");
//  file << "std::variant<std::monostate,";
//  for(int i=2 ; i < 255 ; ++i)
//  	file << "dig_t<" << i << ">,";
//  file << "dig_t<" << 255 << "> >";
//  file.close();
//  }

//  {
//  std::ofstream file("get.txt");
//  file << "std::variant<std::monostate,";
//  for(int i=2 ; i < 256 ; ++i)
//  	file << "        case " << i << " : return std::get<" << i << ">(arg).radix();\n";
//  file.close();
//  }

//	{
//    	std::ofstream file("switch_add_n_assign.txt");
//    	for(int i=2 ; i < 64 ; ++i)
//  		  file
//  		  		<< "\tcase   "
//  		  		<< i
//  		  		<< " :\n"
//  		  		<< "\t{\n"
//  		  		<<"\t\t\tdig_t<"
//  		  		<< i
//  		  		<< "> var_nombre{std::get<"
//  		  		<< i
//  		  		<< ">(cont(nombre))};\n"
//  		  		<< "\t\t\tconst dig_t<"
//  		  		<< i
//  		  		<< "> var_otronombre{std::get<"
//  		  		<< i
//  		  		<< ">(cont(otronombre))};\n"
//  		  		<< "\t\t\tvar_nombre += var_otronombre;\n"
//  		  		<< "\t\t\tcont(nombre,var_nombre);\n"
//  		  		<< "\t\t\treturn true;\n"
//  		  		<< "\t}\n";
//    	file.close();
//	}
//	{
//		std::ofstream file("variant_to_string.txt");
//		for(int i=2 ; i < 64 ; ++i){
//			file << "\t\t\tcase " << i << " : return (std::get<" << i << ">(*this)).to_string();\n";
//		}
//		file.close();
//	}
//	{
//		std::ofstream file("increments.txt");
//		for(int i=2 ; i < 64 ; ++i) {
//			file << "case  " << i << " : {dig_t< " << i << ">& este{std::get< " << i << ">(*this)};++este;return (*this);}\n";
//		}
//		file.close();
//	}

  	return 0;
}
