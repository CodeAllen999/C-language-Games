#include"OtherFuntion.h"

/*-----------it学习吧-【自学去】网站【www.itstudy8.net】站长原创,转载需注名出处，谢谢-----------*/

void gotoxy(int x, int y)
{
	COORD c;
	c.X = 2 * x, c.Y = y; //移动光标
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void HideCursor()//隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void HideCursor1()//恢复光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 1}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void DrawTable( int row,int col,int x,int y )
{
	gotoxy( x,y );
	for(int i = 1; i <= row; ++i)
	{
		for( int j = 1; j <= col; ++j )
		{
			if( i == 1 )
			{
				if( j == 1 )
					printf("╔");
				else if( j == col )
					printf("╗");
				else
					printf("┉");
			}
			else if( i % 2 == 0  )
			{
				if( j == 1 || j == col )
					printf("┋");
				else
					printf("  ");
			}
			else if( i != 1 && i != row && i % 2 == 1 )
			{
				if( j == 1 )
					printf("╠");
				else if( j == col )
					printf("╣");
				else
					printf("═");
			}
			else if( i == row )
			{
				if( j == 1 )
					printf("╚");
				else if( j == col )
					printf("╝");
				else
					printf("┉");
			}
			else
			{}
		}
		gotoxy( x,y+i );
	}
}

void Stop()
{
	printf("请按任意键继续...\n");
	getch();
	HideCursor();
}
