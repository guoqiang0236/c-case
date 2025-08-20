#include <thread>
#include <iostream>
#include <future>
#include <string>
#include <chrono>
using namespace std;

// 测试 future 的线程函数
// 接收一个 promise<string>，用于设置异步结果
void TestFuture(promise<string> p)
{
    cout << "begin TestFuture" << endl;
    // 模拟耗时操作，休眠3秒
    this_thread::sleep_for(3s);
    cout << "begin set value" << endl;
    // 设置 promise 的值，通知 future 可以获取结果
    p.set_value("TestFuture value");
    // 再休眠3秒，模拟后续操作
    this_thread::sleep_for(3s);
    cout << "end TestFuture" << endl;
}

int main(int argc, char* argv[])
{
    // 创建 promise，用于异步传递 string 类型变量
    promise<string> p;

    // 通过 promise 获取 future，用于异步获取结果
    auto future = p.get_future();

    // 创建新线程，执行 TestFuture，并将 promise 移交给线程
    auto th = thread(TestFuture, move(p));

    cout << "begin future.get()" << endl;
    // 阻塞等待子线程设置值，获取结果后输出
    cout << "future get() = " << future.get() << endl;
    cout << "end future.get()" << endl;

    // 等待子线程结束
    th.join();

    // 防止程序直接退出，等待用户输入
    getchar();
    return 0;
}