#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>

/* 【自学去】网站收集 http://www.zixue7.com */

// 定义常量
#define NUM 10
#define	CMD_LEFT		1
#define	CMD_RIGHT		2
#define	CMD_QUIT		4

int box_x = 10;
int box_y = 420;

// 定义球的结构体
struct Ball
{
	int x, y, v;
};

// 获取用户控制
int GetCommand()
{
	int c = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)		c |= CMD_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)	c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)	c |= CMD_QUIT;

	return c;
}

// 倒计时
int Time(int t)
{
	char strsec[10];
	int sec = 20 - (GetTickCount() - t) / 1000;
	itoa(sec, strsec, 10);
	outtextxy(570, 110, "      ");
	outtextxy(570, 110, strcat(strsec, "s"));
	return sec;
}

// 介绍
void menu()
{
	line(449, 0, 449, 480);	
	char runTime[] = "游戏倒计时     : ", 
		 receiveBallNum[] = "接到的球的数量:", copyRight[] = "版权所有:圣石",
		 finishWorkDate[] = "完成日期:2012年12月1日", 
		 introductiona[] = "按方向键控制盒子移动接住", introductionb[] = "小球,倒计时为0时游戏结束";

	settextcolor(GREEN);
	outtextxy(450, 10, introductiona);
	outtextxy(450, 30, introductionb);
	outtextxy(450, 110, runTime);
	outtextxy(450, 210, receiveBallNum);
	outtextxy(450, 310, copyRight);
	outtextxy(450, 410, finishWorkDate);
}

// 产生随机球
void ballRandom(Ball ball[], int i)
{
	ball[i].x = 16 + 45 * i; 
	ball[i].y = 8 + rand() % 32;
	ball[i].v = 1 + rand() % 5;
}

// 画球，并计算得分
void calculateScore(Ball ball[], int &score)
{
	for(int i = 0; i < NUM; i++)
	{
		fillcircle(ball[i].x, ball[i].y, 8);
		if(ball[i].y >= 472)
		{
			ballRandom(ball, i);
			continue;
		}
		if(box_x + 8 <= ball[i].x && ball[i].x <= box_x + 72 && ball[i].y >= 412)
		{
			score++;
			ballRandom(ball, i);
		}
	}
}

// 主函数
int main()
{
	// 初始化
	initgraph(640, 480);
	srand(time(NULL));
	BeginBatchDraw();
	setlinecolor(GREEN);
	setfillcolor(WHITE);

	menu();

	Ball ball[NUM];
	int dx, i, c, score = 0;
	bool flag = true;

	for(i=0; i<NUM; i++)
	{
		ballRandom(ball, i);
	}

	int t = GetTickCount();
	char strScore[10], str[] = "your score:";
	
	// 游戏主循环
	while(flag)
	{
		dx = 0;

		// 显示得分
		char strScore[10];
		itoa(score, strScore, 10);
		outtextxy(570, 210, strScore);

		// 画球，并计算得分
		calculateScore(ball, score);

		// 画盒子
		fillrectangle(box_x, box_y, box_x+80, box_y+60);
		FlushBatchDraw();

		// 获取用户控制命令
		c = GetCommand();
		if (c & CMD_LEFT)	dx = -10;
		if (c & CMD_RIGHT)	dx = 10;
		if (c & CMD_QUIT)	flag = false;
		if (!Time(t)) flag = false;

		// 延时
		Sleep(25);

		// 擦除游戏区
		clearrectangle(0, 0, 448, 480);

		// 计算球的新坐标
		for(i = 0; i < NUM; i++)
		{
			ball[i].y += ball[i].v;
		}

		// 移动盒子
		box_x += dx;
		if(box_x < 0)   box_x = 0;
		if(box_x > 368) box_x = 368;
	}

	// 清空键盘缓冲区
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	// 输出游戏结果
	itoa(score, strScore, 10);
	outtextxy(222, 240, strcat(str, strScore));
	outtextxy(220, 300, "按任意键退出");
	EndBatchDraw();

	// 按任意键退出
	getch();
	closegraph();

	return 0;
}