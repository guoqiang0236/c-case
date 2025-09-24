#include <iostream>

// ����A��������̬��Ա����
class A {
public:
    static int value; // ��̬��Ա�������������๲��
};

// ��̬��Ա��������ͳ�ʼ��
int A::value = 0;

// ������B
class B : public A {
public:
    void setValue(int v) { value = v; }
    int getValue() const { return value; }
};

// ������C
class C : public A {
public:
    void setValue(int v) { value = v; }
    int getValue() const { return value; }
};

// ������D
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
    std::cout << "C sees value: " << c.getValue() << std::endl; // ���10

    d.setValue(20);
    std::cout << "B sees value: " << b.getValue() << std::endl; // ���20

    return 0;
}