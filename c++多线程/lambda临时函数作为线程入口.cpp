#include <thread>
#include <iostream>
#include <string>
//Linux -lpthread
using namespace std;
// test lambda thread
class TestLambda
{
public:
    void Start()
    {
        thread th([this]() {cout << "name = " << name << endl; });
        th.join();
    }

    string name = "test lambda";
};
int main(int argc, char* argv[])
{
    thread th(
        [](int i) {cout << "test lmbda " << i << endl; },
        123
    );
    th.join();
    TestLambda test;
    test.Start();

    return 0;
}