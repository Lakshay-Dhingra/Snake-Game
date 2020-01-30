#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include "LinkedList.h"
#include <windows.h>
using namespace std;

class Food
{
	public:
	int foodx;
	int foody;
	void genFood(int l,int h)
	{
		srand(time(0));
		foodx=(rand()%(l-2))+1;
		foody=(rand()%(h-2))+1;
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
	
	void move(int x,int y)
	{
		mysnake->insert(x,y);
		mysnake->del();
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
	int snk_direction;
	Snake* snk;
	Food* fd;
	int* arr;
	
	public:
	Window(int l,int h,int posx,int posy)
	{
		
		length=l;
		hieght=h;
		snk_direction=80;
		snk=new Snake(4,posx-3,posy);
		fd=new Food();
//		arr=snk->showSnake();
		
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
		fd->genFood(length,hieght);
		while(true)
		{
			if(kbhit())
			{
				ch = _getch();
				if(int(ch)==27)
					break;
				else if(int(ch)==-32||int(ch)==0)
				{	
					switch(_getch())
			    	{
			        	case 72:
			        	//cout<<"UP";
			        	if(snk_direction!=80)
			        	{
			        		snk_direction=72;
			        		snk->move(snk->getHeadX()-1,snk->getHeadY());
						}
			        	break;
			
			        	case 80:
			        	//cout<<"DOWN";
			        	if(snk_direction!=72)
			        	{
			        		snk_direction=80;
			        		snk->move(snk->getHeadX()+1,snk->getHeadY());
						}
						break;
		        
						case 75:
			            //cout<<"LEFT";
			            if(snk_direction!=77)
			        	{
			        		snk_direction=75;
			        		snk->move(snk->getHeadX(),snk->getHeadY()-1);
						}
						break;
			
			        	case 77:
			        	//cout<<"RIGHT";
			            if(snk_direction!=75)
			        	{
			        		snk_direction=77;
			        		snk->move(snk->getHeadX(),snk->getHeadY()+1);
						}
						break;
			    	}
				}
			}
			else
			{
				switch(snk_direction)
		    	{
		        	case 72:
		        	snk->move(snk->getHeadX()-1,snk->getHeadY());
		        	break;
		
		        	case 80:
		        	snk->move(snk->getHeadX()+1,snk->getHeadY());
		        	break;
	        
					case 75:
		            snk->move(snk->getHeadX(),snk->getHeadY()-1);
		        	break;
		
		        	case 77:
		            snk->move(snk->getHeadX(),snk->getHeadY()+1);
		        	break;
		    	}
				
			}
			if(snk->getHeadX()==0||snk->getHeadX()==length-1||snk->getHeadY()==0||snk->getHeadY()==hieght-1)
			{
				break;
			}
			if(snk->getHeadX()==fd->foodx && snk->getHeadY()==fd->foody)
			{
				switch(snk_direction)
		    	{
		        	case 72:
		        	snk->eatFood(fd->foodx-1,fd->foody);
		        	fd->genFood(length,hieght);
		        	break;
		
		        	case 80:
		        	snk->eatFood(fd->foodx+1,fd->foody);
		        	fd->genFood(length,hieght);
		        	break;
	        
					case 75:
		            snk->eatFood(fd->foodx,fd->foody-1);
		            fd->genFood(length,hieght);
		        	break;
		
		        	case 77:
		            snk->eatFood(fd->foodx,fd->foody+1);
		            fd->genFood(length,hieght);
		        	break;
		    	}
			}
			draw();
			Sleep(10);
		}
	}
	
	void draw()
	{
		system("cls");
		arr=snk->showSnake();
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
							if(k==0)
								cout<<"@";
							else
								cout<<"0";
							flag=1;
						}
					}
				}
				if(i==fd->foodx&&j==fd->foody)
				{
					cout<<"=";
					flag=1;
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
	}
};

int main()
{
	Window win(30,50,15,25);
	win.rungame();
	return 0;
}
