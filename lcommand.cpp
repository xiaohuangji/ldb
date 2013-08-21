//
//  lcommand.cpp
//  MylevelDB
//
//  Created by wills on 13-7-26.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#include "lcommand.h"
using namespace std;

Lcommand::Lcommand(){
    ldb=Ldb::getInstance();
}

bool Lcommand::runcommand(LpBody* lpBody){
    return false;
}

bool Lcommand::exec(LpBody* lpBody){
    string cname=lpBody->command;
    Lcommand* command;
    if(cname=="put"){
        command=new putCOMMAND();
    }else if(cname=="get"){        
        command=new getCOMMAND();
    }else{
        return false;
    }
    return command->runcommand(lpBody);
    
}

bool putCOMMAND::runcommand(LpBody* lpBody){
    if(ldb->put(lpBody->keys.at(0),lpBody->values.at(0)))
        lpBody->result="PUT OK";
    return true;
}

bool getCOMMAND::runcommand(LpBody* lpBody){
    if(!ldb->get(lpBody->keys.at(0),lpBody->result))
        lpBody->result="NOT FOUND";
    return true;

}