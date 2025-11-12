@echo off
echo === Configurando Visual Studio 2022 Environment ===
call "D:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x64

if not exist build_test mkdir build_test

echo.
echo === Compilando test_pack2array.cpp ===
cl /EHsc /std:c++latest /I include /I tmp\\Catch2\\src /I build-gcc\\_deps\\catch2-build\\generated-includes /c tests\\test_pack2array.cpp /Fo:build_test\\test_pack2array.obj
cl /EHsc /std:c++latest /I tmp\\Catch2\\src /I build-gcc\\_deps\\catch2-build\\generated-includes /c tmp\\Catch2\\extras\\catch_amalgamated.cpp /Fo:build_test\\catch_amalgamated.obj
link /out:build_test\\test_pack2array.exe build_test\\test_pack2array.obj build_test\\catch_amalgamated.obj

if %ERRORLEVEL% EQU 0 (
    echo.
    echo === Ejecutando tests ===
    build_test\\test_pack2array.exe
) else (
    echo Error en compilacion
)

pause
