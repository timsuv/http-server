#include <stdio.h>
#include <unistd.h>

#include "server.h"
#include "http.h"
#include "router.h"

#define PORT 8080
#define BUFFER_SIZE 4096

int main(void) {

    int server_fd = server_start(PORT);
    while (1) {
        int client_fd = server_accept_client(server_fd);
        if (client_fd < 0) {
            continue;
        }
        char buffer[BUFFER_SIZE] = { 0 };
        ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read > 0) {
            printf("--- Request ---\n%s\n---------------\n", buffer);

            http_request_t req;
            http_parse_request(buffer, &req);
            router_handle(client_fd, &req);
        }
        close(client_fd);        
    }
    close(server_fd);
    return 0;
}   