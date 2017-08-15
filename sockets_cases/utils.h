#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <unistd.h>


#define ADDRESS "127.0.0.1"
#define PORT 5399
#define WAIT_COUNT 128

void rescue(void *msg) {
  fprintf(stderr, "[%s]: %s\n", msg, strerror(errno));
  exit(1);
}

typedef struct _socket_util
{
  struct sockaddr_in *addr;
  unsigned int addr_len;
  int fd;
} socket_util;

void allocate(socket_util **ptr) {
  *ptr = malloc(sizeof(*ptr));
  (*ptr)->addr = malloc(sizeof(struct sockaddr_in));
  (*ptr)->addr_len = sizeof(struct sockaddr_in);
  (*ptr)->fd = 0;
}

void release(socket_util **ptr) {
  free((*ptr)->addr);
  free((*ptr));
  (*ptr)->addr = 0;
  *ptr = 0;
}

void init_tcp_socket_loop(socket_util **ptr) {
  (*ptr)->fd = socket(AF_INET, SOCK_STREAM, 0);
  if ((*ptr)->fd < 0) rescue("socket");
  (*ptr)->addr->sin_family = AF_INET;
  (*ptr)->addr->sin_addr.s_addr = inet_addr(ADDRESS);
  (*ptr)->addr->sin_port = htons(PORT);
  if (setsockopt((*ptr)->fd, SOL_SOCKET, SO_REUSEPORT, &(int) { 1 }, sizeof(int)) < 0) rescue("setsockopt");
  if ( bind((*ptr)->fd, (struct sockaddr *)(*ptr)->addr, (*ptr)->addr_len) < 0 ) rescue("bind");
  if ( listen((*ptr)->fd, WAIT_COUNT) < 0) rescue("listen");
  printf("listening in [%ld]\n", (long)getpid());
  while (true)
  {
    int fd = accept((*ptr)->fd, (struct sockaddr*)(*ptr)->addr, &(*ptr)->addr_len);
    if (fd < 0) rescue("accept");
    if (fork() == 0)
    {
      close((*ptr)->fd);
      char buffer[4096];
      read(fd, buffer, 4096);
      printf("read size %lu\n", strlen(buffer));
      close(fd);
      release(ptr);
      exit(0);
    }
    close(fd);
  }
  release(ptr);
  return;
}

#endif
