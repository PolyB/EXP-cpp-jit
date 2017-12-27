#pragma once
#include <array>
#include <cstdint>
#include "utils.hpp"

namespace Asm
{
  namespace Imm
  {

    template <class Int, Int I>
    struct ImmStaticImpl
    {
      static constexpr std::array<uint8_t, sizeof (Int)> b = utils::intsplit<I>::value;
      static constexpr bool r = false;
      template <class>
      using dep = std::false_type;
    };

    template <class C, class Int, Int (C::*I)>
    struct ImmDynamicImpl
    {
      static constexpr std::array<uint8_t, sizeof (Int)> b = {{0, }};
      static constexpr bool r = true;
      template <class A>
      using dep = std::is_same<A, C>;
      template <uint8_t Byte>
      static inline uint8_t get(C& c)
      {
        return (&c->*I >> (Byte * 8)) & 0xFF;
      };
    };

    template <uint8_t I, class, auto>
    struct imm {
      static_assert(false && I, "invalid immediate");
    };
    template <uint32_t I>
    struct imm<32, uint32_t, I>
    {
      using type = ImmStaticImpl<uint32_t, I>;
    };
    template <class C, uint32_t (C::*I)>
    struct imm<32, uint32_t (C::*), I>
    {
      using type = ImmDynamicImpl<C, uint32_t, I>;
    };
  }

  template<auto O>
  using imm = Imm::imm<utils::smartsizeof<decltype(O)>::size * 8, typename utils::make_unsigned<decltype(O)>::type, (typename utils::make_unsigned<decltype(O)>::type)O>;

  template<uint8_t size, auto O>
  using castimm = Imm::imm<size, decltype(O), O>;

}
