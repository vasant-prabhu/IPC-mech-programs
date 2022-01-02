//use 3 threads to print numbers serially using semaphore
//
//

#include<iostream>
#include<semaphore.h>
#include<chrono>
#include<thread>
using namespace std;
void* func1(void *);
void* func2(void *);
void* func3(void *);

sem_t sem1,sem2,sem3;

int main()
{
pthread_t t1,t2,t3;
int tid[]={1,2,3};
sem_init(&sem1,0,1);
sem_init(&sem2,0,0);
sem_init(&sem3,0,0);

pthread_create(&t1,NULL,func1,&tid[0]);
pthread_create(&t2,NULL,func2,&tid[1]);
pthread_create(&t3,NULL,func3,&tid[2]);
pthread_join(t1,NULL);
pthread_join(t2,NULL);
pthread_join(t3,NULL);

return 0;
}

void* func1(void *tid)
{
while(1)
{
sem_wait(&sem1);
cout<<"hello from thread1"<<endl;
std::this_thread::sleep_for(std::chrono::milliseconds(1000));
sem_post(&sem2);
}
return 0;
}

void* func2(void *tid)
{
	while(1)
	{
sem_wait(&sem2);
cout<<"hello from thread2"<<endl;
std::this_thread::sleep_for(std::chrono::milliseconds(1000));
sem_post(&sem3);
	}
return 0;
	
}

void* func3(void *tid)
{
while(1)
{
sem_wait(&sem3);
cout<<"hello from thread3"<<endl;
std::this_thread::sleep_for(std::chrono::milliseconds(1000));
sem_post(&sem1);
}
return 0;
}

