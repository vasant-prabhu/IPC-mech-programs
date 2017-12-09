#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void func1();
void func2();

pthread_cond_t cond;
pthread_mutex_t mutex;

int food=0;

int main()
{
pthread_t thread[2];
pthread_attr_t attr;
pthread_attr_init(&attr); // attributes should be initialized before pthread_create. 
pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&cond,NULL);

int i=0;
int *status;
void (*funcptr[2])();
funcptr[0]=func1;
funcptr[1]=func2;

for (i=0;i<2;i++)
{
   if(pthread_create(&thread[i],NULL,(void *)funcptr[i],NULL))
   {
      printf("thread %ld failed to create",thread[i]);
   }
}

for (i=0;i<2;i++)
pthread_join(thread[i],(void*)&status);

pthread_exit(0);
return 0;
}

void func1()
{
   while(1)
   {
      sleep(1);
      pthread_mutex_lock(&mutex);
      printf("I am producer -- food is %d\n",++food);
      pthread_cond_signal(&cond);
      pthread_mutex_unlock(&mutex);
      
   }
}

void func2()
{
   while(1)
   {
      sleep(1);
      pthread_mutex_lock(&mutex);
      pthread_cond_wait(&cond,&mutex);
      printf("I am consumer- food is %d\n",--food);
      pthread_mutex_unlock(&mutex);
   }
}

