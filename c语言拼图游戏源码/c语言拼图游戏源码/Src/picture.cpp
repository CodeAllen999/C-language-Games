/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

// ����ͷ�ļ�
#include "../Inc/picture.h"


// ��Ϸ������Ĭ�Ϲ��캯��
GameFrame::GameFrame()
{
    initgraph (xLength, yLength);
    setbkcolor (BgColor);
    cleardevice ();
}

// ���Ʊ���ͼ��
void GameFrame::DrawBackground()
{
	float H, S, L;														// ���� HSL ��ɫģ�͵� 3 ������

	H = 70;
	S = -2.2555f;														// ���Ͷ�
	L = 0.525617f;			
	BeginBatchDraw();
	for(int i = 0; i != yLength; ++i)									// ������Ϸ������ɫ
	{
		L += 0.000000085f;
		S -= 0.0013f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, i, xLength, i);
	}
	EndBatchDraw();
}

// ��ʼ�˵�
void GameFrame::StartMenu()
{
	setbkmode(TRANSPARENT);												// ���ñ���Ϊ͸��
    settextcolor(BLUE);													// ����������ɫΪ��ɫ

	settextstyle(23, 0, _T("�����п�"));								// ����������Ϣ
	outtextxy(700, 25, _T("��Ϸ����: Redman"));							// ������Ϸ���ߵ�����

    settextstyle(30, 0, _T("�����п�"));								// ��������Ĵ�С
    outtextxy(230, 85, _T("��ӭ����ƴͼ��Ϸ������"));                   // ������ʾ��Ϣ
	settextstyle(23, 0, _T("�����п�"));								// ����������Ϣ
	outtextxy(300, 170, _T("ѡ����Ϸ���Ѷ�:"));							// ������ʾ��Ϣ
	outtextxy(300, 210, _T("<A> һ��"));
	outtextxy(300, 270, _T("<B> �е�"));
	outtextxy(300, 330, _T("<C> ����"));

	setlinestyle(PS_SOLID, 5, NULL);
    setlinecolor(BLUE);													// ����������ɫΪ��ɫ
	rectangle(200,50,600,400);
	line(200, 150, 600, 150);
}

// ���ƺ���
void Picture::Run()
{
	switch (Control)
	{
		case 0:
		{
			SetGameDifficult();											// ������Ϸ�Ѷ�
			break;
		}
		case 1:
		{
			SetPicture();												// ����ͼ��
			DrawRect();													// ���ƾ���
			break;
		}
		case 2:
		{
			PrintPicture();												// ��ͼ���������Ļ��
			break;
		}
		case 3:
		{
			ProcessMouse();												// ���������Ϣ
			IsPass();													// �Ƿ�ͨ��
			break;
		}
		default:
		{
		   break;
		}
	}
}

// ������Ϸ���Ѷ�
void Picture::SetGameDifficult()
{
    char num;                                                           // ��ȡ���̵ļ�ֵ

    while (1)
    {
        if (kbhit())
        {
			mciSendString("play  Res\\key.wav", NULL, 0, NULL);
            num = getch();                                              // �Ӽ��̻�ȡ��Ϣ
            
            switch (num)
            {
				case 'a':Diffcult = 3;break;
                case 'b':Diffcult = 4;break;
                case 'c':Diffcult = 5;break;
                default:Diffcult = 0;
            }
        }

		// �����Ϸ�Ѷ��ѻ�ȡ���˳�ѭ��
        if (Diffcult != 0)
        {
            Control = 1;
            break;
        }
    }
}

// ����ͼƬ
void Picture::SetPicture()
{
    loadimage(&img, String.c_str(), Width, Height);						// ����ͼ��

	singleWidth = Width / Diffcult;										// �����и�ͼ��ĳ���
	singleHeight = Height / Diffcult;

    image = new Image *[Diffcult];                                      // ����ռ�
	Query = new int *[Diffcult];										// ����ѯ�������ռ�

    SetWorkingImage(&img);                                              // ���û�ͼ�豸

	// �и�ͼ��, ������λ��
	for (int i = 0; i < Diffcult; ++i)
	{
		image[i] = new Image[Diffcult];
		Query[i] = new int [Diffcult];
        for (int j = 0; j < Diffcult; ++j)
		{
			image[i][j].x = j;
			image[i][j].y = i;
			Query[i][j] = i * Diffcult + j;
			if (i != Diffcult - 1 || j != Diffcult - 1)
			{ 
				getimage(&(image[i][j].image), j * singleWidth,\
				i * singleHeight, singleWidth - 3, singleHeight - 3);
			} 
		}
	}

    SetWorkingImage();                                                  // �ָ�Ĭ�ϻ�ͼ�豸

	
	// ����ȷ�Ľ����������ɢͼƬ, �����ܱ�֤��������н�
	SetLocal();

    // �����и��СͼƬ������һ�Ž��д���
	image[Diffcult - 1][Diffcult - 1].image.Resize(singleWidth - 3, singleHeight - 3);
	SetWorkingImage(&(image[Diffcult - 1][Diffcult -1].image));         // ���û�ͼ�豸
	float H, S, L;														// ���� HSL ��ɫģ�͵� 3 ������
	H = 50;																// ɫ��
	S = -3.2555f;														// ���Ͷ�
	L = 0.525617f;				
	for(i = 0; i != singleHeight; ++i)									// ���������Ƶ�ͼ����ȥ
	{
		L += 0.000000085f;
		S -= 0.0015f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, i, singleWidth, i);
	}
	SetWorkingImage();
	Control = 2;
}

// ��ͼ���������Ļ
void Picture::PrintPicture()
{
	// ���и���ͼ����ص���Ļ��ȥ
    for (int i = 0; i < Diffcult; ++i)
	{
        for (int j = 0; j < Diffcult; ++j)
		{
			putimage(image[i][j].x * singleWidth + 3,\
			image[i][j].y * singleHeight + 3, &(image[i][j].image));
		}
	}
	Resize(&img, 300, 225);
	loadimage(&img, String.c_str(), 300, 225);                          // ��������ͼ��
	setbkmode(TRANSPARENT);
	settextstyle(23, 0, _T("�����п�"));								// ����������Ϣ
	settextcolor(BLUE);
	outtextxy(700, 25, _T("��Ϸ����: Redman"));							// ������Ϸ���ߵ�����
	outtextxy(740, 70, _T("����ͼ��"));
	putimage(630, 100, &img);
	Control = 3;
}

// ��������
void Picture::DrawRect()
{
	setlinecolor(BgColor);												// ���ñ߿���ɫ
	setfillcolor(BgColor);												// ���������ɫ
	POINT points[] = {{0, 0}, {0, 453}, {600, 453}, {600,0}};
	fillpolygon(points, 4);
	Control = 2;
}

// ���������Ϣ
void Picture::ProcessMouse()
{
	int ImageX = image[Diffcult - 1][Diffcult - 1].x;
	int ImageY = image[Diffcult - 1][Diffcult - 1].y;

	// �����갴��
	while (MouseHit())
	{
		MouseMessage = GetMouseMsg();									// ��ȡ�����Ϣ

		switch (MouseMessage.uMsg)
		{
			case WM_LBUTTONDOWN:										// ����������
			{
				mciSendString("play  Res\\key.wav", NULL, 0, NULL);		// ��������
				LocalX = MouseMessage.x / singleWidth;					// ��ȡ�������ڵ�ͼ�������
				LocalY = MouseMessage.y / singleHeight;
				break;
			}
			default:
			{
				break;
			}
		}

		// �ڿ�ͼ�����ܲŻᴦ��������Ϣ
		if (LocalX == ImageX)
		{
			if (LocalY == ImageY - 1 || LocalY == ImageY + 1)
			{
				ProcessPicture();
			}
		} 
		else if (LocalY == ImageY)
		{
			if (LocalX == ImageX - 1 || LocalX == ImageX + 1)
			{
				ProcessPicture();
			}
		}
	}
}

void Picture::ProcessPicture()
{
	int num = 0;
	int Diff = Diffcult -1;
	int x1, y1;

	num = Query[LocalY][LocalX];										// ��λ��괦���ڵ�ͼƬ
	y1 = num / Diffcult;
	x1 = num % Diffcult;
	
	// �޸Ĳ�ѯ�����ֵ
	Query[image[Diff][Diff].y][image[Diff][Diff].x] = num;
	Query[LocalY][LocalX] = Diffcult * Diffcult - 1;

	// ����ͼƬ��λ��
	image[y1][x1].x = image[Diff][Diff].x;
	image[y1][x1].y = image[Diff][Diff].y;
	image[Diff][Diff].x = LocalX;
	image[Diff][Diff].y = LocalY;
	
	// ����ͼƬ
	putimage(image[y1][x1].x * singleWidth + 3, image[y1][x1].y * singleHeight + 3, &(image[y1][x1].image));
	putimage(LocalX * singleWidth + 3, LocalY * singleHeight + 3,&(image[Diff][Diff].image));
}

// �ж��Ƿ�ͨ��
void Picture::IsPass()
{
	int flag = 0;
	char str[20];
	setbkmode(OPAQUE);
	sprintf(str, "�� %d / %d ��", Pass + 1, PassCount);
	settextstyle(23, 0, _T("�����п�"));								// ����������Ϣ
	outtextxy(700, 350, _T("��ǰ״̬: ��Ϸ��"));						// �����Ϸ״̬
	outtextxy(730, 400, str);											// �����ǰ�Ĺ���

	for (int i = 0; i < Diffcult; ++i)
	{
		for (int j = 0; j < Diffcult; ++j)
		{
			if (image[i][j].x == j && image[i][j].y == i)
			{
				++flag;
			}
		}
	}

	// ͨ������
	if (flag == Diffcult * Diffcult)
	{
		Resize(&img, Width, Height);
		loadimage(&img, String.c_str(), Width, Height);					// ����ͼ��
		putimage(0, 0, &img);
		outtextxy(700, 350, _T("��ǰ״̬: ��ͨ��"));					// �����Ϸ״̬
		++Pass;															// ������һ
		String[4] = char((Pass / 10) + 48);								// �޸�
		String[5] = char((Pass % 10) + 48);
		Control = 1;
		mciSendString("play  Res\\ʤ��.mp3", NULL, 0, NULL);
		Sleep(3000);													// ��ʱ 3 ����
	}

	if (Pass == PassCount)
	{
		cleardevice();
		settextstyle(50, 0, _T("�����п�"));								// ����������Ϣ
		outtextxy(220, 250, _T("��ϲ��, ��ͨ��ȫ���ؿ�"));				// �����Ϸ״̬
		Control = 4;													// �ı����ֵ
	}
}

// ����ͼƬλ��
void Picture::SetLocal()
{
	// ��¼�ĸ������ֵ
	int sentryX[4] = {-1, 0, 1, 0};
	int sentryY[4] = {0, -1, 0, 1};

	int index = -1;
	int num = 0;
	int Diff = Diffcult -1;
	int Len = Diff;
	int x1, y1;
	int k = 0;
	loop:
	for (int l = 0; l < 8; ++l)
	{
		++index;
		index = index % 4;
		for (k = Len; k > 0; k--)
		{
			// ��¼ LocalX �� LocalY ��λ��
			LocalX = image[Diff][Diff].x + sentryX[index];
			LocalY = image[Diff][Diff].y + sentryY[index];

			// ��λͼƬλ��
			num = Query[LocalY][LocalX];

			// ��¼ y1, x1 ��λ��
			y1 = num / Diffcult;
			x1 = num % Diffcult;

			// �޸Ĳ�ѯ�����ֵ
			Query[LocalY][LocalX] = Diffcult * Diffcult - 1;
			Query[image[Diff][Diff].y][image[Diff][Diff].x] = num;

			// ����ͼƬλ��
			image[y1][x1].x = image[Diff][Diff].x;
			image[y1][x1].y = image[Diff][Diff].y;
			image[Diff][Diff].x = LocalX;
			image[Diff][Diff].y = LocalY;
		}
	}
	Len--;
	if (Len > 0)
	{
		goto loop;
	}

	// ��������Ĵ���֮��, ͼƬӦ�ñ���ɢ��, Ȼ���ٽ���������̴���
	srand(time(NULL));
	for (k = 0; k < 100; k++)
	{
		loop1:
		index = rand() % 4;
		// ��¼ LocalX �� LocalY ��λ��
		LocalX = image[Diff][Diff].x + sentryX[index];
		LocalY = image[Diff][Diff].y + sentryY[index];
		if (LocalX >= 0 && LocalX <= Diff && LocalY >= 0 && LocalY <= Diff)
		{
			// ��λͼƬλ��
			num = Query[LocalY][LocalX];
			
			// ��¼ y1, x1 ��λ��
			y1 = num / Diffcult;
			x1 = num % Diffcult;
			
			// �޸Ĳ�ѯ�����ֵ
			Query[LocalY][LocalX] = Diffcult * Diffcult - 1;
			Query[image[Diff][Diff].y][image[Diff][Diff].x] = num;
			
			// ����ͼƬλ��
			image[y1][x1].x = image[Diff][Diff].x;
			image[y1][x1].y = image[Diff][Diff].y;
			image[Diff][Diff].x = LocalX;
			image[Diff][Diff].y = LocalY;
		}
		else
		{
			goto loop1;
		}
	}
}

