#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

/*
1.组合TcpServer对象
2.创建EventLoop事件循环对象的指针
3.明确TcpServer构造函数需要的参数，输出ChatServer的构造函数
   TcpServer没有默认构造函数
*/
class ChatServer
{
private:
    TcpServer _server; // #1
    EventLoop *_loop;  // #2

    //专门处理用户的连接创建和断开      epoll  listenfd  accept
    void onConnection(const TcpConnectionPtr&)
    {

    }
public:
    ChatServer(EventLoop *loop,         //事件循环
               const InetAddress &listenAddr,       //IP+Port
               const string &nameArg)               //服务器的名字
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        //给服务器注册用户连接的创建和断开回调
        // 这里，由于回调函数有一个参数，所以使用绑定器，并使用一个参数占位符
        _server.setConnectionCallback(bind(&ChatServer::onConnection, this, _1));
        //给服务器注册用户读写事件回调
    }
    ~ChatServer() {}
};
