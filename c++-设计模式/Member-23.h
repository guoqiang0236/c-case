#pragma once
#include <iostream>
#include "Visitor-23.h"
using namespace std;

// 成员类的基类 
class AbstractMember
{
public:
    AbstractMember(string name) : m_name(name) {}
    string getName()
    {
        return m_name;
    }
    virtual void accept(AbstractAction* action) = 0;
    virtual ~AbstractMember() {}
protected:
    string m_name;
};

// 男性子类
class MaleMember : public AbstractMember
{
public:
    using AbstractMember::AbstractMember;
    void accept(AbstractAction* action) override
    {
        action->maleDoing(this);
    }
};

// 女性子类
class FemaleMember : public AbstractMember
{
public:
    using AbstractMember::AbstractMember;
    void accept(AbstractAction* action) override
    {
        action->femaleDoing(this);
    }
};