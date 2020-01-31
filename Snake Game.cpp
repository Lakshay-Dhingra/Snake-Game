#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include "LinkedList.h"	//My user-defined header file for linked list
#include <windows.h>
using namespace std;

// NOTE:
// 1. I've assumed x-axis as vertically downward and y-axis horizontally toward right
// 2. Run this code along with command -std=c++11


class Food
{
	public:
	int foodx;
	int foody;
	void genFood(int l,int h)	//To Generate Random Food For Snake To Eat
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
	Snake(int l,int x,int y)	//Constructor that creates a linked list for snake with initial lenght l at postion (x,y)
	{
		mysnake=new LL();
		for(int i=0;i<l;i++)
		{
			mysnake->insert((x+i),y);
		}
		length=l;
	}
	
	int getLength() //Returns Length of Snake
	{
		return length;
	}
	
	void eatFood(int x,int y)	//Increases snakes length at head when it eats food
	{
		length+=1;
		mysnake->insert(x,y);
	}
	
	void move(int x,int y)	//To move the snake
	{
		mysnake->insert(x,y);
		mysnake->del();
	}
	
	int* showSnake()	//Returns an array containing x and y corrdinates of snake
	{
		return mysnake->show(length);
	}
	
	int getHeadX()		//Returns x coordinate of snake's head
	{
		return mysnake->head->getx();
	}
	int getHeadY()		//Returns y coordinate of snake's head
	{
		return mysnake->head->gety();
	}
};

class Window
{
	int length;	//vertical length
	int hieght;	//horizontal hieght
	int snk_direction;	//Current direction of movement of snake
	Snake* snk;	//Stores Snake object which is to be shown in the window
	Food* fd;	//Stores Food object which is to be shown in the window
	int* arr;	//Snake's x and y coordinates in array
	int score;
	
	public:
	Window(int l,int h,int posx,int posy)	//Constructor
	{
		length=l;
		hieght=h;
		snk_direction=80;
		snk=new Snake(4,posx-3,posy);
		fd=new Food();
		score=0;
	}
	
	void rungame()	//Runs the actual game 
	{
		char ch;
		fd->genFood(length,hieght);		//To generate new food for the first time
		while(true)
		{
			if(kbhit())				//Takes input from the user and performs required operation
			{
				ch = _getch();
				if(int(ch)==27)		//27--> ascii for ESC key
					break;
				else if(int(ch)==-32||int(ch)==0)	//when an arrow key is pressed
				{	
					switch(_getch())	//checks which arrow key is pressed and sets the snake direction accordingly
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
			else	//If no key is pressed keep snake moving in its initial direction
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
			
			if(snk->getHeadX()==0||snk->getHeadX()==length-1||snk->getHeadY()==0||snk->getHeadY()==hieght-1)	//When snake hits boundary
			{
				break;
			}
			if(snk->getHeadX()==fd->foodx && snk->getHeadY()==fd->foody)	//When snake eats food
			{
				score+=10;
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
			draw();		//To display snake on screen
			Sleep(2);	//To give a delay of 2msec
		}
	}
	
	void draw()		//To draw the actual snake game on screen
	{
		system("cls");	//To clear the screen
		arr=snk->showSnake();	//To get the updated snake coordinates
		bool flag;
		for(int i=0;i<length;i++)
		{
			for(int j=0;j<hieght;j++)
			{
				flag=0;
				if(i==0||i==length-1||j==0||j==hieght-1)
				{
					cout<<"#";	//Boundary
					flag=1;
				}
				else
				{
					for(int k=0;k<snk->getLength();k++)
					{
						if(i==arr[2*k]&&j==arr[2*k+1])
						{
							if(k==0)
								cout<<"@";	//Snake head
							else
								cout<<"0";	//Snake body
							flag=1;
						}
					}
				}
				if(i==fd->foodx&&j==fd->foody)
				{
					cout<<"+";	//snake food
					flag=1;
				}
				if(flag==0)
				{
					cout<<" ";	//Empty space
				}
			}
			cout<<endl;
		}
		cout<<"Score: "<<score;
	}
};

int main()
{
	char ch,ch2;
	cout<<"\n\tWelcome To The Snake Game!\n"<<endl;
	cout<<"Instructions:"<<endl;
	cout<<"1. Fullscreen the console window for better experience."<<endl;
	cout<<"2. Use arrow keys to move the snake."<<endl;
	cout<<"3. Press Esc to exit the game."<<endl;
	cout<<"4. Press Space to start the game."<<endl;
	
	while(true)
	{
		if(kbhit())
		{
			ch = _getch();
			if(int(ch)==32)		//32-->ascii for Space
			{
				Window win(40,80,20,40);
				win.rungame();
				cout<<"\nGame Over!"<<endl<<"Press Space Key to play again..."<<endl<<"Press Esc Key to exit...";
			}
			else if(int(ch)==27)
			{
				break;
			}
		}
	}
	return 0;
}
