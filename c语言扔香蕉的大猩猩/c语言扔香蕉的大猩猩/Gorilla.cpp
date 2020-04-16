// ����Ϸ�Ƿ���΢��ܹ��ϵ�һ����Ϸд�ġ�
// ��Ϸ˵�������������ʹ���㽶������Ķ��֡�
// �������������Ե����ӵĽǶȺ����ȣ�ͬʱ�㽶���ܷ��١��������ٶȺ�¥���Ӱ�졣
//
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

// ���峣��
#define	PI				3.1415926535	// Բ����
#define	SCRWIDTH		640				// ��Ļ���
#define SCRHEIGHT		480				// ��Ļ�߶�
#define	GRAVITY			9.8				// �������ٶ�
#define	BACKATTR		BLUE			// ��������ɫ
#define	OBJECTCOLOR		0x55AAFF		// ���ֵ���ɫ
#define	EXPLOSIONCOLOR	0x5500FF		// ��ը����ɫ
#define	SUNATTR			0x00FFFF		// ̫������ɫ
#define	SUNHEIGHT		40				// ̫���ĸ߶�
#define	SUNHAPPY		true			// ̫������
#define	SUNSHOCK		false			// ̫���ܾ�


// ȫ�ֱ���
IMAGE	g_imgBanana[4];		// �㽶ͼƬ
IMAGE	g_imgGorD;			// ������(˫�ַ���)
IMAGE	g_imgGorL;			// ������(��ߵ���̧��)
IMAGE	g_imgGorR;			// ������(�ұߵ���̧��)
POINT	g_ptGorilla[2];		// ������Ϸ�ߵ�λ��
int		g_iLastBuilding;	// ���һ��¥�ı��
int		g_iWind;			// ����
bool	g_bSunHit;			// �Ƿ����̫��


// ��������
void Init();												// ��ʼ��
void Intro();												// ��Ϸ����
void PlayGame(TCHAR *player1, TCHAR *player2);				// ����Ϸ����
void MakeCityScape(POINT *aryBCoor);						// �����������Ϸ����
void PlaceGorillas (POINT *aryBCoor);						// ����Ϸ�߷ŵ�¥���
void DoSun(bool smile);										// ����̫��
bool DoShot(int idPlayer, int x, int y, int* win);			// ������Ϸ�����룬ʵ�����㽶�����Է�
int  PlotShot(int startX, int startY, double angle, int velocity, int idPlayer);	// �����㽶������ʹ�㽶������Ļ
void DrawBanana(int x, int y, int r, bool d);				// �����㽶
void DoExplosion(int x, int y);								// �㽶������ı�ըЧ��
int  ExplodeGorilla(int x, int y);							// ��Ϸ��������ը
void VictoryDance(int idPlayer);							// ��������Ĵ�����(ʤ����ִ��)



// ������
void main()
{
	Init();
	Intro();
	PlayGame(_T("Player 1"), _T("Player 2"));
}



// ��ʼ������
void Init()
{
	initgraph(SCRWIDTH, SCRHEIGHT);	// ������ͼ����

	// ��ʼ���㽶ͼ��
	IMAGE tmp;
	loadimage(&tmp, _T("GIF"), _T("Banana.gif"));
	SetWorkingImage(&tmp);
	getimage(&g_imgBanana[0], 0, 0, 9, 7);
	getimage(&g_imgBanana[1], 9, 0, 9, 7);
	getimage(&g_imgBanana[2], 18, 0, 9, 7);
	getimage(&g_imgBanana[3], 27, 0, 9, 7);

	// ��ʼ��������ͼ��
	loadimage(&tmp, _T("GIF"), _T("Gorilla.gif"), 0, 0, true);
	SetWorkingImage(&tmp);
	getimage(&g_imgGorD, 0, 0, 30, 30);
	getimage(&g_imgGorL, 30, 0, 30, 30);
	getimage(&g_imgGorR, 60, 0, 30, 30);
	SetWorkingImage(NULL);
}



// ��ʾ��Ϸ����
void Intro()
{
	setfont(24, 0, _T("����"));

	// ����Ļ��������ַ���
	RECT r = {0, 40, 640, 80};
	drawtext(_T("���㽶�Ĵ�����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setfont(16, 0, _T("System"));
	r.top = 120;
	r.bottom = 480;
	drawtext(_T("�����Ϸģ�µ�΢���� 20 ����ǰ��һ��С��Ϸ��\n��֪��˭Ҳ��ӡ���أ�\n\n")
			_T("������������㽶������Ķ��֡�\n�����ͨ��������Ͷ���㽶�ĽǶȺ����ȣ�\n")
			_T("�㽶�����������ٶȵ�Ӱ�졣\nͬʱ����ע����Ļ�ײ���ʾ�����ļ�ͷ��")
			_T("�㽶ͬ�����ܷ���Ӱ�졣\n�����ļ�ͷԽ������ʾ����Խǿ��\n")
			_T("���У���Χ��¥����赲����㽶��\n"),
			&r, DT_CENTER | DT_VCENTER);

	r.top = 400;
	drawtext(_T("�����������"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	_getch();
}



// ����Ϸ����
// ������
//		player1, player2����Ϸ������
void PlayGame(TCHAR *player1, TCHAR *player2)
{
	POINT	aryBCoor[31];				// ¥��Ⱥ������
	int		aryScore[2] = {0, 0};		// ������Ϸ�ߵĵ÷�
	TCHAR	sScore[20];					// ����÷ֵ��ַ���
	int		player = 0;					// ������
  
	setbkcolor(BACKATTR);

	while(true)
    {
		cleardevice();
		srand((unsigned int)time(NULL));
		MakeCityScape(aryBCoor);
		PlaceGorillas(aryBCoor);
		DoSun(SUNHAPPY);

		bool bHit = false;
		while(bHit == false)
		{
			setcolor(WHITE);
			RECT r = {0, 0, SCRWIDTH, 20};
			drawtext(player1, &r, DT_LEFT | DT_SINGLELINE);
			drawtext(player2, &r, DT_RIGHT | DT_SINGLELINE);
			r.top = SCRHEIGHT - 40;
			r.bottom = SCRHEIGHT - 20;
			_stprintf(sScore, _T("%d >Score< %d"), aryScore[0], aryScore[1]);
			drawtext(sScore, &r, DT_CENTER | DT_SINGLELINE);

			int win;

			// ���й���������������Ϸ�߼����� true��ͬʱ������ win Ϊʤ����
			bHit = DoShot(player, g_ptGorilla[player].x, g_ptGorilla[player].y, &win);

			// ���̫�������У��ػ�̫��
			if (g_bSunHit)		DoSun(SUNHAPPY);

			// ������ж��֣����·���
			if (bHit == true)	aryScore[win]++;

			// ���湥��
			player = 1 - player;

			Sleep(100);
		}
		Sleep(1000);
	};
}



// �����������Ϸ����
// ������
//		aryBCoor[]���洢ÿһ��¥�����Ͻ�����
void MakeCityScape(POINT *aryBCoor)
{
	int x = -10;

	// ���������¥Ⱥ��б������
	int slope = rand() % 6;
	int iNewHt;				// ��¥�ĸ߶�
	switch(slope)
	{
		case 0:	iNewHt = 15;	break;		// ������
		case 1: iNewHt = 130;	break;		// �𽥽���
		case 2:
		case 3:
		case 4: iNewHt = 15;	break;		// �� "V" ��(�Ƚϳ���)
		case 5: iNewHt = 130;	break;		// "V" ��
	}

	int iBottomLine = 465;			// ��������Ͷ�
	int iHtInc = 10;				// �߶�����ֵ
	int iDefBWidth = 37;			// Ĭ�ϵĽ������
	int iRandomHeight = 120;		// ����ĸ߶Ȳ���
	int iWWidth = 3;				// �������
	int iWHeight = 6;				// �����߶�
	int iWDifV = 15;				// �����Ĵ�ֱ���
	int iWDifH = 10;				// ������ˮƽ���

	int iCurBuilding = 0;

	do
	{
		switch(slope)
		{
			case 0:		iNewHt += iHtInc;	break;
			case 1:		iNewHt -= iHtInc;	break;
			case 2:
			case 3:
			case 4:		if (x > SCRWIDTH / 2)	iNewHt -= 2 * iHtInc;
						else					iNewHt += 2 * iHtInc;
						break;
			case 5:		if (x > SCRWIDTH / 2)	iNewHt += 2 * iHtInc;
						else					iNewHt -= 2 * iHtInc;
						break;
		}

		// ����¥���ȣ�������Ƿ񳬳���Ļ
		int iBWidth = iDefBWidth + rand() % iDefBWidth;

		// ����¥��߶ȣ������¥���Ƿ񳬳���Ļ�·�
		int iBHeight = iNewHt + rand() % iRandomHeight;
		if (iBHeight < iHtInc)
			iBHeight = iHtInc;

		// ���¥���Ƿ�̫��
		if (iBottomLine - iBHeight <= 25)
			iBHeight = 20;

		// ����¥������
		aryBCoor[iCurBuilding].x = x;
		aryBCoor[iCurBuilding].y = iBottomLine - iBHeight;

		// ����¥��
		COLORREF aryBuildingColor[3] = {CYAN, LIGHTGRAY, RED};	// ����¥���������ɫ
		int colorID = rand() % 3;
		setcolor(BACKATTR);
		rectangle(x - 1, iBottomLine + 1, x + iBWidth + 1, iBottomLine - iBHeight - 1);
		setfillcolor(aryBuildingColor[colorID]);
		bar(x, iBottomLine, x + iBWidth, iBottomLine - iBHeight);

		// ���ƴ���
		int c = x + 3;
		do
		{
			for(int i = iBHeight - 3; i >= 7; i -= iWDifV)
			{
				int winColor;
				if (rand() % 4 == 0)
					winColor = DARKGRAY;
				else
					winColor = YELLOW;

				setfillcolor(winColor);
				bar(c, iBottomLine - i, c + iWWidth, iBottomLine - i + iWHeight);
			}
			c += iWDifH;
		}
		while(c < x + iBWidth - 3);

		x += iBWidth + 2;

		iCurBuilding++;
	}
	while(x < SCRWIDTH - 1);

	g_iLastBuilding = iCurBuilding - 1;		// �������һ��¥�ı��

	// �����������
	g_iWind = rand() % 61 - 30;

	// ���Ʒ����ͷ
	if (g_iWind != 0)
	{
		int windLine = g_iWind * 3 * (SCRWIDTH / 320);
		setcolor(EXPLOSIONCOLOR);
		int arrowDir = (g_iWind > 0) ? -2 : 2;
		line(SCRWIDTH / 2, SCRHEIGHT - 5, SCRWIDTH / 2 + windLine, SCRHEIGHT - 5);
		line(SCRWIDTH / 2 + windLine, SCRHEIGHT - 5, SCRWIDTH / 2 + windLine + arrowDir, SCRHEIGHT - 5 - 2);
		line(SCRWIDTH / 2 + windLine, SCRHEIGHT - 5, SCRWIDTH / 2 + windLine + arrowDir, SCRHEIGHT - 5 + 2);
	}
}



// ����Ϸ�߷ŵ�¥���(�ӱ�Ե���ڶ����������¥����)
// ������
//		aryBCoor[]��¥�����顣����ÿ��¥�����Ͻ�����
void PlaceGorillas(POINT *aryBCoor)
{    
	for (int i = 0; i <= 1; i++)
	{
		int iBNum = (i == 0) ? rand() % 2 + 1 : g_iLastBuilding - 1 - rand() % 2;
		int iBWidth = aryBCoor[iBNum + 1].x - aryBCoor[iBNum].x;

		g_ptGorilla[i].x = aryBCoor[iBNum].x + iBWidth / 2 - g_imgGorD.width / 2;
		g_ptGorilla[i].y = aryBCoor[iBNum].y - g_imgGorD.height;
		putimage(g_ptGorilla[i].x, g_ptGorilla[i].y, &g_imgGorD);
	}
}



// ����̫��
// ������
//		smile��̫���Ƿ�΢Ц
void DoSun(bool smile)
{
	// ����̫����λ��
	int x = SCRWIDTH / 2;
	int y = SUNHEIGHT - 15;

	// ����̫��
	// ��
	setcolor(SUNATTR);
	setfillcolor(SUNATTR);
	fillcircle(x, y, 12);

	// ��â
	for (double a = 0; a < PI * 2; a += PI / 8)
		line(x, y, int(x + cos(a) * 20 + 0.5), int(y + sin(a) * 16 + 0.5));

	// ��
	setcolor(BACKATTR);
	setfillcolor(BACKATTR);
	if (smile)		// ����Ц��
		arc(x - 8, y - 8, x + 8, y + 8, (210 * PI / 180), (330 * PI / 180));
	else			// �����ܾ�����("o" ����)
		fillcircle(x, y + 5, 3);

	// �۾�
	fillcircle(x - 3, y - 2, 1);
	fillcircle(x + 3, y - 2, 1);
}



// ������Ϸ�����룬ʵ�����㽶�����Է�
// ������
//		idPlayer����Ϸ��(׼�����㽶��)
//		x, y����Ϸ�ߵ�λ��
bool DoShot(int idPlayer, int x, int y, int *win)
{
	// ��������Ϣ������
	FlushMouseMsgBuffer();

	// ��������ʼλ��
	int startx = x + (idPlayer == 1 ? g_imgGorD.width : 0);
	int starty = y;
	// �Ƕȸ����ߵ�λ��
	int mx = startx, my = starty - 90;
	int oldmx = mx, oldmy = my;

	double angle = PI / 2;	// Ͷ���Ƕ�
	int velocity = 2;		// Ͷ������

	setwritemode(R2_XORPEN);
	setcolor(RED);
	line(startx, starty, mx, my);

	// ������빥���Ƕ�
	MOUSEMSG msg;
	while(true)
	{
		msg = GetMouseMsg();

		if (msg.uMsg == WM_MOUSEMOVE)
		{
			if (msg.y > y)
			{
				mx = startx + (msg.x > startx ? 90 : -90);
				my = starty;
				angle = msg.x > startx ? 0 : PI;
			}
			else if (msg.x != startx)
			{
				angle = atan(double(starty - msg.y) / (msg.x - startx));
				if (angle < 0)	angle += PI;
				mx = startx + int(cos(angle) * 90 + 0.5);
				my = starty - int(sin(angle) * 90 + 0.5);
			}
			else
			{
				mx = msg.x;
				my = y - 90;
				angle = PI / 2;
			}
			line(startx, starty, oldmx, oldmy);
			line(startx, starty, mx, my);
			oldmx = mx;
			oldmy = my;
		}
		else if (msg.uMsg == WM_LBUTTONDOWN)
			break;
	}
	line(startx, starty, oldmx, oldmy);

	// ������빥������
	setlinestyle(PS_SOLID, NULL, 8);
	oldmx = mx = startx + int(cos(angle) * velocity + 0.5);
	oldmy = my = starty - int(sin(angle) * velocity + 0.5);
	line(startx, starty, mx, my);
	while(true)
	{
		if (MouseHit())
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONUP)
				break;
		}

		mx = startx + int(cos(angle) * velocity + 0.5);
		my = starty - int(sin(angle) * velocity + 0.5);
		line(startx, starty, oldmx, oldmy);
		line(startx, starty, mx, my);
		oldmx = mx;
		oldmy = my;

		if (++velocity > 90)		velocity = 2;

		Sleep(20);
	}
	velocity *= 2;		// ��������һ��
	line(startx, starty, oldmx, oldmy);
	// �ָ�����
	setlinestyle(PS_SOLID, NULL, 1);
	setwritemode(R2_COPYPEN);

	// ʵʩ����
	g_bSunHit = false;
	int iPlayerHit = PlotShot(x, y, angle, velocity, idPlayer);

	// �������
	if (iPlayerHit == -1)
	{
		*win = -1;
		return false;
	}
	else
	{
		*win = (iPlayerHit == idPlayer) ? 1 - idPlayer : idPlayer;
		VictoryDance(*win);
		return true;
	}
}



// �����㽶������ʹ�㽶������Ļ
// ������
//		startX, startY����Ϸ��(���㽶��)������
//		angle���ӳ��ķ���(����)
//		velocity���ӳ�������
//		idPlayer����Ϸ��(���㽶��)
int PlotShot(int startX, int startY, double angle, int velocity, int idPlayer)
{
	// Ͷ�������� x��y �����ϵķ���
	double initXVel = cos(angle) * velocity;
	double initYVel = sin(angle) * velocity;

	double x, y;
	double oldx = startX;
	double oldy = startY;

	// ������Ϸ��(Ͷ������)
	putimage(startX, startY, idPlayer == 0 ? &g_imgGorL : &g_imgGorR);
	Sleep(100);
	// ������Ϸ��(վ������)
	putimage(startX, startY, &g_imgGorD);

	bool bImpact = false;		// �Ƿ���ײ
	bool bShotInSun = false;	// �Ƿ����̫��
	bool bOnScreen = true;		// �㽶�Ƿ�����Ļ��
	int  iPlayerHit = -1;		// �Ƿ���ж���(-1��δ���У�0��1���������ߵ� ID)
	bool bNeedErase = false;	// �Ƿ���Ҫ�������㽶
	POINT look[4];				// ��ײ����λ��(�㽶�������������ĸ��ߵ��е�)
	look[2].x = 0;	look[3].x = g_imgBanana[0].width - 1;
	look[0].x =		look[1].x = look[3].x / 2;
	look[0].y = 0;	look[1].y = g_imgBanana[0].height - 1;
	look[2].y =		look[3].y = look[1].y / 2;

	int startXPos = startX;
	int startYPos = startY - g_imgBanana[0].height;

	if (idPlayer == 1)
		startXPos = startXPos + g_imgGorD.width - g_imgBanana[0].width;

	int pointColor;
	int rot;
	double t = 0;
	while(!bImpact && bOnScreen)
	{
		// �������㽶
		if (bNeedErase)
		{
			bNeedErase = false;
			DrawBanana(int(oldx + 0.5), int(oldy + 0.5), -1, false);
		}

		x = startXPos + (initXVel * t) + (g_iWind / 5.0 * t * t);
		y = startYPos + (-1 * (initYVel * t) + (GRAVITY * t * t));
         
		if ((x >= SCRWIDTH - 10) || (x <= 3) || (y >= SCRHEIGHT - 3))
			bOnScreen = false;
  
		if (bOnScreen && y > 0)
		{
			// ����Ƿ����(���㽶�������������ĸ��ߵ��е������)
			for (int i = 0; i < 4; i ++)
			{
				pointColor = getpixel(int(x + look[i].x + 0.5), int(y + look[i].y + 0.5));
				if (pointColor == BACKATTR || pointColor == WHITE)		// Ŀ���Ǳ���ɫ���ɫ��Ļ��δ����
				{
					bImpact = false;
					if (bShotInSun == true && (abs(SCRWIDTH / 2 - int(x)) > 20 || y > SUNHEIGHT))
						bShotInSun = false;
				}
				else if (pointColor == SUNATTR && y < SUNHEIGHT)	// ����̫��
				{
					if (!g_bSunHit)
						DoSun(SUNSHOCK);

					g_bSunHit = true;
					bShotInSun = true;
				}
				else
					bImpact = true;

				if (bImpact)
					break;
			}
   
			if (!bShotInSun && !bImpact)
			{
				// �����㽶
				rot = int(t * 10) % 4;
				DrawBanana(int(x + 0.5), int(y + 0.5), rot, true);
				bNeedErase = true;
			}
            
			oldx = x;
			oldy = y;
		}
		t += 0.1;

		Sleep(50);
	}

	if (pointColor != OBJECTCOLOR && bImpact)
		DoExplosion(int(x + g_imgBanana[0].width / 2 + 0.5), int(y + g_imgBanana[0].height / 2 + 0.5));
	else if (pointColor == OBJECTCOLOR)
		iPlayerHit = ExplodeGorilla(int(x + 0.5), int(y + 0.5));

	return iPlayerHit;
}



// �����㽶
// ������
//		x, y���㽶��λ��
//		r���㽶����תλ��
//		d�����ƻ��ǲ���(true�����ƣ�false������)
void DrawBanana(int x, int y, int r, bool d)
{
	static IMAGE oldimg;

	if (d)
	{
		getimage(&oldimg, x, y, g_imgBanana[0].width, g_imgBanana[0].height);
		putimage(x, y, &g_imgBanana[r]);
	}
	else
		putimage(x, y, &oldimg);
}



// �㽶������ı�ըЧ��
// ������
//		x, y����ը��λ��
void DoExplosion(int x, int y)
{
	int r = 10;
	int i;

	setcolor(EXPLOSIONCOLOR);
	for (i = 0; i <= r; i++)
	{
		circle(x, y, i);
		Sleep(16);
	}
	
	setcolor(BACKATTR);
	for (i = r; i >= 0; i--)
	{
		circle(x, y, i);
		Sleep(16);
	}

	setfillcolor(BACKATTR);
	fillcircle(x, y, r);
}



// ��Ϸ��������ը
// ������
//		x, y��������λ��
int ExplodeGorilla (int x, int y)
{
	int iPlayerHit = (x < SCRWIDTH / 2) ? 0 : 1;
	int iPlayerX = g_ptGorilla[iPlayerHit].x + g_imgGorD.width / 2;
	int iPlayerY = g_ptGorilla[iPlayerHit].y + g_imgGorD.height / 2;
	int i;

	setcolor(EXPLOSIONCOLOR);

	for (i = 1; i <= 10; i++)
	{
		circle(x, y, i);
		Sleep(10);
	}

	for (i = 1; i <= 16; i++)
	{
		circle(iPlayerX, iPlayerY + 11, i);
		Sleep(10);
	}

	for (i = 1; i <= 32; i++)
	{
		setcolor((i % 2 == 0) ? 0x54A8FC : 0x5400FC);
		circle(iPlayerX, iPlayerY, i);
		Sleep(10);
	}

	for (i = 48; i >= 1; i--)
	{
		setcolor(BACKATTR);
		circle(iPlayerX, iPlayerY, i);
		Sleep(10);
	}

	fillcircle(iPlayerX, iPlayerY, 48);

	return iPlayerHit;
}



// ��������Ĵ�����(ʤ����ִ��)
// ������
//		idPlayer����Ϸ�߱��
void VictoryDance(int idPlayer)
{
	for (int i = 0; i < 4; i++)
	{
		putimage(g_ptGorilla[idPlayer].x, g_ptGorilla[idPlayer].y, &g_imgGorL);
		Sleep(200);
		putimage(g_ptGorilla[idPlayer].x, g_ptGorilla[idPlayer].y, &g_imgGorR);
		Sleep(200);
	}
}
