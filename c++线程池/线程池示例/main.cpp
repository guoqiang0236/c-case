#include "XThreadPool.h"
int main(int argc, char* argv[])
{
	XThreadPool pool;
	pool.Init(14);
	pool.Start();

	getchar();
	return 0;

}