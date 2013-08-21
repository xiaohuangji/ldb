//
//  llog.cpp
//  MylevelDB
//
//  Created by wills on 13-7-25.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#include "llog.h"
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

using namespace std;
LLEVEL Llog::_level=DEBUGL;
string Llog::_path;
FILE* Llog::_file;
Llog* Llog::_instance;

Llog::Llog(){
    _file=fopen(_path.c_str(),"a");
    if(NULL==_file)
        exit(1);
}

Llog::~Llog(){
    fclose(_file);
}

void Llog::init(Server s){
    _path=s.log_file;
    
    if(s.log_level.compare("debug")){
        _level=DEBUGL;
    }else if(s.log_level.compare("info")){
        _level=INFOL;
    }else if(s.log_level.compare("warning")){
        _level=WARNINGL;
    }else if(s.log_level.compare("error")){
        _level=ERRORL;
    }else{
        _level=DEBUGL;
    }
}

Llog* Llog::getInstance(){
    if(NULL == _instance){
        _instance= new Llog();
    }    
    return _instance;
}

void Llog::rawLog(LLEVEL level, const char* msg){
    if(level<_level)
        return ;
    const char* levelstr[]={"debug","info","warning","error"};
    char buf[64];
    int off;
    struct timeval tv;
    
    gettimeofday(&tv,NULL);
    off = strftime(buf,sizeof(buf),"%d %b %H:%M:%S.",localtime(&tv.tv_sec));
    snprintf(buf+off,sizeof(buf)-off,"%03d",(int)tv.tv_usec/1000);
    fprintf(_file,"%s %s %s %s\n",buf,levelstr[level],__FILE__,msg);
    fflush(_file);
}

void Llog::error(const string msg){
    rawLog(ERRORL,msg.c_str());
}
void Llog::warning(const string msg){
    rawLog(WARNINGL, msg.c_str());
}
void Llog::info(const string msg){
    rawLog(INFOL, msg.c_str());
}
void Llog::debug(const string msg){
    rawLog(DEBUGL, msg.c_str());
}
void Llog::error(const char* msg){
    rawLog(ERRORL,msg);
}
void Llog::warning(const char* msg){
    rawLog(WARNINGL, msg);
}
void Llog::info(const char* msg){
    rawLog(INFOL, msg);
}
void Llog::debug(const char* msg){
    rawLog(DEBUGL, msg);
}