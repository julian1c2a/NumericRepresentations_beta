@echo off
C:\msys64\ucrt64\bin\g++.exe -std=c++23 -I./include -c test_minimal_dig.cpp -o test_minimal_dig.o > compile_log.txt 2>&1
echo Exit Code: %ERRORLEVEL% >> compile_log.txt