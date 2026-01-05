#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

// C++14 信号量实现
class Semaphore {
public:
    Semaphore(int count = 0) : count_(count) {}

    void wait() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [&] { return count_ > 0; });
        --count_;
    }

    void post() {
        std::unique_lock<std::mutex> lock(mtx_);
        ++count_;
        cv_.notify_one();
    }

private:
    std::mutex mtx_;
    std::condition_variable cv_;
    int count_;
};

// 定义四个信号量，分别控制a、b、c、d线程
Semaphore sem_a(1), sem_b(0), sem_c(0), sem_d(0);

void print_a() {
    for (int i = 0; i < 5; ++i) {
        sem_a.wait();
        std::cout << "a";
        sem_b.post();
    }
}

void print_b() {
    for (int i = 0; i < 5; ++i) {
        sem_b.wait();
        std::cout << "b";
        sem_c.post();
    }
}

void print_c() {
    for (int i = 0; i < 5; ++i) {
        sem_c.wait();
        std::cout << "c";
        sem_d.post();
    }
}

void print_d() {
    for (int i = 0; i < 5; ++i) {
        sem_d.wait();
        std::cout << "d ";
        sem_a.post();
    }
}

int main() {
    std::thread t1(print_a);
    std::thread t2(print_b);
    std::thread t3(print_c);
    std::thread t4(print_d);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}