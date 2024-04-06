#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CLIENTS 256
#define PORT 8080
#define BUFF_SIZE 4096

typedef enum { STATE_NEW, STATE_CONNECTED, STATE_DISCONNCECTED } state_e;

// Structure to hold client state
typedef struct {
    int fd;
    state_e state;
    char buffer[BUFF_SIZE];
} clientstate_t;

clientstate_t clientStates[MAX_CLIENTS];

void init_clients() {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clientStates[i].fd = -1; // -1 indicates a free slot
        clientStates[i].state = STATE_NEW;
        memset(&clientStates[i].buffer, '\0', BUFF_SIZE); // Clear the buffer from previous user, set all to 0
    }
}

int find_free_slot() {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clientStates[i].fd == -1) {
            return i; // Returns index of max client FDs. See above that -1 indicates a free slot in init_clients
        }
    }
    return -1; // No free slot found
}

int main() {
    int listen_fd, conn_fd, nfds, freeSlot;
    struct sockaddr_in server_addr, client_addr;

    socklen_t client_len = sizeof(client_addr);

    fd_set read_fds, write_fds; // What fds are readable, which are writeable

    // Initialize client states
    init_clients();

    // Create listening socket
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind
    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(listen_fd, 10) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Clear the FD sets
        //
        // 000111001001 old state => 00000000000000

        FD_ZERO(&read_fds);
        FD_ZERO(&write_fds);

        // Add the listening socket to the read set
        // OR bits we wanna check in our fd_set
        FD_SET(listen_fd, &read_fds);
        // Input to select, the highest fd + 1
        nfds = listen_fd + 1;

        // Add active connections to the read set
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clientStates[i].fd != -1) { // Checking if a fd is connectable ofr a read
                FD_SET(clientStates[i].fd, &read_fds);
                if (clientStates[i].fd >= nfds)
                    nfds = clientStates[i].fd + 1;
            }
        }

        // Wait for an activity on one of the sockets
        if (select(nfds, &read_fds, &write_fds, NULL, NULL) == -1) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        // Check for new connections
        if (FD_ISSET(listen_fd, &read_fds)) {
            if ((conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len)) == -1) {
                perror("accept");
                continue;
            }

            printf("New connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            // Find a free slot for the new connection
            freeSlot = find_free_slot();
            if (freeSlot == -1) {
                printf("Server full: closing new connection\n");
                close(conn_fd);
            } else {
                clientStates[freeSlot].fd = conn_fd;
                clientStates[freeSlot].state = STATE_CONNECTED;
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {
            // Find an active FD (that has not been reset) in the FD_ISSET
            if (clientStates[i].fd != -1 && FD_ISSET(clientStates[i].fd, &read_fds)) {
                ssize_t bytes_read = read(clientStates[i].fd, &clientStates[i].buffer, sizeof(clientStates[i].buffer));
                // here we have to close the fd
                // this basically checks if FD should be closed, meaning read has been close() or it encountered some
                // error
                if (bytes_read <= 0) {
                    close(clientStates[i].fd); // Closes the connection at the TCP level, but we have to clear out
                                               // the memory as well in lines below
                    clientStates[i].fd = -1;
                    clientStates[i].state = STATE_DISCONNCECTED;
                    printf("Client disconnected or error\n");
                } else {
                    printf("Received data from client: %s\n", clientStates[i].buffer);
                }
            }
        }
    }

    return 0;
}
