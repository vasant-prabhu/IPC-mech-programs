#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

void* printeven();
void* printodd();

sem_t sem_even,sem_odd;

int main()
{
pthread_t th[2];
sem_init(&sem_even,0,1);
sem_init(&sem_odd,0,0);
void* (*funcptr[2])();
funcptr[0]=printeven;
funcptr[1]=printodd;
for (int i=0;i<2;i++)
{
pthread_create(&th[0],NULL,(void*)funcptr[i],NULL);
}


pthread_join(th[0],NULL);
pthread_join(th[1],NULL);

sem_destroy(&sem_even);
sem_destroy(&sem_odd);


return 0;
}

void* printeven()
{
   int i=0;
   while(i<10)
   {
      sem_wait(&sem_even);
      printf("%d\n",i);
      sleep(random()%3);
      i+=2;
      sem_post(&sem_odd);
   }
   pthread_exit(0);
}

void* printodd()
{
   int i=1;
   while(i<10)
   {
      sem_wait(&sem_odd);
      printf("%d\n",i);
      sleep(random()%4);
      i+=2;
      sem_post(&sem_even);
   }
   pthread_exit(0);
}


