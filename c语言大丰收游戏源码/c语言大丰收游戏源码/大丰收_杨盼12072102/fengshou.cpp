#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <IOSTREAM>
#include <STRING>
using namespace std;
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "Winmm.lib")

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

void printmenu();
void printscore();
void monkeymove();
void printguanshu(int);
void paixu();
void paixu2();


typedef struct targets	//-----------------����ˮ�����ԵĽṹ������
{
	short type;			//-----------------�������ˮ��������
	float x;			//-----------------����
	float y;
	float speed;		//-----------------������ٶ�
	struct targets* node;
}target;

struct scores			//-----------------����ϵͳ
{
	int score0;			//-----------------�÷���
	int score1;			//-----------------�۷���
	int score2;			//-----------------��ߵķ���
	char name[20];		//-----------------�û���Ϣ
	char name1[20];		//-----------------�������
}score;

struct _monkey			//-----------------���ӵ�����
{
	float x;			//-----------------����
	float y;
	float speed;		//-----------------�ٶ�	
} monkey;


int main()
{
	MessageBox(NULL,"��Ϸͨ�����̵����Ҽ�����С�������ƶ����ϼ�����С�����������סshift���Լ��٣����ȷ���������û�������س��������ʼ��ť��ʼ��Ϸ����Ϸ�е����ͣ��������ͣ��Ϸ���ƿ������ٴε����ͣ����ʼ��������������Խ�����Ϸ","���ε���Ϸ˵��",MB_OK);//-------------------�����Ĳ���
	FILE * fp1;			//-----------------��¼��������ɼ�
	FILE * fp;			//-----------------��¼��߷�
	FILE * fp2;			//-----------------��¼��ҳɼ�
	FILE * fp3;			//-----------------��¼�������
	fp1=fopen("����2.txt","a");
	fp2=fopen("����3.txt","a");
	fp3=fopen("test.txt","a");
	if ((fp=fopen("����.txt","r"))==NULL)	//-----�ж������ļ�������       
	{
		cout<<"��ǰ����������"<<endl;		//-----��������ʾ
		fp=fopen("����.txt","w");			//-----��ֻд�ķ�ʽ����һ��txt�ļ�
		paixu();
		paixu2();
		cout<<"��������ҵ�������";			//-----�����û��������û������浽txt
		cin>>score.name;					//-----������ҵ�����
		score.score0=0;						//---- ��ʼ��
		score.score1=0;
		score.score2=0;
	}
	else
	{  
		score.score0=0;
		score.score1=0;
        fp=fopen("����.txt","r+");			//------�ж��ļ����ڴ�
		fscanf(fp,"%s",&score.name1);		//------��ȡ����������Ϊname1
		fscanf(fp,"%d",&score.score2);		//------��ȡ�����ķ���Ϊscore2
        paixu();
		paixu2();
		cout<<"��������ҵ�������";
		cin>>score.name;					//------��ǰ��ҵ�����Ϊname
	}
	
	int speed=10;
	cout<<"������ˮ�����ƶ��ٶȣ�Ҫ�������а����Ƽ�ֵ10-30: ";	// �����û������趨�ٶ�speedΪ�ṹ���speed��ֵ
	cin>>speed;
	
	
	srand((unsigned int)time(NULL));
	initgraph (750,480, NOCLOSE);												// ��ʼ���ڴ�С
	mciSendString("open targets\\����ļ���.mp3 alias mymusic", NULL, 0, NULL);	// ������
	mciSendString("play mymusic", NULL, 0, NULL);								// ��������

	
	MOUSEMSG m,m1,m2;
	int guanshu=1;	//------------------------------�ؿ�ȫ�ֱ���
	IMAGE img_scoredel;
    loadimage(&img_scoredel, "targets\\scoredel.bmp");
	
	
	IMAGE img_xigua;
    loadimage(&img_xigua, "targets\\xigua.bmp");
	
	IMAGE img_taozi;
    loadimage(&img_taozi, "targets\\taozi.bmp");
	
	IMAGE img_boluo;
    loadimage(&img_boluo, "targets\\boluo.bmp");
	
	HDC			dstDC = GetImageHDC();  
	HDC			srcDC;
	
	IMAGE img_zhadan;
    loadimage(&img_zhadan, "targets\\zhadan.bmp");
	
    IMAGE img;
	loadimage(&img, "targets\\monkey.bmp");
	
    IMAGE imgbeijing;
	loadimage(&imgbeijing, "targets\\����.jpg",640,480);
	
	IMAGE imgbeijing1;
	loadimage(&imgbeijing1, "targets\\����1.jpg",640,480);
	
	printmenu();
    putimage(0, 0, &imgbeijing);
	BeginBatchDraw();
	target *head=NULL, *point=NULL, *pre=NULL;
	int count=0;
	
	int i=0;
	int s2=1;
	monkey.x=3200; monkey.speed=0; monkey.y=3800;
    
	while(1)
	{
		//-------------��ʼ��ͣ�������Ʋ���
		
		if(MouseHit())					//-------------------- �ж��Ƿ����
		{
			m=GetMouseMsg();
			switch(m.uMsg)
			{
				case WM_LBUTTONDOWN:	//-------------------- ������
				
					if(m.x>=670&&m.x<=720&&m.y>=0&&m.y<=50)		// ���㿪ʼ����--------��ʼ
					{
						while(1)
						{
							if(MouseHit())						// �ж��Ƿ����
							{
								m1=GetMouseMsg();
								switch(m1.uMsg)
								{
									case WM_LBUTTONDOWN:
										if(m1.x>=670&&m1.x<=720&&m1.y>=60&&m1.y<=110)	// ������ͣ���������ѭ��---------��ͣ
										{
											while(1)
											{
												Sleep(20);
												
												m2=GetMouseMsg();
												if(MouseHit())	//---------------------�ж��ٴε������ѭ������
												{
													if(m2.uMsg==WM_LBUTTONDOWN && m2.x>=670&&m2.x<=720&&m2.y>=60&&m2.y<=110)
													{
														break;
													}
													
												}
											}
										}

										if(m1.x>=670&&m1.x<=720&&m1.y>=120&&m1.y<=170)    //----------����
										{
											closegraph();
											return 0;
										}

										break;
								}
							}
						
							i=rand();
							if(guanshu==1)
							{
								putimage(0,0,&imgbeijing);	//------------ ����
							}
							else
							{
								putimage(0,0,&imgbeijing1);	//------------ ����
							}
							
							printscore();
							monkeymove();
							printguanshu(guanshu);
						
						
							srcDC = GetImageHDC(&img);
							TransparentBlt(dstDC, monkey.x/10, monkey.y/10, 60, 60, srcDC, 0, 0, 60, 60, RGB(0,0,0));
							
							if((i%1000)<=30 && count<15)	//-------------����ˮ������ �����ֵ
							{
								point=head;
								head=(targets*)malloc(sizeof(targets));
								++count;
								head->speed=speed;
								head->type=(i%6);
								head->x=(i%6000);
								head->y=-10;
								head->node=point;
							}	
						
							for(pre=point=head;point!=NULL;pre=point,point=point->node)
							{
								
								if(abs(point->y-monkey.y)<=300 && abs(monkey.x-point->x)<=300) // ����ˮ��������	
								{
									
									if (point->type==3)		//------------���Ӽӷ�
									{
										putimage(700,450,&img_scoredel);
										score.score0+=10;
									}
									
									if (point->type==1)		//------------���ϼӷ�
									{  
										putimage(700,450,&img_scoredel);
										score.score0+=20;
									}
									
									if (point->type==2)		//------------���ܼӷ�
									{
										putimage(700,450,&img_scoredel);
										score.score0+=30;		
									}
									
									if (point->type==0)		//------------ը������
									{   
										putimage(700,450,&img_scoredel);
										score.score0-=40;		
									}
									

									if(head==point)			//------------����������������������ˮ��
									{
										head=point->node;
										free(point);
										--count;
										point=head;
										if(point==NULL)
											break;
										continue;
									}
									pre->node=point->node;
									free(point);
									--count;
									point=pre;
									continue;
								}

								if(point->y > 5000)		//------------�߽�5000
								{						//------------û�нӵ���ˮ���۷�
									if (point->type==3)	//------------����
									{
										score.score1+=10;
									}
								}
								
								if(point->y > 5000)
								{
									if (point->type==1)	//------------����
									{
										score.score1+=10;
									}
								}
								
								if(point->y > 5000)
								{
									if (point->type==2)	//-------------����
									{
										score.score1+=10;
									}
								}
								
							
								if(score.score0>500)	//-------------���÷ִﵽ500����ڶ���
								{
									guanshu=2;
								}
								
								if (score.score1>500)	//-------------��û�ӵ�ˮ���۷ִﵽ500Ҫ���˳���Ϸ
								{
									MessageBox(NULL,"�����ˣ�ϵͳ����������ǰ���û����͵÷�","����������",MB_OK);
									
									fprintf(fp1,"%s ",score.name);	//-д�����������Ϣ
									fprintf(fp1,"%d\0",score.score0);
									fprintf(fp2,"%d\0",score.score0);
									fprintf(fp3,"%s ",score.name);
									
									
									if(score.score0>score.score2)	//�ж�  �����ǰ�û��ĵ÷ִ�����ߵ���ʷ�÷�  ��ô�򸲸����
									{
										fp=fopen("����.txt","w");
										fprintf(fp,"%s ",score.name);
										fprintf(fp,"%d",score.score0);
										
									}
									exit(0);
								}
							
								if(point->y>5000)	//---------------���������ˮ��
								{   
									
									if(head==point)
									{
										head=point->node;
										free(point);
										--count;
										point=head;
										if(point==NULL)
											break;
										continue;
									}
									pre->node=point->node;
									free(point);
									--count;
									point=pre;
									continue;
								}
							
							
								if (point->type==3)	//-------------------------����type�����ֵ��ʾ��ͬ��ˮ��
								{
									
									srcDC = GetImageHDC(&img_taozi);	//-----����
									TransparentBlt(dstDC,point->x/10,point->y/10, 60, 50, srcDC, 0, 0, 60, 50, RGB(0,0,0));
								}
								
								if (point->type==1)
								{
									
									srcDC = GetImageHDC(&img_xigua);	//------����
									TransparentBlt(dstDC,point->x/10,point->y/10, 60, 50, srcDC, 0, 0, 60, 50, RGB(0,0,0));
								}
								
								if (point->type==2)
								{
									
									srcDC = GetImageHDC(&img_boluo);	//------����
									TransparentBlt(dstDC,point->x/10,point->y/10, 60, 50, srcDC, 0, 0, 60, 50, RGB(0,0,0));
								}
								
								if (point->type==0)
								{
									
									srcDC = GetImageHDC(&img_zhadan);	//-------ը��
									TransparentBlt(dstDC,point->x/10,point->y/10, 50, 100, srcDC, 0, 0, 50, 100, RGB(0,0,0));
								}
								
								if(guanshu==1)
								{
									(point->y) = (point->y) + (point->speed) + 5*(point->type);	//------------------��һ��---------------------------------���Ʋ�ͬˮ�����ٶ�  ͨ��type
								}
								else
								{
									(point->y) = (point->y) + (point->speed) + 2*(point->type);	//------------------�ڶ���---------------------------------���Ʋ�ͬˮ�����ٶ�  ͨ��type
									(point->x) = (point->x)+3*s2*(point->type);
									s2=-s2;
								}
							}

							FlushBatchDraw();
							Sleep(10);
						}
					}
				}
		}
	}

	return 0;
}


void printmenu()
{
	outtextxy(680,20,"��ʼ");
	rectangle(670,0,720,50);

	outtextxy(680,80,"��ͣ");
	rectangle(670,60,720,110);

	outtextxy(680,140,"����");
	rectangle(670,120,720,170);

	char s[20];

	sprintf(s, "%d", score.score2);	// ��ʾ��߷�������ͷ�
	outtextxy(680, 230, s);
	outtextxy(680, 200, score.name1);
	outtextxy(640, 180, "����û����÷�");
}


void printscore()
{
	char s[20];							// ����ת���ַ����

	sprintf(s, "%d", score.score0);		// �Ƿ�
	outtextxy(640, 400, "��ǰ�ܵ÷���");
	outtextxy(700, 450, s);
	
	sprintf(s, "%d", score.score1);
	outtextxy(640, 350, "�ܿ۷�");
	outtextxy(700, 375, s);
}


void printguanshu(int x)
{
	IMAGE img_scoredel;
    loadimage(&img_scoredel, "targets\\scoredel.bmp");

	switch(x)
	{
		case 1 :
			outtextxy(640,300,"��һ��");
			break;
		case 2 :
			putimage(640,300,&img_scoredel);
			outtextxy(640,250,"�ڶ���");
			break;
	}
}


void monkeymove()
{
	#define KEYDOWN(vk_code)	((GetAsyncKeyState(vk_code) & 0x8000) ?1:0)
	#define KEYUP(vk_code)		((GetAsyncKeyState(vk_code) & 0x8000) ?0:1 )
	
	if(KEYDOWN(VK_LEFT) && monkey.x>0)	//----------------------�������ҿ��Ʋ���
	{
		if(KEYDOWN(VK_SHIFT))			//----------------------shift����,����
		{
			monkey.x-=40;
		}
		else
		{
			monkey.x-=20;
		}
	}
	
	else if(KEYDOWN(VK_RIGHT) && monkey.x<5800)	//---------------����
	{
		if(KEYDOWN(VK_SHIFT))
		{
			monkey.x+=40;
		}
		else
		{
			monkey.x+=20;
		}
	}
	
	if(KEYDOWN(VK_UP)&&monkey.y==3800)			//--------------����
	{
		monkey.speed=45;
	}
	
	if (KEYDOWN(VK_SPACE))	//----------------------------------��ͣ
	{
		system("pause");
		
	}
	
	monkey.y-=monkey.speed;
	
	if(monkey.y>=3800)		//---------------------------------�����޴���
	{
		monkey.y=3800;
		monkey.speed=0;
	}
	else
		monkey.speed--;
	
}


void paixu()
{
	FILE *fin;
    int x[3],t;
    int i,j;
	
    fin=fopen("����3.txt","r");
    for (i=0;i<3;i++) fscanf(fin,"%d",&x[i]);
    fclose(fin);
    for (i=0;i<3;i++)
		for (j=i+1;j<3;j++)
			if (x[i] > x[j]){ t=x[i];x[i]=x[j];x[j]=t;};
			for (i=0;i<3;i++) 
				cout<<x[i]<<endl;
}


void paixu2()
{
	FILE *fin;
	char a[10];
	char b[10];
	char c[10];
	
	fin=fopen("test.txt","r");
	
	fscanf(fin,"%s%s%s",a,b,c);
	fclose(fin);
	
    cout<<a<<endl<<b<<endl<<c<<endl;
}
