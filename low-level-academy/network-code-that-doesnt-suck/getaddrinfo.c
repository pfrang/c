
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  struct addrinfo hints, *res;
  int errcode;
  char addrstr[100];
  void *ptr;

  if (argc != 2) {
    printf("Usage: %s hostname\n", argv[0]);
    return 1;
  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  errcode = getaddrinfo(argv[1], NULL, &hints, &res);
  if (errcode != 0) {
    perror("getaddrinfo");
    return 1;
  }

  printf("Host: %s\n", argv[1]);
  while (res) {
    inet_ntop(res->ai_family, res->ai_addr->sa_data, addrstr, 100);

    switch (res->ai_family) {
    case AF_INET:
      ptr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
      break;
    case AF_INET6:
      ptr = &((struct sockaddr_in6 *)res->ai_addr)->sin6_addr;
      break;
    }
    inet_ntop(res->ai_family, ptr, addrstr, 100);
    printf("IPv%d address: %s\n", res->ai_family == PF_INET6 ? 6 : 4, addrstr);
    res = res->ai_next;
  }

  return 0;
}
