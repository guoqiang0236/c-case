#include <iostream>
#include <thread>
#include <windows.h>

HANDLE event_a, event_b, event_c, event_d;
int count = 1000;

void print_a() {
    for (int i = 0; i < count; ++i) {
        WaitForSingleObject(event_a, INFINITE);
        std::cout << "a";
        SetEvent(event_b);
    }
}

void print_b() {
    for (int i = 0; i < count; ++i) {
        WaitForSingleObject(event_b, INFINITE);
        std::cout << "b";
        SetEvent(event_c);
    }
}

void print_c() {
    for (int i = 0; i < count; ++i) {
        WaitForSingleObject(event_c, INFINITE);
        std::cout << "c";
        SetEvent(event_d);
    }
}

void print_d() {
    for (int i = 0; i < count; ++i) {
        WaitForSingleObject(event_d, INFINITE);
        std::cout << "d ";
        SetEvent(event_a);
        Sleep(100);
    }
}

int main() {
    event_a = CreateEvent(NULL, FALSE, TRUE, NULL);  // ³õÊ¼ÓÐÐÅºÅ
    event_b = CreateEvent(NULL, FALSE, FALSE, NULL);
    event_c = CreateEvent(NULL, FALSE, FALSE, NULL);
    event_d = CreateEvent(NULL, FALSE, FALSE, NULL);

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