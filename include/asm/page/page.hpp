#pragma once
#include <sys/mman.h>
#include <new> // bad_alloc
#include <unistd.h>

namespace Page
{

// TODO : share
static const size_t pagesize = sysconf(_SC_PAGESIZE);

struct Page
{
  Page()
  {
    page = mmap(nullptr, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (page == MAP_FAILED)
      throw std::bad_alloc();
  }
  ~Page()
  {
    munmap(page, pagesize);
  }

  void * data()
  {
    return page;
  }

  private:
  void *page;

};

}
