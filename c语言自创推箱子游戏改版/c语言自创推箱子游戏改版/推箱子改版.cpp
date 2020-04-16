#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

#define HMAX 22//�߽�߶ȵ����ֵ
#define HMIN 3//�߽�߶ȵ���Сֵ
#define LMAX 37//�߽糤�ȵ����ֵ
#define LMIN 2//�߽糤�ȵ���Сֵ

int mx=20,my=11;
int leave=1;//�ؿ�
int x=20,y=20;//���λ��
int i,j;
int m=10,n=15;//����λ��
int pointx=20,pointy=13;//Ŀ��λ��
char ch;

struct move//С��ṹ��
{
	int x,y;
	int xv,yv;
}ball;
/*----------------------------------------------------------------*/
bool judge();//�ж������ĺ���
void star();
void box(int m,int n);
void gotoxy(int x, int y);
void HideCursor();//���ع��
void tell(char s);//�����ӵĹؼ�����
void goal();
void help();
void welcome();
void move(char ch);
void map();//��ͼ����
void clean(int x,int y);//�����ۼ�����
void moveball();
void moveplay();
void GameOVER();//��Ϸ����ͼ��
void GameJudge();//�ж��Ƿ������
/*--------------------------------------------------------------*/
void player(int x,int y)//���
{
	gotoxy(x,y);
	printf("��");
}

void box(int m,int n)//����һ������
{
	gotoxy(m,n);//���ӵ�λ��
	printf("��");
}

void goal()//Ŀ��λ�õĺ���
{

	if(judge())
	{
		srand(time(NULL));
		pointx=rand()%(36-4)+4;
		pointy=rand()%(21-5)+5;
	}
	gotoxy(pointx,pointy);
	printf("��");//Ŀ���λ��
}
/*--------------------------------------------------------------*/

bool judge()//�ж��������ж������Ƿ񵽴�ָ���ص�
{
	if(pointx==m&&pointy==n)
		return true;
	else
		return false;
}

void condition(int m,int n)//��ʼ��
{
	void goal();
	GameJudge();
	if(judge())
	{   
		leave++;
		system("cls");
		star();
	}
}


void star()
{
	map();
	gotoxy(20,1);
	printf("��%d��",leave);
	box(m,n);
	player(x,y);
	goal();
}
/*-----------------------------������---------------------------------*/
void main()
{
S:  system("color 4f");	//�޸����������ɫ
    welcome();
	HideCursor();
	char ch;
	while(1)
	{
		ch=getch();
		switch(ch)
		{
		case 'w':
		case 'W':
			clean(mx,my);
			my=my-3;
			if(my<11)
				my=my+6;
			gotoxy(mx,my);
			printf("��");
			break;
		case 's':
		case 'S':
			clean(mx,my);
			my=my+3;
			if(my>14)
				my=my-6;
			gotoxy(mx,my);
			printf("��");
			break;
        case '\r':
			if(my==11)
			{
				system("cls");
				HideCursor();
				system("color 2f");//�޸���Ϸ�������ɫ
				star();
				char ch;
				moveball( );
			}
			if(my==14)
			{
				system("cls");
				help();
				while(getch())
				{
					system("cls");
					goto S;//���ڲ�����η���һ��ʼ�Ľ�������ֻ����goto����һ��ʼ�Ľ���
				}
				
			}
			break;
		}
	}
}
/*-----------------------------����---------------------------------*/
void welcome()
{
	printf(" ������������������������������������������������������������������������������\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                �x�y�z�{�|�}�~�������Ӹİ樀�~�}�|�{�z�y�x                ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��  �����˵����                                                            ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��        W ,S ,A ,D �ֱ�����ϡ��¡����ҡ�                               ��\n");
	printf(" ��        �س���ȷ��                                                        ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                               ��������������                             ��\n");
	printf(" ��                               �� �� �� ʼ ��                             ��\n");
	printf(" ��                               ��������������                             ��\n");
	printf(" ��                               ��������������                             ��\n");
	printf(" ��                               �� ��    �� ��                             ��\n");
	printf(" ��                               ��������������                             ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                        by��دSky��ҹح�� ��\n");
	printf(" ��                                                          QQ��598217213   ��\n");
	printf(" ������������������������������������������������������������������������������\n");
	gotoxy(0,0);
}



void help()
{
	printf(" ������������������������������������������������������������������������������\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��            �x�y�z�{�|�}�~�������Ӹİ���Ϸ˵�����~�}�|�{�z�y�x            ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��  ��ʤ��������                                                            ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��          �������Ƶ�Ȧ��͹���                                            ��\n");
	printf(" ��          ����Ϸû�й�������                                              ��\n");
	printf(" ��          ֱ���㱻С����л��߲������˳���Ϸ                              ��\n");
	printf(" ��          ����Ƚϼ򵥣�����ûʲô�Ѷ�!!!!!                              ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                      ���ڱ��˸մ�һ���ո�ѧ������                        ��\n");
	printf(" ��                 ���Ա������кܶ಻��ĵط���������½�                 ��\n");
	printf(" ��                         ��ӭ���һ��������                             ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                            ��������                                ��\n");
	printf(" ��                            ����������ء�                                ��\n");
	printf(" ��                            ��������                                ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                        by��دSky��ҹح�� ��\n");
	printf(" ��                                                           2012��12��20�� ��\n");
	printf(" ������������������������������������������������������������������������������\n");
	gotoxy(0,0);
}
/*-----------------------------����---------------------------------*/

void gotoxy(int x, int y)
{
	COORD c;
	c.X = 2 * x, c.Y = y; //�ƶ����
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void HideCursor()//���ع��
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
/*---------------------------------------------------------------------------*/

void tell(char s)//�����ӵĹؼ�����
{
	if(s=='w'||s=='W')
	{
		if(m==x&&n==y)
		{
			clean(m,n);
			n-=1;
			box(m,n);
		}
	}
	if(s=='s'||s=='S')
	{
		if(m==x&&n==y)
		{
			clean(m,n);
			n+=1;
			box(m,n);
		}
	}
	if(s=='a'||s=='A')
	{
		if(m==x&&n==y)
		{
			clean(m,n);
			m-=1;
			box(m,n);
		}
	}
	if((s=='d'||s=='D'))
	{
		if(m==x&&n==y)
		{
			clean(m,n);
			m+=1;
			box(m,n);
		}
	}
}

/*---------------------------------------------------------------------------*/
/*void move(char ch)//
{
	while(1)
	{
		moveball();/////////////////////////////////////////////////////////////////////
		//condition(m,n);
		//star();
	}	
}*/
/*---------------------------------------------------------------------------*/
void map()
{
	gotoxy(0,2);
	printf(" ����������������������������������������\n");
	printf(" ����������������������������������������\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ���                                                                      ���\n");
	printf(" ����������������������������������������\n");
	printf(" ����������������������������������������\n");
	
}

/*---------------------------------------------------------------------------*/
void clean(int x,int y)
{
	gotoxy(x,y);
	printf(" ");
}


void moveball()//�ƶ�С��
{
	ball.x = 5;
	ball.y = 5;
	ball.xv = 1;
	ball.yv = 1;
	while(1)
	{
		condition(m,n);
		star();
		gotoxy(ball.x,ball.y);
		printf("  ");
		ball.x += ball.xv; 
		ball.y += ball.yv; 
		if(ball.y<=HMIN+1||ball.y>=HMAX-1)
		{
			ball.yv *= -1;
			printf("\a");
		}
		if(ball.x<=LMIN+1||ball.x>=LMAX-1)
		{
			ball.xv *= -1;
			printf("\a");
		}
		gotoxy(ball.x,ball.y);
		printf("��");
		Sleep(20);	
		moveplay();
	}
	
}

void moveplay()//�ƶ���Һ�����
{
	if(kbhit())
	{
		ch=getch();
		switch(ch)
		{
		case 'w':
		case 'W':
			if(y-1>HMIN&&y-1<HMAX)
			{
				clean(x,y);
				y-=1;
				tell(ch);
				box(m,n);
				player(x,y);
			}
			break;
		case 's':
		case 'S':
			if(y+1>HMIN&&y+1<HMAX)
			{
				clean(x,y);
				y+=1;
				tell(ch);
				box(m,n);
				player(x,y);
			}
			break;
		case 'a':
		case 'A':
			if(x-1>LMIN&&x-1<LMAX)
			{
				clean(x,y);
				x-=1;
				tell(ch);
				box(m,n);
				player(x,y);
			}
			break;
		case 'd':
		case 'D':
			if(x+1>LMIN&&x+1<LMAX)
			{
				clean(x,y);
				x+=1;
				tell(ch);
				box(m,n);
				player(x,y);
			}
			break;
		}
	}
}


void GameJudge()
{
	if(ball.x+1==x&&ball.y+1==y||ball.x+1==m&&ball.y+1==n)
	{
		system("cls");
		HideCursor();
		GameOVER();
	}
	if(ball.x-1==x&&ball.y+1==y||ball.x-1==m&&ball.y+1==n)
	{
		system("cls");
		HideCursor();
		GameOVER();
	}
	if(ball.x+1==x&&ball.y-1==y||ball.x-1==m&&ball.y+1==n)
	{
		system("cls");
		HideCursor();
		GameOVER();
	}
	if(ball.x-1==x&&ball.y-1==y||ball.x-1==m&&ball.y+1==n)
	{
		system("cls");
		HideCursor();
		GameOVER();
	}
}





void GameOVER()
{
	system("color 2B");
	printf(" ������������������������������������������������������������������������������\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                ����������ʧ���ˡ�������                      ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                                          ��\n");
	printf(" ��                                                        by��دSky��ҹح�� ��\n");
	printf(" ��                                                          QQ��598217213   ��\n");
	printf(" ������������������������������������������������������������������������������\n");
	Sleep(500);
	exit(0);
}