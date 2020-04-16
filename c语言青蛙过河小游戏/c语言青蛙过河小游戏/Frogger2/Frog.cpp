#include "stdafx.h"
#define PI 3.1415926535
#define UNIT PI/180
#include<math.h>//旋转加速度用到x平方

void initFrog(FrogType *frog)
{
	frog->ch=-1;
	frog->x=WINDOW_LEN/2;
	frog->speed=8;
	frog->life=5;
	frog->passed=0;
	frog->state=NORMAL;//正常
	frog->coin=0;
	frog->score=0;
	frog->esc=0;


}
void resetFrog(FrogType *frog)
{
	frog->ch=-1;
	frog->x=WINDOW_LEN/2;
	frog->state=NORMAL;
	while(_kbhit()){_getch();}//清键盘缓存防止在死亡动画播放时按键。
}

void moveFrog(FrogType *frog,int ChannelSpeed[])
{
	if(frog->state==NORMAL){//死亡则不再允许操作，也不随着河飘走
		//与模板同步产生的移动
		if(frog->ch>-1&&frog->ch<CHANNEL_AMOUNT)
		{
			if(1==((frog->ch+1)%2))
			{frog->x-=ChannelSpeed[frog->ch];}
			else
			{frog->x+=ChannelSpeed[frog->ch];}
		}
		//通过键盘的移动

		if(GetAsyncKeyState('A'))//获取键盘状态而非事件。
		{
			if(!((-1==(frog->ch))&&((frog->x)-(frog->speed)<2)))//-1道左右出界保护
			{
				frog->x-=frog->speed;
			}
		}
		if(GetAsyncKeyState('D'))
		{
			if(!((-1==(frog->ch))&&((frog->x)+(frog->speed)>WINDOW_LEN-2)))//-1道左右出界保护
			{frog->x+=frog->speed;}

		}
		if(GetAsyncKeyState(27))
		{frog->esc=1;}

		int key;
		if(_kbhit())//当键盘按键事件时
		{
			key=_getch();
			switch(key)
			{
			case 'w':frog->ch+=1;
				break;
			case 's':
				{
					if((frog->ch)>-1)//下出界保护
					{
						frog->ch-=1;
					}
					break;
				}
			}
		}
	}
}





void frogOutRange(FrogType *frog,BoardType board[])//青蛙出界（或死亡、过关）判定
{
	int ch=frog->ch;

	if((frog->x)<0||(frog->x)>WINDOW_LEN)//1234道出界
	{frog->state=DEAD;}


	if((ch>-1)&&(ch<CHANNEL_AMOUNT))//在河道里
	{
		int fall=1;//落水判定
		int boardPosi;//木板左上角坐标
		for(int i=0;i<BOARD_AMOUNT;i++)//落水判定
		{
			boardPosi=board[ch].b[i].x;
			if(frog->x>boardPosi&&frog->x<boardPosi+BOARD_LEN)//在木板上
			{
				fall=0;
				break;
			}
		}
		if(1==fall)
		{
			frog->state=DEAD;

		}//落水则死亡
	}


	if(CHANNEL_AMOUNT==ch)//上岸判定,河道数量就是河道下标+1，实际上是最后一道
	{frog->state=PASSED;}//上岸


}

void excuteFrogFunc(FrogType *frog,int ChannelSpeed[],BoardType board[])//青蛙操作综合
{
	moveFrog(frog,ChannelSpeed);
	frogOutRange(frog,board);
}
void channelSpeedUp(int ChannelSpeed[])//河加速
{
	static int channel=0;
	if(4==channel){channel=0;}//重置

	ChannelSpeed[channel]+=2;//2是速度提升基数
	channel++;
}

void drawFrog(FrogType *frog,ImageType *img)
{
	int x1=frog->x;//右上角（判定用）坐标
	int y1=WINDOW_WID-(CHANNEL_WID/2)-(frog->ch+1)*CHANNEL_WID;

	int x2=x1-FROG_LEN/2;
	int y2=y1-FROG_WID/2;

	static double radian;//旋转用的弧度
	static double var=1;//变量,理解成log10x的x
	static double x=0;//变量，过关的sin函数用的

	static IMAGE f,fm;

	if(frog->state==NORMAL){
	//三元光栅，计算背景透明色
	putimage(x2,y2,&(img->frog0Mask),SRCAND);//掩码和背景按位与
	putimage(x2,y2,&(img->frog0),SRCPAINT);//图像与(掩码和背景按位与的结果)按位或
	var=1;//变量重置
	x=0;
	}
	else if(frog->state==DEAD){//旋转
			
		radian=UNIT*(pow(var,2.4));//增加量扩大的系数,用的是平方图像
		var+=0.2;

		rotateimage(&f,&img->frog0,radian,BLACK);//黑背景
		rotateimage(&fm,&img->frog0Mask,radian,WHITE);//掩码白背景

		putimage(x2,y2,&fm,SRCAND);//掩码和背景按位与
		putimage(x2,y2,&f,SRCPAINT);//图像与(掩码和背景按位与的结果)按位或
	}
	else if(frog->state==PASSED)//过关
	{
		radian=(PI/1.5)*sin(1.5*x);
		x+=PI/30;

		rotateimage(&f,&img->frog0,radian,BLACK);//黑背景
		rotateimage(&fm,&img->frog0Mask,radian,WHITE);//掩码白背景
		
		putimage(x2,y2,&fm,SRCAND);//掩码和背景按位与
		putimage(x2,y2,&f,SRCPAINT);//图像与(掩码和背景按位与的结果)按位或
	}

}


void excuteEvent(FrogType *frog,int ChannelSpeed[],ImageType *img)//执行过关或重置等EVENT
{
	int state=frog->state;
	switch(state)
	{
	case DEAD:
		{

			static int dTimer=0;//死亡时显示位置
			if(DEATH_DELAY==dTimer){
				
				resetFrog(frog);
				dTimer=0;
				frog->life-=1;
				frog->score-=10;
				int flag=1;//是否减速
				for(int i=0;i<CHANNEL_AMOUNT;i++)
				{
					if(1==ChannelSpeed[i])
					{
						flag=0;//有速度是1的河道
						break;
					}
				}
				if(flag)//减速
				{
					for(int i=0;i<CHANNEL_AMOUNT;i++)//死亡导致河流减速
					{ChannelSpeed[i]-=1;}
				}
			}
			else
			{dTimer++;}
			if(0==frog->life){frog->esc=1;}//生命为0则退出
			break;//switch case的break
		}
	case PASSED:
		{
			static int pTimer=0;//过关时显示位置
			if(PASS_DELAY==pTimer){
		
				pTimer=0;//计时器重置
				int CSSum=0;
				for(int i=0;i<CHANNEL_AMOUNT;i++)//河流速度总和
				{CSSum+=ChannelSpeed[i];}
				frog->passed+=1;
				frog->coin+=CSSum;
				frog->score+=(CSSum);
				channelSpeedUp(ChannelSpeed);
				resetFrog(frog);
			}
			else
			{pTimer++;}
			break;
		}
	}
}

