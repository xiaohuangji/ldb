ldb
===
基于leveldb的服务端

version:0.1

defect&&roadmap:
1 事件处理只有基于kqueue的。增加linux-epoll支持。
2 client是lua。增加c/c++命令行客户端。
3 client与server的应用层通信协议未经充分测试。
4 只支持get,put两个ldb命令。增加delete,mget,mput命令。
5 tcp连接断开，分批传送等未充分测试。
6 无性能数据。增加性能数据，然后逐步优化。
7 内存溢出等问题未测试。

难缠的问题：
1 据说llvm-g++4.2在预编译头文件时有bug，改用g++4.7后正常。
2 通过链接leveldb动态库有问题，改用静态库后正常。
