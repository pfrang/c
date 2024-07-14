#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    int listen_fd, conn_fd;

    struct sockaddr_in servaddr, cliaddr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;

    if (listen_fd == -1) {
        perror("socket");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8080);
    // setsockopt

    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        return -1;
    }

    if (bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind");
        return -1;
    }

    if (listen(listen_fd, 10) == -1) {
        perror("listen");
        return -1;
    }

    printf("Listening on port 8080\n");

    socklen_t cliaddr_len = sizeof(cliaddr);

    while (1) {

        conn_fd = accept(listen_fd, (struct sockaddr *)&cliaddr, &cliaddr_len);
        if (conn_fd == -1) {
            perror("accept");
            continue;
        }

        printf("Accepted connection\n");

        char buffer[1024];
        int n = read(conn_fd, buffer, 1024);
        if (n == -1) {
            perror("read");
            return -1;
        }

        printf("----------Received----------: \n%s\n", buffer);

        char *response = "HTTP/1.1 200 OK\nContent-Length: 12\n\nHello World!\n";

        n = write(conn_fd, response, strlen(response));

        if (n == -1) {
            perror("write");
            return -1;
        }

        close(conn_fd);
    }
}
