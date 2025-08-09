#pragma once
#include <string>
using namespace std;

// 类声明
class Iterator;
// 定义一个节点
struct Node
{
    Node(string n) :name(n) {}
    string name = string();
    Node* next = nullptr;
    Node* prev = nullptr;
};

// 定义双向链表
class MyList
{
public:
    inline int getCount()
    {
        return m_count;
    }
    inline Node* head()
    {
        return m_head;
    }
    inline Node* tail()
    {
        return m_tail;
    }
    Node* insert(Node* node, string name);
    Node* pushFront(string name);
    Node* pushBack(string name);
    Iterator* getIterator(bool isReverse = true);
private:
    Node* m_head = nullptr;
    Node* m_tail = nullptr;
    int m_count = 0;
};