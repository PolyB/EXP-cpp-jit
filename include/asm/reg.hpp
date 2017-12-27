#pragma once
#include <cstdint>

namespace Asm
{
namespace Reg
{
  template <uint8_t S, uint8_t V>
  struct reg{};
}

  using EAX = Reg::reg<32, 0b000>;
  // TODO : other registers
}
