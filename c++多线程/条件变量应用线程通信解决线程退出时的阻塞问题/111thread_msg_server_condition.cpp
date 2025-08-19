#include "xmsg_server.h"
#include <sstream>
#include <iostream>
#include  <chrono>
using namespace std;
int main(int argc, char* argv[])
{
    XMsgServer server;
    server.Start();//���� main ��ֻ��Ҫ���� Start()���߳̾ͻ��Զ��������� Stop() ʱ����ȷ���գ������ֶ� join �� detach������һ�ֳ����ķ�װ��ʽ�������̵߳�ʹ�á�
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