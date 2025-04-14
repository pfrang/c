#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define PORT2 3000
#define BUFFERSIZE 1024

int main() {
    int sockfd1, sockfd2, rc, max_fd;
    fd_set read_fds;
    char buffer[BUFFERSIZE];

    struct sockaddr_in serverAddr1, serverAddr2;
    socklen_t len1, len2;

    serverAddr1.sin_family = AF_INET;
    serverAddr1.sin_addr.s_addr = INADDR_ANY;
    serverAddr1.sin_port = htons(PORT);

    serverAddr2.sin_family = AF_INET;
    serverAddr2.sin_addr.s_addr = INADDR_ANY;
    serverAddr2.sin_port = htons(PORT2);

    len1 = sizeof(serverAddr1);
    len2 = sizeof(serverAddr2);

    sockfd1 = socket(AF_INET, SOCK_DGRAM, 0);
    sockfd2 = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd1 < 0) {
        perror("socket");
        return -1;
    }

    if (sockfd2 < 0) {
        perror("socket");
        return -1;
    }

    if (bind(sockfd1, (struct sockaddr *)&serverAddr1, sizeof(serverAddr1)) < 0) {
        perror("bind sockfd1");
        return -1;
    }

    if (bind(sockfd2, (struct sockaddr *)&serverAddr2, sizeof(serverAddr2)) < 0) {
        perror("bind sockfd2");
        return -1;
    }

    printf("Server is listening on ports %d and %d\n", PORT, PORT2);

    max_fd = (sockfd1 > sockfd2 ? sockfd1 : sockfd2);
    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(sockfd1, &read_fds);
        FD_SET(sockfd2, &read_fds);

        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0) {
            perror("select");
            close(sockfd1);
            close(sockfd2);
            return -1;
        }

        if (FD_ISSET(sockfd1, &read_fds)) {
            memset(buffer, 0, BUFFERSIZE);
            rc = recvfrom(sockfd1, buffer, BUFFERSIZE, 0, (struct sockaddr *)&serverAddr1, &len1);
            if (rc < 0) {
                perror("recvfrom");
            }

            printf("Message from port %d was %s\n", PORT, buffer);
        }

        if (FD_ISSET(sockfd2, &read_fds)) {
            memset(buffer, 0, BUFFERSIZE);
            rc = recvfrom(sockfd2, buffer, BUFFERSIZE, 0, (struct sockaddr *)&serverAddr2, &len2);
            if (rc < 0) {
                perror("recvfrom");
            }

            printf("Message from port %d was %s\n", PORT2, buffer);
        }
    }

    close(sockfd1);
    close(sockfd2);

    return 0;
}
