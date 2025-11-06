# CTestCustom.cmake - Configuración personalizada de CTest para NumericRepresentations

# Configuración de output
set(CTEST_CUSTOM_MAXIMUM_FAILED_TEST_OUTPUT_SIZE "1000000")
set(CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE "1000000")

message(STATUS "CTest Custom configuration loaded")
message(STATUS "Looking for MSVC-compiled executables with *_extended.exe pattern")