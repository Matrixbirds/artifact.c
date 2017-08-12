#include "util.h"

void fail(void *msg) {
  fprintf(stderr, "[%s]: throw exception %s", msg, strerror(errno));
  exit(-1);
}
