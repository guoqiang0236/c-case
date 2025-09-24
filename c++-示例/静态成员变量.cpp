#include <iostream>

// 基类A，包含静态成员变量
class A {
public:
    static int value; // 静态成员变量，所有子类共享
};

// 静态成员变量定义和初始化
int A::value = 0;

// 派生类B
class B : public A {
public:
    void setValue(int v) { value = v; }
    int getValue() const { return value; }
};

// 派生类C
class C : public A {
public:
    void setValue(int v) { value = v; }
    int getValue() const { return value; }
};

// 派生类D
class D : public A {
public:
    void setValue(int v) { value = v; }
    int getValue() const { return value; }
};

int main() {
    B b;
    C c;
    D d;

    b.setValue(10);
    std::cout << "C sees value: " << c.getValue() << std::endl; // 输出10

    d.setValue(20);
    std::cout << "B sees value: " << b.getValue() << std::endl; // 输出20

    return 0;
}