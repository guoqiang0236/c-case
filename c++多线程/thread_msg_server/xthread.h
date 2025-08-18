
#pragma once
#include <thread>
class XThread
{
public:
    //�����߳�
    virtual void Start();

    //�����߳��˳���־ ���ȴ�
    virtual void Stop();

    //�ȴ��߳��˳���������
    virtual void Wait();

    //�߳��Ƿ��˳�
    bool is_exit();
private:
    //�߳����
    virtual void Main() = 0;
    bool is_exit_ = false;
    std::thread th_;
};

