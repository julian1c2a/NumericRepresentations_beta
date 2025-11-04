#!/usr/bin/env pwsh
# Script para compilar y capturar errores

Write-Host "=== Compilando test_iostream_only.cpp ===" -ForegroundColor Green

try {
    $output = & C:\msys64\ucrt64\bin\g++.exe -std=c++23 -o tests\test_iostream_only.exe tests\test_iostream_only.cpp 2>&1
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✅ Compilación exitosa" -ForegroundColor Green
        Write-Host "Ejecutando test..." -ForegroundColor Blue
        & .\tests\test_iostream_only.exe
    } else {
        Write-Host "❌ Error en compilación:" -ForegroundColor Red
        Write-Host $output
    }
} catch {
    Write-Host "❌ Error capturado: $($_.Exception.Message)" -ForegroundColor Red
}