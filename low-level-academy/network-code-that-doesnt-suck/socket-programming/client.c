#include <arpa/inet.h>
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

// Reads the hdr content TLV sent in from server
void handle_client(int fd) {
    char buf[4096] = {0};
    read(fd, buf, sizeof(proto_hdr_t) + sizeof(int)); // Will read all header data + 4 bytes ahead
    char a[10];
    proto_hdr_t *hdr = buf;

    int h = 2;
    hdr->type = ntohl(hdr->type);
    hdr->len = ntohs(hdr->len);

    int *data = &hdr[1]; // This basically points to the next byte after the
                         // memory allocated by hdr of type proto_hdr_t
    *data = ntohl(*data);

    if (hdr->type != PROTO_HELLO) {
        printf("Protocol mismatch. failing.\n");
    }

    if (*data != 1) {
        printf("Protocol version mimatch, failing.\n");
        return;
    }

    printf("Server connected, protocol v1. \n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <ip of the host>\n", argv[0]);
        return 0;
    }

    struct sockaddr_in serverInfo = {0};

    serverInfo.sin_family = AF_INET;                 // IPv4
    serverInfo.sin_addr.s_addr = inet_addr(argv[1]); // What address we want to connect to
    serverInfo.sin_port = htons(5555);
    int fd = socket(AF_INET, SOCK_STREAM, 0); // its the same as open()
    if (fd == -1) {
        perror("socket");
        return -1;
    }

    if (connect(fd, (struct sockaddr *)&serverInfo, sizeof(serverInfo)) == -1) {
        perror("connect");
        close(fd);
        return 0;
    }

    handle_client(fd);

    close(fd);
}
