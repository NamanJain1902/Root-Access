#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include<error.h>

int main(int argc, char *argv[]){

    // socket creation
    int master_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(master_fd == -1){
        return EXIT_FAILURE;
    }

    // server address setup
    char *ip = "127.0.0.1";
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = inet_addr(ip);

    // bind(): to bind a new socket to server
    int bind__status = bind(master_fd, (struct sockaddr*) &server_address, sizeof(server_address));
    if(bind__status == -1){
        printf("Bind not successfull\n");
    }

    // listen: 
    int listen__status = listen(master_fd, 5);
    if(listen__status == 0){
        printf("SUCCESS:: Listen Connection Setup.]n");
    }else{
        printf("ERROR:: Listen Connection Setup.]n");
    }
    /**
     * Instructs TCP protocol implementation to listen for connections
     * 
     * listen() is **non-blocking**: returns immediately
     * 
     * The listening socket (sockid)
         is never used for sending and receiving
         is used by the server only as a way to get new sockets
    */




    // close
    int close__status = close(master_fd);
    if(close__status == 0){
        return EXIT_SUCCESS;
    }else{
        printf("fd Not Closed\n");
        return EXIT_FAILURE;
    }


}