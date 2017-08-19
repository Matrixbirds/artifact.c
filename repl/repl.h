#ifndef __REPL_H__
#define __REPL_H__

#include <stdio.h>
#include <stdlib.h>

enum {
  help = 0,
  version,
  env
};

void help_handle(void *);
void version_handle(void *);
void env_handle(void *);

typedef void (*actions[])(void *input);

struct repl {
  void *env;
  actions commands;
} _repl = {
  NULL,
  {
    help_handle,
    version_handle,
    env_handle,
  }
};

typedef _repl * REPL;

REPL repl_allocate();
int repl_free(REPL * restrict str);

#endif
