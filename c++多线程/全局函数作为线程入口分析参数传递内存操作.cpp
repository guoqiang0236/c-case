#include <thread>
#include <iostream>
#include <string>
#include <chrono>
//Linux -lpthread
using namespace std;
class Para
{
public:
    Para() { cout << "Create Para" << endl; }
    Para(const Para& p) { cout << "Copy Para" << endl; }
    ~Para() { cout << "Drop Para" << endl; }
    string name;
};

void ThreadMain(int p1, float p2, string str, Para p4)
{
    this_thread::sleep_for(100ms);
    cout << "ThreadMain " << p1 << " " << p2 << " " << str << " " << p4.name << endl;
}

int main(int argc, char* argv[])
{
    thread th;
    {
        float f1 = 12.1f;
        Para p;
        p.name = "test Para class";
        //所有的参数做复制
        th = thread(ThreadMain, 101, f1, "test string para", p);//1.第一次拷贝：std::thread 构造时，将 p 拷贝到线程对象内部（用于异步传递参数）。
    }
    th.join();//2.	第二次拷贝：线程启动时，std::thread 再把这个参数拷贝到新线程的栈上，作为 ThreadMain 的参数 p4。
    return 0;
}