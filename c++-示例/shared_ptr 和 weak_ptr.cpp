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

struct Node; // ǰ������

struct Node {
    std::string name;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev; // �� weak_ptr ��ֹѭ������
    Node(const std::string& n) : name(n) { std::cout << name << " ����\n"; }
    ~Node() { std::cout << name << " ����\n"; }
};

int main() {
    // 1. ���� shared_ptr������������
    std::shared_ptr<int> p1(new int(10));
    std::cout << "p1: " << *p1 << ", use_count: " << p1.use_count() << std::endl;

    // 2. ʹ�� make_shared���Ƽ���
    auto p2 = std::make_shared<Demo>();
    p2->hello();
    std::cout << "p2 use_count: " << p2.use_count() << std::endl;

    // 3. shared_ptr �������飨���Ƽ����Ƽ��� unique_ptr �������飩
    std::shared_ptr<int> arr(new int[3] {1, 2, 3}, [](int* p) { delete[] p; });
    std::cout << "arr[0]: " << arr.get()[0] << ", arr[1]: " << arr.get()[1] << std::endl;

    // 4. �Զ���ɾ����
    std::shared_ptr<int> p3(new int(42), customDeleter);

    // 5. reset() �ͷ���Դ
    p1.reset();
    if (!p1) std::cout << "p1 �ѱ��ͷ�\n";

    // 6. �����͸�ֵ���������ü�����
    auto p4 = std::make_shared<int>(100);
    std::shared_ptr<int> p5 = p4; // ����
    std::cout << "p4 use_count: " << p4.use_count() << ", p5 use_count: " << p5.use_count() << std::endl;

    // 7. swap �������� shared_ptr
    auto p6 = std::make_shared<int>(200);
    p5.swap(p6);
    std::cout << "p5: " << *p5 << ", p6: " << *p6 << std::endl;

    // 8. get() ��ȡԭʼָ�루���Ƽ�ֱ�� delete��
    int* raw = p5.get();
    std::cout << "ԭʼָ��ֵ: " << *raw << std::endl;

    // 9. use_count() ��ȡ���ü���
    std::cout << "p5 use_count: " << p5.use_count() << std::endl;

    // 10. weak_ptr ���ѭ������
    {
        auto n1 = std::make_shared<Node>("n1");
        auto n2 = std::make_shared<Node>("n2");
        n1->next = n2;
        n2->prev = n1; // weak_ptr ���������ü���
        std::cout << "n1 use_count: " << n1.use_count() << ", n2 use_count: " << n2.use_count() << std::endl;
    } // �뿪������n1/n2 ��������

    // 11. weak_ptr �����÷�
    std::shared_ptr<int> sp = std::make_shared<int>(123);
    std::weak_ptr<int> wp = sp;
    std::cout << "sp use_count: " << sp.use_count() << std::endl;
    if (auto locked = wp.lock()) {
        std::cout << "weak_ptr �ɹ����ʵ� shared_ptr��ֵΪ: " << *locked << std::endl;
    }
    sp.reset();
    if (wp.expired()) {
        std::cout << "weak_ptr ָ��Ķ������ͷ�\n";
    }

    // �뿪������ʱ������ shared_ptr �Զ��ͷ���Դ
    return 0;
}