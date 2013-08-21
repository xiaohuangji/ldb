//
//  llinker.h
//  MylevelDB
//
//  Created by wills on 13-8-19.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#ifndef __MylevelDB__linker__
#define __MylevelDB__linker__

#include "lprotocol.h"
#include "lcommand.h"
#include "llog.h"
#include <iostream>

#define BUFFERSIZE 1024

#define LOG_MSG_SIZE 64

class Linker{
private:
    int _fd;
    Lcommand* _lcommand;
    Llog* _logger;
    LpHead* _lpHead;
    LpBody* _lpBody;
    char* _current_head;  // 当前在处理的TCP头
    char* _current_body;  // 当前在处理的包
    char* _buffer;//全局buffer
    int _cursor;//本次处理的游标
    int _plen;//本次处理的buffer长度
    int _current_head_cursor;
    int _current_body_cursor;
    bool parseHead();
    bool parseBody();
    bool getPackage(int llen);
    bool runCommand();
public:
    Linker(int fd):_plen(0),_cursor(0),_current_head_cursor(0),_current_body_cursor(0){
        _fd=fd;
        _lcommand=new Lcommand();
        _logger=Llog::getInstance();
    };
    ~Linker();
    bool handle(int llen);
    friend class LinkerMananer;
};

#endif /* defined(__MylevelDB__llinker__) */
