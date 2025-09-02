#include<iostream>
using namespace std;

// ����ͷ�࣬��ʾһ������ͷ�豸
class Camera
{
public:
    // ������ͷ
    void turnon() {
        cout << "Camera is on" << endl;
    };
    // �ر�����ͷ
    void turnoff() {
        cout << "Camera is off" << endl;
    };
};

// �ƹ��࣬��ʾһ���ƹ��豸
class Light
{
public:
    // �򿪵ƹ�
    void turnon() {
        cout << "Light is on" << endl;
    };
    // �رյƹ�
    void turnoff() {
        cout << "Light is off" << endl;
    };
};

// �������࣬��ʾһ���������豸
class Sensor
{
public:
    // �������
    void active() {
        cout << "Sensor is active" << endl;
    };
    // �رմ�����
    void deactive() {
        cout << "Sensor is deactive" << endl;
    };
};

// �������࣬��ʾһ�������豸
class Alarm
{
public:
    // �������
    void active() {
        cout << "Alarm is active" << endl;
    };
    // �رվ�����
    void deactive() {
        cout << "Alarm is deactive" << endl;
    };
};

// ����ϵͳ�����࣬ͳһ���������豸
class SecuritFacade
{
public:
    // ���캯������ʼ��������ϵͳ
    SecuritFacade() {
        m_pCamera = new Camera();
        m_pLight = new Light();
        m_pSensor = new Sensor();
        m_pAlarm = new Alarm();
    }
    // �����������ͷŸ�����ϵͳ��Դ
    ~SecuritFacade() {
        if (m_pCamera)
        {
            delete m_pCamera;
            m_pCamera = nullptr;
        }
        if (m_pLight)
        {
            delete m_pLight;
            m_pLight = nullptr;
        }
        if (m_pSensor)
        {
            delete m_pSensor;
            m_pSensor = nullptr;
        }
        if (m_pAlarm)
        {
            delete m_pAlarm;
            m_pAlarm = nullptr;
        }
    }
    // ���������豸
    void active()
    {
        cout << "�����豸" << endl;
        m_pCamera->turnon();
        m_pLight->turnon();
        m_pSensor->active();
        m_pAlarm->active();
    }
    // �ر������豸
    void deactive()
    {
        cout << "�ر��豸" << endl;
        m_pCamera->turnoff();
        m_pLight->turnoff();
        m_pSensor->deactive();
        m_pAlarm->deactive();
    }
private:
    Camera* m_pCamera; // ����ͷָ��
    Light* m_pLight;  // �ƹ�ָ��
    Sensor* m_pSensor; // ������ָ��
    Alarm* m_pAlarm;  // ������ָ��
};

int main() {
    // ��ͳ��ʽ���ֱ����ÿ���豸����ע�ͣ�
    /*
    Camera* pCamera = new Camera();
    Light* pLight =   new Light();
    Sensor* pSensor = new Sensor();
    Alarm* pAlarm =   new Alarm();

    cout << "�����豸" << endl;
    pCamera->turnon();
    pLight->turnon();
    pSensor->active();
    pAlarm->active();

    cout << "�ر��豸" << endl;
    pCamera->turnoff();
    pLight->turnoff();
    pSensor->deactive();
    pAlarm->deactive();
    */

    // ʹ������ģʽ��ͳһ���������豸
    SecuritFacade* pSecuritFacade = new SecuritFacade();
    pSecuritFacade->active();
    pSecuritFacade->deactive();

    system("pause");
    return 0;
};