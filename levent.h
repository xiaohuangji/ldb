//
//  levent.h
//  MylevelDB
//
//  Created by wills on 13-7-23.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//
#include "llog.h"
#include "linkerManager.h"

#ifndef __MylevelDB__levent__
#define __MylevelDB__levent__

#define NE_NONE 0       // 未设置
#define NE_READABLE 1   // 可读
#define NE_WRITABLE 2   // 可写

#define LE_SUCC 0
#define LE_FAIL -1

#define LE_MAXSIZE 1000

#define LOG_MSG_SIZE 64

class Levent{
public:
    Levent(int listenfd,int size);
    ~Levent();
    void run();
    void stop();
    
private:
    int _size;
    int _stop;
    int _kqfd;//kqueue的fd
    int _listenfd;
    Llog* _logger;
    Lcommand* _command;
    LinkerMananer* _linkerManager;
    static int _cclient;
    struct kevent *_kevents;//kqueue回调的event保存数组
    int handleNetEvent(int nkevents);
    int addNetEvent(int fd,int mask);
    int deleteNetEvent(int fd,int mask);
    int acceptClient();
    int receiveClient(int fd,int cdata);
};
#endif /* defined(__MylevelDB__levent__) */
