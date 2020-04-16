/* 【自学去】网站收集 http://www.zixue7.com */


#include "ymd.h"

// 主函数
int main()                                                      
{
	char add;
	tm *t;										// 在 time.h 中有定义为一个结构体，用法见 MSDN
	time_t Clock;								// 在 time.h 中有定义为一个结构体，用法见 MSDN
	Time tm;									// 结构体 tm

	// 初始化
	Init();															

	// 获取结构体 Clock 的参数
	time(&Clock);	

	// 获取时间
	t = localtime(&Clock);											

	tm.year = t->tm_year + 1900;				// 当前系统时间所处年份, 至于为什么加 1900, 见 MSDN
	tm.month = t->tm_mon + 1;					// 获取系统时间所在月份, 至于为什么加 1, 见 MSDN
	tm.yearFlag = tm.year;						// 标记当前年份份
	tm.monthFlag = tm.month;					// 标记当前月份

	// 绘制星期
	DrawWeek();									
	
	// 绘制当月的日历
	DrawDate(tm);													

	// 主循环
	while(1)														
	{
		// 从键盘获取按键
		add = getch();												

		// 计算现在的年月
		CalDate(tm, add);											

		// 判断年月是否更改, 改则进入 if 语句
		if (DateFlag(tm.year, tm.yearFlag, tm.month, tm.monthFlag))  
		{
			// 清除屏幕
			cleardevice();
			
			// 从新绘制星期
			DrawWeek();
			
			// 从新绘制当月日历
			DrawDate(tm);

			tm.yearFlag = tm.year;				// 更改新标记年份
			tm.monthFlag = tm.month;			// 更改新标记月份
		}
	}

	// 返回
	return 0;
}