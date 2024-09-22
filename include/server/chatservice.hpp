#if !defined(CHATSERVICE_H)
#define CHATSERVICE_H
#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "json.hpp"
#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
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

    // 数据操作类对象
    UserModel _userModel;
    OfflineMsgeModel _offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;

    // 存储在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    // 互斥锁，保证_userConnMap的线程安全
    mutex _connMutex;

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
    // 一对一聊天
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
        // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);

    // 服务器异常，业务重置方法
    void reset();
};

#endif // CHATSERVICE_H
