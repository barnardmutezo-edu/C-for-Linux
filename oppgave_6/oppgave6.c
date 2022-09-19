#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void)
{

    /*Used nslookup to get the IP4 address for www.eastwillsecurity.com. 
      Alternativly could have used hostent struct, but no need to exaggerate..
    */

    const unsigned char * IP = "77.111.240.75"; // Hardcoded IPV4 address.
    const unsigned char * HTTP = "GET pg3401/test.html HTTP/1.1\r\nHost: www.eastwillsecurity.com\r\n\r\n"; // The http request, with file path
    const unsigned char PORT = 80; // Hardcoded port nr.

    unsigned char n;


    char buffer[1024]; // Buffer to store the request and reply

    struct sockaddr_in addr = {0};

    unsigned char sock;

    // Simple TCP socket
    sock = socket(AF_INET,SOCK_STREAM,0);

    if (sock<0)
    {
        printf("socket error\n");
        exit(1);
    }
    

    addr.sin_family = AF_INET; // Setting up TCP, PORT and IPV4
    addr.sin_port = htons(PORT);

    //Here i used the inet_addr function to convert the ip string to an int and set the value to the adress field
    addr.sin_addr.s_addr = inet_addr(IP);
    

    if (connect(sock,(struct sockaddr*)&addr,sizeof(addr))<0)
    {
          printf("ERROR connecting\n");
          exit(1);
    }
      
    printf("CLIENT: CONNECTED TO SERVER\n\n");

    bzero(buffer,1024);


    strcpy(buffer,HTTP); //Here we pass the GET request to the server with the wanted path.

    n = write(sock,buffer,strlen(buffer)); // Sendig the GET request

    if (n<0)
    {
        printf("Could not write to socket\n");
        exit(1);  
    }

    bzero(buffer,1024); // Reset the buffer to 0 before reading the reply.
    n = read(sock,buffer,(1024-1)); // Receiving  the reply.

    if (n<0){
        printf("Could not read from socket\n");
        exit(1);
    }

    printf("SERVER: %s",buffer); // Displaying the reply.

    // Clean up.
    close(sock);
    sock = -1;
    return 0;
}
