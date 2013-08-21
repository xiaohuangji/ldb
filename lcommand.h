//
//  lcommand.h
//  MylevelDB
//
//  Created by wills on 13-7-26.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#ifndef __MylevelDB__lcommand__
#define __MylevelDB__lcommand__

#include <iostream>
#include <sstream>
#include "ldb.h"
#include "lprotocol.h"

class Lcommand{
protected:
    Ldb* ldb;
public:
    virtual bool runcommand(LpBody* lpBody);
    Lcommand();
    bool exec(LpBody* lpBody);
    
};

class putCOMMAND : public Lcommand{
public:
    bool runcommand(LpBody* lpBody);
    
};

class getCOMMAND : public Lcommand{
public:
    bool runcommand(LpBody* lpBody);
};



#endif /* defined(__MylevelDB__lcommand__) */
