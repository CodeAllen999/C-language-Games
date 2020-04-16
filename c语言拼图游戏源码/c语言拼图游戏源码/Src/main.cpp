
// 加载头文件
#include "../Inc/picture.h"

/* 【自学去】网站收集 http://www.zixue7.com */

int main()
{
	GameFrame gameframe;												// 建立游戏框架
	Picture picture;													// 建立图片框架
	gameframe.DrawBackground();											// 绘制背景
	gameframe.StartMenu();												// 绘制开始信息
	
	while (1)
	{
		picture.Run();													// 运行控制函数
		Sleep(10);														// 适当增加延时, 节约 CPU
	}
	getch();
	return 0;
}
