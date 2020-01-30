#include<iostream>
using namespace std;

class Node
{
	int x;
	int y;
	Node *link;
	
	public:
	Node(int ix,int iy)
	{
		x=ix;
		y=iy;
		link=nullptr;
	}
	
	int getx()
	{
		return x;
	}
	void setx(int x)
	{
		this->x=x;
	}
	int gety()
	{
		return y;
	}
	void sety(int y)
	{
		this->y=y;
	}
	
	Node* getLink()
	{
		return link;
	}
	void setLink(Node* x)
	{
		link=x;
	}
};

class LL
{
	public:
	Node* head;
	LL()
	{
		head=nullptr;
	}
	
	void insert(int x,int y)
	{
		Node* mynode=new Node(x,y);
		Node* temp=head;
		head=mynode;
		head->setLink(temp);
	}
	
	void del()
	{
		if(head->getLink()!=nullptr)
		{
			Node* cur=head;
			Node* par=head;
			while(cur->getLink()!=nullptr)
			{
				par=cur;
				cur=cur->getLink();
			}
			par->setLink(nullptr);
			delete cur;
		}
	}
//	For Debugging:
//	void showList()
//	{
//		Node* cur=head;
//		while(cur->getLink()!=nullptr)
//		{
//			cout<<cur->getx()<<" "<<cur->gety()<<" --> ";
//			cur=cur->getLink();
//		}
//		cout<<cur->getx()<<" "<<cur->gety()<<endl;
//	}
	
	int* show(int l)
	{

		int* arr=new int[2*l];
		int i=0;
		Node* cur=head;
		while(cur!=nullptr)
		{
			arr[i]=cur->getx();
			arr[i+1]=cur->gety();
			i+=2;
			cur=cur->getLink();
		}
		return arr;
	}
	
	~LL()
	{
		Node* temp=head;
		while(head!=nullptr)
		{
			temp=head->getLink();
			delete head;
			head=temp;
		}
	}
};
