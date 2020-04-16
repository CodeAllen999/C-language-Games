/****************************************************/
/*	程 序 名: 拼图2_0								*/
/*	作　　者: Redman <Email: huangxionging@163.com>	*/
/*	编译环境: vc++ 6.0 && EasyX_v20130610(beta)		*/
/*  最后修改: 2013-06-23							*/
/****************************************************/

#ifndef picture_h
#define picture_h

// 加载头文件
#include <easyx.h>
#include <conio.h>
   #include <string>
#include <ctime>

using namespace std;

// 定义游戏的背景颜色
#define BgColor   LIGHTGREEN

#pragma comment(lib,"winmm.lib")                                        //加载库文件

// 游戏的关数
const int PassCount = 8;

// 游戏边框的大小
const int xLength = 953;
const int yLength = 453;
const int Width = 600;
const int Height = 450;

// 图片, 结构体, 保存图像
struct Image
{
    IMAGE image;                                                        // 保存图像
    int x;                                                              // 保存图像的 x 坐标
    int y;                                                              // 保存图像的 y 坐标
};

// 游戏的框架类
class GameFrame
{
    public:
        GameFrame();                                                    // 默认构造函数
        void DrawBackground();                                          // 绘制背景图像
        void StartMenu();                                               // 开始界面, 选择游戏难度
};

// 图像类
class Picture
{
	private:
		IMAGE img;														// 保存完整图像
		Image **image;                                                  // 保存切割图像
        int Control;                                                    // 控制值
        int Diffcult;                                                   // 难度值
        int Pass;                                                       // 记录当前的关数
		int LocalX;														// 记录鼠标的位置信息
		int LocalY;
        string String;													// 保存图片路径
		MOUSEMSG MouseMessage;											// 鼠标消息
		int singleWidth;												// 单幅图像的宽度
		int singleHeight;												// 单幅图像的高度
		int **Query;													// 查询数组, 快速定位图片
    public:
		Picture()														// 默认构造函数
		{
            Control = 0;
            Diffcult = 0;
            Pass = 0;
            String = "Res\\00.jpg";
			LocalX = 0;
			LocalY = 0;
			singleWidth = 0;
			singleHeight = 0;
		}
		void Run();														// 控制函数
		void SetGameDifficult();										// 设置游戏的难度
        void SetPicture();                                              // 设置图片
		void SetLocal();												// 设置位置
		void DrawRect();												// 绘制线条
		void PrintPicture();											// 将图像输出到屏幕
        void ProcessMouse();                                            // 处理鼠标消息, 实现移动的关键算法
		void ProcessPicture();											// 处理图像
		void IsPass();                                                  // 判断是否通关
};

#endif
