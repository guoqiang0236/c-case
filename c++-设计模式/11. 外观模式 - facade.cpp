#include <iostream>
using namespace std;

// 乐可系统
class CokeSystem
{
public:
    void imitCoke()
    {
        cout << "狮吼炮原料<可乐>已经注入完毕..." << endl;
    }
};

// 能量转换系统
class EnergySystem
{
public:
    void energyCovert()
    {
        cout << "已经将所有的可乐转换为了能量..." << endl;
    }
};

// 目标锁定系统
class AimLockSystem
{
public:
    void aimLock()
    {
        cout << "已经瞄准并且锁定了目标..." << endl;
    }
};

// 加农炮发射系统
class Cannon
{
public:
    void cannonFire()
    {
        cout << "狮吼炮正在向目标开火..." << endl;
    }
};

// 风来炮稳定系统
class WindCannon
{
public:
    void windCannonFire()
    {
        cout << "发射风来炮抵消后坐力稳定船身..." << endl;
    }
};

// 狮吼炮类
class LionCannon
{
public:
    LionCannon()
    {
        m_coke = new CokeSystem;
        m_energy = new EnergySystem;
        m_aimlock = new AimLockSystem;
        m_cannon = new Cannon;
        m_windCannon = new WindCannon;
    }
    ~LionCannon()
    {
        delete m_coke;
        delete m_energy;
        delete m_aimlock;
        delete m_cannon;
        delete m_windCannon;
    }
    // 瞄准和锁定
    void aimAndLock()
    {
        m_coke->imitCoke();
        m_energy->energyCovert();
        m_aimlock->aimLock();
    }
    // 开火
    void fire()
    {
        m_cannon->cannonFire();
        m_windCannon->windCannonFire();
    }
private:
    CokeSystem* m_coke = nullptr;
    EnergySystem* m_energy = nullptr;
    AimLockSystem* m_aimlock = nullptr;
    Cannon* m_cannon = nullptr;
    WindCannon* m_windCannon = nullptr;
};

#if 0
int main()
{
    LionCannon* lion = new LionCannon;
    lion->aimAndLock();
    lion->fire();
    delete lion;
    return 0;
}
#endif