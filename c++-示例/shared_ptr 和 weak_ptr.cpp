#include <iostream>
#include <memory>

// 自定义删除器
void customDeleter(int* p) {
    std::cout << "自定义删除器释放资源: " << *p << std::endl;
    delete p;
}

struct Demo {
    Demo() { std::cout << "Demo 构造\n"; }
    ~Demo() { std::cout << "Demo 析构\n"; }
    void hello() { std::cout << "Hello from Demo\n"; }
};

struct Node; // 前向声明

struct Node {
    std::string name;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev; // 用 weak_ptr 防止循环引用
    Node(const std::string& n) : name(n) { std::cout << name << " 构造\n"; }
    ~Node() { std::cout << name << " 析构\n"; }
};

int main() {
    // 1. 创建 shared_ptr，管理单个对象
    std::shared_ptr<int> p1(new int(10));
    std::cout << "p1: " << *p1 << ", use_count: " << p1.use_count() << std::endl;

    // 2. 使用 make_shared（推荐）
    auto p2 = std::make_shared<Demo>();
    p2->hello();
    std::cout << "p2 use_count: " << p2.use_count() << std::endl;

    // 3. shared_ptr 管理数组（不推荐，推荐用 unique_ptr 管理数组）
    std::shared_ptr<int> arr(new int[3] {1, 2, 3}, [](int* p) { delete[] p; });
    std::cout << "arr[0]: " << arr.get()[0] << ", arr[1]: " << arr.get()[1] << std::endl;

    // 4. 自定义删除器
    std::shared_ptr<int> p3(new int(42), customDeleter);

    // 5. reset() 释放资源
    p1.reset();
    if (!p1) std::cout << "p1 已被释放\n";

    // 6. 拷贝和赋值（增加引用计数）
    auto p4 = std::make_shared<int>(100);
    std::shared_ptr<int> p5 = p4; // 拷贝
    std::cout << "p4 use_count: " << p4.use_count() << ", p5 use_count: " << p5.use_count() << std::endl;

    // 7. swap 交换两个 shared_ptr
    auto p6 = std::make_shared<int>(200);
    p5.swap(p6);
    std::cout << "p5: " << *p5 << ", p6: " << *p6 << std::endl;

    // 8. get() 获取原始指针（不推荐直接 delete）
    int* raw = p5.get();
    std::cout << "原始指针值: " << *raw << std::endl;

    // 9. use_count() 获取引用计数
    std::cout << "p5 use_count: " << p5.use_count() << std::endl;

    // 10. weak_ptr 解决循环引用
    {
        auto n1 = std::make_shared<Node>("n1");
        auto n2 = std::make_shared<Node>("n2");
        n1->next = n2;
        n2->prev = n1; // weak_ptr 不增加引用计数
        std::cout << "n1 use_count: " << n1.use_count() << ", n2 use_count: " << n2.use_count() << std::endl;
    } // 离开作用域，n1/n2 正常析构

    // 11. weak_ptr 基本用法
    std::shared_ptr<int> sp = std::make_shared<int>(123);
    std::weak_ptr<int> wp = sp;
    std::cout << "sp use_count: " << sp.use_count() << std::endl;
    if (auto locked = wp.lock()) {
        std::cout << "weak_ptr 成功访问到 shared_ptr，值为: " << *locked << std::endl;
    }
    sp.reset();
    if (wp.expired()) {
        std::cout << "weak_ptr 指向的对象已释放\n";
    }

    // 离开作用域时，所有 shared_ptr 自动释放资源
    return 0;
}