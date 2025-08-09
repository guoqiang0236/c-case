#include <iostream>
#include <vector>
#include <chrono>

// ��ֵ����
void passByValue(std::vector<int> v) {
    volatile int sum = 0;
    for (auto i : v) sum += i;
}

// �����ô���
void passByReference(const std::vector<int>& v) {
    volatile int sum = 0;
    for (auto i : v) sum += i;
}

int main() {
    const int N = 10000000;
    const int LOOP = 100;
    std::vector<int> data(N, 42);

    // ���԰�ֵ����
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < LOOP; ++i) {
        passByValue(data);
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();

    // ���԰����ô���
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < LOOP; ++i) {
        passByReference(data);
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();

    std::cout << "��ֵ���ݺ�ʱ: " << duration1 << " ms" << std::endl;
    std::cout << "�����ô��ݺ�ʱ: " << duration2 << " ms" << std::endl;

    return 0;
}