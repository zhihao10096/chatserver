#if !defined(USERMODEL_H)
#define USERMODEL_H
#include "user.hpp"

// User表的数据操作类
class UserModel
{
private:
    /* data */
public:
    UserModel(/* args */);
    ~UserModel();
    // User表的增加方法
    bool insert(User &user);
};

#endif // USERMODEL_H
