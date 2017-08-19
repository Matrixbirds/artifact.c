#include "repl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  REPL repl = repl_allocate();
  repl->start(":> ");
  repl_free(&repl);
  if (NULL == repl) printf("repl is NULL\n");
  return 0;
}
