#include <iostream>
#include <cstddef>

// ��ʾ�������ص�����
void func(int value) {
    std::cout << "���� func(int)������ֵ: " << value << std::endl;
}

void func(char* ptr) {
    std::cout << "���� func(char*)��ָ���ַ: " << static_cast<void*>(ptr) << std::endl;
}

// ��ʾģ�������Ƶ�
template<typename T>
void templateFunc(T param) {
    std::cout << "ģ���������: " << typeid(T).name() << std::endl;
}

// ��ʾָ���ʼ��
class MyClass {
public:
    void display() {
        std::cout << "MyClass ����" << std::endl;
    }
};

int main() {
    std::cout << "=== 1. �������س��� ===" << std::endl;

    // NULL �����⣺���ܱ�����Ϊ���� 0
    func(NULL);  // ���ܵ��� func(int) - �����壡

    // nullptr ��ȷ����ȷ��ʾ��ָ��
    func(nullptr);  // ���� func(char*)

    std::cout << "\n=== 2. ģ�������Ƶ� ===" << std::endl;

    templateFunc(NULL);     // �Ƶ�Ϊ��������
    templateFunc(nullptr);  // �Ƶ�Ϊ std::nullptr_t

    std::cout << "\n=== 3. ָ���ʼ�� ===" << std::endl;

    // ��ͳ��ʽ
    int* ptr1 = NULL;
    MyClass* obj1 = NULL;

    // C++11 �Ƽ���ʽ
    int* ptr2 = nullptr;
    MyClass* obj2 = nullptr;

    std::cout << "ptr1 (NULL): " << ptr1 << std::endl;
    std::cout << "ptr2 (nullptr): " << ptr2 << std::endl;

    std::cout << "\n=== 4. �����ж� ===" << std::endl;

    if (ptr2 == nullptr) {
        std::cout << "ptr2 �ǿ�ָ��" << std::endl;
    }

    // �����ڴ��ıȽ�
    ptr2 = new int(42);
    if (ptr2 != nullptr) {
        std::cout << "ptr2 ָ����Ч�ڴ棬ֵΪ: " << *ptr2 << std::endl;
        delete ptr2;
    }

    std::cout << "\n=== 5. nullptr ������ ===" << std::endl;

    // nullptr ���Լ�������
    auto null_ptr = nullptr;
    std::cout << "nullptr ������: " << typeid(null_ptr).name() << std::endl;

    // ����ת��Ϊ�κ�ָ������
    int* int_ptr = nullptr;
    char* char_ptr = nullptr;
    MyClass* class_ptr = nullptr;

    std::cout << "nullptr ���Ը�ֵ���κ�ָ������" << std::endl;

    return 0;
}