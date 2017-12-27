#pragma once
#include "ins.hpp"
#include <cstring> // memcpy

namespace Asm
{
  template <class...C>
  struct program
  {
    static constexpr size_t size = (C::b::size+...);
    static void inline copyTo(void *dst)
    {
      std::memcpy(dst, utils::foldjoin<utils::tl<typename C::b...>>::type::value.data(), size);
    }

    template <class T>
    static void inline remplace(void * dst, T t)
    {
      char unused[] = { (C::copy((uint8_t *)dst, t), '\0')... };
      (void)unused;
    }
  };
}
