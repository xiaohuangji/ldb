//
//  llog.h
//  MylevelDB
//
//  Created by wills on 13-7-25.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#ifndef __MylevelDB__llog__
#define __MylevelDB__llog__
#include <iostream>
#include "server.h"

enum LLEVEL{
    DEBUGL,
    INFOL,
    WARNINGL,
    ERRORL
};

class Llog{
public:
    static void init(Server* s);
    static Llog* getInstance();
    void debug(const std::string msg);
    void info(const std::string msg);
    void warning(const std::string msg);
    void error(const std::string msg);
    void debug(const char* msg);
    void info(const char* msg);
    void warning(const char* msg);
    void error(const char* msg);
    void log(LLEVEL level,const char* fmt,...);
private:
    Llog();
    ~Llog();
    static Llog* _instance;
    void rawLog(LLEVEL level,const char* msg);
    static FILE* _file;
    static LLEVEL _level;
    static std::string _path;
};

#endif /* defined(__MylevelDB__llog__) */
