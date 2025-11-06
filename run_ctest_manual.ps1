# run_ctest_manual.ps1 - Ejecución manual estilo CTest para NumericRepresentations

Write-Host "=================================================================" -ForegroundColor Cyan
Write-Host "   CTEST MANUAL EXECUTION - NumericRepresentations" -ForegroundColor Cyan  
Write-Host "=================================================================" -ForegroundColor Cyan
Write-Host ""

$testResults = @()
$totalTests = 0
$passedTests = 0
$failedTests = 0

function Run-Test {
    param(
        [string]$TestName,
        [string]$Executable,
        [string]$Labels
    )
    
    $global:totalTests++
    Write-Host "Test $totalTests : $TestName" -ForegroundColor Yellow
    Write-Host "  Labels: $Labels" -ForegroundColor Gray
    Write-Host "  Command: $Executable" -ForegroundColor Gray
    
    if (Test-Path $Executable) {
        try {
            $startTime = Get-Date
            $result = & $Executable
            $endTime = Get-Date
            $duration = ($endTime - $startTime).TotalSeconds
            
            if ($LASTEXITCODE -eq 0) {
                Write-Host "  Status: PASSED ($([math]::Round($duration, 2))s)" -ForegroundColor Green
                $global:passedTests++
                $global:testResults += [PSCustomObject]@{
                    Test = $TestName
                    Status = "PASSED"
                    Duration = $duration
                    Labels = $Labels
                }
            } else {
                Write-Host "  Status: FAILED ($([math]::Round($duration, 2))s)" -ForegroundColor Red
                $global:failedTests++
                $global:testResults += [PSCustomObject]@{
                    Test = $TestName
                    Status = "FAILED"
                    Duration = $duration
                    Labels = $Labels
                }
            }
        } catch {
            Write-Host "  Status: ERROR - $($_.Exception.Message)" -ForegroundColor Red
            $global:failedTests++
        }
    } else {
        Write-Host "  Status: NOT_FOUND - Executable not available" -ForegroundColor Magenta
    }
    Write-Host ""
}

# ===================================================================
# SUITE 1: INT_REG_DIGS_T - Enteros con Signo (Complemento a la Base)
# ===================================================================

Write-Host "═══ SUITE 1: int_reg_digs_t (Signed Integers) ═══" -ForegroundColor Cyan

Run-Test -TestName "int_reg_digs_ultra_minimal" `
         -Executable ".\test_int_ultra_minimal_extended.exe" `
         -Labels "int_reg_digs_t;phase1;basic;minimal"

# ===================================================================
# SUITE 2: NAT_REG_DIGS_T - Números Naturales (8 Fases)
# ===================================================================

Write-Host "═══ SUITE 2: nat_reg_digs_t (Natural Numbers) ═══" -ForegroundColor Cyan

Run-Test -TestName "nat_reg_digs_basic_methods" `
         -Executable ".\test_basic_methods_extended.exe" `
         -Labels "nat_reg_digs_t;phase1;basic;methods"

Run-Test -TestName "nat_reg_digs_factory_methods" `
         -Executable ".\test_factory_methods_extended.exe" `
         -Labels "nat_reg_digs_t;phase2;factory"

Run-Test -TestName "nat_reg_digs_constructors" `
         -Executable ".\test_minimal_constructors_extended.exe" `
         -Labels "nat_reg_digs_t;phase3;constructors"

Run-Test -TestName "nat_reg_digs_set_operations" `
         -Executable ".\test_set_operations_extended.exe" `
         -Labels "nat_reg_digs_t;phase4;set_operations"

Run-Test -TestName "nat_reg_digs_assignment_operators" `
         -Executable ".\test_assignment_operators_extended.exe" `
         -Labels "nat_reg_digs_t;phase5;assignment;operators"

Run-Test -TestName "nat_reg_digs_arithmetic_operators" `
         -Executable ".\test_arithmetic_operators_extended.exe" `
         -Labels "nat_reg_digs_t;phase6;arithmetic;operators"

Run-Test -TestName "nat_reg_digs_comparison_operators" `
         -Executable ".\test_comparison_operators_extended.exe" `
         -Labels "nat_reg_digs_t;phase7;comparison;operators"

Run-Test -TestName "nat_reg_digs_io_operations" `
         -Executable ".\test_io_operations_extended.exe" `
         -Labels "nat_reg_digs_t;phase8;io;strings"

# ===================================================================
# RESUMEN FINAL
# ===================================================================

Write-Host "=================================================================" -ForegroundColor Cyan
Write-Host "   TEST EXECUTION SUMMARY" -ForegroundColor Cyan
Write-Host "=================================================================" -ForegroundColor Cyan
Write-Host "Total Tests   : $totalTests" -ForegroundColor White
Write-Host "Passed Tests  : $passedTests" -ForegroundColor Green
Write-Host "Failed Tests  : $failedTests" -ForegroundColor $(if($failedTests -gt 0) { "Red" } else { "Green" })
Write-Host "Success Rate  : $([math]::Round(($passedTests / $totalTests) * 100, 1))%" -ForegroundColor $(if($passedTests -eq $totalTests) { "Green" } else { "Yellow" })
Write-Host ""

if ($failedTests -eq 0) {
    Write-Host "🎉 ALL TESTS PASSED!" -ForegroundColor Green
} else {
    Write-Host "⚠️  Some tests failed. Review results above." -ForegroundColor Yellow
}

Write-Host ""
Write-Host "Detailed Results:" -ForegroundColor White
$testResults | Format-Table -AutoSize

Write-Host "=================================================================" -ForegroundColor Cyan