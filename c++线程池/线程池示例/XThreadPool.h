#pragma once
#include <thread>
#include <mutex>
#include <vector>

class XThreadPool
{
public:
	/// ��ʼ���̳߳�
	/// @para num �߳�����
	void Init(int num);

	/// ���������̣߳������ȵ���Init
	void Start();

private:
	//�̳߳��̵߳���ں���
	void Run();

	int thread_num = 0;
	std::mutex mux_;
	std::vector<std::thread*> threads_;

};
