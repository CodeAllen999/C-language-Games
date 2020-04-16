#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <IOSTREAM>
#include <STRING>
using namespace std;
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "Winmm.lib")

/* 【自学去】网站收集 http://www.zixue7.com */

void printmenu();
void printscore();
void monkeymove();
void printguanshu(int);
void paixu();
void paixu2();


typedef struct targets	//-----------------控制水果属性的结构体链表
{
	short type;			//-----------------随机产生水果的种类
	float x;			//-----------------坐标
	float y;
	float speed;		//-----------------下落的速度
	struct targets* node;
}target;

struct scores			//-----------------分数系统
{
	int score0;			//-----------------得分数
	int score1;			//-----------------扣分数
	int score2;			//-----------------最高的分数
	char name[20];		//-----------------用户信息
	char name1[20];		//-----------------最高姓名
}score;

struct _monkey			//-----------------猴子的属性
{
	float x;			//-----------------坐标
	float y;
	float speed;		//-----------------速度	
} monkey;


int main()
{
	MessageBox(NULL,"游戏通过键盘的左右键控制小猴左右移动，上键控制小猴的跳动，按住shift可以加速，点击确定后，输入用户名，后回车，点击开始按钮开始游戏，游戏中点击暂停键可以暂停游戏，移开鼠标后再次点击暂停键开始，点击结束键可以结束游戏","杨盼的游戏说明",MB_OK);//-------------------排名的部分
	FILE * fp1;			//-----------------记录玩家姓名成绩
	FILE * fp;			//-----------------记录最高分
	FILE * fp2;			//-----------------记录玩家成绩
	FILE * fp3;			//-----------------记录玩家姓名
	fp1=fopen("排名2.txt","a");
	fp2=fopen("排名3.txt","a");
	fp3=fopen("test.txt","a");
	if ((fp=fopen("排名.txt","r"))==NULL)	//-----判断排名文件不存在       
	{
		cout<<"当前不存在排名"<<endl;		//-----不存在提示
		fp=fopen("排名.txt","w");			//-----以只写的方式建立一个txt文件
		paixu();
		paixu2();
		cout<<"请输入玩家的姓名：";			//-----输入用户名并将用户名保存到txt
		cin>>score.name;					//-----输入玩家的名字
		score.score0=0;						//---- 初始化
		score.score1=0;
		score.score2=0;
	}
	else
	{  
		score.score0=0;
		score.score1=0;
        fp=fopen("排名.txt","r+");			//------判断文件存在打开
		fscanf(fp,"%s",&score.name1);		//------读取排名的名字为name1
		fscanf(fp,"%d",&score.score2);		//------读取排名的分数为score2
        paixu();
		paixu2();
		cout<<"请输入玩家的姓名：";
		cin>>score.name;					//------当前玩家的名字为name
	}
	
	int speed=10;
	cout<<"请输入水果的移动速度，要量力而行啊！推荐值10-30: ";	// 可以用户自行设定速度speed为结构体的speed赋值
	cin>>speed;
	
	
	srand((unsigned int)time(NULL));
	initgraph (750,480, NOCLOSE);												// 初始窗口大小
	mciSendString("open targets\\明天的记忆.mp3 alias mymusic", NULL, 0, NULL);	// 打开音乐
	mciSendString("play mymusic", NULL, 0, NULL);								// 播放音乐

	
	MOUSEMSG m,m1,m2;
	int guanshu=1;	//------------------------------关卡全局变量
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
	loadimage(&imgbeijing, "targets\\背景.jpg",640,480);
	
	IMAGE imgbeijing1;
	loadimage(&imgbeijing1, "targets\\背景1.jpg",640,480);
	
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
		//-------------开始暂停结束控制部分
		
		if(MouseHit())					//-------------------- 判断是否按鼠标
		{
			m=GetMouseMsg();
			switch(m.uMsg)
			{
				case WM_LBUTTONDOWN:	//-------------------- 鼠标左键
				
					if(m.x>=670&&m.x<=720&&m.y>=0&&m.y<=50)		// 满足开始坐标--------开始
					{
						while(1)
						{
							if(MouseHit())						// 判断是否按鼠标
							{
								m1=GetMouseMsg();
								switch(m1.uMsg)
								{
									case WM_LBUTTONDOWN:
										if(m1.x>=670&&m1.x<=720&&m1.y>=60&&m1.y<=110)	// 满足暂停坐标进入死循环---------暂停
										{
											while(1)
											{
												Sleep(20);
												
												m2=GetMouseMsg();
												if(MouseHit())	//---------------------判断再次点击跳出循环继续
												{
													if(m2.uMsg==WM_LBUTTONDOWN && m2.x>=670&&m2.x<=720&&m2.y>=60&&m2.y<=110)
													{
														break;
													}
													
												}
											}
										}

										if(m1.x>=670&&m1.x<=720&&m1.y>=120&&m1.y<=170)    //----------结束
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
								putimage(0,0,&imgbeijing);	//------------ 清屏
							}
							else
							{
								putimage(0,0,&imgbeijing1);	//------------ 清屏
							}
							
							printscore();
							monkeymove();
							printguanshu(guanshu);
						
						
							srcDC = GetImageHDC(&img);
							TransparentBlt(dstDC, monkey.x/10, monkey.y/10, 60, 60, srcDC, 0, 0, 60, 60, RGB(0,0,0));
							
							if((i%1000)<=30 && count<15)	//-------------生成水果链表 赋随机值
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
								
								if(abs(point->y-monkey.y)<=300 && abs(monkey.x-point->x)<=300) // 碰到水果的条件	
								{
									
									if (point->type==3)		//------------桃子加分
									{
										putimage(700,450,&img_scoredel);
										score.score0+=10;
									}
									
									if (point->type==1)		//------------西瓜加分
									{  
										putimage(700,450,&img_scoredel);
										score.score0+=20;
									}
									
									if (point->type==2)		//------------菠萝加分
									{
										putimage(700,450,&img_scoredel);
										score.score0+=30;		
									}
									
									if (point->type==0)		//------------炸弹减分
									{   
										putimage(700,450,&img_scoredel);
										score.score0-=40;		
									}
									

									if(head==point)			//------------遍历链表消除满足条件的水果
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

								if(point->y > 5000)		//------------边界5000
								{						//------------没有接到的水果扣分
									if (point->type==3)	//------------桃子
									{
										score.score1+=10;
									}
								}
								
								if(point->y > 5000)
								{
									if (point->type==1)	//------------西瓜
									{
										score.score1+=10;
									}
								}
								
								if(point->y > 5000)
								{
									if (point->type==2)	//-------------菠萝
									{
										score.score1+=10;
									}
								}
								
							
								if(score.score0>500)	//-------------当得分达到500进入第二关
								{
									guanshu=2;
								}
								
								if (score.score1>500)	//-------------当没接到水果扣分达到500要求退出游戏
								{
									MessageBox(NULL,"你输了，系统将保存您当前的用户名和得分","杨盼提醒您",MB_OK);
									
									fprintf(fp1,"%s ",score.name);	//-写入所有玩家信息
									fprintf(fp1,"%d\0",score.score0);
									fprintf(fp2,"%d\0",score.score0);
									fprintf(fp3,"%s ",score.name);
									
									
									if(score.score0>score.score2)	//判断  如果当前用户的得分大于最高的历史得分  那么则覆盖最高
									{
										fp=fopen("排名.txt","w");
										fprintf(fp,"%s ",score.name);
										fprintf(fp,"%d",score.score0);
										
									}
									exit(0);
								}
							
								if(point->y>5000)	//---------------消除超界的水果
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
							
							
								if (point->type==3)	//-------------------------根据type的随机值显示不同的水果
								{
									
									srcDC = GetImageHDC(&img_taozi);	//-----桃子
									TransparentBlt(dstDC,point->x/10,point->y/10, 60, 50, srcDC, 0, 0, 60, 50, RGB(0,0,0));
								}
								
								if (point->type==1)
								{
									
									srcDC = GetImageHDC(&img_xigua);	//------西瓜
									TransparentBlt(dstDC,point->x/10,point->y/10, 60, 50, srcDC, 0, 0, 60, 50, RGB(0,0,0));
								}
								
								if (point->type==2)
								{
									
									srcDC = GetImageHDC(&img_boluo);	//------菠萝
									TransparentBlt(dstDC,point->x/10,point->y/10, 60, 50, srcDC, 0, 0, 60, 50, RGB(0,0,0));
								}
								
								if (point->type==0)
								{
									
									srcDC = GetImageHDC(&img_zhadan);	//-------炸弹
									TransparentBlt(dstDC,point->x/10,point->y/10, 50, 100, srcDC, 0, 0, 50, 100, RGB(0,0,0));
								}
								
								if(guanshu==1)
								{
									(point->y) = (point->y) + (point->speed) + 5*(point->type);	//------------------第一关---------------------------------控制不同水果的速度  通过type
								}
								else
								{
									(point->y) = (point->y) + (point->speed) + 2*(point->type);	//------------------第二关---------------------------------控制不同水果的速度  通过type
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
	outtextxy(680,20,"开始");
	rectangle(670,0,720,50);

	outtextxy(680,80,"暂停");
	rectangle(670,60,720,110);

	outtextxy(680,140,"结束");
	rectangle(670,120,720,170);

	char s[20];

	sprintf(s, "%d", score.score2);	// 显示最高分玩家名和分
	outtextxy(680, 230, s);
	outtextxy(680, 200, score.name1);
	outtextxy(640, 180, "最高用户名得分");
}


void printscore()
{
	char s[20];							// 整形转换字符输出

	sprintf(s, "%d", score.score0);		// 记分
	outtextxy(640, 400, "当前总得分数");
	outtextxy(700, 450, s);
	
	sprintf(s, "%d", score.score1);
	outtextxy(640, 350, "总扣分");
	outtextxy(700, 375, s);
}


void printguanshu(int x)
{
	IMAGE img_scoredel;
    loadimage(&img_scoredel, "targets\\scoredel.bmp");

	switch(x)
	{
		case 1 :
			outtextxy(640,300,"第一关");
			break;
		case 2 :
			putimage(640,300,&img_scoredel);
			outtextxy(640,250,"第二关");
			break;
	}
}


void monkeymove()
{
	#define KEYDOWN(vk_code)	((GetAsyncKeyState(vk_code) & 0x8000) ?1:0)
	#define KEYUP(vk_code)		((GetAsyncKeyState(vk_code) & 0x8000) ?0:1 )
	
	if(KEYDOWN(VK_LEFT) && monkey.x>0)	//----------------------上下左右控制部分
	{
		if(KEYDOWN(VK_SHIFT))			//----------------------shift加速,向左
		{
			monkey.x-=40;
		}
		else
		{
			monkey.x-=20;
		}
	}
	
	else if(KEYDOWN(VK_RIGHT) && monkey.x<5800)	//---------------向右
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
	
	if(KEYDOWN(VK_UP)&&monkey.y==3800)			//--------------向上
	{
		monkey.speed=45;
	}
	
	if (KEYDOWN(VK_SPACE))	//----------------------------------暂停
	{
		system("pause");
		
	}
	
	monkey.y-=monkey.speed;
	
	if(monkey.y>=3800)		//---------------------------------超界限处理
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
	
    fin=fopen("排名3.txt","r");
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
