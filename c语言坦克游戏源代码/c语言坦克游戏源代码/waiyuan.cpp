# include "tanke.h"

/////////////////////////////////////////////////////外部
void JShengMing(int *j)
{
	setcolor(GREEN);
	settextstyle(0, 0, ("宋体"));
	char c2[20] = "自己生命值：";
	outtextxy(0, 20, c2);
	
	char c3[10] ;
	sprintf(c3, _T("%.1f"), 100* (60 - *j) / 60.0);
	outtextxy(90, 20, c3);
}

void DShengMing(int * d,int *k)
{
	setcolor(GREEN);
	settextstyle(0, 0, ("宋体"));
	char c2[20] = "敌人生命值：";
	outtextxy(0, 0, c2);
	
	char c3[10] ;
	sprintf(c3, _T("%.1f"), 100* (60 - *d) / 60.0);
	outtextxy(90, 0, c3);

	char c4[40] = "恭喜~! 现在起金币到2200有惊喜!";//胜利

	if ( *k >= 8000 )
			{
				setcolor(YELLOW);
				settextstyle(30, 0, ("宋体"));

				outtextxy(150, 0, c4);
			}
}

void Gold(int * gold)
{
	setcolor(GREEN);
	settextstyle(0, 0, ("宋体"));
	char c2[20] = "金币：";
	outtextxy(0, 40, c2);
	
	char c3[10] ;
	sprintf(c3, _T("%d"), *gold);
	outtextxy(40, 40, c3);
}

void start(void)
{
	initgraph(200, 130);

	TCHAR s1[10]="坦克大战";
	TCHAR s2[30]="按A 开始游戏  按B 退出游戏";
	TCHAR s3[30]="按W S A D控制方向";
	TCHAR s4[20]="按J 发射子弹";
	TCHAR s5[20]="按C 看攻略";
	
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
	TCHAR s1[20]="游戏攻略：";
	TCHAR s2[50]="再打坦克之前先吃法杖打掉白色砖块，";
	TCHAR s3[50]="这样敌坦克打白色就不能回血了，boss更应如此。";
	TCHAR s15[70]="吃盾牌的作用就是可以碾压对手";
	TCHAR s4[50]="打大坦克的时候，别和它对子弹这样会吃亏";
	TCHAR s5[70]="可以直接选择上去碾压它 注意：当血足够少的时候走开，";
	TCHAR s6[50]="用子弹打它这样才能得到钱，";
	TCHAR s7[70]="小boss可以反复刷，虽然挣不到钱，但复活次数更需要。";
	TCHAR s14[70]="吃手枪虽然速度快了但伤害会减少，但打绿boss时伤害反而增加";
	TCHAR s8[70]="血要多吃，肯定划算，钱少了好挣，复活少了，就难挣了。";
	TCHAR s9[50]="打终极boss时，记得要用大子弹打它伤害才能打出来。";
	TCHAR s10[90]="最后温馨提示：有块红砖比较可疑~";
	TCHAR s11[40]="最后：别想着跑后面去打终极Boss了";
	TCHAR s12[30]="因为你超过它会直接被秒。";
	TCHAR s13[30]="按A 开始游戏";
	
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

	printf("游戏秘籍：\n");
	printf("恭喜你通关了，\n");
	printf("告诉你些游戏作弊方法~！。\n");
	printf("当你一直按住子弹不松的话 ，还有直接控制 子弹功能哦~~\n\n");
	printf("哈哈 另外小技巧。打boss前 先把小坦克都压了\n");
	printf("只留一个，因为boss出来 基地就危险了\n");
	printf("还有 有的人 觉得花了600块的大子弹没伤害没用\n");
	printf("我只能说他的用法不对 不是一下一下的点，\n\n");
	printf("而是一直按着然后松开 那伤害高到 爆~！终极boss都打一半血！\n\n");
	printf("还有 就是 就算Gameover了 不算输，我还留了一手\n\n");
	printf("你把所有敌坦克都杀了 再按 Y\n\n");
	printf("这时候你的基地就复活了，\n\n");
	printf("~~嘘~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("另外：小坦克靠近基地时按Y它就乖乖回去了\n\n");
	printf("按B 游戏结束\n\n");	
	
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
	mciSendString("open sound\\坦克大战.mp3 alias mymusic", NULL, 0, NULL);
	mciSendString("play mymusic", NULL, 0, NULL);
	return;
}
void start_(void)
{
	music();
	srand( (unsigned)time( NULL ) );//随机种子
	setcolor(GREEN);
	setfillcolor(RED);
}
void win(pHongZhuan phongzhuan,bool *live2, bool *live3, bool *live4, bool *live5,bool *live6,bool *live7,
		 bool *exist_laowang, bool *exist1, 
		 bool *wexist1,bool *wexist2,bool *wexist3,bool *wexist8)
{
	char c[10] = "YOU WIN";
	settextcolor(YELLOW);
	settextstyle(80, 0, ("宋体"));
	outtextxy(190, 100, c);
	char c1[20] = "按Y键 进入下一关";
	settextstyle(30, 0, ("宋体"));
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
	settextstyle(80, 0, ("宋体"));
	outtextxy(170, 100, c);
	char c1[20] = "按I键 复活,金币-60";
	settextstyle(30, 0, ("宋体"));
	outtextxy(200, 200, c1);
	
	char c2[20] = "剩余复活次数：";
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
		if(MessageBox(NULL, "你确定要退出吗？",
			"提示", MB_YESNO) == IDYES)
			return true;
		
	}
	return false;
}
