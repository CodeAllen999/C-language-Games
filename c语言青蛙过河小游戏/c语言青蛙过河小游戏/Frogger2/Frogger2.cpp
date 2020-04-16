// Frogger2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "funcdef.h"//�Զ���ĺ���

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */


int _tmain(int argc, _TCHAR* argv[])
{


	//ͼ�����
	ImageType img;
	initImage(&img);//����ͼ��
	int ChannelSpeed[CHANNEL_AMOUNT];//={2,2,2,2};//�ӵ�ˮ���ٶ�
	BoardType board[CHANNEL_AMOUNT];//ľ������
	FrogType frog;//���ܶ���

	initgraph(WINDOW_LEN+STATE_BAR_LEN,WINDOW_WID);//��ʼ��ͼ�ν���



	while(initWelcome(&img))//��ӭ����
	{

		//��ʼ��Ϸ
		for(int i=0;i<CHANNEL_AMOUNT;i++){
		ChannelSpeed[i]=2;//�ӵ�ˮ���ٶ�����
		}
		initBoard(board);
		initFrog(&frog);
		initFont();
		while(!frog.esc)
		{

			BeginBatchDraw();//������ͼ��ʼ
			//��ľ��Ĳ���
			excuteBoardFunc(board,ChannelSpeed,&frog);
			//�����ܵĲ���
			excuteFrogFunc(&frog,ChannelSpeed,board);
			//״̬��
			excuteStateBarFunc(&frog,ChannelSpeed);
			//�ؿ��¼�
			excuteEvent(&frog,ChannelSpeed,&img);


			drawStream(&img);//����
			drawBackground(&img);//������
			drawBoard(board,&img);//����
			drawFrog(&frog,&img);//������
			excuteStateBarFunc(&frog,ChannelSpeed);//״̬��
			FlushBatchDraw();//������ͼ���
			Sleep(TICK);
		}
		EndBatchDraw();
		
	}
	
	closegraph();

	return 0;
}

void initImage(ImageType *img)//����ͼƬ
{
	loadimage(&(img->frog0),"res\\frog.jpg",FROG_LEN,FROG_WID,true);
	loadimage(&(img->frog0Mask),"res\\frogMask.gif",FROG_LEN,FROG_WID,true);
	loadimage(&(img->wood),"res\\wood.jpg",BOARD_LEN,int(BOARD_WID),true);
	loadimage(&(img->woodMask),"res\\woodMask.gif",BOARD_LEN,int(BOARD_WID),true);
	loadimage(&(img->stream),"res\\stream.jpg",WINDOW_LEN,WINDOW_WID,true);
	loadimage(&(img->grass1),"res\\grass.jpg",WINDOW_LEN,STREAM_INIT_Y,true);
	loadimage(&(img->grass2),"res\\grass.jpg",WINDOW_LEN,WINDOW_WID-(STREAM_INIT_Y+STREAM_WID),true);
	loadimage(&(img->welcome),"res\\welcome.jpg",WINDOW_LEN+STATE_BAR_LEN,WINDOW_WID,true);
}