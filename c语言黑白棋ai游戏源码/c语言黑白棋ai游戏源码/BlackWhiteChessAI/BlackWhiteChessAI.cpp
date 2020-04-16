#include <graphics.h>	// EasyX_2011惊蛰版
#include <strstream>
#include <ctime>
#pragma comment(lib, "Winmm.lib")
#define T(c) ((c == 'B') ? 'W' : 'B')
using namespace std;

/* 【自学去】网站收集 http://www.zixue7.com */

/*******************************定义全局变量*****************************/
const int difficult = 6;	// 难度
const int move[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1},
						{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
							// 八个方向扩展
char map[8][8];				// 棋盘
IMAGE img[5];				// 保存图片
int black, white;			// 双方的棋子数
int X, Y;					// 白棋的下子点

/**********************************函数声明*****************************/
void load(void);				// 加载素材
void print(void);				// 画棋盘
void draw(int, int, char);		// 下当前子
int judge(int, int, char);		// 判断当前是否可以落下
bool baidu(char);				// 判断是否有棋可吃
bool quit(char);				// 判断是否有棋存活
bool ask(void);					// 弹出对话框
int D(char, int);				// 动态规划
void play(void);				// 游戏过程

/**********************************定义函数*****************************/
void load(void)		// 加载素材
{
	// 加载图片
	loadimage(&img[0], "图片\\空位.bmp");
	loadimage(&img[1], "图片\\黑子.bmp");
	loadimage(&img[2], "图片\\白子.bmp");
	loadimage(&img[3], "图片\\黑子1.bmp");
	loadimage(&img[4], "图片\\白子1.bmp");

	// 加载音乐
	mciSendString("open 音乐\\背景音乐.wma", NULL, 0, NULL);
	mciSendString("open 音乐\\和局.wma", NULL, 0, NULL);
	mciSendString("open 音乐\\胜利.wma", NULL, 0, NULL);
	mciSendString("open 音乐\\失败.wma", NULL, 0, NULL);
	mciSendString("open 音乐\\下子.wma", NULL, 0, NULL);

	// 初始化棋盘
	initgraph(340, 340);
	IMAGE qipan;
	loadimage(&qipan, "图片\\棋盘.bmp");
	putimage(0, 0, &qipan);
	setorigin(26, 26);
	SetWindowText(GetHWnd(), "黑白棋AI版");
}

void print(void)	// 画棋盘
{
	int x, y;
	black = white = 0;
	for(x = 0; x < 8; x++)
		for(y = 0; y < 8; y++)
			switch(map[x][y])
			{
				case 0:
						putimage(37 * y, 37 * x, &img[0]);
					break;
				case 'B':
						putimage(37 * y, 37 * x, &img[1]);
					black++;
					break;
				case 'W':
						putimage(37 * y, 37 * x, &img[2]);
					white++;
					break;
			}
}

void draw(int x, int y, char a)	// 下当前子
{
	char b = T(a);									// 敌方子
	int i, x1, y1, x2, y2;
	bool sign;			
	for (i = 0; i < 8; i++)
	{
		sign = false;
		x1 = x + move[i][0];
		y1 = y + move[i][1];
		while (0 <= x1 && x1 < 8 && 0 <= y1 && y1 < 8 && map[x1][y1])
		{
			if(map[x1][y1] == b)
				sign = true;
			else
			{
				if(sign)
				{
					x1 -= move[i][0];
					y1 -= move[i][1];
					x2 = x + move[i][0];
					y2 = y + move[i][1];
					while (((x <= x2 && x2 <= x1) || (x1 <= x2 && x2 <= x)) && ((y <= y2 && y2 <= y1) || (y1 <= y2 && y2 <= y)))
					{
						map[x2][y2] = a;
						x2 += move[i][0];
						y2 += move[i][1];
					}
				}
				break;
			}
			x1 += move[i][0];
			y1 += move[i][1];
		}
	}
	map[x][y] = a;
}

int judge(int x, int y, char a)	// 判断当前是否可以落下，同draw函数
{
	if(map[x][y])						// 如果当前不是空的返回0值
		return 0;
	char b = T(a);
	int i, x1, y1;
	int n = 0, sign;
	for (i = 0; i < 8; i++)
	{
		sign = 0;
		x1 = x + move[i][0];
		y1 = y + move[i][1];
		while (0 <= x1 && x1 < 8 && 0 <= y1 && y1 < 8 && map[x1][y1])
		{
			if(map[x1][y1] == b)
				sign++;
			else
			{
				n += sign;
				break;
			}
			x1 += move[i][0];
			y1 += move[i][1];
		}
	}
	return n;		// 返回可吃棋数
}

bool baidu(char c)	// 判断是否有棋可吃
{
	int x, y;
	for(x = 0; x < 8; x++)
		for(y = 0; y < 8; y++)
			if(judge(x, y, c))
				return true;
	return false;
}

bool quit(char c)	// 判断是否有棋存活
{
	int x, y;
	bool b = false, w = false;
	for(x = 0; x < 8; x++)
		for(y = 0; y < 8; y++)
		{
			if(map[x][y] == c)
				return false;
		}
	return true;
}

bool ask(void)	// 弹出对话框
{
	HWND wnd = GetHWnd();
	int key;
	char str[50];
	ostrstream strout(str, 50);
	strout <<"黑：" <<black <<"  白：" <<white <<endl;
	if (black == white)
		strout <<"世界和平";
	else if(black > white)
		strout <<"恭喜你赢了！";
	else
		strout <<"小样，还想赢我。";
	strout <<"\n再来一局吗？" <<ends;
	if(black == white)
		key = MessageBox(wnd, str, "和局", MB_YESNO | MB_ICONQUESTION);
	else if(black > white)
		key = MessageBox(wnd, str, "黑胜", MB_YESNO | MB_ICONQUESTION);
	else
		key = MessageBox(wnd, str, "白胜", MB_YESNO | MB_ICONQUESTION);
	if(key == IDYES)
		return true;
	else
		return false;
}

int D(char c, int step)
{
	// 判断是否结束递归
	if (step > difficult)	// 约束步数之内
		return 0;
	if (!baidu(c))
	{
		if (baidu(T(c)))
			return -D(T(c), step);
		else
			return 0;
	}

	int i, j, max = 0, temp, x, y;
	bool ans = false;

	// 建立临时数组
	char **t = new char *[8];
	for (i = 0; i < 8; i++)
		t[i] = new char [8];
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			t[i][j] = map[i][j];

	// 搜索解法
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			if (temp = judge(i, j, c))
			{
				draw(i, j, c);
				temp -= D(T(c), step + 1);
				if (temp > max || !ans)
				{
					max = temp;
					x = i;
					y = j;
					ans = true;
				}
				for (int k = 0; k < 8; k++)
					for (int l = 0; l < 8; l++)
						map[k][l] = t[k][l];
			}

	// 撤销空间
	for (i = 0; i < 8; i++)
		delete [] t[i];
	delete [] t;

	// 如果是第一步则标识白棋下子点
	if (step == 1)
	{
		X = x;
		Y = y;
	}

	return max;	// 返会最优解
}

void play(void)			// 游戏过程
{
	MOUSEMSG m;
	int x, y;

	// 初始化棋子
	for(x = 0; x < 8; x++)
		for(y = 0; y < 8; y++)
			map[x][y] = 0;
	map[3][4] = map[4][3] = 'B';
	map[3][3] = map[4][4] = 'W';

	// 开始游戏
	print();
	mciSendString("play 音乐\\背景音乐.wma from 0 repeat", NULL, 0, NULL);
	do
	{
		if (baidu('B'))										// 如果玩家有下子位置							
		{
			A:
			while(true)
			{
				m = GetMouseMsg();							// 获取鼠标消息
				if(m.uMsg == WM_LBUTTONDOWN && m.x - 26 < 37 * 8 && m.y - 26 < 37 * 8)
															// 如果左键点击
					break;
			}
			x = (m.y - 26) / 37;
			y = (m.x - 26) / 37;
			if(judge(x, y, 'B'))							// 如果当前位置有效
			{
				draw(x, y, 'B');							// 下子
				mciSendString("play 音乐\\下子.wma from 0", NULL, 0, NULL);
				print();
				putimage(37 * y, 37 * x, &img[3]);			// 标识下子点
			}
			else
				goto A;
			if (quit('W'))									// 计算机是否失败
				break;
		}
		if (baidu('W'))										// 如果计算机有下子位置
		{
			clock_t start;
			start = clock();
			D('W', 1);										// 搜索解法
			while (clock() - start < CLOCKS_PER_SEC);
			draw(X, Y, 'W');
			print();
			mciSendString("play 音乐\\下子.wma from 0", NULL, 0, NULL);
			putimage(37 * Y, 37 * X, &img[4]);	// 标识下子点
			if (quit('B'))									// 玩家是否失败
				break;
		}
	}while (baidu('B') || baidu ('W'));

	// 播放庆祝音乐
	mciSendString("stop 音乐\\背景音乐.wma", NULL, 0, NULL);
	if (black > white)
		mciSendString("play 音乐\\胜利.wma from 0", NULL, 0, NULL);
	else if (black < white)
		mciSendString("play 音乐\\失败.wma from 0", NULL, 0, NULL);
	else
		mciSendString("play 音乐\\和局.wma from 0", NULL, 0, NULL);
}

// 主函数
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	load();
	do
	{
		play();
	} while(ask());

	// 关闭音乐
	mciSendString("close 音乐\\背景音乐.wma", NULL, 0, NULL);
	mciSendString("close 音乐\\和局.wma", NULL, 0, NULL);
	mciSendString("close 音乐\\胜利.wma", NULL, 0, NULL);
	mciSendString("close 音乐\\失败.wma", NULL, 0, NULL);
	mciSendString("close 音乐\\下子.wma", NULL, 0, NULL);
	closegraph();
	return 0;
}

/***********************************THE END************************************/