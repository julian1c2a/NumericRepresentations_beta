/**
 * @file analisis_inconsistencia_signo.cpp
 * @brief Análisis de la inconsistencia entre is_minus() y set_minus() en int_reg_digs_t
 *
 * Investigación teórica de las diferencias entre la detección y asignación de signo.
 */

#include "int_reg_digs_t.hpp"
#include <iostream>

using namespace NumRepr;

// Template de prueba: base 2, 3 dígitos + 1 signo = 4 total
using test_int_t = int_reg_digs_t<2, 3>;

int main()
{
    std::cout << "=== ANÁLISIS: INCONSISTENCIA EN SISTEMA DE SIGNO ===\n";
    std::cout << "Template: int_reg_digs_t<2,3> (4 bits total)\n\n";

    // ================================================================
    // ANÁLISIS DE FUNCIONES
    // ================================================================
    std::cout << "=== ANÁLISIS DE CÓDIGO FUENTE ===\n\n";

    std::cout << "1. FUNCIÓN is_minus():\n";
    std::cout << "   constexpr bool is_minus() const { return (!(((*this)[R]).is_0())); }\n";
    std::cout << "\n";
    std::cout << "   ANÁLISIS:\n";
    std::cout << "   - Verifica si dígito[R] ≠ 0\n";
    std::cout << "   - Para int_reg_digs_t<2,3>: R = 3\n";
    std::cout << "   - CUALQUIER valor ≠ 0 en posición [3] → negativo\n";
    std::cout << "   - ACEPTA: dig_1(), dig_Bm1(), valores intermedios\n";
    std::cout << "   - CRITERIO: **FLEXIBLE** - cualquier bit ≠ 0 es signo negativo\n\n";

    std::cout << "2. FUNCIÓN set_minus():\n";
    std::cout << "   constexpr void set_minus() { (*this)[R] = dig_Bm1(); }\n";
    std::cout << "\n";
    std::cout << "   ANÁLISIS:\n";
    std::cout << "   - Establece dígito[R] = dig_Bm1()\n";
    std::cout << "   - dig_Bm1() = dig_max() = Base-1\n";
    std::cout << "   - Para base 2: dig_Bm1() = 1\n";
    std::cout << "   - FUERZA: Solo valor 1₂ en posición [3]\n";
    std::cout << "   - CRITERIO: **RÍGIDO** - signo negativo debe ser exactamente 1\n\n";

    std::cout << "3. FUNCIÓN normalize_sign():\n";
    std::cout << "   constexpr void normalize_sign() { is_minus() ? set_minus() : dig_t{}; }\n";
    std::cout << "\n";
    std::cout << "   ANÁLISIS:\n";
    std::cout << "   - Si is_minus() == true → aplica set_minus()\n";
    std::cout << "   - Si is_minus() == false → no hace nada (¿bug?)\n";
    std::cout << "   - PROBLEMA: No establece set_plus() explícitamente\n";
    std::cout << "   - COMPORTAMIENTO: Normaliza solo negativos, no positivos\n\n";

    // ================================================================
    // ESCENARIOS DE INCONSISTENCIA
    // ================================================================
    std::cout << "=== ESCENARIOS DE INCONSISTENCIA ===\n\n";

    std::cout << "ESCENARIO 1: Valor intermedio en bit de signo\n";
    std::cout << "  Configuración hipotética: dígitos = [1, 0, 1, X]\n";
    std::cout << "  Donde X es un valor intermedio (no 0, no 1)\n";
    std::cout << "\n";
    std::cout << "  En base 16 (dig_Bm1() = 15):\n";
    std::cout << "    X = 7 (valor intermedio)\n";
    std::cout << "    is_minus(): 7 ≠ 0 → TRUE (detecta negativo) ✓\n";
    std::cout << "    set_minus(): establece X = 15 (normaliza a máximo)\n";
    std::cout << "    RESULTADO: [1, 0, 1, 7] → [1, 0, 1, 15]\n";
    std::cout << "\n";

    std::cout << "ESCENARIO 2: Bit de signo con valor mínimo positivo\n";
    std::cout << "  Configuración: dígitos = [0, 0, 0, 1]\n";
    std::cout << "  En base 2:\n";
    std::cout << "    is_minus(): 1 ≠ 0 → TRUE (detecta negativo) ✓\n";
    std::cout << "    set_minus(): establece 1 = 1 (ya correcto)\n";
    std::cout << "    RESULTADO: Sin cambio, pero lógicamente consistente\n";
    std::cout << "\n";

    std::cout << "ESCENARIO 3: Número positivo grande\n";
    std::cout << "  Configuración: dígitos = [1, 1, 1, 0] = +7 en complemento\n";
    std::cout << "    is_minus(): 0 == 0 → FALSE (detecta positivo) ✓\n";
    std::cout << "    normalize_sign(): No hace nada (problema potencial)\n";
    std::cout << "    RESULTADO: Queda [1, 1, 1, 0], pero ¿es consistente?\n";
    std::cout << "\n";

    // ================================================================
    // ANÁLISIS DE APROXIMACIONES
    // ================================================================
    std::cout << "=== ANÁLISIS: ¿CUÁL ES MÁS EXACTA? ===\n\n";

    std::cout << "**APROXIMACIÓN is_minus() (FLEXIBLE):**\n";
    std::cout << "✅ VENTAJAS:\n";
    std::cout << "  - Detecta cualquier indicación de signo negativo\n";
    std::cout << "  - Robusto ante valores intermedios o corruptos\n";
    std::cout << "  - Compatible con diferentes representaciones internas\n";
    std::cout << "  - Tolerante a inconsistencias temporales\n";
    std::cout << "\n";
    std::cout << "❌ DESVENTAJAS:\n";
    std::cout << "  - Puede detectar falsos negativos\n";
    std::cout << "  - No distingue entre diferentes grados de 'negatividad'\n";
    std::cout << "  - Menos estricto en validación\n";
    std::cout << "\n";

    std::cout << "**APROXIMACIÓN set_minus() (RÍGIDA):**\n";
    std::cout << "✅ VENTAJAS:\n";
    std::cout << "  - Representación canónica consistente\n";
    std::cout << "  - Garantiza formato estándar (bit signo = B-1)\n";
    std::cout << "  - Fácil de verificar y debuggear\n";
    std::cout << "  - Compatible con aritmética basada en bit de signo\n";
    std::cout << "\n";
    std::cout << "❌ DESVENTAJAS:\n";
    std::cout << "  - Puede sobrescribir información útil\n";
    std::cout << "  - Menos flexible ante variaciones\n";
    std::cout << "  - Potencial pérdida de datos en conversiones\n";
    std::cout << "\n";

    // ================================================================
    // EVALUACIÓN TÉCNICA
    // ================================================================
    std::cout << "=== EVALUACIÓN TÉCNICA ===\n\n";

    std::cout << "**PARA COMPLEMENTO A LA BASE PURO:**\n";
    std::cout << "  En complemento verdadero, el signo está distribuido:\n";
    std::cout << "  -1 en base 2, 4 bits = 1111₂ (todos los bits)\n";
    std::cout << "  -1 ≠ 0001₂ (solo bit de signo)\n";
    std::cout << "  \n";
    std::cout << "  VEREDICTO: **AMBAS APROXIMACIONES SON INCORRECTAS**\n";
    std::cout << "  para complemento a la base puro.\n";
    std::cout << "\n";

    std::cout << "**PARA SISTEMA BIT DE SIGNO + MAGNITUD:**\n";
    std::cout << "  Bit de signo independiente en MSB:\n";
    std::cout << "  +7 = 0111₂, -7 = 1111₂\n";
    std::cout << "  +0 = 0000₂, -0 = 1000₂\n";
    std::cout << "\n";
    std::cout << "  is_minus(): ✅ CORRECTO - detecta bit de signo\n";
    std::cout << "  set_minus(): ✅ CORRECTO - establece bit de signo\n";
    std::cout << "\n";

    std::cout << "**PARA SISTEMA HÍBRIDO (IMPLEMENTACIÓN ACTUAL):**\n";
    std::cout << "  Parece usar bit de signo con normalización:\n";
    std::cout << "  \n";
    std::cout << "  is_minus(): ✅ APROPIADO - detección flexible\n";
    std::cout << "  set_minus(): ✅ APROPIADO - normalización estricta\n";
    std::cout << "  \n";
    std::cout << "  VEREDICTO: **AMBAS SON CORRECTAS** para sistema híbrido\n";
    std::cout << "  La flexibilidad + rigidez es el patrón deseado.\n";
    std::cout << "\n";

    // ================================================================
    // RECOMENDACIÓN FINAL
    // ================================================================
    std::cout << "=== RECOMENDACIÓN FINAL ===\n\n";

    std::cout << "**ANÁLISIS DE LA INCONSISTENCIA:**\n";
    std::cout << "  La 'inconsistencia' es realmente un PATRÓN DE DISEÑO:\n";
    std::cout << "  \n";
    std::cout << "  1. **DETECCIÓN FLEXIBLE** (is_minus):\n";
    std::cout << "     - Acepta cualquier indicación de signo negativo\n";
    std::cout << "     - Útil durante construcción y conversiones\n";
    std::cout << "     - Robusto ante estados intermedios\n";
    std::cout << "\n";
    std::cout << "  2. **NORMALIZACIÓN RÍGIDA** (set_minus):\n";
    std::cout << "     - Fuerza representación canónica\n";
    std::cout << "     - Garantiza consistencia interna\n";
    std::cout << "     - Facilita operaciones aritméticas\n";
    std::cout << "\n";

    std::cout << "**VEREDICTO TÉCNICO:**\n";
    std::cout << "  ✅ **AMBAS APROXIMACIONES SON CORRECTAS**\n";
    std::cout << "  \n";
    std::cout << "  La combinación FLEXIBLE + RÍGIDA es INTENCIONADA:\n";
    std::cout << "  - is_minus(): Detección tolerante\n";
    std::cout << "  - set_minus(): Normalización estricta\n";
    std::cout << "  - normalize_sign(): Puente entre ambas\n";
    std::cout << "\n";
    std::cout << "  Este patrón es común en sistemas numéricos que manejan:\n";
    std::cout << "  - Conversiones entre formatos\n";
    std::cout << "  - Estados intermedios durante cálculos\n";
    std::cout << "  - Representaciones canónicas vs. trabajos temporales\n";
    std::cout << "\n";

    // ================================================================
    // PROBLEMA REAL DETECTADO
    // ================================================================
    std::cout << "=== PROBLEMA REAL DETECTADO ===\n\n";

    std::cout << "⚠️  **VERDADERO PROBLEMA en normalize_sign():**\n";
    std::cout << "  \n";
    std::cout << "  Código actual:\n";
    std::cout << "    normalize_sign() { is_minus() ? set_minus() : dig_t{}; }\n";
    std::cout << "  \n";
    std::cout << "  PROBLEMA:\n";
    std::cout << "  - Si es negativo → set_minus() ✅ CORRECTO\n";
    std::cout << "  - Si es positivo → dig_t{} ❌ NO HACE NADA\n";
    std::cout << "  \n";
    std::cout << "  DEBERÍA SER:\n";
    std::cout << "    normalize_sign() { is_minus() ? set_minus() : set_plus(); }\n";
    std::cout << "  \n";
    std::cout << "  IMPACTO:\n";
    std::cout << "  - Números positivos pueden quedar sin normalizar\n";
    std::cout << "  - Bit de signo positivo puede tener valores residuales\n";
    std::cout << "  - Inconsistencia en representación canónica\n";
    std::cout << "\n";

    std::cout << "**CONCLUSIÓN FINAL:**\n";
    std::cout << "  1. is_minus() y set_minus() son CONSISTENTES por diseño\n";
    std::cout << "  2. La 'rigidez' vs 'flexibilidad' es INTENCIONAL\n";
    std::cout << "  3. El VERDADERO problema está en normalize_sign()\n";
    std::cout << "  4. Falta normalización explícita para casos positivos\n";
    std::cout << "\n";
    std::cout << "🎯 **RESPUESTA A TU PREGUNTA:**\n";
    std::cout << "   AMBAS aproximaciones son exactas para sus propósitos.\n";
    std::cout << "   La diferencia es FUNCIONAL, no un error de diseño.\n";

    return 0;
}