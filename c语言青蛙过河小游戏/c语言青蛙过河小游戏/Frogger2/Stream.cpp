#include "stdafx.h"



void drawStream(ImageType *img)//»­ºÓ
{
	setfillstyle(LIGHTBLUE);//Ìî³äÉ«£ºÀ¶
	int x1=0;
	int y1=STREAM_INIT_Y;
	putimage(x1,y1,&(img->stream));
}

void drawBackground(ImageType *img)
{
	setfillstyle(LIGHTGREEN); 
	putimage(0,0,&(img->grass1));
	putimage(0,STREAM_INIT_Y+STREAM_WID,&(img->grass2));
}