#include<iostream>
#include<condition_variable>
#include<thread>
#include<mutex>
using namespace std;
int num=0;
std::mutex mu;
std::condition_variable cv;

void printeven()
{
	while(1)
	{
		unique_lock<std::mutex>lck(mu);
		cv.wait(lck,[]{return (num%2==1)?true:false;});
		num++;
		cout<<" "<<num;
		lck.unlock();
		cv.notify_one();
        if(num>100)break;
	}
}

void printodd()
{

	
	while(1)
	{
        unique_lock<std::mutex>lck(mu);
		cv.wait(lck,[]{return (num%2==0)?true:false;});
		num++;
		cout<<" "<<num;
		lck.unlock();
		cv.notify_one();
        if(num>100)break;
	}
}

int main()
{
	thread t1(printeven),t2(printodd);

	t1.join();
	t2.join();
	return 0;
}

