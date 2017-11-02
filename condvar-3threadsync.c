#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void func1();
void func2();

void func3();
pthread_cond_t cond,cond2;
pthread_mutex_t mutex;


int main()
{
pthread_t thread[2];
pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&cond,NULL);

pthread_cond_init(&cond2,NULL);

int i=0;
int *status;
void (*funcptr[3])();
funcptr[0]=func1;
funcptr[1]=func2;
funcptr[2]=func3;

for (i=0;i<3;i++)
{
   if(pthread_create(&thread[i],NULL,(void *)funcptr[i],NULL))
   {
      printf("thread %ld failed to create",thread[i]);
   }
}

for (i=0;i<3;i++)
pthread_join(thread[i],(void*)&status);

pthread_exit(0);
return 0;
}

void func1()
{
      pthread_mutex_lock(&mutex);
      printf("I am producer\n");
      pthread_cond_signal(&cond);
      pthread_mutex_unlock(&mutex);
      
   }

void func2()
{
      pthread_mutex_lock(&mutex);
      pthread_cond_wait(&cond,&mutex);
      printf("I am consumer\n");
      pthread_mutex_unlock(&mutex);
      pthread_cond_signal(&cond2);
}

void func3()
{
      pthread_mutex_lock(&mutex);
      pthread_cond_wait(&cond2,&mutex);
      printf("I am in 3rd thread\n");
      pthread_mutex_unlock(&mutex);
}



