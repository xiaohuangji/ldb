//
//  lconfig.cpp
//  MylevelDB
//
//  Created by wills on 13-7-25.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#include "lconfig.h"
#include <stdlib.h>

using namespace std;

Lconfig::Lconfig(const string &path){
    _path=path;
}

void initOneSetting(Server* server,const string key ,const string value){
    if(key=="host"){
        server->host=value;
        return;
    }
    if(key=="port"){
        server->port= atoi(value.c_str());
        return;
    }
    if(key=="log_level"){
        server->log_level=value;
        return;
    }
    if(key=="log_file"){
        server->log_file=value;
        return;
    }
    if(key=="daemon"){
        if(value=="0")
            server->daemon=false;
        else
            server->daemon=true;
        return;
    }
    if(key=="max_client"){
        server->max_client=atoi(value.c_str());
        return;
    }
    if(key=="db_dir"){
        server->db_dir=value;
        return;
    }
    if(key=="pid_file"){
        server->pid_file=value;
        return;
    }
}

Server* Lconfig::initServerConfig(){
    Server* server=new Server();
    _file=new ifstream(_path.c_str());
    char buf[100];
    while(!_file->eof()){
        _file->getline(buf, 100);
        string s=string(buf);
        if(s.length()==0)
            continue;
        string::size_type position=s.find("=");
        string key=s.substr(0,position);
        string value=s.substr(position+1,s.length()-1);
        initOneSetting(server, key,value);
    }
    delete _file;
    return server;
}