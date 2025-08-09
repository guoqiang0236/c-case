#include <iostream>
using namespace std;

// 战士的基类
class Soldier
{
public:
    Soldier() {}
    Soldier(string name) : m_name(name) {}
    string getName()
    {
        return m_name;
    }
    virtual void fight() = 0;
    virtual ~Soldier() {}
protected:
    string m_name = string();
};

// 黑胡子
class Teach : public Soldier
{
public:
    using Soldier::Soldier;
    void fight()
    {
        cout << m_name << "依靠惊人的力量和高超的体术战斗..." << endl;
    }
};

// 恶魔果实基类
class DevilFruit : public Soldier
{
public:
    void enchantment(Soldier* soldier)
    {
        m_soldier = soldier;
        m_name = soldier->getName();
    }
protected:
    Soldier* m_soldier = nullptr;
};

// 暗暗果实
class DarkFruit : public DevilFruit
{
public:
    void fight() override
    {
        m_soldier->fight();
        // 使用恶魔果实能力战斗
        cout << m_soldier->getName()
            << "吃了暗暗果实, 可以拥有黑洞一样的无限吸引力..." << endl;
        warning();
    }
private:
    void warning()
    {
        cout << m_soldier->getName()
            << "你要注意: 吃了暗暗果实, 身体元素化之后不能躲避攻击，会吸收所有伤害!" << endl;
    }
};
// 震震果实
class QuakeFruit : public DevilFruit
{
public:
    void fight() override
    {
        m_soldier->fight();
        // 使用恶魔果实能力战斗
        cout << m_soldier->getName()
            << "吃了震震果实, 可以在任意空间引发震动, 摧毁目标...!" << endl;
    }
};

// 大丙果实
class PieFruit : public DevilFruit
{
public:
    void fight() override
    {
        m_soldier->fight();
        // 使用恶魔果实能力战斗
        cout << m_soldier->getName()
            << "吃了大饼果实, 获得大饼铠甲...!" << endl;
        ability();
    }
    void ability()
    {
        cout << "最强辅助 -- 大饼果实可以将身边事物变成大饼, 帮助队友回血..." << endl;
    }
};

#if 0
int main()
{
    Soldier* soldier = new Teach;
    DevilFruit* dark = new DarkFruit;
    DevilFruit* quake = new QuakeFruit;
    DevilFruit* pie = new PieFruit;
    // 通过暗暗恶魔果实去装饰黑胡子
    dark->enchantment(soldier);
    // 通过震震恶魔果实去装饰黑胡子
    quake->enchantment(dark);
    // 通过暗暗恶魔果实去装饰黑胡子
    pie->enchantment(quake);
    pie->fight();

    delete soldier;
    delete dark;
    delete quake;
    delete pie;

    return 0;
}
#endif