#include "stdafx.h"

void createBoard(BoardType board[],int channel,int interval)
{
	for(int i=0;i<BOARD_AMOUNT;i++)
	{
		if(0==board[channel].b[i].onMap)//���ڵ�ͼ��
		{

			if(1==(channel+1)%2)//��һ�͵�����,������
			{
				if(0==i)//��һ�� 
				{board[channel].b[i].x=board[channel].b[BOARD_AMOUNT-1].x+BOARD_LEN+interval;}
				else
				{board[channel].b[i].x=board[channel].b[i-1].x+BOARD_LEN+interval;}
			}
			else//�ڶ��͵��ĵ�,������
			{
				if(0==i)//��һ�� 
				{board[channel].b[i].x=board[channel].b[BOARD_AMOUNT-1].x-BOARD_LEN-interval;}
				else
				{board[channel].b[i].x=board[channel].b[i-1].x-BOARD_LEN-interval;}
			}
			board[channel].b[i].onMap=1;//ע��Ϊ�ڵ�ͼ��
			break;
		}
	}

}

void initBoard(BoardType b[])//��ÿ��ľ���������
{
	int ch;//�ӵ���
	int i=0;//ֻ������һ����
	for(ch=0;ch<CHANNEL_AMOUNT;ch++)
	{
		if(1==(ch+1)%2)//��һ�͵�����,������
		{
			b[ch].b[i].x=WINDOW_LEN+(i+1)*(BOARD_INTERVAL+BOARD_LEN);
			b[ch].b[i].onMap=1;
		}
		else//�ڶ��͵��ĵ�
		{
			b[ch].b[i].x=0-((i+1)*(BOARD_INTERVAL+BOARD_LEN));
			b[ch].b[i].onMap=1;
		}
	}

	//��ʼ������ľ��
	for(ch=0;ch<CHANNEL_AMOUNT;ch++)
	{
		if(1==(ch+1)%2)//��һ�͵�����,������
		{
			for(i=1;i<BOARD_AMOUNT;i++)
			{
				b[ch].b[i].x=b[ch].b[i-1].x+(BOARD_INTERVAL+BOARD_LEN);
				b[ch].b[i].onMap=1;
			}
		}
		else//�ڶ��͵��ĵ�
			for(i=1;i<BOARD_AMOUNT;i++)
			{
				b[ch].b[i].x=b[ch].b[i-1].x-(BOARD_INTERVAL+BOARD_LEN);
				b[ch].b[i].onMap=1;
			}
	}
}



void moveBoard(BoardType board[],int speed[],FrogType *frog)//�ƶ�ľ��
{
	if(frog->state!=DEAD){//������ʱ�ڼ䲻�ƶ�ľ��
		for(int ch=0;ch<CHANNEL_AMOUNT;ch++)
		{
			if(1==(ch+1)%2)
			{
				for(int i=0;i<BOARD_AMOUNT;i++)
				{
					board[ch].b[i].x-=speed[ch];//һ����
				}
			}
			else
			{
				for(int i=0;i<BOARD_AMOUNT;i++)
				{
					board[ch].b[i].x+=speed[ch];//���ĵ�
				}
			}
		}
	}
}

void boardOutRange(BoardType board[])//ľ������ж�
{
	for(int ch=0;ch<CHANNEL_AMOUNT;ch++)
	{
		if(1==(ch+1)%2)//һ����
		{
			for(int i=0;i<BOARD_AMOUNT;i++)
			{
				if(board[ch].b[i].x<0-BOARD_LEN)
				{board[ch].b[i].onMap=0;}
			}
		}
		else//���ĵ�
		{
			for(int i=0;i<BOARD_AMOUNT;i++)
			{
				if(board[ch].b[i].x>WINDOW_LEN)
				{board[ch].b[i].onMap=0;}
			}
		}
	}
}

void outRangeBoardReset(BoardType board[],int interval)//���ó����ľ��
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

void drawBoard(BoardType board[],ImageType *img)//��ľ��
{
	setfillstyle(BROWN);
	int x1,y1;
	for(int ch=0;ch<CHANNEL_AMOUNT;ch++)
	{
		for(int i=0;i<BOARD_AMOUNT;i++)
		{
			x1=board[ch].b[i].x;
			y1=(int)(STREAM_INIT_Y+STREAM_WID-CHANNEL_WID*(ch+1)+(CHANNEL_WID-BOARD_WID)/2);
			putimage(x1,y1,&(img->woodMask),SRCAND);//λ��
			putimage(x1,y1,&(img->wood),SRCPAINT);//λ��
			//����͸��\(^o^)/~
		}
	}
}


void excuteBoardFunc(BoardType board[],int ChannelSpeed[],FrogType *frog)
{
	moveBoard(board,ChannelSpeed,frog);//�ƶ�
	boardOutRange(board);//�����ж�
	outRangeBoardReset(board,BOARD_INTERVAL);//���ó����ľ��

}