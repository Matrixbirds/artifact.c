#include "utils.h"

int main(int argc, char * argv[]) {
  socket_util *socket = NULL;
  allocate(&socket);
  init_tcp_socket_loop(&socket);
  return 0;
}

