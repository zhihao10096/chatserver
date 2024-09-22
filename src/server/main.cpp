#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>

using namespace std;

// 处理服务器ctrl+c结束后，重置user的状态信息
void resetHandler(int)
{
    ChatService::instance()->reset();
    // cout << "------------------捕捉到信号" << endl;
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, resetHandler);

    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "Chatserver");

    server.start();
    loop.loop();

    
    return 0;
}
