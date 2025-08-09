#include <iostream>
using namespace std;

// 父类
class GermaSoldier
{
public:
    virtual GermaSoldier* clone() = 0;
    virtual string whoAmI() = 0;
    virtual ~GermaSoldier() {}
};

// 子类
class Soldier66 : public GermaSoldier
{
public:
    GermaSoldier* clone() override
    {
        return new Soldier66(*this);
    }
    string whoAmI() override
    {
        return "我是 Soldier66 的士兵!!!";
    }
};

class Soldier67 : public GermaSoldier
{
public:
    GermaSoldier* clone() override
    {
        return new Soldier67(*this);
    }
    string whoAmI() override
    {
        return "我是 Soldier67 的士兵!!!";
    }
};

#if 0
int main()
{
    GermaSoldier* obj = new Soldier66;
    GermaSoldier* soldier = obj->clone();
    cout << soldier->whoAmI();
    delete soldier;
    delete obj;

    obj = new Soldier67;
    soldier = obj->clone();
    cout << soldier->whoAmI();
    delete soldier;
    delete obj;

    return 0;
}
#endif