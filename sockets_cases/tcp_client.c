#include "utils.h"

#define SER_IP "127.0.0.1"

int main(int argc, char *argv[]) {
  socket_util *sock = NULL;
  allocate(&sock);
  sock->fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock->fd < 0)
    rescue("sock");
  sock->addr->sin_family = AF_INET;
  inet_pton(AF_INET, SER_IP, &sock->addr->sin_addr);
  sock->addr->sin_port = htons(PORT);

  if (connect(sock->fd, (struct sockaddr*)sock->addr, sock->addr_len) < 0)
    rescue("connect");

  char s[] = "loremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremloremlorem";
  write(sock->fd, s, strlen(s)+1);
  printf("write length: %lu\n", strlen(s)+1);
  printf("Done\n");
  close(sock->fd);

  return 0;
}
