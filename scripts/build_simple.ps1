# NumericRepresentations - Build Script (PowerShell)
param(
    [ValidateSet("gcc", "clang", "msvc")]
    [string]$Compiler = "gcc",
    
    [ValidateSet("debug", "release")]
    [string]$Mode = "debug",
    
    [switch]$Clean,
    [switch]$TestOnly,
    [switch]$Verbose,
    [switch]$CleanOnly,
    [switch]$Help
)

$MSVC_PATH = "D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64"
$UCRT64_PATH = "C:\msys64\ucrt64\bin"

function Write-Info    { param([string]$msg) Write-Host "[INFO] $msg" -ForegroundColor Blue }
function Write-Success { param([string]$msg) Write-Host "[OK] $msg" -ForegroundColor Green }
function Write-Warning { param([string]$msg) Write-Host "[WARN] $msg" -ForegroundColor Yellow }
function Write-ErrorMsg{ param([string]$msg) Write-Host "[ERROR] $msg" -ForegroundColor Red }

function Show-Help {
    Write-Host "NumericRepresentations Build Script" -ForegroundColor Blue
    Write-Host "Usage: .\build.ps1 [OPTIONS]"
    Write-Host ""
    Write-Host "PARAMETERS:"
    Write-Host "  -Compiler gcc|clang|msvc"
    Write-Host "  -Mode debug|release"
    Write-Host "  -Clean               Limpiar antes"
    Write-Host "  -TestOnly            Solo probar headers"
    Write-Host "  -Verbose             Salida detallada"
    Write-Host "  -CleanOnly           Solo limpiar"
    Write-Host "  -Help                Esta ayuda"
}

function Test-CompilerPath {
    param([string]$CompilerName)
    
    $exePath = ""
    if ($CompilerName -eq "gcc") { $exePath = "$UCRT64_PATH\g++.exe" }
    elseif ($CompilerName -eq "clang") { $exePath = "$UCRT64_PATH\clang++.exe" }
    elseif ($CompilerName -eq "msvc") { $exePath = "$MSVC_PATH\cl.exe" }
    
    if (Test-Path $exePath) {
        Write-Success "$CompilerName encontrado en: $exePath"
        return $true
    } else {
        Write-ErrorMsg "$CompilerName NO encontrado en: $exePath"
        return $false
    }
}

function Get-CompilerSettings {
    param([string]$CompilerName, [string]$BuildMode)
    
    if ($CompilerName -eq "gcc") {
        $exe = "$UCRT64_PATH\g++.exe"
        $flags = "-std=c++23 -I./include -Wall -Wextra -pedantic"
        if ($BuildMode -eq "debug") {
            $flags += " -g -O0 -DDEBUG"
        } else {
            $flags += " -O3 -DNDEBUG"
        }
    }
    elseif ($CompilerName -eq "clang") {
        $exe = "$UCRT64_PATH\clang++.exe"
        $flags = "-std=c++23 -I./include -Wall -Wextra -pedantic"
        if ($BuildMode -eq "debug") {
            $flags += " -g -O0 -DDEBUG"
        } else {
            $flags += " -O3 -DNDEBUG"
        }
    }
    elseif ($CompilerName -eq "msvc") {
        $exe = "$MSVC_PATH\cl.exe"
        $flags = "/std:c++23 /I./include /EHsc /W4 /permissive-"
        if ($BuildMode -eq "debug") {
            $flags += " /Od /Zi"
        } else {
            $flags += " /O2 /DNDEBUG"
        }
    }
    
    return @{
        Executable = $exe
        Flags = $flags
    }
}

function Invoke-Clean {
    Write-Info "Limpiando archivos de build..."
    
    $itemsToRemove = @("build*", "test_build", "obj", "Debug", "Release", "*.obj", "*.o", "*.exe", "*.pdb")
    
    foreach ($item in $itemsToRemove) {
        Get-ChildItem -Path $item -ErrorAction SilentlyContinue | Remove-Item -Recurse -Force -ErrorAction SilentlyContinue
    }
    
    Write-Success "Limpieza completada"
}

function Test-HeaderCompilation {
    param([string]$CompilerName, [string]$CompilerExe, [string]$Flags)
    
    Write-Info "Probando headers con $CompilerName..."
    
    $headers = @("include\auxiliary_types.hpp", "include\auxiliary_functions.hpp", "include\basic_types.hpp", "include\dig_t.hpp")
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
            $outputFile = "test_build\${baseName}_test.obj"
            $command = "& `"$CompilerExe`" $Flags /c `"$header`" /Fo:`"$outputFile`""
        } else {
            $outputFile = "test_build\${baseName}_test.o"  
            $command = "& `"$CompilerExe`" $Flags -c `"$header`" -o `"$outputFile`""
        }
        
        try {
            if ($Verbose) {
                Write-Host "Comando: $command" -ForegroundColor Gray
                Invoke-Expression $command
            } else {
                Invoke-Expression "$command 2>`$null" | Out-Null
            }
            
            if ($LASTEXITCODE -eq 0) {
                Write-Success "[OK] $header compilado"
                $success++
            } else {
                Write-ErrorMsg "[ERROR] Error compilando $header"
            }
        }
        catch {
            Write-ErrorMsg "[ERROR] Excepcion compilando $header"
        }
    }
    
    Write-Info "Resultado: $success/$total headers compilados"
    return ($success -eq $total)
}

function Invoke-ProjectBuild {
    param([string]$CompilerName, [string]$CompilerExe, [string]$Flags)
    
    Write-Info "Compilando archivos fuente con $CompilerName..."
    
    # Crear directorio de build
    $buildDir = "build"
    New-Item -ItemType Directory -Path $buildDir -Force | Out-Null
    
    # Obtener archivos fuente
    $sourceFiles = Get-ChildItem -Path "src" -Filter "*.cpp" | Where-Object { $_.Name -ne "test_driver.cpp" }
    
    if ($sourceFiles.Count -eq 0) {
        Write-ErrorMsg "No se encontraron archivos fuente"
        return $false
    }
    
    Write-Info "Archivos fuente encontrados: $($sourceFiles.Count)"
    
    $objectFiles = @()
    $compilationSuccess = $true
    
    # Compilar cada archivo fuente
    foreach ($sourceFile in $sourceFiles) {
        $baseName = [System.IO.Path]::GetFileNameWithoutExtension($sourceFile.Name)
        Write-Info "Compilando: $($sourceFile.Name)"
        
        if ($CompilerName -eq "msvc") {
            $objectFile = "$buildDir\${baseName}.obj"
            $command = "& `"$CompilerExe`" $Flags /c `"$($sourceFile.FullName)`" /Fo:`"$objectFile`""
        } else {
            $objectFile = "$buildDir\${baseName}.o"
            $command = "& `"$CompilerExe`" $Flags -c `"$($sourceFile.FullName)`" -o `"$objectFile`""
        }
        
        try {
            if ($Verbose) {
                Write-Host "Comando: $command" -ForegroundColor Gray
                Invoke-Expression $command
            } else {
                Invoke-Expression "$command 2>`$null" | Out-Null
            }
            
            if ($LASTEXITCODE -eq 0) {
                Write-Success "Compilado: $($sourceFile.Name)"
                $objectFiles += $objectFile
            } else {
                Write-ErrorMsg "Error compilando: $($sourceFile.Name)"
                $compilationSuccess = $false
            }
        }
        catch {
            Write-ErrorMsg "Excepcion compilando: $($sourceFile.Name)"
            $compilationSuccess = $false
        }
    }
    
    if (!$compilationSuccess) {
        Write-ErrorMsg "Fallos en compilación de fuentes"
        return $false
    }
    
    # Enlazar ejecutable
    Write-Info "Enlazando ejecutable..."
    $executableName = if ($CompilerName -eq "msvc") { "$buildDir\NumericRepresentations.exe" } else { "$buildDir/NumericRepresentations" }
    
    if ($CompilerName -eq "msvc") {
        $linkCommand = "& `"$CompilerExe`" $($objectFiles -join ' ') /Fe:`"$executableName`""
    } else {
        $linkCommand = "& `"$CompilerExe`" $($objectFiles -join ' ') -o `"$executableName`""
    }
    
    try {
        if ($Verbose) {
            Write-Host "Enlace: $linkCommand" -ForegroundColor Gray
            Invoke-Expression $linkCommand
        } else {
            Invoke-Expression "$linkCommand 2>`$null" | Out-Null
        }
        
        if ($LASTEXITCODE -eq 0) {
            Write-Success "Ejecutable creado: $executableName"
            return $true
        } else {
            Write-ErrorMsg "Error en enlazado"
            return $false
        }
    }
    catch {
        Write-ErrorMsg "Excepcion en enlazado"
        return $false
    }
}

# Main execution
if ($Help) {
    Show-Help
    return
}

if ($CleanOnly) {
    Invoke-Clean
    return
}

Write-Host "==========================================" -ForegroundColor Blue
Write-Host " NumericRepresentations Build" -ForegroundColor Blue
Write-Host " Compilador: $Compiler | Modo: $Mode" -ForegroundColor Blue
Write-Host "==========================================" -ForegroundColor Blue

if ($Clean) {
    Invoke-Clean
}

if (!(Test-CompilerPath $Compiler)) {
    Write-ErrorMsg "Compilador no disponible"
    return
}

# Setup environment
if ($Compiler -in @("gcc", "clang")) {
    $env:PATH = "$UCRT64_PATH;$env:PATH"
}

$settings = Get-CompilerSettings $Compiler $Mode
Write-Info "Ejecutable: $($settings.Executable)"
Write-Info "Flags: $($settings.Flags)"

# Test headers
$testResult = Test-HeaderCompilation $Compiler $settings.Executable $settings.Flags

if ($testResult) {
    Write-Success "Pruebas de headers exitosas"
} else {
    Write-ErrorMsg "Fallos en pruebas de headers"
}

if ($TestOnly) {
    Write-Info "Modo test-only completado"
} else {
    if ($testResult) {
        Write-Info "Iniciando build completo del proyecto..."
        $buildResult = Invoke-ProjectBuild $Compiler $settings.Executable $settings.Flags
        if ($buildResult) {
            Write-Success "Build completo exitoso"
        } else {
            Write-ErrorMsg "Falló el build del proyecto"
        }
    } else {
        Write-ErrorMsg "No se puede hacer build - fallan las pruebas de headers"
    }
}

Write-Host "==========================================" -ForegroundColor Green
Write-Host " Completado" -ForegroundColor Green
Write-Host "==========================================" -ForegroundColor Green