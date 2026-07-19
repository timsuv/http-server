#include <stdio.h> 
#include <string.h>  
#include "http.h"


void http_parse_request(const char* raw_buffer, http_request_t* req) {
    sscanf(raw_buffer, "%7s %255s", req->method, req->path);
}

static const char* status_text(int status_code) {
    switch (status_code)
    {
    case 200: return "OK";
    case 404: return "Not Found";
    case 400: return "Bad Request";
    case 500: return "Internal Server Error";
    default: return "Unknown";
    }
}

int http_build_response(char* out_buffer, int out_buffer_size, int status_code, const char* content_type, const char* body) {
    int len = snprintf(out_buffer, out_buffer_size,
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status_code, status_text(status_code),
        content_type, strlen(body), body);

    return len;
}