#ifndef __ALLOC_INC_H__
#define __ALLOC_INC_H__
#include "common.hpp"
#include "types.hpp"
#include "debug.hpp"

#define alloc_printf(_str...) ({                     \
    u8* _tmp;                                        \
    s32 _len = snprintf(NULL, 0, _str);              \
    if (_len < 0) FATAL("Whoa, snprintf() fails?!"); \
    _tmp = ck_alloc(_len + 1);                       \
    snprintf((char*)_tmp, _len + 1, _str);           \
    _tmp;                                            \
  })

/* Allocate a buffer, returning zeroed memory. */

static inline void* ck_alloc(u32 size) {

  void* mem;

  if (!size) FATAL("alloc size is zero");

  mem = malloc(size + 1);

  if (mem == NULL)
    PANIC("malloc failed");

  return memset(mem, 0, size + 1);

}


#endif