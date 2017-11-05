// This is a client that would be writing to a shared buffer
// This code will be run by multiple clients in a safe way

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
#include <time.h>

int main()
{
   //Initialize the semaphores
   sem_t *mutex_sem = sem_open("/mymutex",0,0,0);
   sem_t *shared_buffer_sem = sem_open("/shmbuffer",0,0,0);
   sem_t *spool_sem = sem_open("/myspool",0,0,0);

   // Server should check if there is some print coming from the client

   int fd = shm_open("/sharedmemory",O_RDWR,0);   
   //ftruncate(fd,sizeof(shmem));
   struct shm *shmptr = mmap(NULL,sizeof(struct shm),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);


   char buf[200]={'\0'};
char *cp;
   printf("Please type a message");
   while(fgets(buf,198,stdin))
   {
      int length = strlen(buf);
      if (buf[length-1] =='\n')
      buf[length-1]='\0';
      //Now check if shared memory buffer is free
      sem_wait(shared_buffer_sem);

      //Now there may be number of producers trying to write into 
      //the shared memory,so lock it using a mutex

      sem_wait(mutex_sem);
      // Entering critical section

      time_t now = time (NULL);
            cp = ctime (&now);
            int len = strlen (cp);
            if (*(cp + len -1) == '\n')
                *(cp + len -1) = '\0';
  sprintf (shmptr->buf[shmptr->client_buffer],"%d: %s %s\n", getpid (),cp, buf);
      shmptr->client_buffer++;
     printf("hello 3");

      if (shmptr->client_buffer == MAX_BUFFER)
      {
         shmptr->client_buffer=0;
      }
      sem_post(mutex_sem);
      
      // Now string is available , so signal spool to put it into the 
      //text file
      sem_post(spool_sem);
      printf("Please enter a message");
   }

   return 0;
}
