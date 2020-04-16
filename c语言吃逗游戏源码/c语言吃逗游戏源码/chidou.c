

#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <bios.h>

#define LEFT 0x4b00
#define RIGHT 0x4d00
#define UP 0x4800
#define DOWN 0x5000
#define ESC 0x011b
#define ENTER 0x1c0b

/* 【自学去】网站收集 http://www.zixue7.com */

/*2墙壁,1可以移动地方,3自己,4敌人*/
int a[15][20]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	       2,1,1,1,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,2,
               2,1,2,2,2,1,1,2,1,1,0,0,0,1,1,4,1,1,0,2,
               2,1,1,0,2,1,1,2,0,1,1,2,2,2,2,2,0,0,0,2,
               2,4,1,0,2,1,1,2,1,1,1,0,1,1,1,1,0,1,1,2,
               2,1,2,1,2,1,1,2,1,3,2,2,1,1,1,1,2,2,1,2,
               2,1,2,1,2,1,1,1,1,1,1,1,1,0,0,0,1,1,1,2,
               2,1,2,1,0,1,1,1,1,2,1,0,1,2,2,2,1,1,1,2,
               2,1,0,1,0,1,2,1,1,2,1,0,1,2,1,1,4,1,1,2,
               2,1,0,2,0,1,2,1,1,2,1,0,1,2,1,1,1,1,1,2,
               2,1,0,2,1,1,2,1,1,2,1,0,2,2,1,0,0,0,1,2,
               2,1,1,2,1,1,2,1,1,2,1,0,2,1,1,2,2,1,1,2,
               2,1,2,2,1,2,2,1,1,1,1,0,1,4,1,2,0,0,1,2,
               2,1,0,0,0,0,0,4,0,1,1,0,1,1,1,1,0,0,1,2,
               2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};/*数组就是地图*/
struct play /*游戏中人物的结构体*/
{
 int x;
 int y;
};
struct play you,them[5];
int sum=0;/*统计吃的豆子个数,吃满50颗就算胜利*/
int xx[5][2];/*判定敌人方向用的结构体*/
int false=0;

void init();
void begin();
void play();
void win();
void fun(struct play *them);
void movethem(struct play *them);
void loseyes();
void drawblackdou(int x,int y);
void lose();
/*游戏玩法：当任意按下键时，游戏启动，敌人随机移动，自己开始躲避敌人和墙壁，尽可能多的吃豆豆*/
void play()
{
	int key,i;
	while(1)
	{       key=bioskey(2);
		while(!kbhit())				/*当无按键时敌人自己移动 */
		{
			setcolor(GREEN);/*重画敌人*/
			for(i=0;i<5;i++)
				circle(them[i].y*20+100,them[i].x*20+100,9);
				sleep(1);
				fun(them);/*处理敌人*/

			for(i=0;i<5;i++)
				if(them[i].x==you.x&&them[i].y==you.y)
					false=1;/*假如失败的话*/
		loseyes();/*判定是否失败*/
			if(false)
				break;
		}/*跳出while（！kbhit（））*/
	if(false)
		break;
	key=bioskey(0);
	setcolor(0);/*把自己原来位置的人给删除掉*/
	circle(100+you.y*20,100+you.x*20,9);
	if(key==ESC)
		break;
	else if(key==UP)/*这里开始的判定主要是是否吃到豆子和碰到墙壁*/
	{
		you.x--;
		if(a[you.x][you.y]==2)
			you.x++;
		else if(a[you.x][you.y]==0)
			drawblackdou(you.x,you.y);
	}
	else if(key==DOWN)
	{
		you.x++;
		if(a[you.x][you.y]==2)
			you.x--;
		else if(a[you.x][you.y]==0)
			drawblackdou(you.x,you.y);
	}
   else if(key==RIGHT)
    {
	   you.y++;
	   if(a[you.x][you.y]==2)
		   you.y--;
     else if(a[you.x][you.y]==0)
		drawblackdou(you.x,you.y);
   }
   else if(key==LEFT)
    {
	   you.y--;
	   if(a[you.x][you.y]==2)
		   you.y++;
     else if(a[you.x][you.y]==0)
		drawblackdou(you.x,you.y);
   }
   if(sum==50)
      break;
  setcolor(RED);/*执行了一次键盘后再画出自己的位置*/
  circle(100+you.y*20,100+you.x*20,9);
  loseyes();/*自己走上去碰到敌人的可能*/
   if(false)
    break;
 }

}
void fun(struct play *them)/*移动中的判定*/
{
 int i;
 setcolor(0);/*把敌人的老位置删除*/
   for(i=0;i<5;i++)
    circle(them[i].y*20+100,them[i].x*20+100,9);
  movethem(them);/*根据控制者的位置来决定敌人的移动方向*/
}


void lose()/*输的画面*/
{
	cleardevice();
	settextstyle(0,0,4);
	while(!kbhit())
	{
		setcolor(rand()%13+1);
		outtextxy(180,200,"GAME OVER!");
		delay(3);
	}

}
void win()/*赢的画面*/
{
	cleardevice();
	settextstyle(0,0,4);
	while(!kbhit())
	{
		setcolor(rand()%13+1);
		outtextxy(200,200,"YOU WIN!");
		delay(3);
	}

}
void drawblackdou(int x,int y)/*吃豆子*/
{
	setcolor(0);
	circle(100+y*20,100+x*20,3);/*画圆x，y，半径*/
	sum++;/*吃到豆子后就加一*/
	a[x][y]=1;/*吃到后这里就成为普通平地*/
}
void loseyes()/*判断是否失败*/
{
	int i;
	for(i=0;i<5;i++)
    if(them[i].x==you.x&&them[i].y==you.y)
		false=1;/*假如失败的话*/


}
void movethem(struct play *them)/*them的移动过程*/
{
	int i,loop;
	randomize();/*随机排列，任意打乱*/
	for(i=0;i<5;i++)
	{
		/*只要控制者在身边就立即靠上去*/
		if(you.x==them[i].x&&(them[i].y+1)==you.y)
			them[i].y++;
		else if(you.x==them[i].x&&(them[i].y-1)==you.y)
			them[i].y--;
		else if(you.y==them[i].y&&(them[i].x+1)==you.x)
			them[i].x++;
		else if(you.y==them[i].y&&(them[i].x-1)==you.x)
			them[i].x--;
		else
		{
		loop:
			xx[i][0]=rand()%4+1;/*这里的方向采取随机赋值,原则是新的方向不可以和原来的方向相反*/
			if(xx[i][0]==1&&xx[i][1]==2||xx[i][0]==2&&xx[i][1]==1)
				goto loop;
			if(xx[i][0]==3&&xx[i][1]==4||xx[i][0]==4&&xx[i][1]==3)
				goto loop;
			xx[i][1]=xx[i][0];
			if(xx[i][0]==1)/*四个方向*/
			{
				them[i].x--;
				if(a[them[i].x][them[i].y]==2)/*假如碰墙壁的话就回到原来的地方等待随机的方向*/
				{
					them[i].x++;
					goto loop;
				}
			}
			else if(xx[i][0]==2)
			{
				them[i].x++;
				if(a[them[i].x][them[i].y]==2)
				{
					them[i].x--;
					goto loop;
				}
			}
			else if(xx[i][0]==3)
			{
				them[i].y++;
				if(a[them[i].x][them[i].y]==2)
				{
					them[i].y--;
					goto loop;
				}
			}
			else if(xx[i][0]==4)
			{
				them[i].y--;
				if(a[them[i].x][them[i].y]==2)
				{
					them[i].y++;
					goto loop;
				}
			}
		}
	}
}



void begin()
{
	/*setbkcolor(WHITE);*/
	int i,j;
	sleep(1);
	for(i=0;i<15;i++)
		for(j=0;j<20;j++)
			if(a[i][j]==2)/*代表墙壁*/
			{
				setfillstyle(SOLID_FILL,9);
				bar(100+j*20-10,100+i*20+10,100+j*20+10,100+i*20-10);
			}
			else if(a[i][j]==3)/*代表自己*/
			{
				setcolor(RED);
				circle(100+j*20,100+i*20,9);
			}
			else if(a[i][j]==4)/*代表敌人*/
			{
				setcolor(GREEN);
				circle(100+j*20,100+i*20,9);

			}
			else if(a[i][j]==0)/*代表豆子*/
			{
				setcolor(YELLOW);
				setlinestyle(0,0,1);
				circle(100+j*20,100+i*20,3);
			}
	you.x=5;you.y=9;/*自己和敌人的初始坐标*/
	them[0].x=2;them[0].y=15;
	them[1].x=4;them[1].y=1;
	them[2].x=8;them[2].y=16;
	them[3].x=12;them[3].y=13;
	them[4].x=13;them[4].y=7;


}
void init()/*是否开始游戏*/
{
	setcolor(3);
	setlinestyle(DASHED_LINE, 0, 3);							/*设置线的宽度和形式*/
	rectangle(100, 100, 550, 350);								/*画矩形*/


	settextstyle(3,0,3);
	outtextxy(200,200,"GAME START!");
	settextstyle(3,0,3);
	outtextxy(110,300,"ESC-exit/press any key to continue");
	 getch();
}

main()
{
	int gd=DETECT,gm;
	int key;
	initgraph(&gd,&gm,"");/*图形界面初始化*/
	init();/*调用初始化函数显示进入游戏初始界面*/
	key=bioskey(0);/*接收键盘按键*/
	if(key==ESC)
		exit(0);
	else
	{
		cleardevice();
		begin();

		play();/*编写游戏实现过程*/


		if(sum==50)/*吃满豆子了*/
		{
			win();
			getch();
		}
		if(false)
		{
			lose();
			getch();

		}

	}
closegraph();
	

}
