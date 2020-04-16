/* ����ѧȥ����վ�ռ� http://www.zixue7.com */
#include <graphics.h>
#include <time.h>

#define	CHESIZE	40		// ���̳ߴ磬�����������
#define	RESETX	170
#define	RESETY	350		// ����ԭ��

typedef enum			// Ҫ�õ�������ID
{
	si, jun, shi, lv, tuan, 
	ying, lian, pai, ban, gong, 
	fei, chao, zha, qi, lei, bian,
	xian, sheng,  shen
}CHESSID;

typedef enum			// ��������
{
	comatt, preatt, noatt
}ATTSTYLE;

typedef enum			// ��ǰ��Ϸ��������������
{
	blue, red, white
}TEAM;

typedef enum			// ѡ����δѡ��
{
	alchoose, unchoose
}CHOOSESTATE;

typedef enum			// ����״̬
{
	unknow, empty, exist
}STATE;

typedef struct			// ����
{
	int x;
	int y;
}COOR;

typedef struct			// ����
{
	CHESSID    id;		// ���ӵ�ID
	int        power;	// ���ӵĵȼ�
	TEAM       team;	// ������
	char       *image;	// �����ӵ�ͼƬ�����ǵ��������⣬���������ִ���
	int        scoopc;	// �������ڵ��ĵ�����
}CHESS;

typedef struct			// ����
{
	COOR crdld;			// �������������
	CHESS chess;		// ���������
	STATE  state;		// ����״̬
}AREA;

typedef struct			// �û���ѡ����Ϣ
{
	int i;      
	int j;
	CHOOSESTATE state;	// ѡ��״̬
}CHOOSE;

IMAGE image;
AREA area[6][6];		// �������̴�С
CHESS datachess[19];	// ���ֻ�����������
CHOOSE choose;			// �û�ѡ����Ϣ
MOUSEMSG mmsg;			// �����Ϣ
TEAM  user;				// ִ�巽
int lockchessboard = 0;	// �Ƿ���������
int i;					// ��ǰ����������������
int j;                         
char *str[]={"��","��","��","��","Ӫ","��","��","ʦ","��","˾","��","ը","��","��","��","��","��","��","��"}; 

void init();      
void initchessbute();	// ����ʼ�����ӻ�������
void initvalue();
void drawboard();		// ������
void randomarr(int *);	// ʵ������������
void judge();
void getpreij();		// ��õ�ǰ���������������
int  checkij();			// ��鵱�����������
void open();			// ����������
int  whemove();			// �ж��Ƿ����ƶ�
void move();			// �ƶ�
int  judgeunknow();		// ��⵱ǰδ����������
ATTSTYLE  wheattack();	// �ж��Ƿ��ܹ���
void kill();			// ɱ����ǰѡ�����
void killself();		// ��ɱ
void perishtogether();	// ͬ���ھ�
void getteam();			// �����ı���������ʱ����������������ֵ
void userchange();		// ����ִ�巽
void judgebunko();		// �ж���Ӯ
void choosearea();		// ѡ������
void cancelchoose();	// ȡ��ѡ��
void change();			// ����
void bluewin();			// ����ʤ��
void redwin();			// �췽ʤ��
void gamehelp();		// ����˵��
void quit();			// �˳���Ϸ
void peace();			// ����
void surrender();		// Ͷ��
void resetchessboard();	// ����

// ���漸������Ϊ�ж����ӵĹ�������
ATTSTYLE judgegong();	// �жϹ���
ATTSTYLE judgecom();	// ����ͨ����
ATTSTYLE judgezha();	// �ж�ը��

void main()				// ������
{
	init();

	while (true)
	{
		mmsg = GetMouseMsg();
		getpreij();

		if (mmsg.uMsg == WM_LBUTTONDOWN)   //�������
		{
			judge();
		}
		else if (mmsg.uMsg == WM_RBUTTONDOWN
				&& choose.state==alchoose) //�����Ҽ�
		{
			cancelchoose();
		}
		else if (mmsg.uMsg == WM_MBUTTONDOWN
				&& choose.state == alchoose
				&& area[choose.i][choose.j].chess.id != zha) //�����м�
		{
			killself();
			cancelchoose();
			userchange();
			judgebunko(); 
		}
	}
}


void init()
{
	initgraph(640, 480);

	setorigin(RESETX, RESETY);		// ����ԭ��
	setaspectratio(1, -1);			// �� y ���Ϸ���Ϊ������

	drawboard();
	initvalue();

}

void drawboard()					// ������
{
	int i1;

	setlinecolor(WHITE);
	for (i1=0; i1<7; i1++)
	{
		line(i1*CHESIZE, 0, i1*CHESIZE, CHESIZE*6);
	}

	for (i1=0; i1<7; i1++)
	{
		line(0, i1*CHESIZE, CHESIZE*6, i1*CHESIZE);
	}


	setlinecolor(WHITE);
	setfillcolor(RED);
	rectangle(-10, -10, CHESIZE*6+10, CHESIZE*6+10);
	floodfill(-1, -1, WHITE);

	rectangle(7*CHESIZE, CHESIZE, 9*CHESIZE, 6*CHESIZE);
	line(7*CHESIZE, 5*CHESIZE, 9*CHESIZE, 5*CHESIZE);
	line(7*CHESIZE, 4*CHESIZE, 9*CHESIZE, 4*CHESIZE);
	line(7*CHESIZE, 3*CHESIZE, 9*CHESIZE, 3*CHESIZE);
	line(7*CHESIZE, 2*CHESIZE, 9*CHESIZE, 2*CHESIZE);
	setaspectratio(1, 1);
	settextstyle(35, 18, "����");
	settextcolor(RED);
	outtextxy(7*CHESIZE+2, -6*CHESIZE+2, "����");
	settextcolor(BROWN);
	outtextxy(7*CHESIZE+2, -5*CHESIZE+2, "Ͷ��");
	settextcolor(GREEN);
	outtextxy(7*CHESIZE+2, -4*CHESIZE+2, "����");
	settextcolor(YELLOW);
	outtextxy(7*CHESIZE+2, -3*CHESIZE+2, "����");
	settextcolor(CYAN);
	outtextxy(7*CHESIZE+2, -2*CHESIZE+2, "�˳�");

	settextcolor(LIGHTMAGENTA);
	settextstyle(50, 20, "����");
	outtextxy(CHESIZE, -CHESIZE*8, "��������");

	setaspectratio(1, -1);
}

void initchessbute()				// �������ӻ�������
{
	datachess[0].id = gong;
	datachess[0].power = 1;
	datachess[0].image = str[0];
	datachess[0].scoopc = 0;

	datachess[1].id = ban;
	datachess[1].power = 2;
	datachess[1].image = str[1];
	datachess[1].scoopc = 0;

	datachess[2].id = pai;
	datachess[2].power = 3;
	datachess[2].image = str[2];
	datachess[2].scoopc = 0;

	datachess[3].id = lian;
	datachess[3].power = 4;
	datachess[3].image = str[3];
	datachess[3].scoopc = 0;

	datachess[4].id = ying;
	datachess[4].power = 5;
	datachess[4].image = str[4];
	datachess[4].scoopc = 0;

	datachess[5].id = tuan;
	datachess[5].power = 6;
	datachess[5].image = str[5];
	datachess[5].scoopc = 0;

	datachess[6].id = lv;
	datachess[6].power = 7;
	datachess[6].image = str[6];
	datachess[6].scoopc = 0;

	datachess[7].id = shi;
	datachess[7].power = 8;
	datachess[7].image = str[7];
	datachess[7].scoopc = 0;

	datachess[8].id = jun;
	datachess[8].power = 9;
	datachess[8].image = str[8];
	datachess[8].scoopc = 0;

	datachess[9].id = si;
	datachess[9].power = 10;
	datachess[9].image = str[9];
	datachess[9].scoopc = 0;

	datachess[10].id =  qi;
	datachess[10].power = 100;
	datachess[10].image = str[10];
	datachess[10].scoopc = 0;

	datachess[11].id = zha;
	datachess[11].power = 99;
	datachess[11].image = str[11];
	datachess[11].scoopc = 0;

	datachess[12].id = bian;
	datachess[12].power = 0;
	datachess[12].image = str[12];
	datachess[12].scoopc = 0;

	datachess[13].id = lei;
	datachess[13].power = 98;
	datachess[13].image = str[13];
	datachess[13].scoopc = 0;

	datachess[14].id = fei;
	datachess[14].power = 9;
	datachess[14].image = str[14];
	datachess[14].scoopc = 0;

	datachess[15].id = chao;
	datachess[15].power = 11;
	datachess[15].image = str[15];
	datachess[15].scoopc = 0;

	datachess[16].id = sheng;
	datachess[16].power = 10;
	datachess[16].image = str[16];
	datachess[16].scoopc = 0;

	datachess[17].id = shen;
	datachess[17].power = 11;
	datachess[17].image = str[17];
	datachess[17].scoopc = 0;

	datachess[18].id = xian;
	datachess[18].power = 11;
	datachess[18].image = str[18];
	datachess[18].scoopc = 0;	
}

void initvalue()					// ��ʼ��ֵ
{
	CHESS chess[36];
	int random[36];
	int count;
	int i1, j1;
	
	initchessbute();

	randomarr(random);

	for (i1=0; i1<=11; i1++)
	{
		chess[i1] = datachess[i1];
		chess[i1].team = red;
	}
	chess[i1] = datachess[11];
	chess[i1].team = red;
	chess[i1+1] = datachess[0];
	chess[i1+1].team = red;

	for (i1=0; i1<=11; i1++)
	{
		chess[i1+14] = datachess[i1];
		chess[i1+14].team = blue;
	}
	chess[i1+14] = datachess[11];
	chess[i1+14].team = blue;
	chess[i1+15] = datachess[0];
	chess[i1+15].team = blue;	

	for (i1=0; i1<4; i1++)
	{
		chess[i1+28] = datachess[12];
		chess[i1+28].team = white;
		chess[i1+32] = datachess[13];
		chess[i1+32].team = white;
	}

	setfillcolor(YELLOW);
	for (count=0, i1=0; i1<6; i1++)
	{
		for (j1=0; j1<6; j1++, count++)
		{
			area[i1][j1].chess = chess[random[count]];
			area[i1][j1].crdld.x = i1 * CHESIZE + 1;
			area[i1][j1].crdld.y = j1 * CHESIZE + 1;
			area[i1][j1].state = unknow;
			floodfill(area[i1][j1].crdld.x, area[i1][j1].crdld.y, WHITE);
		}
	}
	user = red;
	choose.state = unchoose;

}

void randomarr(int random[])		// �õ�0~36���ֵ��������
{
	int i1, j1;
	int flag = 0;

	srand(time(NULL));
	random[0] = rand() % 36 ;

	for (i1=1; i1<36; i1++)
	{
		while (1)
		{
			random[i1] = rand() % 36 ;
			for (j1=0; j1<i1; j1++)
			{
				if (random[j1] == random[i1])
				{
					flag = 1;
					break;
				}
			}
			if (flag)
			{
				flag = 0;
			}
			else
			{
				break;
			}
		}
	}
}

void judge()						// �жϵ�ǰҪ���еĲ���
{
	ATTSTYLE  attstyle;				// ��������

	getpreij();
	if (checkij())
	{
		if (area[i][j].state==unknow && choose.state==unchoose)	// ��
		{
			open();
			userchange();
		}
		else if(area[i][j].state == empty)
		{
			if (choose.state == alchoose)						// �ƶ�
			{
				if (whemove())
				{
					move();
					cancelchoose();
					userchange();
				}
			}
		}
		else
		{
			if (choose.state == unchoose)                       
			{
				if (area[i][j].chess.team==user && area[i][j].chess.id!=qi)  //ѡ��  
				{
					choosearea();                                         
				}
			}
			else
			{
				if (area[i][j].state!=unknow)		// ����
				{
					attstyle = wheattack();
					if (attstyle == comatt)
					{
						kill();
						cancelchoose();
						userchange();
					}
					else if (attstyle == preatt)
					{
						perishtogether();
						cancelchoose();
						userchange();
					}
					else
					{
						;
					}
				}
			}
		}

		if (!judgeunknow())		// ���������Ӷ�������������ж���Ӯ
		{
			judgebunko();                 
		}
	}
}

int  judgeunknow()
{
	int i1, i2;
	int num = 0;

	for (i1=0; i1<6; i1++)
	{
		for (i2=0; i2<6; i2++)
		{
			if (area[i1][i2].state == unknow)
			{
				num++;
			}
		}
	}

	return num;
}

// ѡ������
void choosearea()
{
	choose.i = i;
	choose.j = j;
	choose.state = alchoose;

	setlinecolor(GREEN);
	rectangle(choose.i*CHESIZE, choose.j*CHESIZE, choose.i*CHESIZE+CHESIZE, choose.j*CHESIZE+CHESIZE);
}

// ȡ��ѡ��
void cancelchoose()
{ 
	setlinecolor(WHITE);
	rectangle(choose.i*CHESIZE, choose.j*CHESIZE, choose.i*CHESIZE+CHESIZE, choose.j*CHESIZE+CHESIZE);
	choose.state = unchoose;
}

// ��ǰ�����������
void getpreij()
{
	i = (mmsg.x-RESETX) / CHESIZE;
	j = -(mmsg.y-RESETY) / CHESIZE;
}

// �������Ƿ�����Ч������
int  checkij()
{
	if ((i==7 || i==8) && j==5)
	{
		gamehelp();
		return 0;
	}
	else if ((i==7 || i==8) && j==4)
	{
		if (!lockchessboard)
		{
			surrender();
		}
		return 0;
	}
	else if ((i==7 || i==8) && j==3)
	{
		if (!lockchessboard)
		{
			peace();
		}
		return 0;
	}
	else if ((i==7 || i==8) && j==2)
	{  
		resetchessboard();
		lockchessboard = 0;
		return 0;
	}
	else if ((i==7 || i==8) && j==1)
	{
		quit();
		return 0;
	}
	else
	{
		if (!lockchessboard)
		{
			if ((i>=0 && i<=5 && j>=0 && j<=5 && (mmsg.x-RESETX)>0 && -(mmsg.y-RESETY)>0))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
}

// �򿪲���
void open()
{
	setfillcolor(BLACK);
	floodfill(area[i][j].crdld.x, area[i][j].crdld.y, WHITE);

	setaspectratio(1, 1);
	if (area[i][j].chess.team == blue)
	{
		settextcolor(BLUE);
	}
	else if (area[i][j].chess.team == red)
	{
		settextcolor(RED);
	}
	else
	{
		settextcolor(MAGENTA);
	}
	settextstyle(35, 18, "����");
	outtextxy(area[i][j].crdld.x, -area[i][j].crdld.y-CHESIZE+2, area[i][j].chess.image);
	area[i][j].state = exist;
	setaspectratio(1, -1);
}

// �ж��Ƿ����ƶ�
int whemove()
{
	if (area[choose.i][choose.j].chess.id==fei || area[choose.i][choose.j].chess.id==sheng
		|| area[choose.i][choose.j].chess.id==shen)
	{
		if (choose.i==i && abs(choose.j-j)<=5 || choose.j==j && abs(choose.i-i)<=5)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (area[choose.i][choose.j].chess.id == xian)
	{
		return 1;
	}
	else
	{
		if (choose.i==i && abs(choose.j-j)==1 || choose.j==j && abs(choose.i-i)==1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

// �ƶ�
void move()
{
	setfillcolor(BLACK);
	floodfill(area[choose.i][choose.j].crdld.x, area[choose.i][choose.j].crdld.y, GREEN);
	
	setaspectratio(1, 1);
	if (area[choose.i][choose.j].chess.id==gong && area[choose.i][choose.j].chess.scoopc>0)
	{
		if (area[choose.i][choose.j].chess.team == blue)
		{
			settextcolor(LIGHTBLUE);
		}
		else
		{
			settextcolor(LIGHTRED);
		}
	}
	else
	{
		if (user == blue)
		{
			settextcolor(BLUE);
		}
		else 
		{
			settextcolor(RED);
		}
	}
	settextstyle(35, 18, "����");
	outtextxy(area[i][j].crdld.x, -area[i][j].crdld.y-CHESIZE+2, area[choose.i][choose.j].chess.image);

	area[choose.i][choose.j].state = empty;
	area[i][j].state = exist;
	area[i][j].chess = area[choose.i][choose.j].chess;
	setaspectratio(1, -1);
}

// �ж��Ƿ��ܹ����������ع�������
ATTSTYLE  wheattack()                              
{
	if (whemove())
	{
		if (area[choose.i][choose.j].chess.id == gong)
		{
			return judgegong();
		}
		else if (area[choose.i][choose.j].chess.id == zha)
		{
			return judgezha();
		}
		else
		{
			return judgecom();
		}
	}
	else
	{
		return noatt;
	}
			
}

// �жϹ���
ATTSTYLE judgegong()                    
{
	if (area[i][j].chess.team != white)
	{
		if (area[choose.i][choose.j].chess.team != area[i][j].chess.team)
		{
			if (area[i][j].chess.id==gong || area[i][j].chess.id==zha)
			{
				return preatt;
			}
			else if (area[i][j].chess.id == qi)
			{
				if (area[choose.i][choose.j].chess.scoopc == 0)
				{
					return noatt;
				}
				else if (area[choose.i][choose.j].chess.scoopc == 1)
				{
					area[choose.i][choose.j].chess = datachess[14];
					getteam();
					return comatt;
				}
				else if (area[choose.i][choose.j].chess.scoopc == 2)
				{
					area[choose.i][choose.j].chess = datachess[16];
					getteam();
					return comatt;
				}
				else if (area[choose.i][choose.j].chess.scoopc == 3)
				{
					area[choose.i][choose.j].chess = datachess[17];
					getteam();
					return comatt;
				}
				else
				{
					area[choose.i][choose.j].chess = datachess[18];
					getteam();
					return comatt;
				}
			}
			else
			{
				return noatt;
			}
		}
		else
		{
			return noatt;
		}
	}
	else
	{
		if (area[i][j].chess.id == lei)
		{
			area[choose.i][choose.j].chess.scoopc++;
			return comatt;
		}
		else
		{
			change();
			return comatt;
		}
	}
}

// �ж�ը��
ATTSTYLE judgezha()                          
{
	if (area[choose.i][choose.j].chess.team != area[i][j].chess.team)
	{
		if (area[i][j].chess.id != qi)
		{
			return preatt;
		}
		else
		{
			return noatt;
		}
	}
	else
	{
		return noatt;
	}
}

// �ж���ͨ����  
ATTSTYLE judgecom()                    
{
	if (area[i][j].chess.team != white)
	{
		if (area[choose.i][choose.j].chess.team != area[i][j].chess.team)
		{
			if (area[choose.i][choose.j].chess.power==area[i][j].chess.power || area[i][j].chess.id==zha)
			{
				return preatt;
			}
			else if (area[choose.i][choose.j].chess.power > area[i][j].chess.power)
			{
				return comatt;
			}
			else 
			{
				return noatt;
			}
		}
		else
		{
			return noatt;
		}
	}
	else
	{
		if (area[i][j].chess.id == lei)
		{
			return noatt;
		}
		else
		{
			change();
			return comatt;
		}
	}
}

// ����
void change()                              
{
	int x;
	x = rand() % 50;
	if (x == 6)
	{
		area[choose.i][choose.j].chess = datachess[15];
		getteam();
	}
	else
	{
		x = rand() % 4;
		if (x == 3)
		{
			x = rand() % 2;
			if (x == 0)
			{
				area[choose.i][choose.j].chess = datachess[7];
			}
			else
			{
				area[choose.i][choose.j].chess = datachess[8];
			}
			
			getteam();
		}
		else
		{
			x = rand() % 6;
			area[choose.i][choose.j].chess = datachess[x];

			getteam();
		}
	}
}

// ��������������ֵ
void getteam()                       
{
	if (user == blue)
	{
		area[choose.i][choose.j].chess.team = blue;
	}
	else
	{
		area[choose.i][choose.j].chess.team = red;
	}
}

// ɱ���Է�
void kill()                        
{
	move();
}

// ��ɱ
void killself()                     
{
	setfillcolor(BLACK);
	floodfill(area[choose.i][choose.j].crdld.x, area[choose.i][choose.j].crdld.y, GREEN);
	area[choose.i][choose.j].state = empty;
}

// ͬ���ھ�
void perishtogether()              
{
	setfillcolor(BLACK);
	cancelchoose();
	floodfill(area[choose.i][choose.j].crdld.x, area[choose.i][choose.j].crdld.y, WHITE);
	floodfill(area[i][j].crdld.x, area[i][j].crdld.y, WHITE);

	area[choose.i][choose.j].state = empty;
	area[i][j].state = empty;
}

// �л�ִ�巽
void userchange()                    
{
	if (user == blue)
	{
		user = red;
		setfillcolor(RED);
		floodfill(-1, -1, WHITE);
	}
	else
	{
		user = blue;
		setfillcolor(BLUE);
		floodfill(-1, -1, WHITE);
	}
}

// �ж���Ӯ
void judgebunko()                          
{
	int i1, j1;
	int num1 = 0, num2 = 0;

	for (i1=0; i1<6; i1++)
	{
		for (j1=0; j1<6; j1++)
		{
			if (area[i1][j1].state != empty)
			{
				if (area[i1][j1].chess.team==red && area[i1][j1].chess.id!=qi)
				{
					num1++;
				}
				else if(area[i1][j1].chess.team==blue && area[i1][j1].chess.id!=qi)
				{
					num2++;
				}
			}
		}
	}
	
	if (num1==0 && num2!=0)
	{
		bluewin();
	}

	if (num2==0 && num1!=0)
	{
		redwin();
	}
	
	if (num1==0 && num2==0)
	{
		peace();
	}
}

// ����ʤ
void bluewin()                   
{
	setaspectratio(1, 1);
	settextcolor(BLUE);
	settextstyle(50, 20, "����");
	outtextxy(CHESIZE, -CHESIZE*8, "����ʤ��");
	setaspectratio(1, -1);
	setfillcolor(BLUE);
	floodfill(-1, -1, WHITE);

	lockchessboard = 1;              //��������
}

// �췽ʤ
void redwin()                    
{
	setaspectratio(1, 1);
	settextcolor(RED);
	settextstyle(50, 20, "����");
	outtextxy(CHESIZE, -CHESIZE*8, "�췽ʤ��");
	setaspectratio(1, -1);
	setfillcolor(RED);
	floodfill(-1, -1, WHITE);

	lockchessboard = 1;
}

// ����
void peace()                      
{ 
	setaspectratio(1, 1); 
	settextcolor(GREEN);
	settextstyle(50, 20, "����");
	outtextxy(CHESIZE, -CHESIZE*8, "�����Ժ�");
	setaspectratio(1, -1);
	setfillcolor(GREEN);
	floodfill(-1, -1, WHITE);

	lockchessboard = 1;
}

// Ͷ��
void surrender()                   
{
	if (user == blue)
	{
		redwin();
	}
	else
	{
		bluewin();
	}
}

// ����
void resetchessboard()              
{
	cleardevice();
	init();
}

// ��Ϸ˵��
void gamehelp()              
{
	getimage(&image, -10, -10, 500, 350);
	cleardevice();

	setorigin(50, 0);
	setaspectratio(1, 1);

	settextcolor(RED);
	settextstyle(14, 0, "����");
	outtextxy(-50, 0, "ע:�����������ص���Ϸ����");

	settextcolor(WHITE);
	settextstyle(24, 0, "����");
	outtextxy(230, 5, "��Ϸ˵��");
	settextstyle(12, 0, "����");
	outtextxy(0, 35, "���̴�С:6*6;              ��������:36;            �ж�˫��:��,��");
	outtextxy(0, 60, "�������:����(�췽����,14��) ����(��������,14��) ����(������,8��)");
	outtextxy(0, 85, "����(����)����:˾��,����,ʦ��,�ó�,�ų�,Ӫ��,����,�೤,����,����*2,ը��*2.");
	outtextxy(0, 100, "��������:����*4,������*4.  ע:'*'�����ʾ���������,ûע��ֻ��һ��");
	outtextxy(0, 125, "����˵��:1.˾�����,������С,��ĳ�С��,һ����ͬ���ھ�,");
	outtextxy(textwidth("����˵��:1."), 140, "ը����ը����͵з������������е���(ը��Ҳ����ʧ)." );
	outtextxy(textwidth("����˵��:"), 155, "2.�������ڵ���,�����ɿ��Է������(�ڵ���Խ��,��ɵ�����Խ����).");
	outtextxy(textwidth("����˵��:"), 170, "3.������ɳԱ�,�Ժ��ܱ�ɹ���~�����е�һ��,��һ�����ʱ������BOSS.");
	outtextxy(textwidth("����˵��:"), 185, "4.���������ɱ(��һ�β���).");
	outtextxy(textwidth("����˵��:"), 200, "5.ִ�巽������һ����Ч������,�ͻ��Է�ִ��(�߿���ɫ��ǰִ�巽).");
	outtextxy(textwidth("����˵��:"), 215, "6.һ������(�������)ȫ������,������; ͬʱȫ��û��,�����.");
	outtextxy(0, 240, "ִ�巽�ܽ��еĲ���:����1:������(��һ�β���).");
	outtextxy(textwidth("ִ�巽�ܽ��еĲ���:"), 255, "����2:����.");
	outtextxy(textwidth("ִ�巽�ܽ��еĲ���:"), 270, "����3:�ƶ�.");
	outtextxy(textwidth("ִ�巽�ܽ��еĲ���:"), 285, "����4:����(������)����.");
	outtextxy(textwidth("ִ�巽�ܽ��еĲ���:"), 300, "����5:�Ա���.");
	outtextxy(textwidth("ִ�巽�ܽ��еĲ���:"), 315, "����6:��ɱ.");
	outtextxy(0, 340, "ʵʩ��Ϸ����˵��(������):ʵʩ����1:ѡ��Ҫ���������ڵ�����,����.");
	outtextxy(textwidth("ʵʩ��Ϸ����˵��(������):"), 355, "ʵʩ����2~5:����ѡ��������(���ӱ߿�����)");
	outtextxy(textwidth("ʵʩ��Ϸ����˵��(������):ʵʩ����2~5:"), 370, "�ٵ���ѡ�б�����.");
	outtextxy(textwidth("ʵʩ��Ϸ����˵��(������):"), 385, "ʵʩ����6:ѡ�м�������,���������м�.");
	settextcolor(RED);
	outtextxy(textwidth("ʵʩ��Ϸ����˵��(������):"), 400,"ע:Ҫ������������,���ȳ�����ǰѡ��(�����Ҽ�����)");
	settextcolor(WHITE);
	setlinecolor(WHITE);
	line(-30, 420, 570, 420);
	outtextxy(0, 425, "������ȼ�һ��(�ȸ�ɱ��С):��1 ��2 ��3 Ӫ4 ��5 ��6 ʦ7");
	outtextxy(textwidth("������ȼ�һ��(�ȸ�ɱ��С):"), 440, "��8 ��8 ˾9 ��9 ��10 ��10");
	outtextxy(0, 455, "ע:'��' '��' '��' '��' ��Ϊ�������׺�������,'��''��''��'��ֱ�߷�,'��'�������");

	while (true)
	{
		mmsg = GetMouseMsg();

		if (mmsg.uMsg == WM_LBUTTONDOWN)
		{
			break;
		}
	}

	cleardevice();
	setorigin(RESETX, RESETY);
	setaspectratio(1, -1);
	putimage(-10, -10, &image);
}

// �˳���Ϸ
void quit()     
{
	closegraph();
}