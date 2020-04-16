#include <iostream>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include <time.h>

using namespace std;

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

/******ȫ�ֱ���******/
#define STEPDISTANCE	6		// һ���ľ��롣��ֵԽ���ƶ��ٶ�Խ��
#define JUMPSPEED		10		// ��ֵԽС������ԽԶ
#define ROLLDISTANCE	30		// �������ܲ�������ֵԽ�󣬹���ԽԶ

/******ȫ�ֱ���******/
int s_v		= STEPDISTANCE;		//�ϰ���������ƶ��ٶ�
int p_v		= JUMPSPEED;		//������Ծ�ٶ�
int score	= 0;				//����
int	max_s	= 0;
char keydown;					//����ֵ

/********************/
void move();
void Login();

/*************************************�ϰ�����****************************************/
// �ϰ���
class zhangai
{
public:
	int left;
	int top;
	int right;
	int bottom;
	int r;
public:
	void draw(int l, int t, int r, int b);	// �����ϰ���
	void style();							// �ϰ�������
	
} s1, s2, s3;

// �ϰ�������
void zhangai::style()
{
	int a;
	srand((unsigned int) time(NULL));
	a = rand() % 5 + 1;
	switch(a)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			top = 330;
			bottom = 361;
			break;
		case 5:
			top = 260;
			bottom = 291;
			break;
	}
}

//�ϰ����ʼ��
void zhangai::draw(int l,int t,int ri,int b)
{
	left=l;
	top=t;
	right=ri;
	bottom=b;
	solidrectangle(l, t, ri, b);
}

/**************************************������***********************************/
class people
{
public:
	int i;					// ���������ƶ�֡��
	int b;					// �����������֡��
	int b1;					// �����������ʱ��
	int j;					// ������Ծ�������ٶ�
	int k;					// �����½����ٶ�
	int left;
	int top;
	int right;
	int bottom;

private:
	IMAGE img1[8];			// ����ͼ��
	IMAGE img2[8];			// ����ͼ��
	IMAGE img3;				// ��Ծͼ��

public:
	people();				// ���캯��
	void jump();			// ������Ծ
	void move();			// �����ƶ�
	void roll();			// �������
	bool impact(zhangai *ps);			// ��ײ
} p;

// ���캯��
people::people()
{
	// �����ܶ�ͼ��
	loadimage(&img1[0], _T("rc\\picture\\move8_1.jpg"), 70, 100);
	loadimage(&img1[1], _T("rc\\picture\\move8_2.jpg"), 70, 100);
	loadimage(&img1[2], _T("rc\\picture\\move8_3.jpg"), 70, 100);
	loadimage(&img1[3], _T("rc\\picture\\move8_4.jpg"), 70, 100);
	loadimage(&img1[4], _T("rc\\picture\\move8_5.jpg"), 70, 100);
	loadimage(&img1[5], _T("rc\\picture\\move8_6.jpg"), 70, 100);
	loadimage(&img1[6], _T("rc\\picture\\move8_7.jpg"), 70, 100);
	loadimage(&img1[7], _T("rc\\picture\\move8_8.jpg"), 70, 100);

	// ���ع���ͼ��
	loadimage(&img2[0], _T("rc\\picture\\gun8_1.jpg"), 50, 50);
	loadimage(&img2[1], _T("rc\\picture\\gun8_2.jpg"), 50, 50);
	loadimage(&img2[2], _T("rc\\picture\\gun8_3.jpg"), 50, 50);
	loadimage(&img2[3], _T("rc\\picture\\gun8_4.jpg"), 50, 50);
	loadimage(&img2[4], _T("rc\\picture\\gun8_5.jpg"), 50, 50);
	loadimage(&img2[5], _T("rc\\picture\\gun8_6.jpg"), 50, 50);
	loadimage(&img2[6], _T("rc\\picture\\gun8_7.jpg"), 50, 50);
	loadimage(&img2[7], _T("rc\\picture\\gun8_8.jpg"), 50, 50);

	// ������Ծͼ��
	loadimage(&img3, _T("rc\\picture\\move8_5.jpg"), 70, 100);
}

//������Ծ
void people::jump()
{
	if(j >= 70)			//����
	{
		putimage(left,j, &img3);
		clearrectangle(40,j+100,120,j+120);
		p.top = j;
		p.bottom = p.top  + 120;
		j=j-p_v;
		k=j;
	}
	else if(k <= 240)		//�½�
	{
		putimage(left,k+20, &img3);
		clearrectangle(40,70,120,k+20);
		p.top = k;
		p.bottom = p.top  + 120;
		k=k+p_v;
	}
}

//�����ƶ�
void people::move()
{
	putimage(50, 260, &img1[p.i]);
	p.left	= 50;
	p.top	= 240;
	p.right	= p.left + 65;
	p.bottom= p.top  + 120;
	p.i++;				// �ı�����֡��
	if(p.i == 8)		// ����ѭ���ƶ�
	{
		p.i = 0;
	}
}

//�������
void people::roll()
{
	putimage(50, 300, &img2[p.b]);
	p.left=50;
	p.top =300;
	p.right = p.left + 50;
	p.bottom = p.top + 50;
	p.b1++;
	p.b++;				// �ı��������֡��
	if(p.b==8)			// ����ѭ������
	{
		p.b=0;
	}
}

// �����Ƿ���ָ���ϰ�������ײ
bool people::impact(zhangai *ps)
{
	return (max(left, ps->left) < min(right, ps->right) && max(top, ps->top) < min(bottom, ps->bottom));
}

/*************************����********************************/
// ����ϰ�
void zhangai_rnd()
{
	s1.r=rand() % 200 + 200;
	s2.r=rand() % 200 + 200;
	s3.r=rand() % 200 + 200;
}

// ��ʼ���ϰ�
void chushi()
{
	s1.left = 640;
	s2.left = s1.left + s1.r;
	s3.left = s2.left + s2.r;
	s1.style();
	s2.style();
	s3.style();
}

// �����ϰ�
void show_zhangai()
{
	s1.draw(s1.left, s1.top, s1.left + 40, s1.bottom);
	s2.draw(s2.left, s2.top, s2.left + 40, s2.bottom);
	s3.draw(s3.left, s3.top, s3.left + 40, s3.bottom);
}

// ɾ���ϰ�
void delete_zhangai()
{
	clearrectangle(s1.left, s1.top, s1.left+40, s1.bottom);
	clearrectangle(s2.left, s2.top, s2.left+40, s2.bottom);
	clearrectangle(s3.left, s3.top, s3.left+40, s3.bottom);
}

// �ϰ���ѭ��
void xunhuan()
{
	if(s1.left+40<=0)
	{
		s3.r = rand() % 200 + 200;
		s1.left = s3.left + s3.r;
		s1.style();
	}
	else if(s2.left+40<=0)
	{
		s1.r = rand() % 200 + 200;
		s2.left = s1.left + s1.r;
		s2.style();
	}
	else if(s3.left + 40 <= 0)
	{
		s2.r = rand() % 200 + 200;
		s3.left = s2.left + s2.r;
		s3.style();
	}
}

// �����ϰ��ƶ��ٶ�
void set_speed()
{
	s1.left -= s_v;
	s2.left -= s_v;
	s3.left -= s_v;
}

// ������Ϸ��ʼ��
void game_again()
{
	score = 0;
	s_v = STEPDISTANCE;
	p_v = JUMPSPEED;
	cleardevice();
	solidrectangle(0, 360, 640, 400);
	move();
}

// ����ɼ�
void gave_score()
{
	ofstream outfile("score.txt", ios::out);
	if(!outfile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	outfile << score << " ";
	outfile.close();
}

// ��ȡ��߷�
void max_score()
{
	int value;
	ifstream infile("score.txt", ios::in);
	
	if(!infile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	infile>>value;
	infile.close();
	max_s = value;
}

// �ı���߷�
void change_score()
{
	int value;
	ifstream infile("score.txt", ios::in);
	
	if(!infile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	infile>>value;
	infile.close();
	if(score>value)
	{
		gave_score();
	}
}

// ��Ϸ����
void game_over()
{
	FlushMouseMsgBuffer();		//�����껺����
	change_score();
	Sleep(1000);
	p.i = 0;
	cleardevice();

	Login();
}

// ��ײ
void pengzhuang()
{
	// ָ��ǰ�ϰ���ָ��
	zhangai *ps;

	// ��ȡ��ǰ�ϰ�
	ps = &s1;
	if (s2.left < ps->left)	ps = &s2;
	if (s3.left < ps->left)	ps = &s3;

	// �����ײ
	if (p.impact(ps))
	{
		p_v = 0;
		s_v = 0;
		game_over();
	}
}

/******************************************************************************************/
// �ƶ�
void move()
{
	keydown=' ';				// ��ռ��̻�����
	setfillstyle(BS_SOLID);		// ���û�ͼ��ʽ
	cleardevice();	
	solidrectangle(0, 360, 640, 400);
	char s[10];
	char max[10];
	char ss[] = "����:0";
	char sss[] = "��߷�:";
	max_score();				// ��߷�
	settextcolor(BLUE);
	sprintf(max, "%d", max_s);	// ��ֵ��ʽ��
	outtextxy(490, 40, max);		// �����߷�
	outtextxy(58, 40, ss);
	outtextxy(400, 40, sss);
	p.i  = 0;
	p.b  = 0;
	p.b1 = 0;
	p.j  = p.k = p.top = 240;
	p.left = 50;
	zhangai_rnd();
	chushi();
	IMAGE img1;
	loadimage(&img1, _T("rc\\picture\\move8_1.jpg"),70,100);
	putimage(50,260, &img1);
	while(true)
	{
		keydown=getch();
		
		while(!kbhit())
		{
			sprintf(s,"%d",score);
			
			outtextxy(120,40,s);
			
			show_zhangai();
			
			if(keydown == 'w')
			{
				p.i = 0;
				p.b1 = 0;
				p.jump();
				if(p.k > 240)
				{
					keydown = ' ';
					p.j = 240;
				}
			}
			else if(keydown == 's')
			{
				if(p.b1 == 0)
					clearrectangle(50, 240, 120, 361);

				if(p.k >= 240)
					p.roll();
				else
					keydown='w';
			}
			else
			{
				if(p.k >= 240)
					p.move();
				else
					keydown = 'w';

				if(p.b1 == 0)
					p.move();
				else
					keydown = 's';
			}
			
			if(p.b1 >= ROLLDISTANCE)
			{
				p.b1 = 0;
				keydown = ' ';
				p.b = 0;
			}
			
			Sleep(20);
			
			pengzhuang();
			
			delete_zhangai();
			
			set_speed();
			
			score++;		// ����
			
			xunhuan();		// �ϰ���ѭ���ƶ� 
		}
	}
}

// ��¼����
void Login()
{
	setfillstyle(BS_SOLID);
	setbkcolor(LIGHTBLUE);
	char s[]	= "��ʼ��Ϸ";
	char ss[]	= "�˳���Ϸ";
	char sss[]	= "��Ϸ˵��: W �� = ��Ծ   S �� = ����";
	
	MOUSEMSG m;
	solidrectangle(240, 100, 380, 150);
	solidrectangle(240, 160, 380, 210);
	settextcolor(BLUE);					// ����������ɫ
	
	outtextxy(260, 113, s);
	outtextxy(260, 173, ss);
	
	setbkcolor(WHITE);
	outtextxy(110, 250, sss);
	
	setfillcolor(LIGHTBLUE);
	
	solidrectangle(0, 360, 640, 400);
	
	while(true)
	{
		m = GetMouseMsg();				// �ж��Ƿ������
		if(m.x >= 240 && m.x <= 380 && m.y >= 100 && m.y <= 150)
		{
			setlinecolor(RED);			// ѡ�п��������ɫ
			rectangle(235, 95, 385, 155);
			if(m.uMsg==WM_LBUTTONDOWN )
			{
				clearrectangle(240, 100, 380, 150);
				clearrectangle(240, 160, 380, 210);
				setbkcolor(WHITE);
				cleardevice();
				game_again();
			}
		}
		else if(m.x >= 240 && m.x <= 380 && m.y >= 160 && m.y <= 210)
		{
			setlinecolor(RED);			// ѡ�п��������ɫ
			rectangle(235, 155, 385, 215);
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				exit(1);
			}
		}
		else
		{
			setlinecolor(WHITE);
			rectangle(235, 95,  385, 155);
			rectangle(235, 155, 385, 215);
		}
	}
}

/***********************************************************************/
// �����ʼ��
void UI()
{
	initgraph(640, 400);				// ���ڳ�ʼ����С
	setbkcolor(WHITE);					// ���ñ�����ɫ
	cleardevice();
	setlinecolor(BLACK);				// ���û�ͼ��ɫ
	settextcolor(BLACK);				// ����������ɫ
	setfillcolor(LIGHTBLUE);			// ���������ɫ
	settextstyle(25, 0, _T("����"));	// ������ʽ��С
	srand((unsigned int) time(NULL));	// �����������
}

/*******************************������**********************************/
void main()
{
	UI();					// �����ʼ��
	Login();				// ��¼����
	getch();				// �����������
	closegraph();			// �ر�ͼ�ν���
}
