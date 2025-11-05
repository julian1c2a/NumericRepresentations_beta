# 📚 REFERENCIA RÁPIDA - NumericRepresentations

## 🚀 Compilación Estándar

### ✅ Método Recomendado
```bash
.\compile_simple_extended.bat mi_archivo.cpp
```
**Automáticamente aplica todos los flags necesarios para MSVC**

### 🔧 Método Manual (si necesario)
```bash
cl /EHsc /std:c++latest /I.\include /constexpr:depth2048 /constexpr:steps1048576 /bigobj /permissive- archivo.cpp
```

## 📋 Flags MSVC Críticos

| Flag                      | ¿Qué hace?                      | ¿Por qué necesario?                   |
| ------------------------- | ------------------------------- | ------------------------------------- |
| `/constexpr:depth2048`    | Profundidad recursión constexpr | Template metaprogramming recursivo    |
| `/constexpr:steps1048576` | Pasos evaluación constexpr      | Cálculos complejos tiempo compilación |
| `/bigobj`                 | Objetos .obj grandes            | Templates generan muchos símbolos     |
| `/permissive-`            | Conformancia C++ estricta       | Compatibilidad con GCC/Clang          |

## 🧪 Tests Disponibles

### Tests Básicos
- `test_dig_t_only.cpp` - Solo dig_t.hpp
- `test_utilities_refactor.cpp` - utilities.hpp refactorizado  
- `test_reg_digs_instantiation.cpp` - reg_digs_t básico

### Test Completo
- `test_proyecto_final.cpp` - Verificación integral del proyecto

### Verificación Sistemática
- `verificacion_final.bat` - Testing completo automático

## ⚡ Solución de Problemas

### Error C1001 MSVC
```bash
# ❌ Error: fatal error C1001: Error interno del compilador
# ✅ Solución: Usar compile_simple_extended.bat (flags automáticos)
```

### Constructor Variádico No Disponible
```cpp
// ❌ No compila en algunos casos:
reg_digs_t<10, 3> reg{dig_t<10>(1), dig_t<10>(2), dig_t<10>(3)};

// ✅ Workaround siempre funciona:
reg_digs_t<10, 3> reg;
reg[0] = dig_t<10>(1);
reg[1] = dig_t<10>(2); 
reg[2] = dig_t<10>(3);
```

## 📁 Headers Documentados

| Header                    | Estado          | Descripción                         |
| ------------------------- | --------------- | ----------------------------------- |
| `basic_types.hpp`         | ✅ Documentado   | Tipos fundamentales del sistema     |
| `auxiliary_types.hpp`     | ✅ Documentado   | Utilidades matemáticas              |
| `auxiliary_functions.hpp` | ✅ Documentado   | Funciones auxiliares                |
| `dig_t.hpp`               | ✅ Funcional     | Dígitos en bases arbitrarias        |
| `utilities.hpp`           | ✅ Refactorizado | Template metaprogramming optimizado |
| `reg_digs_t.hpp`          | ✅ Documentado   | Registros de dígitos (COMPLETO)     |

## 🎯 Uso Típico

### 1. Crear Dígitos
```cpp
#include "include/dig_t.hpp"
using namespace NumRepr;

dig_t<10> d1{7}, d2{3};                    // Base 10
auto suma = d1 + d2;                       // Operaciones aritméticas
std::cout << static_cast<int>(suma.get()); // ⚠️ IMPORTANTE: Cast para visualización
```

### ⚠️ Problema de Visualización uint8_t

```cpp
// ❌ PROBLEMA: Bases pequeñas usan uint8_t → caracteres ASCII
std::cout << d1.get();                     // Puede mostrar símbolos extraños

// ✅ SOLUCIONES:

// Método 1: Cast manual (siempre funciona)
std::cout << static_cast<int>(d1.get());       // Para números con signo
std::cout << static_cast<unsigned>(d1.get());  // Para números sin signo
std::cout << +d1.get();                        // Alternativa corta (promoción)

// Método 2: Helper automático (recomendado)
#include "include/dig_t_display_helpers.hpp"
using namespace NumRepr;

std::cout << display(d1);                      // Función helper
std::cout << d1;                               // Operador<< mejorado (formato: d[5]B10)
```

### 📋 ¿Cuándo Ocurre el Problema?
- **Bases ≤ 255**: Usan `uint8_t` → Problema con `std::cout`
- **Bases > 255**: Usan `uint16_t` o mayor → Sin problema

### 2. Crear Registros
```cpp
#include "include/reg_digs_t.hpp"
using namespace NumRepr;

reg_digs_t<10, 4> registro;       // 4 dígitos base 10
registro[0] = dig_t<10>(1);       // Asignación individual
registro[1] = dig_t<10>(9);
registro[2] = dig_t<10>(8);
registro[3] = dig_t<10>(5);       // Registro: [1,9,8,5]
```

### 3. Operaciones Avanzadas
```cpp
// Comparación
bool iguales = (registro1 == registro2);

// Reverse
registro.reverse();               // [1,9,8,5] -> [5,8,9,1]

// Acceso y modificación
auto primer_digito = registro[0].get();
```

## 🏆 Estado del Proyecto

**✅ COMPLETO Y FUNCIONAL**
- Multi-compilador: MSVC (flags ext.) + GCC + Clang  
- Documentación: Doxygen completa
- Testing: Automático y verificado
- Build system: Scripts optimizados

---
**📞 Soporte**: Usar `compile_simple_extended.bat` para compilar
**🔍 Debug**: Ejecutar `verificacion_final.bat` para diagnóstico completo