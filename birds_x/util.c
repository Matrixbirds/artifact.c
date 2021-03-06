#include "util.h"

void fail(void * restrict msg) {
  goto error;
error:
  fprintf(stderr, "[%s]: throw exception %s", msg, strerror(errno));
  exit(-1);
}
