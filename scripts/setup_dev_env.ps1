# NumericRepresentations - Multi-Compiler Development Environment Setup
# Configura MSVC, Clang y GCC para el proyecto

param(
    [Parameter(HelpMessage="Compilador a usar: msvc, clang, gcc, o all")]
    [ValidateSet("msvc", "clang", "gcc", "all")]
    [string]$Compiler = "all"
)

Write-Host "Configurando entorno de desarrollo para NumericRepresentations..." -ForegroundColor Green

# Rutas de compiladores
$VS_PATH = "D:\Program Files\Microsoft Visual Studio\2022\Community"
$MSVC_PATH = "$VS_PATH\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64"
$UCRT64_PATH = "C:\msys64\ucrt64\bin"

# Verificar existencia de compiladores
function Test-CompilerPath {
    param([string]$Path, [string]$Name)
    if (Test-Path $Path) {
        Write-Host "[OK] $Name encontrado en: $Path" -ForegroundColor Green
        return $true
    } else {
        Write-Host "[ERROR] $Name NO encontrado en: $Path" -ForegroundColor Red
        return $false
    }
}

Write-Host "`n--- Verificando Compiladores ---" -ForegroundColor Yellow

$msvc_ok = Test-CompilerPath "$MSVC_PATH\cl.exe" "MSVC (cl.exe)"
$clang_ok = Test-CompilerPath "$UCRT64_PATH\clang++.exe" "Clang++"
$gcc_ok = Test-CompilerPath "$UCRT64_PATH\g++.exe" "GCC (g++)"

# Configurar PATH para compiladores
$original_path = $env:PATH

function Set-CompilerEnv {
    param([string]$CompilerType)
    
    switch ($CompilerType) {
        "msvc" {
            if ($msvc_ok) {
                # Configurar entorno de Visual Studio
                $env:PATH = "$MSVC_PATH;$VS_PATH\Common7\IDE;$original_path"
                # Configurar variables de entorno de MSVC
                $env:INCLUDE = "$VS_PATH\VC\Tools\MSVC\14.44.35207\include;$VS_PATH\VC\Tools\MSVC\14.44.35207\atlmfc\include"
                $env:LIB = "$VS_PATH\VC\Tools\MSVC\14.44.35207\lib\x64;$VS_PATH\VC\Tools\MSVC\14.44.35207\atlmfc\lib\x64"
                Write-Host "[OK] Entorno MSVC configurado" -ForegroundColor Green
            }
        }
        "clang" {
            if ($clang_ok) {
                $env:PATH = "$UCRT64_PATH;$original_path"
                Write-Host "[OK] Entorno Clang configurado" -ForegroundColor Green
            }
        }
        "gcc" {
            if ($gcc_ok) {
                $env:PATH = "$UCRT64_PATH;$original_path"
                Write-Host "Entorno GCC configurado" -ForegroundColor Green
            }
        }
    }
}

# Funciones de compilación
function Compile-WithMSVC {
    Write-Host "`n--- Compilando con MSVC ---" -ForegroundColor Cyan
    Set-CompilerEnv "msvc"
    
    $flags = "/std:c++23", "/I.\include", "/EHsc", "/W4", "/permissive-"
    $cmd = "cl.exe $($flags -join ' ') /c include\dig_t.hpp /Fo:dig_t_msvc.obj"
    
    Write-Host "Comando: $cmd" -ForegroundColor Gray
    Invoke-Expression $cmd
}

function Compile-WithClang {
    Write-Host "`n--- Compilando con Clang ---" -ForegroundColor Cyan
    Set-CompilerEnv "clang"
    
    $flags = "-std=c++23", "-I./include", "-Wall", "-Wextra", "-pedantic"
    $cmd = "clang++ $($flags -join ' ') -c include/dig_t.hpp -o dig_t_clang.o"
    
    Write-Host "Comando: $cmd" -ForegroundColor Gray
    Invoke-Expression $cmd
}

function Compile-WithGCC {
    Write-Host "`n--- Compilando con GCC ---" -ForegroundColor Cyan
    Set-CompilerEnv "gcc"
    
    $flags = "-std=c++23", "-I./include", "-Wall", "-Wextra", "-pedantic"
    $cmd = "g++ $($flags -join ' ') -c include/dig_t.hpp -o dig_t_gcc.o"
    
    Write-Host "Comando: $cmd" -ForegroundColor Gray
    Invoke-Expression $cmd
}

# Ejecutar según parámetro
switch ($Compiler) {
    "msvc" { if ($msvc_ok) { Compile-WithMSVC } else { Write-Host "MSVC no disponible" -ForegroundColor Red } }
    "clang" { if ($clang_ok) { Compile-WithClang } else { Write-Host "Clang no disponible" -ForegroundColor Red } }
    "gcc" { if ($gcc_ok) { Compile-WithGCC } else { Write-Host "GCC no disponible" -ForegroundColor Red } }
    "all" {
        if ($msvc_ok) { Compile-WithMSVC }
        if ($clang_ok) { Compile-WithClang }
        if ($gcc_ok) { Compile-WithGCC }
    }
}

Write-Host "`n--- Resumen de Compilación ---" -ForegroundColor Yellow
Get-ChildItem -Name "dig_t_*.obj", "dig_t_*.o" 2>$null | ForEach-Object {
    Write-Host "[OK] Generado: $_" -ForegroundColor Green
}

# Restaurar PATH original
$env:PATH = $original_path
Write-Host "`nEntorno restaurado." -ForegroundColor Gray