#include "computeRxDelay.h"
#include <iostream>
#include <chrono>


int main() {
    std::cout << "=== ������ʱ�������ܱȽ� (�Ż�ѭ��˳��) ===\n";
    std::cout << "��Ԫ����: " << numElements << "\n";
    std::cout << "��������: " << numTrigs << "\n";
    std::cout << "��������: " << numPoints << "\n";
    std::cout << "�ܼ�����: " << numTrigs * numElements * numPoints << " ��\n\n";

    double* delays_ptr = new double[numPoints * numPoints * numTrigs];
    std::vector<double> delays_vec;
	delays_vec.resize(numElements * numPoints * numTrigs);
 

    auto start = std::chrono::high_resolution_clock::now();   
    calculate_delays_sequential(delays_ptr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_seq_ptr = end - start;

    start = std::chrono::high_resolution_clock::now();
    calculate_delays_sequential(delays_vec);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_seq_vec = end - start;

    start = std::chrono::high_resolution_clock::now();
    calculate_delays_parallel(delays_vec);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_par_vec = end - start;

    start = std::chrono::high_resolution_clock::now();
    calculate_delays_parallel(delays_ptr);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_par_ptr = end - start;

   

    delete[] delays_ptr;

    std::cout << "���ܱȽ�:\n";
    std::cout << "˳�����ʱ��(Pointer): " << duration_seq_ptr.count() * 1000 << " ms\n";
    std::cout << "˳�����ʱ��(Vector): " << duration_seq_vec.count() * 1000 << " ms\n";
    std::cout << "���м���ʱ��(Pointer): " << duration_par_ptr.count() * 1000 << " ms\n";
    std::cout << "���м���ʱ��(Vector): " << duration_par_vec.count() * 1000 << " ms\n";

    return 0;
}