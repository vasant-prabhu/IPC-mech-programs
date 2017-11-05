#ifndef _SHMEM_BUFFER
#define _SHMEM_BUFFER

#define MAX_BUFFER 10

struct shm
{
   char buf[MAX_BUFFER][256];
   int print_buffer;
   int client_buffer; 
}shmem;


#endif
