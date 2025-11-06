# CMake generated Testfile for 
# Source directory: D:/GDrive/NumericRepresentations
# Build directory: D:/GDrive/NumericRepresentations/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[nat_reg_digs_basic_methods]=] "D:/GDrive/NumericRepresentations/build/test_nat_basic_methods.exe")
set_tests_properties([=[nat_reg_digs_basic_methods]=] PROPERTIES  LABELS "nat_reg_digs_t;basic;phase1" TIMEOUT "30" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/CMakeLists.txt;102;add_test;D:/GDrive/NumericRepresentations/CMakeLists.txt;0;")
add_test([=[nat_reg_digs_factory_methods]=] "D:/GDrive/NumericRepresentations/build/test_nat_factory_methods.exe")
set_tests_properties([=[nat_reg_digs_factory_methods]=] PROPERTIES  LABELS "nat_reg_digs_t;factory;phase2" TIMEOUT "30" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/CMakeLists.txt;115;add_test;D:/GDrive/NumericRepresentations/CMakeLists.txt;0;")
add_test([=[nat_reg_digs_constructors]=] "D:/GDrive/NumericRepresentations/build/test_nat_constructors.exe")
set_tests_properties([=[nat_reg_digs_constructors]=] PROPERTIES  LABELS "nat_reg_digs_t;constructors;phase3" TIMEOUT "30" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/CMakeLists.txt;128;add_test;D:/GDrive/NumericRepresentations/CMakeLists.txt;0;")
add_test([=[nat_reg_digs_set_operations]=] "D:/GDrive/NumericRepresentations/build/test_nat_set_operations.exe")
set_tests_properties([=[nat_reg_digs_set_operations]=] PROPERTIES  LABELS "nat_reg_digs_t;set_operations;phase4" TIMEOUT "30" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/CMakeLists.txt;141;add_test;D:/GDrive/NumericRepresentations/CMakeLists.txt;0;")
add_test([=[nat_reg_digs_assignment_operators]=] "D:/GDrive/NumericRepresentations/build/test_nat_assignment_operators.exe")
set_tests_properties([=[nat_reg_digs_assignment_operators]=] PROPERTIES  LABELS "nat_reg_digs_t;assignment;operators;phase5" TIMEOUT "30" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/CMakeLists.txt;154;add_test;D:/GDrive/NumericRepresentations/CMakeLists.txt;0;")
add_test([=[nat_reg_digs_arithmetic_operators]=] "D:/GDrive/NumericRepresentations/build/test_nat_arithmetic_operators.exe")
set_tests_properties([=[nat_reg_digs_arithmetic_operators]=] PROPERTIES  LABELS "nat_reg_digs_t;arithmetic;operators;phase6" TIMEOUT "45" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/CMakeLists.txt;167;add_test;D:/GDrive/NumericRepresentations/CMakeLists.txt;0;")
add_test([=[nat_reg_digs_comparison_operators]=] "D:/GDrive/NumericRepresentations/build/test_nat_comparison_operators.exe")
set_tests_properties([=[nat_reg_digs_comparison_operators]=] PROPERTIES  LABELS "nat_reg_digs_t;comparison;operators;phase7" TIMEOUT "30" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/CMakeLists.txt;180;add_test;D:/GDrive/NumericRepresentations/CMakeLists.txt;0;")
add_test([=[nat_reg_digs_io_operations]=] "D:/GDrive/NumericRepresentations/build/test_nat_io_operations.exe")
set_tests_properties([=[nat_reg_digs_io_operations]=] PROPERTIES  LABELS "nat_reg_digs_t;io_operations;strings;phase8" TIMEOUT "30" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/CMakeLists.txt;193;add_test;D:/GDrive/NumericRepresentations/CMakeLists.txt;0;")
add_test([=[int_reg_digs_ultra_minimal]=] "D:/GDrive/NumericRepresentations/build/test_int_ultra_minimal_exe.exe")
set_tests_properties([=[int_reg_digs_ultra_minimal]=] PROPERTIES  LABELS "int_reg_digs_t;basic;minimal;phase1" TIMEOUT "30" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/CMakeLists.txt;210;add_test;D:/GDrive/NumericRepresentations/CMakeLists.txt;0;")
add_test([=[int_reg_digs_basic_methods]=] "D:/GDrive/NumericRepresentations/build/test_int_basic_methods_exe.exe")
set_tests_properties([=[int_reg_digs_basic_methods]=] PROPERTIES  LABELS "int_reg_digs_t;basic;methods" TIMEOUT "30" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/CMakeLists.txt;223;add_test;D:/GDrive/NumericRepresentations/CMakeLists.txt;0;")
add_test([=[basic_test]=] "D:/GDrive/NumericRepresentations/build/test_basic.exe")
set_tests_properties([=[basic_test]=] PROPERTIES  LABELS "auxiliary;utilities" TIMEOUT "20" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/CMakeLists.txt;239;add_test;D:/GDrive/NumericRepresentations/CMakeLists.txt;0;")
add_test([=[minimal_factory_test]=] "D:/GDrive/NumericRepresentations/build/test_minimal_factory_exe.exe")
set_tests_properties([=[minimal_factory_test]=] PROPERTIES  LABELS "utilities;factory;minimal" TIMEOUT "20" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/CMakeLists.txt;249;add_test;D:/GDrive/NumericRepresentations/CMakeLists.txt;0;")
