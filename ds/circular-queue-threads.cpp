#include<iostream>
#include<thread>
#include <mutex>
#define ARRSIZE 10
using namespace std;

std::mutex t;
std::conditional_variable cv;



class circularQueue
{
public:
	circularQueue(int size);
	~circularQueue();
	int enqueue(int val);
	int dequeue();
	void printQueue();
 	void listenqueue();
	void listdequeue();		
private:
	int *arr;
	int front;
	int rear;
};

void circularQueue::listenqueue()
{
enqueue(35);
enqueue(45);
enqueue(55);
enqueue(65);
enqueue(75);
cv.signal();
}


void circularQueue::listdequeue()
{
 dequeue();
 dequeue();
 dequeue();
 dequeue();
}


circularQueue::~circularQueue()
{
 delete[] arr;
}

circularQueue::circularQueue(int size)
{
 arr = new int[size];
 front=rear=-1;
}

//add elements from rear
int circularQueue::enqueue(int val)
{
	//check if array is full
	if( ((front==0)&&(rear==ARRSIZE-1)) || (rear+1 == front) )
	{
		 cout<<"circular buffer is full"<<endl;
		 return -1;
	}
	else if( front == -1)//its the first element
	{
		front=rear=0;
		arr[rear]=val;
	}	
	else if((front!=0)&&(rear==ARRSIZE-1))  //loopback condition
	{
		rear=0;
		arr[rear]= val;
	}
	else //normal case
	{
		rear++;
		arr[rear]=val;
	}
}

int circularQueue::dequeue()
{
	int result=0;
	cv.wait(m,)


	//check if its empty
	if (front == -1)
	{
	cout<<"Queue is empty"<<endl;
	return -1;
	}
	
	int val = arr[front];
	
	if(rear == front)
	{
        rear=front=-1;
	}	
	else if(front == ARRSIZE-1)
	{
	 front=0;
	}
	else
	{
	front++;
	}
}

void circularQueue::printQueue()
{
	if(front<=rear) //straight fwd
	{
		for (int i=front;i<=rear;i++)
		{
			cout<<arr[i]<<" ";
		}
		cout<<endl;
	}
	else //rear is behind front
	{	 	
		for (int i=front;i<=ARRSIZE-1;i++)
		{
			cout<<arr[i]<<" ";
		}
	
		for (int i=0;i<=rear;i++)
		{
			cout<<arr[i]<<" ";
		}
	}
}

class Base
{
public:
void operator()(int num)
{
cout<<"my name is vasant "<<num<<endl;
}
};

//lambda

//auto mylambda = [](){
//cout<<"this is a lambda"<<endl;
//};

int main()
{
circularQueue myqueue(10);

//std::thread t1(&circularQueue::enqueue,&myqueue,45);

std::thread t1(&circularQueue::listenqueue,&myqueue);

std::thread t2(&circularQueue::listdequeue,&myqueue);

//functor
//std::thread t1((Base()),10);
t1.join();
t2.join();
myqueue.printQueue();

//myqueue.enqueue(45);
//myqueue.enqueue(25);
//myqueue.printQueue();
//myqueue.dequeue();
//myqueue.printQueue();

return 0;
}

