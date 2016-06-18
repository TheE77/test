#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "tpl.h"
typedef enum {
	CREATE,
	DELETE,
	FIND,
} msg_type;

typedef struct {
	char* _name;
} msg_create;

typedef struct {
	char* _name;
} msg_delete;

typedef struct {
	char* _name;
} msg_find;

typedef struct {
	msg_type _type;
} msg_header;

typedef union {
	msg_create _create;
	msg_delete _delete;
	msg_find _find;
} msg_body;

typedef struct {
	msg_header _header;
	msg_body _body;
} msg;

#endif
