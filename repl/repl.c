#include "repl.h"

static void info(void)
{
  printf("REPL Commands: \n");
  printf("  help -- REPL Commands Help\n");
  printf("  show -- REPL current stack variables\n");
  printf("  env -- REPL ENV variables\n");
  printf("Current command abbreviations (type 'help command alias' for more info): \n");
  printf("For more information on any command, type 'help <command-name>'\n");
}

void help_handle(void * restrict input)
{
  info();
}

void show_handle(void * restrict input)
{
  info();
}

void env_handle(void * restrict input)
{
  info();
}

REPL repl_allocate()
{
  return allocate(1, sizeof(struct repl));
}

int repl_free(REPL * restrict str)
{
  if (NULL == *str) return -1;
  free(*str);
  return 0;
}
