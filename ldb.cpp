//
//  db.cpp
//  MylevelDB
//
//  Created by wills on 13-7-20.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#include "ldb.h"
using namespace std;

leveldb::DB* Ldb::rdb;
Ldb* Ldb::_instance;
pthread_mutex_t Ldb::db_lock;
string Ldb::db_dir;

Ldb::Ldb(){
    pthread_mutex_init(&db_lock, NULL);
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, db_dir, &rdb);
}
void Ldb::init(Server* s){
    db_dir=s->db_dir;
}

Ldb::~Ldb(){
    delete rdb;
}
Ldb* Ldb::getInstance(){
    if(_instance==NULL){
        _instance=new Ldb();
    }
    return _instance;
}

bool Ldb::put(const string key ,const string value){
    pthread_mutex_lock(&db_lock);
    leveldb::Status s;
    s = rdb->Put(leveldb::WriteOptions(), key,value);
    pthread_mutex_unlock(&db_lock);
    return s.ok();
}

bool Ldb::get(const string key,string &result){
    leveldb::Status s;
    s = rdb->Get(leveldb::ReadOptions(), key, &result);
    return s.ok();
}
