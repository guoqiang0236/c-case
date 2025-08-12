#include <thread>
#include <iostream>
#include <string>
#include <chrono> // ��Ӵ���
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

void ThreadMainPtr(Para* p)
{
    this_thread::sleep_for(100ms);
    cout << "ThreadMainPtr name = " << p->name << endl;
}

void ThreadMainRef(Para& p)
{
    this_thread::sleep_for(100ms);
    cout << "ThreadMainPtr name = " << p.name << endl;
}
int main(int argc, char* argv[])
{
    {
        //��������
        Para p;
        p.name = "test ref";
        thread th(ThreadMainRef, ref(p));
        th.join();
    }
    getchar();

    {
        //�����߳�ָ��
        Para p;
        p.name = "test ThreadMainPtr name";
        thread th(ThreadMainPtr, &p); //���� ���̷߳��ʵ�p�ռ����ǰ�ͷ�
        th.detach();
    }
    // Para �ͷ�
    getchar();
    {
        //�����߳�ָ��
        Para p;
        p.name = "test ThreadMainPtr name";
        thread th(ThreadMainPtr, &p);
        th.join();
        getchar();
    }


    thread th;
    {
        float f1 = 12.1f;
        Para p;
        p.name = "test Para class";
        //���еĲ���������
        th = thread(ThreadMain, 101, f1, "test string para", p);
    }
    th.join();
    return 0;
}