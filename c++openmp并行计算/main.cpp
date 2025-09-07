#include "computeRxDelay.h"
#include <iostream>
#include <chrono>


int main() {
    std::cout << "=== 接收延时计算性能比较 (优化循环顺序) ===\n";
    std::cout << "阵元数量: " << numElements << "\n";
    std::cout << "触发次数: " << numTrigs << "\n";
    std::cout << "采样点数: " << numPoints << "\n";
    std::cout << "总计算量: " << numTrigs * numElements * numPoints << " 次\n\n";

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

    std::cout << "性能比较:\n";
    std::cout << "顺序计算时间(Pointer): " << duration_seq_ptr.count() * 1000 << " ms\n";
    std::cout << "顺序计算时间(Vector): " << duration_seq_vec.count() * 1000 << " ms\n";
    std::cout << "并行计算时间(Pointer): " << duration_par_ptr.count() * 1000 << " ms\n";
    std::cout << "并行计算时间(Vector): " << duration_par_vec.count() * 1000 << " ms\n";

    return 0;
}