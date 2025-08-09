#include "NewsAgency-19.h"
#include "Observer-19.h"
#include <iostream>
using namespace std;

void NewsAgency::attach(Observer* ob)
{
    m_list.push_back(ob);
}

void NewsAgency::detach(Observer* ob)
{
    m_list.remove(ob);
}

void Morgans::notify(string msg)
{
    cout << "摩根斯新闻社报纸的订阅者一共有<" << m_list.size() << ">人" << endl;
    for (const auto& item : m_list)
    {
        // 通过观察者更新数据
        item->update(msg);
    }
}

void Gossip::notify(string msg)
{
    cout << "八卦新闻社报纸的订阅者一共有<" << m_list.size() << ">人" << endl;
    for (const auto& item : m_list)
    {
        // 通过观察者更新数据
        item->update(msg);
    }
}
