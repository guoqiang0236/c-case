#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <shared_mutex>
//Linux -lpthread
using namespace std;

// RAII���Ļ�����������
// ����ʱ�Զ�����������ʱ�Զ�������ȷ�����������̰߳�ȫ
class XMutex
{
public:
    // ���캯��������
    XMutex(mutex& mux) :mux_(mux)
    {
        cout << "Lock" << endl;
        mux.lock();
    }
    // ��������������
    ~XMutex()
    {
        cout << "Unlock" << endl;
        mux_.unlock();
    }
private:
    mutex& mux_; // �����ⲿ����������
};

static mutex mux; // ȫ�ֻ�����

// ���Ի������ĺ���
// ���뺯��ʱ�Զ��������뿪ʱ�Զ�����
void TestMutex(int status)
{
    XMutex lock(mux); // ����������ȷ��������ִ���ڼ������
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
    TestMutex(1); // ����statusΪ1�����
    TestMutex(2); // ����status��Ϊ1�����

    getchar(); // ��ֹ����ֱ���˳�
    return 0;
}