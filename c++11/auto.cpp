#include<iostream>
#include<string>
#include <map>
//auto关键字并不是万能的，在以下这些场景中是不能完成类型推导的：
//int func(auto a, auto b)	// error
//{
//	cout << "a: " << a << ", b: " << b << endl;
//}


//不能用于类的非静态成员变量的初始化
class Test
{
	//auto v1 = 0;                    // error
	//static auto v2 = 0;             // error,类的静态非常量成员不允许在类内部直接初始化
	static const auto v3 = 10;      // ok
};

//不能使用auto关键字定义数组
int func()
{
	int array[] = { 1,2,3,4,5 };  // 定义数组
	auto t1 = array;            // ok, t1被推导为 int* 类型
	//auto t2[] = array;          // error, auto无法定义数组
	//auto t3[] = { 1,2,3,4,5 };;   // error, auto无法定义数组
	return 0;
}

//无法使用auto推导出模板参数
template <typename T>
struct Test2 {};

int func2()
{
	Test2<double> t;
	//Test<auto> t1 = t;           // error, 无法推导出模板类型
	return 0;
}



using namespace std;

class T1
{
public:
	static int get()
	{
		return 10;
	}
};

class T2
{
public:
	static string get()
	{
		return "hello, world";
	}
};

template <class A>
void func5(void)
{
	auto val = A::get();
	cout << "val: " << val << endl;
}





int main()
{
	auto x = 3.14;      // x 是浮点型 double
	auto y = 520;       // y 是整形 int
	auto z = 'a';       // z 是字符型 char
	//auto nb;            // error，变量必须要初始化
	//auto double nbl;    // 语法错误, 不能修改数据类型   

	int temp = 110;
	auto *a = &temp;      //变量a的数据类型为 int* ，因此auto关键字被推导为 int类型   
	auto b = &temp;		  //变量b的数据类型为 int* ，因此auto关键字被推导为 int* 类型
	auto& c = temp;		  //变量c的数据类型为 int& ，因此auto关键字被推导为 int类型
	auto d = temp;        //变量d的数据类型为 int，因此auto关键字被推导为 int类型


	int tmp = 250;          
	const auto a1 = tmp;    //变量a1的数据类型为 const int，因此auto关键字被推导为 int类型


	auto a2 = a1;            //变量a2的数据类型为 int，但是a2没有声明为指针或引用因此 const属性被去掉, auto被推导为 int 

	const auto& a3 = tmp;   //变量a3的数据类型为 const int& ，a3被声明为引用因此 const属性被保留，auto关键字被推导为 int类型

	
	auto& a4 = a3;          //变量a4的数据类型为 const int& ，a4被声明为引用因此 const属性被保留，auto关键字被推导为 const int类型


	//遍历
	std::map<int, std::string>person;
	for (auto it = person.begin(); it != person.end(); it++)
	{
		//do something
	}

	func5<T1>();
	func5<T2>();
	system("pause"); 
	return 0;

}