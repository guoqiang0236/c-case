#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <chrono>
//Linux -lpthread
using namespace std;
static mutex mux;
void TestThread()
{
    for (;;)
    {
        //��ȡ����Դ�����û���������ȴ�
        //mux.lock(); //
        if (!mux.try_lock())
        {
            cout << "." << flush;
            this_thread::sleep_for(100ms);
            continue;
        }
        cout << "==============================" << endl;
        cout << "test 001" << endl;
        cout << "test 002" << endl;
        cout << "test 003" << endl;
        cout << "==============================" << endl;
        mux.unlock();
        this_thread::sleep_for(1000ms);
    }
}
void ThreadMainMux(int i)
{
    for (;;)
    {
        mux.lock();
        cout << i << "[in]" << endl;
        this_thread::sleep_for(1000ms);
        mux.unlock();
        this_thread::sleep_for(1ms);// ��ֹ�߳�unlock�����ϱ��Լ�lock������߳���������Դ
    }
}
int main(int argc, char* argv[])
{
   /* for (int i = 0; i < 3; i++)
    {
        thread th(ThreadMainMux, i + 1);
        th.detach();
    }



    getchar();*/
    for (int i = 0; i < 10; i++)
    {
        thread th(TestThread);
        th.detach();
    }
    getchar();
    return 0;
}