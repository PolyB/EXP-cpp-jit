#pragma once
#include <cstdint>

namespace Asm
{
namespace Reg
{
  template <uint8_t S, uint8_t V>
  struct reg{};
}
  using AL = Reg::reg<8, 0b000>;
  using CL = Reg::reg<8, 0b001>;
  using DL = Reg::reg<8, 0b010>;
  using BL = Reg::reg<8, 0b011>;
  using AH = Reg::reg<8, 0b100>;
  using CH = Reg::reg<8, 0b101>;
  using DH = Reg::reg<8, 0b110>;
  using BH = Reg::reg<8, 0b111>;

  using AX = Reg::reg<16, 0b000>;
  using CX = Reg::reg<16, 0b001>;
  using DX = Reg::reg<16, 0b010>;
  using BX = Reg::reg<16, 0b011>;
  using SP = Reg::reg<16, 0b100>;
  using BP = Reg::reg<16, 0b101>;
  using SI = Reg::reg<16, 0b110>;
  using DI = Reg::reg<16, 0b111>;

  using EAX = Reg::reg<32, 0b000>;
  using ECX = Reg::reg<32, 0b001>;
  using EDX = Reg::reg<32, 0b010>;
  using EBX = Reg::reg<32, 0b011>;
  using ESP = Reg::reg<32, 0b100>;
  using EBP = Reg::reg<32, 0b101>;
  using ESI = Reg::reg<32, 0b110>;
  using EDI = Reg::reg<32, 0b111>;

  using RAX = Reg::reg<64, 0b000>;
  using RCX = Reg::reg<64, 0b001>;
  using RDX = Reg::reg<64, 0b010>;
  using RBX = Reg::reg<64, 0b011>;
  using RSP = Reg::reg<64, 0b100>;
  using RBP = Reg::reg<64, 0b101>;
  using RSI = Reg::reg<64, 0b110>;
  using RDI = Reg::reg<64, 0b111>;
  // TODO : other registers
}
