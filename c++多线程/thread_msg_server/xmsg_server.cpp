
#include "xmsg_server.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace this_thread;
//处理消息的线程入口函数
void XMsgServer::Main()
{
    while (!is_exit())
    {
        sleep_for(10ms);
        unique_lock<mutex> lock(mux_);
        if (msgs_.empty())
            continue;
        while (!msgs_.empty())
        {
            //消息处理业务逻辑
            cout << "recv : " << msgs_.front() << endl;
            msgs_.pop_front();
        }

    }
}

//给当前线程发消息
void XMsgServer::SendMsg(std::string msg)
{
    unique_lock<mutex> lock(mux_);
    msgs_.push_back(msg);
}