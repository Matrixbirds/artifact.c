#include "defs.h"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>

#define IP4_HDRLEN 20
#define TCP_HDRLEN 20

int create_raw_socket(void) {
  int fd;
  if ((fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
    rescue("socket");
  return fd;
}

typedef struct _virtual_ip {
  char *interface;
  char *src_ip;
  char *dst_ip;
  char *target;
  struct addrinfo hints;
} v_ip;

typedef v_ip * ip_ptr;

typedef struct _virtual_tcp {
  ip_ptr ip_segment;
  struct ifreq ifr;
} v_tcp;

typedef v_tcp * tcp_ptr;

void allocate_ip_segment(ip_ptr * const ip_segment) {
  *ip_segment = calloc(0, sizeof(v_ip));
  if (NULL == *ip_segment) rescue("calloc");
}

void allocate_v_tcp(tcp_ptr * const ptr) {
  *ptr = calloc(0, sizeof(v_tcp));
  if (NULL == *ptr) rescue("calloc");
  allocate_ip_segment(&(*ptr)->ip_segment);
}

char *allocate_charmem(int size)
{
  void *tmp = NULL;
  if (size <= 0) rescue("size invalid size must be >= 0");
  tmp = calloc(0, size * sizeof(char));
  if (NULL == tmp) rescue("calloc");
  return tmp;
}

int *allocate_intmem(int size)
{
  void *tmp = NULL;
  if (size <= 0) rescue("size invalid size must be >= 0");
  tmp = calloc(0, size * sizeof(int));
  if (NULL == tmp) rescue("calloc");
  return tmp;
}

void fill_ip_segment(tcp_ptr * const ptr, int * const fd)
{
  (*ptr)->ip_segment->interface = allocate_charmem(1);
  strcpy((*ptr)->ip_segment->interface, "lo0");
  memset(&(*ptr)->ifr, 0, sizeof((*ptr)->ifr));
  snprintf((*ptr)->ifr.ifr_name, sizeof((*ptr)->ifr.ifr_name), "%s", (*ptr)->ip_segment->interface);
  if (ioctl(*fd, SIOCGIFADDR, &(*ptr)->ifr) < 0)
    rescue("ioctl");
  close(*fd);
  printf("Index for interface %s\n", (*ptr)->ip_segment->interface);
  ip_ptr * const ip = &(*ptr)->ip_segment;
  (*ip)->src_ip = allocate_charmem(1);
  strcpy((*ip)->src_ip, "127.0.0.1");
  (*ip)->target = allocate_charmem(1);
  strcpy((*ip)->target, "localhost");
  (*ip)->dst_ip = allocate_charmem(1);
  memset(&(*ip)->hints, 0, sizeof(struct addrinfo));
  (*ip)->hints.ai_family = AF_INET;
  (*ip)->hints.ai_socktype = SOCK_STREAM;
  (*ip)->hints.ai_flags = (*ip)->hints.ai_flags | AI_CANONNAME;
  int status;
  struct addrinfo *res;
  if ((status = getaddrinfo((*ip)->target, NULL, &(*ip)->hints, &res)) != 0)
    rescue("getaddrinfo");
  struct sockaddr_in *ipv4 = (struct sockaddr_in *) res->ai_addr;
  void *tmp = &(ipv4->sin_addr);
  if (inet_ntop(AF_INET, tmp, (*ip)->dst_ip, INET_ADDRSTRLEN) == NULL) {
    status = errno;
    rescue("inet_ntop");
  }
  freeaddrinfo(res);
}

int main(int argc, char *argv[])
{
  tcp_ptr tcp;
  int fd = create_raw_socket();
  allocate_v_tcp(&tcp);
  fill_ip_segment(&tcp, &fd);
  return 0;
}

