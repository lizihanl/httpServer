//
// Created by mac on 2023/3/12.
//

#ifndef HTTPSERVER_TCP_H
#define HTTPSERVER_TCP_H

#include <db.h>
#define MAXFDS 1024
#define ERRLOG(errmsg)                                       \
    do                                                       \
    {                                                        \
        printf("%s--%s(%d):", __FILE__, __func__, __LINE__); \
        perror(errmsg);                                      \
        exit(-1);                                            \
    } while (0)


typedef enum
{
    TIMEOUT = -2,
    ERROR   = -1,
    NORMAL  = 0
}HttpState_e;



int socket_bind_listen( char *host, int port);

#endif //HTTPSERVER_TCP_H
