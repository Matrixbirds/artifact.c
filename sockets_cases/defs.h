#ifndef __DEFS_H__
#define __DEFS_H__

#define SERVER_ADDRESS
#define SERVER_PORT

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
void rescue(void *msg) {
  fprintf(stderr, "[%s]: %s\n", msg, strerror(errno));
  exit(1);
}

#endif
