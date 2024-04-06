select

-- Run program with strace./select.c 
-- or just run program with ./select.c to setup a server that will write the output

What we have now is set up a synchronous multiplexing I/O server using the select system call.
This is in contrast to an asynchronous server, which would use non-blocking I/O and callbacks or events to handle multiple connections.


-- when program is running. connect to it with nc localhost 8080, and a connection is setup
-- you can see on the server from which PID etc connection is coming from, and you can write data to it by simlpy pressingf something in the terminal and hit enter
-- even from POSTMAN hitting localhost:8080 send in raw body text you can see its ocntent on the server
