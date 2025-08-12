#include <thread>
#include <iostream>
#include <string>
//Linux -lpthread
#include <chrono>
using namespace std;
class MyThread
{
public:
    //入口线程函数
    void Main()
    {
        cout << "MyThread Main " << name << ":" << age;
    }
    string name;
    int age = 100;
};
class XThread
{
public:
    virtual void Start()
    {
        is_exit_ = false;
        th_ = std::thread(&XThread::Main, this);
    }
    virtual void Stop()
    {
        is_exit_ = true;
        Wait();
    }
    virtual void Wait()
    {
        if (th_.joinable())
            th_.join();
    }
    bool is_exit() { return is_exit_; }
private:
    virtual void Main() = 0;
    std::thread th_;
    bool is_exit_ = false;
};
class TestXThread :public XThread
{
public:
    void Main() override
    {
        cout << "TestXThread Main begin" << endl;
        while (!is_exit())
        {
            this_thread::sleep_for(100ms);
            cout << "." << flush;
        }
        cout << "TestXThread Main end" << endl;
    }
    string name;
};
int main(int argc, char* argv[])
{
    TestXThread testth;
    testth.name = "TestXThread name ";
    testth.Start();
    this_thread::sleep_for(3s);
    testth.Stop();

    testth.Wait();
    getchar();//主线程被 getchar() 阻塞

    MyThread myth;
    myth.name = "Test name 001";
    myth.age = 20;
    thread th(&MyThread::Main, &myth);
    th.join();
   

    return 0;
}