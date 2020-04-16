////////////////////////////////////////////////////////////
//画素材的x和y都是反的，因为x表示行,但是画出来x表示列，y同
////////////////////////////////////////////////////////////

/* 【自学去】网站收集 http://www.zixue7.com */

#include <graphics.h>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#pragma comment(lib, "Winmm.lib")
using namespace std;


/*******************************定义枚举类型*****************************/
enum color{blank, red, yellow, blue, green, white, orange, purple, shizijia, zhadan, qicai, alarm};


/*******************************定义全局变量*****************************/
const int MaxT = 12;	// 时间上限
const int T = 10 * MaxT;// 时间速度
const int V = 300;		// 停留时间
clock_t start, now;		// 控制时间
color gem[9][8];		// 地图
						// IMAGE对象
IMAGE img[12], music_img[2], exit_img, jindutiao;
int Score, Time;		// 成绩 时间
bool Flag, Music = true;// 是否加载 音乐


/**********************************函数声明*****************************/
void load(void);	// 加载IMAGE对象
void Blank(void);	// 清空
bool soso(void);	// 搜索空格
bool baidu(void);	// 搜索解法
void New(void);		// 更新
void print(void);	// 输出
bool judge(void);	// 判断是否可以消除
void fall(void);	// 下落
void draw(void);	// 消除
bool quit(void);	// 是否重新开始
void play(void);	// 游戏过程


/**********************************定义函数*****************************/
void load(void)
{
	char c[20];
	int i;

	// 加载IMAGE对象
	for (i = 0; i < 12; i++)
	{
		ostrstream strout(c, 50);
		strout <<"图片\\" <<i <<".jpg" <<ends;
		loadimage(&img[i], c);
	}
	loadimage(&music_img[0], "图片\\音乐关.jpg");
	loadimage(&music_img[1], "图片\\音乐开.jpg");
	loadimage(&exit_img, "图片\\退出.jpg");
	loadimage(&jindutiao, "图片\\进度条.jpg");

	// 加载音乐
	mciSendString("open 背景音乐.mp3 alias mymusic", NULL, 0, NULL);

	// 随机种子
	srand(unsigned(time(NULL)));

	// 打开文件
	ifstream fin("存档.dat");
	if (!fin)
		throw -1;	// 如果打开失败则抛出异常

	// 读存档
	fin >>Flag >>Music;
	if (Flag)
	{
		HWND wnd = GetHWnd();
		SetWindowText(wnd, "对对碰");
		if (MessageBox(wnd, "是否继续上次游戏？", "游戏开始", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			fin >>Score >>Time;
			for (i = 0; i < 9; i++)
				for (int j = 0; j < 8; j++)
				{
					int t;
					fin >>t;
					gem[i][j] = color(t);
				}
		}
		else
			Flag = false;
	}
	fin.close();
}

void Blank(void)
{
	for (int i = 1; i < 9; i++)
		for (int j = 0; j < 8; j++)
			gem[i][j] = blank;
	print();
	fall();
}

bool soso(void)
{
	for (int i = 1; i < 9; i++)
		for (int j = 0; j < 8; j++)
			if (gem[i][j] == blank)
				return true;
	return false;
}

bool baidu(void)
{
	int i, j;
	color t;
	bool flag = false;

	// 如果有一个道具则返回真
	for (i = 1; i < 9; i++)
		for (j = 0; j < 8; j++)
			if (gem[i][j] >= shizijia)
				return true;

	// 搜索解法
	for (i = 1; i < 9; i++)
		for (j = 0; j < 7; j++)
		{
			t = gem[i][j];
			gem[i][j] = gem[i][j + 1];
			gem[i][j + 1] = t;
			if (judge())
				flag = true;
			t = gem[i][j];
			gem[i][j] = gem[i][j + 1];
			gem[i][j + 1] = t;
			if (flag)
				return true;
		}
	for (i = 1; i < 7; i++)
		for (j = 0; j < 8; j++)
		{
			t = gem[i][j];
			gem[i][j] = gem[i + 1][j];
			gem[i + 1][j] = t;
			if (judge())
				flag = true;
			t = gem[i][j];
			gem[i][j] = gem[i + 1][j];
			gem[i + 1][j] = t;
			if (flag)
				return true;
		}
	return false;
}

void New(void)
{
	static int old_score = -1, old_time = T;
	bool flag = false;
	if (Score != old_score)	// 更新分数
	{
		if (Score > 999999999)
		{
			if (MessageBox(GetHWnd(), "恭喜你达到了最高分！\n是否重新开始？", "游戏结束", MB_YESNO | MB_ICONQUESTION) == IDYES)
				Score = 0;
			else
				exit(0);
		}
		char s[15];
		ostrstream strout(s, 15);
		strout <<'$' <<setiosflags(ios::right) <<setw(9) <<Score <<ends;
		setfont(30, 0, "微软雅黑");
		setcolor(RGB(255, 128, 0));
		outtextxy(480, 60, s);
		old_score = Score;
		flag = true;
	}
	if (Time != old_time)	// 更新时间
	{
		if (Time > old_time)
			putimage(540, 140, &jindutiao);
		setcolor(BLACK);
		for (int i = 0; i < T - Time; i++)
		{
			line(540, 140 + 2 * i, 580, 140 + 2 * i);
			line(540, 140 + 2 * i + 1, 580, 140 + 2 * i + 1);
		}
		old_time = Time;
		flag = true;
	}
	if (flag)				// 写存档
	{
		ofstream fout("存档.dat");
		fout <<Flag		<<'\t'
			 <<Music	<<'\t'
			 <<Score	<<'\t'
			 <<Time		<<endl;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 8; j++)
				fout <<int(gem[i][j]) <<'\t';
			fout <<endl;
		}
		fout.close();
	}
}

void print(void)
{
	int i, j;
	for (i = 1; i < 9; i++)
		for (j = 0; j < 8; j++)
			putimage(60 * j, 60 * (i - 1), &img[int(gem[i][j])]);
	New();
}

bool judge(void)
{
	int i, j;
	for (i = 1; i < 9; i++)
		for (j = 0; j < 6; j++)
			if (gem[i][j] == gem[i][j + 1] && gem[i][j] == gem[i][j + 2])
				return true;
	for (i = 1; i < 7; i++)
		for (j = 0; j < 8; j++)
			if (gem[i][j] == gem[i + 1][j] && gem[i][j] == gem[i + 2][j])
				return true;
	return false;
}

void fall(void)
{
	{
		int i, j, a[8] = {0};
		bool sign = false;
		for (j = 0; j < 8; j++)
			for (i = 8; i >= 1; i--)
				if (gem[i][j] == blank)
				{
					a[j] = i;
					sign = true;
					break;
				}
		if (sign == false)
			return;
		IMAGE im[8];
		for (j = 0; j < 8; j++)
			if (a[j] > 1)
				getimage(&im[j], 60 * j, 0, 60, 60 * (a[j] - 1));
		for (i = 0; i < 60 ; i += 2)
			for (j = 0; j < 8; j++)
				if (a[j] > 0)
				{
					if (a[j] > 1)
						putimage(60 * j, i + 2, &im[j]);
					putimage(60 * j, i + 2 - 60, &img[int(gem[0][j])]);
					Sleep(1);
				}
		for (j = 0; j < 8; j++)
			if (a[j] > 0)
			{
				for (i = a[j]; i > 0; i--)
					gem[i][j] = gem[i - 1][j];
				if (rand() % 50 == 0)
					gem[0][j] = color(rand() % 4 + 8);
				else
					gem[0][j] = color(rand() % 7 + 1);
			}
	}	// 加对大括号使递归时撤销内存空间
	if (soso())
		fall();
	if (judge())
		draw();
}

void draw(void)
{
	{
		int i, j;
		bool a[9][8] = {false};
		for (i = 1; i < 9; i++)
			for (j = 0; j < 6; j++)
				if (gem[i][j] == gem[i][j + 1] && gem[i][j] == gem[i][j + 2])
					a[i][j] = a[i][j + 1] = a[i][j + 2] = true;
		for (i = 1; i < 7; i++)
			for (j = 0; j < 8; j++)
				if (gem[i][j] == gem[i + 1][j] && gem[i][j] == gem[i + 2][j])
					a[i][j] = a[i + 1][j] = a[i + 2][j] = true;
		for (i = 1; i < 9; i++)
			for (j = 0; j < 8; j++)
				if (a[i][j])
				{
					gem[i][j] = blank;
					Score += 10;
				}
		Sleep(V);
		Time += T / MaxT;
		if (Time > T)
			Time = T;
		print();
	}	// 加对大括号使递归时撤销内存空间
	fall();
}

bool quit(void)
{
	char str[50];
	ostrstream strout(str, 50);
	strout <<"得分：" <<Score <<"\n重新开始吗？" <<ends;
	if (MessageBox(GetHWnd(), str, "游戏结束", MB_YESNO | MB_ICONQUESTION) == IDYES)
		return true;
	return false;
}

void play(void)
{
	MOUSEMSG m;
	int i, j, x, y, x1, y1;
	char fx;
	color t;
	bool sign;
	if (Flag == false)
	{
		do
		{
			for (i = 0; i < 9; i++)
				for (j = 0; j < 8; j++)
					gem[i][j] = color(rand() % 7 + 1);
		}while (judge() || !baidu());
		Score = 0;
		Time = T;
	}
	setbkcolor(BLACK);
	cleardevice();
	setfont(30, 0, "微软雅黑");
	setcolor(RGB(255, 128, 0));
	outtextxy(480, 60, "$       0");
	putimage(480, 400, &music_img[int(Music)]);
	putimage(560, 400, &exit_img);
	putimage(540, 140, &jindutiao);
	print();
	now = start = clock();
	Flag = true;
	do
	{
		if (soso())
			fall();
		fx = 0;
		sign = true;
		while (true)
		{
			if (MouseHit())
			{
				m = GetMouseMsg();
				x1 = m.x;
				y1 = m.y;
				if (m.uMsg == WM_LBUTTONDOWN)
				{
					if (x1 < 480)
					{
						x = y1 / 60 + 1;
						y = x1 / 60;
						switch (gem[x][y])
						{
						case shizijia:
							for (i = 1; i < 9; i++)
							{
								gem[i][y] = blank;
								Score += 10;
							}
							for (j = 0; j < 8; j++)
							{
								gem[x][j] = blank;
								Score += 10;
							}
							Score -= 20;
							Time += T / MaxT;
							if (Time > T)
								Time = T;
							print();
							Sleep(V);
							fall();
							if (!baidu())
								Blank();
							break;

						case zhadan:
							if (x > 1)
							{
								gem[x - 1][y] = blank;
								Score += 10;
								if (y > 0)
								{
									gem[x - 1][y - 1] =blank;
									Score += 10;
								}
							}
							if (y > 0)
							{
								gem[x][y - 1] = blank;
								if (x < 8)
								{
									gem[x + 1][y - 1] =blank;
									Score += 10;
								}
							}
							if (x < 8)
							{
								gem[x + 1][y] = blank;
								if (y < 7)
								{
									gem[x + 1][y + 1] =blank;
									Score += 10;
								}
							}
							if (y < 7)
							{
								gem[x][y + 1] = blank;
								if (x > 1)
								{
									gem[x - 1][y + 1] =blank;
									Score += 10;
								}							
							}
							gem[x][y] = blank;
							Time += T / MaxT;
							if (Time > T)
								Time = T;
							print();
							Sleep(V);
							fall();
							if (!baidu())
								Blank();
							break;

						case qicai:
							t = color(rand() % 7 + 1);
							putimage(60 * y, 60 * (x - 1), &img[int(t)]);
							Sleep(V);
							for (i = 1; i < 9; i++)
								for (j = 0; j < 8; j++)
									if (gem[i][j] == t)
									{
										gem[i][j] = blank;
										putimage(60 * j, 60 * (i - 1), &img[0]);
										Score += 10;
									}
							gem[x][y] = blank;
							Time += T / MaxT;
							if (Time > T)
								Time = T;
							print();
							fall();
							if (!baidu())
								Blank();
							break;

						case alarm:
							Time = T;
							gem[x][y] = blank;
							print();
							fall();
							if (!baidu())
								Blank();
							break;
						}
						break;
					}
					else if (x1 > 480 && x1 < 560 && y1 > 400 && y1 < 480)
					{
						if (Music)
							mciSendString("stop mymusic", NULL, 0, NULL);
						else
							mciSendString("play mymusic from 0 repeat", NULL, 0, NULL);
						Music = !Music;
						putimage(480, 400, &music_img[int(Music)]);
					}
					else if (x1 > 560 && x1 < 640 && y1 > 400 && y1 < 480)
						exit(0);
				}
			}
			now = clock();
			if (now - start >= CLOCKS_PER_SEC * MaxT / T)
			{
				start = now;
				Time--;
				New();
				if (Time <= 0)
					return;
			}
		}
		while (m.mkLButton && m.y < 480)
		{
			m = GetMouseMsg();
			x = m.x;
			y = m.y;
			if (x - x1 > 30 || x1 - x > 30 || y - y1 > 30 || y1 - y > 30)
			{
				sign = false;
				break;
			}
			now = clock();
			if (now - start >= CLOCKS_PER_SEC * MaxT / T)
			{
				start = now;
				Time--;
				New();
				if (Time <= 0)
					return;
			}
		}
		if(sign)
		{
			putimage(x1 - x1 % 60, y1 - y1 % 60, &img[int(gem[y1 / 60 + 1][x1 / 60])], SRCPAINT);
			continue;
		}
		if (y1 - y > 30 && y1 / 60 > 0)
			fx = 'u';
		if (y - y1 > 30 && y1 / 60 < 7)
			fx = 'd';
		if (x1 - x > 30 && x1 / 60 > 0)
			fx = 'l';
		if (x - x1 > 30 && x1 / 60 < 7)
			fx = 'r';
		x = y1 / 60 + 1;
		y = x1 / 60;
		x1 = y1 = 0;
		switch (fx)
		{
			case 'u':x1 = -1;	break;
			case 'd':x1 = 1;	break;
			case 'l':y1 = -1;	break;
			case 'r':y1 = 1;	break;
			case '\0':continue;
		}
		for (i = 0; i < 60;)
		{
			putimage(60 * y, 60 * (x - 1), &img[0]);
			putimage(60 * y, 60 * (x - 1), &img[0]);
			i += 1;
			putimage(60 * (y + y1) - i * y1, 60 * (x - 1 + x1) - i * x1, &img[int(gem[x + x1][y + y1])]);
			putimage(60 * y + i * y1, 60 * (x - 1) + i * x1, &img[int(gem[x][y])]);
			Sleep(2);
		}
		t = gem[x][y];
		gem[x][y] = gem[x + x1][y + y1];
		gem[x + x1][y + y1] = t;
		if (judge())
		{
			draw();
			if (!baidu())
				Blank();
		}
		else
		{
			for (i = 0; i < 60;)
			{
				putimage(60 * y, 60 * (x - 1), &img[0]);
				putimage(60 * y, 60 * (x - 1), &img[0]);
				i += 1;
				putimage(60 * (y + y1) - i * y1, 60 * (x - 1 + x1) - i * x1, &img[int(gem[x + x1][y + y1])]);
				putimage(60 * y + i * y1, 60 * (x - 1) + i * x1, &img[int(gem[x][y])]);
				Sleep(2);
			}
			t = gem[x][y];
			gem[x][y] = gem[x + x1][y + y1];
			gem[x + x1][y + y1] = t;
		}
		now = clock();
		if (now - start >= CLOCKS_PER_SEC * MaxT / T)
		{
			start = now;
			Time--;
			New();
			if (Time <= 0)
				return;
		}
	}while (true);
}


/***********************************主函数******************************/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try
	{
		// 加载素材
		load();
	}
	catch (int)
	{
		ofstream fout("存档.dat");
		fout <<false <<'\t' <<true <<endl;
	}

	// 打开界面
	initgraph(640, 480);

	// 游戏过程
	do
	{
		if (Music)
			mciSendString("play mymusic from 0 repeat", NULL, 0, NULL);
		play();
		if (Music)
			mciSendString("stop mymusic", NULL, 0, NULL);
		Flag = false;
	}while (quit());

	// 关闭游戏
	ofstream fout("存档.dat");
	fout <<false <<'\t' <<Music <<endl;
	fout.close();
	mciSendString("close mymusic", NULL, 0, NULL);
	closegraph();
	return 0;
}


/***********************************THE END************************************/