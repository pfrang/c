#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define MAX_CONNECTIONS 5

int main()
{
  int server_socket, client_socket;
  struct sockaddr_in server_address, client_address;

  // Create the server socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  char s = "hei";

  // Configure the server address
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(PORT);

  // Bind the socket to the address
  bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

  // Listen for incoming connections
  listen(server_socket, MAX_CONNECTIONS);

  // Accept incoming connections
  while (1)
  {
    int client_address_size = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t *)&client_address_size);

    // Handle incoming requests on the same connection
    while (1)
    {
      // Read the incoming request
      char buffer[1024] = {0};
      int bytes_received = recv(client_socket, buffer, 1024, 0);

      // Check if the connection was closed by the client
      if (bytes_received == 0)
      {
        printf("Client disconnected.\n");
        break;
      }

      printf("Received: %s\n", buffer);

      // Send a response
      char *response = "HTTP/1.1 200 OK\nContent-Length: 12\nConnection: keep-alive\nContent-Type: text/plain\n\nHello World!";
      send(client_socket, response, strlen(response), 0);
    }
    close(client_socket);
  }

  // Close the server socket
  close(server_socket);

  return 0;
}
