#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>
#include <string>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

/*
1.组合TcpServer对象
2.创建EventLoop事件循环对象的指针
3.明确TcpServer构造函数需要的参数，输出ChatServer的构造函数
   TcpServer没有默认构造函数
4.在当前服务器类的构造函数当中，注册处理连接的回调函数和处理读写事件的回调函数
5.设置合适的服务端线程数量，muduo库会自己分配I/o线程和worker线程
*/
class ChatServer
{
private:
    TcpServer _server; // #1
    EventLoop *_loop;  // #2

    // 专门处理用户的连接创建和断开      epoll  listenfd  accept
    void onConnection(const TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << "state:online" << endl;
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << "state:offline" << endl;
            conn->shutdown();       //close()
        }
        
    }
    // 专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn,
                   Buffer *buffer,
                   Timestamp receiveTime)
    {
        string buf = buffer->retrieveAllAsString();
        cout << "recv data:"  << buf << "time :" << receiveTime.toString() << endl;
        conn->send(buf);
    }

public:
    ChatServer(EventLoop *loop,               // 事件循环
               const InetAddress &listenAddr, // IP+Port
               const string &nameArg)         // 服务器的名字
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        // 给服务器注册用户连接的创建和断开回调
        //  这里，由于回调函数有一个参数，所以使用绑定器，并使用一个参数占位符
        _server.setConnectionCallback(bind(&ChatServer::onConnection, this, _1));
        // 给服务器注册用户读写事件回调
        _server.setMessageCallback(bind(&ChatServer::onMessage, this, _1, _2, _3));

        // 设置服务器端的线程数量       1个IO线程，3个worker线程
        _server.setThreadNum(4);
    }

    // 开启事件循环
    void start()
    {
        _server.start();
    }
    ~ChatServer() {}
};


int main(int argc, char const *argv[])
{
    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");

    server.start();     //listenfd epoll_ctl=>epoll
    loop.loop();        //epol1_wait以阻塞方式等待新用户连接，已连接用户的读写事件等
    return 0;
}

