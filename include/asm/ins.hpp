#pragma once
#include "imm.hpp"
#include "reg.hpp"
#include "utils.hpp"

#define DEFINSTR(S) \
  template <class... C> struct S{ static_assert(false && sizeof...(C), "invalid "#S); }

namespace Asm
{
  namespace Ins
  {
    // TODO
  }
  // mov
  DEFINSTR(mov);
  template <auto Imm, uint8_t Reg, class ImmT> struct mov<Imm::imm<32, ImmT, Imm>, Reg::reg<32, Reg>>{
    using Imm_ = typename Imm::imm<32, ImmT, Imm>::type;
    using b = utils::bits<0b10111000 | Reg, Imm_::b[0], Imm_::b[1], Imm_::b[2], Imm_::b[3]>;

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

  // ret
  DEFINSTR(ret);
  template <> struct ret<>{
    using b = utils::bits<0b11000011>;
    static constexpr bool r = false;
    template <class T> static inline void copy(uint8_t*, const T&){};
  };

}
