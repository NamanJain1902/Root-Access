#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<cstring>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<error.h>

/*
 * Commonly used socket header files are:
    
     /usr/include/netinet/in.h : Defines Internet constants and structures.
     /usr/include/netdb.h      : Contains data definitions for socket subroutines.
     /usr/include/sys/socket.h : Contains data definitions and socket structures.
     /usr/include/sys/types.h  : Contains data type definitions.
     /usr/include/arpa.h       : Contains definitions for internet operations.
     /usr/include/sys/errno.h  : Defines the errno values that are returned by drivers and
                                  other kernel-level code.
*/
int main(int argc, char **argv[]){


    // socket creation
    int sockid = socket(AF_INET, SOCK_STREAM, 0);
    if(sockid == -1){
        printf("Descriptor returned -1.");
        return EXIT_FAILURE;
    }
    /**
     * int sockid = socket(family, type, protocol);
     * sockid: socket descriptor, an integer (like a file-handle).
     * family: : integer, communication domain, e.g
     *       PF_INET, IPv4 protocols, Internet addresses (typically used)
     *       PF_UNIX, Local communication, File addresses
     * type: communication type
     *       SOCK_STREAM - reliable, 2-way, connection-based service
     *       SOCK_DGRAM - unreliable, connectionless, messages of maximum length
     * protocol: spcifies protocol
     *       IPPROTO_TCP IPPROTO_UDP
     *       usually set to 0 (i.e., use default protocol)
     * upon failure returns -1
    */

    // socket close, When finished using a socket, the socket should be closed.
    int status = close(sockid);
    if(status == 0){
        return EXIT_SUCCESS;
    }else{
        return EXIT_FAILURE; // error
    }
    /**
     * Closing a socket
         closes a connection (for stream socket)
         frees up the port used by the socket
    */
}
