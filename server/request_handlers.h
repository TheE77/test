#ifndef REQUEST_HANDLERS_H
#define REQUEST_HANDLERS_H

#include "protocol.h"

void handle_create(const msg_create* message, int sock);
void handle_delete(const msg_delete* message, int sock);
void handle_find(const msg_find* message, int sock);
void handle_request(const msg* message, int sock);

#endif
