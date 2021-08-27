#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

int PORT = 9002;
char *ip = "127.0.0.1";

const int BUFFER__MAX = 2048;


void client__chatter(int socket_fd){
    
    char buffer[BUFFER__MAX];
    int n;
    // infinite loop for chat
    for(;;){
        bzero(buffer, BUFFER__MAX);
        // read the message from client and store it in buffer.
        printf("Client: ");
        n=0;
        // scanf("Client: %s", buffer);
        while ((buffer[n++] = getchar()) != '\n');
        write(socket_fd, buffer, sizeof(buffer));

        bzero(buffer, BUFFER__MAX);
        // storing server message in buffer
        read(socket_fd, buffer, sizeof(buffer));
        printf("Server: %s", buffer);
        // sending that buffer to client

        if((strncmp("bye", buffer, 4)) == 0){
            printf("Client Exiting...");
            break ;
        }
    }
}

int main(int argc, char *argv[]){

    // socket fd
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0){
        printf("Socket faliled!");
        return EXIT_FAILURE;
    }

    // storing cli arguments to respective variables.
    for(int i=1; i<argc; i++){
        printf("%s\n", argv[i]);
        if(argv[i] == "-p"){
            printf("Something...\n");
            i++;
            PORT = atoi(argv[i]);
            printf("%d\n", PORT);
        } 
        if(argv[i] == "-ip"){
            i++;
            strcpy(ip, argv[i]);
            printf("%s", ip);
        }
    }

    printf("%d\n", PORT);
    printf("%s\n", ip);

    // structure of socket
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(ip);

    socklen_t server_address__size__ = sizeof(server_address);
  
    // bind 
    int connect__status__ = connect(socket_fd, (struct sockaddr*) &server_address, server_address__size__);
    if(connect__status__ < 0){
        printf("connect() failed!\n");
        return EXIT_FAILURE;
    }else{
        printf("connect() successfull!\n");
    }


    client__chatter(socket_fd);

    int close__status__ = close(socket_fd);

    if(close__status__ == 0){
        return EXIT_SUCCESS;
    }else{
        return EXIT_FAILURE;
    }
}
