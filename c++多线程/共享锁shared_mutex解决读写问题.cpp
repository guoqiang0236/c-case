#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <chrono>
//Linux -lpthread
using namespace std;
//c++17  ������
//shared_mutex smux;

//c++14 
shared_timed_mutex stmux;

void ThreadRead(int i)
{
    for (;;)
    {
        stmux.lock_shared();
        cout << i << " Read" << endl;
        this_thread::sleep_for(500ms);
        stmux.unlock_shared();
        this_thread::sleep_for(1ms);
    }
}
void ThreadWrite(int i)
{
    for (;;)
    {
        stmux.lock_shared();
        //��ȡ����
        stmux.unlock_shared();
        stmux.lock(); //������ д��
        cout << i << " Write" << endl;
        this_thread::sleep_for(300ms);
        stmux.unlock();
        this_thread::sleep_for(1ms);
    }
}
int main(int argc, char* argv[])
{
    for (int i = 0; i < 3; i++)
    {
        thread th(ThreadWrite, i + 1);
        th.detach();
    }
    for (int i = 0; i < 3; i++)
    {
        thread th(ThreadRead, i + 1);
        th.detach();
    }
    getchar();
    return 0;
}