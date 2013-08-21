//
//  tcpserver.h
//  MylevelDB
//
//  Created by wills on 13-7-20.
//  Copyright (c) 2013年 renren-pc. All rights reserved.
//

#ifndef MylevelDB__lnet_h
#define MylevelDB__lnet_h


class TcpServer{
public:
    static int tcpWrite(int fd,const char* buf,int count);
    static int tcpRead(int fd,char* buf ,int count);
    static int tcpListen(const char* ip,int port);
    static int tcpAccept(int fd);
    static int tcpClose(int fd);
};

#endif /* defined(__MylevelDB__lnet_h) */
