#include <stdlib.h>

#include "serializer.h"
#include "tpl.h"
#include "assert.h"

void serialize_create(const msg_create* message, char* buff)
{
    puts("serialize_create start");
    *buff = (char)CREATE;
    tpl_node *tn = tpl_map("S(s)", message);
    tpl_pack(tn, 0);
    tpl_dump(tn, TPL_MEM|TPL_PREALLOCD, buff + 1, 999);
    tpl_free(tn);
    puts(buff);
}
void serialize_delete(const msg_delete* message, char* buff)
{
    *buff = (char)DELETE;
    tpl_node *tn = tpl_map("S(s)", message);
    tpl_pack(tn, 0);
    tpl_dump(tn, TPL_MEM|TPL_PREALLOCD, buff, 1000);
    tpl_free(tn);
}
void serialize_find(const msg_find* message, char* buff)
{
    *buff = (char)FIND;
    tpl_node *tn = tpl_map("S(s)", message);
    tpl_pack(tn, 0);
    tpl_dump(tn, TPL_MEM|TPL_PREALLOCD, buff, 1000);
    tpl_free(tn);
}

void serialize(const msg* message, char* buff)
{
    puts("Called serialize");
	switch(message->_header._type)
	{
	case CREATE:
		serialize_create((msg_create*)&message->_body, buff);
        break;
	case DELETE:
		serialize_delete((msg_delete*)&message->_body, buff);
        break;
	case FIND:
		serialize_find((msg_find*)&message->_body, buff);
        break;
	default:
		assert(0);
        break;
	}
}

void deserialize_create(const char* message, msg* buff)
{
    puts("before deserialize");
    buff->_header._type = CREATE;
    puts("before deserialize");
    tpl_node *tn = tpl_map("S(s)", buff);
    puts("before deserialize");
    tpl_load(tn, TPL_MEM|TPL_EXCESS_OK, message, 1000);
    puts("before deserialize");
    tpl_unpack(tn, 0);
    puts("before deserialize");
    tpl_free(tn);
    puts("after deserialize");
}

void deserialize_delete(const char* message, msg* buff)
{
//    *buff = (char)CREATE;
//    tpl_node *tn = tpl_map("S(msg_create)", message);
//    tpl_pack(tn, 0);
//    tpl_dump(tn, TPL_MEM, buff, sizeof(buff));
//    tpl_free(tn);
}

void deserialize_find(const char* message, msg* buff)
{
//    *buff = (char)CREATE;
//    tpl_node *tn = tpl_map("S(msg_create)", message);
//    tpl_pack(tn, 0);
//    tpl_dump(tn, TPL_MEM, buff, sizeof(buff));
//    tpl_free(tn);
}

void deserialize(const char* message, msg* buff)
{
    puts("dddddddddd");
	assert(message != NULL);

	msg_type t = (msg_type)(*message);
	switch(t) {
	case CREATE:
		deserialize_create(message + 1, buff);
        break;
	case DELETE:
		deserialize_delete(message + 1, buff);
        break;
	case FIND:
		deserialize_find(message + 1, buff);
        break;
	default:
		assert(0);
        break;
	}

	buff->_header._type = t;
    puts("gggggg");
}
