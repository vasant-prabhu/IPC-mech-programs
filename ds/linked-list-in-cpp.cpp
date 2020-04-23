#include<iostream>

struct Node
{
	int data;
	Node *next;
};

class List
{
private:
//these are pointers to the head node 
Node *head;

public:
List(){head=nullptr;}
~List(){clear();}

void insertNode(int val);
void deleteNode(int val);
void deleteNodeAtPosition(int position);
void printList();
void clear();
};

void List::insertNode(int val)
{
	Node *newnode=new Node;//a physical node is created somewhere on the heap
	newnode->data=val;
	newnode->next=nullptr;
	if(head==nullptr)
	{
		//As this is 1st element , both pointers will point to the first element
		head = newnode;
	}
	else
	{
		Node *temp=head;
		while(temp->next!=nullptr)
		{
			temp=temp->next;
		}
		temp->next=newnode;		
	}		
}

//Linked list element with this value will be deleted
void List::deleteNode(int val)
{
	Node* temp= head; //create a temp variable to traverse the linked list
	Node* prev=head;//keeps track of prev node
	temp=temp->next;
	//Search for val
	while(temp->data!=val)
	{
		temp=temp->next;
		prev=prev->next;
	}
	if (temp->data==val)
	{
		prev->next=temp->next;
		delete temp;
	}
}


//Linked list element in this position will be deleted.Starts from 1 onwards
void List::deleteNodeAtPosition(int position)
{
	Node* temp= head; //create a temp variable to traverse the linked list
	Node* prev=head;//keeps track of prev node
	temp=temp->next;
	
	if(position==1)
	{
		head=temp;
		delete prev;
	}
	else
	{
		for(int i=2;i<position;i++)
		{
			temp=temp->next;
			prev=prev->next;
		}
		prev->next=temp->next;
		delete temp;
	}
}

void List::printList()
{
	Node *temp=head;
	while(temp!=NULL)
	{
		std::cout<<temp->data<<" ";
		temp=temp->next;
	}
}


void List::clear()
{
	//Delete the entire linked list
	if(head->next==nullptr)
	{
		delete head;
		return; 
	}
	Node *temp=head->next;
	while(temp!=nullptr)
	{
		delete head;
		head=temp;
		temp=temp->next;
	}
}

int main()
{
List obj1;
obj1.insertNode(12);
obj1.insertNode(14);
obj1.insertNode(21);
obj1.insertNode(32);
obj1.printList();
std::cout<<std::endl;
obj1.deleteNode(14);
obj1.printList();
obj1.deleteNodeAtPosition(1);
std::cout<<std::endl;
obj1.printList();
std::cout<<std::endl;
obj1.insertNode(82);
obj1.insertNode(62);
obj1.insertNode(52);
obj1.insertNode(42);
obj1.printList();
std::cout<<"delete 4th element"<<std::endl;
obj1.deleteNodeAtPosition(4);
obj1.printList();
//TODO reverse a linked list.
//TODO intersection of 2 linked list
//TODO detection of a loop in linked list-floyd algorithm


return 0;

}
