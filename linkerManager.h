//
//  linkerManager.h
//  MylevelDB
//
//  Created by wills on 13-8-19.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#ifndef __MylevelDB__linkerManager__
#define __MylevelDB__linkerManager__

#include <iostream>
#include <list>
#include "linker.h"
#include "llog.h"

#define LOG_MSG_SIZE 64

class LinkerMananer{
public:
    bool handle(int fd,int len);
    void rmLinker(int fd);
    LinkerMananer(){
        _logger=Llog::getInstance();
    }
private:
    Llog* _logger;
    std::list<Linker*> _linkers;
};
#endif /* defined(__MylevelDB__linkerManager__) */
