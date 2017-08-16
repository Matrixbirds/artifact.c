#ifndef __SERVER_H__
#define __SERVER_H__

#include "defs.h"

#define BUFFER_SIZE 512
#define MAX_CONNECTIONS 512
#define PORT 4399
#define BIRDS_RESPONSE_HEADER "Birds_X: RESPONSE HEADER\n"

typedef struct {
  struct sockaddr_in *address;
  socklen_t address_len;
  int sock_fd;
} birds_socket_t;

void create_socket(birds_socket_t * const * restrict);
int create_accept(birds_socket_t * const * restrict);
int bind_socket(birds_socket_t * const * restrict);
int listen_socket(birds_socket_t * const * restrict birds);
int init_socket_loop(birds_socket_t ** restrict);
void allocate(birds_socket_t ** restrict);
void release(birds_socket_t ** restrict);

define_method(void recv_all, const int * restrict socket, void * restrict buffer, size_t length);
define_method(void send_all, const int * restrict socket, void * restrict buffer, size_t length);

#endif
