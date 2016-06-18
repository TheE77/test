#include "communicator.h"
 
int main(int argc , char *argv[])
{
    msg message;
    message._header._type = CREATE;
    msg_create message_create;
    message_create._name = "my_file.txt";
    message._body = (msg_body) message_create;
    request(message);
    return 0;
}
