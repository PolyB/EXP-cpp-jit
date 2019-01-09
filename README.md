# cpp-jit
Building jitted code at compile-time with c++ templates (Proof of Concept).


## exemple

```cpp
#include "../include/asm/program.hpp"
#include "../include/asm/page/page.hpp"
#include <cassert>
#include <iostream>

struct vars
{
  uint32_t ret;
};

using namespace Asm;

using Prgm = Asm::program<
              push<EBX>,
              mov<imm<12>, EAX>,
              mov<imm<&vars::ret>, EBX>,
              add<EBX, EAX>,
              pop<EBX>,
              ret<>
              >;

extern "C" using fptr = uint32_t (*)();

int main()
{
  Page::Page p;

  Prgm::copyTo(p.data());
  fptr f = reinterpret_cast<uint32_t(*)()>(p.data());

  Prgm::remplace(p.data(), vars{ .ret = 1337 });
  assert(f() == 1337 + 12);

  Prgm::remplace(p.data(), vars{ .ret = 1338 });

  assert(f() == 1338 + 12);
}
```

## test
This code can be tested with
```sh
cd test
make t1
./t1
```
