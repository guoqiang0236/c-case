/*
 * ���ģʽѧϰ����������ģʽ��Adapter Pattern��
 * -------------------------------------------------
 * ������ģʽ��һ�ֽṹ�����ģʽ����Ҫ���ڽ���ӿڲ����ݵ����⡣
 * ��ͨ������һ���������࣬��һ����Ľӿ�ת���ɿͻ�����������һ���ӿڣ�ʹԭ�����ڽӿڲ�ƥ����޷�һ���������ܹ�Эͬ������
 * ������ģʽ��Ϊ���������Ͷ�������������ʵ�ַ�ʽ��
 * ��ʾ���ֱ���ʾ�������ַ�ʽ��
 * 1. ����������OutletAdapter����ͨ�����ؼ̳�ʵ�ֽӿ�ת����
 * 2. ������������OutletObjAdapter����ͨ����Ϸ�ʽʵ�ֽӿ�ת����
 */

#include <iostream>
using namespace std;

// �������ӿڣ��ṩ���幦��
class ThreePauseOutlet
{
public:
    void doThreePause() {
        cout << "ThreePauseOutlet::doThreePause()" << endl;
    }
};

// ����������ӿڣ�����ͳһ���뷽��
class TwoPauseOutlet
{
public:
    virtual void doPlug() = 0;
};

// ����������ͨ�����ؼ̳�ʵ�ֽӿ�����
class OutletAdapter : public TwoPauseOutlet, public ThreePauseOutlet
{
    void doPlug() override {
        doCovertor();      // ת�����߼�
        doThreePause();    // ��������������
    }

    void doCovertor() {
        std::cout << "�������ڽ�����ͷת��������ͷ" << std::endl;
    }
};

// ������������ͨ����Ϸ�ʽʵ�ֽӿ�����
class OutletObjAdapter : public TwoPauseOutlet
{
public:
    // ���캯������������������
    OutletObjAdapter(ThreePauseOutlet* obj) :m_pOutlet(obj)
    {

    }

    void doPlug() override {
        doCovertor();           // ת�����߼�
        m_pOutlet->doThreePause(); // ��������������
    }
private:
    void doCovertor() {
        std::cout << "�������ڽ�����ͷת��������ͷ" << std::endl;
    }
    ThreePauseOutlet* m_pOutlet; // ��������������ָ��
};

int main() {
    // ʹ����������
    TwoPauseOutlet* testoutlet = new OutletAdapter();
    testoutlet->doPlug();

    // ʹ�ö���������
    OutletObjAdapter* testoutletobj = new OutletObjAdapter(new ThreePauseOutlet());
    testoutletobj->doPlug();
    system("pause");
    return 0;
}