#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "protocol.h"

void serialize(const msg* message, char* buff);

void deserialize(const char* message, msg* buff);

#endif
