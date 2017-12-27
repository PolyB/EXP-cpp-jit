#pragma once
#include <cstdint>

namespace Asm
{
  namespace Cast
  {
    template <auto
    struct uncast

  }

  template <uint8_t D, auto Val>
  struct cast {
    static constexpr decltype(Val) val = Val;
  };

}
