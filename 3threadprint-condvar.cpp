#include<iostream>
#include<thread>
#include<condition_variable>
#include<chrono>
std::mutex mu;
std::condition_variable cv,cv2,cv3;
using namespace std;
bool result1=false;
bool result2=false;
bool result3=true;
int i=1;//global

void func1()
{
   while(1)
   {
      std::unique_lock<std::mutex>lck(mu);
      cv3.wait(lck,[]{return result3?true:false;});
      result3=false;
      cout<<i<<endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      i++;
      result1=true;
      lck.unlock();
      cv.notify_one();
      if(i>100)break;
   }
}

void func2()
{
   while(1)
   {
      std::unique_lock<std::mutex>lck(mu);
      cv.wait(lck,[]{return result1?true:false;});
      result1=false;
      cout<<i<<endl;

      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      i++;
      
      result2=true;
      lck.unlock();
      cv2.notify_one();
      if(i>100)break;
   }
}

void func3()
{  
    while(1)
    {  
      std::unique_lock<std::mutex>lck(mu);
      cv2.wait(lck,[]{return result2?true:false;});
      result2=false;
      cout<<i<<endl;
      i++;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      result3=true;
      lck.unlock();
      cv3.notify_one();
      if(i>100)break;
    }
}

//driver code
int main()
{
std::thread t1(func1);
std::thread t2(func2);
std::thread t3(func3);

t1.join();
t2.join();
t3.join();

return 0;
}
