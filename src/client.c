/*
The MIT License (MIT)

Copyright (c) 2015 Victor Norgren

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int socketConnection, portNumber, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if(argc < 3) {
        fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
        exit(0);
    }

    portNumber = atoi(argv[2]);

    socketConnection = socket(AF_INET, SOCK_STREAM, 0);

    if(socketConnection < 0) error("ERROR opening socket\n");

    server = gethostbyname(argv[1]);

    if(server == NULL) {
        fprintf(stderr, "ERROR no such host\n");
        exit(0);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portNumber);

    if(connect(socketConnection,(struct sockaddr *)&serv_addr, sizeof(serv_addr))< 0) error("ERROR connecting\n");

    printf("Message: ");

    bzero(buffer, 256);
    if(fgets(buffer, 255, stdin) == NULL) error("ERROR reading stdin stream\n");
    n = write(socketConnection, buffer, strlen(buffer));

    if(n < 0) error("ERROR writing to socket\n");

    bzero(buffer, 256);
    n = read(socketConnection, buffer, 255);

    if(n < 0) error("ERROR reading from socket\n");

    printf("%s\n", buffer);

    close(socketConnection);
    return 0;
}
