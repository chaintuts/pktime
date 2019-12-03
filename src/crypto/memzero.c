#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1  // C11's bounds-checking interface.
#endif
#include <string.h>
#include "memzero.h"

// Adapted from
// https://github.com/jedisct1/libsodium/blob/1647f0d53ae0e370378a9195477e3df0a792408f/src/libsodium/sodium/utils.c#L102-L130

void memzero(void *const pnt, const size_t len) {

  volatile unsigned char *volatile pnt_ = (volatile unsigned char *volatile)pnt;
  size_t i = (size_t)0U;

  while (i < len) {
    pnt_[i++] = 0U;
  }
}
