#include<conio.h>
#include<windows.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

struct player
{
	char name[10];
	int power,speed,wisdom;
	int att,def;
	int HPmax,HP;
	float burst,dodge;
	int EXP,EXPmax,LV,spot;
}player1;
struct monster
{
	char name[10];
	int HP;
	int att,def;
	int	EXP;
	float burst,dodge;
}monster1;
main()
{
	int i=1,j=0,m=28,n=12;
	char c1;
	void play1();
	int bug1(int sli);
	void help();
	void HideCursor();
	void gotoxy(int x,int y);
	void start();
	void wait();
    void initp1();
	void initm1();
	void boundary();
	void play();
	void addspot();
	void sure();
	void p1order();
	void p1die();
S:	m=28,n=12;
	start();
	system("color 2B");
	HideCursor();
	gotoxy(m,n);
    while(1)//{gotoxy(28,12);}
	{
		
		c1=getch();
		switch(c1)
		{
		case'w':
		case'W':
			printf("  ");
			n-=3;
			if(n<12)n=18;
			gotoxy(m,n);
			printf("��");
			gotoxy(m-1,n);
			break;
		case's':
		case'S':
   			printf("  ");
			n+=3;
			if(n>18)n=12;
			gotoxy(m,n);
			printf("��");
			gotoxy(m-1,n);
			break;
		case'j':
		case'J':
			if(18==n)
				exit(0);
			if(15==n)
			{
				system("cls");
			    help();
				while(getch()){system("cls");goto S;}
			}
			if(12==n)
			{	
				system("cls");
			    wait();
				initp1();
				initm1();
				while(1)
				{
					printf("�������������:(������10���ַ�)\n");
					sprintf(player1.name,"%s","\0");
		            gets(player1.name);
		            if(strlen(player1.name)<=9)break;
				}
				system("cls");
                boundary();
				while(1){
				initm1();
				play();
				Sleep(1000);
				addspot();
				sure();
             	Sleep(1000);
				p1order();}

			}
			break;
		}
	}
			


    



}
void gotoxy(int x,int y)       //������ƶ�������Ϊ(x,y)�ĵط�
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;                            
    HANDLE hConsoleOut;
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
    csbiInfo.dwCursorPosition.X = x;                                    
    csbiInfo.dwCursorPosition.Y = y;                                    
    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);   
}

void HideCursor()//���ع��
{
CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

int bug1(int sli)
{
    if(sli<0)sli=0;
	return sli;
}

void play1()
{
	int t=0,i=1;
	int LV=1,EXPmax=10,EXP=0,HPmax=30,HP=30,power=0,speed=0,wisdom=0,att=10,def=5,spot=0;
	float dodge=5,burst=5;
	int AI1_HP,AI1_att,AI1_def,AI1_exp;
    int AI2_HP,AI2_att,AI2_def,AI2_exp;
	char yc1,yc2;
	char enter1,enter2;
	char name[10];
	srand(time(NULL));
	power=rand()%8+7;
	speed=rand()%8+7;
	wisdom=rand()%8+7;
	spot=45-power-speed-wisdom;
NO3:printf("��������ǣ�\n");
	scanf(" %s",name);
NO2:while(1)
	{
    printf("�����������Ե㡣��a.����b.�ٶ�c.�����������HP%d,����%d,�ٶ�%d,����%d,����%d,����%d,������%f,������%f,ʣ��%d�㣩\n",HPmax=30+power*2,power,speed,wisdom,att=10+power*1.5,def=5+wisdom*1.5,dodge=5+speed*0.4,burst=5+speed*0.4,spot);
	scanf(" %c",&yc1);
	switch(yc1)
	{
	case'a':power+=1,spot-=1;break;
	case'b':speed+=1,spot-=1;break;
	case'c':wisdom+=1,spot-=1;break;
	default:printf("�����������������롣\n");
	}
    if(spot==0)break;
	}
	printf("�ǳƣ�%s\n״̬��LV��%d\nEXP��%d/%d\n���HP��%d\nHP��%d\n��������%d\n��������%d\n�����ʣ�%f\n�����ʣ�%f\n",name,LV,EXP,EXPmax,HPmax,HP=HPmax,att,def,dodge,burst);
NO1:printf("��y����\n");
	while(1)
	{
	scanf(" %c",&enter1);
	if(enter1!='y')printf("��y����\n");
    if(enter1=='y')break;
	}
    AI1_HP=rand()%20+30;
    AI1_att=rand()%15+25;
    AI1_def=50-AI1_att;
	AI1_exp=15;
    printf("�������׼������ս����\n������Ϣ��\nHP��%d\n������%d\n������%d\n",AI1_HP,AI1_att,AI1_def);
	while(1)
	{
	if(HP<=0)break;
	printf("a.����b.����\n");
    scanf(" %c",&yc2);
	switch(yc2)
	{
	case'a':if(rand()%100+1<=5)printf("%s������miss!\n",name);
		    else if((rand()%100+1)*10<=burst*10)
				printf("%s������������������ʧ%dHP,����ʣ��%dHP\n",name,att,bug1(AI1_HP-=att));
			else
				printf("%s������������ʧ%dHP,����ʣ��%dHP\n",name,bug1(att-AI1_def),bug1(AI1_HP-=bug1(att-AI1_def)));
            if(AI1_HP<=0)break;
            if((rand()%100+1)*10<=dodge*10)printf("���﹥����miss!\n");
		    else if(rand()%100+1<=5)
				printf("���﹥����������%s��ʧ%dHP,%sʣ��%dHP\n",name,AI1_att,name,bug1(HP-=AI1_att));
			else 
				printf("���﹥����%s��ʧ%dHP,%sʣ��%dHP\n",name,bug1(AI1_att-def),name,bug1(HP-=bug1(AI1_att-def)));break;
	case'b':if(rand()%2==0)goto NO1;
		    else if((rand()%100+1)*10<=dodge*10)printf("����ʧ�ܣ����﹥����miss!\n");
			else if(rand()%100+1<=5)
				printf("����ʧ�ܣ����﹥����������%s��ʧ%dHP,%sʣ��%dHP\n",name,AI1_att,name,bug1(HP-=AI1_att));
			else 
				printf("����ʧ�ܣ����﹥����%s��ʧ%dHP,%sʣ��%dHP\n",name,bug1(AI1_att-def),name,bug1(HP-=bug1(AI1_att-def)));break;
	default:printf("�����������������롣\n");
	}
	if(AI1_HP<=0)break;
	}
    if(HP<=0)goto END;
    EXP+=AI1_exp;
	if(EXP>=EXPmax)LV+=1,spot+=5,EXP-=EXPmax,EXPmax+=20*(LV-1),printf("��ܹ��%s�����ˡ�\n",name);
	else printf("��ܹ������y��������,����q�鿴���ԡ�\n");
    if(spot!=0)goto NO2;
    while(1)
	{
	scanf(" %c",&enter2);
	if(enter2!='y')printf("��y����\n");
    if(enter2=='q')printf("�ǳƣ�%s\n״̬�����HP��%d\nHP��%d\n��������%d\n��������%d\n�����ʣ�%f\n�����ʣ�%f\n",name,HPmax,HP=HPmax,att,def,dodge,burst);
	if(enter2=='y')goto NO1;
	}
END:printf("��ɫ��������Ϸ������\n");



}

void wait()
{
    int i=0,m=4,n=3;
	void HideCursor();
	void gotoxy(int x,int y);
	printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
    printf("�U                                                                            �U");
    printf("�U  �u�������������������������������������������������������������������������U");
    printf("�U  ��                                                                  ��%%  �U");
    printf("�U  �v�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x���x���U");
    printf("�U                                                                            �U");
    printf("�U                                                                            �U");
    printf("�U                                                                            �U");
    printf("�U                                                                            �U");
    printf("�U            ���q���੤�����������Щ������������������r�Щ��r                �U");
    printf("�U            �������੤�����������ੰ�ةة������������r�����r                �U");
    printf("�U            �������ة����������q�ȩ��������������������੤��                �U");
    printf("�U            �����������ȡ����������������ȡ������������ة���                �U");
    printf("�U            �����������ȡ����������������ȡ����������Щ��ੴ                �U");
    printf("�U            ���t��������      �����������s      ���������s��                �U");
    printf("�U                                                                            �U");
    printf("�U                                                                            �U");
    printf("�U                                                                            �U");
    printf("�U                                                                            �U");
    printf("�U                                                                            �U");
    printf("�U                                                                            �U");
    printf("�U                                                                            �U");
    printf("�U                                                                            �U");
    printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
    while(1)
	{

		  Sleep(50);
		  gotoxy(m+=2,n);
		  printf("��");
		  gotoxy(76,n);
		  printf("%2d",i+=3);
		  if(i==99)
		  {
			  Sleep(2000);
			  break;
		  }
	}
	system("cls");
}

void start()
{
    printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	printf("�UBeta0.1                                                                     �U");
	printf("�U                                                                            �U");
	printf("�U    ���[�T�m�T�[���q�j�T���j�[���������[�������X�T�T�T�T�[���X�[�q�T�T�[    �U");
	printf("�U    �X�d�X�T�[�����X�m�T�T�s�[���^�T�T�d�T�a���U�T�T�T�T�U���U�U�U�����U    �U");
	printf("�U    ���U�U���U�������s�j�T�T�[���������U�������X�T�T�T�[�U���U�s�a�T�T�^    �U");
	printf("�U    ���U�U���U�[���^�T�T�T�T�s���������U�������d�T�T�T�g�U���U�U�X�X���[    �U");
	printf("�U    ���U�U���U�U���^�s�j�T�T�[���������U�T�r���d�T�T�T�g�U���d�s�t�t�X�s    �U");
	printf("�U    �^�m�s���^�s  �^�T�T�T�T�s  �^�T�T�s���a  �^�T�T�T�s�t  �^���T�T�m�a    �U");
	printf("�U                                                                            �U");
	printf("�U                                                                            �U");
	printf("�U                              ������������                                  �U");
	printf("�U                          ��  ����    ʼ��                                  �U");
	printf("�U                              ������������                                  �U");
	printf("�U                              ������������                                  �U");
	printf("�U                              ����    ����                                  �U");
	printf("�U                              ������������                                  �U");
	printf("�U                              ������������                                  �U");
	printf("�U                              ����    ����                                  �U");
	printf("�U                              ������������                                  �U");
	printf("�U                                                                            �U");
	printf("�U                                                             ����QQ993107057�U");
	printf("�U                                                             �ٶ�ID:������ǧ�U");
	printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
}

void initp1()
{
    player1.power=player1.speed=player1.wisdom=0;
	player1.att=10+player1.power*1.5;
    player1.def=5+player1.wisdom*1.5;
    player1.HPmax=30+player1.power*2;
	player1.HP=player1.HPmax;
    player1.burst=player1.dodge=5+player1.speed*0.4;
	player1.LV=1;
	player1.EXPmax=15+20*player1.LV*(player1.LV-1);
	player1.EXP=0;
	player1.spot=30;
}

void initm1()
{
	srand(time(0));
	sprintf(monster1.name,"%s","����");
    monster1.HP=rand()%20+30;
    monster1.att=rand()%15+25;
    monster1.def=50-monster1.att;
    monster1.EXP=15;
	monster1.burst=monster1.dodge=5;
}

void play()
{
	int bug1(int x);
	player1.att=10+player1.power*1.5;
	player1.def=5+player1.wisdom*1.5;
	player1.HPmax=30+player1.power*2;
	player1.burst=player1.dodge=5+player1.speed*0.4;
	gotoxy(11,2);
	printf("%s",player1.name);
	gotoxy(11,3);
	printf("%3d/%3d",bug1(player1.HP),player1.HPmax);
	gotoxy(11,4);
	printf("%3d",player1.att);
	gotoxy(11,5);
	printf("%3d",player1.def);
	gotoxy(11,6);
	printf("%2.1f",player1.burst);
	gotoxy(11,7);
	printf("%2.1f",player1.dodge);
	gotoxy(11,8);
    printf("%3d",player1.power);
	gotoxy(11,9);
	printf("%3d",player1.speed);
	gotoxy(11,10);
	printf("%3d",player1.wisdom);
	gotoxy(11,11);
	printf("%3d/%3d",player1.EXP,player1.EXPmax);
	gotoxy(11,12);
	printf("%2d",player1.LV);
	gotoxy(35,5);
	printf("%2d",player1.spot);
	gotoxy(67,2);
	printf("%s",monster1.name);
	gotoxy(67,3);
	printf("%3d",bug1(monster1.HP));
	gotoxy(67,4);
	printf("%3d",monster1.att);
    gotoxy(67,5);
	printf("%3d",monster1.def);
	gotoxy(67,6);
	printf("%2.1f",monster1.burst);
	gotoxy(67,7);
	printf("%2.1f",monster1.dodge);
	gotoxy(67,8);
	printf("%3d",monster1.EXP);
}

void boundary()
{
	printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	printf("�U����������������������������������������                ���������������������U");
	printf("�U��  name:         ����          ���������q�r�q�r�q�T�T�r��  name:         ���U");
	printf("�U��    HP:         ����          ���ٶȩ��U�U�U�U�U�q�T�s��    HP:         ���U");
	printf("�U��������:         ����          ���������U�U�U�U�U�t�T�r��������:         ���U");
	printf("�U��������:         ����ʣ��ӵ���:     ���U�U�U�U�t�T�r�U��������:         ���U");
	printf("�U��������:         �����������������������t�r�q�s�q�T�s�U��������:         ���U");
	printf("�U��������:         ����            ������  �t�s���t�T�T�s��������:         ���U");
	printf("�U��  ����:         ����            ���ܩ�                ��   EXP:         ���U");
	printf("�U��  �ٶ�:         ����  �q����r    ��                ��      ____()()  ���U");
	printf("�U��  ����:         ����  {/-���-/}    ��                ��     /      @@  ���U");
	printf("�U��   EXP:         ����   ( (oo) )     ��                ��~~~~~\\_;m__m._>o���U");
	printf("�U��    LV:         ����    ����      ��                ��                ���U");
	printf("�U�����������������������������������������������������������������������������U");
	printf("�U                                                                            �U");
	printf("�U                                                                            �U");
	printf("�U                                                                            �U");
	printf("�U                                                                            �U");
	printf("�U                                                                            �U");
	printf("�U                                                                            �U");
	printf("�U                                                                            �U");
	printf("�U                                                                            �U");
	printf("�U                                                                            �U");
	printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
}


void addspot()
{        
        char c2;
	    int m=28,n=2;
		if(player1.spot>0){
	    gotoxy(2,14);
        printf("                                                   ");
		gotoxy(2,14);
		printf("��ӵ�!");
	    gotoxy(m,n);
		printf("��");
		gotoxy(27,2);
		while(1)
		{
			c2=getch();
			switch(c2)
			{
		case'w':
		case'W':
			printf("  ");
			n-=1;
			if(n<2)n=4;
			gotoxy(m,n);
			printf("��");
			gotoxy(m-1,n);
			break;
		case's':
		case'S':
   			printf("  ");
			n+=1;
			if(n>4)n=2;
			gotoxy(m,n);
			printf("��");
			gotoxy(m-1,n);
			break;
		case'j':
		case'J':
			if(n==2)player1.power+=1,player1.spot-=1;
		    if(n==3)player1.speed+=1,player1.spot-=1;
            if(n==4)player1.wisdom+=1,player1.spot-=1;
			play();
			gotoxy(m,n);
			break;
			}
			if(player1.spot==0)
			{
				gotoxy(27,2);
					printf("  ");
				gotoxy(27,3);
				printf("  ");
				gotoxy(27,4);
				printf("  ");
					break;}}
		}
}

void sure()
{
    char c3;
	int m,n;
A:  m=45,n=9;
	gotoxy(42,8);
	printf("�X�T�T�T�T�T�T�[");
	gotoxy(42,9);
	printf("�U            �U");
	gotoxy(42,10);
	printf("�U            �U");
	gotoxy(42,11);
    printf("�U            �U");
	gotoxy(42,12);
    printf("�^�T�T�T�T�T�T�a");
	gotoxy(51,9);
	printf("����");
	gotoxy(51,11);
	printf("�˳�");
	gotoxy(45,9);
	printf("��");
	gotoxy(45,9);
	while(1)
	{
		c3=getch();
		switch(c3)
		{
		case'w':
		case'W':
			printf("  ");
			n-=2;
			if(n<9)n=11;
			gotoxy(m,n);
			printf("��");
			gotoxy(m-1,n);
			break;
		case's':
		case'S':
   			printf("  ");
			n+=2;
			if(n>11)n=9;
			gotoxy(m,n);
			printf("��");
			gotoxy(m-1,n);
			break;
		case'j':
		case'J':
			if(n==9)
			{
	gotoxy(42,8);
	printf("                ");
	gotoxy(42,9);
	printf("                ");
	gotoxy(42,10);
	printf("                ");
	gotoxy(42,11);
    printf("                ");
	gotoxy(42,12);
    printf("                ");
	goto B;
			}
			if(n==11)
			{
    gotoxy(42,8);
	printf("�X�T�T�T�T�T�T�[");
	gotoxy(42,9);
	printf("�U            �U");
	gotoxy(42,10);
	printf("�U            �U");
	gotoxy(42,11);
    printf("�U            �U");
	gotoxy(42,12);
    printf("�^�T�T�T�T�T�T�a");
	gotoxy(46,9);
	printf("��   ��");
	gotoxy(46,10);
	printf("��");
	gotoxy(46,10);
	m=46,n=10;
	while(1)
	{
	    c3=getch();
		switch(c3)
		{
		case'a':
		case'A':
			printf("  ");
			m-=5;
			if(m<46)m=51;
			gotoxy(m,n);
			printf("��");
			gotoxy(m-1,n);
			break;
		case'd':
		case'D':
   			printf("  ");
			m+=5;
			if(m>51)m=46;
			gotoxy(m,n);
			printf("��");
			gotoxy(m-1,n);
			break;
		case'j':
		case'J':
			if(m==51)exit(0);
			if(m==46)goto A;
		}
	}
			}
		}
	}
B:gotoxy(28,7);
}

void p1die()
{
printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
printf("�U                                                                            �U");
printf("�U                           .-\"      \"-.                                     �U");	
printf("�U                          /            \\                                    �U");
printf("�U                         |      ��      |                                   �U");
printf("�U                         |,  .-.  .-.  ,|                                   �U");
printf("�U                         | )(__/  \\__)( |                                   �U");
printf("�U                         |/     /\\     \\|                                   �U");
printf("�U               (@_       (_     ^^     _)                                   �U");
printf("�U          _     ) \\_______\\__|IIIIII|__/__________________________          �U");
printf("�U         (_)@8@8{}<________|-\\IIIIII/-|___________________________>         �U");
printf("�U                )_/        \\          /                                     �U");
printf("�U               (@           `--------`                                      �U");
printf("�U                                                                            �U");
printf("�U                                                                            �U");
printf("�U    �ǩ������������ǩ��������������ש����ש����������r����                  �U");
printf("�U    �������ש������s�����ש��������ǩ����������ש����ߩ��s                  �U");
printf("�U    �������������������������������s����������������������                  �U");
printf("�U    �ǩ����ǩ��ϡ������������������t���ϩǩ���������������                  �U");
printf("�U    �ǩ����ǩ��ϡ��ǩ����ߩ��s����������������������������                  �U");
printf("�U    �s���������s  �t���������s  �������s���s  �����������s                  �U");
printf("�U                                                                            �U");
printf("�U                                                                            �U");
printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
Sleep(5000);
system("cls");
gotoxy(0,0);
exit(0);
}       

void p1order()
{
	char c4;
	int m,n;
	void addspot();
	void p1att();
	void m1att();
	void play();
	int p1run();
	gotoxy(28,7);
	printf("  ");
	gotoxy(28,8);
	printf("  ");
	gotoxy(28,7);
	printf("��");
	gotoxy(28,7);
	m=28,n=7;
	while(1)
	{
		c4=getch();
		switch(c4)
		{
		case'w':
		case'W':
			gotoxy(28,7);
            printf("  ");
	        gotoxy(28,8);
	        printf("  ");
			n-=1;
			if(n<7)n=8;
			gotoxy(m,n);
			printf("��");
			gotoxy(m-1,n);
			break;
		case's':
		case'S':
   				gotoxy(28,7);
	        printf("  ");
	       gotoxy(28,8);
	         printf("  ");
			n+=1;
			if(n>8)n=7;
			gotoxy(m,n);
			printf("��");
			gotoxy(m-1,n);
			break;
		case'j':
		case'J':
			if(n==7){p1att();addspot();if(monster1.HP<=0){sure();initm1();play();}}
			if(n==8)
			{
				p1run();
				if(player1.HP<=0)
			{
				system("cls");
				gotoxy(0,0);
				p1die();
				Sleep(3);
			}
			
			}
			
		}
	}
		

}

void p1att()
{
	void gotoxy();
	void play();
	void sure();
	int bug1(int x);
	srand(time(0));
	gotoxy(2,16);
    printf("                                                   ");
	gotoxy(2,14);
	printf("                                                   ");
    gotoxy(2,14);
	Sleep(1000);
			if(rand()%100+1<=5)printf("%s������miss!\n",player1.name);
		    else if((rand()%100+1)*10<=player1.burst*10)
				printf("%s������������������ʧ%dHP,����ʣ��%dHP\n",player1.name,player1.att,bug1(monster1.HP-=player1.att));
			else
				printf("%s������������ʧ%dHP,����ʣ��%dHP\n",player1.name,bug1(player1.att-monster1.def),bug1(monster1.HP-=bug1(player1.att-monster1.def)));
        play(); 
	gotoxy(2,15);
	printf("                                                   ");
	gotoxy(2,15);

			if(monster1.HP<=0)
			{
				player1.EXP+=monster1.EXP;
				gotoxy(2,16);
				printf("��ܹ�����%d����.",monster1.EXP);
				if(player1.EXP>=player1.EXPmax)
				player1.LV+=1,player1.spot+=5,player1.EXP-=player1.EXPmax,player1.EXPmax+=20*(player1.LV-1),player1.HP=player1.HPmax,printf("������!");
				play();
				goto NEXT;
			}
           Sleep(1000);
		    gotoxy(2,16);
            if((rand()%100+1)*10<=player1.dodge*10)printf("���﹥����miss!\n");
		    else if(rand()%100+1<=5)
				printf("���﹥����������%s��ʧ%dHP,%sʣ��%dHP\n",player1.name,monster1.att,player1.name,bug1(player1.HP-=monster1.att));
			else 
				printf("���﹥����%s��ʧ%dHP,%sʣ��%dHP\n",player1.name,bug1(monster1.att-player1.def),player1.name,bug1(player1.HP-=bug1(monster1.att-player1.def)));
			play();
			gotoxy(28,7);
            if(player1.HP<=0)
			{
				system("cls");
				gotoxy(0,0);
				p1die();
				Sleep(3);
			}
    NEXT:;
}			

int p1run()
{

	        if(rand()%2==0)
			{
				gotoxy(2,14);
				printf("                                                   ");
				gotoxy(2,14);
				printf("���ܳɹ�!");
				sure();
				p1order();
			}
		    else if((rand()%100+1)*10<=player1.dodge*10)
			{
				gotoxy(2,14);
				printf("                                                   ");
				gotoxy(2,14);
				printf("����ʧ�ܣ����﹥����miss!\n");
			}
			else if(rand()%100+1<=5)
			{
				gotoxy(2,14);
				printf("                                                   ");
				gotoxy(2,14);
				printf("����ʧ�ܣ����﹥����������%s��ʧ%dHP,%sʣ��%dHP\n",player1.name,monster1.att,player1.name,bug1(player1.HP-=monster1.att));
				play();
			}
			else 
			{
				gotoxy(2,14);
				printf("                                                   ");
				gotoxy(2,14);
				printf("����ʧ�ܣ����﹥����%s��ʧ%dHP,%sʣ��%dHP\n",player1.name,bug1(monster1.att-player1.def),player1.name,bug1(player1.HP-=bug1(monster1.att-player1.def)));
				play();
			}
   return player1.HP;
}

void help()
{
printf("                    �������������������              \n");
printf("                    ��       �� �� �� ð ��           ��              \n");
printf("                    ��                                ��              \n");
printf("                    ��     ��               ��        ��              \n");
printf("                    ��                                ��              \n");
printf("                    �������������������              \n");
printf("+������������+1.5��HPmax+2��+�ٶȣ����������ܸ�+0.4��+������������+1.5\n");
printf("                                                                      \n");
printf("                          ��Ϊ���ǵ�һ�β��԰棬                      \n");
printf("         W              ������Ϸ�������пӵ�Ԫ�ء�                    \n");
printf("         ��               ������Ϸ�����Ի����ߣ�                      \n");
printf("                        ��Ҫ����Ϊû��ó�ʼ���ԡ�                    \n");
printf("                     ��������������������������������    ��������     \n");
printf("  S��          ��D   ����л�ٶȰ���ID6210001��ָ��!��    ��ȷ�ϩ�     \n");
printf("                     ��������������������������������    ��������     \n");
printf("                       ����Ҳֻ�Ǹ����ϴ�һ��ѧ����                   \n");
printf("         ��               ��ѧC���ԣ��������ޡ�             J         \n");
printf("         S                   ��������ĩ�ڼ䣬                         \n");
printf("                         ����Ҫ�����Ƶĸ�ϰͻ����                     \n");
printf("                             ûʱ�������Ϸ��                         \n");
printf("                                 �����¡�                             \n");
printf("                                                           ������ǧ   \n");
printf("                                                        2012��12��10��\n");
}



                                     

                                     
                                                                 
                                                                 
                                                                 
                                                                               
         
