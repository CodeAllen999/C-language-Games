#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

/* 【自学去】网站收集 http://www.zixue7.com */

#define HMAX 22//边界高度的最大值
#define HMIN 3//边界高度的最小值
#define LMAX 37//边界长度的最大值
#define LMIN 2//边界长度的最小值

int mx=20,my=11;
int leave=1;//关卡
int x=20,y=20;//玩家位置
int i,j;
int m=10,n=15;//箱子位置
int pointx=20,pointy=13;//目标位置
char ch;

struct move//小球结构体
{
	int x,y;
	int xv,yv;
}ball;
/*----------------------------------------------------------------*/
bool judge();//判断条件的函数
void star();
void box(int m,int n);
void gotoxy(int x, int y);
void HideCursor();//隐藏光标
void tell(char s);//推箱子的关键函数
void goal();
void help();
void welcome();
void move(char ch);
void map();//地图界面
void clean(int x,int y);//擦出痕迹函数
void moveball();
void moveplay();
void GameOVER();//游戏结束图像
void GameJudge();//判断是否被球擦到
/*--------------------------------------------------------------*/
void player(int x,int y)//玩家
{
	gotoxy(x,y);
	printf("★");
}

void box(int m,int n)//创建一个箱子
{
	gotoxy(m,n);//箱子的位置
	printf("■");
}

void goal()//目标位置的函数
{

	if(judge())
	{
		srand(time(NULL));
		pointx=rand()%(36-4)+4;
		pointy=rand()%(21-5)+5;
	}
	gotoxy(pointx,pointy);
	printf("⊙");//目标点位置
}
/*--------------------------------------------------------------*/

bool judge()//判断条件。判断箱子是否到达指定地点
{
	if(pointx==m&&pointy==n)
		return true;
	else
		return false;
}

void condition(int m,int n)//初始化
{
	void goal();
	GameJudge();
	if(judge())
	{   
		leave++;
		system("cls");
		star();
	}
}


void star()
{
	map();
	gotoxy(20,1);
	printf("第%d关",leave);
	box(m,n);
	player(x,y);
	goal();
}
/*-----------------------------主函数---------------------------------*/
void main()
{
S:  system("color 4f");	//修改主界面的颜色
    welcome();
	HideCursor();
	char ch;
	while(1)
	{
		ch=getch();
		switch(ch)
		{
		case 'w':
		case 'W':
			clean(mx,my);
			my=my-3;
			if(my<11)
				my=my+6;
			gotoxy(mx,my);
			printf("★");
			break;
		case 's':
		case 'S':
			clean(mx,my);
			my=my+3;
			if(my>14)
				my=my-6;
			gotoxy(mx,my);
			printf("★");
			break;
        case '\r':
			if(my==11)
			{
				system("cls");
				HideCursor();
				system("color 2f");//修改游戏界面的颜色
				star();
				char ch;
				moveball( );
			}
			if(my==14)
			{
				system("cls");
				help();
				while(getch())
				{
					system("cls");
					goto S;//由于不懂如何返回一开始的界面所以只能用goto跳到一开始的界面
				}
				
			}
			break;
		}
	}
}
/*-----------------------------界面---------------------------------*/
void welcome()
{
	printf(" □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	printf(" □                                                                          □\n");
	printf(" □                ▁▂▃▄▅▆▇█推箱子改版█▇▆▅▄▃▂▁                □\n");
	printf(" □                                                                          □\n");
	printf(" □  ☆控制说明☆                                                            □\n");
	printf(" □                                                                          □\n");
	printf(" □        W ,S ,A ,D 分别控制上、下、左、右。                               □\n");
	printf(" □        回车键确认                                                        □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                               ┏━━━━━┓                             □\n");
	printf(" □                               ┃ 开 ★ 始 ┃                             □\n");
	printf(" □                               ┗━━━━━┛                             □\n");
	printf(" □                               ┏━━━━━┓                             □\n");
	printf(" □                               ┃ 帮    助 ┃                             □\n");
	printf(" □                               ┗━━━━━┛                             □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                        by：丿Sky灬夜丨殇 □\n");
	printf(" □                                                          QQ：598217213   □\n");
	printf(" □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	gotoxy(0,0);
}



void help()
{
	printf(" □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □            ▁▂▃▄▅▆▇█推箱子改版游戏说明█▇▆▅▄▃▂▁            □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □  ☆胜利条件☆                                                            □\n");
	printf(" □                                                                          □\n");
	printf(" □          把箱子推到圈里就过关                                            □\n");
	printf(" □          本游戏没有关数限制                                              □\n");
	printf(" □          直到你被小球打中或者擦到就退出游戏                              □\n");
	printf(" □          程序比较简单，所以没什么难度!!!!!                              □\n");
	printf(" □                                                                          □\n");
	printf(" □                      由于本人刚大一，刚刚学完数组                        □\n");
	printf(" □                 所以本程序还有很多不足的地方，望大家谅解                 □\n");
	printf(" □                         欢迎大家一起交流讨论                             □\n");
	printf(" □                                                                          □\n");
	printf(" □                            ☆☆☆☆☆☆☆                                □\n");
	printf(" □                            ☆任意键返回☆                                □\n");
	printf(" □                            ☆☆☆☆☆☆☆                                □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                        by：丿Sky灬夜丨殇 □\n");
	printf(" □                                                           2012年12月20日 □\n");
	printf(" □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	gotoxy(0,0);
}
/*-----------------------------界面---------------------------------*/

void gotoxy(int x, int y)
{
	COORD c;
	c.X = 2 * x, c.Y = y; //移动光标
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void HideCursor()//隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
/*---------------------------------------------------------------------------*/

void tell(char s)//推箱子的关键函数
{
	if(s=='w'||s=='W')
	{
		if(m==x&&n==y)
		{
			clean(m,n);
			n-=1;
			box(m,n);
		}
	}
	if(s=='s'||s=='S')
	{
		if(m==x&&n==y)
		{
			clean(m,n);
			n+=1;
			box(m,n);
		}
	}
	if(s=='a'||s=='A')
	{
		if(m==x&&n==y)
		{
			clean(m,n);
			m-=1;
			box(m,n);
		}
	}
	if((s=='d'||s=='D'))
	{
		if(m==x&&n==y)
		{
			clean(m,n);
			m+=1;
			box(m,n);
		}
	}
}

/*---------------------------------------------------------------------------*/
/*void move(char ch)//
{
	while(1)
	{
		moveball();/////////////////////////////////////////////////////////////////////
		//condition(m,n);
		//star();
	}	
}*/
/*---------------------------------------------------------------------------*/
void map()
{
	gotoxy(0,2);
	printf(" ◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎\n");
	printf(" ◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎                                                                      ◎◎\n");
	printf(" ◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎\n");
	printf(" ◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎\n");
	
}

/*---------------------------------------------------------------------------*/
void clean(int x,int y)
{
	gotoxy(x,y);
	printf(" ");
}


void moveball()//移动小球
{
	ball.x = 5;
	ball.y = 5;
	ball.xv = 1;
	ball.yv = 1;
	while(1)
	{
		condition(m,n);
		star();
		gotoxy(ball.x,ball.y);
		printf("  ");
		ball.x += ball.xv; 
		ball.y += ball.yv; 
		if(ball.y<=HMIN+1||ball.y>=HMAX-1)
		{
			ball.yv *= -1;
			printf("\a");
		}
		if(ball.x<=LMIN+1||ball.x>=LMAX-1)
		{
			ball.xv *= -1;
			printf("\a");
		}
		gotoxy(ball.x,ball.y);
		printf("●");
		Sleep(20);	
		moveplay();
	}
	
}

void moveplay()//移动玩家和箱子
{
	if(kbhit())
	{
		ch=getch();
		switch(ch)
		{
		case 'w':
		case 'W':
			if(y-1>HMIN&&y-1<HMAX)
			{
				clean(x,y);
				y-=1;
				tell(ch);
				box(m,n);
				player(x,y);
			}
			break;
		case 's':
		case 'S':
			if(y+1>HMIN&&y+1<HMAX)
			{
				clean(x,y);
				y+=1;
				tell(ch);
				box(m,n);
				player(x,y);
			}
			break;
		case 'a':
		case 'A':
			if(x-1>LMIN&&x-1<LMAX)
			{
				clean(x,y);
				x-=1;
				tell(ch);
				box(m,n);
				player(x,y);
			}
			break;
		case 'd':
		case 'D':
			if(x+1>LMIN&&x+1<LMAX)
			{
				clean(x,y);
				x+=1;
				tell(ch);
				box(m,n);
				player(x,y);
			}
			break;
		}
	}
}


void GameJudge()
{
	if(ball.x+1==x&&ball.y+1==y||ball.x+1==m&&ball.y+1==n)
	{
		system("cls");
		HideCursor();
		GameOVER();
	}
	if(ball.x-1==x&&ball.y+1==y||ball.x-1==m&&ball.y+1==n)
	{
		system("cls");
		HideCursor();
		GameOVER();
	}
	if(ball.x+1==x&&ball.y-1==y||ball.x-1==m&&ball.y+1==n)
	{
		system("cls");
		HideCursor();
		GameOVER();
	}
	if(ball.x-1==x&&ball.y-1==y||ball.x-1==m&&ball.y+1==n)
	{
		system("cls");
		HideCursor();
		GameOVER();
	}
}





void GameOVER()
{
	system("color 2B");
	printf(" □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                ☆☆☆☆☆☆☆你失败了☆☆☆☆☆☆☆                      □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                                          □\n");
	printf(" □                                                        by：丿Sky灬夜丨殇 □\n");
	printf(" □                                                          QQ：598217213   □\n");
	printf(" □□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	Sleep(500);
	exit(0);
}