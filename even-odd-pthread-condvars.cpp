#include<iostream>
#include<pthread.h>
#include<stdlib.h>

using namespace std;
int num=0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void* printeven(void * tid)
{
	while(num<100)
	{
		
		pthread_mutex_lock(&mutex);
		while(num%2==0)
		    pthread_cond_wait(&cond,&mutex);
		cout<<" "<<++num;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	return 0;
}

void* printodd(void *tid)
{
	while(num<100)
	{
		pthread_mutex_lock(&mutex);
                while(num%2==1)
                    pthread_cond_wait(&cond,&mutex);
		cout<<" "<<++num;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	return 0;
}

int main()
{
	pthread_t t1,t2;
	int tid[]={1,2};
	
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	pthread_create(&t1,NULL,printeven,&tid[0]);
	pthread_create(&t2,NULL,printodd,&tid[1]);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}

