#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<cstring>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h> // Contains definitions for internet operations.e.g. inet_addr
#include<error.h>

int main(int argc, char **argv[]){


    // socket creation
    int sockid = socket(AF_INET, SOCK_STREAM, 0);
    if(sockid == -1){
        printf("Descriptor returned -1.");
        return EXIT_FAILURE;
    }

    char *ip = "127.0.0.1";
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002); // specifying port
    server_address.sin_addr.s_addr = inet_addr(ip); // alternative, INADDR_ANY or htonl(INADDR_ANY)


    int bind__status = bind(sockid, (struct sockaddr*) &server_address, sizeof(server_address));
    if(bind__status == -1){
        return EXIT_FAILURE;
    }
    /*
     * bind()
     * associates and reserves a port for use by the socket
    */ 

    /**
     * int bind__status = bind(sockid, &addrport, size);
     * 
     * sockid : integer, socket descriptor.
     * adddrport: struct sockaddr, the (IP) address and port of the machine.
     *       for TCP/IP server, internet address is usually set to INADDR_ANY, i.e.,
     *          chooses any incoming interface 
     * size: the size (in bytes) of the addrport structure
     * status: upon failure -1 is returned
    */
    

    




    // socket close, When finished using a socket, the socket should be closed.
    int status = close(sockid);
    if(status == 0){
        return EXIT_SUCCESS;
    }else{
        return EXIT_FAILURE; // error
    }
}
