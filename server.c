#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // close()
#include <arpa/inet.h>  // sockaddr_in, htons, INADDR_ANY
#include <sys/socket.h> // socket(), bind(), listen(), accept()

#define PORT 8080
#define BUFFER_SIZE 4096

int main(void) {

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //bind sockets to an adress and port
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // listen to all local intefaces
    address.sin_port = htons(PORT); // host to network byte order
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //start listening to the connections 
    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Listening on http://localhost:%d\n", PORT);

    while (1)
    {
        struct sockaddr_in client_adress;
        socklen_t client_len = sizeof(client_adress);

        int client_fd = accept(server_fd, (struct sockaddr*)&client_adress, &client_len);
        if (client_fd < 0) {
            perror("accpet_failed");
            continue;
        }

        char buffer[BUFFER_SIZE] = { 0 };
        ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read > 0) {
            printf("--- Request ---\n%s\n---------------\n", buffer);

            char method[8], path[256];
            sscanf(buffer, "%7s %255s", method, path);

            char body[512];

            snprintf(body, sizeof(body),
                "<html><body><h1>Hello from C!</h1>"
                "<p>You requested: %s %s</p></body></html>",
                method, path);

            char response[1024];

            int response_len = snprintf(response, sizeof(response),
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: %zu\r\n"
                "Connection: close\r\n"
                "\r\n"
                "%s",
                strlen(body), body);

            write(client_fd, response, response_len);
        }
        close(client_fd);
    }
    close(server_fd);
    return 0;

}