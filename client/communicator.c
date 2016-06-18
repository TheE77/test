#include "communicator.h"

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int request(msg message)
{
	int sock;
    struct sockaddr_in server;
    char buff[1000];
	char server_reply[2000];
     
    //Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        printf("Could not create socket");
    }
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 0;
    }
    
    //keep communicating with server
    while(1)
    {
		serialize(&message, buff);
         
        //Send some data
        puts("before send");
        if(send(sock , buff , 1000 , 0) < 0)
        {
            puts("Send failed");
            close(sock);
            return 0;
        }
        puts("after send");
         
        //Receive a reply from the server
        if(recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
    }
     
    close(sock);
	return (int)*server_reply;
}
