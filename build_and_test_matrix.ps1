# PowerShell script para automatizar la matriz multi-compilador con CMake
# Crea y compila en carpetas separadas para MSVC, GCC y Clang, y ejecuta todos los tests

$ErrorActionPreference = 'Stop'

$root = Split-Path -Parent $MyInvocation.MyCommand.Definition
cd $root

$compilers = @(
    @{ name = 'msvc'; generator = 'Visual Studio 17 2022'; cmake_args = '' },
    @{ name = 'gcc';  generator = 'MinGW Makefiles'; cmake_args = '-G "MinGW Makefiles"' },
    @{ name = 'clang'; generator = 'Ninja'; cmake_args = '-G "Ninja" -DCMAKE_CXX_COMPILER=clang++' }
)

foreach ($c in $compilers) {
    $buildDir = "build_$($c.name)"
    if (!(Test-Path $buildDir)) { mkdir $buildDir | Out-Null }
    Write-Host "\n=== Configurando y compilando para $($c.name.ToUpper()) ===" -ForegroundColor Cyan
    Push-Location $buildDir
    if ($c.name -eq 'msvc') {
        cmake .. -G "Visual Studio 17 2022" | Write-Host
        cmake --build . --config Release | Write-Host
    } else {
        cmake .. $($c.cmake_args) | Write-Host
        cmake --build . | Write-Host
    }
    Write-Host "\n--- Ejecutando tests para $($c.name.ToUpper()) ---" -ForegroundColor Yellow
    ctest --output-on-failure | Write-Host
    Pop-Location
}

Write-Host "\nMatriz multi-compilador completada." -ForegroundColor Green
