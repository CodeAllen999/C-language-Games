#undef UNICODE
#undef _UNICODE
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>

#define MAXTASK 50							// ������Ϸ��Ҫ��ɵĺڿ�����

// ����� __sprintf ����Ӧ vc6 �� vc2013
#if _MSC_VER > 1200
	#define __sprintf(...) sprintf_s(__VA_ARGS__)
#else
	#define __sprintf sprintf
#endif


// ��ȷ��ʱ����(���Ծ�ȷ�� 1ms������ ��1ms)
/* ����ѧȥ����վ�ռ� http://www.zixue7.com */
void HpSleep(int ms)
{
	static clock_t oldclock = clock();		// ��̬��������¼��һ�� tick

	oldclock += ms * CLOCKS_PER_SEC / 1000;	// ���� tick

	if (clock() > oldclock)					// ����Ѿ���ʱ��������ʱ
		oldclock = clock();
	else
		while (clock() < oldclock)			// ��ʱ
			Sleep(1);						// �ͷ� CPU ����Ȩ������ CPU ռ����
}


// ��Ϸ״̬����
enum STATUS{BEGIN,			// ��Ϸ��ʼ
			RUNNING,		// ��Ϸ������
			PASSANI,		// ��Ϸͨ���Ķ���
			PASS,			// ��Ϸͨ��
			FAILANI,		// ��Ϸʧ�ܵĶ���
			FAIL };			// ��Ϸʧ��


// ��Ϸ���ࣨÿ����Ϸ�߶���һ����������Ϸ����
class PLAYER
{
private:
	STATUS	m_status;					// ��Ϸ״̬
	char*	m_strName;					// ��Ϸ������
	POINT	m_offset;					// �����ƫ����
	char*	m_keys;						// ����

	// ����
	byte	m_Task[MAXTASK];			// �����б�
	byte	m_iTask;					// ��ǰ��Ҫִ�е����� ID
	int		m_nextTaskY;				// ��������һ������� Y ����

	// ʱ�Ӻ���Ϸ��¼
	clock_t	m_beginClock;				// ��Ϸ��ʼ��ʱ�Ӽ���
	float	m_bestTime;					// ��Ѽ�¼�����ʱ��
	float	m_lastTime;					// ���һ�ε����ʱ��

	// ����ʧ�ܶ����ı���
	byte	m_failErrorKey;				// ����ļ�����ţ�ֵΪ 0��1��2��3��
	RECT	m_failRect;					// ����ļ�������
	int		m_failFrame;				// ʧ�ܺ�Ķ�����֡����

public:
	PLAYER(char* name, char* keys, int offsetx, int offsety);		// ���캯��
	void Hit(char key);												// ������Ϸ�߰���
	void Draw();													// ���Ƹ���Ϸ�ߵ���Ϸ����
private:
	void Init();						// ��ʼ����ǰ��Ϸ�ߵ���Ϸ��Ϣ
	void DrawFrame();					// ������Ϸ��������
	void DrawRow(int baseY, int iTask);	// ������Ϸ�����е�һ������
	void DrawPass();					// ����ͨ����Ϸ��Ľ���
	void DrawFail();					// ������Ϸʧ�ܺ�Ľ���

	// ����ƫ��������Ļ�ͼ����
	void OutTextXY(int x, int y, LPCTSTR s)							// ��ָ��λ������ַ���
	{
		outtextxy(m_offset.x + x, m_offset.y + y, s);
	}
	void OutTextXY(int x, int y, char c)							// ��ָ��λ������ַ�
	{
		outtextxy(m_offset.x + x, m_offset.y + y, c);
	}
	void Rectangle(int x1, int y1, int x2, int y2)					// ���ƾ���
	{
		rectangle(m_offset.x + x1, m_offset.y + y1, m_offset.x + x2, m_offset.y + y2);
	}
	void FillRectangle(int x1, int y1, int x2, int y2)				// �����б߿�������
	{
		fillrectangle(m_offset.x + x1, m_offset.y + y1, m_offset.x + x2, m_offset.y + y2);
	}
	void SolidRectangle(int x1, int y1, int x2, int y2)				// �����ޱ߿�������
	{
		solidrectangle(m_offset.x + x1, m_offset.y + y1, m_offset.x + x2, m_offset.y + y2);
	}
};


// ���캯��
//	������
//		name: ��Ϸ������
//		keys: ��Ϸ�����ð�����ָ�򳤶�Ϊ 4 ���ַ�����
//		offsetx, offsety: ��Ϸ�߶�Ӧ����Ϸ�������������е�ƫ����
PLAYER::PLAYER(char* name, char* keys, int offsetx, int offsety)
{
	m_strName	= name;
	m_keys		= keys;
	m_offset.x	= offsetx;
	m_offset.y	= offsety;

	m_bestTime	= 99;	// ������ѳɼ�

	Init();				// ��ʼ����Ϸ��
}


// ��ʼ����ǰ��Ϸ�ߵ���Ϸ��Ϣ
void PLAYER::Init()
{
	// ��ʼ������
	for (int i = 0; i < MAXTASK; i++)
		m_Task[i] = rand() % 4;

	m_iTask		= 0;			// �ӵ�һ������ʼ
	m_nextTaskY	= 200;			// �趨��һ������� Y ���꣬100 �ǻ�׼��200 ��ʾ��ʼ��������Ķ���
	m_status	= BEGIN;		// ������Ϸ��ʼ״̬
	m_failFrame = 0;			// ����ʧ�ܺ�Ķ�����֡����

	// ��ʼ����Ϸ����
	DrawFrame();
}


// ���Ƹ���Ϸ�ߵ���Ϸ����
void PLAYER::Draw()
{
	switch (m_status)
	{
		case PASSANI:			// ��Ϸ�ɹ���Ķ���
			if (m_nextTaskY == 100)
			{
				m_status = PASS;
				DrawPass();
				break;
			}

		case BEGIN:				// ��Ϸ���ο�ʼ
		case RUNNING:			// ��Ϸ������
		{
			// ������洦�ھ�ֹ��ֱ�ӷ��ز����ػ�
			if (m_nextTaskY == 100)
				return;

			m_nextTaskY -= (m_nextTaskY - 100 + 9) / 10;

			// ������ɵ�������
			int rowy = m_nextTaskY;
			int itask = m_iTask;
			do
			{
				rowy -= 100;
				itask--;
				DrawRow(rowy, itask);
			} while (rowy > 0);

			// ����δ��ɵ�������
			rowy = m_nextTaskY;
			itask = m_iTask;
			do
			{
				DrawRow(rowy, itask);
				rowy += 100;
				itask++;
			} while (rowy < 400);

			break;
		}

		case FAILANI:			// ��Ϸʧ�ܺ�Ķ���
			DrawFail();
			break;

		case PASS:				// ��Ϸͨ����ĳɼ���ʾ
		case FAIL:				// ��Ϸʧ�ܺ�ĳɼ���ʾ
			break;
	}
}


// ������Ϸ��������
void PLAYER::DrawFrame()
{
	// �����
	setlinecolor(0xfb9700);
	Rectangle(0, 0, 243, 464);
	setfillcolor(0xeca549);
	settextcolor(BLACK);
	settextstyle(16, 0, "Verdana");
	setbkmode(TRANSPARENT);

	// ��������
	SolidRectangle(2, 2, 241, 21);
	int w = textwidth(m_strName);
	OutTextXY((244 - w) / 2, 4, m_strName);

	// ���ɼ���
	SolidRectangle(2, 23, 241, 42);
	char tmp[50];
	__sprintf(tmp, "��ü�¼��%.3f ��", m_bestTime);
	OutTextXY(10, 26, tmp);

	// 2 <= x <= 241, 44 <= y <= 443 Ϊ��Ϸ��

	// ��������
	SolidRectangle(2, 445, 241, 462);
	for (int i = 0; i < 4; i++)
		OutTextXY(2 + i * 60 + 26, 446, m_keys[i]);
}


// ������Ϸ�����е�һ������
void PLAYER::DrawRow(int baseY, int iTask)
{
	int fromY = baseY;				// �����е���ʼ y ����
	int toY = baseY + 99;			// �����е���ֹ y ����

	// ��� y ���곬����ʾ��Χ��������
	if (fromY < 0) fromY = 0;
	if (toY > 399) toY = 399;

	COLORREF c[4];					// �������ĸ��������ɫ
	if (iTask < 0)
	{
		for (int i = 0; i < 4; i++)
			c[i] = YELLOW;
	}
	else if (iTask >= MAXTASK)
	{
		for (int i = 0; i < 4; i++)
			c[i] = GREEN;
	}
	else
	{
		for (int i = 0; i < 4; i++)
			c[i] = WHITE;
		
		c[m_Task[iTask]] = (iTask < m_iTask)? LIGHTGRAY : BLACK;
	}

	// �������е��ĸ�����
	setlinecolor(0xe9dbd6);
	for (int i = 0; i < 4; i++)
	{
		setfillcolor(c[i]);
		FillRectangle(2 + i * 60, 44 + 399 - fromY, 2 + i * 60 + 59, 44 + 399 - toY);
	}

	// ����ǵ�һ�У��ڷ������д����ʼ��������
	if (iTask == 0 && m_iTask == 0)
	{
		int w = textwidth("��ʼ");
		int h = textheight("��ʼ");
		int x = 2 + m_Task[iTask] * 60 + (60 - w) / 2;
		int y = 44 + 399 - 99 - fromY + (100 - h) / 2;
		settextcolor(WHITE);
		settextstyle(16, 0, "Verdana");
		OutTextXY(x, y, "��ʼ");
	}
}


// ����ͨ����Ϸ��Ľ���
void PLAYER::DrawPass()
{
	// ���Ƴɹ��ı���
	setfillcolor(GREEN);
	SolidRectangle(2, 44, 241, 443);

	// ���"�ɹ�"
	settextcolor(WHITE);
	settextstyle(60, 0, "Verdana");
	int w = textwidth("�ɹ�");
	OutTextXY((244 - w) / 2, 100, "�ɹ�");

	// ����ɼ�
	char tmp[100];
	settextstyle(32, 0, "Verdana");
	__sprintf(tmp, "�ɼ���%.3f ��", m_lastTime);
	w = textwidth(tmp);
	OutTextXY((244 - w) / 2, 200, tmp);
	__sprintf(tmp, "�ٶȣ�%.3f/s", MAXTASK / m_lastTime);
	OutTextXY((244 - w) / 2, 240, tmp);

	// ������¿�ʼ����ʾ
	settextstyle(16, 0, "Verdana");
	w = textwidth("��������Ƽ����¿�ʼ");
	OutTextXY((244 - w) / 2, 400, "��������Ƽ����¿�ʼ");
}


// ������Ϸʧ�ܺ�Ľ���
void PLAYER::DrawFail()
{
	if (m_failFrame == 0)
	{	// ��ʼ����������˸Ч��������
		m_failRect.left		= 3 + m_failErrorKey * 60;
		m_failRect.right	= m_failRect.left + 57;
		m_failRect.bottom	= m_nextTaskY + 1;
		m_failRect.top		= m_nextTaskY + 98;

		if (m_failRect.top > 398) m_failRect.top = 398;
		m_failRect.bottom	= 44 + 399 - m_failRect.bottom;
		m_failRect.top		= 44 + 399 - m_failRect.top;
	}

	if (m_failFrame < 60)
	{	// ʵ����˸Ч��
		setfillcolor(((m_failFrame / 6) % 2 == 0) ? RED : LIGHTRED);
		SolidRectangle(m_failRect.left, m_failRect.bottom, m_failRect.right, m_failRect.top);
		m_failFrame++;
	}
	else
	{
		// �ı���Ϸ״̬
		m_status = FAIL;

		// ����ʧ�ܵı���
		setfillcolor(RED);
		SolidRectangle(2, 44, 241, 443);

		// ���"ʧ��"
		settextcolor(WHITE);
		settextstyle(60, 0, "Verdana");
		int w = textwidth("ʧ��");
		OutTextXY((244 - w) / 2, 100, "ʧ��");

		// �����ʷ�ɼ�
		settextstyle(20, 0, "Verdana");
		char tmp[100];
		__sprintf(tmp, "��ʷ��óɼ���%.3f ��", m_bestTime);
		w = textwidth(tmp);
		OutTextXY((244 - w) / 2, 200, tmp);

		// ������¿�ʼ����ʾ
		settextstyle(16, 0, "Verdana");
		w = textwidth("��������Ƽ����¿�ʼ");
		OutTextXY((244 - w) / 2, 400, "��������Ƽ����¿�ʼ");
	}
}


// ������Ϸ�߰���
void PLAYER::Hit(char key)
{
	switch (m_status)
	{
		case BEGIN:				// ��Ϸ���ο�ʼ
			if (strchr(m_keys, key) != NULL)
			{
				m_beginClock = clock();				// ��¼��Ϸ��ʼʱ��ʱ��
				m_status = RUNNING;					// �ı���Ϸ״̬
			}

		case RUNNING:			// ��Ϸ������
		{
			char* pdest = strchr(m_keys, key);
			byte pos;
			if (pdest != NULL)						// �ж��Ƿ��ǵ�ǰ��Ϸ�߰���
			{
				pos = pdest - m_keys;				// ���㰴����Ӧ��λ��

				if (pos == m_Task[m_iTask])			// �жϰ����Ƿ���ȷ
				{
					// ������ȷ
					m_iTask++;
					m_nextTaskY += 100;

					if (m_iTask == MAXTASK)			// ��������ȫ������
					{
						// �������ʱ��
						clock_t t = clock();
						m_lastTime = ((float)(clock() - m_beginClock)) / CLOCKS_PER_SEC;

						// ������ü�¼
						if (m_lastTime < m_bestTime)
							m_bestTime = m_lastTime;

						// �����һ�������������Ļ
						m_iTask++;
						m_nextTaskY += 100;
						m_status = PASSANI;
					}
				}
				else
				{
					// ����ʧ��
					m_failErrorKey = pos;
					m_status = FAILANI;
				}
			}

			break;
		}

		case PASSANI:			// ��Ϸ�ɹ���Ķ���
		case FAILANI:			// ��Ϸʧ�ܺ�Ķ���
			break;

		case PASS:				// ��Ϸͨ����ĳɼ���ʾ
		case FAIL:				// ��Ϸʧ�ܺ�ĳɼ���ʾ
			if (strchr(m_keys, key) != NULL)
				Init();
			break;
	}
}


// �������������
void main()
{

	initgraph(640, 480);					// ������ͼ����
	srand((unsigned)time(NULL));			// ���������������

	setbkcolor(0x01bbfb);
	cleardevice();

	PLAYER p1("ϲ����", "asdf", 38, 8);		// ������Ϸ�� ϲ����
	PLAYER p2("��̫��", "jkl;", 358, 8);	// ������Ϸ�� ��̫��

	char c = 0;

	while (c != 27)
	{
		while (_kbhit())					// �ж��Ƿ��а���
		{
			// ��������
			c = _getch();
			p1.Hit(c);
			p2.Hit(c);
		}

		// ������Ϸ����
		p1.Draw();
		p2.Draw();

		// ��ʱ
		HpSleep(16);
	}

	// ������Ϸ
	closegraph();							// �رջ�ͼ����
}