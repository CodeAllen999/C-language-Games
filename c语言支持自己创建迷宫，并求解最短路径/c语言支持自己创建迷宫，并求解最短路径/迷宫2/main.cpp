
#include "labyrith.h"

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

// ������
int main()
{
	FrameWindow frame;	// ����ͼ�ν���
	frame.Run();		// ���п��ƺ���

	while(1)			// ��ѭ��
	{
		frame.Run();	// ���п���
	}

	getch();			// ���а�����ʱ��ر�ͼ��
	closegraph();

	return 0;
}