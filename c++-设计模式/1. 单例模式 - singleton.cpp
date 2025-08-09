#include <iostream>
#include <mutex>
#include <atomic>
#include <queue>
#include <thread>
using namespace std;

#if 0
// 饿汉模式 -> 定义类的时候创建单例对象
// 定义一个单例模式的任务队列
class TaskQueue
{
public:
    TaskQueue(const TaskQueue & t) = delete;
    TaskQueue& operator=(const TaskQueue& t) = delete;
    static TaskQueue* getInstance()
    {
        return m_taskQ;
    }

    void print()
    {
        cout << "我是单例对象的一个成员函数..." << endl;
    }

private:
    TaskQueue() = default;
    // TaskQueue(const TaskQueue& t) = default;
    // TaskQueue& operator=(const TaskQueue& t) = default;
    // 只能通过类名访问静态属性或方法
    static TaskQueue* m_taskQ;
};
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;
#endif

#if 0
// 懒汉模式 -> 什么时候使用这个单例对象, 在使用的时候再去创建对应的实例
// 使用双重检查锁定 + 原子变量解决线程安全问题
class TaskQueue
{
public:
    TaskQueue(const TaskQueue& t) = delete;
    TaskQueue& operator=(const TaskQueue& t) = delete;
    static TaskQueue* getInstance()
    {
        TaskQueue* task = m_taskQ.load();
        if (task == nullptr)
        {
            m_mutex.lock();
            task = m_taskQ.load();
            if (task == nullptr)
            {
                task = new TaskQueue;
                m_taskQ.store(task);
            }
            m_mutex.unlock();
        }
        return task;
    }

    void print()
    {
        cout << "我是单例对象的一个成员函数..." << endl;
    }

private:
    TaskQueue() = default;
    // TaskQueue(const TaskQueue& t) = default;
    // TaskQueue& operator=(const TaskQueue& t) = default;
    // 只能通过类名访问静态属性或方法
    // static TaskQueue* m_taskQ;
    static mutex m_mutex;
    static atomic<TaskQueue*> m_taskQ;
};
// TaskQueue* TaskQueue::m_taskQ = nullptr;
atomic<TaskQueue*> TaskQueue::m_taskQ;
mutex TaskQueue::m_mutex;
#endif

#if 0
// 懒汉模式 -> 什么时候使用这个单例对象, 在使用的时候再去创建对应的实例
// 使用静态的局部对象解决线程安全问题 - > 编译器必须支持c++11
class TaskQueue
{
public:
    TaskQueue(const TaskQueue& t) = delete;
    TaskQueue& operator=(const TaskQueue& t) = delete;
    static TaskQueue* getInstance()
    {
        static TaskQueue task;
        return &task;
    }

    void print()
    {
        cout << "我是单例对象的一个成员函数..." << endl;
    }

private:
    TaskQueue() = default;
    // TaskQueue(const TaskQueue& t) = default;
    // TaskQueue& operator=(const TaskQueue& t) = default;
};
#endif

#if 1
// 替巴基写一个任务队列
class TaskQueue
{
public:
    TaskQueue(const TaskQueue& t) = delete;
    TaskQueue& operator=(const TaskQueue& t) = delete;
    static TaskQueue* getInstance()
    {
        return m_taskQ;
    }

    void print()
    {
        cout << "我是单例对象的一个成员函数..." << endl;
    }

    // 判断任务队列是否为空
    bool isEmpty()
    {
        lock_guard<mutex> locker(m_mutex);
        bool flag = m_data.empty();
        return flag;
    }
    // 添加任务
    void addTask(int node)
    {
        lock_guard<mutex> locker(m_mutex);
        m_data.push(node);
    }
    // 删除任务
    bool popTask()
    {
        lock_guard<mutex> locker(m_mutex);
        if (m_data.empty())
        {
            return false;
        }
        m_data.pop();
        return true;
    }
    // 取出一个任务(不删除任务)
    int takeTask()
    {
        lock_guard<mutex> locker(m_mutex);
        if (m_data.empty())
        {
            return -1;
        }
        int data = m_data.front();
        return data;
    }

private:
    TaskQueue() = default;
    // TaskQueue(const TaskQueue& t) = default;
    // TaskQueue& operator=(const TaskQueue& t) = default;
    // 只能通过类名访问静态属性或方法
    static TaskQueue* m_taskQ;
    // 定义任务队列
    queue<int> m_data;
    mutex m_mutex;
};
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;
#endif

#if 0
int main()
{
    TaskQueue* taskQ = TaskQueue::getInstance();
    
    // 生产者
    thread t1([=]()
        {
            for (int i = 0; i < 10; ++i)
            {
                taskQ->addTask(i + 100);
                cout << "+++ push data: " << i + 100 << ", threadID: " <<
                    this_thread::get_id() << endl;
                this_thread::sleep_for(chrono::milliseconds(500));
            }
        });

    // 消费者
    thread t2([=]()
        {
            this_thread::sleep_for(chrono::milliseconds(100));
            while(!taskQ->isEmpty())
            {
                int num = taskQ->takeTask();
                cout << "+++ take data: " << num << ", threadID: " <<
                    this_thread::get_id() << endl;
                taskQ->popTask();
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
        });

    t1.join();
    t2.join();

    return 0;
}
#endif