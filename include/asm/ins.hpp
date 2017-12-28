#pragma once
#include "imm.hpp"
#include "reg.hpp"
#include "utils.hpp"

#define DEFINSTR(S) \
  template <class... C> struct S { static_assert(false && sizeof...(C), "invalid "#S); }

namespace Asm
{
  namespace Ins
  {
    // ConstBase is for expressions that cannot be changed at runtime
    struct ConstBase
    {
      template <class C>
      static constexpr inline void copy(uint8_t *, C&){}
      static constexpr bool r = false;
    };

    // Base is a helper for expressions that can be changed a runtime NOTE : need to implement copy
    struct Base
    {
      static constexpr bool r = true;
    };
  }
  // mov
  DEFINSTR(mov);
  template <auto Imm, uint8_t Reg, class ImmT> struct mov<Imm::imm<32, ImmT, Imm>, Reg::reg<32, Reg>>{
    using Imm_ = typename Imm::imm<32, ImmT, Imm>::type;
    using b = utils::bits<0b10111000 | Reg, Imm_::b[0], Imm_::b[1], Imm_::b[2], Imm_::b[3]>;

    static constexpr bool r = Imm_::r;

    template <class T>
    static inline void copy(uint8_t *dst, T& t) {
      if constexpr (Imm_::template dep<T>::value)
      {
        dst[1] = Imm_::template get<0>(t);
        dst[2] = Imm_::template get<1>(t);
        dst[3] = Imm_::template get<2>(t);
        dst[4] = Imm_::template get<3>(t);
      }
    }
  };
  template <uint8_t Reg1, uint8_t Reg2> struct mov<Reg::reg<32, Reg1>, Reg::reg<32, Reg2>> : Ins::ConstBase { using b = utils::bits<0b10001001, 0b11000000 | (Reg1 << 3) | (Reg2)>; }; // TODO : find the difference (like add)

  template <auto Imm, uint8_t Reg, class ImmT> struct mov<Imm::imm<64, ImmT, Imm>, Reg::reg<64, Reg>>{
    using Imm_ = typename Imm::imm<64, ImmT, Imm>::type;
    using b = utils::bits<0b01001001, 0b10111000 | Reg, Imm_::b[0], Imm_::b[1], Imm_::b[2], Imm_::b[3], Imm_::b[4], Imm_::b[5], Imm_::b[6], Imm_::b[7]>;
    static constexpr bool r = Imm_::r;

    template <class T>
    static inline void copy(uint8_t *dst, T& t) {
      if constexpr (Imm_::template dep<T>::value)
      {
        dst[3] = Imm_::template get<0>(t);
        dst[4] = Imm_::template get<1>(t);
        dst[5] = Imm_::template get<2>(t);
        dst[6] = Imm_::template get<3>(t);
        dst[7] = Imm_::template get<4>(t);
        dst[8] = Imm_::template get<5>(t);
        dst[9] = Imm_::template get<6>(t);
        dst[10] = Imm_::template get<7>(t);
      }
    }
  };

  // ret
  DEFINSTR(ret);
  template <> struct ret<> : Ins::ConstBase { using b = utils::bits<0b11000011>; };

  // dec
  DEFINSTR(dec);
  template <uint8_t Reg> struct dec<Reg::reg<32, Reg>> : Ins::ConstBase { using b = utils::bits<0b11111111, 0b11001000 | Reg>; };

  // push
  DEFINSTR(push);
  template <uint8_t Reg> struct push<Reg::reg<32, Reg>> : Ins::ConstBase { using b = utils::bits<0b01010000 | Reg>; };

  // pop
  DEFINSTR(pop);
  template <uint8_t Reg> struct pop<Reg::reg<32, Reg>> : Ins::ConstBase { using b = utils::bits<0b01011000 | Reg>; };

  // nop
  DEFINSTR(nop);
  template <> struct nop<> : Ins::ConstBase { using b = utils::bits<0b10010000>; };

  // add
  DEFINSTR(add);
  template <uint8_t Reg1, uint8_t Reg2> struct add<Reg::reg<32, Reg1>, Reg::reg<32, Reg2>> : Ins::ConstBase { using b = utils::bits<0b00000001, 0b11000000 | (Reg1 << 3) | (Reg2)>; }; // TODO : find the difference between 0b00000001 and 0b00000011

  // int
  template <uint8_t I > struct Int : Ins::ConstBase { using b = utils::bits<0b11001101, I>;};
  template <> struct Int<3> : Ins::ConstBase { using b = utils::bits<0b11001100>; };

}
