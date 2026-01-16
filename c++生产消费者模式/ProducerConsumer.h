#pragma once
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

class ProducerConsumer {
public:
    ProducerConsumer();
    ~ProducerConsumer();

    // 启动生产者和消费者线程
    void Start();

    // 停止生产者和消费者线程
    void Stop();

private:
    // 生产者线程函数
    void ProducerThread();

    // 消费者线程函数
    void ConsumerThread();

    std::list<int> m_dataQueue;           // 数据队列
    std::mutex m_mutex;                    // 互斥锁
    std::condition_variable m_condVar;     // 条件变量
    std::atomic<bool> m_running;           // 运行状态标志

    std::thread m_producerThread;          // 生产者线程
    std::thread m_consumerThread;          // 消费者线程

    static const size_t MAX_QUEUE_SIZE = 10; // 队列最大长度
};