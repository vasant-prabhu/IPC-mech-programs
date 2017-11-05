// This is a server that would receive prints from a client

#include<stdio.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<semaphore.h>
#include "sharedmem.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
   //Initialize the semaphores
   sem_t *mutex_sem = sem_open("/mymutex",O_CREAT,0644,0);
   sem_t *shared_buffer_sem = sem_open("/shmbuffer",O_RDWR,0644,10);
   sem_t *spool_sem = sem_open("/myspool",O_CREAT,0644,0);

   int logfd = open("./preeti-log.txt",O_CREAT|O_WRONLY|O_APPEND|O_SYNC,0666);

   char mybuf[256];
   // Server should check if there is some print coming from the client

   int fd = shm_open("/sharedmemory",O_RDWR|O_CREAT,0644);   
   ftruncate(fd,sizeof(struct shm));

   struct shm *shmptr = mmap(NULL,sizeof(struct shm),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

    shmptr->print_buffer=shmptr->client_buffer=0;

   //Now that shared memory is initialised , unlock the mutex semaphore

   sem_post(mutex_sem);

   // Now do the job of reading from shared memory , continuously
   while(1)
   {
      //Before we do anything , wait on spool signal from client
      sem_wait(spool_sem);
      strcpy(mybuf,shmptr->buf[shmptr->print_buffer]);
      shmptr->print_buffer++;

      if (shmptr->print_buffer == MAX_BUFFER)
      {
         shmptr->print_buffer=0;
      }
      
      // Now that shm buffer write is complete, released the shared memory
      sem_post(shared_buffer_sem);

      write(logfd,mybuf,strlen(mybuf));
   }

   return 0;
}
