//
//  lprotocol.h
//  MylevelDB
//
//  Created by wills on 13-8-19.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#ifndef __MylevelDB__lprotocol__
#define __MylevelDB__lprotocol__

#include <iostream>
#include <vector>

#define LpHeadLen 8
#define HeadArgc 3
#define HeadBodyLen 5
//头部一共8个字节，3位表示argc,5位表示bodylen。不足位数前面补0
//全部是字符串格式表示。
//002000103#get4#test这种格式
//003000203#put4#test10#0123456789

//上行命令head包装体
class LpHead{
public:
    int argc;
    int bodylen;
};
//上行命令body包装体
//put key  value
//get key
//mput key1 value1 key2 value2
//get key1 key2
class  LpBody{
public:
    std::string command;
    std::vector<std::string> keys;
    std::vector<std::string> values;
    std::string result;
};



#endif /* defined(__MylevelDB__lprotocol__) */
