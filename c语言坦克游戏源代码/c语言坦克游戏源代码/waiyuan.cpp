# include "tanke.h"

/////////////////////////////////////////////////////�ⲿ
void JShengMing(int *j)
{
	setcolor(GREEN);
	settextstyle(0, 0, ("����"));
	char c2[20] = "�Լ�����ֵ��";
	outtextxy(0, 20, c2);
	
	char c3[10] ;
	sprintf(c3, _T("%.1f"), 100* (60 - *j) / 60.0);
	outtextxy(90, 20, c3);
}

void DShengMing(int * d,int *k)
{
	setcolor(GREEN);
	settextstyle(0, 0, ("����"));
	char c2[20] = "��������ֵ��";
	outtextxy(0, 0, c2);
	
	char c3[10] ;
	sprintf(c3, _T("%.1f"), 100* (60 - *d) / 60.0);
	outtextxy(90, 0, c3);

	char c4[40] = "��ϲ~! �������ҵ�2200�о�ϲ!";//ʤ��

	if ( *k >= 8000 )
			{
				setcolor(YELLOW);
				settextstyle(30, 0, ("����"));

				outtextxy(150, 0, c4);
			}
}

void Gold(int * gold)
{
	setcolor(GREEN);
	settextstyle(0, 0, ("����"));
	char c2[20] = "��ң�";
	outtextxy(0, 40, c2);
	
	char c3[10] ;
	sprintf(c3, _T("%d"), *gold);
	outtextxy(40, 40, c3);
}

void start(void)
{
	initgraph(200, 130);

	TCHAR s1[10]="̹�˴�ս";
	TCHAR s2[30]="��A ��ʼ��Ϸ  ��B �˳���Ϸ";
	TCHAR s3[30]="��W S A D���Ʒ���";
	TCHAR s4[20]="��J �����ӵ�";
	TCHAR s5[20]="��C ������";
	
	outtextxy(70, 0, s1);
	outtextxy(0,  110, s2);
	outtextxy(60, 90, s5);
	outtextxy(55, 30, s4);
	outtextxy(35, 60, s3);
	
	while (true)
	{
		Sleep(500);
		if (GetAsyncKeyState('A'))
		{
			BeginBatchDraw();
			closegraph();
			initgraph(640, 480);
			Sleep(200);
			Quit();
			return ;
		}	
		if (GetAsyncKeyState('C'))
		{
			Sleep(200);
			GongLue();
		}
	}
}
void GongLue(void)
{	
	initgraph(450, 300);
	TCHAR s1[20]="��Ϸ���ԣ�";
	TCHAR s2[50]="�ٴ�̹��֮ǰ�ȳԷ��ȴ����ɫש�飬";
	TCHAR s3[50]="������̹�˴��ɫ�Ͳ��ܻ�Ѫ�ˣ�boss��Ӧ��ˡ�";
	TCHAR s15[70]="�Զ��Ƶ����þ��ǿ�����ѹ����";
	TCHAR s4[50]="���̹�˵�ʱ�򣬱�������ӵ�������Կ�";
	TCHAR s5[70]="����ֱ��ѡ����ȥ��ѹ�� ע�⣺��Ѫ�㹻�ٵ�ʱ���߿���";
	TCHAR s6[50]="���ӵ������������ܵõ�Ǯ��";
	TCHAR s7[70]="Сboss���Է���ˢ����Ȼ������Ǯ���������������Ҫ��";
	TCHAR s14[70]="����ǹ��Ȼ�ٶȿ��˵��˺�����٣�������bossʱ�˺���������";
	TCHAR s8[70]="ѪҪ��ԣ��϶����㣬Ǯ���˺������������ˣ��������ˡ�";
	TCHAR s9[50]="���ռ�bossʱ���ǵ�Ҫ�ô��ӵ������˺����ܴ������";
	TCHAR s10[90]="�����ܰ��ʾ���п��ש�ȽϿ���~";
	TCHAR s11[40]="��󣺱������ܺ���ȥ���ռ�Boss��";
	TCHAR s12[30]="��Ϊ�㳬������ֱ�ӱ��롣";
	TCHAR s13[30]="��A ��ʼ��Ϸ";
	
	outtextxy(0, 0,  s1);
	outtextxy(0, 20, s2);
	outtextxy(0, 40, s3);
	outtextxy(0, 60, s15);
	outtextxy(0, 80, s4);
	outtextxy(0, 100, s5);
	outtextxy(0, 120, s6);
	outtextxy(0, 140, s14);
	outtextxy(0, 160, s7);
	outtextxy(0, 180, s8);
	outtextxy(0, 200, s9);
	outtextxy(0, 220, s10);
	outtextxy(0, 240, s11);
	outtextxy(0, 260, s12);
	outtextxy(0, 280, s13);
	
	while (true)
	{
		Sleep(500);
		if (GetAsyncKeyState('A'))
		{
			keybd_event(65,0,0,0);
			keybd_event(65,0,KEYEVENTF_KEYUP,0);
			return ;
		}	
	}
	
}

void MiJi(void)
{		
	closegraph();

	printf("��Ϸ�ؼ���\n");
	printf("��ϲ��ͨ���ˣ�\n");
	printf("������Щ��Ϸ���׷���~����\n");
	printf("����һֱ��ס�ӵ����ɵĻ� ������ֱ�ӿ��� �ӵ�����Ŷ~~\n\n");
	printf("���� ����С���ɡ���bossǰ �Ȱ�С̹�˶�ѹ��\n");
	printf("ֻ��һ������Ϊboss���� ���ؾ�Σ����\n");
	printf("���� �е��� ���û���600��Ĵ��ӵ�û�˺�û��\n");
	printf("��ֻ��˵�����÷����� ����һ��һ�µĵ㣬\n\n");
	printf("����һֱ����Ȼ���ɿ� ���˺��ߵ� ��~���ռ�boss����һ��Ѫ��\n\n");
	printf("���� ���� ����Gameover�� �����䣬�һ�����һ��\n\n");
	printf("������е�̹�˶�ɱ�� �ٰ� Y\n\n");
	printf("��ʱ����Ļ��ؾ͸����ˣ�\n\n");
	printf("~~��~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("���⣺С̹�˿�������ʱ��Y���͹ԹԻ�ȥ��\n\n");
	printf("��B ��Ϸ����\n\n");	
	
	while (true)
	{
		Sleep(500);
		if (GetAsyncKeyState('B'))
		{
			exit(0);
		}	
	}
	
}
void music(void)
{
	mciSendString("open sound\\̹�˴�ս.mp3 alias mymusic", NULL, 0, NULL);
	mciSendString("play mymusic", NULL, 0, NULL);
	return;
}
void start_(void)
{
	music();
	srand( (unsigned)time( NULL ) );//�������
	setcolor(GREEN);
	setfillcolor(RED);
}
void win(pHongZhuan phongzhuan,bool *live2, bool *live3, bool *live4, bool *live5,bool *live6,bool *live7,
		 bool *exist_laowang, bool *exist1, 
		 bool *wexist1,bool *wexist2,bool *wexist3,bool *wexist8)
{
	char c[10] = "YOU WIN";
	settextcolor(YELLOW);
	settextstyle(80, 0, ("����"));
	outtextxy(190, 100, c);
	char c1[20] = "��Y�� ������һ��";
	settextstyle(30, 0, ("����"));
	outtextxy(230, 200, c1);
	if (GetAsyncKeyState('Y'))
	{
		*live2 = true;
		*live3 = true;
		*live4 = true;
		*live5 = true;
		*live6 = true;
		*live7 = true;
		
		*exist_laowang =true;
		*exist1 = true;
	
		phongzhuan[0].exist = true;
		phongzhuan[1].exist = true;
		*wexist1 = true;
		*wexist2 = true;
		*wexist3 = true;
		*wexist8 = true;
	}
	return ;
}

void lost(bool * live1, int *relive, int *gold)
{
	char c[10] = "YOU LOST";
	settextcolor(YELLOW);
	settextstyle(80, 0, ("����"));
	outtextxy(170, 100, c);
	char c1[20] = "��I�� ����,���-60";
	settextstyle(30, 0, ("����"));
	outtextxy(200, 200, c1);
	
	char c2[20] = "ʣ�ิ�������";
	outtextxy(220, 230, c2);
	
	char c3[10] ;
	sprintf(c3, _T("%d"), 2 - *relive);
	outtextxy(426, 230, c3);
	
	if (GetAsyncKeyState('I'))
	{
		keybd_event(73,0,KEYEVENTF_KEYUP,0);
		
		(*relive)++;
		*gold -= 60;
		
		if (*relive < 3)
			*live1 = true;
	}
	if (*relive >= 3)
		GameOver();
	return ;
}

void GameOver(void)
{
	IMAGE img;
	loadimage(&img,_T("res\\gameover.bmp"));
	
	HDC	dstDC = GetImageHDC();  
	HDC	srcDC = GetImageHDC(&img);

	TransparentBlt(dstDC,200,50, 248, 160, srcDC, 0, 0, 248,  160, RGB(0,0,0));
}

bool Quit(void)
{
	if(GetAsyncKeyState('B'))
	{
		if(MessageBox(NULL, "��ȷ��Ҫ�˳���",
			"��ʾ", MB_YESNO) == IDYES)
			return true;
		
	}
	return false;
}
