#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#define MAX 64				// 圆盘的最大数目
#define NULL 0

/* 【自学去】网站收集 http://www.zixue7.com */

// 定义栈
struct STKNODE
{
	int a[4];
};

struct STK 
{
	STKNODE*	stack[MAX];
	int			top;
};


// 定义全局变量
STK s[3];					// 声明三个栈，分别代表一号二号三号钢针上圆盘的状态
int v = 5;					// 调整速度
 


// 函数声明
void Initstk(STK* s);							// 初始化栈
void Hannoi(int n, char a, char b, char c);		// 汉诺塔递归
void start();									// 开始画面
void Move(int n, char a, char b);				// 移动过程
int switchab(char a);							// 返回钢针号
void adjust();									// 调整速度暂停



// 主函数
void main()
{
	int n, ta[4] = {115, 500, 285, 520};			// 第一个圆盘的位置
	printf("尽量小于16\n");							// 因为大于十六时就会显示有误，但程序可以正常运行
	printf("请输入汉诺塔的层数（1~64）：");
	scanf("%d", &n);
	STKNODE** p;
	p = (STKNODE**)malloc(n * sizeof(STKNODE **));	// 声明一个元素为 n 个的动态 STKNODE 型指针数组
	for (int i2 = 0; i2 < n; i2 ++)
	{
		p[i2] = (STKNODE *)malloc(sizeof(STKNODE));	// 为每一个指针申请空间
	} 
	Initstk(&s[0]);
	Initstk(&s[1]);
	Initstk(&s[2]);									// 将三个栈初始化
	start();										// 呈现开始画面
	setfillstyle(YELLOW);							// 圆盘的颜色
	for (int i=0; i < n; i++)
	{
		ta[0] += 5;
		ta[1] -= 20;
		ta[2] -= 5;
		ta[3] -= 20;
		bar(ta[0], ta[1], ta[2], ta[3]);			// 画出n个从大到小一次叠放的黄色圆盘
		++s[0].top;									// 进栈
		for (int i1 = 0; i1 < 4; i1++)
		{
			p[i]->a[i1] = ta[i1];
			s[0].stack[s[0].top] = p[i];			// 记录每个矩形的位置，top为圆盘的个数
		}
	}	
	Hannoi(n, 'a', 'b', 'c');						// 汉诺塔递归函数
	system("pause");
	printf("\t\t\t\tGame Over!\n");
}



///////////////////////////////////////////////////
// 函数定义

// 汉诺塔的递归
void Hannoi(int n, char a, char b, char c)  
{
	if(n == 1)
		Move(1, a, c);
	else
	{
		Hannoi(n-1, a, c, b);
		Move(n, a, c);
		Hannoi(n-1, b, a, c);
    }
}

// 栈的初始化
void Initstk(STK *s) 
{  
	int i;
	s->top = 0;
	for (i = 0; i <= MAX; i++)
		s->stack[++s->top] = NULL;
	s->top = 0;
}

// 移动过程
void Move(int n, char a, char b)
{
	int i3, i4 = 0, i5 = 0;					
	i3 = b - a;												// 目的钢针与源钢针的位置差值
	i4 = switchab(a);										// 源钢针钢针号
	i5 = switchab(b);										// 目的钢针号
	STKNODE *q1, *q0;										// 两个中间结点用于源栈和目的栈间的值得传递，q1为目的栈，q0为源栈
	q1 = (STKNODE *)malloc(sizeof(STKNODE));
	q0 = (STKNODE *)malloc(sizeof(STKNODE));

	// 源栈与目的栈值的传递
	q0 = s[i4].stack[s[i4].top];
	++s[i5].top;											// 进栈
	q1->a[0] = q0->a[0] + i3 * 200;
	q1->a[1] = 500 - s[i5].top * 20;
	q1->a[2] = q0->a[2] + i3 * 200;
	q1->a[3] = 500 - s[i5].top * 20 + 20;
	s[i5].stack[s[i5].top] = q1;
	--s[i4].top;											// 出栈

	// 向上运动
	while (q0->a[1] >= 100)
	{
		setfillstyle(YELLOW);
		bar(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		adjust();											// 调整函数
		Sleep(10 * v);										// 暂停（ms）
		setfillstyle(WHITE);
		bar(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		setcolor(RED);
		line((q0->a[0] + q0->a[2]) / 2, q0->a[1], (q0->a[0] + q0->a[2]) / 2, q0->a[3]);	// 重新画上被擦掉原有的红线
		q0->a[1] -= 10;
		q0->a[3] -= 10;
		if (s[i4].top == 0)									// 重新画上最后一个矩形块擦掉的底座上的两条红线
		{
			line(110 + i4 * 200, 500, 290 + i4 * 200, 500);
			line(110 + i4 * 200, 493, 290 + i4 * 200, 493);
		}
	}

	// 向左或右运动，与 i3 的正负有关
	while (q0->a[2] != q1->a[2])
	{
		setfillstyle(YELLOW);
		bar(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		adjust();
		Sleep(10 * v);
		setfillstyle(WHITE);
		bar(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		if (i3 < 0)											// i3<0向左移
		{
			q0->a[0] -= 20;
			q0->a[2] -= 20;
		} 
		else												// i3>0向右移
		{
			q0->a[0] += 20;
			q0->a[2] += 20;
		}
	}

	// 向下运动
	while (q0->a[3] <= q1->a[3])
	{
		setfillstyle(YELLOW);
		bar(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		adjust();
		Sleep(10 * v);
		setfillstyle(WHITE);
		bar(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		setcolor(RED);
		if (q0->a[1] > 100)									// 重画被擦掉的红线
		{
			setcolor(RED);
			line((q0->a[0] + q0->a[2]) / 2, q0->a[1], (q0->a[0] + q0->a[2]) / 2, q0->a[3]);
		}
		q0->a[1] += 10;
		q0->a[3] += 10;
	}

	// 在目的钢针上的相应位置绘制出黄色矩形块
	setfillstyle(YELLOW);
	bar(q1->a[0], q1->a[1], q1->a[2], q1->a[3]);
}

// 绘制开始界面
void start()
{

	// 初始化画面大小
	initgraph(800, 650);

	// 背景设为白色
	setbkcolor(WHITE);

	// 用白色填充整个画面
	cleardevice();
	
	// 绘制彩虹，形成一道彩虹，摘自 easyx 帮助文档示例程序
	float H, S, L; 
	H = 0;			// 色相
	S = 1;			// 饱和度
	L = 0.5f;		// 亮度
	setlinestyle(PS_SOLID, NULL, 2);								// 设置线宽为 2
	for(int r = 600; r > 544; r--)
	{
		H += 5;
		setcolor( HSLtoRGB(H, S, L) );
		circle(750, 900, r);
	}

	// 说明
	setfont(50, 0, "华文楷体");
	setcolor(RED);
	outtextxy(200, 150, "汉诺塔移动动画");
	setfont(20, 0, "黑体");
	outtextxy(600, 200, "BY:Ronald");
	outtextxy(500, 200, "版本V1.1");
	setfont(50, 0, "黑体");
	setcolor(GREEN);
	outtextxy(200, 350, "随便按一个键开始吧！");

	// 绘制运动的矩形
	while (1)
	{

		// 检测是否有键盘敲击
		if (kbhit())
		{
			break; 
		}

		// 向右
		int a = 40, b = 40;									//初始位置
		while (a <= 760)
		{
			setfillstyle(YELLOW);
			bar(a, b, a + 10, b + 20);
			Sleep(10);
			setfillstyle(WHITE + a);
			bar(a, b, a + 10, b + 20);
			a += 10;
		}

		if (kbhit())
		{
			break;
		}

		// 向下
		while (b<=610)
		{
			setfillstyle(RED);
			bar(a, b, a + 10, b + 20);
			Sleep(10);
			setfillstyle(WHITE - b);
			bar(a, b, a + 10, b + 20);
			b += 10;
		}
		
		if (kbhit())
		{
			break;
		}

		// 向左
		while (a >= 40)
		{
			setfillstyle(GREEN);
			bar(a, b, a + 10, b + 20);
			Sleep(10);
			setfillstyle(WHITE - a);
			bar(a, b, a + 10, b + 20);
			a -= 10;
		}

		if (kbhit())
		{
			break;
		}

		// 向上
		while (b >= 40)
		{
			setfillstyle(BLUE);
			bar(a, b, a + 10, b + 20);
			Sleep(10);
			setfillstyle(WHITE + b);
			bar(a, b, a + 10, b + 20);
			b -= 10;
		}
	}

	// 清空开始界面
	cleardevice();

	// 绘制运动画面的的环境
	setcolor(RED);

	// 三根红色线段作为钢针
	line(400, 110, 400, 500);
	line(600, 110, 600, 500);
	line(200, 110, 200, 500);

	// 长方体形的底座
	setfillstyle(LIGHTGRAY);
	bar3d(80, 500, 720, 510, 10, true); 
	
	// 暂停按钮
	bar(360, 540, 440, 580);
	setfont(30, 0, "黑体");
	setcolor(GREEN);
	outtextxy(370, 550, "暂停");                              
	setfont(20, 0, "宋体");
	setcolor(RED);
	outtextxy(300, 580, "鼠标暂停后请按空格继续");

	// 加速按钮
	bar(160, 540, 240, 580);
	setfont(30, 0, "黑体");
	setcolor(GREEN);
	outtextxy(170, 550, "加速");
	setfont(20, 0, "宋体");
	setcolor(RED);
	outtextxy(170, 580, "请按 d");

	// 减速按钮
	bar(560, 540, 640, 580);
	setfont(30, 0, "黑体");
	setcolor(GREEN);
	outtextxy(570, 550, "减速");
	setfont(20, 0, "宋体");
	setcolor(RED);
	outtextxy(570, 580, "请按 a");

	// 说明
	setfont(50, 0, "宋体");
	setcolor(GREEN);
	outtextxy(10, 10, "正在进行中请欣赏：");
}

// 判断目的钢针与源钢针的钢针号返回钢针号
int switchab(char a)
{
	switch (a)
	{
		case 'a':
			return 0;
		case 'b':
			return 1;
		case 'c':
			return 2;
		default:
			return 0;
	}
}

// 调整函数，实现加速，减速，暂停
void adjust()
{
	char f;												// 接收键盘敲进去的按钮和鼠标点击时赋予的变化值

	// 用 f 接受键盘的键入值
	if(kbhit())
		f = getch();

	// 检测鼠标消息
	if (MouseHit()==true)									
	{

		// 接收鼠标消息
		MOUSEMSG Mouse;
		Mouse = GetMouseMsg();

		// 响应鼠标消息
		if (Mouse.x >= 360 && Mouse.x <= 440 && Mouse.y >= 540 && Mouse.y <= 580 && Mouse.mkLButton)
		{
			f = ' ';
		}
		if (Mouse.x >= 160 && Mouse.x <= 240 && Mouse.y >= 540 && Mouse.y <= 580 && Mouse.mkLButton)
		{
			f = 'd';
		}
		if (Mouse.x >= 560 && Mouse.x <= 640 && Mouse.y >= 540 && Mouse.y <= 580 && Mouse.mkLButton)
		{
			f = 'a';
		}
	}

	// 作用于动画
	switch(f)
	{
		
		// 暂停
		case ' ':
		
			// 用‘继续’覆盖‘暂停’  
			setfont(30, 0, "黑体");
			setcolor(GREEN);
			outtextxy(370, 550, "继续");  
			getch();
		
			// 继续后变回显示‘暂停’
			setfont(30, 0, "黑体");
			setcolor(GREEN);
			outtextxy(370, 550, "暂停");  
			break;
		
		// 减速
		case 'a':
		
			// 当被点击时，‘减速’位置震动一下
			setfillstyle(LIGHTGRAY);
			bar(560, 540, 640, 580);
			setfont(30, 0, "黑体");
			setcolor(GREEN);
			outtextxy(575, 545, "减速"); 
			Sleep(30);
		
			// 减速
			v++; 
		
			// 回原位
			setfillstyle(LIGHTGRAY);
			bar(560, 540, 640, 580);
			setfont(30, 0, "黑体");
			setcolor(GREEN);
			outtextxy(570, 550, "减速");
			break;
		
		// 加速
		case 'd':
			setfillstyle(LIGHTGRAY);
			bar(160, 540, 240, 580);
			setfont(30, 0, "黑体");
			setcolor(GREEN);
			outtextxy(165, 545, "加速");
			Sleep(30);
			setfillstyle(LIGHTGRAY);
			bar(160, 540, 240, 580);
			setfont(30, 0, "黑体");
			setcolor(GREEN);
			outtextxy(170, 550, "加速");

			// 加速
			v--;
		
			// v 最小为1
			if (v <= 0)              
			{
				v = 1;
			}
			break;
		
		default:
			break;
	} 
	
	f = 'r';									// f 初始化为 r
	FlushMouseMsgBuffer();						// 清空鼠标消息
}