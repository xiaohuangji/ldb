//
//  llinker.cpp
//  MylevelDB
//
//  Created by wills on 13-8-19.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#include "linker.h"
#include "lnet.h"
#include <stdlib.h>
using namespace std;

Linker::~Linker(){
    TcpServer::tcpClose(_fd);
    free(_lcommand);
}

bool Linker::getPackage(int llen){
    _buffer=(char*)malloc(llen);
    int hrSize=0;
    while( hrSize<llen ){
        int c=TcpServer::tcpRead(_fd, _buffer+hrSize, llen-hrSize);
        if(c==-1)
            return false;
        hrSize+=c;
    }
    *(_buffer+llen)=NULL;
    _plen=hrSize;
    return true;
}

bool Linker::parseHead(){
    if(_current_head_cursor<LpHeadLen){
        int left_head_size=LpHeadLen-_current_head_cursor;//头部还需要这么多数据才能完成
        int left_buffer=_plen-_cursor;//还有这些数据可供组装
       // if(_current_head==NULL){
            _current_head=(char*)malloc(LpHeadLen);
        //}
        if(left_head_size>left_buffer)//剩下的包不够head。
        {
            strncpy(_current_head+_current_head_cursor,_buffer+_cursor,left_buffer);
            _current_head_cursor+=left_buffer;
            _cursor+=left_buffer;
            return false;//返回false,中断接下来的解析执行。
        }else{
            strncpy(_current_head+_current_head_cursor,_buffer+_cursor,left_head_size);
            _current_head_cursor+=left_head_size;
            _cursor+=left_head_size;
            *(_current_head+_current_head_cursor)=NULL;
            return true;//头已经解析完成，接着执行body
        }
        
    }
    return true;
}

bool genHead(LpHead* lpHead,const char* data){
    
    char argc[HeadArgc+1];
    strncpy(argc, data, HeadArgc);
    argc[HeadArgc]=NULL;
    char bodylen[HeadBodyLen+1];
    strncpy(bodylen, data+HeadArgc, HeadBodyLen);
    bodylen[HeadBodyLen]=NULL;
    lpHead->argc=atoi(argc);
    lpHead->bodylen=atoi(bodylen);
    return true;
}
bool genBody(LpBody* lpBody,const char* data){
    const char* temp=data;
    vector<string> vv;
    int i=0;
    int j=0;
    while(*temp){
        ++j;
        if(*temp=='#'){
            char* c=(char*)malloc(j);
            strncpy(c,data+i,j);
            c[j-1]=NULL;
            int count=atoi(c);
            char* str=(char*)malloc(count);
            strncpy(str,temp+1,count);
            vv.push_back(string(str));
            temp+=count;
            i=i+j+count;
            j=0;
            free(c);
            free(str);
        }
        ++temp;
        
    }
    vector<string>::iterator vit=vv.begin();
    std::vector<string> keys;
    std::vector<string> values;
    int k=0;
    while(vit!=vv.end()){
        if(k==0){
            lpBody->command=*vit;
        }
        if(k!=0&&k%2==0){//偶数
            values.push_back(*vit);
        }
        if(k%2==1){//奇数
            keys.push_back(*vit);
        }
        ++vit;
        ++k;
    }
    
    lpBody->keys=keys;
    lpBody->values=values;
    return true;
}

bool Linker::parseBody(){
    //要根据head内容才能解析出body
    _lpHead=new LpHead();
    genHead(_lpHead,_current_head);
    
    int bodyLen=_lpHead->bodylen;
    if(_current_body_cursor<bodyLen){
        int left_body_size=bodyLen-_current_body_cursor;//body还需要这么多数据才能完成
        int left_buffer=_plen-_cursor;//还有这些数据可供组装
        
        _current_body=(char*)malloc(bodyLen);
       
        if(left_body_size>left_buffer)//剩下的包不够body。
        {
            strncpy(_current_body+_current_body_cursor,_buffer+_cursor,left_buffer);
            _current_body_cursor+=left_buffer;
            _cursor+=left_buffer;
            return false;//返回false,中断接下来的解析执行。
        }else{
            strncpy(_current_body+_current_body_cursor,_buffer+_cursor,left_body_size);
            _current_body_cursor+=left_body_size;
            _cursor+=left_body_size;
            *(_current_body+_current_body_cursor)=NULL;
            return true;//body解析完成，执行后续逻辑
        }
        
    }
    return true;
    
}

bool Linker::runCommand(){
    _lpBody=new LpBody();
    genBody(_lpBody,_current_body);
    
    _lcommand->exec(_lpBody);
    _logger->info(_lpBody->command+":"+_lpBody->result);

    int r=TcpServer::tcpWrite(_fd, _lpBody->result.c_str(), _lpBody->result.length());
    if(r==-1)
        return false;
    return true;
}
bool Linker::handle(int llen){
    
    if(!getPackage(llen)) return false;
    
    while(_cursor<_plen){
        if(!parseHead())///解析了一半的head，不进行下去
            break;
        if(!parseBody())//解析了一半的body，不进行下去。
            break;
        //当前head和body都正确解析，执行
        //执行命令并返回
        
        runCommand();
        //重置current游标
        _current_head_cursor=0;
        _current_body_cursor=0;
        free(_current_head);
        free(_current_body);
        delete _lpBody;
        delete _lpHead;
    }
    //buffer全部解析完成，还原全局设置
    free(_buffer);
    _cursor=0;
    _plen=0;
    return true;
}



