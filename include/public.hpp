#if !defined(PUBLIC_H)
#define PUBLIC_H

// server和client的公共文件


enum EnMsgType
{
    LOGIN_MSG = 1,      //登陆消息
    LOGIN_MSG_ACK,      //登录响应消息
    REG_MSG,           //注册消息
    REG_MSG_ACK,         //注册响应消息
    ONE_CHAT_ONE,        //聊天消息
    ADD_FRIEND_MAG,     //添加好友信息
};

#endif // PUBLIC_H