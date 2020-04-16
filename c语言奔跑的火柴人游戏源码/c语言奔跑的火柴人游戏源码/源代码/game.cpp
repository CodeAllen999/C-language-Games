#include <iostream>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include <time.h>

using namespace std;

/* 【自学去】网站收集 http://www.zixue7.com */

/******全局变量******/
#define STEPDISTANCE	6		// 一步的距离。数值越大，移动速度越快
#define JUMPSPEED		10		// 数值越小，跳得越远
#define ROLLDISTANCE	30		// 滚动的总步数。数值越大，滚得越远

/******全局变量******/
int s_v		= STEPDISTANCE;		//障碍物和人物移动速度
int p_v		= JUMPSPEED;		//人物跳跃速度
int score	= 0;				//分数
int	max_s	= 0;
char keydown;					//按键值

/********************/
void move();
void Login();

/*************************************障碍物类****************************************/
// 障碍物
class zhangai
{
public:
	int left;
	int top;
	int right;
	int bottom;
	int r;
public:
	void draw(int l, int t, int r, int b);	// 绘制障碍物
	void style();							// 障碍物类型
	
} s1, s2, s3;

// 障碍物类型
void zhangai::style()
{
	int a;
	srand((unsigned int) time(NULL));
	a = rand() % 5 + 1;
	switch(a)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			top = 330;
			bottom = 361;
			break;
		case 5:
			top = 260;
			bottom = 291;
			break;
	}
}

//障碍物初始化
void zhangai::draw(int l,int t,int ri,int b)
{
	left=l;
	top=t;
	right=ri;
	bottom=b;
	solidrectangle(l, t, ri, b);
}

/**************************************人物类***********************************/
class people
{
public:
	int i;					// 控制人物移动帧数
	int b;					// 控制人物滚动帧数
	int b1;					// 控制人物滚动时间
	int j;					// 人物跳跃上升的速度
	int k;					// 人物下降的速度
	int left;
	int top;
	int right;
	int bottom;

private:
	IMAGE img1[8];			// 人物图像
	IMAGE img2[8];			// 滚动图像
	IMAGE img3;				// 跳跃图像

public:
	people();				// 构造函数
	void jump();			// 人物跳跃
	void move();			// 人物移动
	void roll();			// 人物滚动
	bool impact(zhangai *ps);			// 碰撞
} p;

// 构造函数
people::people()
{
	// 加载跑动图像
	loadimage(&img1[0], _T("rc\\picture\\move8_1.jpg"), 70, 100);
	loadimage(&img1[1], _T("rc\\picture\\move8_2.jpg"), 70, 100);
	loadimage(&img1[2], _T("rc\\picture\\move8_3.jpg"), 70, 100);
	loadimage(&img1[3], _T("rc\\picture\\move8_4.jpg"), 70, 100);
	loadimage(&img1[4], _T("rc\\picture\\move8_5.jpg"), 70, 100);
	loadimage(&img1[5], _T("rc\\picture\\move8_6.jpg"), 70, 100);
	loadimage(&img1[6], _T("rc\\picture\\move8_7.jpg"), 70, 100);
	loadimage(&img1[7], _T("rc\\picture\\move8_8.jpg"), 70, 100);

	// 加载滚动图像
	loadimage(&img2[0], _T("rc\\picture\\gun8_1.jpg"), 50, 50);
	loadimage(&img2[1], _T("rc\\picture\\gun8_2.jpg"), 50, 50);
	loadimage(&img2[2], _T("rc\\picture\\gun8_3.jpg"), 50, 50);
	loadimage(&img2[3], _T("rc\\picture\\gun8_4.jpg"), 50, 50);
	loadimage(&img2[4], _T("rc\\picture\\gun8_5.jpg"), 50, 50);
	loadimage(&img2[5], _T("rc\\picture\\gun8_6.jpg"), 50, 50);
	loadimage(&img2[6], _T("rc\\picture\\gun8_7.jpg"), 50, 50);
	loadimage(&img2[7], _T("rc\\picture\\gun8_8.jpg"), 50, 50);

	// 加载跳跃图像
	loadimage(&img3, _T("rc\\picture\\move8_5.jpg"), 70, 100);
}

//人物跳跃
void people::jump()
{
	if(j >= 70)			//上升
	{
		putimage(left,j, &img3);
		clearrectangle(40,j+100,120,j+120);
		p.top = j;
		p.bottom = p.top  + 120;
		j=j-p_v;
		k=j;
	}
	else if(k <= 240)		//下降
	{
		putimage(left,k+20, &img3);
		clearrectangle(40,70,120,k+20);
		p.top = k;
		p.bottom = p.top  + 120;
		k=k+p_v;
	}
}

//人物移动
void people::move()
{
	putimage(50, 260, &img1[p.i]);
	p.left	= 50;
	p.top	= 240;
	p.right	= p.left + 65;
	p.bottom= p.top  + 120;
	p.i++;				// 改变人物帧数
	if(p.i == 8)		// 人物循环移动
	{
		p.i = 0;
	}
}

//人物滚动
void people::roll()
{
	putimage(50, 300, &img2[p.b]);
	p.left=50;
	p.top =300;
	p.right = p.left + 50;
	p.bottom = p.top + 50;
	p.b1++;
	p.b++;				// 改变人物滚动帧数
	if(p.b==8)			// 人物循环滚动
	{
		p.b=0;
	}
}

// 返回是否与指定障碍发生碰撞
bool people::impact(zhangai *ps)
{
	return (max(left, ps->left) < min(right, ps->right) && max(top, ps->top) < min(bottom, ps->bottom));
}

/*************************函数********************************/
// 随机障碍
void zhangai_rnd()
{
	s1.r=rand() % 200 + 200;
	s2.r=rand() % 200 + 200;
	s3.r=rand() % 200 + 200;
}

// 初始化障碍
void chushi()
{
	s1.left = 640;
	s2.left = s1.left + s1.r;
	s3.left = s2.left + s2.r;
	s1.style();
	s2.style();
	s3.style();
}

// 绘制障碍
void show_zhangai()
{
	s1.draw(s1.left, s1.top, s1.left + 40, s1.bottom);
	s2.draw(s2.left, s2.top, s2.left + 40, s2.bottom);
	s3.draw(s3.left, s3.top, s3.left + 40, s3.bottom);
}

// 删除障碍
void delete_zhangai()
{
	clearrectangle(s1.left, s1.top, s1.left+40, s1.bottom);
	clearrectangle(s2.left, s2.top, s2.left+40, s2.bottom);
	clearrectangle(s3.left, s3.top, s3.left+40, s3.bottom);
}

// 障碍物循环
void xunhuan()
{
	if(s1.left+40<=0)
	{
		s3.r = rand() % 200 + 200;
		s1.left = s3.left + s3.r;
		s1.style();
	}
	else if(s2.left+40<=0)
	{
		s1.r = rand() % 200 + 200;
		s2.left = s1.left + s1.r;
		s2.style();
	}
	else if(s3.left + 40 <= 0)
	{
		s2.r = rand() % 200 + 200;
		s3.left = s2.left + s2.r;
		s3.style();
	}
}

// 设置障碍移动速度
void set_speed()
{
	s1.left -= s_v;
	s2.left -= s_v;
	s3.left -= s_v;
}

// 重新游戏初始化
void game_again()
{
	score = 0;
	s_v = STEPDISTANCE;
	p_v = JUMPSPEED;
	cleardevice();
	solidrectangle(0, 360, 640, 400);
	move();
}

// 储存成绩
void gave_score()
{
	ofstream outfile("score.txt", ios::out);
	if(!outfile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	outfile << score << " ";
	outfile.close();
}

// 读取最高分
void max_score()
{
	int value;
	ifstream infile("score.txt", ios::in);
	
	if(!infile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	infile>>value;
	infile.close();
	max_s = value;
}

// 改变最高分
void change_score()
{
	int value;
	ifstream infile("score.txt", ios::in);
	
	if(!infile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	infile>>value;
	infile.close();
	if(score>value)
	{
		gave_score();
	}
}

// 游戏结束
void game_over()
{
	FlushMouseMsgBuffer();		//清空鼠标缓存区
	change_score();
	Sleep(1000);
	p.i = 0;
	cleardevice();

	Login();
}

// 碰撞
void pengzhuang()
{
	// 指向当前障碍的指针
	zhangai *ps;

	// 获取当前障碍
	ps = &s1;
	if (s2.left < ps->left)	ps = &s2;
	if (s3.left < ps->left)	ps = &s3;

	// 检测碰撞
	if (p.impact(ps))
	{
		p_v = 0;
		s_v = 0;
		game_over();
	}
}

/******************************************************************************************/
// 移动
void move()
{
	keydown=' ';				// 清空键盘缓存区
	setfillstyle(BS_SOLID);		// 设置绘图样式
	cleardevice();	
	solidrectangle(0, 360, 640, 400);
	char s[10];
	char max[10];
	char ss[] = "分数:0";
	char sss[] = "最高分:";
	max_score();				// 最高分
	settextcolor(BLUE);
	sprintf(max, "%d", max_s);	// 数值格式化
	outtextxy(490, 40, max);		// 输出最高分
	outtextxy(58, 40, ss);
	outtextxy(400, 40, sss);
	p.i  = 0;
	p.b  = 0;
	p.b1 = 0;
	p.j  = p.k = p.top = 240;
	p.left = 50;
	zhangai_rnd();
	chushi();
	IMAGE img1;
	loadimage(&img1, _T("rc\\picture\\move8_1.jpg"),70,100);
	putimage(50,260, &img1);
	while(true)
	{
		keydown=getch();
		
		while(!kbhit())
		{
			sprintf(s,"%d",score);
			
			outtextxy(120,40,s);
			
			show_zhangai();
			
			if(keydown == 'w')
			{
				p.i = 0;
				p.b1 = 0;
				p.jump();
				if(p.k > 240)
				{
					keydown = ' ';
					p.j = 240;
				}
			}
			else if(keydown == 's')
			{
				if(p.b1 == 0)
					clearrectangle(50, 240, 120, 361);

				if(p.k >= 240)
					p.roll();
				else
					keydown='w';
			}
			else
			{
				if(p.k >= 240)
					p.move();
				else
					keydown = 'w';

				if(p.b1 == 0)
					p.move();
				else
					keydown = 's';
			}
			
			if(p.b1 >= ROLLDISTANCE)
			{
				p.b1 = 0;
				keydown = ' ';
				p.b = 0;
			}
			
			Sleep(20);
			
			pengzhuang();
			
			delete_zhangai();
			
			set_speed();
			
			score++;		// 分数
			
			xunhuan();		// 障碍物循环移动 
		}
	}
}

// 登录界面
void Login()
{
	setfillstyle(BS_SOLID);
	setbkcolor(LIGHTBLUE);
	char s[]	= "开始游戏";
	char ss[]	= "退出游戏";
	char sss[]	= "游戏说明: W 键 = 跳跃   S 键 = 滚动";
	
	MOUSEMSG m;
	solidrectangle(240, 100, 380, 150);
	solidrectangle(240, 160, 380, 210);
	settextcolor(BLUE);					// 设置字体颜色
	
	outtextxy(260, 113, s);
	outtextxy(260, 173, ss);
	
	setbkcolor(WHITE);
	outtextxy(110, 250, sss);
	
	setfillcolor(LIGHTBLUE);
	
	solidrectangle(0, 360, 640, 400);
	
	while(true)
	{
		m = GetMouseMsg();				// 判断是否按下鼠标
		if(m.x >= 240 && m.x <= 380 && m.y >= 100 && m.y <= 150)
		{
			setlinecolor(RED);			// 选中框框线条颜色
			rectangle(235, 95, 385, 155);
			if(m.uMsg==WM_LBUTTONDOWN )
			{
				clearrectangle(240, 100, 380, 150);
				clearrectangle(240, 160, 380, 210);
				setbkcolor(WHITE);
				cleardevice();
				game_again();
			}
		}
		else if(m.x >= 240 && m.x <= 380 && m.y >= 160 && m.y <= 210)
		{
			setlinecolor(RED);			// 选中框框线条颜色
			rectangle(235, 155, 385, 215);
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				exit(1);
			}
		}
		else
		{
			setlinecolor(WHITE);
			rectangle(235, 95,  385, 155);
			rectangle(235, 155, 385, 215);
		}
	}
}

/***********************************************************************/
// 界面初始化
void UI()
{
	initgraph(640, 400);				// 窗口初始化大小
	setbkcolor(WHITE);					// 设置背景颜色
	cleardevice();
	setlinecolor(BLACK);				// 设置绘图颜色
	settextcolor(BLACK);				// 设置文字颜色
	setfillcolor(LIGHTBLUE);			// 设置填充颜色
	settextstyle(25, 0, _T("宋体"));	// 字体样式大小
	srand((unsigned int) time(NULL));	// 设置随机种子
}

/*******************************主函数**********************************/
void main()
{
	UI();					// 界面初始化
	Login();				// 登录界面
	getch();				// 按任意键继续
	closegraph();			// 关闭图形界面
}
