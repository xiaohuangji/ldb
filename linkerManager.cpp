//
//  linkerManager.cpp
//  MylevelDB
//
//  Created by wills on 13-8-19.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#include "linkerManager.h"
using namespace std;


bool LinkerMananer::handle(int fd,int llen){
    list<Linker*>::iterator itr=_linkers.begin();
    while(itr!=_linkers.end()){
        if((*itr)->_fd==fd)
            break;
        ++itr;
    }
    if(itr!=_linkers.end()){
        char buf[LOG_MSG_SIZE];
        sprintf(buf, "%s:%d","linker exsited linkers:",_linkers.size());
        _logger->info(buf);
        return (*itr)->handle(llen);
    }else{
        Linker *linker=new Linker(fd);
        _linkers.push_back(linker);
        char buf[LOG_MSG_SIZE];
        sprintf(buf, "%s:%d","pushback to linkermanager:",fd);
        _logger->info(buf);
        return _linkers.back()->handle(llen);
    }
    
}

void LinkerMananer::rmLinker(int fd){
    list<Linker*>::iterator itr=_linkers.begin();
    while(itr!=_linkers.end()){
        if((*itr)->_fd==fd){
            _linkers.erase(itr);
            delete *itr;
            break;
        }
    }
}