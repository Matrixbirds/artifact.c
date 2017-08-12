#include <stdio.h>
#include <strings.h>

#include "server.h"

int main(int argc, char *argv[]) {
  birds_socket_t *birds = NULL;
  allocate(&birds);
  create_socket(&birds);
  bind_socket(&birds);
  listen_socket(&birds);
  init_socket_loop(&birds);
  release(&birds);
  return 0;
}
