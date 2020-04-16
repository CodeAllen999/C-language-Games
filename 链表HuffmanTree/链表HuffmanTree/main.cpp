#include"OtherFuntion.h"
#include"HuffmanTree.h"

/*----------------要成功运行本程序需要电脑上有 graphics.h 这个头文件否则无法编译----------*/

/*-----------it学习吧-【自学去】网站【www.itstudy8.net】站长原创,转载需注名出处，谢谢-----------*/
void main()
{
	system("color 06");
	HuffmanTree HT = NULL;
	HuffmanCode HC;
	char EnteringData[MAX_FILE_SIZE];
	while( 1 )
	{
		Menu( HT,HC,EnteringData );
	}
	gotoxy( 0,23 );
}