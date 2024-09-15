#include "chatserver.hpp"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "Chatserver");

    server.start();
    loop.loop();

    
    return 0;
}
