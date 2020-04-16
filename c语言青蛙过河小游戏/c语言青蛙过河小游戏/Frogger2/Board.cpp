#include "stdafx.h"

void createBoard(BoardType board[],int channel,int interval)
{
	for(int i=0;i<BOARD_AMOUNT;i++)
	{
		if(0==board[channel].b[i].onMap)//不在地图上
		{

			if(1==(channel+1)%2)//第一和第三道,从右来
			{
				if(0==i)//第一个 
				{board[channel].b[i].x=board[channel].b[BOARD_AMOUNT-1].x+BOARD_LEN+interval;}
				else
				{board[channel].b[i].x=board[channel].b[i-1].x+BOARD_LEN+interval;}
			}
			else//第二和第四道,从左来
			{
				if(0==i)//第一个 
				{board[channel].b[i].x=board[channel].b[BOARD_AMOUNT-1].x-BOARD_LEN-interval;}
				else
				{board[channel].b[i].x=board[channel].b[i-1].x-BOARD_LEN-interval;}
			}
			board[channel].b[i].onMap=1;//注册为在地图上
			break;
		}
	}

}

void initBoard(BoardType b[])//给每个木版分配坐标
{
	int ch;//河道数
	int i=0;//只创建第一条船
	for(ch=0;ch<CHANNEL_AMOUNT;ch++)
	{
		if(1==(ch+1)%2)//第一和第三道,从右来
		{
			b[ch].b[i].x=WINDOW_LEN+(i+1)*(BOARD_INTERVAL+BOARD_LEN);
			b[ch].b[i].onMap=1;
		}
		else//第二和第四道
		{
			b[ch].b[i].x=0-((i+1)*(BOARD_INTERVAL+BOARD_LEN));
			b[ch].b[i].onMap=1;
		}
	}

	//初始化其他木板
	for(ch=0;ch<CHANNEL_AMOUNT;ch++)
	{
		if(1==(ch+1)%2)//第一和第三道,从右来
		{
			for(i=1;i<BOARD_AMOUNT;i++)
			{
				b[ch].b[i].x=b[ch].b[i-1].x+(BOARD_INTERVAL+BOARD_LEN);
				b[ch].b[i].onMap=1;
			}
		}
		else//第二和第四道
			for(i=1;i<BOARD_AMOUNT;i++)
			{
				b[ch].b[i].x=b[ch].b[i-1].x-(BOARD_INTERVAL+BOARD_LEN);
				b[ch].b[i].onMap=1;
			}
	}
}



void moveBoard(BoardType board[],int speed[],FrogType *frog)//移动木板
{
	if(frog->state!=DEAD){//死亡延时期间不移动木板
		for(int ch=0;ch<CHANNEL_AMOUNT;ch++)
		{
			if(1==(ch+1)%2)
			{
				for(int i=0;i<BOARD_AMOUNT;i++)
				{
					board[ch].b[i].x-=speed[ch];//一三道
				}
			}
			else
			{
				for(int i=0;i<BOARD_AMOUNT;i++)
				{
					board[ch].b[i].x+=speed[ch];//二四道
				}
			}
		}
	}
}

void boardOutRange(BoardType board[])//木板出界判定
{
	for(int ch=0;ch<CHANNEL_AMOUNT;ch++)
	{
		if(1==(ch+1)%2)//一三道
		{
			for(int i=0;i<BOARD_AMOUNT;i++)
			{
				if(board[ch].b[i].x<0-BOARD_LEN)
				{board[ch].b[i].onMap=0;}
			}
		}
		else//二四道
		{
			for(int i=0;i<BOARD_AMOUNT;i++)
			{
				if(board[ch].b[i].x>WINDOW_LEN)
				{board[ch].b[i].onMap=0;}
			}
		}
	}
}

void outRangeBoardReset(BoardType board[],int interval)//重置出界的木板
{
	for(int ch=0;ch<CHANNEL_AMOUNT;ch++)
	{
		for(int i=0;i<BOARD_AMOUNT;i++)
		{
			if(0==board[ch].b[i].onMap)
			{
				createBoard(board,ch,interval);
			}
		}
	}
}

void drawBoard(BoardType board[],ImageType *img)//画木板
{
	setfillstyle(BROWN);
	int x1,y1;
	for(int ch=0;ch<CHANNEL_AMOUNT;ch++)
	{
		for(int i=0;i<BOARD_AMOUNT;i++)
		{
			x1=board[ch].b[i].x;
			y1=(int)(STREAM_INIT_Y+STREAM_WID-CHANNEL_WID*(ch+1)+(CHANNEL_WID-BOARD_WID)/2);
			putimage(x1,y1,&(img->woodMask),SRCAND);//位与
			putimage(x1,y1,&(img->wood),SRCPAINT);//位或
			//背景透明\(^o^)/~
		}
	}
}


void excuteBoardFunc(BoardType board[],int ChannelSpeed[],FrogType *frog)
{
	moveBoard(board,ChannelSpeed,frog);//移动
	boardOutRange(board);//出界判定
	outRangeBoardReset(board,BOARD_INTERVAL);//重置出界的木板

}