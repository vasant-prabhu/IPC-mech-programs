// This is the server which will issue Airplane seat tokens on request to clients.
// Once it receives a request , it will place the token onto the client's message queue.
// Client will communicate its message queue name to server.
//************************JAI SHRI RAM*******************************************

//Step 1:- Create a message queue for the server

#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define SERVER_MSG_QUEUE "/server-queue"

int main()
{

mqd_t serverid,clientid;

long int token_counter=1;

struct mq_attr attr;

attr.mq_flags=0;
attr.mq_maxmsg=10;
attr.mq_msgsize=255;
attr.mq_curmsgs=0;

if (serverid=mq_open(SERVER_MSG_QUEUE,O_CREAT|O_RDONLY,0660,&attr)==-1)
{
printf("Error creating server message queue\n");
exit(-1);
}

//Step 2: Now the clients will want to contact the server for tokens
char in_buffer[265];
char out_buffer[265];

while (1)
{
   //Receive the name of the client in in_buffer

   if(mq_receive(serverid,in_buffer,strlen(in_buffer),0)==-1)
   {
      printf("server: recd name %s",in_buffer);
      printf("Failed to receive request from client\n");
      sleep(5);
     continue; 
   }

   //Now that we have received a request from client , issue the token
   //by writing into its message queue

   clientid=mq_open(in_buffer,O_WRONLY);

   sprintf(out_buffer,"%ld",token_counter);

   if (mq_send(clientid,out_buffer,strlen(out_buffer),0)==-1)
   {
      printf("Failed to send the message to client");
   }
   token_counter++;
}
return 0;
}

