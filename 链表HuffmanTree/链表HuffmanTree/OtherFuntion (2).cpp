#include"OtherFuntion.h"

/*-----------itѧϰ��-����ѧȥ����վ��www.itstudy8.net��վ��ԭ��,ת����ע��������лл-----------*/

void gotoxy(int x, int y)
{
	COORD c;
	c.X = 2 * x, c.Y = y; //�ƶ����
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void HideCursor()//���ع��
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void HideCursor1()//�ָ����
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
					printf("�X");
				else if( j == col )
					printf("�[");
				else
					printf("��");
			}
			else if( i % 2 == 0  )
			{
				if( j == 1 || j == col )
					printf("��");
				else
					printf("  ");
			}
			else if( i != 1 && i != row && i % 2 == 1 )
			{
				if( j == 1 )
					printf("�d");
				else if( j == col )
					printf("�g");
				else
					printf("�T");
			}
			else if( i == row )
			{
				if( j == 1 )
					printf("�^");
				else if( j == col )
					printf("�a");
				else
					printf("��");
			}
			else
			{}
		}
		gotoxy( x,y+i );
	}
}

void Stop()
{
	printf("�밴���������...\n");
	getch();
	HideCursor();
}
