#include "xmsg_server.h"
#include <sstream>
#include <iostream>
#include  <chrono>
using namespace std;
int main(int argc, char* argv[])
{
    XMsgServer server;
    server.Start();//你在 main 里只需要调用 Start()，线程就会自动启动并在 Stop() 时被正确回收，无需手动 join 或 detach。这是一种常见的封装方式，简化了线程的使用。
    for (int i = 0; i < 10; i++)
    {
        stringstream ss;
        ss << " msg : " << i + 1;
        server.SendMsg(ss.str());
        this_thread::sleep_for(500ms);
    }
    server.Stop();
    cout << "Server stoped!" << endl;
    return 0;
}