#include "../include/asm/program.hpp"
#include <iostream>

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
  std::array<uint8_t, Prgm::size> s{};
  Prgm::copyTo(s.data());
  std::cout << std::hex;
  for (uint8_t i : s)
    std::cout << (int)i << ' ';
  std::cout << std::endl;
  Prgm::remplace(s.data(),
                  vars{ .ret = 0xFFFF });
  for (uint8_t i : s)
    std::cout << (int)i << ' ';
  std::cout << std::endl;
}
