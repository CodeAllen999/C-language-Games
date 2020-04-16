#include <easyx.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

// ���峣��
#define PI			3.141592653589		// Բ����
#define UNIT_GROUND	0					// ��ʾ����
#define UNIT_WALL	1					// ��ʾǽ
#define LIGHT_A		PI / 3				// �ƹ�ĽǶȷ�Χ
#define	LIGHT_R		120					// �ƹ���������
#define	WIDTH		480					// �󾮵Ŀ��
#define	HEIGHT		480					// �󾮵ĸ߶�
#define SCREENWIDTH	640					// ��Ļ���
#define	SCREENHEIGHT 480				// ��Ļ�߶�
#define	UNIT		20					// ÿ��ǽ�ڵ�λ�Ĵ�С
#define PLAYER_R	5					// ��Ϸ�ߵİ뾶

// ���峣��
const	SIZE	g_utMap = {23, 23};		// �󾮵�ͼ�ĳߴ�(���� UNIT ��λ)
const	POINT	g_utPlayer = {1, 1};	// ��Ϸ�ߵ�λ��(���� UNIT ��λ)
const	POINT	g_utExit = {21, 22};	// ����λ��(���� UNIT ��λ)
const	POINT	g_ptOffset = {10, 10};	// ����ʾ����Ļ�ϵ�ƫ����

//////////////////////////////////////////////////////
// ����ȫ�ֱ���
//
POINT	g_ptPlayer;						// ��Ϸ�ߵ�λ��
POINT	g_ptMouse;						// ���λ��
IMAGE	g_imgMap(WIDTH, HEIGHT);		// ��ƽ��ͼ
DWORD*	g_bufMap;						// ��ƽ��ͼ���Դ�ָ��
IMAGE	g_imgRender(WIDTH, HEIGHT);		// ��Ⱦ
DWORD*	g_bufRender;					// ��Ⱦ���Դ�ָ��
DWORD*	g_bufScreen;					// ��Ļ���Դ�ָ��

// ö���û��Ŀ�������
enum CMD { CMD_QUIT = 1, CMD_UP = 2, CMD_DOWN = 4, CMD_LEFT = 8, CMD_RIGHT = 16, CMD_RESTART = 32 };



//////////////////////////////////////////////////////
// ��������
//

// ��ʼ��
void	Welcome();									// ������Ϸ����
void	ReadyGo();									// ׼����ʼ��Ϸ
void	InitGame();									// ��ʼ����Ϸ����

// ������
void	MakeMaze(int width, int height);			// ��ʼ��(ע����߱���������)
void	TravelMaze(int x, int y, BYTE** aryMap);	// ���� (x, y) ����
void	DrawWall(int x, int y, bool left, bool top, bool right, bool bottom);
													// ��һ��ǽ
// ����
void	Paint();									// ������Ұ��Χ�ڵĿ�
void	Lighting(int _x, int _y, double _a);		// ��ָ��λ�úͽǶȡ�������
void	DrawPlayer();								// ������Ϸ��
void	DrawExit();									// ���Ƴ���

// �����û�����
int		GetCmd();									// ��ȡ�û����������
void	OnUp();										// �����ƶ�
void	OnLeft();									// �����ƶ�
void	OnRight();									// �����ƶ�
void	OnDown();									// �����ƶ�
bool	CheckWin();									// ����Ƿ񵽳���



//////////////////////////////////////////////////////
// ��������
//

// ������
void main()
{
	// ��ʼ��
	initgraph(SCREENWIDTH, SCREENHEIGHT);		// ������ͼ����
	srand((unsigned)time(NULL));				// �����������
	
	// ��ʾ������
	Welcome();

	// ��Ϸ����
	int c;
	do
	{
		ReadyGo();

		while(true)
		{
			// ����û�����
			c = GetCmd();

			// �����û�����
			if (c & CMD_UP)			OnUp();
			if (c & CMD_DOWN)		OnDown();
			if (c & CMD_LEFT)		OnLeft();
			if (c & CMD_RIGHT)		OnRight();
			if (c & CMD_RESTART)
			{
				if (MessageBox(GetHWnd(), _T("��Ҫ����һ����"), _T("ѯ��"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
					break;
			}
			if (c & CMD_QUIT)
			{
				if (MessageBox(GetHWnd(), _T("��ȷ��Ҫ�˳���Ϸ��"), _T("ѯ��"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
					break;
			}

			// ���Ƴ���
			Paint();

			// �ж��Ƿ��߳���
			if (CheckWin())
			{
				// �Ƿ�����һ��
				HWND hwnd = GetHWnd();
				if (MessageBox(hwnd, _T("��ϲ���߳����ˣ�\n��������һ����"), _T("��ϲ"), MB_YESNO | MB_ICONQUESTION) != IDYES)
					c = CMD_QUIT;

				break;
			}

			// ��ʱ
			Sleep(16);
		}

	}
	while(!(c & CMD_QUIT));

	// �ر�ͼ��ģʽ
	closegraph();
}


// ׼����ʼ��Ϸ
void ReadyGo()
{
	// ��ʼ��
	InitGame();

	// ͣ��ǰ��
	int time[7] = {1000, 50, 500, 50, 50, 50, 50};
	int i, x, y;
	for (i = 0; i < 7; i++)
	{
		if (i % 2 == 0)
		{
			putimage(0, 0, &g_imgMap);
			DrawPlayer();
			DrawExit();
		}
		else
			clearrectangle(0, 0, WIDTH - 1, HEIGHT - 1);
		Sleep(time[i]);
	}
	// ���������ж�
	for (i = 255; i >= 0; i -= 5)
	{
		for (y = (HEIGHT - 1) * SCREENWIDTH; y >= 0; y -= SCREENWIDTH)
			for (x = 0; x < WIDTH; x++)
				if (g_bufScreen[y + x] != 0)
					g_bufScreen[y + x] = g_bufScreen[y + x] - 0x050505;

		FlushBatchDraw();
		DrawPlayer();
		DrawExit();
		Sleep(50);
	}

	// ������Ϸ��
	Paint();
}


// ������Ϸ����
void Welcome()
{
	setfillcolor(DARKGRAY);
	solidrectangle(WIDTH, 0, SCREENWIDTH - 1, SCREENHEIGHT - 1);

	// ����������ʽ
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);

	// ���Ʊ���
	settextstyle(24, 0, _T("����"));
	outtextxy(512, 40, _T("������"));

	// ���Ʋ���˵��
	RECT r = {488, 100, 632, 470};
	settextstyle(12, 0, _T("����"));
	drawtext(_T("[��Ϸ˵��]\n��������ĵ�·�ֳ������ˡ�Ѹ�ٽ������ͷ�ƣ�����ڵĿ���\
		�ҵ������ӳ�ȥ�ɡ�\n\n[����˵��]\n������� �ƶ�\nA/S/D/W���ƶ�\n��꣺�� ��������\
		����\nF2������ ����һ��\nESC�������˳���Ϸ"), &r, DT_WORDBREAK);
	outtextxy(495, 465, _T("Powered by yw80@qq.com"));
}


// ��ʼ����Ϸ����
void InitGame()
{
	// ��ô����Դ�ָ��
	g_bufRender = GetImageBuffer(&g_imgRender);
	g_bufMap = GetImageBuffer(&g_imgMap);
	g_bufScreen = GetImageBuffer(NULL);

	// ���� Render ����
	SetWorkingImage(&g_imgRender);
	setbkmode(TRANSPARENT);
	SetWorkingImage(NULL);

	// ������
	MakeMaze(g_utMap.cx, g_utMap.cy);

	// ������Ϸ��λ��
	g_ptPlayer.x = g_utPlayer.x * UNIT + UNIT / 2 + g_ptOffset.x;
	g_ptPlayer.y = g_utPlayer.y * UNIT + UNIT / 2 + g_ptOffset.y;
}


// ���ɿ󾮣���ʼ��(ע����߱���������)
void MakeMaze(int width, int height)
{
	if (width % 2 != 1 || height % 2 != 1)
		return;

	int x, y;

	// ����󾮶�ά���飬����ʼ��ȫ��Ϊǽ��
	// ��߱�ʵ�ʶ� 2������Ϊ���˸���һ�����ڱ��������ڷ��㴦������
	BYTE** aryMap = new BYTE*[width + 2];
	for(x = 0; x < width + 2; x++)
	{
		aryMap[x] = new BYTE[height + 2];
		memset(aryMap[x], UNIT_WALL, height + 2);
	}

	// ����߽�(�ڱ�����)
	for (x = 0; x <= width + 1; x++)
		aryMap[x][0] = aryMap[x][height + 1] = UNIT_GROUND;
	for (y = 1; y <= height; y++)
		aryMap[0][y] = aryMap[width + 1][y] = UNIT_GROUND;

	// ������㿪ʼ�������ɿ�
	TravelMaze(((rand() % (width - 1)) & 0xfffe) + 2, ((rand() % (height - 1)) & 0xfffe) + 2, aryMap);

	// ���ó���
	aryMap[g_utExit.x + 1][g_utExit.y + 1] = UNIT_GROUND;

	// ���󾮻����� IMAGE ������
	SetWorkingImage(&g_imgMap);
	cleardevice();
	for (y = 1; y <= height; y++)
		for (x = 1; x <= width; x++)
			if (aryMap[x][y] == UNIT_WALL)
				DrawWall(x, y,  aryMap[x - 1][y] == UNIT_WALL,
								aryMap[x][y - 1] == UNIT_WALL,
								aryMap[x + 1][y] == UNIT_WALL,
								aryMap[x][y + 1] == UNIT_WALL);
	SetWorkingImage(NULL);
}


// ���ɿ󾮣����� (x, y) ����
void TravelMaze(int x, int y, BYTE** aryMap)
{
	// �����������
	int d[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
	
	// ��������������
	int n, t, i;
	for(i = 0; i < 4; i++)
	{
		n = rand() % 4;
		t = d[i][0], d[i][0] = d[n][0], d[n][0] = t;
		t = d[i][1], d[i][1] = d[n][1], d[n][1] = t;
	}
	
	// ������Χ�ĸ�����
	aryMap[x][y] = UNIT_GROUND;
	for(i = 0; i < 4; i++)
		if (aryMap[x + 2 * d[i][0]][y + 2 * d[i][1]] == UNIT_WALL)
		{
			aryMap[x + d[i][0]][y + d[i][1]] = UNIT_GROUND;
			TravelMaze(x + d[i][0] * 2, y + d[i][1] * 2, aryMap);		// �ݹ�
		}
}


// ���ɿ󾮣���һ��ǽ
// ������left/top/right/bottom ��ʾǽ���Ƿ����Ա�����
void DrawWall(int x, int y, bool left, bool top, bool right, bool bottom)
{
	// ǽ�ں� 4 pixel
	int cx, cy;
	cx = x * UNIT - UNIT / 2 - 2 + 10;
	cy = y * UNIT - UNIT / 2 - 2 + 10;
	if (left)	solidrectangle(x * UNIT - UNIT + 10, cy, cx + 4, cy + 4);
	if (top)	solidrectangle(cx, y * UNIT - UNIT + 10, cx + 4, cy + 4);
	if (right)	solidrectangle(cx, cy, x * UNIT + 9, cy + 4);
	if (bottom)	solidrectangle(cx, cy, cx + 4, y * UNIT + 9);
}


// ������Ұ��Χ�ڵĿ�
void Paint()
{
	// ���û�ͼĿ��Ϊ Render ����
	SetWorkingImage(&g_imgRender);

	// ��� Render ����
	cleardevice();

	// ������Ұ�Ƕ�
	double dx, dy, a;
	dx = g_ptMouse.x - g_ptPlayer.x;
	dy = g_ptMouse.y - g_ptPlayer.y;
	if (dx == 0 && dy == 0)
		a = 0;
	else if (dx != 0 && dy != 0)
		a = atan(dy / dx);
	else if (dx == 0)
		a = (dy > 0) ? PI / 2 : PI * 3 / 2;
	else
		a = 0;
	if (dx < 0)	a += PI;
	if (a < 0) a += PI * 2;

	// ���Ƶƹ�
	Lighting(g_ptPlayer.x, g_ptPlayer.y, a);

	// ����Ϸ��
	DrawPlayer();

	// ������
	DrawExit();

	// ���û�ͼĿ��Ϊ����
	SetWorkingImage(NULL);
	
	// ��ʾ��������
	putimage(0, 0, &g_imgRender);
}


// ��ָ��λ�úͽǶȡ�������
void Lighting(int _x, int _y, double _a)
{
	int i;		// ����ѭ������
	int x, y;	// ������ʱ����
	double a;	// ������ʱ�Ƕ�

	// ����ƹ������ĽǶ�����
	double a1 = _a - LIGHT_A / 2;
	double a2 = _a + LIGHT_A / 2;
	for(a = a1; a < a2; a += PI / 360)					// ����ѭ��
	{
		for(int r = 0; r < LIGHT_R; r++)				// �뾶ѭ��
		{
			// �������䵽��λ��
			x = (int)(_x + cos(a) * r);
			y = (int)(_y + sin(a) * r);

			// ���߳�����Ļ��Χ����ֹ
			// (Ϊ�˼�ȫƾģ�����㣬���������Ϻ�����һ��)
			if (x < 0 || x >= WIDTH || y <= 0 || y >= HEIGHT - 1)
				break;

			// ���������������ֹ
			if(g_bufMap[y * WIDTH + x])
				break;

			// ���ߵ���
			g_bufRender[y * WIDTH + x] += 0x202000;		// 0x202000 �Ǻܵ��Ļ�ɫ
		}
	}

	// ������������������С��Χ����
	// ��������� 7 �������ֵ��Բ�ġ�Բ�����ˡ�Բ�� xy ��� 4 ������
	// ��һ������ʼ�� 7 ����
	POINT pt[7];
	pt[0].x = _x;									pt[0].y = _y;
	pt[1].x = int(_x + LIGHT_R * cos(a1) + 0.5);	pt[1].y = int(_y + LIGHT_R * sin(a1) + 0.5);
	pt[2].x = int(_x + LIGHT_R * cos(a2) + 0.5);	pt[2].y = int(_y + LIGHT_R * sin(a2) + 0.5);

	for (a = ceil(a1 * 4 / (2 * PI)) * (PI / 2), i = 3; a < a2; a += PI / 2, i++)
	{
		pt[i].x = int(_x + LIGHT_R * cos(a) + 0.5);
		pt[i].y = int(_y + LIGHT_R * sin(a) + 0.5);
	}

	// �ڶ�������ȡ 7 ����������Сֵ���õ���С��Χ����
	i--;
	RECT r = {pt[i].x, pt[i].y, pt[i].x, pt[i].y};

	for (--i; i >= 0; i--)
	{
		if (pt[i].x < r.left)	r.left = pt[i].x;
		if (pt[i].x > r.right)	r.right = pt[i].x;
		if (pt[i].y < r.top)	r.top = pt[i].y;
		if (pt[i].y > r.bottom)	r.bottom = pt[i].y;
	}

	// �������η�Χ
	if (r.left < 0)				r.left	= 0;
	if (r.top < 1)				r.top	= 1;
	if (r.right >= WIDTH)		r.right	= WIDTH - 1;
	if (r.bottom >= HEIGHT - 1)	r.bottom = HEIGHT - 2;

	// �����ع���ȵĵ�
	for (y = r.top; y <= r.bottom; y++)
		for (x = r.left; x <= r.right; x++)
		{
			i = y * WIDTH + x;
			if (g_bufRender[i] > 0xffff00)
				g_bufRender[i] = 0xffff00;
		}

	// ������ģ������(�ܿ�������)
	for (y = r.top; y <= r.bottom; y++)
		for (x = r.left; x <= r.right; x++)
		{
			i = y * WIDTH + x;
			if (!g_bufMap[i])
				g_bufRender[i] = RGB(
					(GetRValue(g_bufRender[i - WIDTH]) + GetRValue(g_bufRender[i - 1]) + GetRValue(g_bufRender[i])
								+ GetRValue(g_bufRender[i + 1]) + GetRValue(g_bufRender[i + WIDTH])) / 5,
					(GetGValue(g_bufRender[i - WIDTH]) + GetGValue(g_bufRender[i - 1]) + GetGValue(g_bufRender[i])
								+ GetGValue(g_bufRender[i + 1]) + GetGValue(g_bufRender[i + WIDTH])) / 5,
					(GetBValue(g_bufRender[i - WIDTH]) + GetBValue(g_bufRender[i - 1]) + GetBValue(g_bufRender[i])
								+ GetBValue(g_bufRender[i + 1]) + GetBValue(g_bufRender[i + WIDTH])) / 5);
		}
}


// ������Ϸ��
void DrawPlayer()
{
	// ����ȫñ
	setlinecolor(DARKGRAY);
	circle(g_ptPlayer.x, g_ptPlayer.y, 5);
}


// ���Ƴ���
void DrawExit()
{
	settextstyle(12, 0, _T("����"));
	outtextxy(g_utExit.x * UNIT + g_ptOffset.x, g_utExit.y * UNIT + g_ptOffset.y + 8, _T("����"));
}


// ��ȡ�û����������
int GetCmd()
{
	int c = 0;

	if ((GetAsyncKeyState(VK_LEFT)	& 0x8000) ||
		(GetAsyncKeyState('A')		& 0x8000))		c |= CMD_LEFT;
	if ((GetAsyncKeyState(VK_RIGHT)	& 0x8000) ||
		(GetAsyncKeyState('D')		& 0x8000))		c |= CMD_RIGHT;
	if ((GetAsyncKeyState(VK_UP)	& 0x8000) ||
		(GetAsyncKeyState('W')		& 0x8000))		c |= CMD_UP;
	if ((GetAsyncKeyState(VK_DOWN)	& 0x8000) ||
		(GetAsyncKeyState('S')		& 0x8000))		c |= CMD_DOWN;
	if (GetAsyncKeyState(VK_F2)		& 0x8000)		c |= CMD_RESTART;
	if (GetAsyncKeyState(VK_ESCAPE)	& 0x8000)		c |= CMD_QUIT;

	MOUSEMSG m;
	while(MouseHit())
	{
		m = GetMouseMsg();
		g_ptMouse.x = m.x;
		g_ptMouse.y = m.y;
	}

	return c;
}


// �����ƶ�
void OnUp()
{
	int i = (g_ptPlayer.y - 6) * WIDTH + (g_ptPlayer.x - 5) + 1;
	int j;
	for (j = 0; j < 5; j++, i += 2)
		if (g_bufMap[i])
			break;

	if (j == 5)
		g_ptPlayer.y--;
}


// �����ƶ�
void OnLeft()
{
	int i = (g_ptPlayer.y - 5) * WIDTH + (g_ptPlayer.x - 5);
	int j;
	for (j = 0; j < 5; j++, i += WIDTH)
		if (g_bufMap[i])
			break;

	if (j == 5)
		g_ptPlayer.x--;
}


// �����ƶ�
void OnRight()
{
	int i = (g_ptPlayer.y - 5) * WIDTH + (g_ptPlayer.x + 5) + 1;
	int j;
	for (j = 0; j < 5; j++, i += WIDTH)
		if (g_bufMap[i])
			break;

	if (j == 5)
		g_ptPlayer.x++;
}


// �����ƶ�
void OnDown()
{
	int i = (g_ptPlayer.y + 5) * WIDTH + (g_ptPlayer.x - 5) + 1;
	int j;
	for (j = 0; j < 5; j++, i += 2)
		if (g_bufMap[i])
			break;

	if (j == 5)
		g_ptPlayer.y++;
}


// ����Ƿ񵽳���
bool CheckWin()
{
	return (g_ptPlayer.y >= g_utExit.y * UNIT + UNIT / 2 + g_ptOffset.y);
}