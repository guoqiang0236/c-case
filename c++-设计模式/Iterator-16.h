#pragma once
#include "MyList-16.h"
// 定义抽象的迭代器类
class Iterator
{
public:
    Iterator(MyList* list) : m_list(list) {}
    Node* current()
    {
        return m_current;
    }
    virtual Node* first() = 0;
    virtual Node* next() = 0;
    virtual bool isDone() = 0;
protected:
    MyList* m_list = nullptr;
    Node* m_current = nullptr;
};

// 正向遍历
class ForwardIterator : public Iterator
{
public:
    using Iterator::Iterator;
    Node* first() override
    {
        m_current = m_list->head();
        return m_current;
    }
    Node* next() override
    {
        m_current = m_current->next;
        return m_current;
    }
    bool isDone() override
    {
        return m_current == m_list->tail()->next;
    }
};

// 逆向遍历
class ReverseIterator : public Iterator
{
public:
    using Iterator::Iterator;
    Node* first() override
    {
        m_current = m_list->tail();
        return m_current;
    }
    Node* next() override
    {
        m_current = m_current->prev;
        return m_current;
    }
    bool isDone() override
    {
        return m_current == m_list->head()->prev;
    }
};
