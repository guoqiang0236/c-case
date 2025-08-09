#include <iostream>
using namespace std;

// 产品类的父类 - 人造恶魔果实
class AbstractSmile
{
public:
    virtual void transform() = 0;
    virtual void ability() = 0;
    virtual ~AbstractSmile() {}
};

class SheepSmile : public AbstractSmile
{
public:
    void transform() override
    {
        cout << "变成人兽 -- 山羊人形态..." << endl;
    }
    void ability() override
    {
        cout << "将手臂变成绵羊角的招式 -- 巨羊角" << endl;
    }
};

class LionSmile : public AbstractSmile
{
public:
    void transform() override
    {
        cout << "变成人兽 -- 狮子人形态..." << endl;
    }
    void ability() override
    {
        cout << "火遁· 豪火球之术..." << endl;
    }
};

class BatSmile : public AbstractSmile
{
public:
    void transform() override
    {
        cout << "变成人兽 -- 蝙蝠人形态..." << endl;
    }
    void ability() override
    {
        cout << "声纳引箭之万剑归宗..." << endl;
    }
};

// 定义工厂类 - 父类
class AbstractFactory
{
public:
    virtual AbstractSmile* createSmile() = 0;
    virtual ~AbstractFactory() {}
};

// 生产山羊的恶魔果实
class SheepFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile()
    {
        return new SheepSmile;
    }
    ~SheepFactory() 
    {
        cout << "SheepFactory 被析构了..." << endl;
    }
};

// 生产狮子的恶魔果实
class LionFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile()
    {
        return new LionSmile;
    }
    ~LionFactory()
    {
        cout << "LionFactory 被析构了..." << endl;
    }
};

// 生产蝙蝠的恶魔果实
class BatFactory : public AbstractFactory
{
public:
    AbstractSmile* createSmile()
    {
        return new BatSmile;
    }
    ~BatFactory()
    {
        cout << "BatFactory 被析构了..." << endl;
    }
};

#if 0
int main()
{
    AbstractFactory* factory = new LionFactory;
    AbstractSmile* obj = factory->createSmile();
    obj->transform();
    obj->ability();
    delete obj;
    delete factory;

    return 0;
}
#endif