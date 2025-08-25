#include "XThreadPool.h"
#include <iostream>
using namespace std;

void XThreadPool::Init(int num)
{
	unique_lock<mutex> lock(mux_);

	this->thread_num = num;

	cout << "Thread pool Init " << num << endl;
}

void XThreadPool::Start()
{
	unique_lock<mutex>lock(mux_);
    if (thread_num <= 0)
    {
        cerr << "Please Init XThreadPool" << endl;
        return;
    }
    if (!threads_.empty())
    {
        cerr << "Thread pool has start!" << endl;
        return;
    }
    //Æô¶¯Ïß³Ì
    for(int i=0;i<thread_num;i++)
    {
        auto th = new thread(&XThreadPool::Run, this);
		threads_.push_back(th);
	}

}

void XThreadPool::Run()
{
    unique_lock<mutex>lock(mux_);
    cout << "begin XThreadPool Run " << this_thread::get_id() << endl;

    cout << "end XThreadPool Run " << this_thread::get_id() << endl;
}
