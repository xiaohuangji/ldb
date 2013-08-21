//
//  db.h
//  MylevelDB
//
//  Created by wills on 13-7-20.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#ifndef MylevelDB_db_h
#define MylevelDB_db_h

#include <leveldb/db.h>
#include <iostream>
#include "server.h"

class Ldb{
    
public:
    bool put(const std::string key ,const std::string value);
    bool get(const std::string key,std::string &result);
    static Ldb* getInstance();
    static void init(Server s);
private:
    Ldb();
    ~Ldb();
    static leveldb::DB* rdb;
    static Ldb* _instance;
    static pthread_mutex_t db_lock;
    static std::string db_dir;
};


#endif
