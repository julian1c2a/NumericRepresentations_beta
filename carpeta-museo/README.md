# Carpeta Museo - Código Experimental Histórico

Esta carpeta contiene código experimental que fue desarrollado durante la exploración de diferentes técnicas de metaprogramación, pero que **no está siendo utilizado** en la implementación actual del proyecto.

## Archivos

### TplMp_typelist_t.hxx
- **Propósito original**: Metaprogramación con listas de tipos (typelists)
- **Funcionalidad**: 
  - Concatenación de tipos en tiempo de compilación
  - Acceso indexado a tipos mediante `get<Idx>`
  - Manipulación de tuplas (head, tail, middle, shead, slast, etc.)
  - Implementación de `cat_t` para concatenación
- **Estado**: Experimental, no utilizado en `reg_digs_t.hpp` ni `nat_reg_digs_t.hpp`
- **Líneas**: 1146 líneas
- **Fecha de archivo**: 13 de noviembre de 2025

### auxiliary_types.hpp
- **Propósito original**: Definiciones de enumeraciones y funciones auxiliares
- **Funcionalidad**:
  - Enumeraciones: `sign_funct_e`, `dig_format_e`, `num_type_e`, `nat_num_format_e`, `int_num_format_e`, `rat_num_format_e`, `binop_e`
  - Funciones auxiliares: `to_int()`, `is_positive()`, `is_negative()`, `is_zero()`, `opposite_sign()`
- **Estado**: Duplicado 100% de `core/internal/basic_types.hpp`, no incluido en ningún archivo
- **Líneas**: 145 líneas
- **Fecha de archivo**: 13 de noviembre de 2025

## Notas

El código aquí presente se conserva con propósitos de referencia histórica y como ejemplo de técnicas de metaprogramación exploradas. No forma parte de la implementación activa del proyecto.
