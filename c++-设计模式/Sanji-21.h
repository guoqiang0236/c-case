#pragma once
#include "State-21.h"

class SanJi
{
public:
    SanJi()
    {
        m_state = new ForenoonState;
    }
    // 工作函数
    void working()
    {
        m_state->working(this);
    }

    // 切换状态
    void setState(AbstractState* state)
    {
        if (m_state != nullptr)
        {
            delete m_state;
            m_state = nullptr;
        }
        m_state = state;
    }

    int getClock()
    {
        return m_clock;
    }

    void setClock(int clock)
    {
        m_clock = clock;
    }
private:
    int m_clock = 0;    // 当前时间点
    AbstractState* m_state = nullptr;
};