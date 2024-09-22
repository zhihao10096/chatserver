#ifndef __FRIENDMODEL_H__
#define __FRIENDMODEL_H__

#include"user.hpp"
#include <vector>
using namespace std;
// 维护好友信息的操作接口方法
class FriendModel
{
private:
    /* data */
public:
    FriendModel(/* args */);
    ~FriendModel();

    // 添加好友关系
    void insert(int userid, int friendid);

    // 返回用户好友列表
    // 从Friend表中查到id，再从User中查到用户名
    vector<User> query(int userid);
};




#endif // __FRIENDMODEL_H__