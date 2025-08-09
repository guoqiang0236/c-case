#pragma once
#include <string>
#include <list>
using namespace std;

class Observer;
// 发布者基类
class NewsAgency
{
public:
    // 添加订阅者
    void attach(Observer* ob);
    // 删除订阅者
    void detach(Observer* ob);
    // 通知订阅者
    virtual void notify(string msg) = 0;
    virtual ~NewsAgency() {}
protected:
    list<Observer*> m_list;
};

// 发布者子类 - 摩根斯
class Morgans : public NewsAgency
{
public:
    // 通知订阅者
    void notify(string msg) override;
};

// 发布者子类 - 八卦新闻社
class Gossip : public NewsAgency
{
public:
    // 通知订阅者
    void notify(string msg) override;
};