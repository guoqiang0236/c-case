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
        //获取锁资源，如果没有则阻塞等待
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
        this_thread::sleep_for(1ms);
    }
}
timed_mutex tmux;//超时锁

void ThreadMainTime(int i)
{


    for (;;)
    {
        if (!tmux.try_lock_for(chrono::milliseconds(500)))//线程尝试在 500 毫秒内获取 tmux 锁，如果失败（超时），就输出提示并继续下一轮。
        {
            cout << i << "[try_lock_for timeout]" << endl;
            continue;
        }
        cout << i << "[in]" << endl;
        this_thread::sleep_for(2000ms);
        tmux.unlock();
        this_thread::sleep_for(1ms);
    }
}

recursive_mutex rmux;//递归锁
void Task1()
{
    rmux.lock();
    cout << "task1 [in]" << endl;
    rmux.unlock();
}
void Task2()
{
    rmux.lock();
    cout << "task2 [in]" << endl;
    rmux.unlock();
}
void ThreadMainRec(int i)
{
    for (;;)
    {
        rmux.lock();
        Task1();
        cout << i << "[in]" << endl;
        this_thread::sleep_for(2000ms);
        Task2();
        rmux.unlock();
        this_thread::sleep_for(1ms);
    }
}
int main(int argc, char* argv[])
{
    for (int i = 0; i < 3; i++)
    {
        thread th(ThreadMainRec, i + 1);
        th.detach();
    }
    getchar();
    for (int i = 0; i < 3; i++)
    {
        thread th(ThreadMainTime, i + 1);
        th.detach();
    }
    getchar();
    for (int i = 0; i < 3; i++)
    {
        thread th(ThreadMainMux, i + 1);
        th.detach();
    }



    getchar();
    for (int i = 0; i < 10; i++)
    {
        thread th(TestThread);
        th.detach();
    }
    getchar();
    return 0;
}