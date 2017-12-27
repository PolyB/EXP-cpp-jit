#include "../include/asm/program.hpp"
#include "../include/asm/page/page.hpp"
#include <iostream>
#include <cassert>

struct vars
{
  uint32_t ret;
};

using namespace Asm;

using Prgm = Asm::program<
              mov<imm<&vars::ret>, EAX>,
              ret<>
              >;

int main()
{
  Page::Page p;

  Prgm::copyTo(p.data());

  int (*f)() = reinterpret_cast<int(*)()>(p.data());


  Prgm::remplace(p.data(), vars{ .ret = 1337 });

  assert(f() == 1337);

  Prgm::remplace(p.data(), vars{ .ret = 1338 });

  assert(f() == 1338);
}
