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
//������Ϣ���߳���ں���
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
            //��Ϣ����ҵ���߼�
            cout << "recv : " << msgs_.front() << endl;
            msgs_.pop_front();
        }

    }
}

//����ǰ�̷߳���Ϣ
void XMsgServer::SendMsg(std::string msg)
{
    unique_lock<mutex> lock(mux_);
    msgs_.push_back(msg);
    lock.unlock();
    cv_.notify_one();
}