#include <iostream>
#include <thread>
#include <windows.h>

HANDLE event_a, event_b, event_c, event_d;
int count = 1000;

void print_a() {
    for (int i = 0; i < count; ++i) {
        WaitForSingleObject(event_a, INFINITE);
        std::cout << "a";
        ReleaseSemaphore(event_b, 1, NULL);
    }
}

void print_b() {
    for (int i = 0; i < count; ++i) {
        WaitForSingleObject(event_b, INFINITE);
        std::cout << "b";
        ReleaseSemaphore(event_c, 1, NULL);
    }
}

void print_c() {
    for (int i = 0; i < count; ++i) {
        WaitForSingleObject(event_c, INFINITE);
        std::cout << "c";
        ReleaseSemaphore(event_d, 1, NULL);
    }
}

void print_d() {
    for (int i = 0; i < count; ++i) {
        WaitForSingleObject(event_d, INFINITE);
        std::cout << "d ";
        ReleaseSemaphore(event_a,1, NULL);
        Sleep(100);
    }
}

int main() {
    // 把 event_a 当作计数信号量，初始计数 6，最大计数也设为 6
    event_a = CreateSemaphore(NULL, 6, 6, NULL);
    // 其它信号量初始为 0，最大计数设为 count（或其它合适上限）
    event_b = CreateSemaphore(NULL, 0, count, NULL);
    event_c = CreateSemaphore(NULL, 0, count, NULL);
    event_d = CreateSemaphore(NULL, 0, count, NULL);

    std::thread t1(print_a);
    std::thread t2(print_b);
    std::thread t3(print_c);
    std::thread t4(print_d);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    CloseHandle(event_a);
    CloseHandle(event_b);
    CloseHandle(event_c);
    CloseHandle(event_d);

    return 0;
}