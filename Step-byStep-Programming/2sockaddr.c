#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<error.h>

int main(int argc, char **argv[]){


    // socket creation
    int sockid = socket(AF_INET, SOCK_STREAM, 0);
    if(sockid == -1){
        printf("Descriptor returned -1.");
        return EXIT_FAILURE;
    }
    
    // Specifying Address
    // Socket API defines a generic data type for addresses.
    struct sockaddr {
        unsigned short sa_family; /* Address family (e.g. AF_INET) */
        char data[14]; /* Family-specific address information */
    };

    // Particular form of the sockaddr used for TCP/IP addresses:
    struct in_addr{
        unsigned long s_addr; /* Internet address (32 bits) */
    };
    
    struct sockaddr_in {
        unsigned short sin_family; /* Internet protocol (AF_INET) */
        unsigned short sin_port; /* Address port (16 bits) */
        struct in_addr sin_addr; /* Internet address (32 bits) */
        char sin_zero[8]; // Not used
    };

    /*
     * 
     *  Important: sockaddr_in can be casted to a sockaddr
     * 
     */


    // socket close, When finished using a socket, the socket should be closed.
    int status = close(sockid);
    if(status == 0){
        return EXIT_SUCCESS;
    }else{
        return EXIT_FAILURE; // error
    }
}
