#include<iostream>


template<class T1,class T2>

class MyClass
{
public:
	T1 t11;
	T2 t22;
	MyClass(T1 t1, T2 t2) :t11(t1), t22(t2) {}  

	void display()
	{
		std::cout << "t11: " << t11 << ", t22: " << t22 << std::endl;
	}

};

int main()
{
	MyClass<int, double> obj1(10, 20.5);
	obj1.display();
	MyClass<std::string, char>obj2("Hello", 'A');
	obj2.display();
	return 0;
}


