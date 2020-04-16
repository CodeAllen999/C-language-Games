#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#define MAX 64				// Բ�̵������Ŀ
#define NULL 0

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

// ����ջ
struct STKNODE
{
	int a[4];
};

struct STK 
{
	STKNODE*	stack[MAX];
	int			top;
};


// ����ȫ�ֱ���
STK s[3];					// ��������ջ���ֱ����һ�Ŷ������Ÿ�����Բ�̵�״̬
int v = 5;					// �����ٶ�
 


// ��������
void Initstk(STK* s);							// ��ʼ��ջ
void Hannoi(int n, char a, char b, char c);		// ��ŵ���ݹ�
void start();									// ��ʼ����
void Move(int n, char a, char b);				// �ƶ�����
int switchab(char a);							// ���ظ����
void adjust();									// �����ٶ���ͣ



// ������
void main()
{
	int n, ta[4] = {115, 500, 285, 520};			// ��һ��Բ�̵�λ��
	printf("����С��16\n");							// ��Ϊ����ʮ��ʱ�ͻ���ʾ���󣬵����������������
	printf("�����뺺ŵ���Ĳ�����1~64����");
	scanf("%d", &n);
	STKNODE** p;
	p = (STKNODE**)malloc(n * sizeof(STKNODE **));	// ����һ��Ԫ��Ϊ n ���Ķ�̬ STKNODE ��ָ������
	for (int i2 = 0; i2 < n; i2 ++)
	{
		p[i2] = (STKNODE *)malloc(sizeof(STKNODE));	// Ϊÿһ��ָ������ռ�
	} 
	Initstk(&s[0]);
	Initstk(&s[1]);
	Initstk(&s[2]);									// ������ջ��ʼ��
	start();										// ���ֿ�ʼ����
	setfillstyle(YELLOW);							// Բ�̵���ɫ
	for (int i=0; i < n; i++)
	{
		ta[0] += 5;
		ta[1] -= 20;
		ta[2] -= 5;
		ta[3] -= 20;
		bar(ta[0], ta[1], ta[2], ta[3]);			// ����n���Ӵ�Сһ�ε��ŵĻ�ɫԲ��
		++s[0].top;									// ��ջ
		for (int i1 = 0; i1 < 4; i1++)
		{
			p[i]->a[i1] = ta[i1];
			s[0].stack[s[0].top] = p[i];			// ��¼ÿ�����ε�λ�ã�topΪԲ�̵ĸ���
		}
	}	
	Hannoi(n, 'a', 'b', 'c');						// ��ŵ���ݹ麯��
	system("pause");
	printf("\t\t\t\tGame Over!\n");
}



///////////////////////////////////////////////////
// ��������

// ��ŵ���ĵݹ�
void Hannoi(int n, char a, char b, char c)  
{
	if(n == 1)
		Move(1, a, c);
	else
	{
		Hannoi(n-1, a, c, b);
		Move(n, a, c);
		Hannoi(n-1, b, a, c);
    }
}

// ջ�ĳ�ʼ��
void Initstk(STK *s) 
{  
	int i;
	s->top = 0;
	for (i = 0; i <= MAX; i++)
		s->stack[++s->top] = NULL;
	s->top = 0;
}

// �ƶ�����
void Move(int n, char a, char b)
{
	int i3, i4 = 0, i5 = 0;					
	i3 = b - a;												// Ŀ�ĸ�����Դ�����λ�ò�ֵ
	i4 = switchab(a);										// Դ��������
	i5 = switchab(b);										// Ŀ�ĸ����
	STKNODE *q1, *q0;										// �����м�������Դջ��Ŀ��ջ���ֵ�ô��ݣ�q1ΪĿ��ջ��q0ΪԴջ
	q1 = (STKNODE *)malloc(sizeof(STKNODE));
	q0 = (STKNODE *)malloc(sizeof(STKNODE));

	// Դջ��Ŀ��ջֵ�Ĵ���
	q0 = s[i4].stack[s[i4].top];
	++s[i5].top;											// ��ջ
	q1->a[0] = q0->a[0] + i3 * 200;
	q1->a[1] = 500 - s[i5].top * 20;
	q1->a[2] = q0->a[2] + i3 * 200;
	q1->a[3] = 500 - s[i5].top * 20 + 20;
	s[i5].stack[s[i5].top] = q1;
	--s[i4].top;											// ��ջ

	// �����˶�
	while (q0->a[1] >= 100)
	{
		setfillstyle(YELLOW);
		bar(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		adjust();											// ��������
		Sleep(10 * v);										// ��ͣ��ms��
		setfillstyle(WHITE);
		bar(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		setcolor(RED);
		line((q0->a[0] + q0->a[2]) / 2, q0->a[1], (q0->a[0] + q0->a[2]) / 2, q0->a[3]);	// ���»��ϱ�����ԭ�еĺ���
		q0->a[1] -= 10;
		q0->a[3] -= 10;
		if (s[i4].top == 0)									// ���»������һ�����ο�����ĵ����ϵ���������
		{
			line(110 + i4 * 200, 500, 290 + i4 * 200, 500);
			line(110 + i4 * 200, 493, 290 + i4 * 200, 493);
		}
	}

	// ��������˶����� i3 �������й�
	while (q0->a[2] != q1->a[2])
	{
		setfillstyle(YELLOW);
		bar(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		adjust();
		Sleep(10 * v);
		setfillstyle(WHITE);
		bar(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		if (i3 < 0)											// i3<0������
		{
			q0->a[0] -= 20;
			q0->a[2] -= 20;
		} 
		else												// i3>0������
		{
			q0->a[0] += 20;
			q0->a[2] += 20;
		}
	}

	// �����˶�
	while (q0->a[3] <= q1->a[3])
	{
		setfillstyle(YELLOW);
		bar(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		adjust();
		Sleep(10 * v);
		setfillstyle(WHITE);
		bar(q0->a[0], q0->a[1], q0->a[2], q0->a[3]);
		setcolor(RED);
		if (q0->a[1] > 100)									// �ػ��������ĺ���
		{
			setcolor(RED);
			line((q0->a[0] + q0->a[2]) / 2, q0->a[1], (q0->a[0] + q0->a[2]) / 2, q0->a[3]);
		}
		q0->a[1] += 10;
		q0->a[3] += 10;
	}

	// ��Ŀ�ĸ����ϵ���Ӧλ�û��Ƴ���ɫ���ο�
	setfillstyle(YELLOW);
	bar(q1->a[0], q1->a[1], q1->a[2], q1->a[3]);
}

// ���ƿ�ʼ����
void start()
{

	// ��ʼ�������С
	initgraph(800, 650);

	// ������Ϊ��ɫ
	setbkcolor(WHITE);

	// �ð�ɫ�����������
	cleardevice();
	
	// ���Ʋʺ磬�γ�һ���ʺ磬ժ�� easyx �����ĵ�ʾ������
	float H, S, L; 
	H = 0;			// ɫ��
	S = 1;			// ���Ͷ�
	L = 0.5f;		// ����
	setlinestyle(PS_SOLID, NULL, 2);								// �����߿�Ϊ 2
	for(int r = 600; r > 544; r--)
	{
		H += 5;
		setcolor( HSLtoRGB(H, S, L) );
		circle(750, 900, r);
	}

	// ˵��
	setfont(50, 0, "���Ŀ���");
	setcolor(RED);
	outtextxy(200, 150, "��ŵ���ƶ�����");
	setfont(20, 0, "����");
	outtextxy(600, 200, "BY:Ronald");
	outtextxy(500, 200, "�汾V1.1");
	setfont(50, 0, "����");
	setcolor(GREEN);
	outtextxy(200, 350, "��㰴һ������ʼ�ɣ�");

	// �����˶��ľ���
	while (1)
	{

		// ����Ƿ��м����û�
		if (kbhit())
		{
			break; 
		}

		// ����
		int a = 40, b = 40;									//��ʼλ��
		while (a <= 760)
		{
			setfillstyle(YELLOW);
			bar(a, b, a + 10, b + 20);
			Sleep(10);
			setfillstyle(WHITE + a);
			bar(a, b, a + 10, b + 20);
			a += 10;
		}

		if (kbhit())
		{
			break;
		}

		// ����
		while (b<=610)
		{
			setfillstyle(RED);
			bar(a, b, a + 10, b + 20);
			Sleep(10);
			setfillstyle(WHITE - b);
			bar(a, b, a + 10, b + 20);
			b += 10;
		}
		
		if (kbhit())
		{
			break;
		}

		// ����
		while (a >= 40)
		{
			setfillstyle(GREEN);
			bar(a, b, a + 10, b + 20);
			Sleep(10);
			setfillstyle(WHITE - a);
			bar(a, b, a + 10, b + 20);
			a -= 10;
		}

		if (kbhit())
		{
			break;
		}

		// ����
		while (b >= 40)
		{
			setfillstyle(BLUE);
			bar(a, b, a + 10, b + 20);
			Sleep(10);
			setfillstyle(WHITE + b);
			bar(a, b, a + 10, b + 20);
			b -= 10;
		}
	}

	// ��տ�ʼ����
	cleardevice();

	// �����˶�����ĵĻ���
	setcolor(RED);

	// ������ɫ�߶���Ϊ����
	line(400, 110, 400, 500);
	line(600, 110, 600, 500);
	line(200, 110, 200, 500);

	// �������εĵ���
	setfillstyle(LIGHTGRAY);
	bar3d(80, 500, 720, 510, 10, true); 
	
	// ��ͣ��ť
	bar(360, 540, 440, 580);
	setfont(30, 0, "����");
	setcolor(GREEN);
	outtextxy(370, 550, "��ͣ");                              
	setfont(20, 0, "����");
	setcolor(RED);
	outtextxy(300, 580, "�����ͣ���밴�ո����");

	// ���ٰ�ť
	bar(160, 540, 240, 580);
	setfont(30, 0, "����");
	setcolor(GREEN);
	outtextxy(170, 550, "����");
	setfont(20, 0, "����");
	setcolor(RED);
	outtextxy(170, 580, "�밴 d");

	// ���ٰ�ť
	bar(560, 540, 640, 580);
	setfont(30, 0, "����");
	setcolor(GREEN);
	outtextxy(570, 550, "����");
	setfont(20, 0, "����");
	setcolor(RED);
	outtextxy(570, 580, "�밴 a");

	// ˵��
	setfont(50, 0, "����");
	setcolor(GREEN);
	outtextxy(10, 10, "���ڽ����������ͣ�");
}

// �ж�Ŀ�ĸ�����Դ����ĸ���ŷ��ظ����
int switchab(char a)
{
	switch (a)
	{
		case 'a':
			return 0;
		case 'b':
			return 1;
		case 'c':
			return 2;
		default:
			return 0;
	}
}

// ����������ʵ�ּ��٣����٣���ͣ
void adjust()
{
	char f;												// ���ռ����ý�ȥ�İ�ť�������ʱ����ı仯ֵ

	// �� f ���ܼ��̵ļ���ֵ
	if(kbhit())
		f = getch();

	// ��������Ϣ
	if (MouseHit()==true)									
	{

		// ���������Ϣ
		MOUSEMSG Mouse;
		Mouse = GetMouseMsg();

		// ��Ӧ�����Ϣ
		if (Mouse.x >= 360 && Mouse.x <= 440 && Mouse.y >= 540 && Mouse.y <= 580 && Mouse.mkLButton)
		{
			f = ' ';
		}
		if (Mouse.x >= 160 && Mouse.x <= 240 && Mouse.y >= 540 && Mouse.y <= 580 && Mouse.mkLButton)
		{
			f = 'd';
		}
		if (Mouse.x >= 560 && Mouse.x <= 640 && Mouse.y >= 540 && Mouse.y <= 580 && Mouse.mkLButton)
		{
			f = 'a';
		}
	}

	// �����ڶ���
	switch(f)
	{
		
		// ��ͣ
		case ' ':
		
			// �á����������ǡ���ͣ��  
			setfont(30, 0, "����");
			setcolor(GREEN);
			outtextxy(370, 550, "����");  
			getch();
		
			// ����������ʾ����ͣ��
			setfont(30, 0, "����");
			setcolor(GREEN);
			outtextxy(370, 550, "��ͣ");  
			break;
		
		// ����
		case 'a':
		
			// �������ʱ�������١�λ����һ��
			setfillstyle(LIGHTGRAY);
			bar(560, 540, 640, 580);
			setfont(30, 0, "����");
			setcolor(GREEN);
			outtextxy(575, 545, "����"); 
			Sleep(30);
		
			// ����
			v++; 
		
			// ��ԭλ
			setfillstyle(LIGHTGRAY);
			bar(560, 540, 640, 580);
			setfont(30, 0, "����");
			setcolor(GREEN);
			outtextxy(570, 550, "����");
			break;
		
		// ����
		case 'd':
			setfillstyle(LIGHTGRAY);
			bar(160, 540, 240, 580);
			setfont(30, 0, "����");
			setcolor(GREEN);
			outtextxy(165, 545, "����");
			Sleep(30);
			setfillstyle(LIGHTGRAY);
			bar(160, 540, 240, 580);
			setfont(30, 0, "����");
			setcolor(GREEN);
			outtextxy(170, 550, "����");

			// ����
			v--;
		
			// v ��СΪ1
			if (v <= 0)              
			{
				v = 1;
			}
			break;
		
		default:
			break;
	} 
	
	f = 'r';									// f ��ʼ��Ϊ r
	FlushMouseMsgBuffer();						// ��������Ϣ
}