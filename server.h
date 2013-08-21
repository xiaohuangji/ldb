//
//  server.h
//  MylevelDB
//
//  Created by wills on 13-7-25.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#include <iostream>

#ifndef __MylevelDB__server__
#define __MylevelDB__server__

struct  Server{
    bool daemon;
    int port;
    std::string host;
    int max_client;
    std::string log_file;
    std::string log_level;
    std::string db_dir;
};



#endif /* defined(__MylevelDB__server__) */
