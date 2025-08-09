#include <iostream>
using namespace std;

// 抽象机器人类
class AbstractRobot
{
public:
    // 武器
    virtual void weapon() = 0;
    // 外观
    virtual void appearance() = 0;
    // 战斗能力
    virtual void fightAbility() = 0;
    // 名字
    virtual string getName() = 0;
    // 自愈能力
    virtual void selfHealing() {}
    // 是否能飞
    virtual bool canFlying()
    {
        return false;
    }
    // 是否可以自动控制
    virtual bool isAuto()
    {
        return true;
    }
    // 得到当前机器人的属性
    virtual void getProperty()
    {
        cout << "贝加庞克制造的" << getName() << "有以下属性: " << endl;
        if (canFlying())
        {
            cout << "有飞行能力..." << endl;
        }
        else
        {
            cout << "没有飞行能力..." << endl;
        }
        if (isAuto())
        {
            cout << "可以自动控制, 完全体机器人!" << endl;
        }
        else
        {
            cout << "不能自动控制, 半自动机器人!" << endl;
        }
        weapon();
        appearance();
        fightAbility();
        selfHealing();
    }
};

// 机器人子类1 - 和平主义者
class Pacifist : public AbstractRobot
{
public:
    // 武器
    void weapon() override
    {
        cout << "可以发射镭射光..." << endl;
    }
    // 外观
    void appearance() override
    {
        cout << "外部和巴索罗米·熊一样, 体型庞大，拥有呈半圆形的耳朵，内部似乎金属。" << endl;
    }
    // 战斗能力
    void fightAbility() override
    {
        cout << "结实抗揍, 可以通过手部或者嘴部发射镭射激光, 可以融化钢铁!!!" << endl;
    }
    // 名字
    string getName() override
    {
        return "和平主义者";
    }
};

// 机器人子类2 - 炽天使
class Angel : public AbstractRobot
{
public:
    // 武器
    void weapon() override
    {
        cout << "可以发射镭射激光, 鹰眼外形的炽天使携带者一把巨剑, 可以斩断一切!!!" << endl;
    }
    // 外观
    void appearance() override
    {
        cout << "外观和七武海小时候的外形一样, 并且拥有一对和烬一样的翅膀!!!" << endl;
    }
    // 战斗能力
    void fightAbility() override
    {
        cout << "不仅可以发射镭射激光, 还拥有七武海的能力, 牛逼plus, 无敌了!!!!" << endl;
    }
    // 名字
    string getName() override
    {
        return "炽天使";
    }
    // 自愈能力
    void selfHealing() override
    {
        cout << "非常厚实抗揍, 并且拥有非常强的自愈能力, 开挂了!!!" << endl;
    }
    bool canFlying() override
    {
        return true;
    }
};

#if 0
int main()
{
    AbstractRobot* robot = new Pacifist;
    robot->getProperty();
    delete robot;
    cout << "================" << endl;
    robot = new Angel;
    robot->getProperty();
    delete robot;
    return 0;
}
#endif