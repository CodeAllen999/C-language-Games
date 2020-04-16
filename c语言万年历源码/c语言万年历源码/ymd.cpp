#include "ymd.h"

int x1[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};						// �����ÿ������
int x2[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};						// ƽ���ÿ������

char *Week[] = {"������", "����һ", "���ڶ�", "������", "������", "������", "������"};	// ��������
char num[3];																			// ���� num �ַ���
char xy[30];																				// ���� xy �ַ���,

// ��ʼ��
void Init()																			   
{
	// ��ʼ����ͼ����
	initgraph(640, 640);
	setbkcolor(0x0055ff);
	cleardevice();
}

// ��������
void DrawWeek()																		   
{
	char str[7];
	int x1 = 0;

	for (int i = 0; i < 7; i++)
	{
		sprintf(str, "%s", Week[i]);
		outtextxy(120 + x1, 100, str);
		x1 += 60;
	}
}

// �������ڵ�����
void CalDate(Time& tm, char x)														   
{
	switch(x)
	{
		case 'q':	tm.year++;				break;
		case 'w':	tm.year += 10;			break;
		case 'e':	tm.year += 100;			break;
		case 'r':	tm.year += 1000;		break;
		case 't':	if (tm.month < 12)		tm.month++;			break;
		case 'a':	if (tm.year > 0)		tm.year--;			break;
		case 's':	if (tm.year >= 10)		tm.year -= 10;		break;
		case 'd':	if (tm.year >= 100)		tm.year -= 100;		break;
		case 'f':	if (tm.year >= 1000)	tm.year -= 1000;	break;
		case 'g':	if (tm.month > 1)		tm.month--;			break;
	} 
}

// �ж���ݺ��·��Ƿ����
bool DateFlag(int y1, int y2, int m1, int m2)										   
{
	return (y1 != y2 || m1 != m2);
}

// �ж������껹��ƽ��
bool CalYear(int year)														   
{ 
	return ((year % 4 == 0 && year % 10 != 0) || year % 400 == 0);
} 

// ���Ƶ�������
void DrawDate(Time &tm)																	
{
	int y = 0, z = 0;
	int s;

	sprintf(xy, "���ǹ�Ԫ %d �� %d �µ�����", tm.year, tm.month);
	outtextxy(20, 50, xy);

	s = (5 + (tm.year + 1) + (tm.year - 1 ) / 4 - (tm.year - 1) 
		/ 100 + (tm.year - 1) / 400) % 7;

	if (CalYear(tm.year))                       // �����ǰ���������
	{
		for (int i = 1; i < tm.month; i++)
		{
			s = (x1[i] + s) % 7;
		}

		if (s / 6 != 1)
		{
			y = (s + 1) * 60;
		}

		for (i = 1; i <= x1[tm.month]; i++)
		{ 
			sprintf(num, " %d ", i);
			outtextxy(140 + y, 150 + z, num);
			y += 60;
			if ((i + s) % 7 == 6 && (i + s) >= 6)
			{
				z += 85;
				y = 0;
			}
		} 
	}
	else									 // �����ǰ��ݲ�������
	{
		for (int i = 1; i < tm.month; i++)
		{
			s = (x2[i] + s) % 7;
		}

		if (s / 6 != 1)
		{
			y = (s + 1) * 60;
		}

		for (i = 1; i <= x2[tm.month]; i++)
		{ 
			sprintf(num, " %d ", i);
			outtextxy(140 + y, 150 + z, num);
			y += 60;
			if ((i + s) % 7 == 6)
			{
				z += 85;
				y = 0;
			}			
		} 
	}
}