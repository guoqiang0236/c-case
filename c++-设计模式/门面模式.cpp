#include<iostream>
using namespace std;

// 摄像头类，表示一个摄像头设备
class Camera
{
public:
    // 打开摄像头
    void turnon() {
        cout << "Camera is on" << endl;
    };
    // 关闭摄像头
    void turnoff() {
        cout << "Camera is off" << endl;
    };
};

// 灯光类，表示一个灯光设备
class Light
{
public:
    // 打开灯光
    void turnon() {
        cout << "Light is on" << endl;
    };
    // 关闭灯光
    void turnoff() {
        cout << "Light is off" << endl;
    };
};

// 传感器类，表示一个传感器设备
class Sensor
{
public:
    // 激活传感器
    void active() {
        cout << "Sensor is active" << endl;
    };
    // 关闭传感器
    void deactive() {
        cout << "Sensor is deactive" << endl;
    };
};

// 警报器类，表示一个警报设备
class Alarm
{
public:
    // 激活警报器
    void active() {
        cout << "Alarm is active" << endl;
    };
    // 关闭警报器
    void deactive() {
        cout << "Alarm is deactive" << endl;
    };
};

// 安防系统门面类，统一管理所有设备
class SecuritFacade
{
public:
    // 构造函数，初始化各个子系统
    SecuritFacade() {
        m_pCamera = new Camera();
        m_pLight = new Light();
        m_pSensor = new Sensor();
        m_pAlarm = new Alarm();
    }
    // 析构函数，释放各个子系统资源
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
    // 启动所有设备
    void active()
    {
        cout << "启动设备" << endl;
        m_pCamera->turnon();
        m_pLight->turnon();
        m_pSensor->active();
        m_pAlarm->active();
    }
    // 关闭所有设备
    void deactive()
    {
        cout << "关闭设备" << endl;
        m_pCamera->turnoff();
        m_pLight->turnoff();
        m_pSensor->deactive();
        m_pAlarm->deactive();
    }
private:
    Camera* m_pCamera; // 摄像头指针
    Light* m_pLight;  // 灯光指针
    Sensor* m_pSensor; // 传感器指针
    Alarm* m_pAlarm;  // 警报器指针
};

int main() {
    // 传统方式，分别操作每个设备（已注释）
    /*
    Camera* pCamera = new Camera();
    Light* pLight =   new Light();
    Sensor* pSensor = new Sensor();
    Alarm* pAlarm =   new Alarm();

    cout << "启动设备" << endl;
    pCamera->turnon();
    pLight->turnon();
    pSensor->active();
    pAlarm->active();

    cout << "关闭设备" << endl;
    pCamera->turnoff();
    pLight->turnoff();
    pSensor->deactive();
    pAlarm->deactive();
    */

    // 使用门面模式，统一操作所有设备
    SecuritFacade* pSecuritFacade = new SecuritFacade();
    pSecuritFacade->active();
    pSecuritFacade->deactive();

    system("pause");
    return 0;
};