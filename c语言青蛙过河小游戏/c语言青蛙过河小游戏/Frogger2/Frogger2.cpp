// Frogger2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "funcdef.h"//自定义的函数

/* 【自学去】网站收集 http://www.zixue7.com */


int _tmain(int argc, _TCHAR* argv[])
{


	//图像对象
	ImageType img;
	initImage(&img);//加载图像
	int ChannelSpeed[CHANNEL_AMOUNT];//={2,2,2,2};//河道水流速度
	BoardType board[CHANNEL_AMOUNT];//木板类型
	FrogType frog;//青蛙对象

	initgraph(WINDOW_LEN+STATE_BAR_LEN,WINDOW_WID);//初始化图形界面



	while(initWelcome(&img))//欢迎界面
	{

		//开始游戏
		for(int i=0;i<CHANNEL_AMOUNT;i++){
		ChannelSpeed[i]=2;//河道水流速度重置
		}
		initBoard(board);
		initFrog(&frog);
		initFont();
		while(!frog.esc)
		{

			BeginBatchDraw();//批量绘图开始
			//对木板的操作
			excuteBoardFunc(board,ChannelSpeed,&frog);
			//对青蛙的操作
			excuteFrogFunc(&frog,ChannelSpeed,board);
			//状态栏
			excuteStateBarFunc(&frog,ChannelSpeed);
			//关卡事件
			excuteEvent(&frog,ChannelSpeed,&img);


			drawStream(&img);//画河
			drawBackground(&img);//画背景
			drawBoard(board,&img);//画船
			drawFrog(&frog,&img);//画青蛙
			excuteStateBarFunc(&frog,ChannelSpeed);//状态栏
			FlushBatchDraw();//批量绘图输出
			Sleep(TICK);
		}
		EndBatchDraw();
		
	}
	
	closegraph();

	return 0;
}

void initImage(ImageType *img)//加载图片
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