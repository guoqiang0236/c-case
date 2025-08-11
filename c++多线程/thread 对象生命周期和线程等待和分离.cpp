#include <thread>
#include <iostream>
//Linux -lpthread
using namespace std;
bool is_exit = false;
void ThreadMain()
{
    cout << "begin sub thread main " << this_thread::get_id() << endl;
    for (int i = 0; i < 10; i++)
    {
        if (!is_exit) break;
        cout << "in thread " << i << endl;
        this_thread::sleep_for(chrono::seconds(1));//1000ms
    }
    cout << "end sub thread main " << this_thread::get_id() << endl;
}
int main(int argc, char* argv[])
{
    {
        //thread th(ThreadMain); //����thread�������� ���̻߳�������
    }
    {
        thread th(ThreadMain);
        th.detach(); //���߳������̷߳��� �ػ��߳�
        //�� �����߳��˳��� ���̲߳�һ���˳�
    }

    {
        thread th(ThreadMain);
        this_thread::sleep_for(chrono::seconds(1));//1000ms
        is_exit = true; //֪ͨ���߳��˳�
        cout << "���߳��������ȴ����߳��˳�" << endl;
        th.join(); //���߳��������ȴ����߳��˳�
        cout << "���߳��Ѿ��˳���" << endl;
    }
    getchar();

    return 0;
}