#include <iostream>
#include <vector>


// 普通左值引用
void func_lvalue(int& x) {
    std::cout << "左值引用函数被调用，值为: " << x << std::endl;
}

// 右值引用
void func_rvalue(int&& x) {
    std::cout << "右值引用函数被调用，值为: " << x << std::endl;
}

int main() {
    int a = 10;
    func_lvalue(a);      // 传递左值，调用左值引用版本
    //func_lvalue(20);  // 错误：不能将右值传给左值引用

    // func_rvalue(a);   // 错误：不能将左值传给右值引用
    func_rvalue(20);     // 传递右值，调用右值引用版本

    // std::move 可以把左值变成右值
    func_rvalue(std::move(a)); // 调用右值引用版本

    // 右值延长生命周期示例
    const int& ref = 30; // 用const左值引用绑定右值
    std::cout << "右值延长生命周期，ref = " << ref << std::endl;

    // 复杂类型同样适用
    const std::string& sref = std::string("hello");
    std::cout << "右值延长生命周期，sref = " << sref << std::endl;

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = std::move(v1); // v1 资源被“搬走”

    return 0;
}