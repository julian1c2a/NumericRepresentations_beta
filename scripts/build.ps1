# NumericRepresentations - Universal Build Script (PowerShell)
# Soporte para MSVC, Clang y GCC con modos Debug/Release

param(
    [Parameter(HelpMessage="Compilador a usar")]
    [ValidateSet("gcc", "clang", "msvc")]
    [string]$Compiler = "gcc",
    
    [Parameter(HelpMessage="Modo de compilación")]
    [ValidateSet("debug", "release")]
    [string]$Mode = "debug",
    
    [Parameter(HelpMessage="Limpiar antes de compilar")]
    [switch]$Clean,
    
    [Parameter(HelpMessage="Solo probar headers")]
    [switch]$TestOnly,
    
    [Parameter(HelpMessage="Salida verbose")]
    [switch]$Verbose,
    
    [Parameter(HelpMessage="Solo limpiar")]
    [switch]$CleanOnly,
    
    [Parameter(HelpMessage="Mostrar ayuda")]
    [switch]$Help
)

# Rutas de compiladores
$MSVC_PATH = "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64"
$UCRT64_PATH = "C:\msys64\ucrt64\bin"

function Write-ColorOutput {
    param(
        [string]$Message,
        [string]$Color = "White"
    )
    
    switch ($Color) {
        "Red"    { Write-Host $Message -ForegroundColor Red }
        "Green"  { Write-Host $Message -ForegroundColor Green }
        "Yellow" { Write-Host $Message -ForegroundColor Yellow }
        "Blue"   { Write-Host $Message -ForegroundColor Blue }
        "Cyan"   { Write-Host $Message -ForegroundColor Cyan }
        default  { Write-Host $Message }
    }
}

function Write-Info    { param([string]$msg) Write-ColorOutput "[INFO] $msg" "Blue" }
function Write-Success { param([string]$msg) Write-ColorOutput "[OK] $msg" "Green" }
function Write-Warning { param([string]$msg) Write-ColorOutput "[WARN] $msg" "Yellow" }
function Write-Error   { param([string]$msg) Write-ColorOutput "[ERROR] $msg" "Red" }

function Show-Help {
    Write-ColorOutput "NumericRepresentations Build Script" "Blue"
    Write-Host "Usage: .\build.ps1 [OPTIONS]"
    Write-Host ""
    Write-Host "PARAMETERS:"
    Write-Host "  -Compiler COMPILER    Compilador: gcc, clang, msvc (default: gcc)"
    Write-Host "  -Mode MODE           Modo: debug, release (default: debug)"
    Write-Host "  -Clean               Limpiar antes de compilar"
    Write-Host "  -TestOnly            Solo probar headers (no compilar ejecutable)"
    Write-Host "  -Verbose             Salida verbose"
    Write-Host "  -CleanOnly           Solo limpiar archivos de build"
    Write-Host "  -Help                Mostrar esta ayuda"
    Write-Host ""
    Write-Host "EXAMPLES:"
    Write-Host "  .\build.ps1 -Compiler gcc -Mode release     # Compilar con GCC en modo Release"
    Write-Host "  .\build.ps1 -Compiler clang -Clean          # Compilar con Clang, limpiando primero"
    Write-Host "  .\build.ps1 -Compiler msvc -TestOnly        # Solo probar headers con MSVC"
    Write-Host "  .\build.ps1 -CleanOnly                      # Solo limpiar archivos de build"
}

function Test-CompilerAvailable {
    param([string]$CompilerName)
    
    $path = switch ($CompilerName) {
        "gcc"   { "$UCRT64_PATH\g++.exe" }
        "clang" { "$UCRT64_PATH\clang++.exe" }
        "msvc"  { "$MSVC_PATH\cl.exe" }
        default { "" }
    }
    
    if (Test-Path $path) {
        Write-Success "$CompilerName encontrado en: $path"
        return $true
    } else {
        Write-Error "$CompilerName NO encontrado en: $path"
        return $false
    }
}

function Get-CompilerFlags {
    param(
        [string]$CompilerName,
        [string]$BuildMode
    )
    
    $flags = switch ($CompilerName) {
        "gcc" {
            $base = "-std=c++23 -I./include -Wall -Wextra -pedantic"
            if ($BuildMode -eq "debug") {
                "$base -g -O0 -DDEBUG"
            } else {
                "$base -O3 -DNDEBUG -march=native"
            }
        }
        "clang" {
            $base = "-std=c++23 -I./include -Wall -Wextra -pedantic"
            if ($BuildMode -eq "debug") {
                "$base -g -O0 -DDEBUG"
            } else {
                "$base -O3 -DNDEBUG -march=native"
            }
        }
        "msvc" {
            $base = "/std:c++23 /I./include /EHsc /W4 /permissive-"
            if ($BuildMode -eq "debug") {
                "$base /Od /Zi"
            } else {
                "$base /O2 /DNDEBUG"
            }
        }
    }
    
    return $flags
}

function Get-CompilerExecutable {
    param([string]$CompilerName)
    
    return switch ($CompilerName) {
        "gcc"   { "$UCRT64_PATH\g++.exe" }
        "clang" { "$UCRT64_PATH\clang++.exe" }
        "msvc"  { "$MSVC_PATH\cl.exe" }
    }
}

function Invoke-CleanBuild {
    Write-Info "Limpiando archivos de build..."
    
    # Directorios de build
    $buildDirs = @("build", "build_*", "obj", "Debug", "Release", "test_build")
    foreach ($dir in $buildDirs) {
        if (Test-Path $dir) {
            Write-Info "Eliminando directorio: $dir"
            Remove-Item $dir -Recurse -Force -ErrorAction SilentlyContinue
        }
    }
    
    # Archivos objeto y ejecutables
    $patterns = @("*.o", "*.obj", "*.exe", "*_test.o", "*_test.obj", "*.pdb", "*.ilk")
    foreach ($pattern in $patterns) {
        Get-ChildItem -Path . -Name $pattern -Recurse -ErrorAction SilentlyContinue | 
            ForEach-Object { Remove-Item $_ -Force -ErrorAction SilentlyContinue }
    }
    
    Write-Success "Limpieza completada"
}

function Test-Headers {
    param(
        [string]$CompilerName,
        [string]$Flags,
        [string]$CompilerExe
    )
    
    Write-Info "Probando compilación de headers con $CompilerName..."
    
    $headers = @(
        "include\auxiliary_types.hpp",
        "include\auxiliary_functions.hpp",
        "include\basic_types.hpp",
        "include\dig_t.hpp"
    )
    
    $success = 0
    $total = 0
    
    New-Item -ItemType Directory -Path "test_build" -Force | Out-Null
    
    foreach ($header in $headers) {
        if (!(Test-Path $header)) {
            Write-Warning "Header no encontrado: $header"
            continue
        }
        
        $total++
        $baseName = [System.IO.Path]::GetFileNameWithoutExtension($header)
        
        Write-Info "Probando: $header"
        
        if ($CompilerName -eq "msvc") {
            $outputFile = "test_build\${baseName}_${CompilerName}_test.obj"
            $cmd = "$CompilerExe $Flags /c $header /Fo:`"$outputFile`""
        } else {
            $outputFile = "test_build\${baseName}_${CompilerName}_test.o"
            $cmd = "$CompilerExe $Flags -c $header -o `"$outputFile`""
        }
        
        try {
            if ($Verbose) {
                Write-Host "Ejecutando: $cmd" -ForegroundColor Gray
                Invoke-Expression $cmd
            } else {
                Invoke-Expression "$cmd 2>`$null" | Out-Null
            }
            
            if ($LASTEXITCODE -eq 0) {
                Write-Success "✓ $header compilado exitosamente"
                $success++
            } else {
                Write-Error "✗ Error compilando $header"
            }
        } catch {
            Write-Error "✗ Error compilando $header: $_"
        }
    }
    
    Write-Info "Resultado: $success/$total headers compilados exitosamente"
    
    if ($success -eq $total) {
        Write-Success "Todas las pruebas de headers pasaron con $CompilerName"
        return $true
    } else {
        Write-Error "Algunos headers fallaron con $CompilerName"
        return $false
    }
}

function Build-Project {
    param(
        [string]$CompilerName,
        [string]$BuildMode,
        [string]$Flags,
        [string]$CompilerExe
    )
    
    Write-Info "Compilando proyecto con $CompilerName en modo $BuildMode..."
    
    $buildDir = "build_${CompilerName}_${BuildMode}"
    New-Item -ItemType Directory -Path $buildDir -Force | Out-Null
    
    $sources = @(
        "src\main.cpp",
        "src\test_driver.cpp",
        "src\get.cpp"
    )
    
    $objects = @()
    $compileSuccess = $true
    
    foreach ($source in $sources) {
        if (!(Test-Path $source)) {
            Write-Warning "Archivo fuente no encontrado: $source"
            continue
        }
        
        $baseName = [System.IO.Path]::GetFileNameWithoutExtension($source)
        
        if ($CompilerName -eq "msvc") {
            $objectFile = "$buildDir\${baseName}.obj"
            $cmd = "$CompilerExe $Flags /c $source /Fo:`"$objectFile`""
        } else {
            $objectFile = "$buildDir\${baseName}.o"
            $cmd = "$CompilerExe $Flags -c $source -o `"$objectFile`""
        }
        
        Write-Info "Compilando: $source -> $objectFile"
        
        try {
            if ($Verbose) {
                Invoke-Expression $cmd
            } else {
                Invoke-Expression "$cmd 2>`$null" | Out-Null
            }
            
            if ($LASTEXITCODE -eq 0) {
                Write-Success "✓ $source compilado"
                $objects += $objectFile
            } else {
                Write-Error "✗ Error compilando $source"
                $compileSuccess = $false
            }
        } catch {
            Write-Error "✗ Error compilando $source: $_"
            $compileSuccess = $false
        }
    }
    
    if (!$compileSuccess) {
        Write-Error "Errores en la compilación"
        return $false
    }
    
    # Enlazar ejecutable
    $executable = "$buildDir\NumericRepresentations.exe"
    
    Write-Info "Enlazando: $executable"
    
    if ($CompilerName -eq "msvc") {
        $linkCmd = "$CompilerExe $($objects -join ' ') /Fe:`"$executable`""
    } else {
        $linkCmd = "$CompilerExe $($objects -join ' ') -o `"$executable`""
    }
    
    try {
        if ($Verbose) {
            Invoke-Expression $linkCmd
        } else {
            Invoke-Expression "$linkCmd 2>`$null" | Out-Null
        }
        
        if ($LASTEXITCODE -eq 0) {
            Write-Success "✓ Ejecutable generado: $executable"
            return $true
        } else {
            Write-Error "✗ Error en el enlazado"
            return $false
        }
    } catch {
        Write-Error "✗ Error en el enlazado: $_"
        return $false
    }
}

# Main execution
if ($Help) {
    Show-Help
    exit 0
}

if ($CleanOnly) {
    Invoke-CleanBuild
    exit 0
}

Write-ColorOutput "==========================================" "Blue"
Write-ColorOutput " NumericRepresentations Build Script" "Blue"
Write-ColorOutput " Compilador: $Compiler | Modo: $Mode" "Blue"
Write-ColorOutput "==========================================" "Blue"

# Clean if requested
if ($Clean) {
    Invoke-CleanBuild
}

# Check compiler availability
if (!(Test-CompilerAvailable $Compiler)) {
    exit 1
}

# Setup environment for UCRT64 compilers
if ($Compiler -in @("gcc", "clang")) {
    $env:PATH = "$UCRT64_PATH;$env:PATH"
}

# Get compiler settings
$compilerFlags = Get-CompilerFlags $Compiler $Mode
$compilerExe = Get-CompilerExecutable $Compiler

Write-Info "Flags: $compilerFlags"
Write-Info "Ejecutable: $compilerExe"

# Test headers first
if (!(Test-Headers $Compiler $compilerFlags $compilerExe)) {
    Write-Error "Pruebas de headers fallaron"
    exit 1
}

# Build project if not test-only
if (!$TestOnly) {
    if (Build-Project $Compiler $Mode $compilerFlags $compilerExe) {
        Write-Success "Build completado exitosamente"
    } else {
        Write-Error "Build falló"
        exit 1
    }
} else {
    Write-Info "Modo test-only: solo se probaron los headers"
}

Write-ColorOutput "==========================================" "Green"
Write-ColorOutput " Build completado" "Green"
Write-ColorOutput "==========================================" "Green"