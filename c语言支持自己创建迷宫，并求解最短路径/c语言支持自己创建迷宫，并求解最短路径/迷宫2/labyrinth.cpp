#include "labyrith.h"

int Wall[22][22];	// ǽ��
int entranceX;		// ���
int entranceY;
int exitX;			// ����
int exitY;

// Ĭ�Ϲ��캯��
FrameWindow::FrameWindow()
{
	initgraph(960, 660);					// ����ͼ�ν���
	setbkcolor(LIGHTGREEN);					// ���ñ�����ɫΪ����ɫ
	direct = 0;								// ���� direct �ĳ�ֵΪ 0
	control = 0;							// Ĭ�Ͽ���ȨΪ 0 
	loadimage(&img, "res\\bk.jpg", 29, 29);	// ����ͼƬ
}

// ���п���
void FrameWindow::Run()
{
	cleardevice();		// ����
	NewBackground();	// �����±���ͼ
	DrawSome();			// ����Щ����
	control = 0;		// ���Ƚ������Գ������Ŀ���Ȩ�� 0
	direct = 0;			// ���� direct �ĳ�ֵΪ 0

	// ��ѭ��
	while(1)
	{
		if(kbhit())													// ��ⰴ��
		{
 			direct = getch();										// �Ӱ�����ȡ����
			mciSendString("play  res\\key.wav", NULL, 0, NULL);		// ������
			if( direct == 115 &&  control == 0)						// s �ļ�ֵΪ 115
			{
				StartDrawLabyrith();								// ��ʼ�����Թ�
			}


			if(direct == 101 && control == 2)						// e �ļ�ֵΪ 101
			{
				SetLabyrith();										// �����Թ�����ںͳ���
			}

			if(direct == 100 && control == 3)						// d �ļ�ֵΪ 100
			{
				control = -1;										// �� control ����Ϊ -1 ��Ŀ����
																	// �ó���� Demo() �ص� Run() ʱֻ��Ӧˢ�²���
				Demo();												// Ѱ��·������ʾ
			}

			if(direct == 63 && (control == 0 || control == -1))		// �� F5 ˢ��
			{
				break;
			}
		}
		else
		{
			Sleep(10);
		}
	}
}

// �����±���
void FrameWindow::NewBackground()
{
	float H, S, L;					// ���� HSL ��ɫģ�͵� 3 ������
	H = 110;						// ɫ��
	S = 1;							// ���Ͷ�
	L = 0.4522f;					// ����
	for(int y = 0; y != 660; ++y)	// �����Թ�������ɫ
	{
		L += 0.000125f;
		S -= 0.00125f;
		setcolor(HSLtoRGB(H, S, L));
		line(0, y, 660, y);
	}

	H = 50;							// ɫ��
	S = -3.2555f;					// ���Ͷ�
	L = 0.525617f;					// ����
	for(y = 0; y != 660; ++y)		// ������ʾ��Ϣ���ֱ���
	{
		L += 0.000000085f;
		S -= 0.0015f;
		setcolor(HSLtoRGB(H, S, L));
		line(660, y, 960, y);
	}
}

// ����Щ����
void FrameWindow::DrawSome()
{
	setcolor(LIGHTRED);
	for(int i = 0; i < 22; ++i)								
	{
		// ��Χǽ���� Wall �����е�λ���� 1 
		Wall[0][i] = 1;
		Wall[i][0] = 1;
		Wall[21][i] = 1;
		Wall[i][21] = 1;

		// ������Χǽ��
		putimage(0 * 30 + 1, i * 30 + 1, &img);
		putimage(i * 30 + 1, 0 * 30 + 1, &img);
		putimage(631, i * 30 + 1, &img);
		putimage(i * 30 + 1, 631, &img);
		putimage(931, i * 30 + 1, &img);

		line(i * 30, 0, i * 30, 660);		// ���Ƹ�����
		line(0, i * 30, 660, i * 30);		// ���Ƹ�����
	}

	for(i = 0; i < 10; ++i)					// ������ʾ������Χ��
	{
		putimage(i * 30 + 661, 1, &img);
		putimage(i * 30 + 661, 631, &img);
	}

	for(i = 1; i <= 20; ++i)				// ������ Wall �����ֵ��ʱ�� 0
	{
		for(int j = 1; j <= 20; ++j)
		{
			Wall[i][j] = 0;
		}
	}

	// ������ʾ��Ϣ
	RECT r = {710, 40, 900, 300};
	setbkmode(TRANSPARENT);					// ����������ֱ���ģʽΪ͸��
	setcolor(BLUE);							// �������������ɫ
	setfont(15, 0, "����");
	
	// �����ʾ��Ϣ
	drawtext("��Ϸ�������ܣ�\n\n���� S�������Թ���\n����������ǽ�ڣ�\
		����Ҽ�����ǽ�ڡ�\n\n���� E�������Թ�����ںͳ��ڡ�\nʹ�����\
		�����������ںͳ��ڣ��Ҽ�ȡ�����á�\n\n���� D�������Թ���̽��\
		��Ѱ�Ҵ���ڵ����ڵ����·������С������ʾ����ڵ����ڵ�·����",
		&r, DT_WORDBREAK);

	setbkmode(OPAQUE);						// �ָ�Ĭ�������ɫ

	// �����ʾ��Ϣ
	outtextxy(730, 400, "�Թ�״̬: ");
	outtextxy(810, 400, "�ȴ�����");
	outtextxy(750, 500, "�� F5 ���¿�ʼ");
}

// ��ʼ�����Թ�
void FrameWindow::StartDrawLabyrith()
{
	int x = 0, y = 0;						// �����������ʹ��
	outtextxy(810, 400, "���ڻ���");		// �޸��Թ�״̬
	FlushMouseMsgBuffer();					// ��������Ϣ������
 
	// ��ѭ��
	while(1)
	{
		if(kbhit())
		{
			direct = getch();									// ��ȡ������Ϣ
			mciSendString("play  res\\key.wav", NULL, 0, NULL);	// ������
			if(direct == 101)									// e �ļ�ֵΪ 101
			{
				control = 2;									// ����ȨֵΪ 2 
				break;
			}
			else if(direct == 63)								// F5 ˢ��
			{
 				break;
			}
		}
		else if(MouseHit())
		{
			msg = GetMouseMsg();										// ��ȡ�����Ϣ
			x = msg.x / 30;												// ��ȡ������ڸ����� Wall �е�λ��
			y = msg.y / 30;
			if(msg.x > 30 && msg.x < 630 && msg.y > 30 && msg.y < 630)	// ֻ�����������������Ӧ�����Ϣ
			{
				switch(msg.uMsg)										// ��Ϣ������
				{
					case WM_LBUTTONDOWN:								// �������
						{
							Wall[y][x] = 1;								// y ��Ӧ��, x ��Ӧ��, ����Ӧ��λ���� 1
							putimage(x * 30 + 1, y * 30 +1, &img);		// ����ͼƬ
						}
						break;
					case WM_RBUTTONDOWN:								// �Ҽ�����
						{
							Wall[y][x] = 0;								// y ��Ӧ��, x ��Ӧ��, ����Ӧ��λ���� 0
							PrintGrid(x * 30, y * 30);					// ���»����������
							setcolor(BLUE );
						}
						break;
					default:break;
					}
			}

		}
		else 
		{
			Sleep(10);
		}
	}
}

// ������ںͳ���
void FrameWindow::SetLabyrith()
{
	int x = 0, y = 0;	// ��ʱ����
	entranceX = -1;		// ���
	entranceY = -1;
	exitX = -1;			// ����
	exitY = -1;	

	outtextxy(810, 400, "�������");	// ��ʾ��Ϣ
	
	// ��ѭ��
	while(1)
	{
		if(kbhit())						// ������Ϣ
		{
			direct = getch();										// ��ȡ��Ϣ
			mciSendString("play  res\\key.wav", NULL, 0, NULL);		// ������
			if(direct == 100 && entranceX != -1 && exitX != -1)		// �������ڶ����ú�, �� d ���˳�����ģʽ
			{
				control = 3;										// ����Ȩ��Ϊ 3, �ص� Run �������ж���˭���Ƴ���;
				break;
			}
			else if(direct == 63)									// F5 ˢ��
			{
				control = 0;
				break;
			}
		}
		else if(MouseHit())
		{
			msg = GetMouseMsg();												// ��ȡ�����Ϣ
			x = msg.x / 30;														// ��ȡ������ڸ����� Wall �е�λ��
			y = msg.y / 30;	

			if(entranceX != -1 && exitX != -1)									// �������
			{
				outtextxy(810, 400, "�������");
			}

			if(msg.x > 30 && msg.x < 630 && msg.y > 30 && msg.y < 630)			// ֻ�����������������Ӧ�����Ϣ
			{
				if(Wall[y][x] == 0 && msg.uMsg == WM_LBUTTONDOWN)				// ������λ�ò���ǽ��, ���Ұ������
				{
					if(entranceX == -1 && (exitX != x || exitY != y))			// ȷ���˴�û������
					{
						entranceX = x;											// ���λ��
						entranceY = y;
						Wall[y][x] = 1;
						outtextxy(x * 30 + 8, y * 30 + 10,_T("In"));			// ���˴����Ϊ In 

						if(exitX == -1)											// ����ʱ��δ���ó���
						{
							outtextxy(810, 400, "���ó���");					// �ı��Թ�״̬
						}
					}
					else if(exitX == -1 && (entranceX != x || entranceY != y))	// �˴�δ���ó����Ҳ������λ��
					{
						exitX = x;												// ����λ��
						exitY = y;
						Wall[y][x] = 1;
						outtextxy(x * 30 + 4, y * 30 + 8,_T("Out"));			// ���˴����Ϊ Out

						if(entranceX == -1)										// ����ʱ��δ�������
						{
							outtextxy(810, 400, "�������");					// �ı��Թ�״̬
						}
					}
				}
				else if(Wall[y][x] == 1 && msg.uMsg == WM_RBUTTONDOWN)			// ������λ�ò���ǽ��, ���Ұ����Ҽ�
				{
					if(x == entranceX && y == entranceY)						// ȡ���������
					{
						entranceX = -1;
						entranceY = -1;
						Wall[y][x] = 0;
						outtextxy(810, 400, "�������");						// �ı��Թ�״̬
						PrintGrid(x * 30, y * 30);								// ���»��Ƹ���
						setcolor(BLUE);											// �ָ�ԭ������ɫ
					}
					else if(x == exitX && y == exitY)							// ȡ�����ó���
					{
						exitX = -1;
						exitY = -1;
						Wall[y][x] = 0;
						outtextxy(810, 400, "���ó���");						// �ı��Թ�״̬
						PrintGrid(x * 30, y * 30);								// ���»��Ƹ���
						setcolor(BLUE);											// �ָ�ԭ������ɫ
					}
				} 
			} 
		} 
	} 
} 

// ̽���Թ�·��, ����ʾ�ɹ�
void FrameWindow::Demo()
{
	Queue qu;
	Node node;
	int zx[4] = {1,0,-1,0},zy[4] = {0,1,0,-1};		// �ĸ�����
	int find = 0;									// find ֵΪ 1 ��ʾ����Ѱ��·��
	int x = 0, y = 0;								// ��ʱ���� x, y

	node.x = entranceX;								// ���λ��
	node.y = entranceY;
	outtextxy(810, 400, "������ʾ");				// �����Թ�״̬
	qu.Push(node);									// ��Ӳ���

	// ��������㷨Ѱ�����·��
	while(qu.GetFront() < qu.GetRear() && find == 0)
	{
		node.x = qu.visit(qu.GetFront()).x;			// �¶�ͷ������
		node.y = qu.visit(qu.GetFront()).y;

		for(int i = 0; i < 4; ++i)					// ���ĸ�����̽��
		{
			x = node.x;
			y = node.y;

			node.x += zx[i];
			node.y += zy[i];

			if(Wall[node.y][node.x] == 0)			// ����Աߵ�λ�ò���ǽ�ڲ���û�б�����
			{
				qu.Push(node);						// ����λ�ü������
				Wall[node.y][node.x] = 1;
			}

			if(node.x == exitX && node.y == exitY)	// �ҵ�����λ��
			{
				qu.Push(node);						// ������λ�ü������
				find = 1;							// find �� 1, ��ʾ�ҵ�����
				break;
			}

			node.x = x;
			node.y = y;
		}
		qu.Pop();							// ����ͷ����
	}

	if(find == 1)							// ����ҵ�����
	{
		qu.ResetPre();						// ���ýڵ�ǰ��
		qu.PrintRoute();					// ���·��
	}
	else
	{
		outtextxy(760, 440, "������·��");	// ����, ��Ϊ������·��
	}

}

// �����¸���
void PrintGrid(int x, int y)
{
	float H = 110, S = 1, L = 0.4522f;	// ���� H S L�ĳ�ֵ
	S -= (float)y * 0.00125f;			// ���� S ����������ֵ
	L += (float)y * 0.000125f;			// ���� L �����������
	for(int i = y + 1; i < y + 30; ++i)	// ѭ����������
	{
		L += 0.000125f;
		S -= 0.00125f;
		setcolor(HSLtoRGB(H, S, L));
		line(x + 1, i, x + 29, i);
	}
}

// Ĭ�Ϲ��캯��
Queue::Queue()
{
	data = new Node[QueueMaxLength];	// ������д洢�ռ�
	front = 0;							// ��ͷΪ 0
	rear = 0;							// ��βΪ 0
}

// ��������
Queue::~Queue()
{
	delete (data);	// �ͷŶ��д洢�ռ�
}

// ���Ӳ���
void Queue::Pop()
{
	++front;		// ���Ӳ���
}

// ��Ӳ���
void Queue::Push(Node node)
{
	data[rear].x = node.x;
	data[rear].y = node.y;

	if(rear == 0)						// ����ǵ�һ��Ԫ�����, ����ǰ��ָ���
	{
		data[rear].pre = NULL;
	}
	else
	{
		data[rear].pre = &data[front];	// ����, ��ǰ��ָ���ͷ
	}
	++rear;								// ��β�� 1
}

// ��ȡ��ͷ
inline int Queue::GetFront()
{
	return front;
}

// ��ȡ��β
inline int Queue::GetRear()
{
	return rear;
}

// ���ʶ���
Node Queue::visit(int i)
{
	return data[i];
}

// ���ýڵ�ǰ��
void Queue::ResetPre()
{
	Node *s = &data[rear - 1];	// ָ�����
	Node *p = s->pre;			// ���ڵ�ǰ��
	Node *r ;

	// ��ѭ��
	while(1)
	{
		r = p->pre;				// r ָ�� p ��ǰ��
		p->pre = s;				// p ��ǰ��ָ�� s
		s = p;					// s ָ�� p
		p = r;					// p ָ�� r
		if(r == NULL)			// ��� r Ϊ��, �˳�ѭ��
		{
			break;
		}
	}
}

// ���·��
void Queue::PrintRoute()
{
	Node * s = data[0].pre;								// ���λ��

	// ��ѭ��
	while(s != &data[rear - 1])
	{
		setfillstyle(LIGHTRED);							// ���������ɫ

		// ����Բ
		fillcircle(s->x * 30 + 15, s->y * 30 + 15, 10);
		Sleep(100);
		s = s->pre;										// s ָ����ǰ��
	}
	outtextxy(810, 400, "��ʾ���");					// �ı��Թ�״̬
}

