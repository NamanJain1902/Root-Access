#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string>
#include<error.h>

int main(int argc, char *argv[]){

    // socket creation
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(client_fd == -1){
        return EXIT_FAILURE;
    }

    // server address setup
    char *ip = "127.0.0.1";
    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(9002);
    client_address.sin_addr.s_addr = inet_addr(ip);

    // bind(): to bind a new socket to server
    int bind__status = bind(client_fd, (struct sockaddr*) &client_address, sizeof(client_address));
    if(bind__status == -1){
        printf("Bind not successfull\n");
    }

    // listen: 
    int listen__status = listen(client_fd, 5);
    if(listen__status == 0){
        printf("SUCCESS:: Listen Connection Setup.]n");
    }else{
        printf("ERROR:: Listen Connection Setup.]n");
    }
    
    // connect
    int connect__status = connect(client_fd, (struct sockaddr*) &client_address, sizeof(client_address));
    /**
     * connect() is blocking
    */

    // close
    int close__status = close(client_fd);
    if(close__status == 0){
        return EXIT_SUCCESS;
    }else{
        printf("fd Not Closed\n");
        return EXIT_FAILURE;
    }

}