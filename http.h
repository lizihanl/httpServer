//
// Created by mac on 2023/3/12.
//

#ifndef HTTPSERVER_HTTP_H
#define HTTPSERVER_HTTP_H




#define CONNECTTIMEOUT 3
#define MAX_SIZE_HEARER 2048


//Type definition



typedef enum {
    GET,
    POST
}RequestMethod_e;




typedef struct
{
    char host[16];
    char url[128]; //Contains parameters passed in from the url
    int  port;
    int  method;
    int  timeouts;
    int  timeoutus;
    char *content; //apply for space to store data
}HttpParam_t;

struct PostData
{
    char key[10];
    char value[20];
};

//Function declaration


int http(HttpParam_t httpparam);
void getMethod(int accept_fd,char buff[1024]);
void postMethod(int accept_fd,char buff[1024]);
void headMethod(int accept_fd,char buff[1024]);

int httpPostData(char *postBuff);











#endif //HTTPSERVER_HTTP_H
