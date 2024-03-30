
In the realm of networking code, everything in UNIX is treated as a file, and sockets are no exception. A socket serves as a file used by the kernel to establish communication between two computers, forming the cornerstone of all networking code we'll explore in this course.

MIN FORKLARING
Socket is establish stuff like IPv4 and TCP vs UDP (wait for server to accept connection or just push). Returns a fd
Server is establishing and waiting for a connection on a specific port (bound the socket to a port). 
Listen for a connection with accept. When accept returns it return a new fd represents a new socket, a connection to that client.

---INTERNET and communication between client and a server---
Connection between a client and a server. Both need to establish a file descriptor. 
The sockets are then connected which alllows for read/write between files.


SERVER
 - Socket
 - Bind to a port
 - Listen
 - Accept
Set up a port
The server has to be setup such that it listens for requests

Client
 - Socket
 - Client
