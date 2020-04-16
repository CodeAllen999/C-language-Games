/* 【自学去】网站收集 http://www.zixue7.com */

// 加载头文件
#include "../Inc/picture.h"


// 游戏框架类的默认构造函数
GameFrame::GameFrame()
{
    initgraph (xLength, yLength);
    setbkcolor (BgColor);
    cleardevice ();
}

// 绘制背景图像
void GameFrame::DrawBackground()
{
	float H, S, L;														// 定义 HSL 颜色模型的 3 个变量

	H = 70;
	S = -2.2555f;														// 饱和度
	L = 0.525617f;			
	BeginBatchDraw();
	for(int i = 0; i != yLength; ++i)									// 绘制游戏背景颜色
	{
		L += 0.000000085f;
		S -= 0.0013f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, i, xLength, i);
	}
	EndBatchDraw();
}

// 开始菜单
void GameFrame::StartMenu()
{
	setbkmode(TRANSPARENT);												// 设置背景为透明
    settextcolor(BLUE);													// 设置文字颜色为蓝色

	settextstyle(23, 0, _T("华文行楷"));								// 设置字体信息
	outtextxy(700, 25, _T("游戏作者: Redman"));							// 绘制游戏作者的名字

    settextstyle(30, 0, _T("华文行楷"));								// 设置字体的大小
    outtextxy(230, 85, _T("欢迎来到拼图游戏的世界"));                   // 绘制提示信息
	settextstyle(23, 0, _T("华文行楷"));								// 设置字体信息
	outtextxy(300, 170, _T("选择游戏的难度:"));							// 绘制提示信息
	outtextxy(300, 210, _T("<A> 一般"));
	outtextxy(300, 270, _T("<B> 中等"));
	outtextxy(300, 330, _T("<C> 较难"));

	setlinestyle(PS_SOLID, 5, NULL);
    setlinecolor(BLUE);													// 设置线条颜色为蓝色
	rectangle(200,50,600,400);
	line(200, 150, 600, 150);
}

// 控制函数
void Picture::Run()
{
	switch (Control)
	{
		case 0:
		{
			SetGameDifficult();											// 设置游戏难度
			break;
		}
		case 1:
		{
			SetPicture();												// 设置图像
			DrawRect();													// 绘制矩形
			break;
		}
		case 2:
		{
			PrintPicture();												// 将图像输出到屏幕上
			break;
		}
		case 3:
		{
			ProcessMouse();												// 处理鼠标消息
			IsPass();													// 是否通关
			break;
		}
		default:
		{
		   break;
		}
	}
}

// 设置游戏的难度
void Picture::SetGameDifficult()
{
    char num;                                                           // 读取键盘的键值

    while (1)
    {
        if (kbhit())
        {
			mciSendString("play  Res\\key.wav", NULL, 0, NULL);
            num = getch();                                              // 从键盘获取信息
            
            switch (num)
            {
				case 'a':Diffcult = 3;break;
                case 'b':Diffcult = 4;break;
                case 'c':Diffcult = 5;break;
                default:Diffcult = 0;
            }
        }

		// 如果游戏难度已获取则退出循环
        if (Diffcult != 0)
        {
            Control = 1;
            break;
        }
    }
}

// 设置图片
void Picture::SetPicture()
{
    loadimage(&img, String.c_str(), Width, Height);						// 加载图像

	singleWidth = Width / Diffcult;										// 单个切割图像的长度
	singleHeight = Height / Diffcult;

    image = new Image *[Diffcult];                                      // 分配空间
	Query = new int *[Diffcult];										// 给查询数组分配空间

    SetWorkingImage(&img);                                              // 设置绘图设备

	// 切割图像, 设置其位置
	for (int i = 0; i < Diffcult; ++i)
	{
		image[i] = new Image[Diffcult];
		Query[i] = new int [Diffcult];
        for (int j = 0; j < Diffcult; ++j)
		{
			image[i][j].x = j;
			image[i][j].y = i;
			Query[i][j] = i * Diffcult + j;
			if (i != Diffcult - 1 || j != Diffcult - 1)
			{ 
				getimage(&(image[i][j].image), j * singleWidth,\
				i * singleHeight, singleWidth - 3, singleHeight - 3);
			} 
		}
	}

    SetWorkingImage();                                                  // 恢复默认绘图设备

	
	// 从正确的结果出发来打散图片, 这样能保证结果绝对有解
	SetLocal();

    // 对最切割成小图片后的最后一张进行处理
	image[Diffcult - 1][Diffcult - 1].image.Resize(singleWidth - 3, singleHeight - 3);
	SetWorkingImage(&(image[Diffcult - 1][Diffcult -1].image));         // 设置绘图设备
	float H, S, L;														// 定义 HSL 颜色模型的 3 个变量
	H = 50;																// 色相
	S = -3.2555f;														// 饱和度
	L = 0.525617f;				
	for(i = 0; i != singleHeight; ++i)									// 将线条绘制到图像中去
	{
		L += 0.000000085f;
		S -= 0.0015f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, i, singleWidth, i);
	}
	SetWorkingImage();
	Control = 2;
}

// 将图像输出到屏幕
void Picture::PrintPicture()
{
	// 将切割后的图像加载到屏幕中去
    for (int i = 0; i < Diffcult; ++i)
	{
        for (int j = 0; j < Diffcult; ++j)
		{
			putimage(image[i][j].x * singleWidth + 3,\
			image[i][j].y * singleHeight + 3, &(image[i][j].image));
		}
	}
	Resize(&img, 300, 225);
	loadimage(&img, String.c_str(), 300, 225);                          // 加载完整图像
	setbkmode(TRANSPARENT);
	settextstyle(23, 0, _T("华文行楷"));								// 设置字体信息
	settextcolor(BLUE);
	outtextxy(700, 25, _T("游戏作者: Redman"));							// 绘制游戏作者的名字
	outtextxy(740, 70, _T("完整图像"));
	putimage(630, 100, &img);
	Control = 3;
}

// 绘制线条
void Picture::DrawRect()
{
	setlinecolor(BgColor);												// 设置边框颜色
	setfillcolor(BgColor);												// 设置填充颜色
	POINT points[] = {{0, 0}, {0, 453}, {600, 453}, {600,0}};
	fillpolygon(points, 4);
	Control = 2;
}

// 处理鼠标信息
void Picture::ProcessMouse()
{
	int ImageX = image[Diffcult - 1][Diffcult - 1].x;
	int ImageY = image[Diffcult - 1][Diffcult - 1].y;

	// 如果鼠标按下
	while (MouseHit())
	{
		MouseMessage = GetMouseMsg();									// 获取鼠标消息

		switch (MouseMessage.uMsg)
		{
			case WM_LBUTTONDOWN:										// 鼠标左键按下
			{
				mciSendString("play  Res\\key.wav", NULL, 0, NULL);		// 播放声音
				LocalX = MouseMessage.x / singleWidth;					// 获取鼠标的所在的图像的特征
				LocalY = MouseMessage.y / singleHeight;
				break;
			}
			default:
			{
				break;
			}
		}

		// 在空图像四周才会处理该鼠标信息
		if (LocalX == ImageX)
		{
			if (LocalY == ImageY - 1 || LocalY == ImageY + 1)
			{
				ProcessPicture();
			}
		} 
		else if (LocalY == ImageY)
		{
			if (LocalX == ImageX - 1 || LocalX == ImageX + 1)
			{
				ProcessPicture();
			}
		}
	}
}

void Picture::ProcessPicture()
{
	int num = 0;
	int Diff = Diffcult -1;
	int x1, y1;

	num = Query[LocalY][LocalX];										// 定位鼠标处所在的图片
	y1 = num / Diffcult;
	x1 = num % Diffcult;
	
	// 修改查询数组的值
	Query[image[Diff][Diff].y][image[Diff][Diff].x] = num;
	Query[LocalY][LocalX] = Diffcult * Diffcult - 1;

	// 交换图片的位置
	image[y1][x1].x = image[Diff][Diff].x;
	image[y1][x1].y = image[Diff][Diff].y;
	image[Diff][Diff].x = LocalX;
	image[Diff][Diff].y = LocalY;
	
	// 放置图片
	putimage(image[y1][x1].x * singleWidth + 3, image[y1][x1].y * singleHeight + 3, &(image[y1][x1].image));
	putimage(LocalX * singleWidth + 3, LocalY * singleHeight + 3,&(image[Diff][Diff].image));
}

// 判断是否通关
void Picture::IsPass()
{
	int flag = 0;
	char str[20];
	setbkmode(OPAQUE);
	sprintf(str, "第 %d / %d 关", Pass + 1, PassCount);
	settextstyle(23, 0, _T("华文行楷"));								// 设置字体信息
	outtextxy(700, 350, _T("当前状态: 游戏中"));						// 输出游戏状态
	outtextxy(730, 400, str);											// 输出当前的关数

	for (int i = 0; i < Diffcult; ++i)
	{
		for (int j = 0; j < Diffcult; ++j)
		{
			if (image[i][j].x == j && image[i][j].y == i)
			{
				++flag;
			}
		}
	}

	// 通关条件
	if (flag == Diffcult * Diffcult)
	{
		Resize(&img, Width, Height);
		loadimage(&img, String.c_str(), Width, Height);					// 加载图像
		putimage(0, 0, &img);
		outtextxy(700, 350, _T("当前状态: 已通关"));					// 输出游戏状态
		++Pass;															// 关数加一
		String[4] = char((Pass / 10) + 48);								// 修改
		String[5] = char((Pass % 10) + 48);
		Control = 1;
		mciSendString("play  Res\\胜利.mp3", NULL, 0, NULL);
		Sleep(3000);													// 延时 3 秒钟
	}

	if (Pass == PassCount)
	{
		cleardevice();
		settextstyle(50, 0, _T("华文行楷"));								// 设置字体信息
		outtextxy(220, 250, _T("恭喜你, 已通关全部关卡"));				// 输出游戏状态
		Control = 4;													// 改变控制值
	}
}

// 设置图片位置
void Picture::SetLocal()
{
	// 记录四个方向的值
	int sentryX[4] = {-1, 0, 1, 0};
	int sentryY[4] = {0, -1, 0, 1};

	int index = -1;
	int num = 0;
	int Diff = Diffcult -1;
	int Len = Diff;
	int x1, y1;
	int k = 0;
	loop:
	for (int l = 0; l < 8; ++l)
	{
		++index;
		index = index % 4;
		for (k = Len; k > 0; k--)
		{
			// 记录 LocalX 和 LocalY 的位置
			LocalX = image[Diff][Diff].x + sentryX[index];
			LocalY = image[Diff][Diff].y + sentryY[index];

			// 定位图片位置
			num = Query[LocalY][LocalX];

			// 记录 y1, x1 的位置
			y1 = num / Diffcult;
			x1 = num % Diffcult;

			// 修改查询数组的值
			Query[LocalY][LocalX] = Diffcult * Diffcult - 1;
			Query[image[Diff][Diff].y][image[Diff][Diff].x] = num;

			// 交换图片位置
			image[y1][x1].x = image[Diff][Diff].x;
			image[y1][x1].y = image[Diff][Diff].y;
			image[Diff][Diff].x = LocalX;
			image[Diff][Diff].y = LocalY;
		}
	}
	Len--;
	if (Len > 0)
	{
		goto loop;
	}

	// 经过上面的处理之后, 图片应该被打散了, 然后再进行随机过程处理
	srand(time(NULL));
	for (k = 0; k < 100; k++)
	{
		loop1:
		index = rand() % 4;
		// 记录 LocalX 和 LocalY 的位置
		LocalX = image[Diff][Diff].x + sentryX[index];
		LocalY = image[Diff][Diff].y + sentryY[index];
		if (LocalX >= 0 && LocalX <= Diff && LocalY >= 0 && LocalY <= Diff)
		{
			// 定位图片位置
			num = Query[LocalY][LocalX];
			
			// 记录 y1, x1 的位置
			y1 = num / Diffcult;
			x1 = num % Diffcult;
			
			// 修改查询数组的值
			Query[LocalY][LocalX] = Diffcult * Diffcult - 1;
			Query[image[Diff][Diff].y][image[Diff][Diff].x] = num;
			
			// 交换图片位置
			image[y1][x1].x = image[Diff][Diff].x;
			image[y1][x1].y = image[Diff][Diff].y;
			image[Diff][Diff].x = LocalX;
			image[Diff][Diff].y = LocalY;
		}
		else
		{
			goto loop1;
		}
	}
}

