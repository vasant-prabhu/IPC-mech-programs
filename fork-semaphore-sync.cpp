// To synchronise 2 processes using Named semaphore.

#include<iostream>
#include<unistd.h>
#include<semaphore.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>

const char* SEMNAME="/preeti";

int main()
{
    using namespace std;
    pid_t pid_child;

sem_t *mysem = sem_open(SEMNAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, 0);
sem_init(mysem,1,0);// process shared is set to 1

if (!fork())
{  
    cout<<"I am in child class"<<endl;
    sleep(5);
    sem_post(mysem);
}
else
{
    mysem = sem_open(SEMNAME, O_RDWR);
    sem_wait(mysem);
    cout<<"I am in parent class"<<endl;
    pid_child = getpid();
    cout<<"pid of child is"<<pid_child<<endl;
}
//wait(NULL);
return 0;
}



