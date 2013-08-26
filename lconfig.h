//
//  lconfig.h
//  MylevelDB
//
//  Created by wills on 13-7-25.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#ifndef __MylevelDB__lconfig__
#define __MylevelDB__lconfig__

#include <iostream>
#include <fstream>
#include "server.h"

class Lconfig{
public:
    Lconfig(const std::string &path);
    Server* initServerConfig();
    
private:
    std::string _path;
    std::ifstream * _file;
};

#endif /* defined(__MylevelDB__lconfig__) */
