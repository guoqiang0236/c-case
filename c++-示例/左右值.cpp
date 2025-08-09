#include <iostream>
#include <vector>


// ��ͨ��ֵ����
void func_lvalue(int& x) {
    std::cout << "��ֵ���ú��������ã�ֵΪ: " << x << std::endl;
}

// ��ֵ����
void func_rvalue(int&& x) {
    std::cout << "��ֵ���ú��������ã�ֵΪ: " << x << std::endl;
}

int main() {
    int a = 10;
    func_lvalue(a);      // ������ֵ��������ֵ���ð汾
    //func_lvalue(20);  // ���󣺲��ܽ���ֵ������ֵ����

    // func_rvalue(a);   // ���󣺲��ܽ���ֵ������ֵ����
    func_rvalue(20);     // ������ֵ��������ֵ���ð汾

    // std::move ���԰���ֵ�����ֵ
    func_rvalue(std::move(a)); // ������ֵ���ð汾

    // ��ֵ�ӳ���������ʾ��
    const int& ref = 30; // ��const��ֵ���ð���ֵ
    std::cout << "��ֵ�ӳ��������ڣ�ref = " << ref << std::endl;

    // ��������ͬ������
    const std::string& sref = std::string("hello");
    std::cout << "��ֵ�ӳ��������ڣ�sref = " << sref << std::endl;

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = std::move(v1); // v1 ��Դ�������ߡ�

    return 0;
}