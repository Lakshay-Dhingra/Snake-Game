#include<iostream>
#include<conio.h>
#include <unistd.h>
#include<cstdlib>
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

		int* arr=new int(2*l);
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

class Snake
{
	int length;
	LL* mysnake;
	
	public:
	Snake(int l,int x,int y)
	{
		mysnake=new LL();
		for(int i=0;i<l;i++)
		{
			mysnake->insert((x+i),y);
		}
		length=l;
	}
	
	int getLength()
	{
		return length;
	}
	
	void eatFood(int x,int y)
	{
		length+=1;
		mysnake->insert(x,y);
	}
	
	int* showSnake()
	{
		return mysnake->show(length);
	}
	
	int getHeadX()
	{
		return mysnake->head->getx();
	}
	int getHeadY()
	{
		return mysnake->head->gety();
	}
};

class Window
{
	int length;
	int hieght;
	Snake* snk;
	int* arr;
	
	public:
	Window(int l,int h,int posx,int posy)
	{
		
		length=l;
		hieght=h;
		snk=new Snake(4,posx-3,posy);
		arr=snk->showSnake();
		
//		rungame();
//		For Debugging:
//		for(int i=0;i<2*(sk.getLength());i++)
//		{
//			cout<<arr[i]<<" ";
//		}
	}
	
	void rungame()
	{
		char ch;
		while(true)
		{
			if(kbhit())
			{
			ch = _getch();
			if(int(ch)==27)
				break;
//			else if(int(ch)==-32||int(ch)==0)
//			{	
//				switch(_getch())
//		    	{
//		        	case 72:
//		        	//cout<<"UP";
//		        	snk->eatFood(snk->getHeadX(),snk->getHeadY()+1);
//		        	break;
//		
//		        	case 80:
//		        	//cout<<"DOWN";
//		        	z=80;
//		        	y++;
//					break;
//		        
//					case 75:
//		            //cout<<"LEFT";
//		            z=75;
//		            x--;
//					break;
//		
//		        	case 77:
//		        	z=77;
//		        	//cout<<"RIGHT";
//		            x++;
//					break;
//		    	}
//			}
			}
			draw();
		}
	}
	
	void draw()
	{
//		system("cls");
//		arr=snk->showSnake();
//		cout<<"world ";
		bool flag;
		for(int i=0;i<length;i++)
		{
			for(int j=0;j<hieght;j++)
			{
				flag=0;
				if(i==0||i==length-1||j==0||j==hieght-1)
				{
					cout<<"#";
					flag=1;
				}
				else
				{
					for(int k=0;k<snk->getLength();k++)
					{
						if(i==arr[2*k]&&j==arr[2*k+1])
						{
							cout<<"O";
							flag=1;
						}
					}
				}

				if(flag==0)
				{
					cout<<" ";
				}
			}
			cout<<endl;
		}
//		For Debugging:
//		for(int k=0;k<snk->getLength();k++)
//			cout<<arr[2*k]<<" "<<arr[2*k+1]<<" ";
		usleep(100000);
	}
};

int main()
{
	Window win(30,50,15,25);
//	cout<<"hello ";
	win.rungame();
	return 0;
}
