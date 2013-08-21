//
//  tcpserver.cpp
//  MylevelDB
//
//  Created by wills on 13-7-20.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//


#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include "lnet.h"

#define ANET_OK 0
#define ANET_ERR -1
#define ANET_ERR_LEN 256


int TcpServer::tcpListen(const char* ip,int port){
    int fd= -1;
    int on = 1;
    struct sockaddr_in sa;
    
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        //anetSetError(err, "creating socket: %s", strerror(errno));
        return ANET_ERR;
    }
    
    /* Make sure connection-intensive things like the redis benckmark
     * will be able to close/open sockets a zillion of times */
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        //anetSetError(err, "setsockopt SO_REUSEADDR: %s", strerror(errno));
        return ANET_ERR;
    }
    
    
    memset(&sa,0,sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (ip && inet_aton(ip, &sa.sin_addr) == 0) {
        close(fd);
        return ANET_ERR;
    }
    //s,(struct sockaddr*)&sa,sizeof(sa)
    if (bind(fd,(struct sockaddr*)&sa,sizeof(sa)) == -1) {
        close(fd);
        return ANET_ERR;
    }
    
    if (listen(fd, 511) == -1) {
        close(fd);
        return ANET_ERR;
    }
    
    return fd;

}

int TcpServer::tcpWrite(int fd,const char* buf,int count){
    int nwritten, totlen = 0;
    while(totlen != count) {
        nwritten = write(fd,buf,count-totlen);
        if (nwritten == 0) return totlen;
        if (nwritten == -1) return -1;
        totlen += nwritten;
        buf += nwritten;
    }
    return totlen;
}

int TcpServer::tcpRead(int fd,char* buf,int count){
    int nread, totlen = 0;
    while(totlen != count) {
        nread = read(fd,buf,count-totlen);
        if (nread == 0) return totlen;
        if (nread == -1) return -1;
        totlen += nread;
        buf += nread;
    }
    return totlen;
}

int TcpServer::tcpAccept(int fd){
    int clientfd = accept(fd, NULL, NULL);
    if(clientfd == -1) return ANET_ERR;
    return clientfd;
}

int TcpServer::tcpClose(int fd){
    if( close(fd)==-1)
        return ANET_ERR;
    return ANET_OK;
}
