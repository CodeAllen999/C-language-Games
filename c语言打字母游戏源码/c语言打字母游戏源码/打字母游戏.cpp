#include <graphics.h>
#include <conio.h>
#include <time.h>

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

// ��ӭ����
void welcome()
{
	// �����Ļ��ʾ
	cleardevice();
	setcolor(YELLOW);
	setfont(64, 0, "����");
	outtextxy(160, 50, "����ĸ��Ϸ");
	setcolor(WHITE);
	setfont(16, 0, "����");
	outtextxy(100, 200, "���Ǻܴ�ͳ���Ǹ�����ĸȻ����Ӧ������ʧ����Ϸ");
	outtextxy(100, 240, "ֻ������һ���򵥵�ʵ��");
	outtextxy(100, 280, "���ܲ��������ƣ������������������ȶ�û��д");
	outtextxy(100, 320, "����Ȥ���Լ��ӽ�ȥ��");
	
	// ʵ����˸�ġ��������������
	int c=255;
	while(!kbhit())
	{
		setcolor(RGB(c, 0, 0));
		outtextxy(280, 400, "�����������");
		c -= 8;
		if (c < 0) c = 255;
		Sleep(20);
	}
	getch();
	cleardevice();
}

// �˳�����
void goodbye()
{
	cleardevice();
	setcolor(YELLOW);
	setfont(48, 0, "����");
	outtextxy(104, 180, "��д����  �����ഺ");
	getch();
}

// ������
void main()
{
	initgraph(640, 480);		// ��ʼ����ĻΪ 640x480
	
	welcome();					// ��ʾ��ӭ����
	
	srand(time(NULL));			// �����������
	setfont(16, 0, "Arial");	// ������ĸ������ʹ�С
	setfillstyle(BLACK);		// ���������ĸ�����������ɫ
	
	char target;				// Ŀ����ĸ
	char key;					// �û��İ���
	int x, y;					// ��ĸ��λ��
	
	// ��ѭ��
	while(true)
	{
		target = 65 + rand() % 26;		// ���������д��ĸ
		x = rand() % 620;				// ������������λ��
		for (y=0; y<460; y++)
		{
			setcolor(WHITE);			// ������ĸ����ɫ
			outtextxy(x, y, target);	// ��ʾ��ĸ
			
			if(kbhit())
			{
				key = getch();			// ��ȡ�û�����
				
				if((key == target) || (key == target + 32))
				{
					// ������ȷ�������䡱��ĸ������ɫ���������
					bar(x, y, x + 16, y + 16);
					break;				// ����ѭ����������һ����ĸ
				}
				else if (key == 27)
				{
					goto EXIT;			// ����� ESC���˳���Ϸ��ѭ��
				}
			}
			
			// ��ʱ���������ĸ
			Sleep(10);
			bar(x, y, x + 16, y + 16);
		}
	}
	
EXIT:
	// �˳�����
	goodbye();
	
	// �ر�ͼ�ν���
	closegraph();
}