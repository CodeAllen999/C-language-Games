#include <graphics.h>	// EasyX_2011���ݰ�
#include <strstream>
#include <ctime>
#pragma comment(lib, "Winmm.lib")
#define T(c) ((c == 'B') ? 'W' : 'B')
using namespace std;

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

/*******************************����ȫ�ֱ���*****************************/
const int difficult = 6;	// �Ѷ�
const int move[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1},
						{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
							// �˸�������չ
char map[8][8];				// ����
IMAGE img[5];				// ����ͼƬ
int black, white;			// ˫����������
int X, Y;					// ��������ӵ�

/**********************************��������*****************************/
void load(void);				// �����ز�
void print(void);				// ������
void draw(int, int, char);		// �µ�ǰ��
int judge(int, int, char);		// �жϵ�ǰ�Ƿ��������
bool baidu(char);				// �ж��Ƿ�����ɳ�
bool quit(char);				// �ж��Ƿ�������
bool ask(void);					// �����Ի���
int D(char, int);				// ��̬�滮
void play(void);				// ��Ϸ����

/**********************************���庯��*****************************/
void load(void)		// �����ز�
{
	// ����ͼƬ
	loadimage(&img[0], "ͼƬ\\��λ.bmp");
	loadimage(&img[1], "ͼƬ\\����.bmp");
	loadimage(&img[2], "ͼƬ\\����.bmp");
	loadimage(&img[3], "ͼƬ\\����1.bmp");
	loadimage(&img[4], "ͼƬ\\����1.bmp");

	// ��������
	mciSendString("open ����\\��������.wma", NULL, 0, NULL);
	mciSendString("open ����\\�;�.wma", NULL, 0, NULL);
	mciSendString("open ����\\ʤ��.wma", NULL, 0, NULL);
	mciSendString("open ����\\ʧ��.wma", NULL, 0, NULL);
	mciSendString("open ����\\����.wma", NULL, 0, NULL);

	// ��ʼ������
	initgraph(340, 340);
	IMAGE qipan;
	loadimage(&qipan, "ͼƬ\\����.bmp");
	putimage(0, 0, &qipan);
	setorigin(26, 26);
	SetWindowText(GetHWnd(), "�ڰ���AI��");
}

void print(void)	// ������
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

void draw(int x, int y, char a)	// �µ�ǰ��
{
	char b = T(a);									// �з���
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

int judge(int x, int y, char a)	// �жϵ�ǰ�Ƿ�������£�ͬdraw����
{
	if(map[x][y])						// �����ǰ���ǿյķ���0ֵ
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
	return n;		// ���ؿɳ�����
}

bool baidu(char c)	// �ж��Ƿ�����ɳ�
{
	int x, y;
	for(x = 0; x < 8; x++)
		for(y = 0; y < 8; y++)
			if(judge(x, y, c))
				return true;
	return false;
}

bool quit(char c)	// �ж��Ƿ�������
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

bool ask(void)	// �����Ի���
{
	HWND wnd = GetHWnd();
	int key;
	char str[50];
	ostrstream strout(str, 50);
	strout <<"�ڣ�" <<black <<"  �ף�" <<white <<endl;
	if (black == white)
		strout <<"�����ƽ";
	else if(black > white)
		strout <<"��ϲ��Ӯ�ˣ�";
	else
		strout <<"С��������Ӯ�ҡ�";
	strout <<"\n����һ����" <<ends;
	if(black == white)
		key = MessageBox(wnd, str, "�;�", MB_YESNO | MB_ICONQUESTION);
	else if(black > white)
		key = MessageBox(wnd, str, "��ʤ", MB_YESNO | MB_ICONQUESTION);
	else
		key = MessageBox(wnd, str, "��ʤ", MB_YESNO | MB_ICONQUESTION);
	if(key == IDYES)
		return true;
	else
		return false;
}

int D(char c, int step)
{
	// �ж��Ƿ�����ݹ�
	if (step > difficult)	// Լ������֮��
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

	// ������ʱ����
	char **t = new char *[8];
	for (i = 0; i < 8; i++)
		t[i] = new char [8];
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			t[i][j] = map[i][j];

	// �����ⷨ
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

	// �����ռ�
	for (i = 0; i < 8; i++)
		delete [] t[i];
	delete [] t;

	// ����ǵ�һ�����ʶ�������ӵ�
	if (step == 1)
	{
		X = x;
		Y = y;
	}

	return max;	// �������Ž�
}

void play(void)			// ��Ϸ����
{
	MOUSEMSG m;
	int x, y;

	// ��ʼ������
	for(x = 0; x < 8; x++)
		for(y = 0; y < 8; y++)
			map[x][y] = 0;
	map[3][4] = map[4][3] = 'B';
	map[3][3] = map[4][4] = 'W';

	// ��ʼ��Ϸ
	print();
	mciSendString("play ����\\��������.wma from 0 repeat", NULL, 0, NULL);
	do
	{
		if (baidu('B'))										// ������������λ��							
		{
			A:
			while(true)
			{
				m = GetMouseMsg();							// ��ȡ�����Ϣ
				if(m.uMsg == WM_LBUTTONDOWN && m.x - 26 < 37 * 8 && m.y - 26 < 37 * 8)
															// ���������
					break;
			}
			x = (m.y - 26) / 37;
			y = (m.x - 26) / 37;
			if(judge(x, y, 'B'))							// �����ǰλ����Ч
			{
				draw(x, y, 'B');							// ����
				mciSendString("play ����\\����.wma from 0", NULL, 0, NULL);
				print();
				putimage(37 * y, 37 * x, &img[3]);			// ��ʶ���ӵ�
			}
			else
				goto A;
			if (quit('W'))									// ������Ƿ�ʧ��
				break;
		}
		if (baidu('W'))										// ��������������λ��
		{
			clock_t start;
			start = clock();
			D('W', 1);										// �����ⷨ
			while (clock() - start < CLOCKS_PER_SEC);
			draw(X, Y, 'W');
			print();
			mciSendString("play ����\\����.wma from 0", NULL, 0, NULL);
			putimage(37 * Y, 37 * X, &img[4]);	// ��ʶ���ӵ�
			if (quit('B'))									// ����Ƿ�ʧ��
				break;
		}
	}while (baidu('B') || baidu ('W'));

	// ������ף����
	mciSendString("stop ����\\��������.wma", NULL, 0, NULL);
	if (black > white)
		mciSendString("play ����\\ʤ��.wma from 0", NULL, 0, NULL);
	else if (black < white)
		mciSendString("play ����\\ʧ��.wma from 0", NULL, 0, NULL);
	else
		mciSendString("play ����\\�;�.wma from 0", NULL, 0, NULL);
}

// ������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	load();
	do
	{
		play();
	} while(ask());

	// �ر�����
	mciSendString("close ����\\��������.wma", NULL, 0, NULL);
	mciSendString("close ����\\�;�.wma", NULL, 0, NULL);
	mciSendString("close ����\\ʤ��.wma", NULL, 0, NULL);
	mciSendString("close ����\\ʧ��.wma", NULL, 0, NULL);
	mciSendString("close ����\\����.wma", NULL, 0, NULL);
	closegraph();
	return 0;
}

/***********************************THE END************************************/