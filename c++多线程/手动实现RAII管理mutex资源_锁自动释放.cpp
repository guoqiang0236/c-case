#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>
//Linux -lpthread
using namespace std;

// RAII风格的互斥锁管理类
// 构造时自动加锁，析构时自动解锁，确保作用域内线程安全
class XMutex
{
public:
    // 构造函数：加锁
    XMutex(mutex& mux) :mux_(mux)
    {
        cout << "Lock" << endl;
        mux.lock();
    }
    // 析构函数：解锁
    ~XMutex()
    {
        cout << "Unlock" << endl;
        mux_.unlock();
    }
private:
    mutex& mux_; // 引用外部互斥锁对象
};

static mutex mux; // 全局互斥锁

// 测试互斥锁的函数
// 进入函数时自动加锁，离开时自动解锁
void TestMutex(int status)
{
    XMutex lock(mux); // 作用域锁，确保本函数执行期间持有锁
    if (status == 1)
    {
        cout << "=1" << endl;
        return;
    }
    else
    {
        cout << "!=1" << endl;
        return;
    }
}

int main(int argc, char* argv[])
{
    TestMutex(1); // 测试status为1的情况
    TestMutex(2); // 测试status不为1的情况

    getchar(); // 防止程序直接退出
    return 0;
}