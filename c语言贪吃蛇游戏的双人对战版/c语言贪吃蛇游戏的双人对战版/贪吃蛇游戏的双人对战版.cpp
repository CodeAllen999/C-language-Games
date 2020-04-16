/* ����ѧȥ����վ�ռ� http://www.zixue7.com */
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <queue>

using namespace std;

#define	WIDTH		64			// ��Ϸ����������
#define	HEIGHT		48			// ��Ϸ��������߶�
#define	ITEMSIZE	10			// ��ϷԪ�ش�С
#define	CMD_A_UP	0x1			// ���������Ϸ�� A ����
#define	CMD_A_DOWN	0x2			// ���������Ϸ�� A ����
#define	CMD_A_LEFT	0x4			// ���������Ϸ�� A ����
#define	CMD_A_RIGHT	0x8			// ���������Ϸ�� A ����
#define	CMD_B_UP	0x10		// ���������Ϸ�� B ����
#define	CMD_B_DOWN	0x20		// ���������Ϸ�� B ����
#define	CMD_B_LEFT	0x40		// ���������Ϸ�� B ����
#define	CMD_B_RIGHT	0x80		// ���������Ϸ�� B ����
#define	CMD_QUIT	0x100		// ��������˳���Ϸ

// ������ϷԪ��
enum ITEM { EMPTY = 0, WALL, PLAYER_A, PLAYER_B, PLAYER_DEAD, PLAYER_A_NEXT, PLAYER_B_NEXT };

// ȫ�ֱ���
ITEM	g_world[WIDTH][HEIGHT];	// ������Ϸ��
POINT	g_player_a;				// ��Ϸ�� A ������
POINT	g_player_b;				// ��Ϸ�� B ������
POINT	g_offset_a;				// ��Ϸ�� A ���ƶ�ƫ�Ʒ���
POINT	g_offset_b;				// ��Ϸ�� B ���ƶ�ƫ�Ʒ���



// ������ϷԪ��
void DrawItem(int x, int y, ITEM item)
{
	switch(item)
	{
		case EMPTY:			setfillcolor(BLACK);		break;
		case WALL:			setfillcolor(LIGHTGRAY);	break;
		case PLAYER_A:		setfillcolor(BLUE);			break;
		case PLAYER_B:		setfillcolor(RED);			break;
		case PLAYER_DEAD:	setfillcolor(MAGENTA);		break;
	}
	bar(x * ITEMSIZE + 1, y * ITEMSIZE + 1, (x + 1) * ITEMSIZE - 2, (y + 1) * ITEMSIZE - 2);
	g_world[x][y] = item;
}



// ��ʼ����Ϸ
void init()
{
	int x, y;

	// ����ǽ��
	for(x = 0; x < WIDTH; x++)
	{
		DrawItem(x, 0, WALL);
		DrawItem(x, HEIGHT - 1, WALL);
	}
	for(y = 1; y < HEIGHT - 1; y++)
	{
		DrawItem(0, y, WALL);
		DrawItem(WIDTH - 1, y, WALL);
	}

	// ������Ϸ����
	for (x = 1; x < WIDTH - 1; x++)
		for (y = 1; y < HEIGHT - 1; y++)
			DrawItem(x, y, EMPTY);

	// �������������Ϸ�ߵ�λ�ã����ټ�� 5 ��
	do
	{
		g_player_a.x = rand() % (WIDTH - 6) + 3;	g_player_a.y = rand() % (HEIGHT - 6) + 3;
		g_player_b.x = rand() % (WIDTH - 6) + 3;	g_player_b.y = rand() % (HEIGHT - 6) + 3;
	}while (  (g_player_b.x - g_player_a.x) * (g_player_b.x - g_player_a.x)
			+ (g_player_b.y - g_player_a.y) * (g_player_b.y - g_player_b.x) <= 25);
	// ����������Ϸ�ߵ�λ��
	DrawItem(g_player_a.x, g_player_a.y, PLAYER_A);
	DrawItem(g_player_b.x, g_player_b.y, PLAYER_B);

	// �������������Ϸ�ߵ��ƶ�����
	// �÷�����ԭ�������http://www.easyx.cn/skills/View.aspx?id=115
	int n;
	n = (rand() % 4) * 2 + 1;	g_offset_a.x = n / 3 - 1;	g_offset_a.y = n % 3 - 1;
	n = (rand() % 4) * 2 + 1;	g_offset_b.x = n / 3 - 1;	g_offset_b.y = n % 3 - 1;

	// ���� Player A ���ķ�����ʾ�ƶ�����
	int tx = g_player_a.x + g_offset_a.x;
	int ty = g_player_a.y + g_offset_a.y;
	setcolor(BLUE);
	rectangle(tx * ITEMSIZE + 1, ty * ITEMSIZE + 1, (tx + 1) * ITEMSIZE - 2, (ty + 1) * ITEMSIZE - 2);
	// ���� Player B ���ķ�����ʾ�ƶ�����
	tx = g_player_b.x + g_offset_b.x;
	ty = g_player_b.y + g_offset_b.y;
	setcolor(RED);
	rectangle(tx * ITEMSIZE + 1, ty * ITEMSIZE + 1, (tx + 1) * ITEMSIZE - 2, (ty + 1) * ITEMSIZE - 2);

	// ��ȷ����ʼ��Ϸ
	MessageBox(GetHWnd(), _T("��ս̰���� ��Ϸ˵����\n\n") \
		_T("��ϷĿ�꣺�����ߣ�������ǽ�ڻ������κ��ߵ���������䡣\n") \
		_T("Player A ʹ�� A S D W ������ɫС���ƶ�����\n") \
		_T("Player B ʹ���������ҿ��ƺ�ɫС���ƶ�����\n\n") \
		_T("�㡰ȷ������ť��ʼ��Ϸ��"), _T("��Ϸ˵��"), MB_OK | MB_ICONINFORMATION);
}



// ��ȡ�û�����
int GetCmd()
{
	// ���������û����������
	static queue<int> PLAYER_A_CMD;
	static queue<int> PLAYER_B_CMD;

	// ����ÿ�η��ص�����
	int cmd = 0;

	// ������
	while(_kbhit())
	{
		switch(_getch())
		{
			case  27:				cmd  = CMD_QUIT;	break;
			case 'W':	case 'w':	if (PLAYER_A_CMD.size() < 16)	PLAYER_A_CMD.push(CMD_A_UP);	break;
			case 'S':	case 's':	if (PLAYER_A_CMD.size() < 16)	PLAYER_A_CMD.push(CMD_A_DOWN);	break;
			case 'A':	case 'a':	if (PLAYER_A_CMD.size() < 16)	PLAYER_A_CMD.push(CMD_A_LEFT);	break;
			case 'D':	case 'd':	if (PLAYER_A_CMD.size() < 16)	PLAYER_A_CMD.push(CMD_A_RIGHT);	break;
			case  0 :	case 0xE0:
				switch(_getch())
				{
					case 72:		if (PLAYER_B_CMD.size() < 16)	PLAYER_B_CMD.push(CMD_B_UP);	break;
					case 80:		if (PLAYER_B_CMD.size() < 16)	PLAYER_B_CMD.push(CMD_B_DOWN);	break;
					case 75:		if (PLAYER_B_CMD.size() < 16)	PLAYER_B_CMD.push(CMD_B_LEFT);	break;
					case 77:		if (PLAYER_B_CMD.size() < 16)	PLAYER_B_CMD.push(CMD_B_RIGHT);	break;
				}
		}
	}

	// ��ȡ Player A ������
	int c = 0;
	while(!PLAYER_A_CMD.empty())
	{
		c = PLAYER_A_CMD.front();
		PLAYER_A_CMD.pop();
		if ((c == CMD_A_UP	 || c == CMD_A_DOWN)  && g_offset_a.x != 0)	break;
		if ((c == CMD_A_LEFT || c == CMD_A_RIGHT) && g_offset_a.y != 0)	break;
	}
	if (c != 0)
		cmd |= c;

	// ��ȡ Player B ������
	c = 0;
	while(!PLAYER_B_CMD.empty())
	{
		c = PLAYER_B_CMD.front();
		PLAYER_B_CMD.pop();
		if ((c == CMD_B_UP	 || c == CMD_B_DOWN)  && g_offset_b.x != 0)	break;
		if ((c == CMD_B_LEFT || c == CMD_B_RIGHT) && g_offset_b.y != 0)	break;
	}
	if (c != 0)	cmd |= c;

	// ��������
	return cmd;
}



// ��������
bool DealCmd(int cmd)
{
	if ((cmd & CMD_A_UP)	&& g_offset_a.x != 0)	{ g_offset_a.x = 0;		g_offset_a.y = -1;	}
	if ((cmd & CMD_A_DOWN)	&& g_offset_a.x != 0)	{ g_offset_a.x = 0;		g_offset_a.y = 1;	}
	if ((cmd & CMD_A_LEFT)	&& g_offset_a.y != 0)	{ g_offset_a.x = -1;	g_offset_a.y = 0;	}
	if ((cmd & CMD_A_RIGHT) && g_offset_a.y != 0)	{ g_offset_a.x = 1;		g_offset_a.y = 0;	}
	if ((cmd & CMD_B_UP)	&& g_offset_b.x != 0)	{ g_offset_b.x = 0;		g_offset_b.y = -1;	}
	if ((cmd & CMD_B_DOWN)	&& g_offset_b.x != 0)	{ g_offset_b.x = 0;		g_offset_b.y = 1;	}
	if ((cmd & CMD_B_LEFT)	&& g_offset_b.y != 0)	{ g_offset_b.x = -1;	g_offset_b.y = 0;	}
	if ((cmd & CMD_B_RIGHT)	&& g_offset_b.y != 0)	{ g_offset_b.x = 1;		g_offset_b.y = 0;	}
	if (cmd & CMD_QUIT)
		if (MessageBox(GetHWnd(), _T("��Ҫ�˳���Ϸ��"), _T("��Ϸ��ͣ"), MB_OKCANCEL) == IDOK)
			return false;

	return true;
}



// ������Ϸ
bool DealGame()
{
	// Player A��B ǰ��
	g_player_a.x += g_offset_a.x;
	g_player_a.y += g_offset_a.y;
	g_player_b.x += g_offset_b.x;
	g_player_b.y += g_offset_b.y;

	// �ж� Player A��B ������״̬
	bool dead_a = false, dead_b = false, dead_ab = false;

	if (g_player_a.x == g_player_b.x && g_player_a.y == g_player_b.y)
	{
		DrawItem(g_player_a.x, g_player_a.y, PLAYER_DEAD);
		dead_ab = true;
	}
	else if (g_world[g_player_a.x][g_player_a.y] != EMPTY)
	{
		DrawItem(g_player_a.x, g_player_a.y, PLAYER_DEAD);
		dead_a = true;
	}
	else if (g_world[g_player_b.x][g_player_b.y] != EMPTY)
	{
		DrawItem(g_player_b.x, g_player_b.y, PLAYER_DEAD);
		dead_b = true;
	}
	else
	{
		DrawItem(g_player_a.x, g_player_a.y, PLAYER_A);
		DrawItem(g_player_b.x, g_player_b.y, PLAYER_B);
		return true;
	}

	// �ж��Ƿ�Ҫ���¿�ʼ
	bool restart = false;

	if (dead_ab || (dead_a && dead_b))
		restart = MessageBox(GetHWnd(), _T("Player A �� Player B �����ˡ�\nҪ����һ����"),
							_T("GAME OVER"), MB_YESNO | MB_ICONINFORMATION) == IDYES;
	else if (dead_a)
		restart = MessageBox(GetHWnd(), _T("Player A ���ˡ�\nҪ����һ����"),
							_T("GAME OVER"), MB_YESNO | MB_ICONINFORMATION) == IDYES;
	else if(dead_b)
		restart = MessageBox(GetHWnd(), _T("Player B ���ˡ�\nҪ����һ����"),
							_T("GAME OVER"), MB_YESNO | MB_ICONINFORMATION) == IDYES;

	if (restart)
	{
		init();
		return true;
	}
	else
		return false;
}



// ������
void main()
{
	initgraph(640, 480);
	srand((unsigned)time(NULL));

	// ��ʼ��
	init();

	// ��Ϸ��ѭ��
	while(true)
	{
		int cmd = GetCmd();					// ��ȡ�û�����
		if (!DealCmd(cmd))	break;			// ��������
		if (!DealGame())	break;			// ������Ϸ
		Sleep(200);							// ��ʱ
	}

	// �رջ�ͼ����
	closegraph();
}