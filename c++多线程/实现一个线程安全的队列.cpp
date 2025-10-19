#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
public:
	ThreadSafeQueue() = default;
	ThreadSafeQueue(const ThreadSafeQueue&) = delete;
	ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
private:
	std::queue<T> m_queue;
	mutable std::mutex m_mutex;
	std::condition_variable m_condvar;
public:
	void enqueue(T value) {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_queue.push(std::move(value));
		m_condvar.notify_one();
    }
	T dequeue() {
		std::unique_lock<std::mutex>lock(m_mutex);
		m_condvar.wait(lock, [this]() { return !m_queue.empty(); });
		T value = std::move(m_queue.front());
		m_queue.pop();
		return value;
	}
};
#include <iostream>
#include <thread>
#include <chrono>
int main() {
	ThreadSafeQueue<int> tsQueue;
	tsQueue.enqueue(42);
	int value = tsQueue.dequeue();
	// 1. 线程创建并立即开始执行 ⚡
	std::thread producer([&tsQueue]() {
		for (int i = 0; i < 10000; i++) {
			tsQueue.enqueue(i);
			std::cout << "生产了: " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		});  // ← 执行到这里,producer 线程就已经在后台运行了!

	std::thread consumer([&tsQueue]() {
		for (int i = 0; i < 10000; i++) {
			int value = tsQueue.dequeue();
			std::cout << "消费了: " << value << std::endl;
		}
		});  // ← 执行到这里,consumer 线程也已经在后台运行了!

	// 2. 主线程执行到这里,两个子线程已经在并发执行了
	producer.join();  // ← 等待 producer 线程完成(阻塞主线程)
	consumer.join();  // ← 等待 consumer 线程完成(阻塞主线程)
	system("pause");
	return 0;
}
