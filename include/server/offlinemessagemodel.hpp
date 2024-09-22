#ifndef __OFFLINEMESSAGEMODEL_H__
#define __OFFLINEMESSAGEMODEL_H__
#include <string>
#include <vector>

using namespace std;
// 提供离线消息表的操作接口方法
class OfflineMsgeModel
{
private:
    /* data */
public:
    // OfflineMsgeModel(/* args */);
    // ~OfflineMsgeModel();

    // 存储用户的离线消息
    void insert(int userid, string msg);

    // 删除用户的离线消息
    void remove(int userid);

    // 查询用户离线消息
    vector<string> query(int userid);
};

#endif // __OFFLINEMESSAGEMODEL_H__