/********************************************
 * ��������: ������                         *
 * ���뻷��: vc++6.0 + EasyX_20120603(beta) *
 * ��    ��: Redman <huangxionging@163.com> *
 * ����޸�: 2012-09-19                     *
 ********************************************/

#ifndef ymd_h
#define ymd_h


#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <string>
#include <time.h>

using namespace std;

struct Time										// ������һ���ṹ��
{
	int year, month;							// ����
	int yearFlag, monthFlag;					// ������������Ƿ�ı�
};


void Init();									// ���Ƴ�ʼͼ�ν���
void DrawWeek();								// ��������
bool CalYear(int year);							// �ж������껹��ƽ��
void DrawDate(Time &tm);						// ���Ƶ�������
void CalDate(Time& tm, char x);					// �������ڵ�����
bool DateFlag(int y1, int y2, int m1, int m2);	// �ж���ݺ��·��Ƿ����


extern char *Week[];							// ���� Week �ַ�������
extern int x1[13];								// ���� x1 ��������
extern int x2[13];								// ���� x2 ��������
extern char num[3];								// ���� num �ַ���
extern char xy1[5];								// ���� xy �ַ���

#endif
