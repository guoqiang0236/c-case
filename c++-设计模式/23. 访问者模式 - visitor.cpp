#include "Visitor-23.h"
#include "Member-23.h"
#include <iostream>
#include <list>
#include <vector>
using namespace std;

void Anger::maleDoing(MaleMember* male)
{
    cout << "我是草帽海贼团的" << male->getName() << endl;
    fight();
}

void Anger::fight()
{
    cout << "只要还活着就得跟这家伙血战到底!!!" << endl;
}

void Anger::femaleDoing(FemaleMember* female)
{
    cout << "我是草帽海贼团的" << female->getName() << endl;
    warning();
}

void Anger::warning()
{
    cout << "大家块逃，我快顶不住了, 不要管我!!!" << endl;
}

void Horror::maleDoing(MaleMember* male)
{
    cout << "我是草帽海贼团的" << male->getName() << endl;
    thinking();
}

void Horror::thinking()
{
    cout << "得辅助同伴们一块攻击这个家伙, 不然根本打不过呀!!!" << endl;
}

void Horror::femaleDoing(FemaleMember* female)
{
    cout << "我是草帽海贼团的" << female->getName() << endl;
    help();
}

void Horror::help()
{
    cout << "这个大熊太厉害, 太可怕了, 快救救我。。。" << endl;
}

// 定义一个用于测试的类
class CaoMaoTeam
{
public:
    CaoMaoTeam()
    {
        m_actions.push_back(new Anger);
        m_actions.push_back(new Horror);
    }
    void add(AbstractMember* member)
    {
        m_members.push_back(member);
    }
    void remove(AbstractMember* member)
    {
        m_members.remove(member);
    }
    void display()
    {
        for (const auto& item : m_members)
        {
            int index = rand() % 2;
            item->accept(m_actions.at(index));
        }
    }
    ~CaoMaoTeam()
    {
        for (const auto& item : m_members)
        {
            delete item;
        }
        for (const auto& item : m_actions)
        {
            delete item;
        }
    }
private:
    list<AbstractMember*> m_members;
    vector<AbstractAction*> m_actions;
};

int main()
{
    srand(time(NULL));
    vector<string> names{
    "路飞", "索隆","山治", "乔巴", "弗兰奇", "乌索普", "布鲁克"
    };
    CaoMaoTeam* team = new CaoMaoTeam;
    for (const auto& item : names)
    {
        team->add(new MaleMember(item));
    }
    team->add(new FemaleMember("娜美"));
    team->add(new FemaleMember("罗宾"));

    team->display();

    delete team;

    return 0;
}

