#ifndef __UTIL_H__
#define __UTIL_H__

#include "defs.h"

#define define_method(method, ...) \
  method(__VA_ARGS__); \

void fail(void *msg);

#endif
