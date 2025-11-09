#ifndef UTIL_FUNCTS_HPP_INCLUDED
#define UTIL_FUNCTS_HPP_INCLUDED

#include "core/internal/auxiliary_functions.hpp"

namespace util_functs {
  using NumRepr::auxiliary_functions::pow2;
  using NumRepr::auxiliary_functions::pow2ct;
  using NumRepr::auxiliary_functions::log2;
  using NumRepr::auxiliary_functions::log2ct;

  // Also expose the new int_* names for incremental migration.
  using NumRepr::auxiliary_functions::int_pow2;
  using NumRepr::auxiliary_functions::int_pow2ct;
  using NumRepr::auxiliary_functions::int_log2;
  using NumRepr::auxiliary_functions::int_log2ct;
}

#endif // UTIL_FUNCTS_HPP_INCLUDED
