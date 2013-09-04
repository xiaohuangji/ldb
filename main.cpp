//
//  testMydb.cpp
//  MylevelDB
//
//  Created by wills on 13-7-20.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#include "lnet.h"
#include "levent.h"
#include "lconfig.h"
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include<sys/stat.h>

using namespace std;

static void exit_0(void){
    printf("ldb-server exit:%d ...\n",getpid());
}

static int set_daemon(){
    pid_t pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);
    
    setsid();
    
    signal(SIGINT, SIG_IGN);
    signal(SIGHUP,SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
    
    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);

    umask(0);
    
    int fd = open("/dev/null", O_RDWR);
    if (fd < 0) {
        return -1;
    }
    
    int status = dup2(fd, STDIN_FILENO);
    
    if (status < 0) {
        close(fd);
        return -1;
    }
    
    status = dup2(fd, STDOUT_FILENO);
    if (status < 0) {
        close(fd);
        return -1;
    }
    
//    status = dup2(fd, STDERR_FILENO);
//    if (status < 0) {
//        close(fd);
//        return -1;
//    }
    
    if (fd > STDERR_FILENO) {
        status = close(fd);
        if (status < 0) {
            return -1;
        }
    }
    return 0;
}

static int create_pid_file(Server* s){

    FILE* fd = fopen(s->pid_file.c_str(),"w");
    
    if (fd < 0) {
        perror("opening pid file fail\n");
        return -1;
    }

    char pidbuf[10];
    int pidlen=sprintf(pidbuf, "%d", getpid());
    
    int n = fwrite(pidbuf, pidlen, 1, fd);
    if (n < 0) {
        perror("write to pid file failed\n");
        return -1;
    }
    
    fclose(fd);
    
    return 0;
}

int main(int argc,char * argv[])
{
    
    char buffer[100];
    getcwd(buffer, 100);
    //init
    Lconfig config=Lconfig(string(buffer)+"/lbase.conf");
    Server* server=config.initServerConfig();
    
    //daemon
    if (server->daemon == true) {
        if(set_daemon()!=0){
            perror("ldb-server daemon error,exit\n");
            exit(0);
        }
    }
    
    //pre-run
    if(atexit(exit_0)!=0){
        perror("ldb-server atexit error\n");
        exit(0);
    }
    
    if(create_pid_file(server)!=0){
        perror("create pid file error\n");
        exit(0);
    }
    
    Llog::init(server);
    Ldb::init(server);
    
    //listen
    int listenfd=TcpServer::tcpListen(server->host.c_str(), server->port);
    if(listenfd==-1){
        perror("tcplisten error\n");
        exit(0);
    }
    
    //run loop
    Levent *le=new Levent(listenfd,server->max_client);
    le->run();
    

}