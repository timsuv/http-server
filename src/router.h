#ifndef ROUTER_H
#define ROUTER_H

#include "http.h"

void router_handle(int client_fd, const http_request_t* req);

#endif