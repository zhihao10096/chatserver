#include "chatservice.hpp"
#include "public.hpp"
#include "muduo/base/Logging.h"

using namespace muduo;

ChatService::ChatService(/* args */)
{
    // 成员函数作回调函数，需要使用绑定器
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
    _msgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});
}

ChatService::~ChatService()
{
}

// 这里类外实现不需加static
ChatService *ChatService::instance()
{
    static ChatService service;
    return &service;
}

void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "do login service!!";
}

void ChatService::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "do reg service!!";

}

MagHandler ChatService::getHandler(int msgid)
{
    // 记录错误日至，msgid没有对应的事件处理回调
    auto it = _msgHandlerMap.find(msgid);
    if (it == _msgHandlerMap.end())
    {
        // 返回一个默认的处理器，空操作
        return [=](const TcpConnectionPtr &conn, json &js, Timestamp time)
        {
            LOG_ERROR << "msgid:" << msgid << "can not find handler!";
        };
    }
    else
    {
        return _msgHandlerMap[msgid];
    }
}
