#include <iostream>
using namespace std;

// 代理类的基类
class Communication
{
public:
    virtual void communicate() = 0;
    virtual ~Communication() {}
};

// 子类 - 讲话的类
class Speaker : public Communication
{
public:
    void communicate()
    {
        cout << "开始说话..." << endl;
        cout << "通话时发生了一些列的表情变化..." << endl;
    }
};

// 代理类
class DenDenMuShi : public Communication
{
public:
    DenDenMuShi()
    {
        m_isStart = true;
        m_speaker = new Speaker;
    }

    bool isStart()
    {
        return m_isStart;
    }

    void setStart(bool flag)
    {
        m_isStart = flag;
    }
    void communicate() override
    {
        if (m_isStart)
        {
            cout << "电话虫开始实时模仿通话者的语言和表情..." << endl;
            m_speaker->communicate();
        }
    }
    ~DenDenMuShi()
    {
        if (m_speaker != nullptr)
        {
            delete m_speaker;
        }
    }
private:
    bool m_isStart = false;
    Speaker* m_speaker = nullptr;
};

#if 0
int main()
{
    // 直接交流
    Communication* speaker = new Speaker;
    speaker->communicate();
    delete speaker;
    cout << "===================" << endl;
    // 通过电话虫交流
    speaker = new DenDenMuShi;
    speaker->communicate();
    delete speaker;

    return 0;
}
#endif