#include "stdafx.h"
#include "string.h"
#include <stdlib.h>//_itoa������ת�ַ���

void printText(char str[],int value,int *line)//����ı�
{
	char strValue[6];//�м��������������.
	_itoa_s(value,strValue,10);//_itoa������ת�ַ���
	strcat_s(str,30,strValue);
	outtextxy(WORD_START_X,WORD_START_Y+(*line-1)*WORD_LINE_SPACING,str);
	(*line)++;
	//�����仰������ʾ������Ĭ��ʹ��UNICODE���롣�޸���Ŀ����(Alt+F7)���ַ�����Use Multi-Byte Character Set��
	//������VC6���롣����:http://www.easyx.cn/skills/View.aspx?id=35

}

void drawStateBar()
{

	setfillstyle(DARKGRAY);
	bar(WINDOW_LEN,0,WINDOW_LEN+STATE_BAR_LEN,STATE_BAR_WID);

}

void drawBarValue(FrogType *frog,int ChannelSpeed[])

{	
	int line=0;//����
	setcolor(LIGHTRED);
	char str[30];
	
	strcpy_s(str,"����ֵ��");
	printText(str,frog->life,&line);
	strcpy_s(str,"��ң�");
	printText(str,frog->coin,&line);
	strcpy_s(str,"���֣�");
	printText(str,frog->score,&line);
	strcpy_s(str,"�ɺӴ�����");
	printText(str,frog->passed,&line);
	int ch=0;
	strcpy_s(str,"�ӵ�һ�ٶȣ�");
	printText(str,ChannelSpeed[ch++],&line);
	strcpy_s(str,"�ӵ����ٶȣ�");
	printText(str,ChannelSpeed[ch++],&line);
	strcpy_s(str,"�ӵ����ٶȣ�");
	printText(str,ChannelSpeed[ch++],&line);
	strcpy_s(str,"�ӵ����ٶȣ�");
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
	getfont(&f);                          // ��ȡ��ǰ��������
	f.lfHeight = 24;                      // ��������߶�Ϊ 48�������оࣩ
	strcpy_s(f.lfFaceName, "��������");   // ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	f.lfWeight=500;						  // ��ϸ
	setfont(&f);                          // ����������ʽ

}