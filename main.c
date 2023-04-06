#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include "http.h"
#include "tcp.h"
#include <db.h>


void postMethod(int accept_fd,char buff[1024])
{

    char http_head[]="HTTP/1.1 200 OK\r\n"      \
                "Content-Type: Text/Html\r\n"   \
                "\r\n";
    char http_err[]="HTTP/1.1 404 Not Found\r\n"  \
                "Content-Type: Text/Html\r\n"     \
                "\r\n"                            \
                "<HTML><BODY>File Not Found</BODY><HTML>";
    ssize_t ret1;

    //Obtain the file name of the static web page to be accessed by the browser through the obtained data packet
    char http_fileName[128]="";
    sscanf(buff,"POST / %s",http_fileName);//sscanf end if meet space, directly get the file name
    if(strncmp(http_fileName,"HTTP/1.1", strlen("HTTP/1.1"))==0) {
        strcpy(http_fileName, "index.html");
    }
    printf("filename = %s\n",http_fileName);
    char path[128]="./html/";
    strcat(path, http_fileName);
    printf("file:%s\n",path);
    //Check whether the path and file name are valid
    int http_fd;
    if((http_fd= open(path,O_RDONLY))<0) {
        if(errno==ENOENT){
            ret1= send(accept_fd, http_err,strlen(http_err), 0);
            if(ret1<0){
                ERRLOG("Fail to send!");
            }
            close(accept_fd);
        }
        else{
            ERRLOG("Fail to open!");
        }
    }
    ret1= send(accept_fd, http_head,strlen(http_head), 0);
    if(ret1<0){
        ERRLOG("Fail to send!");
    }
    // Store the post data in the database
        DB_ENV *dbenv;
        DB *dbp;
        int ret;
        /* Create a database environment */
        if ((ret = db_env_create(&dbenv, 0)) != 0) {
            fprintf(stderr, "Failed to create DB environment: %s\n", db_strerror(ret));
            exit(1);
        }
        /* Open the database environment */
        if ((ret = dbenv->open(dbenv, "/path/to/dbenv", DB_CREATE | DB_INIT_MPOOL, 0)) != 0) {
            fprintf(stderr, "Failed to open DB environment: %s\n", db_strerror(ret));
            exit(1);
        }
        /* Create a database */
        if ((ret = db_create(&dbp, dbenv, 0)) != 0) {
            fprintf(stderr, "Failed to create DB: %s\n", db_strerror(ret));
            exit(1);
        }
        /* Open the database */
        if ((ret = dbp->open(dbp, NULL, "/path/to/db", NULL, DB_BTREE, DB_CREATE, 0664)) != 0) {
            fprintf(stderr, "Failed to open DB: %s\n", db_strerror(ret));
            exit(1);
        }
    
//    The post data is read and stored in the database
    httpPostData(buff, dbp);
    //Read the web file and send it
    size_t len_http_body;
    char http_body[1024]="";
    while ((len_http_body= read(http_fd,http_body,1024))>0){
        ret1= send(accept_fd,http_body ,len_http_body, 0);
        if(ret1<0){
            ERRLOG("Fail to send!");
        }
    }
}

void getMethod(int accept_fd,char buff[1024])
{
    char http_head[]="HTTP/1.1 200 OK\r\n"      \
                "Content-Type: Text/Html\r\n"   \
                "\r\n";
    char http_err[]="HTTP/1.1 404 Not Found\r\n"  \
                "Content-Type: Text/Html\r\n"     \
                "\r\n"                            \
                "<HTML><BODY>File Not Found</BODY><HTML>";
    ssize_t ret1;

    //Obtain the file name of the static web page to be accessed by the browser through the obtained data packet
    char http_fileName[128]="";
    sscanf(buff,"GET / %s",http_fileName);
    if(strncmp(http_fileName,"HTTP/1.1", strlen("HTTP/1.1"))==0) {
        strcpy(http_fileName, "index.html");
    }
    printf("filename = %s\n",http_fileName);
    char path[128]="./html/";
    strcat(path, http_fileName);
    printf("file:%s\n",path);
    //Check whether the path and file name are valid
    int http_fd;
    if((http_fd= open(path,O_RDONLY))<0) {
        if(errno==ENOENT){
            ret1= send(accept_fd, http_err,strlen(http_err), 0);
            if(ret1<0){
                ERRLOG("Fail to send!");
            }
            close(accept_fd);
        }
        else{
            ERRLOG("Fail to open!");
        }
    }
    ret1= send(accept_fd, http_head,strlen(http_head), 0);
    if(ret1<0){
        ERRLOG("Fail to send!");
    }
    //Read the web file and send it
    size_t len_http_body;
    char http_body[1024]="";
    while ((len_http_body= read(http_fd,http_body,1024))>0){
        ret1= send(accept_fd,http_body ,len_http_body, 0);
        if(ret1<0){
            ERRLOG("Fail to send!");
        }
    }
}

void headMethod(int accept_fd,char buff[1024])
{
    char http_head[]="HTTP/1.1 200 OK\r\n"      \
                "Content-Type: Text/Html\r\n"   \
                "\r\n";
    char http_err[]="HTTP/1.1 404 Not Found\r\n"  \
                "Content-Type: Text/Html\r\n"     \
                "\r\n"                            \
                "<HTML><BODY>File Not Found</BODY><HTML>";
    ssize_t ret1;

    //Obtain the file name of the static web page to be accessed by the browser through the obtained data packet
    char http_fileName[128]="";
    sscanf(buff,"HEAD / %s",http_fileName);
    if(strncmp(http_fileName,"HTTP/1.1", strlen("HTTP/1.1"))==0) {
        strcpy(http_fileName, "index.html");
    }
    printf("filename = %s\n",http_fileName);
    char path[128]="./html/";
    strcat(path, http_fileName);
    printf("file:%s\n",path);
    //Check whether the path and file name are valid
    int http_fd;
    if((http_fd= open(path,O_RDONLY))<0) {
        if(errno==ENOENT){
            ret1= send(accept_fd, http_err,strlen(http_err), 0);
            if(ret1<0){
                ERRLOG("Fail to send!");
            }
            close(accept_fd);
        }
        else{
            ERRLOG("Fail to open!");
        }
    }
    ret1= send(accept_fd, http_head,strlen(http_head), 0);
    if(ret1<0){
        ERRLOG("Fail to send!");
    }
    /*
    //Read the web file and send it
    size_t len_http_body;
    char http_body[1024]="";
    while ((len_http_body= read(http_fd,http_body,1024))>0){
        ret1= send(accept_fd,http_body ,len_http_body, 0);
        if(ret1<0){
            ERRLOG("Fail to send!");
        }
    }
     */
}



int http(HttpParam_t httpparam)
{

    DBM *db;
    datum key, value;

     db = dbm_open("test.db", O_RDWR | O_CREAT, 0666);

     if (!db) {
        fprintf(stderr, "Cannot open database\n");
        return 1;
    }
    //Check the number of command line parameters
    /*
    if (3 != argc)
    {
        printf("Usage : %s <IP> <PORT>\n", argv[0]);
        exit(-1);
    }
    */


    //Create socket - Populate server network information structure - Bind - Listen
    int sockfd = socket_bind_listen(httpparam.host,httpparam.port);

    //Size of socket to listen in the fds array
    int max_fd;
    struct pollfd fds[MAXFDS];      //fds stores the socket to be listened
    //Initialize fds
    for(int i=0;i<MAXFDS;i++)
        fds[i].fd=-1;               //-1 will not be listened
    //Put the listened socket into the array
    fds[sockfd].fd=sockfd;
    fds[sockfd].events=POLLIN;//Data readable event (new client connection, client sending data, client disconnection)
    max_fd = sockfd;//Record the maximum file descriptor

    printf("listen_fd:%d\n",sockfd);

    int ret=0;
    ssize_t ret1;
    int accept_fd;
    char buff[1024] = {0};
    int i;

    while (1)
    {
//        int sttime;
//        sttime=20000;
        ret= poll(fds, max_fd+1,-1);  //
        if (ret == -1)
            ERRLOG("Poll error");
        //If the system times out, a timeout message is displayed. Now NULL regardless of timeout
        if(ret==0){
            printf("Poll timeout!\n");
            continue;
        }




        for (i = 0; i < max_fd + 1; i++)
        {
            if(fds[i].fd<0) continue;
            if((fds[i].revents&POLLIN)==0) continue;
            fds[i].revents=0;
//            printf("fd:%d\n",fds[i].fd);
            if (i == sockfd)
            {
                //If the event is the listen socket, a new client is connected
                struct sockaddr_in client;
                socklen_t len= sizeof(client);
                accept_fd = accept(sockfd, (struct sockaddr*)&client,&len);//NULL, NULL);
                if (-1 == accept_fd)
                    ERRLOG("accept error");

                printf("client [%d] connect\n", accept_fd);
                if(accept_fd>MAXFDS) {
                    printf("ClientSocket(%d)>MAXFDS(%d)\n", accept_fd, MAXFDS);
                    close(accept_fd);
                    continue;
                }
                //Add accept_fd to the collection to be monitored as well
                fds[accept_fd].fd=accept_fd;
                fds[accept_fd].events=POLLIN;
                fds[accept_fd].revents=0;
                //Record the maximum file descriptor
                max_fd = (max_fd > accept_fd ? max_fd : accept_fd);
            }
            else
            {//Note A client sends a message (sends data or disconnects).
                accept_fd = i;
                bzero(buff, 1024);
                //Receive data from the client
                if (0 > (ret1 = recv(accept_fd, buff,sizeof(buff), 0)))
                {
                    perror("recv error");
                    break;
                }
                else if (0 == ret1)//CTRL+C on the client
                {
                    printf("client [%d] cut the connection\n",accept_fd);
                    //Delete the client from the collection
                    fds[i].fd=-1;
                    if(i==max_fd){
                        for(int ii=max_fd;ii>0;ii--){
                            if(fds[ii].fd!=-1){
                                max_fd=ii;
                                break;
                            }
                        }
                    }
                    //Close the socket for the client
                    close(i);
                    continue;//End the loop
                }
                else
                {

                    printf("client [%d] send message:\n%s\n", i, buff);
                    char reqMethod[5]="";
                    sscanf(buff,"%s",reqMethod);
                    printf("req:%s\n",reqMethod);
                    if(strcmp(reqMethod,"GET")==0)
                    {
                        getMethod(accept_fd,buff);
                    }
                    else if(strcmp(reqMethod,"POST")==0){
                        postMethod(accept_fd,buff, db);
                    }
                    else if(strcmp(reqMethod,"HEAD")==0){
                        headMethod(accept_fd,buff);
                    }
                    else{
                        char noMethod[]="<HTML><BODY>400 Bad Request</BODY><HTML>";
                        int errMth=send(accept_fd,noMethod,strlen(noMethod), 0);
                    }
                    //response
//                    ret1= send(accept_fd, buff,sizeof(buff), 0);
//                    if (0 > ret1)
//                    {
//                        perror("send error");
//                        break;
//                    }
                }
            }
            ret--;
        }
//        fds[sockfd].fd=sockfd;
//        fds[sockfd].events=POLLIN;
//        max_fd = sockfd;

    }
    //close socket
    close(sockfd);
    return 0;
}






int httpPostData(char postBuff[1024], DB *db)
{
    if(postBuff == NULL){
        return -1;
    }

    struct PostData pData[2];
    char *prtData;
    prtData = strstr(postBuff , "\r\n\r\n");
    prtData += 4;
    int i=0,j=0;
    int flag=0; //is 0:key; 1:value
    while (*prtData!='\0'){
        if(*prtData=='&'){
            pData[i].value[j]='\0';
            flag=0;
            j=0;
            i++;
            prtData++;
            continue;
        }
        else if(*prtData=='='){
            pData[i].key[j]='\0';
            j=0;
            prtData++;
            flag=1;
            continue;
        }
        else{
            if(flag==0){
                pData[i].key[j]=*prtData;
                prtData++;
            }
            else{
                pData[i].value[j]=*prtData;
                prtData++;
            }
            j++;
        }
    }

    // Insert the key-value pairs into the database
    DBT key, value;
    memset(&key, 0, sizeof(key));
    memset(&value, 0, sizeof(value));
    for (int k = 0; k < 2; k++) {
        key.data = pData[k].key;
        key.size = strlen(pData[k].key) + 1;
        value.data = pData[k].value;
        value.size = strlen(pData[k].value) + 1;
        int ret = db->put(db, NULL, &key, &value, 0);
        if (ret != 0) {
            fprintf(stderr, "Failed to insert key-value pair into database: %s\n", db_strerror(ret));
            return -1;
        }
    }

    printf("%s: %s\n%s: %s\n", pData[0].key, pData[0].value, pData[1].key, pData[1].value);

    return 0;
}


int main()
{
    DBM *db;
    datum key, value;

     db = dbm_open("test.db", O_RDWR | O_CREAT, 0666);

     if (!db) {
        fprintf(stderr, "Cannot open database\n");
        return 1;
    }
    HttpParam_t httpparam;
    memset(httpparam.host, 0, sizeof(httpparam.host));
    memset(httpparam.url, 0, sizeof(httpparam.url));
    strcpy(httpparam.host, "127.0.0.1");
    strcpy(httpparam.url, "./html");
    httpparam.port = 8000;
    httpparam.method = POST;
    httpparam.timeouts = 1;
    httpparam.timeoutus = 0;





    int re = http(httpparam);

    dbm_close(db);

//    free(httpparam.content);
    //printf("%s\n",content);


}

