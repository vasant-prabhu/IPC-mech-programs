// This is the client which will send request to server for  Airplane seat tokens.
// Once enter is pressed , it sends request to server for a token 
// Client will communicate its message queue name to server.

//Step 1:- Create a message queue for the client

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define SERVER_MSG_QUEUE "/server-queue"

int main()
{

mqd_t serverid,clientid;
char client_queue_name[64];

struct mq_attr attr;

attr.mq_flags=0;
attr.mq_maxmsg=10;
attr.mq_msgsize=255;
attr.mq_curmsgs=0;
sprintf(client_queue_name,"/client-queue-%d",getpid());


if (clientid = mq_open(client_queue_name,O_CREAT|O_RDONLY,0660,&attr)==-1)
{
printf("Error creating client message queue\n");
exit(-1);
}

if (serverid = mq_open(SERVER_MSG_QUEUE,O_WRONLY)==-1)
{
printf("Error creating server message queue\n");
exit(-1);
}


//Step 2: Now the client will want to contact the server for tokens
char in_buffer[265];
char out_buffer[10];

   printf("Just press ENTER to send a request to server");
while (fgets(out_buffer,2,stdin))
{
int i=0;
   i= mq_send(serverid,client_queue_name,strlen(client_queue_name),0);
   
    if (i!=0)
    {
      printf("error is %s",strerror(errno));
      printf("Not able to send request to server");
      printf("%s",client_queue_name);
      sleep(5);
      continue;
   }

// in_buffer will be filled by server with token number

   if(mq_receive(clientid,in_buffer,strlen(in_buffer),0)==-1)
   {
      printf("Failed to receive token from the server \n");
      sleep(5);
     continue; 
   }

   printf("The received token is %s",in_buffer);

   printf("Just press ENTER to send a request to server");
}
return 0;
}

