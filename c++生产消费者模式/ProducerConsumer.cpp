#include "ProducerConsumer.h"
#include <iostream>
#include <chrono>

ProducerConsumer::ProducerConsumer()
    : m_running(false) {
}

ProducerConsumer::~ProducerConsumer() {
    Stop();
}

void ProducerConsumer::Start() {
    if (m_running) {
        return;
    }

    m_running = true;
    m_producerThread = std::thread([this]() {
		ProducerThread();
        });
    m_consumerThread = std::thread([this]() {
		ConsumerThread();
        });
}

void ProducerConsumer::Stop() {
    if (!m_running) {
        return;
    }

    m_running = false;
    m_condVar.notify_all(); // 唤醒所有等待的线程

    if (m_producerThread.joinable()) {
        m_producerThread.join();
    }

    if (m_consumerThread.joinable()) {
        m_consumerThread.join();
    }
}

void ProducerConsumer::ProducerThread() {
    int data = 0;

    while (m_running) {
        std::unique_lock<std::mutex> lock(m_mutex);

        // 等待队列有空间
        m_condVar.wait(lock, [this]() {
            return !m_running || m_dataQueue.size() < MAX_QUEUE_SIZE;
            });

        if (!m_running) {
            break;
        }

        // 生产数据
        m_dataQueue.push_back(data);
        std::cout << "生产数据: " << data << ", 队列大小: " << m_dataQueue.size() << std::endl;
        data++;

        lock.unlock();
        m_condVar.notify_one(); // 通知消费者

        // 模拟生产耗时
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void ProducerConsumer::ConsumerThread() {
    while (m_running) {
        std::unique_lock<std::mutex> lock(m_mutex);

        // 等待队列有数据
        m_condVar.wait(lock, [this]() {
            return !m_running || !m_dataQueue.empty();
            });

        if (!m_running && m_dataQueue.empty()) {
            break;
        }

        if (!m_dataQueue.empty()) {
            // 消费数据
            int data = m_dataQueue.front();
            m_dataQueue.pop_front();
            std::cout << "消费数据: " << data << ", 队列大小: " << m_dataQueue.size() << std::endl;

            lock.unlock();
            m_condVar.notify_one(); // 通知生产者

            // 模拟消费耗时
           std::this_thread::sleep_for(std::chrono::milliseconds(120));
        }
    }
}