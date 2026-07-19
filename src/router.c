#include <string.h>
#include <unistd.h> 

#include "router.h"
#include "http.h"

#define RESPONSE_BUFFER_SIZE 2048

static void send_response(int client_fd, int status_code, const char* body) {
    char response[RESPONSE_BUFFER_SIZE];
    int len = http_build_response(response, sizeof(response), status_code, "text/html", body);
    write(client_fd, response, len);
}

void router_handle(int client_fd, const http_request_t* req) {
    if (strcmp(req->path, "/") == 0) {
        send_response(client_fd, 200, "<html><body><h1>Home</h1><p>Welcome to the C server.</p></body></html>");
    }
    else if (strcmp(req->path, "/about") == 0) {
        send_response(client_fd, 200,
            "<html><body><h1>About</h1><p>Built from scratch with raw sockets.</p></body></html>");

    }
    else {
        send_response(client_fd, 404, "<html><body><h1>404 Not Found</h1></body></html>");
    }
}
    