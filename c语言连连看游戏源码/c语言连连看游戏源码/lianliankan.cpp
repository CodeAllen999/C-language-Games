#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#pragma comment(lib,"winmm.lib")

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

//150  150  12  7  21  ��
//60   100  16  9  32  ��
//100  120  14  8  28  ��
#define leftedge  150         //��Ϸ������߿����
#define topedge   150         //��Ϸ�����ϱ߿����
#define COL       12          //��Ϸ������
#define ROW       7           //��Ϸ������
#define GridNum	  21          //��ϷͼƬ��Ŀ

#define GridW	  42          //��ϷͼƬ�ĳ�
#define GridH	  48          //��ϷͼƬ�Ŀ�
#define N         555		  //������С(��) 
#define M         785		  //������С(��)

IMAGE image[GridNum + 1][2];	 //ͼƬ��
IMAGE image2;                    //���ͼƬ
int   GridID[ROW + 2][COL + 2];  //��Ϸͼֽ
MOUSEMSG mouse;                  //��¼�����Ϣ

struct GridInfor        //�������ͼƬ��Ϣ
{
	int idx,idy;        //ͼֽ����
	int leftx,lefty;	//��Ļ����
	int GridID;         //ͼƬ����
}pre,cur,dur;

struct                  //��¼���ߵ�
{
	int x;
	int y;
}point[4]; 
static int pn;          //��¼���ߵ����

void InitFace ();													//��ʼ������
void Shuffle  ();													//�漴����ͼƬ
void ShowGrid ();													//��ʾͼƬ
void RandGrid ();													//���Ƶ�ͼ
void Link     ();                                                   //������ͼ
void Des_direct ();                                                 //ֱ������
void Des_one_corner();                                              //һ������
void Des_two_corner();                                              //��������
void Load_picture ();												//����ͼƬ
void Init_Grid (GridInfor& pre);									//��ʼ��������Ϣ
void Leftbottondown (MOUSEMSG mouse);								//ʵ��������Ч��
void Draw_frame (int leftx,int lefty);								//���Ʊ߿�
void Mousemove (int leftx,int lefty);								//ʵ������ƶ�Ч��
bool Judg_val (int leftx,int lefty);								//�ж�����Ƿ�����Ϸ��
void SeleReact (int leftx,int lefty);								//��ʾѡ��Ч��
void TranstoPhycoor (int* idx,int* idy);							//ͼֽ����ת��Ϊ��Ļ����
void GridPhy_coor (int& leftx,int& lefty);							//�淶��������
void iPaint (long x1,long y1,long x2,long y2);                      //��ֱ������
void DrawLine (int x1,int y1,int x2,int y2) ;                       //��ֱ��������ͼ
bool DesGrid (GridInfor pre,GridInfor cur);							//�ж������Ƿ�������
bool Match_direct (POINT ppre,POINT pcur);							//�ж������Ƿ��ܹ�ֱ������
bool Match_one_corner (POINT ppre,POINT pcur);						//�ж������Ƿ���һ������
bool Match_two_corner (POINT ppre,POINT pcur);						//�ж������Ƿ�����������
void ExchaVal (GridInfor& pre,GridInfor& cur);						//����ͼƬ��Ϣ
bool Single_click_judge (int mousex,int mousey);                    //�жϵ����Ƿ���Ч	
void RecordInfor (int leftx,int lefty,GridInfor &grid);				//��¼ѡ�е���Ϣ
void TranstoDracoor (int mousex,int mousey,int *idx,int *idy);		//�������ת��Ϊͼֽ����
void Explot (POINT point,int *left,int *right,int *top,int *bottel);//̽��point�㸽���Ŀ�λ��

void main()
{
	initgraph(M,N);
	mciSendString("play game_begin.mp3 repeat", NULL, 0, NULL); 
	InitFace();
	while(1)
	{	
		mouse = GetMouseMsg();	
		switch(mouse.uMsg)
		{
		case WM_MOUSEMOVE:
			Mousemove(mouse.x,mouse.y);  break;
		case WM_LBUTTONDOWN:
			if(Single_click_judge(mouse.x,mouse.y))
			{
				Leftbottondown(mouse);
			}						  	 break;
		default:						 break;
		}
	}
	closegraph();
}

////////////////////////////////////////���ɲ���//////////////////////////////
void RandGrid()										//����ͼƬ�ı��
{
	for(int iCount = 0, x = 1; x <= ROW; ++x )
	{
		for( int y = 1; y <= COL; ++y )
		{
			GridID[x][y] =  iCount++ % GridNum + 1;
}	}   }

void Shuffle(  )									//��������
{
	int ix, iy, jx, jy, grid;
	for( int k = 0; k < 84; ++k )
	{
		ix = rand() % ROW + 1;	// ���� 1 - COL �������
		iy = rand() % COL + 1;	// ���� 1 - ROW �������
		jx = rand() % ROW + 1;  // ���� 1 - COL �������
		jy = rand() % COL + 1;	// ���� 1 - ROW �������
		if( GridID[ix][iy] != GridID[jx][jy] )  //�������Ⱦͽ�������
		{
			grid = GridID[ix][iy];
			GridID[ix][iy] = GridID[jx][jy];
			GridID[jx][jy] = grid;
}	}	}

////////////////////////////////��ʼ������///////////////////////////////////////
void InitFace()  
{
	srand((unsigned)time(NULL));
	Load_picture();
    RandGrid();
	IMAGE image3;
	loadimage(&image3,"res\\bg.bmp");
	putimage(0,0,&image3);
	getimage(&image2,3 * 42,2 * 48,42, 48);
    Shuffle();
    ShowGrid();	
}

void Load_picture()									//����ͼƬ
{
	IMAGE image1,background;
	loadimage(&image1,"IMAGE","grids");	
 	SetWorkingImage(&image1);
	for(int i = 1 ;i < GridNum + 1 ;i ++)	
		for(int j = 0;j < 2;j++)
			getimage(&image[i][j],j * 42,i * 48,42, 48);
	loadimage(&background,"IMAGE","bg");
	SetWorkingImage(&background);
	getimage(&image2,3 * 42,2 * 48,42, 48);
	SetWorkingImage();
	putimage(0,0,&background);
}

void ShowGrid()
{
	int idx,idy;
	for(int i = 0 ;i < ROW; i ++)
		for(int j = 0 ;j < COL ; j++)
		{
			idy = i * 48 + topedge ,idx = j * 42 + leftedge;
			putimage(idx,idy,&image[GridID[i + 1][j + 1]][0]);			
}		}

/////////////////////////////////������////////////////////////////////////////
void Mousemove (int leftx,int lefty)					//����ƶ�ʱ�ı仯
{
 	static int prex,prey,preidx,preidy,  curidx,curidy;
	if(Judg_val(leftx,lefty))
	{	
		TranstoDracoor(leftx,lefty,&curidx,&curidy);  //ת��Ϊͼֽ����
		if(GridID[curidy][curidx] != 0)
		{	
			GridPhy_coor(leftx,lefty);
			if(pre.idx == preidx && pre.idy == preidy)
				putimage(prex,prey,&image[GridID[preidy][preidx]][1]);
			else
				putimage(prex,prey,&image[GridID[preidy][preidx]][0]);
			prex = leftx,  		prey = lefty;
			preidx = curidx,    preidy = curidy;
            Draw_frame(leftx,lefty);					//���Ʊ߿�	
}	}  }	

void Leftbottondown (MOUSEMSG mouse)					//���ʱ�ı仯
{
	static int click = 0,  idx,idy;
	click++;
	SeleReact (mouse.x,mouse.y);						//��ʾѡ��Ч�� 
	if(click == 1)		RecordInfor(mouse.x,mouse.y,pre);
	if(click == 2) 
	{	
		TranstoDracoor (mouse.x,mouse.y,&idx,&idy);
		if(idx != pre.idx || idy != pre.idy)
		{
			RecordInfor (mouse.x,mouse.y,cur);
			if(pre.GridID == cur.GridID && 	DesGrid(pre,cur))
			{
				GridID[pre.idy][pre.idx] = GridID[cur.idy][cur.idx] =0;
				Link ();    pn = 0;
				putimage(pre.leftx,pre.lefty,&image2);
				putimage(cur.leftx,cur.lefty,&image2);
				Init_Grid(pre);   Init_Grid(cur);    click = 0;
			}
			else
			{
				ExchaVal(dur,pre);  	ExchaVal(pre,cur);   
				Init_Grid(cur);			click = 1;
				putimage(dur.leftx,dur.lefty,&image[GridID[dur.idy][dur.idx]][0]);
		}	}
		else  click = 1;	
}		}

void SeleReact (int leftx,int lefty)							//ѡ��ʱЧ��
{	
	if(Judg_val(leftx,lefty))
	{
		int idx,idy;
		TranstoDracoor (leftx,lefty,&idx,&idy);
		GridPhy_coor (leftx,lefty);
		putimage(leftx,lefty,&image[GridID[idy][idx]][1]);
}	}

bool Judg_val(int leftx,int lefty)					           //�ж�����Ƿ�����Ϸ��
{	
	return leftx > leftedge && leftx < leftedge + GridW * COL && 
	       lefty > topedge  &&  lefty < topedge + GridH * ROW;
}

void TranstoDracoor (int mousex,int mousey ,int *idx,int *idy) //�������ת��Ϊͼֽ����
{
	if(Judg_val(mousex,mousey))
	{	
		*idx = (mousex - leftedge) / 42 + 1;
		*idy = (mousey - topedge) / 48 + 1 ;
}	}

void RecordInfor(int leftx,int lefty,GridInfor &grid)			//��¼ѡ�е���Ϣ
{
	TranstoDracoor(leftx,lefty,&grid.idx,&grid.idy);
	grid.leftx = (grid.idx - 1) * 42 + leftedge;
	grid.lefty = (grid.idy - 1) * 48 + topedge;
	grid.GridID = GridID[grid.idy][grid.idx];
}

bool Single_click_judge (int mousex,int mousey)			//�жϵ����Ƿ���Ч
{
	int idx,idy;
	TranstoDracoor (mousex,mousey,&idx,&idy);			//ת��Ϊͼֽ����
	if(Judg_val(mouse.x,mouse.y) && GridID[idy][idx] != 0)
		return true;
	return false;
}

void Draw_frame(int leftx,int lefty)				//���Ʒ���
{
	setcolor(RGB(126,91,68));
	setlinestyle(PS_SOLID,NULL,1);
	rectangle(leftx,lefty,leftx+41,lefty+47);
	rectangle(leftx + 2,lefty + 2,leftx+39,lefty+45);
	setcolor(RGB(250,230,169));
	rectangle(leftx + 1,lefty + 1,leftx+40,lefty+46);	
}

////////////////////////////////�ж���������/////////////////////////////////////
bool DesGrid (GridInfor pre,GridInfor cur)						//�ж������Ƿ�������
{
	bool match = false; POINT ppre,pcur; 
	ppre.x = pre.idx; ppre.y = pre.idy;  
	pcur.x = cur.idx; pcur.y = cur.idy;
	if(Match_direct(ppre,pcur)) match = true;   
	else if(Match_one_corner(ppre,pcur)) match = true;
	else if(Match_two_corner(ppre,pcur)) match =true;
	return match;
}

bool Match_direct(POINT ppre,POINT pcur)						//�ж������Ƿ��ܹ�ֱ������
{
	int k,t;
	if(ppre.x == pcur.x)
	{	
		k = ppre.y > pcur.y ? ppre.y : pcur.y;
		t = ppre.y < pcur.y ? ppre.y : pcur.y;
		if(t + 1 == k)  goto FIND;
		for(int i = t + 1;i < k ;i++)
			if(GridID[i][ppre.x] != 0)    return false;
		if(i == k)      goto FIND;
	}
	else 
		if(ppre.y == pcur.y)
		{	
			k = ppre.x > pcur.x ? ppre.x : pcur.x;
			t = ppre.x < pcur.x ? ppre.x : pcur.x;
			if(t + 1 == k)  goto FIND;
			for(int i = t + 1;i < k ;i++)
				if(GridID[ppre.y][i] != 0) return false;
			if(i == k)      goto FIND;
		}
		return false;
FIND:	point[pn].x = pcur.x,  point[pn].y = pcur.y;    pn++;
		point[pn].x = ppre.x,  point[pn].y = ppre.y;	pn++; 
		return true;
}

bool Match_one_corner(POINT ppre,POINT pcur)					//�ж������Ƿ���һ������
{
	int left,right,top,bottel,x = ppre.x,y = ppre.y;
	Explot(ppre,&left,&right,&top,&bottel);
	ppre.y = top - 1;
RESEARCHX:	if(ppre.y < bottel)		ppre.y++;
			else goto BACK;
			if(Match_direct(ppre,pcur)) goto FIND;
			else goto RESEARCHX;
BACK:		ppre.y = y; ppre.x = left - 1;
RESEARCHY:  if(ppre.x < right)     ppre.x++;
			else goto REBACK;
			if(Match_direct(ppre,pcur)) goto FIND;
			else goto RESEARCHY;
REBACK:     pn = 0; return false;
FIND:       point[pn].x = x,point[pn].y = y,pn++;
			return true;
}

bool Match_two_corner(POINT ppre,POINT pcur)					//�ж������Ƿ�����������
{
	int left,right,top,bottel,x = ppre.x,y = ppre.y;
	Explot(ppre,&left,&right,&top,&bottel);
	ppre.y = top - 1;
RESEARCHX:	if(ppre.y < bottel)		ppre.y++;
			else goto BACK;
			if(Match_one_corner(ppre,pcur)) goto FIND;
			else goto RESEARCHX;
BACK:		ppre.y = y; ppre.x = left - 1;
RESEARCHY:  if(ppre.x < right)     ppre.x++;
			else goto REBACK;
			if(Match_one_corner(ppre,pcur)) goto FIND;
			else goto RESEARCHY;
REBACK:     pn = 0;return false;
FIND:		point[pn].x = x,point[pn].y = y,pn++;
			return true;
}

void Explot(POINT point,int *left,int *right,int *top,int *bottel)
{
	int x = point.x,y = point.y;	x++;
	while(x <= COL + 1 &&  GridID[y][x] == 0)  x++;	  *right = x - 1;  x = point.x; x--;
	while(x >= 0	   &&  GridID[y][x] == 0)  x--;   *left	 = x + 1;  x = point.x; y++;
	while(y <= ROW + 1 &&  GridID[y][x] == 0)  y++;   *bottel= y - 1;  y = point.y; y--;
	while(y >= 0	   &&  GridID[y][x] == 0)  y--;   *top   = y + 1;  
}

/////////////////////////////////��������////////////////////////////////////////
void Link ()
{
	switch(pn)
	{
	case 2:
		Des_direct();	    break;
	case 3:
		Des_one_corner();	break;
	case 4:
		Des_two_corner();   break;
	default : break;
}	}

void Des_direct ()
{
	TranstoPhycoor(&point[0].x,&point[0].y);
	TranstoPhycoor(&point[1].x,&point[1].y);
	DrawLine(point[0].x,point[0].y,point[1].x,point[1].y);
	Sleep(250);
	iPaint(point[0].x,point[0].y,point[1].x,point[1].y);
}

void Des_one_corner()
{
	TranstoPhycoor(&point[0].x,&point[0].y);
	TranstoPhycoor(&point[1].x,&point[1].y);
	TranstoPhycoor(&point[2].x,&point[2].y);
	DrawLine(point[0].x,point[0].y,point[1].x,point[1].y);
	DrawLine(point[1].x,point[1].y,point[2].x,point[2].y);
	Sleep(250);
	iPaint(point[0].x,point[0].y,point[1].x,point[1].y);
	iPaint(point[1].x,point[1].y,point[2].x,point[2].y);
}

void Des_two_corner()
{
	TranstoPhycoor(&point[0].x,&point[0].y);
	TranstoPhycoor(&point[1].x,&point[1].y);
	TranstoPhycoor(&point[2].x,&point[2].y);
	TranstoPhycoor(&point[3].x,&point[3].y);
	DrawLine(point[0].x,point[0].y,point[1].x,point[1].y);
	DrawLine(point[1].x,point[1].y,point[2].x,point[2].y);
	DrawLine(point[2].x,point[2].y,point[3].x,point[3].y);
	Sleep(250);
	iPaint(point[0].x,point[0].y,point[1].x,point[1].y);
	iPaint(point[1].x,point[1].y,point[2].x,point[2].y);
	iPaint(point[2].x,point[2].y,point[3].x,point[3].y);
}
	
void DrawLine (int x1,int y1,int x2,int y2)
{
	setlinestyle(PS_SOLID,NULL,3);
	setcolor(RGB(90,43,9));
	line(x1 + 21,y1 + 24,x2 + 21,y2 + 24);
}

void iPaint (long x1,long y1,long x2,long y2)      
{   
	int minx,miny,maxx,maxy;
	if(x1 == x2)
	{
		maxy = y1 > y2? y1:y2;
		miny = y1 < y2? y1:y2;
		for(int i = miny; i <= maxy;i += 48)
			putimage(x1,i,&image2);
	}		
	else if(y1 == y2)
	{
		maxx = x1 > x2? x1:x2;
		minx = x1 < x2? x1:x2;
		for(int j = minx; j <= maxx;j += 42 )
			putimage(j,y1,&image2);
}	}

/////////////////////////////////////////////////////////////////////////////////

void GridPhy_coor(int& leftx,int& lefty)			//ת��Ϊ��׼��������
{
	leftx = ((leftx - leftedge) / 42) * 42 + leftedge;
	lefty = ((lefty - topedge) / 48) * 48 + topedge;
}

void ExchaVal(GridInfor& pre,GridInfor& cur)		//����������Ϣ
{
	pre.GridID = cur.GridID;
	pre.idx = cur.idx;pre.idy = cur.idy;
	pre.leftx = cur.leftx;pre.lefty = cur.lefty;
}

void Init_Grid(GridInfor& grid)                     //��ʼ������
{
	grid.GridID = 0;
	grid.idx	= 0;    grid.idy   = 0;
	grid.leftx  = 0;    grid.lefty = 0;
}

void TranstoPhycoor (int* idx,int* idy)		   //ͼֽ����ת��Ϊ��Ļ����
{   
	int x ,y;x =*idx,y = *idy;
	*idy = (y - 1) * 48 + leftedge;
	*idx = (x - 1) * 42 + topedge;
}

///////////////////////////////////end//////////////////////////////////////////