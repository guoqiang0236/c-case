

#pragma once
#include "xthread.h"
#include <string>
#include <list>
#include <mutex>
class XMsgServer:public XThread
{
public:
    //����ǰ�̷߳���Ϣ
    void SendMsg(std::string msg);

private:
    //������Ϣ���߳���ں���
    void Main() override;

    //��Ϣ���л���
    std::list<std::string> msgs_;

    //���������Ϣ����
    std::mutex mux_;
    
};

