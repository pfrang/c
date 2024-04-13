#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080

void initialize_server(int *serverSocket) {
    struct sockaddr_in server_client;

    server_client.sin_family = AF_INET;
    server_client.sin_addr.s_addr = INADDR_ANY;
    server_client.sin_port = htons(PORT);

    if ((*serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    if (bind(*serverSocket, (struct sockaddr *)&server_client, sizeof(server_client)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(*serverSocket, 10) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);
}

int main() {
    fd_set readfds;
    int serverSocket, fd1 = -1, fd2 = -1, nfds;
    socklen_t addrlen;
    struct sockaddr_in client1, client2;
    char buffer[1024];
    initialize_server(&serverSocket);

    // Wait for input on either socket
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(serverSocket, &readfds);
        if (fd1 != -1)
            FD_SET(fd1, &readfds);
        if (fd2 != -1)
            FD_SET(fd2, &readfds);
        nfds = (fd1 > fd2 ? fd1 : fd2);
        nfds = (serverSocket > nfds ? serverSocket : nfds) + 1;
        printf("server socket %d\n", serverSocket);
        if (select(nfds, &readfds, NULL, NULL, NULL) > 0) {
            if (FD_ISSET(serverSocket, &readfds)) {
                int newfd;
                struct sockaddr_in newclient;
                addrlen = sizeof(newclient);
                // Check for any new connection
                if ((newfd = accept(serverSocket, (struct sockaddr *)&newclient, &addrlen)) == -1) {
                    perror("accept");
                    continue;
                }
                if (fd1 == -1) {
                    fd1 = newfd;
                    client1 = newclient;
                    printf("New connection on fd %d from port %d\n", fd1, ntohs(client1.sin_port));
                } else if (fd2 == -1) {
                    fd2 = newfd;
                    client2 = newclient;
                    printf("New connection on fd %d from port %d\n", fd2, ntohs(client2.sin_port));
                } else {
                    printf("Server is full\n");
                    close(newfd); // Close the new connection immediately
                }
            }
            if (fd1 != -1 && FD_ISSET(fd1, &readfds)) {
                memset(buffer, 0, sizeof(buffer));
                if (read(fd1, buffer, sizeof(buffer)) > 0) {
                    printf("Received from fd1, %d: %s\n", fd1, buffer);
                } else {
                    close(fd1);
                    printf("Client on fd1, %d, disconnected with addr %s\n", fd1, inet_ntoa(client1.sin_addr));
                    fd1 = -1;
                }
            }

            if (fd2 != -1 && FD_ISSET(fd2, &readfds)) {
                memset(buffer, 0, sizeof(buffer));
                if (read(fd2, buffer, sizeof(buffer)) > 0) {
                    printf("Received from fd2, %d,: %s\n", fd2, buffer);
                } else {
                    close(fd2);
                    printf("Client on fd2, %d, disconnected with addr %s\n", fd2, inet_ntoa(client2.sin_addr));
                    fd2 = -1;
                }
            }
        } else {
            perror("select");
            printf("Something bad happened");
        }
    }
}
