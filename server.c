#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int socketConnectionInQueue, socketConnection, portNumber;
    socklen_t socketLength;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    
    if(argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    
    socketConnectionInQueue = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socketConnectionInQueue < 0)
    {
        error("ERROR opening socket");
    }
    
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portNumber = atoi(argv[1]);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNumber);
    
    if(bind(socketConnectionInQueue, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }
    
    listen(socketConnectionInQueue, 5);
    
    socketLength = sizeof(cli_addr);
    socketConnection = accept(socketConnectionInQueue, (struct sockaddr *)&cli_addr, &socketLength);
    
    if(socketConnection < 0)
    {
        error("ERROR on accept");
    }
    
    bzero(buffer, 256);
    n = read(socketConnection, buffer, 255);
    if(n < 0) error("ERROR reading from socket");
    printf("Message: %s\n", buffer);
    n = write(socketConnection, "Message received.", 17);
    if(n < 0) error("ERROR writing to socket");
    close(socketConnection);
    close(socketConnectionInQueue);
    return 0;
}