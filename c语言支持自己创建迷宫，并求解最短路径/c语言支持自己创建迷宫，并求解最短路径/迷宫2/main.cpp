
#include "labyrith.h"

/* 【自学去】网站收集 http://www.zixue7.com */

// 主函数
int main()
{
	FrameWindow frame;	// 建立图形界面
	frame.Run();		// 运行控制函数

	while(1)			// 主循环
	{
		frame.Run();	// 运行控制
	}

	getch();			// 当有按键的时候关闭图形
	closegraph();

	return 0;
}