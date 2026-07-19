#ifndef HTTP_H
#define HTTP_H

#define MAX_METHOD_LEN 8
#define MAX_PATH_LEN   256

typedef struct {
    char method[MAX_METHOD_LEN];
    char path[MAX_PATH_LEN];
} http_request_t;

void http_parse_request(const char* raw_buffer, http_request_t* req);

int http_build_response(char* out_buffer, int out_buffer_size, int status_code, const char* content_type, const char* body);

#endif


