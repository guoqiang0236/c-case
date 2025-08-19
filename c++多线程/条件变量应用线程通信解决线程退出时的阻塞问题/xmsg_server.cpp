#include "xmsg_server.h"
#include <iostream>
using namespace std;
using namespace this_thread;
void XMsgServer::Stop()
{
    is_exit_ = true;
    cv_.notify_all();
    Wait();
}
//处理消息的线程入口函数
void XMsgServer::Main()
{
    while (!is_exit())
    {
        //sleep_for(10ms);
        unique_lock<mutex> lock(mux_);
        cv_.wait(lock, [this] 
            {
                cout << "wait cv" << endl;
                if (is_exit())return true;
                return !msgs_.empty(); 
            });
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
    lock.unlock();
    cv_.notify_one();
}