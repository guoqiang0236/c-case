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

int main() {
    // 1. 创建 unique_ptr，管理单个对象
    std::unique_ptr<int> p1(new int(10));
    std::cout << "p1: " << *p1 << std::endl;

    // 2. 使用 make_unique（推荐，C++14及以上）
    auto p2 = std::make_unique<Demo>();
    p2->hello();

    // 3. unique_ptr 管理数组
    std::unique_ptr<int[]> arr(new int[3] {1, 2, 3});
    std::cout << "arr[0]: " << arr[0] << ", arr[1]: " << arr[1] << std::endl;

    // 4. 自定义删除器
    std::unique_ptr<int, void(*)(int*)> p3(new int(42), customDeleter);

    // 5. 释放资源（reset 或离开作用域自动释放）
    p1.reset(); // 手动释放 p1 管理的资源
    if (!p1) std::cout << "p1 已被释放\n";

    // 6. 转移所有权
    auto p4 = std::make_unique<int>(100);
    std::unique_ptr<int> p5 = std::move(p4); // p4 资源转移给 p5
    if (!p4) std::cout << "p4 已无所有权\n";
    std::cout << "p5: " << *p5 << std::endl;

    // 7. get() 获取原始指针（不推荐直接 delete）
    int* raw = p5.get();
    std::cout << "原始指针值: " << *raw << std::endl;

    // 8. release() 释放所有权但不删除对象（需手动 delete）
    int* released = p5.release();
    if (!p5) std::cout << "p5 已 release\n";
    delete released; // 手动释放

    // 9. unique_ptr 不能拷贝，只能移动
    // std::unique_ptr<int> p6 = p5; // 错误，不能拷贝

    // 10. unique_ptr 用于自定义类型
    auto demoPtr = std::make_unique<Demo>();

    // 离开作用域时，所有 unique_ptr 自动释放资源
    return 0;
}