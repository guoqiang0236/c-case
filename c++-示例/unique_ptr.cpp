#include <iostream>
#include <memory>

// �Զ���ɾ����
void customDeleter(int* p) {
    std::cout << "�Զ���ɾ�����ͷ���Դ: " << *p << std::endl;
    delete p;
}

struct Demo {
    Demo() { std::cout << "Demo ����\n"; }
    ~Demo() { std::cout << "Demo ����\n"; }
    void hello() { std::cout << "Hello from Demo\n"; }
};

int main() {
    // 1. ���� unique_ptr������������
    std::unique_ptr<int> p1(new int(10));
    std::cout << "p1: " << *p1 << std::endl;

    // 2. ʹ�� make_unique���Ƽ���C++14�����ϣ�
    auto p2 = std::make_unique<Demo>();
    p2->hello();

    // 3. unique_ptr ��������
    std::unique_ptr<int[]> arr(new int[3] {1, 2, 3});
    std::cout << "arr[0]: " << arr[0] << ", arr[1]: " << arr[1] << std::endl;

    // 4. �Զ���ɾ����
    std::unique_ptr<int, void(*)(int*)> p3(new int(42), customDeleter);

    // 5. �ͷ���Դ��reset ���뿪�������Զ��ͷţ�
    p1.reset(); // �ֶ��ͷ� p1 �������Դ
    if (!p1) std::cout << "p1 �ѱ��ͷ�\n";

    // 6. ת������Ȩ
    auto p4 = std::make_unique<int>(100);
    std::unique_ptr<int> p5 = std::move(p4); // p4 ��Դת�Ƹ� p5
    if (!p4) std::cout << "p4 ��������Ȩ\n";
    std::cout << "p5: " << *p5 << std::endl;

    // 7. get() ��ȡԭʼָ�루���Ƽ�ֱ�� delete��
    int* raw = p5.get();
    std::cout << "ԭʼָ��ֵ: " << *raw << std::endl;

    // 8. release() �ͷ�����Ȩ����ɾ���������ֶ� delete��
    int* released = p5.release();
    if (!p5) std::cout << "p5 �� release\n";
    delete released; // �ֶ��ͷ�

    // 9. unique_ptr ���ܿ�����ֻ���ƶ�
    // std::unique_ptr<int> p6 = p5; // ���󣬲��ܿ���

    // 10. unique_ptr �����Զ�������
    auto demoPtr = std::make_unique<Demo>();

    // �뿪������ʱ������ unique_ptr �Զ��ͷ���Դ
    return 0;
}