/* ����ѧȥ����վ�ռ� http://www.zixue7.com */


#include "ymd.h"

// ������
int main()                                                      
{
	char add;
	tm *t;										// �� time.h ���ж���Ϊһ���ṹ�壬�÷��� MSDN
	time_t Clock;								// �� time.h ���ж���Ϊһ���ṹ�壬�÷��� MSDN
	Time tm;									// �ṹ�� tm

	// ��ʼ��
	Init();															

	// ��ȡ�ṹ�� Clock �Ĳ���
	time(&Clock);	

	// ��ȡʱ��
	t = localtime(&Clock);											

	tm.year = t->tm_year + 1900;				// ��ǰϵͳʱ���������, ����Ϊʲô�� 1900, �� MSDN
	tm.month = t->tm_mon + 1;					// ��ȡϵͳʱ�������·�, ����Ϊʲô�� 1, �� MSDN
	tm.yearFlag = tm.year;						// ��ǵ�ǰ��ݷ�
	tm.monthFlag = tm.month;					// ��ǵ�ǰ�·�

	// ��������
	DrawWeek();									
	
	// ���Ƶ��µ�����
	DrawDate(tm);													

	// ��ѭ��
	while(1)														
	{
		// �Ӽ��̻�ȡ����
		add = getch();												

		// �������ڵ�����
		CalDate(tm, add);											

		// �ж������Ƿ����, ������� if ���
		if (DateFlag(tm.year, tm.yearFlag, tm.month, tm.monthFlag))  
		{
			// �����Ļ
			cleardevice();
			
			// ���»�������
			DrawWeek();
			
			// ���»��Ƶ�������
			DrawDate(tm);

			tm.yearFlag = tm.year;				// �����±�����
			tm.monthFlag = tm.month;			// �����±���·�
		}
	}

	// ����
	return 0;
}