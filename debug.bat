@echo off
call "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
cl /EHsc /std:c++latest /I.\include debug_large.cpp /Fe:debug_large.exe
if %ERRORLEVEL% EQU 0 (
    debug_large.exe
)