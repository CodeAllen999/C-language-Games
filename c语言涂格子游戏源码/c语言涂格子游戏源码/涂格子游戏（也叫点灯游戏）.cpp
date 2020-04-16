/* ����ѧȥ����վ�ռ� http://www.zixue7.com */
#include	<graphics.h>
#include	<conio.h>
#define		MaxNum				14		//������������
#define		G_length			30		//���ӱ߳�
#define		USER_LBUTTONDOWN	101
#define		USER_RBUTTONDOWN	102
#define		USER_MBUTTONDOWN	103

///////////////////////////////////////////////
void PaintGrid(int Mid_x, int Mid_y, int num, int color);	// ������Ϸ���ӣ���ʼ������
void OnLButtonDown(MOUSEMSG m, int num);					// �������
void OnRButtonDown(int num);								// �Ҽ�����
void OnMButtonDown();										// �м�����*���޶���*
void welcome();												// ��ʾ��Ϸ������
void goodbye(int num);										// ��ʾ��������
void NextLevel(int num);									// ��һ��
int	 GetMessage(MOUSEMSG m);								// ��ȡ�����Ϣ
int  DispatchMessage(MOUSEMSG m, int opt);					// �ַ������Ϣ
int  JudgeFull(int num, int array[MaxNum][MaxNum]);			// �����Ƿ�����

///////////////////////////////////////////////
// ������Ϸ���ӽṹ��
struct Grid
{
	int left;	// ��Ϸ����߽�
	int right;
	int top;
	int bottom;
	int array[MaxNum][MaxNum];	// ��¼����״̬
	int num;	// ��¼�߽������Ŀ
}grid;


///////////////////////////////////////////////
void main()
{
	int opt, end=0;
	grid.num=4; 
	welcome();
	PaintGrid(320, 240, grid.num, RGB(0,255,0));
	MOUSEMSG m;
	while(end!=1)
	{
		m = GetMouseMsg();
		opt = GetMessage(m);
		end=DispatchMessage(m, opt);	
	}
	goodbye(grid.num);
    closegraph();
}


///////////////////////////////////////////////
// ��ȡ�����Ϣ
int GetMessage(MOUSEMSG m)
{
	//���ѭ��
	switch(m.uMsg)
	{
		case WM_LBUTTONDOWN:
			return USER_LBUTTONDOWN;
		case WM_RBUTTONDOWN:
			return USER_RBUTTONDOWN;
		case WM_MBUTTONDOWN:
			return USER_MBUTTONDOWN;
	}
	return 0;
}


///////////////////////////////////////////////
// �ַ���Ϣ
int DispatchMessage(MOUSEMSG m, int opt)
{
	switch(opt)
	{
		case USER_LBUTTONDOWN:
			// �����ɫ
			OnLButtonDown(m, grid.num);	
			// �ж��Ƿ�����
			if(JudgeFull(grid.num, grid.array)==1)
				{
					grid.num++;
					// ������Ŀ�������ֵͨ��
					if(grid.num>MaxNum)
					{
						return 1;
						break;
					}
					else
						NextLevel(grid.num);
				}
			break;

		case USER_RBUTTONDOWN:
			// �Ҽ����
			OnRButtonDown(grid.num);
			break;

		case USER_MBUTTONDOWN:
			return 1;
			break;
	}

	return 0;
}


///////////////////////////////////////////////
// �������
void OnLButtonDown(MOUSEMSG m, int num)
{
	int nx, ny, x, y;	
	if(m.x>grid.left && m.x<grid.right && m.y>grid.top && m.y<grid.bottom)
	{
		// ����λ��
		nx=(int)(m.x - grid.left)/G_length; 
		ny=(int)(m.y - grid.top )/G_length;
		// ת������״̬
		grid.array[nx][ny] = -grid.array[nx][ny];
		if(nx >= 0 && nx <  num-1) grid.array[nx+1][ny] = -grid.array[nx+1][ny];
		if(nx >  0 && nx <= num-1) grid.array[nx-1][ny] = -grid.array[nx-1][ny];
		if(ny >= 0 && ny <  num-1) grid.array[nx][ny+1] = -grid.array[nx][ny+1];
		if(ny >  0 && ny <= num-1) grid.array[nx][ny-1] = -grid.array[nx][ny-1];
		// ɨ����ɫ
		for(nx=0; nx<num; nx++)
		for(ny=0; ny<num; ny++)
		{
			if(grid.array[nx][ny] == 1)
				setfillcolor(GREEN);
			else
				setfillcolor(BLACK);
			x= nx * G_length + grid.left;
			y= ny * G_length + grid.top;
			solidrectangle(x+1, y+1, x+G_length-1, y+G_length-1);
		}
	}
}


///////////////////////////////////////////////
// �Ҽ��������
void OnRButtonDown(int num)
{
	int x, y, nx, ny;

	for(x=0; x<num; x++)
		for(y=0; y<num; y++)
			grid.array[x][y] = -1;

	for(nx=0; nx<num; nx++)
		for(ny=0; ny<num; ny++)
		{
			setfillcolor(BLACK);
			x= nx*G_length + grid.left;
			y= ny*G_length + grid.top;
			solidrectangle(x+1, y+1, x+G_length-1, y+G_length-1);
		}
}


///////////////////////////////////////////////
// ��ʾ��һ��
// ������
//	num:	��һ�صı߽������
void NextLevel(int num)
{
	// ����
	BeginBatchDraw();
	for(int y=0; y<=480; y+=5)
	{
		setlinecolor(RGB(0, 255, 0));
		settextcolor(RGB(0, 255, 0));
		line(0, y, 640, y);
		line(0, 480-y, 640, 480-y);
		outtextxy(300, y, "��һ��");
		FlushBatchDraw();
		Sleep(16);
		setfillcolor(BLACK);
		solidrectangle(0, y+4, 640, y-5);
		solidrectangle(0, 480-y, 640, 480-y+5);
	}
	EndBatchDraw();

	// ������һ�ظ���
	PaintGrid(320, 240, num, RGB(0,255,0));
}	


///////////////////////////////////////////////
// �жϸ����Ƿ�����
// ������
//	num:	���߸�����Ŀ
//	array:	�����������ʵ��
int JudgeFull(int num, int array[MaxNum][MaxNum])
{
	int c=-1;
	int nx=0, ny=0;
	while(nx<num && ny<num)
	{
		for(nx=0; nx<num; nx++)
			for(ny=0; ny<num; ny++)
				if(array[nx][ny]==1)
					continue;
				else 
					return c;
	}
	c=1;
	return c;
}


///////////////////////////////////////////////
// ������Ϸ���ӣ���ʼ������
// ������
//	Mid_x:	��Ļ���� x ����
//	Mid_y:	��Ļ���� y ����
//	num:	���߸�����Ŀ
//	color:	����������ɫ
void PaintGrid(int Mid_x, int Mid_y, int num, int color)
{
	int x,y,nx,ny;
	// ��Ϸ�����С
    grid.left   = Mid_x-num*G_length/2;
	grid.right  = Mid_x+num*G_length/2;
	grid.top    = Mid_y-num*G_length/2;
	grid.bottom = Mid_y+num*G_length/2;
	// ���Ƹ���
	setlinecolor(color);
	for(x=grid.left; x<=grid.right;  x+=G_length)
	{
		line(x, grid.top, x, grid.bottom);
		Sleep(10);
	}
	for(y=grid.top;  y<=grid.bottom; y+=G_length)
	{
		line(grid.left, y, grid.right, y);
		Sleep(10);
	}
	// ��߿�
	for(x=20;x>10;x--)
	{
		line(grid.left-x,	grid.top-x,		grid.right+x,	grid.top-x);
		line(grid.left-x,	grid.bottom+x,	grid.right+x,	grid.bottom+x);
		line(grid.left-x,	grid.top-x,		grid.left-x,	grid.bottom+x);
		line(grid.right+x,	grid.top-x,		grid.right+x,	grid.bottom+x);
		Sleep(5);
	}
	// ��յ�Ԫ��
	for(x=0; x<num; x++)
		for(y=0; y<num; y++)
			grid.array[x][y] = -1;
	for(nx=0; nx<num; nx++)
	for(ny=0; ny<num; ny++)
	{
		setfillcolor(BLACK);
		x = nx * G_length + grid.left;
		y = ny * G_length + grid.top;
		solidrectangle(x+1, y+1, x+G_length-1, y+G_length-1);
	}
}


///////////////////////////////////////////////
// ��ʾ��Ϸ������
void welcome()
{
	// ��ʼ������
	initgraph(640, 480);

	// �����Ļ��ʾ
	cleardevice();
	settextcolor(RGB(0,255,0));
	settextstyle(64, 0, "����");
	outtextxy(70, 50, "Ϳ������Ϸ(���)");
	settextcolor(WHITE);
	settextstyle(16, 0, "����");
	outtextxy(100, 200, "ÿ��һ�����ӣ��������ҵĸ���Ҳ����������״�෴�Ķ���");
	outtextxy(100, 240, "�ܹ�11�أ������ɫ���Ҽ��������м��˳�");
	outtextxy(100, 280, "ֻ��һ��������ʾ�汾���Ժ��ٸĽ�");
	outtextxy(400, 320, "by:doufuguolyl");
	settextstyle(16, 0, "����");
	outtextxy(400, 340, "Ver 0.1");

	// ʵ����˸��"�����������"
	int c=255;
	while(!kbhit())
	{
		settextcolor(RGB(0, c, 0));
		outtextxy(280, 400, "�����������");
		c -= 8;
		if (c < 0) c = 255;
		Sleep(20);
	}

	getch();
	cleardevice();
}


///////////////////////////////////////////////
// ��ʾ��������
void goodbye(int num)
{
	int c=255;

	// ����
	BeginBatchDraw();
	for(int y=0; y<=480; y+=5)
	{
		setlinecolor(RGB(0, 255, 0));
		line(0, y, 640, y);
		line(0, 480-y, 640, 480-y);
		FlushBatchDraw();
		Sleep(16);
		setfillcolor(BLACK);
		solidrectangle(0, y+4, 640, y-5);
		solidrectangle(0, 480-y, 640, 480-y+5);
	}
	EndBatchDraw();

	//�ж���ʾ����
	if(num == MaxNum+1)
	{
		settextcolor(RGB(0, c, 0));
		settextstyle(48, 0, "����");
		outtextxy(280, 200, "ͨ��");
		settextstyle(20, 0, "����");
	}
	else
	{
		settextcolor(RGB(0, c, 0));
		settextstyle(48, 0, "����");
		outtextxy(200, 200, "�ٽ�����");
		settextstyle(20, 0, "����");
	}

	while(!kbhit())
	{
		settextcolor(RGB(0, c, 0));
		outtextxy(400, 400, "QQ: 372480348");
		c -= 8;
		if (c < 0) c = 255;
		Sleep(20);
	}

	getch();
}