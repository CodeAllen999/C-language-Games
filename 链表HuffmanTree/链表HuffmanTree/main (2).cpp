#include"OtherFuntion.h"
#include"HuffmanTree.h"

/*----------------Ҫ�ɹ����б�������Ҫ�������� graphics.h ���ͷ�ļ������޷�����----------*/

/*-----------itѧϰ��-����ѧȥ����վ��www.itstudy8.net��վ��ԭ��,ת����ע��������лл-----------*/
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