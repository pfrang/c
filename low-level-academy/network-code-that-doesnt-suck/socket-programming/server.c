#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef enum {
  PROTO_HELLO,
} proto_type_e;

// TLV - how big the data is and the type
typedef struct {
  proto_type_e type;
  unsigned short len;
} proto_hdr_t;

void handle_client(int fd) {
  char buf[4096] = {0};
  proto_hdr_t *hdr = buf;
  hdr->type = htonl(PROTO_HELLO);
  hdr->len = htons(sizeof(int));
  int reallen = hdr->len;
  hdr->len = htons(hdr->len);

  int *data = (int *)&hdr[1];
  *data = htonl(1);

  write(fd, hdr, sizeof(proto_hdr_t) + reallen);
}

int main() {

  struct sockaddr_in serverInfo = {0};

  struct sockaddr_in clientInfo = {0};

  int clientSize = 0;
  serverInfo.sin_family = AF_INET; // IPv4
  serverInfo.sin_addr.s_addr = 0; // we are accepting connections from every iip
  serverInfo.sin_port = htons(5555);
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0); // its the same as open()
  if (serverSocket == -1) {
    perror("socket");
    return -1;
  }

  printf("%d\n", serverSocket);

  // bind -- To What port etc
  if (bind(serverSocket, (struct sockaddr *)&serverInfo, sizeof(serverInfo)) ==
      -1) {
    perror("bind");
    close(serverSocket);
    return -1;
  }
  // listen
  if (listen(serverSocket, 0) == -1) {
    perror("listen");
    close(serverSocket);
    return -1;
  }; // Second argument is how many processes it can put in baclog. 0 means
     // unlimited

  while (1) {
    int cfd = accept(serverSocket, (struct sockaddr *)&clientInfo, &clientSize);

    if (cfd == -1) {
      perror("accept");
      close(serverSocket);
      return -1;
    }

    handle_client(cfd);

    close(cfd);
  }
  // accept
}
