#include <iostream>
#include <cstddef>

// 演示函数重载的区别
void func(int value) {
    std::cout << "调用 func(int)，参数值: " << value << std::endl;
}

void func(char* ptr) {
    std::cout << "调用 func(char*)，指针地址: " << static_cast<void*>(ptr) << std::endl;
}

// 演示模板类型推导
template<typename T>
void templateFunc(T param) {
    std::cout << "模板参数类型: " << typeid(T).name() << std::endl;
}

// 演示指针初始化
class MyClass {
public:
    void display() {
        std::cout << "MyClass 对象" << std::endl;
    }
};

int main() {
    std::cout << "=== 1. 函数重载场景 ===" << std::endl;

    // NULL 的问题：可能被解释为整数 0
    func(NULL);  // 可能调用 func(int) - 有歧义！

    // nullptr 正确：明确表示空指针
    func(nullptr);  // 调用 func(char*)

    std::cout << "\n=== 2. 模板类型推导 ===" << std::endl;

    templateFunc(NULL);     // 推导为整数类型
    templateFunc(nullptr);  // 推导为 std::nullptr_t

    std::cout << "\n=== 3. 指针初始化 ===" << std::endl;

    // 传统方式
    int* ptr1 = NULL;
    MyClass* obj1 = NULL;

    // C++11 推荐方式
    int* ptr2 = nullptr;
    MyClass* obj2 = nullptr;

    std::cout << "ptr1 (NULL): " << ptr1 << std::endl;
    std::cout << "ptr2 (nullptr): " << ptr2 << std::endl;

    std::cout << "\n=== 4. 条件判断 ===" << std::endl;

    if (ptr2 == nullptr) {
        std::cout << "ptr2 是空指针" << std::endl;
    }

    // 分配内存后的比较
    ptr2 = new int(42);
    if (ptr2 != nullptr) {
        std::cout << "ptr2 指向有效内存，值为: " << *ptr2 << std::endl;
        delete ptr2;
    }

    std::cout << "\n=== 5. nullptr 的类型 ===" << std::endl;

    // nullptr 有自己的类型
    auto null_ptr = nullptr;
    std::cout << "nullptr 的类型: " << typeid(null_ptr).name() << std::endl;

    // 可以转换为任何指针类型
    int* int_ptr = nullptr;
    char* char_ptr = nullptr;
    MyClass* class_ptr = nullptr;

    std::cout << "nullptr 可以赋值给任何指针类型" << std::endl;

    return 0;
}