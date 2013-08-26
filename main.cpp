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

using namespace std;

int main(int argc,char * argv[])
{
    
    char buffer[100];
    getcwd(buffer, 100);
    //init
    Lconfig config=Lconfig(string(buffer)+"/lbase.conf");
    Server* server=config.initServerConfig();
    
    if (server->daemon == true) {
        pid_t pid = fork();
        if (pid < 0)
            exit(EXIT_FAILURE);
        if (pid > 0)
            exit(EXIT_SUCCESS);
    }
    
    Llog::init(server);
    Ldb::init(server);
    
    //listen
    int listenfd=TcpServer::tcpListen(server->host.c_str(), server->port);
    
    //run loop
    Levent *le=new Levent(listenfd,server->max_client);
    le->run();
    

}