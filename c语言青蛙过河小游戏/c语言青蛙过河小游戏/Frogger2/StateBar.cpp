#include "stdafx.h"
#include "string.h"
#include <stdlib.h>//_itoa，整形转字符串

void printText(char str[],int value,int *line)//输出文本
{
	char strValue[6];//中间变量，放数字用.
	_itoa_s(value,strValue,10);//_itoa，整型转字符串
	strcat_s(str,30,strValue);
	outtextxy(WORD_START_X,WORD_START_Y+(*line-1)*WORD_LINE_SPACING,str);
	(*line)++;
	//如果这句话出错，表示编译器默认使用UNICODE编码。修改项目属性(Alt+F7)，字符集：Use Multi-Byte Character Set。
	//或者用VC6编译。详情:http://www.easyx.cn/skills/View.aspx?id=35

}

void drawStateBar()
{

	setfillstyle(DARKGRAY);
	bar(WINDOW_LEN,0,WINDOW_LEN+STATE_BAR_LEN,STATE_BAR_WID);

}

void drawBarValue(FrogType *frog,int ChannelSpeed[])

{	
	int line=0;//行数
	setcolor(LIGHTRED);
	char str[30];
	
	strcpy_s(str,"生命值：");
	printText(str,frog->life,&line);
	strcpy_s(str,"金币：");
	printText(str,frog->coin,&line);
	strcpy_s(str,"积分：");
	printText(str,frog->score,&line);
	strcpy_s(str,"渡河次数：");
	printText(str,frog->passed,&line);
	int ch=0;
	strcpy_s(str,"河道一速度：");
	printText(str,ChannelSpeed[ch++],&line);
	strcpy_s(str,"河道二速度：");
	printText(str,ChannelSpeed[ch++],&line);
	strcpy_s(str,"河道三速度：");
	printText(str,ChannelSpeed[ch++],&line);
	strcpy_s(str,"河道四速度：");
	printText(str,ChannelSpeed[ch++],&line);

}

void excuteStateBarFunc(FrogType *frog,int ChannelSpeed[])
{
	drawStateBar();
	drawBarValue(frog,ChannelSpeed);
}

void initFont()
{
	setbkmode(TRANSPARENT);
	LOGFONT f;
	getfont(&f);                          // 获取当前字体设置
	f.lfHeight = 24;                      // 设置字体高度为 48（包含行距）
	strcpy_s(f.lfFaceName, "华文中宋");   // 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	f.lfWeight=500;						  // 粗细
	setfont(&f);                          // 设置字体样式

}