# Build and run tests script for NumericRepresentations headers
param(
    [Parameter()]
    [ValidateSet("gcc", "clang", "msvc")]
    [string]$Compiler = "gcc"
)

Write-Host "========================================" -ForegroundColor Cyan
Write-Host " Building NumericRepresentations Tests" -ForegroundColor Cyan  
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Configuración de directorios
$TestDir = "tests"
$IncludeDir = "../include"
$BuildDir = "../build"

# Crear directorio de build si no existe
if (-not (Test-Path $BuildDir)) {
    New-Item -ItemType Directory -Path $BuildDir | Out-Null
}

# Configuración del compilador
$CompilerExe = ""
$CompilerFlags = ""

switch ($Compiler) {
    "gcc" {
        $CompilerExe = "C:\msys64\ucrt64\bin\g++.exe"
        $CompilerFlags = "-std=c++23", "-I$IncludeDir", "-Wall", "-Wextra", "-pedantic", "-g", "-O0", "-DDEBUG"
    }
    "clang" {
        $CompilerExe = "C:\msys64\ucrt64\bin\clang++.exe"
        $CompilerFlags = "-std=c++23", "-I$IncludeDir", "-Wall", "-Wextra", "-pedantic", "-g", "-O0", "-DDEBUG"
    }
    "msvc" {
        $CompilerExe = "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe"
        $CompilerFlags = "/std:c++23", "/I$IncludeDir", "/EHsc", "/W4", "/permissive-", "/Od", "/Zi"
    }
}

# Verificar que el compilador existe
if (-not (Test-Path $CompilerExe)) {
    Write-Host "❌ Compilador $Compiler no encontrado en: $CompilerExe" -ForegroundColor Red
    exit 1
}

Write-Host "Compilador: $Compiler" -ForegroundColor Yellow
Write-Host "Ejecutable: $CompilerExe" -ForegroundColor Gray
Write-Host "Flags: $($CompilerFlags -join ' ')" -ForegroundColor Gray
Write-Host ""

# Lista de archivos de test
$TestFiles = @(
    "test_auxiliary_types",
    "test_auxiliary_functions", 
    "test_basic_types",
    "test_dig_t"
)

# Ya estamos en el directorio de tests

$BuildSuccess = $true

# Compilar cada test
foreach ($TestFile in $TestFiles) {
    Write-Host "Compilando: $TestFile.cpp" -ForegroundColor White
    
    $OutputFile = "$TestFile.exe"
    $SourceFile = "$TestFile.cpp"
    
    try {
        if ($Compiler -eq "msvc") {
            # MSVC necesita sintaxis especial
            $Arguments = $CompilerFlags + @("/Fe:$OutputFile", $SourceFile)
        } else {
            # GCC/Clang sintaxis
            $Arguments = $CompilerFlags + @("-o", $OutputFile, $SourceFile)
        }
        
        $Process = Start-Process -FilePath $CompilerExe -ArgumentList $Arguments -Wait -PassThru -NoNewWindow
        
        if ($Process.ExitCode -eq 0) {
            Write-Host "OK $TestFile compilado exitosamente" -ForegroundColor Green
        } else {
            Write-Host "ERROR compilando $TestFile (codigo: $($Process.ExitCode))" -ForegroundColor Red
            $BuildSuccess = $false
        }
    }
    catch {
        Write-Host "ERROR compilando $TestFile : $($_.Exception.Message)" -ForegroundColor Red
        $BuildSuccess = $false
    }
    
    Write-Host ""
}

if ($BuildSuccess) {
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host " Ejecutando Tests" -ForegroundColor Cyan
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host ""
    
    $TotalTests = 0
    $PassedTests = 0
    
    # Ejecutar cada test
    foreach ($TestFile in $TestFiles) {
        $TotalTests++
        $ExePath = "./$TestFile.exe"
        
        Write-Host "Ejecutando: $TestFile.exe" -ForegroundColor White
        
        try {
            $Process = Start-Process -FilePath $ExePath -Wait -PassThru -NoNewWindow
            
            if ($Process.ExitCode -eq 0) {
                Write-Host "PASSED $TestFile" -ForegroundColor Green
                $PassedTests++
            } else {
                Write-Host "FAILED $TestFile (codigo: $($Process.ExitCode))" -ForegroundColor Red
            }
        }
        catch {
            Write-Host "ERROR $TestFile : $($_.Exception.Message)" -ForegroundColor Red
        }
        
        Write-Host ""
    }
    
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host " Resumen de Tests" -ForegroundColor Cyan
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "Total: $TotalTests" -ForegroundColor White
    Write-Host "Exitosos: $PassedTests" -ForegroundColor Green
    Write-Host "Fallidos: $($TotalTests - $PassedTests)" -ForegroundColor $(if ($TotalTests -eq $PassedTests) { "Green" } else { "Red" })
    
    if ($PassedTests -eq $TotalTests) {
        Write-Host ""
        Write-Host "TODOS LOS TESTS EXITOSOS!" -ForegroundColor Green
        exit 0
    } else {
        Write-Host ""
        Write-Host "Algunos tests fallaron." -ForegroundColor Red
        exit 1
    }
} else {
    Write-Host "❌ Fallos en compilación - no se ejecutarán los tests" -ForegroundColor Red
    exit 1
}