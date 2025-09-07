/*
在C++中，拷贝构造函数和**赋值运算符（operator=）**的参数通常必须是“引用”，
而且一般是“const引用”。原因如下：
1. 拷贝构造函数
•	如果参数不是引用（如 MyClass other），会导致在调用拷贝构造函数时，参数传递又需要拷贝一次对象，这样会递归调用拷贝构造函数，导致无限递归，编译失败。
•	使用const可以允许用常量对象或临时对象进行拷贝。
2. 赋值运算符
•	同样，如果参数不是引用，会导致不必要的拷贝和递归。
•	返回类型是引用（MyClass&），以支持连续赋值（如a = b = c;）。
总结
•	必须用引用，否则会无限递归或效率低下。
•	推荐用const引用，以支持常量对象和避免不必要的修改。
*/

class Example {
public:
    Example() {}
    Example(const Example& other) { /* 拷贝逻辑 */ }
    Example& operator=(const Example& other) { /* 赋值逻辑 */ return *this; }
};