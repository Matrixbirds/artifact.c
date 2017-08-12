#include "server.h"

char buffer[BUFFER_SIZE];

void create_socket(birds_socket_t* const* const birds) {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    fail("create socket failured");
  }
  (*birds)->sock_fd = fd;
}

int bind_socket(birds_socket_t* const* const birds) {
  (*birds)->address->sin_family = AF_INET;
  (*birds)->address->sin_port = htons(PORT);
  (*birds)->address->sin_addr.s_addr = inet_addr("127.0.0.1");
  int fd;
  if ((fd = setsockopt((*birds)->sock_fd, SOL_SOCKET, SO_REUSEPORT, &(int) { 1 }, sizeof(int))) < 0) {
    fail("setsockopt failured");
  }
  if ((fd = bind((*birds)->sock_fd, (struct sockaddr *)(*birds)->address, sizeof((*(*birds)->address)))) < 0) {
    fail("bind socket failured");
  }
  return fd;
}

int listen_socket(birds_socket_t* const* const birds) {
  int fd = listen((*birds)->sock_fd, MAX_CONNECTIONS);
  if (fd < 0) {
    fail("listen socket failured");
  }
  return fd;
}

int init_socket_loop(birds_socket_t** const birds) {
  while (1) {
    int accept_fd = create_accept(birds);
    int len = 0;
    bzero(&buffer, sizeof(BUFFER_SIZE));
    printf("%s\n", buffer);
    recv_all(&accept_fd, &buffer, sizeof(BUFFER_SIZE));
    send_all(&accept_fd, &buffer, strlen(buffer));
    close(accept_fd);
  }
  printf("Done\n");
  close((*birds)->sock_fd);
}

int create_accept(birds_socket_t* const* const birds) {
  int fd;
  ssize_t len = sizeof((*(*birds)->address));
  if ((fd = accept((*birds)->sock_fd, (struct sockaddr*)(*birds)->address, &len)) < 0) {
    fail("create accept socket failured");
  }
  return fd;
}

void allocate(birds_socket_t** const birds) {
  *birds = malloc(sizeof(birds_socket_t));
  (*birds)->address = malloc(sizeof(struct sockaddr_in));
  (*birds)->sock_fd = -1;
}

void release(birds_socket_t** birds) {
  free((*birds)->address);
  free((*birds));
  *birds = NULL;
}

void send_all(const int* const socket, void* buffer, size_t length) {
  char *ptr = (char *) buffer;
  while (length > 0)
  {
    int i = send(*socket, ptr, length, MSG_DONTROUTE);
    if (i < 0) fail("send failure");
    if (i < 1) break;
    ptr += i;
    length -= i;
  }
}

void recv_all(const int* const socket, void* buffer, size_t length) {
  char *ptr = (char *) buffer;
  while (length > 0)
  {
    int i = recv(*socket, ptr, length, MSG_PEEK);
    if (i < 0) fail("recv failure");
    if (i < 1) break;
    ptr += i;
    length -= i;
  }
}
