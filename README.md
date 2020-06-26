Yuange
===

Yuange is C++ project to wrap the leveldb library. Initially want to build a very cool application like Redis. 

===
基于leveldb的服务端

version
===
0.1

defect&&roadmap:
===

1 事件处理只有基于kqueue的。增加linux-epoll支持。

2 client是lua。增加c/c++命令行客户端。

3 client与server的应用层通信协议未经充分测试。

4 只支持get,put两个ldb命令。增加delete,mget,mput命令。

5 tcp连接断开，分批传送等未充分测试。

6 无性能数据。增加性能数据，然后逐步优化。

7 内存溢出等问题未测试。

8 完善异常处理，增加中断信号处理。
