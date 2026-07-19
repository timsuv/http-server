#ifndef SERVER_H
#define SERVER_H

//creates, binds and starts listening on a socket
int server_start(int port);

int server_accept_client(int server_fd);

#endif