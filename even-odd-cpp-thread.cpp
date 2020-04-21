#include<iostream>
#include<mutex>
#include<condition_variable>
#include<chrono>
#include<thread>

std::mutex mu;
std::condition_variable cv;
int i=0;

using namespace std;

void printeven()
{
   while(1) 
   {
      std::unique_lock<std::mutex>lck(mu);
      cv.wait(lck,[]{return (i%2==1)?true:false;});
      cout<<" "<<++i;
      lck.unlock();
      cv.notify_one();
      if(i>100)break;
   } 
}

void printodd()
{
while(1)
{
      std::unique_lock<std::mutex>lck(mu);
      cv.wait(lck,[]{return (i%2==0)?true:false;});
      cout<<" "<<++i;
      lck.unlock();
      cv.notify_one();
      if(i>100)break;
}
}

int main()
{

std::thread t1(printeven);
std::thread t2(printodd);

t1.join();
t2.join();

return 0;
}
