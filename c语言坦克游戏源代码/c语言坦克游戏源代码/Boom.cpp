
# include "tanke.h"
/////////////////////////////////////////////////效果
bool DBoom(int (*x)[2][3], int * x_, int *y_, int *d,int *gold)
{
	int i;//循环用
	IMAGE imgBoom;
	loadimage(&imgBoom, _T("res\\explode1.bmp"));
	for (i=1; i<39; i++)//被击中爆炸
		if (x[i][0][0] <= *x_+48 && x[i][0][0] >= *x_ + 20 && x[i][1][0] <= *y_ + 48 && x[i][1][0] >= *y_ + 20)
		{

			if	 (*d % 10 ==  0)
				x[i][0][0] = 0;

			putimage(*x_, *y_, 28, 28, &imgBoom,0 ,0 );
			(*d)++;
			if (*d >= 60)
			{
				mciSendString("open sound//boom.mp3 alias mymusic_1", NULL, 0, NULL);
				mciSendString("play mymusic_1", NULL, 0, NULL);
		
				*d = 0;
				*gold += 10;
				return false;
			}
			mciSendString("close mymusic_1", NULL, 0, NULL);
		}	
		
		return true;
		
}

bool QZBoom(int (*x)[2][3], int * x_, int *y_)//强制子弹消失，物体爆炸。
{
	int i;//循环用
	for (i=1; i<39; i++)//被击中爆炸
		if (x[i][0][0] <= *x_+52 && x[i][0][0] >= *x_ + 20 && x[i][1][0] <= *y_ + 52 && x[i][1][0] >= *y_ + 20)
		{	
			x[i][0][0] = 0;
			
			return false;
		}			
		
		return true;
}


bool DBoomBig(int (*x)[2][3], int * x_, int *y_, int *d)
{
	int i;//循环用
	IMAGE imgBoom;
	loadimage(&imgBoom,_T("res\\explode2.bmp"));
	for (i=1; i<39; i++)//被击中爆炸
		if (x[i][0][0] <= *x_+52 && x[i][0][0] >= *x_ + 20 && x[i][1][0] <= *y_ + 52 && x[i][1][0] >= *y_ + 20)
		{
			putimage(*x_ - 18, *y_ -18, 64, 64, &imgBoom,0 ,0 );
			(*d)++;
			
			if	 (*d % 10 ==  0)
				x[i][0][0] = 0;
			
			
		if (*d >= 60)
			{
				mciSendString("open sound//boom.mp3 alias mymusic_1", NULL, 0, NULL);
				mciSendString("play mymusic_1", NULL, 0, NULL);
	
				*d = 0;
				return false;
			}
			mciSendString("close mymusic_1", NULL, 0, NULL);
		}	
		
		return true;
		
}
bool DBossBoomBig(int (*x)[2][3], int * x_, int *y_, int *k, int*zhidan)
{
	int i;//循环用
	IMAGE imgBoom;
	loadimage(&imgBoom,_T("res\\explode2.bmp"));
	for (i=1; i<39; i++)//被击中爆炸
		if (x[i][0][0] <= *x_+70 && x[i][0][0] >= *x_ + 20 && x[i][1][0] <= *y_ + 70 && x[i][1][0] >= *y_ + 20)
		{
			putimage(*x_ - 18, *y_ -18, 64, 64, &imgBoom,0 ,0 );
			
			if (*zhidan == 5)
				(*k)++;
			
			if (*zhidan == 15)
				(*k) += 10;
			
			if (*k >= 8000)
			{
				x[i][0][0] = 0;
				
				keybd_event(89,0,0,0);
				keybd_event(89,0,KEYEVENTF_KEYUP,0);

				return false;
			}
			
		}
		setcolor(GREEN);
		settextstyle(0, 0, ("宋体"));
		char c2[20] = "BOSS生命值：";
		outtextxy(220, 0, c2);
		
		char c3[10] ;
		sprintf(c3, _T("%.1f"),1000*(8000 - *k)/8000.0 );
		outtextxy(320, 0, c3);

		return true;

}
bool DBossBoomSmall(int (*x)[2][3], int * x_, int *y_, int *l, int*sd)
{
	int i;//循环用
	IMAGE imgBoom;
	loadimage(&imgBoom, _T("res\\explode2.bmp"));
	for (i=1; i<39; i++)//被击中爆炸
		if (x[i][0][0] <= *x_+48 && x[i][0][0] >= *x_ + 20 && x[i][1][0] <= *y_ + 48 && x[i][1][0] >= *y_ + 20)
		{
			putimage(*x_ - 18, *y_ -18, 64, 64, &imgBoom,0 ,0 );
			
			if (*sd == 2)
				(*l)++;
			
			if (*sd == 1)
				(*l) += 10;
			
			if (*l >= 1000)
			{
				x[i][0][0] = 0;
				*l = 0;
				return false;
			}
			
		}
		setcolor(GREEN);
		settextstyle(0, 0, ("宋体"));
		char c2[20] = "BOSS生命值：";
		outtextxy(220, 0, c2);
		
		char c3[10] ;
		sprintf(c3, _T("%.1f"),1000*(1000 - *l)/1000.0 );
		outtextxy(320, 0, c3);
		return true;
}