
// ����ͷ�ļ�
#include "../Inc/picture.h"

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

int main()
{
	GameFrame gameframe;												// ������Ϸ���
	Picture picture;													// ����ͼƬ���
	gameframe.DrawBackground();											// ���Ʊ���
	gameframe.StartMenu();												// ���ƿ�ʼ��Ϣ
	
	while (1)
	{
		picture.Run();													// ���п��ƺ���
		Sleep(10);														// �ʵ�������ʱ, ��Լ CPU
	}
	getch();
	return 0;
}
