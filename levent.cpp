//
//  levent.cpp
//  MylevelDB
//
//  Created by wills on 13-7-23.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include "levent.h"
#include "lnet.h"
#include <signal.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int Levent::_cclient=0;

Levent::Levent(int listenfd,int size){
    _kqfd=kqueue();
    _listenfd=listenfd;
    _size=size;
    _kevents=new struct kevent[_size];
    _logger=Llog::getInstance();
    _linkerManager=new LinkerMananer();
    
    int re=addNetEvent(_listenfd,NE_READABLE);
    if(re==LE_SUCC){
        _logger->info("addlistentokqueue succ");
    }else{
        _logger->error("add listen to kqueue error");
        exit(1);
    }
}

Levent::~Levent(){

}

int Levent::addNetEvent(int fd,int mask){
    
    //加入kqueue中管理
    struct kevent ke;
    
    if (mask & NE_READABLE) {
        EV_SET(&ke, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
        if (kevent(_kqfd, &ke, 1, NULL, 0, NULL) == -1) return LE_FAIL;
    }
    if (mask & NE_WRITABLE) {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
        if (kevent(_kqfd, &ke, 1, NULL, 0, NULL) == -1) return LE_FAIL;
    }
    _cclient++;
    return LE_SUCC;
}

int Levent::deleteNetEvent(int fd,int mask){
    //从kqueue中取消
    struct kevent ke;
    
    if (mask & NE_READABLE) {
        EV_SET(&ke, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        if (kevent(_kqfd, &ke, 1, NULL, 0, NULL)==-1)
            return LE_FAIL;
    }
    if (mask & NE_WRITABLE) {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
        if (kevent(_kqfd, &ke, 1, NULL, 0, NULL)==-1)
            return LE_FAIL;
    }
    _cclient--;
    return LE_SUCC;
}

void Levent::stop(){
    _stop=1;
}

void Levent::run(){
    _stop = 0;
    while (!_stop) {
        // 开始处理事件
        int ret = kevent(_kqfd, NULL, 0, _kevents, _size, NULL);
        if( ret== -1) return;
        handleNetEvent(ret);
    }
}
int Levent::acceptClient(){
    int client_id =TcpServer::tcpAccept(_listenfd);
    char buf[LOG_MSG_SIZE];
    sprintf(buf, "%s:%d","accetpclient:",client_id);
    _logger->info(buf);
    return addNetEvent(client_id,NE_READABLE);
}

int Levent::receiveClient(int fd,int cdata){
    if(cdata==0||!_linkerManager->handle(fd,cdata)){
        cout<<"closefd:"<<fd<<endl;
        _linkerManager->rmLinker(fd);
        deleteNetEvent(fd,NE_READABLE);
        return 0;
    }
    return cdata;
}

int Levent::handleNetEvent(int nevents){

    for(int i=0;i<nevents;i++){
        
        int fd = _kevents[i].ident;
        int cdata = _kevents[i].data;
        if(fd==_listenfd){
            acceptClient();
        }else{
            receiveClient(fd,cdata);
        }
    }
    return LE_SUCC;
}
    

