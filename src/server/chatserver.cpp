#include "chatserver.hpp"
#include <functional>
#include "json.hpp"
#include <string>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg) : _server(loop, listenAddr, nameArg), _loop(loop)
{
    _server.setConnectionCallback(bind(&ChatServer::onConnection, this, _1));

    _server.setMessageCallback(bind(&ChatServer::onMessage, this, _1, _2, _3));

    _server.setThreadNum(4);
}



void ChatServer::start()
{
    _server.start();
}


void ChatServer::onConnection(const TcpConnectionPtr& conn)
{
    // 客户端断开连接
    if (!conn->connected())
    {
        conn->shutdown();
    }
    

}



void ChatServer::onMessage(const TcpConnectionPtr& conn,
                            Buffer* buffer,
                            Timestamp receiveTime)
{
    string buf = buffer->retrieveAllAsString();
    // 数据反序列化
    json js = json::parse(buf);

    
}


ChatServer::~ChatServer()
{

}

