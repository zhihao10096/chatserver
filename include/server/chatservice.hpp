#if !defined(CHATSERVICE_H)
#define CHATSERVICE_H
#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

// 使用回调函数，根据参数调用不同的函数
// 这里后面试一下参数列表为空可不可以，反正后面会用绑定器
using MagHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp time)>;

// 聊天服务器业务类
class ChatService
{
private:
    // 存储消息ID和对应的业务处理方法
    unordered_map<int, MagHandler> _msgHandlerMap;

    // 对成员属性初始化
    ChatService(/* args */);

public:
    // 获取单例对象
    static ChatService *instance();
    ~ChatService();
    // 处理登陆业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 获取消息对应的处理器
    MagHandler getHandler(int msgid);
};

#endif // CHATSERVICE_H
