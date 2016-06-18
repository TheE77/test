#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "request_handlers.h"

void* connection_handler(void*);
 
int main()
{
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
     
    //Bind
    if(bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    
    //Listen
    listen(socket_desc , 3);
    
    c = sizeof(struct sockaddr_in);
	pthread_t thread_id;
	
    while((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)))
    {
        if( pthread_create(&thread_id , NULL ,  connection_handler , (void*) &client_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
    }
     
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
     
    return 0;
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char client_message[1000];
     
    //Receive a message from client
    puts("rrrrrrrrrr");
    while((read_size = recv(sock , client_message , 1000 , 0)) > 0)
    {
        puts("rrrrrrrrrr");
        //end of string marker
		client_message[read_size] = '\0';
		
		deserialize(client_message, &message);
        puts("bbbbbbbbbbbbbbb");
		handle_request(&message, sock);
        puts("bbbbbbbbbbbbbbb");
		
		//clear the message buffer
		memset(client_message, 0, 2000);
    }
     
    puts("rrrrrrrrrr");
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    
    else if(read_size == -1)
    {
        perror("recv failed");
    }
         
    return 0;
} 
