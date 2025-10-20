#include<vector>
#include<mutex>
#include<condition_variable>
#include<iostream>

template<typename data>
class ThreadSafeVector {

public:
     ThreadSafeVector() = default;
	 ThreadSafeVector(const ThreadSafeVector&) = delete;
	 ThreadSafeVector operator=(const ThreadSafeVector&) = delete;

	 void push_back(const data& value) {
		 std::lock_guard<std::mutex> lock(m_mutex);
		 m_datas.push_back(value);
		 m_condition.notify_one();
	 }

	 data pop_back() {
		 std::unique_lock<std::mutex> lock(m_mutex);
		 m_condition.wait(lock, [this]() { return !m_datas.empty(); });
		 data value = std::move(m_datas.back());
		 m_datas.pop_back();
		 return 
			 value;
	 }
	 bool try_pop_back(data& value) {
		 std::lock_guard<std::mutex> lock(m_mutex);
		 if (m_datas.empty()) {
			 return false;
		 }
		 value = std::move(m_datas.back());
		 m_datas.pop_back();
		 return true;
	 }

	 size_t size() const {
		 std::lock_guard<std::mutex> lock(m_mutex);
		 return m_datas.size();
	 }
private:
	std::vector<data> m_datas;
	mutable std::mutex m_mutex;
	std::condition_variable m_condition;
};

int main() {
	ThreadSafeVector<int> tsVector;
	std::thread producer1([&tsVector]() {
			for(int i = 0; i < 50; ++i) {
				tsVector.push_back(i);
				std::cout << "生产者1 添加: " << i << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	);

	std::thread producer2([&tsVector]() {
		for (int i = 0; i < 50; ++i) {
			tsVector.push_back(i);
			std::cout << "生产者2 添加: " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
		}
	);

	std::thread consumer1([&tsVector]() {
			for (int i = 0; i < 20; ++i) {
				int value = tsVector.pop_back();
				std::cout << "消费者1 移除: " << value << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}
		}
	);

	std::thread consumer2([&tsVector]() {
		for (int i = 0; i < 31; ++i) {
			int value = tsVector.pop_back();
			std::cout << "消费者2 移除: " << value << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(170));
		}
		}
	);

	producer1.join();
	producer2.join();
	consumer1.join();
	consumer2.join();

	std::cout << "\n最终容器大小: " << tsVector.size() << std::endl;
	return 0;
}