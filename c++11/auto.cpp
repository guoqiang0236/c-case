#include<iostream>
#include<string>
#include <map>
//auto�ؼ��ֲ��������ܵģ���������Щ�������ǲ�����������Ƶ��ģ�
//int func(auto a, auto b)	// error
//{
//	cout << "a: " << a << ", b: " << b << endl;
//}


//����������ķǾ�̬��Ա�����ĳ�ʼ��
class Test
{
	//auto v1 = 0;                    // error
	//static auto v2 = 0;             // error,��ľ�̬�ǳ�����Ա�����������ڲ�ֱ�ӳ�ʼ��
	static const auto v3 = 10;      // ok
};

//����ʹ��auto�ؼ��ֶ�������
int func()
{
	int array[] = { 1,2,3,4,5 };  // ��������
	auto t1 = array;            // ok, t1���Ƶ�Ϊ int* ����
	//auto t2[] = array;          // error, auto�޷���������
	//auto t3[] = { 1,2,3,4,5 };;   // error, auto�޷���������
	return 0;
}

//�޷�ʹ��auto�Ƶ���ģ�����
template <typename T>
struct Test2 {};

int func2()
{
	Test2<double> t;
	//Test<auto> t1 = t;           // error, �޷��Ƶ���ģ������
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
	auto x = 3.14;      // x �Ǹ����� double
	auto y = 520;       // y ������ int
	auto z = 'a';       // z ���ַ��� char
	//auto nb;            // error����������Ҫ��ʼ��
	//auto double nbl;    // �﷨����, �����޸���������   

	int temp = 110;
	auto *a = &temp;      //����a����������Ϊ int* �����auto�ؼ��ֱ��Ƶ�Ϊ int����   
	auto b = &temp;		  //����b����������Ϊ int* �����auto�ؼ��ֱ��Ƶ�Ϊ int* ����
	auto& c = temp;		  //����c����������Ϊ int& �����auto�ؼ��ֱ��Ƶ�Ϊ int����
	auto d = temp;        //����d����������Ϊ int�����auto�ؼ��ֱ��Ƶ�Ϊ int����


	int tmp = 250;          
	const auto a1 = tmp;    //����a1����������Ϊ const int�����auto�ؼ��ֱ��Ƶ�Ϊ int����


	auto a2 = a1;            //����a2����������Ϊ int������a2û������Ϊָ���������� const���Ա�ȥ��, auto���Ƶ�Ϊ int 

	const auto& a3 = tmp;   //����a3����������Ϊ const int& ��a3������Ϊ������� const���Ա�������auto�ؼ��ֱ��Ƶ�Ϊ int����

	
	auto& a4 = a3;          //����a4����������Ϊ const int& ��a4������Ϊ������� const���Ա�������auto�ؼ��ֱ��Ƶ�Ϊ const int����


	//����
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