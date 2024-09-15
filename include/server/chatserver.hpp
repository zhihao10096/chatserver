#if !defined(CHATSERVER_H)
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

class ChatServer
{
private:
    TcpServer _server;
    EventLoop *_loop;
// 上报连接信息相关的回调
    void onConnection(const TcpConnectionPtr& conn);

    void onMessage(const TcpConnectionPtr& conn,
                            Buffer* buffer,
                            Timestamp receiveTime);


public:
// 初始化聊天服务器对象
    ChatServer(EventLoop* loop,
            const InetAddress& listenAddr,
            const string& nameArg);

    void start();
    ~ChatServer();
};





#endif // CHATSERVER_H
