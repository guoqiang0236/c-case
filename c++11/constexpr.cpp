#include <iostream>
#include <array>
// 1. constexpr �����������ڱ���ʱ��ʼ��
constexpr int MAX_SIZE = 100;  // ����ֵ����


void func(const int num)
{
    const int count = 24;
    //int array[num];            // error��num��һ��ֻ�����������ǳ���
    int array1[count];         // ok��count��һ������

    int a1 = 520;
    int a2 = 250;
    const int& b = a1;
    //b = a2;                         // error
    a1 = 1314;
    std::cout << "b: " << b << std::endl;     // ������Ϊ1314
}

//constexpr struct constTest
//{
//    int id;
//    int num;
//};

struct Test
{
    int id;
    int num;
};

// error������func1()û�з���ֵ,���ǳ������ʽ����
constexpr void func1()
{
    int a = 100;
    std::cout << "a: " << a << std::endl;
}

// error������func2()����ֵ���ǳ������ʽ,���ǳ������ʽ����
constexpr int func2()
{
    int a = 100;
    return a;
}

// error
constexpr int func3()
{
    constexpr int a = 100;
    constexpr int b = 10;
    for (int i = 0; i < b; ++i)
    {
        std::cout << "i: " << i << std::endl;
    }
    return a + b;
}

// ok
constexpr int func4()
{
    using mytype = int;
    constexpr mytype a = 100;
    constexpr mytype b = 10;
    constexpr mytype c = a * b;
    return c - (a + b);
}


struct Person {
    constexpr Person(const char* p, int age) :name(p),age(age)
    {

    }
    const char* name;
    int age;
};

int main() {
    func(1);
    constexpr Test t{ 1,2 };
    constexpr int id = t.id;
    constexpr int num = t.num;
    //t.num += 100;
    std::cout << "id: " << id << ", num: " << num << std::endl;

    constexpr struct Person p1("luffy", 19);
    std::cout << "luffy's name: " << p1.name << ", age: " << p1.age << std::endl;



    system("pause");
	return 0;
}