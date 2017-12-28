#pragma once

#include <cstdint>
#include <array>
#include <iostream>

namespace Asm
{
namespace utils
{
  template<uint8_t...B>
  struct bits{
    static constexpr size_t size = sizeof...(B);
    static void print(std::ostream& os)
    {
      os << std::hex;
      int unused[] = {(os << (int)B << ' ', 0)...};
      (void)unused;
    }
  };

  template <class...> struct tl{};

  template <class, uint8_t...>
    struct foldjoin{};
  template <uint8_t...N>
    struct foldjoin<tl<>, N...>
    {
      using type = foldjoin<tl<>, N...>;
      static constexpr std::array<uint8_t, sizeof...(N)> value{{N...}};
    };
  template <class...I, uint8_t ...B, uint8_t...N>
    struct foldjoin<tl<bits<B...>, I...>, N...>
    {
      using type = typename foldjoin<tl<I...>, N..., B...>::type;
    };


  template <auto A>
  class intsplit
  {
    private:
    static constexpr std::array<uint8_t, sizeof (A)> cvalue()
    {
      std::array<uint8_t, sizeof (A)> res{};
      for (uint8_t i = 0; i < sizeof (A); i++)
        res[i] = (A >> (i * 8)) & 0xFF;
      return res;
    }
    public:
    static constexpr auto value = cvalue();
  };

  template <class C> struct smartsizeof{};

  template <> struct smartsizeof<uint8_t> { static constexpr uint8_t size = 1; };
  template <> struct smartsizeof<uint16_t> { static constexpr uint8_t size = 2; };
  template <> struct smartsizeof<uint32_t> { static constexpr uint8_t size = 4; };
  template <> struct smartsizeof<uint64_t> { static constexpr uint8_t size = 8; };
  template <> struct smartsizeof<int8_t> { static constexpr uint8_t size = 1; };
  template <> struct smartsizeof<int16_t> { static constexpr uint8_t size = 2; };
  template <> struct smartsizeof<int32_t> { static constexpr uint8_t size = 4; };
  template <> struct smartsizeof<int64_t> { static constexpr uint8_t size = 8; };
  // ignore the case when returning a pointer to member function
  template <class C, class R> struct smartsizeof<R (C::*)> { static constexpr uint8_t size = smartsizeof<R>::size; };
  // size of a pointer
  template <class C> struct smartsizeof<C*> { static constexpr uint8_t size = 8; };
  // size of a pointer to fun (don't know why clang don't match a ptr)
  template <class C, class... Args> struct smartsizeof<C(*)(Args...)> { static constexpr uint8_t size = sizeof (C*); };


  template <class C> struct make_unsigned{};

  template <> struct make_unsigned<uint8_t>   { using type = uint8_t; };
  template <> struct make_unsigned<uint16_t>  { using type = uint16_t; };
  template <> struct make_unsigned<uint32_t>  { using type = uint32_t; };
  template <> struct make_unsigned<uint64_t>  { using type = uint64_t; };
  template <> struct make_unsigned<int8_t>    { using type = uint8_t; };
  template <> struct make_unsigned<int16_t>   { using type = uint16_t; };
  template <> struct make_unsigned<int32_t>   { using type = uint32_t; };
  template <> struct make_unsigned<int64_t>   { using type = uint64_t; };
  template <class C, class R> struct make_unsigned<R (C::*)>   { using type = typename make_unsigned<R>::type (C::*); };
  // a ptr is a uint64_t
  template <class C> struct make_unsigned<C*> { using type = uint64_t; };

}
}
