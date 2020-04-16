/********************************************
 * 程序名称: 万年历                         *
 * 编译环境: vc++6.0 + EasyX_20120603(beta) *
 * 作    者: Redman <huangxionging@163.com> *
 * 最后修改: 2012-09-19                     *
 ********************************************/

#ifndef ymd_h
#define ymd_h


#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <string>
#include <time.h>

using namespace std;

struct Time										// 定义了一个结构体
{
	int year, month;							// 年月
	int yearFlag, monthFlag;					// 用来标记年月是否改变
};


void Init();									// 绘制初始图形界面
void DrawWeek();								// 绘制星期
bool CalYear(int year);							// 判断是闰年还是平年
void DrawDate(Time &tm);						// 绘制当月日历
void CalDate(Time& tm, char x);					// 计算现在的年月
bool DateFlag(int y1, int y2, int m1, int m2);	// 判断年份和月份是否更改


extern char *Week[];							// 声明 Week 字符串数组
extern int x1[13];								// 声明 x1 整数数组
extern int x2[13];								// 声明 x2 整数数组
extern char num[3];								// 声明 num 字符串
extern char xy1[5];								// 声明 xy 字符串

#endif
