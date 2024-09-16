#include "chatserver.hpp"
#include <functional>
#include "json.hpp"
#include "chatservice.hpp"
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
    // 达到的目的：完全解耦网络模块的代码和业务模块的代码
    // 通过js["msgid"]获取=》业务handler=》conn js time
    auto msghandler = ChatService::instance()->getHandler(js["msgid"].get<int>());        //注意这里get模板函数
    // 回调消息绑定好的事件处理器，执行相应的业务
    msghandler(conn, js, receiveTime);
}


ChatServer::~ChatServer()
{

}

