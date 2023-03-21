//
// Created by mac on 2023/3/12.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tcp.h"
//#include "http.h"


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


//Create socket - Populate server network information structure - Bind - Listen
int socket_bind_listen( char *host, int port)
{
    // 1.创建套接字      //IPV4   //TCP
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
        ERRLOG("socket error");


    // Populate server network information structure
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));//clear
    server_addr.sin_family = AF_INET;// IPV4

    // atoi change string to integer
    //htons set the unsigned 2-byte integer, host to network
    server_addr.sin_port = htons(port);

    //inet_addr string is converted to a 32-bit network byte order binary value
    server_addr.sin_addr.s_addr = inet_addr(host);

    //size of structure
    socklen_t server_addr_len = sizeof(server_addr);

    // Bind a socket to a network information structure
    if (-1 == bind(sockfd, (struct sockaddr *)&server_addr, server_addr_len))
        ERRLOG("bind error");


    //Set the socket to  listen
    if (-1 == listen(sockfd, 10))
        ERRLOG("listen error");

    return sockfd;
}

