//
//  stringParse.h
//  MylevelDB
//
//  Created by wills on 13-7-26.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#ifndef MylevelDB_comandParse_h
#define MylevelDB_comandParse_h
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Parse{
public:
    static string* parseA(string commandStr,int argc){
        string* data=new string[argc];
        
        istringstream iss(commandStr);
        int i=0;
        do
        {
            string sub;
            iss >> sub;
            if(!sub.empty())
                data[i++]=sub;
        } while (iss);

        return data;
    }
    
    static string parseC(string commandStr){
        string c;
        istringstream iss(commandStr);
        do
        {
            string sub;
            iss >> sub;
            if(!sub.empty()){
                c=sub;
                return c;
            }
        } while (iss);
        
        return "";
    }
    
    static vector<string> split(string& str,const char* c)
    {
        char *cstr, *p;
        vector<string> res;
        cstr = new char[str.size()+1];
        strcpy(cstr,str.c_str());
        p = strtok(cstr,c);
        while(p!=NULL)
        {
            res.push_back(p);
            p = strtok(NULL,c);
        }
        return res;
    }
};
#endif
