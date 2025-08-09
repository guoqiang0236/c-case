#include <iostream>
using namespace std;

// 抽象的策略类
class AbstractStrategy
{
public:
    virtual void fight(bool isfar = false) = 0;
    virtual ~AbstractStrategy() {}
};

// 一档
class YiDang : public AbstractStrategy
{
public:
    void fight(bool isfar = false) override
    {
        cout << "*** 现在使用的是一档: ";
        if (isfar)
        {
            cout << "橡胶机关枪" << endl;
        }
        else
        {
            cout << "橡胶·攻城炮" << endl;
        }
    }
};

// 2档
class ErDang : public AbstractStrategy
{
public:
    void fight(bool isfar = false) override
    {
        cout << "*** 现在使用的是2档: ";
        if (isfar)
        {
            cout << "橡胶Jet火箭" << endl;
        }
        else
        {
            cout << "橡胶Jet·铳乱打" << endl;
        }
    }
};

// 3档
class SanDang : public AbstractStrategy
{
public:
    void fight(bool isfar = false) override
    {
        cout << "*** 现在使用的是3档: ";
        if (isfar)
        {
            cout << "橡胶巨人回旋弹" << endl;
        }
        else
        {
            cout << "橡胶巨人战斧" << endl;
        }
    }
};

// 4档
class SiDang : public AbstractStrategy
{
public:
    void fight(bool isfar = false) override
    {
        cout << "*** 现在使用的是4档: ";
        if (isfar)
        {
            cout << "橡胶狮子火箭炮" << endl;
        }
        else
        {
            cout << "橡胶犀牛榴弹炮" << endl;
        }
    }
};

// 5档
class WuDang : public AbstractStrategy
{
public:
    void fight(bool isfar = false) override
    {
        cout << "*** 切换成五挡: 变成尼卡形态可以把物体变成橡胶, 并任意改变物体的形态对其进行攻击!!!" << endl;
    }
};

// 路飞类
enum class Level:char{Easy, Normal, Hard, Experts, Professional};
class Luffy
{
public:
    void fight(Level level, bool isfar = false)
    {
        if (m_strategy != nullptr)
        {
            delete m_strategy;
            m_strategy = nullptr;
        }
        switch (level)
        {
        case Level::Easy:
            m_strategy = new YiDang;
            break;
        case Level::Normal:
            m_strategy = new ErDang;
            break;
        case Level::Hard:
            m_strategy = new SanDang;
            break;
        case Level::Experts:
            m_strategy = new SiDang;
            break;
        case Level::Professional:
            m_strategy = new WuDang;
            break;
        default:
            break;
        }
        m_strategy->fight(isfar);
    }

    ~Luffy()
    {
        if (m_strategy != nullptr)
        {
            delete m_strategy;
        }
    }
private:
    AbstractStrategy* m_strategy = nullptr;
};

#if 0
int main()
{
    Luffy* luffy = new Luffy;
    cout << "--- 在香波地群岛遇到了海军士兵: " << endl;
    luffy->fight(Level::Easy);
    cout << "--- 在魔谷镇遇到了贝拉米: " << endl;
    luffy->fight(Level::Normal);
    cout << "--- 在司法岛遇到了罗布·路奇: " << endl;
    luffy->fight(Level::Hard);
    cout << "--- 在德雷斯罗萨遇到了多弗朗明哥: " << endl;
    luffy->fight(Level::Experts);
    cout << "--- 在鬼岛遇到了凯多: " << endl;
    luffy->fight(Level::Professional);
    delete luffy;
    return 0;
}
#endif