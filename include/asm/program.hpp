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
      uint8_t *ptr = reinterpret_cast<uint8_t*>(dst);
      char unused[] = { (C::copy(ptr, t), ptr += C::b::size, '\0')... };
      (void)unused;
    }
  };
}
