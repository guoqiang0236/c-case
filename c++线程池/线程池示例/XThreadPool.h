#pragma once
#include <thread>
#include <mutex>
#include <vector>

class XThreadPool
{
public:
	/// 初始化线程池
	/// @para num 线程数量
	void Init(int num);

	/// 启动所有线程，必须先调用Init
	void Start();

private:
	//线程池线程的入口函数
	void Run();

	int thread_num = 0;
	std::mutex mux_;
	std::vector<std::thread*> threads_;

};
