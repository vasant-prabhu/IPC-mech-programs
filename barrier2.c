//barriers wait for other threads to complete and then barrier is removed

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void func1();
void func2();
void func3();
pthread_barrier_t barrier;

int main()
{
int ret=-1;
pthread_t t[3];
pthread_barrier_init(&barrier,0,3);

ret=pthread_create(&t[0],NULL,(void*)func1,NULL);

if(ret)
{
printf("Thread 1 failed");
}

ret=pthread_create(&t[1],NULL,(void*)func2,NULL);
if(ret)
{
printf("Thread 2 failed");
}


ret=pthread_create(&t[2],NULL,(void*)func3,NULL);
if(ret)
{
printf("Thread 3 failed");
}

for (int i=0;i<3;i++)
pthread_join(t[i],NULL);

pthread_exit(NULL);

return 0;

}

void func1()
{
printf("Before th1 hits the barrier..\n");
pthread_barrier_wait(&barrier);

printf("After th1 hits the barrier..\n");
pthread_exit(NULL);
}

void func2()
{

printf("Before th2 hits the barrier..\n");

pthread_barrier_wait(&barrier);


printf("After th2 hits the barrier..\n");

pthread_exit(NULL);
}

void func3()
{

sleep(5);
printf("Before th3 hits the barrier..\n");
pthread_barrier_wait(&barrier);
printf("After th3 hits the barrier..\n");
int i=0;
while(i<=10)
printf("%d\n",i++);

pthread_exit(NULL);
}




