# CMake generated Testfile for 
# Source directory: D:/GDrive/NumericRepresentations/tests
# Build directory: D:/GDrive/NumericRepresentations/build-gcc/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(AuxiliaryFunctionsTest "D:/GDrive/NumericRepresentations/build-gcc/build_tests/gcc/AuxiliaryFunctionsTest.exe")
set_tests_properties(AuxiliaryFunctionsTest PROPERTIES  LABELS "core;auxiliary" _BACKTRACE_TRIPLES "D:/GDrive/NumericRepresentations/tests/CMakeLists.txt;41;add_test;D:/GDrive/NumericRepresentations/tests/CMakeLists.txt;0;")
subdirs("../_deps/catch2-build")
