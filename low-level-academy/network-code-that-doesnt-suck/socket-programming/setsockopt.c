#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int listen_fd, nfds, conn_fd;
    struct sockaddr_in client_addr, server_addr;
    int opt = -1;
    // socket
    socklen_t clientSize = sizeof(client_addr);
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // setsockopt function is particularly important for controlling the behavior of sockets at a lower level
    // enabling features like address reuse, time-out adjustments, and buffer size modifications.

    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_port = htons(PORT);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(listen_fd, 10) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    struct pollfd fds[10];

    memset(fds, 0, sizeof(fds));
    fds[0].fd = listen_fd;
    fds[0].events = POLLIN;
    nfds = 1;

    while (1) {

        int n_events = poll(fds, nfds, -1);
        if (n_events == -1) {
            perror("poll");
            exit(EXIT_FAILURE);
        }

        if (fds[0].revents & POLLIN) {
            if ((conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &clientSize)) == -1) {
                perror("accept");
                continue;
            }

            printf("New connection from %s from port %d\n", inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port));
            fds[nfds].fd = conn_fd;
            fds[nfds].events = POLLIN;
            nfds++;
            n_events--; // Decrement because we have now connected
        }

        for (int i = 1; i <= nfds && n_events > 0; i++) {
            if (fds[i].revents & POLLIN) {
                n_events--;
                char buff[1000];
                ssize_t bytes_read = read(fds[i].fd, &buff, sizeof(buff));
                if (bytes_read <= 0) {
                    close(fds[i].fd);
                    printf("Client disconnected %s from port %d\n", inet_ntoa(client_addr.sin_addr),
                           ntohs(client_addr.sin_port));
                    nfds--;
                    i--; // Decrement i to compensate for the shift
                } else {
                    buff[bytes_read] = '\0';
                    printf("Received data on fd %d, data: %s\n", fds[i].fd, buff);
                }
            }
        }
    }

    return 0;
}
