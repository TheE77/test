#include "request_handlers.h"

void handle_create(const msg_create* message, int sock)
{
	printf("Create file: %s", message->_name);
	write(sock , '1', 1);
}

void handle_delete(const msg_delete* message, int sock)
{
	printf("Delete file: %s", message->_name);
	write(sock , '1', 1);
}

void handle_find(const msg_find* message, int sock)
{
	printf("Find file: %s", message->_name);
	write(sock , '1', 1);
}

void handle_request(const msg* message, int sock)
{
    puts("aaaaaaaaaaaa");
	switch(message->_header._type)
	{
	case CREATE:
		handle_create((msg_create*)&message->_body, sock);
		break;
	case DELETE:
		handle_delete((msg_delete*)&message->_body, sock);
		break;
	case FIND:
		handle_find((msg_find*)&message->_body, sock);
		break;
	default:
        assert(0);
		break;
	}
}

