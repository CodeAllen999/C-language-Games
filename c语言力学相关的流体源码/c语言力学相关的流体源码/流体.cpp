#include <graphics.h>
#include <math.h>
#include <time.h>

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

#define WIDTH		1024		// ��Ļ��
#define HEIGHT		576			// ��Ļ��
#define NUM_MOVERS	600			// С������
#define	FRICTION	0.96f		// Ħ����


// ����С��ṹ
struct Mover
{
	COLORREF	color;			// ��ɫ
	float		x, 	y;			// ����
	float		vX,	vY;			// �ٶ�
};


// ����ȫ�ֱ���
Mover	movers[NUM_MOVERS];			// С������
int		mouseX,		mouseY;			// ��ǰ�������
int		mouseVX,	mouseVY;		// ����ٶ�
int		prevMouseX,	prevMouseY;		// �ϴ��������
bool	isMouseDown;				// �������Ƿ���
DWORD*	pBuffer;					// �Դ�ָ��


// ��ʼ��
void init()
{
	// ��ʼ��С������
	for (int i = 0; i < NUM_MOVERS; i++)
	{
		movers[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		movers[i].x   = WIDTH * 0.5;
		movers[i].y   = HEIGHT * 0.5;
		movers[i].vX  = float(cos(float(i))) * (rand() % 34);
		movers[i].vY  = float(sin(float(i))) * (rand() % 34);
	}
	
	// ��ʼ��������
	mouseX = prevMouseX = WIDTH / 2;
	mouseY = prevMouseY = HEIGHT / 2;

	// �����������
	srand((unsigned int)time(NULL));

	// ��ȡ�Դ�ָ��
	pBuffer = GetImageBuffer(NULL);
}


// ȫ���䰵 50%
void darken()
{
	for(int i = WIDTH * HEIGHT - 1; i >= 0; i--)
		if (pBuffer[i] != 0)
			pBuffer[i] = RGB(GetRValue(pBuffer[i]) >> 1, GetGValue(pBuffer[i]) >> 1, GetBValue(pBuffer[i]) >> 1);
}


// ������ʱ
void delay(DWORD ms)
{
	static DWORD oldtime = GetTickCount();

	while(GetTickCount() - oldtime < ms)
		Sleep(1);

	oldtime = GetTickCount();
}


// ���ƶ���(һ֡)
void run()
{
	darken();	// ȫ���䰵

	mouseVX    = mouseX - prevMouseX;
	mouseVY    = mouseY - prevMouseY;
	prevMouseX = mouseX;
	prevMouseY = mouseY;
	
	float toDist   = WIDTH * 0.86f;
	float stirDist = WIDTH * 0.125f;
	float blowDist = WIDTH * 0.5f;
	
	for(int i = 0; i < NUM_MOVERS; i++)
	{
		float x  = movers[i].x;
		float y  = movers[i].y;
		float vX = movers[i].vX;
		float vY = movers[i].vY;
		
		float dX = x - mouseX;
		float dY = y - mouseY; 
		float d  = (float)sqrt(dX * dX + dY * dY);
		dX = d ? dX / d : 0;
		dY = d ? dY / d : 0;
		
		if (isMouseDown && d < blowDist)
		{
			float blowAcc = (1 - (d / blowDist)) * 14;
			vX += dX * blowAcc + 0.5f - float(rand()) / RAND_MAX;
			vY += dY * blowAcc + 0.5f - float(rand()) / RAND_MAX;
		}
		
		if (d < toDist)
		{
			float toAcc = (1 - (d / toDist)) * WIDTH * 0.0014f;
			vX -= dX * toAcc;
			vY -= dY * toAcc;			
		}
		
		if (d < stirDist)
		{
			float mAcc = (1 - (d / stirDist)) * WIDTH * 0.00026f;
			vX += mouseVX * mAcc;
			vY += mouseVY * mAcc;			
		}
		
		vX *= FRICTION;
		vY *= FRICTION;
		
		float avgVX = (float)fabs(vX);
		float avgVY = (float)fabs(vY);
		float avgV  = (avgVX + avgVY) * 0.5f;
		
		if (avgVX < 0.1) vX *= float(rand()) / RAND_MAX * 3;
		if (avgVY < 0.1) vY *= float(rand()) / RAND_MAX * 3;
		
		float sc = avgV * 0.45f;
		sc = max(min(sc, 3.5f), 0.4f);
		
		float nextX = x + vX;
		float nextY = y + vY;
		
		if		(nextX > WIDTH)	{ nextX = WIDTH;	vX *= -1; }
		else if (nextX < 0)		{ nextX = 0;		vX *= -1; }
		if		(nextY > HEIGHT){ nextY = HEIGHT;	vY *= -1; }
		else if (nextY < 0)		{ nextY = 0;		vY *= -1; }
		
		movers[i].vX = vX;
		movers[i].vY = vY;
		movers[i].x  = nextX;
		movers[i].y  = nextY;
		
		// ��С��
		setcolor(movers[i].color);
		setfillstyle(movers[i].color);
		fillcircle(int(nextX + 0.5), int(nextY + 0.5), int(sc + 0.5));
	}
}


// ������
void main()
{
	// ������ͼ����
	initgraph(WIDTH, HEIGHT);
	// ��������ͼģʽ
	BeginBatchDraw();

	// ��ʼ��
	init();

	// �����Ϣ����
	MOUSEMSG m;

	while(true)
	{
		// ���������Ϣ
		while(MouseHit())
		{
			m = GetMouseMsg();

			switch(m.uMsg)
			{
				case WM_MOUSEMOVE:		mouseX = m.x;	mouseY = m.y;	break;
				case WM_LBUTTONDOWN:	isMouseDown = true;				break;
				case WM_LBUTTONUP:		isMouseDown = false;			break;
			}
		}

		// ���ƶ���
		run();

		// ��ʾ����Ļ�������
		FlushBatchDraw();

		// ��ʱ 20 ����
		delay(20);
	}

	// �ر�
	EndBatchDraw();
	closegraph();
}