#include<iostream>
#include<vector>
template<typename T>
void bianli(const std::vector<T>&source) {
	for(const auto&item:source) {
		std::cout << item << " ";
	}
}



int main() {
	// 示例 1: 遍历整数 vector
	std::vector<int> numbers = { 1, 2, 3, 4, 5 };
	std::cout << "整数: ";
	bianli(numbers);
	std::cout << std::endl;

	// 示例 2: 遍历浮点数 vector
	std::vector<double> decimals = { 1.1, 2.2, 3.3, 4.4 };
	std::cout << "浮点数: ";
	bianli(decimals);
	std::cout << std::endl;

	// 示例 3: 遍历字符串 vector
	std::vector<std::string> words = { "Hello", "World", "C++" };
	std::cout << "字符串: ";
	bianli(words);
	std::cout << std::endl;

	// 示例 4: 遍历字符 vector
	std::vector<char> chars = { 'A', 'B', 'C', 'D' };
	std::cout << "字符: ";
	bianli(chars);
	std::cout << std::endl;

	// 示例 5: 遍历空 vector
	std::vector<int> empty;
	std::cout << "空向量: ";
	bianli(empty);
	std::cout << std::endl;

	return 0;
}