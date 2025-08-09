#pragma once

class SanJi;
// 状态类的基类
class AbstractState
{
public:
    virtual void working(SanJi* sanji) = 0;
    virtual ~AbstractState() {}
};

// 上午状态
class ForenoonState : public AbstractState
{
public:
    void working(SanJi* sanji) override;
};

// 中午状态
class NoonState : public AbstractState
{
public:
    void working(SanJi* sanji) override;
};

//下午状态
class AfternoonState : public AbstractState
{
public:
    void working(SanJi* sanji) override;
};

// 晚上状态
class EveningState : public AbstractState
{
public:
    void working(SanJi* sanji) override;
};