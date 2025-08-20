#include <thread>
#include <iostream>
#include <future>
#include <string>
#include <chrono>
using namespace std;

// ���� future ���̺߳���
// ����һ�� promise<string>�����������첽���
void TestFuture(promise<string> p)
{
    cout << "begin TestFuture" << endl;
    // ģ���ʱ����������3��
    this_thread::sleep_for(3s);
    cout << "begin set value" << endl;
    // ���� promise ��ֵ��֪ͨ future ���Ի�ȡ���
    p.set_value("TestFuture value");
    // ������3�룬ģ���������
    this_thread::sleep_for(3s);
    cout << "end TestFuture" << endl;
}

int main(int argc, char* argv[])
{
    // ���� promise�������첽���� string ���ͱ���
    promise<string> p;

    // ͨ�� promise ��ȡ future�������첽��ȡ���
    auto future = p.get_future();

    // �������̣߳�ִ�� TestFuture������ promise �ƽ����߳�
    auto th = thread(TestFuture, move(p));

    cout << "begin future.get()" << endl;
    // �����ȴ����߳�����ֵ����ȡ��������
    cout << "future get() = " << future.get() << endl;
    cout << "end future.get()" << endl;

    // �ȴ����߳̽���
    th.join();

    // ��ֹ����ֱ���˳����ȴ��û�����
    getchar();
    return 0;
}