#include <iostream>
#include <cmath>
#include <graphics.h>
#include "resource.h"//�Ի�����Դ
using namespace std;

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

enum BLOCK {BORDER=0,EMPTY=1,CC=2,GY=3,ZF=4,ZY=5,MC=6,HZ=7,BING=8}; //ľ��

IMAGE border,empty,cc,gy,zf,zy,mc,hz,bing,buffer(500,350),gameinterface,menuitf,aboutitf,cmapitf,winimg; //ͼƬ

BLOCK map[6][7];//��ͼ

struct BLock//��ṹ��
{
    int x;
    int y;
};

int msmode,mapnum,movenum,lstdir=-3;
char mapname[11];

void about();//������Ϸ
void win();//ʤ��
void game(int mapnum);//���ĺ�����ִ����Ϸ
void menu();//�˵�
void choosemap();//��ͼ�˵�
void draw();//����

//���ڻص�����
BOOL WINAPI HelpDlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)// ���� WM_XX ��Ϣ
    {
		case WM_INITDIALOG:
			return true;

		case WM_COMMAND:
			if((HWND)lParam==GetDlgItem(hWnd,IDC_CLOSE))
			{
				EndDialog(hWnd,1);
			}
    }
    return false;
}

//�жϵ������λ���㷨
bool inrect(int x,int y,int x1,int y1,int w1,int h1)
{
    if(x>=x1&&x<x1+w1&&y>=y1&&y<y1+h1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//���ص�ͼ
void loadmap(int number)
{
    FILE *fp;
    char filename[50];
    sprintf(filename,"�ؿ�\\�ؿ�%d.map",number);
    fp=fopen(filename,"r");
    int i,j;
    for(i=0; i<6; i++)
        for(j=0; j<7; j++)
        {
            map[i][j]=BORDER;
        }

    for(j=0; j<5; j++)
        for(i=0; i<4; i++)
        {
            switch(fgetc(fp))
            {
				case 'E':	map[i+1][j+1]=EMPTY;	break;
				case 'C':	map[i+1][j+1]=CC;		break;
				case 'G':	map[i+1][j+1]=GY;		break;
				case 'Z':	map[i+1][j+1]=ZF;		break;
				case 'z':	map[i+1][j+1]=ZY;		break;
				case 'M':	map[i+1][j+1]=MC;		break;
				case 'H':	map[i+1][j+1]=HZ;		break;
				case 'B':	map[i+1][j+1]=BING;		break;
            }
        }
    fscanf(fp,"%s",mapname);
}

//����ͼƬ
void loadres()
{
    loadimage(&empty,"IMAGE","EMPTY");
    loadimage(&bing,"IMAGE","BING");
    loadimage(&border,"IMAGE","BORDER");
    loadimage(&cc,"IMAGE","CC");
    loadimage(&gy,"IMAGE","GY");
    loadimage(&zf,"IMAGE","ZF");
    loadimage(&zy,"IMAGE","ZY");
    loadimage(&mc,"IMAGE","MC");
    loadimage(&hz,"IMAGE","HZ");
    loadimage(&gameinterface,"IMAGE","GAMEITF");
    loadimage(&menuitf,"IMAGE","MENU");
    loadimage(&cmapitf,"IMAGE","MAPMENU");
    loadimage(&aboutitf,"IMAGE","ABTGAME");
    loadimage(&winimg,"IMAGE","WIN");
}

//Ѱ���廢�Ͻ����ܲٵ�λ��
BLock FindBlock(BLOCK block)
{
    struct BLock Block= {0,0};
    int x,y;
    for(x=0; x<=6;)
    {
        for(y=0; y<=7;)
        {
            if(map[x][y]==block)
            {
                Block.x=x;
                Block.y=y;
                return Block;
            }
            else
            {
                y+=1;
            }
        }
        x+=1;
    }
    return Block;
}

//���ĺ������ƶ�ľ�麯��
bool move(BLOCK block,int dx,int dy)
{
    bool win=false,moved=false;

	//��
    if(msmode>10)
    {
        if(map[msmode/10+dx][msmode%10+dy]==EMPTY)
        {
            map[msmode/10][msmode%10]=EMPTY;
            map[msmode/10+dx][msmode%10+dy]=BING;
            msmode+=dx*10+dy;
            moved=true;
        }
    }

    //���ŵĽ�
    if(block>GY&&block<BING)
    {
        BLock blk;
        blk=FindBlock(block);
        if(dx!=0)
        {
            if(map[blk.x+dx][blk.y]==EMPTY&&map[blk.x+dx][blk.y+1]==EMPTY)
            {
                map[blk.x][blk.y]=EMPTY;
                map[blk.x][blk.y+1]=EMPTY;
                map[blk.x+dx][blk.y]=block;
                map[blk.x+dx][blk.y+1]=block;
                moved=true;
            }
        }
        if(dy==1)
        {
            if(map[blk.x][blk.y+2]==EMPTY)
            {
                map[blk.x][blk.y]=EMPTY;
                map[blk.x][blk.y+2]=block;
                moved=true;
            }
        }
        if(dy==-1)
        {
            if(map[blk.x][blk.y-1]==EMPTY)
            {
                map[blk.x][blk.y+1]=EMPTY;
                map[blk.x][blk.y-1]=block;
                moved=true;
            }
        }
    }

    //����
    if(block==GY)
    {
        BLock blk2;
        blk2=FindBlock(block);
        if(dy!=0)
        {
            if(map[blk2.x][blk2.y+dy]==EMPTY&&map[blk2.x+1][blk2.y+dy]==EMPTY)
            {
                map[blk2.x][blk2.y]=EMPTY;
                map[blk2.x+1][blk2.y]=EMPTY;
                map[blk2.x][blk2.y+dy]=GY;
                map[blk2.x+1][blk2.y+dy]=GY;
                moved=true;
            }
        }
        if(dx==1)
        {
            if(map[blk2.x+2][blk2.y]==EMPTY)
            {
                map[blk2.x+2][blk2.y]=GY;
                map[blk2.x][blk2.y]=EMPTY;
                moved=true;
            }
        }
        if(dx==-1)
        {
            if(map[blk2.x-1][blk2.y]==EMPTY)
            {
                map[blk2.x-1][blk2.y]=GY;
                map[blk2.x+1][blk2.y]=EMPTY;
                moved=true;
            }
        }
    }

    //�ܲ�
    if(block==CC)
    {
        BLock blk3;
        blk3=FindBlock(block);
        if(dx==1)
        {
            if(map[blk3.x+2][blk3.y]==EMPTY&&map[blk3.x+2][blk3.y+1]==EMPTY)
            {
                map[blk3.x+2][blk3.y]=CC;
                map[blk3.x+2][blk3.y+1]=CC;
                map[blk3.x][blk3.y]=EMPTY;
                map[blk3.x][blk3.y+1]=EMPTY;
                moved=true;
            }
        }
        if(dx==-1)
        {
            if(map[blk3.x-1][blk3.y]==EMPTY&&map[blk3.x-1][blk3.y+1]==EMPTY)
            {
                map[blk3.x-1][blk3.y]=CC;
                map[blk3.x-1][blk3.y+1]=CC;
                map[blk3.x+1][blk3.y]=EMPTY;
                map[blk3.x+1][blk3.y+1]=EMPTY;
                moved=true;
            }
        }
        if(dy==1)
        {
            if(blk3.x==2&&blk3.y==4)
            {
                win=true;
            }
            else if(map[blk3.x][blk3.y+2]==EMPTY&&map[blk3.x+1][blk3.y+2]==EMPTY)
            {
                map[blk3.x][blk3.y+2]=CC;
                map[blk3.x+1][blk3.y+2]=CC;
                map[blk3.x][blk3.y]=EMPTY;
                map[blk3.x+1][blk3.y]=EMPTY;
                moved=true;
            }
        }
        if(dy==-1)
        {
            if(map[blk3.x][blk3.y-1]==EMPTY&&map[blk3.x+1][blk3.y-1]==EMPTY)
            {
                map[blk3.x][blk3.y-1]=CC;
                map[blk3.x+1][blk3.y-1]=CC;
                map[blk3.x][blk3.y+1]=EMPTY;
                map[blk3.x+1][blk3.y+1]=EMPTY;
                moved=true;
            }
        }
    }

	//�ƶ��ɹ�����
    if(moved)
    {
        lstdir=dx*2+dy;
    }

    return win;
}

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	//��ֹ����Ϸͬʱ����
    if(FindWindow(NULL,"���ݵ�������ȱ�д")!=NULL)
    {
        exit(0);
    }
    loadres();
    initgraph(500,350);
	//�޸ı���
    SetWindowText(GetHWnd(),"���ݵ�������ȱ�д");
    menu();
    return 0;
}

//��Ϸ����
void game(int mapnum)
{
    loadmap(mapnum);
    MOUSEMSG msg;
    int pmx,pmy;
    while(true)
    {
        while(MouseHit())
        {
            msg=GetMouseMsg();
            if(msg.uMsg==WM_LBUTTONDOWN)//����ʱ
            {
				//����Ϸ��
                if(msg.x<250&&msg.x>=50&&msg.y>=50&&msg.y<300)
                {
					//��¼�¿�ʼ���µ�����
                    pmx=msg.x;
                    pmy=msg.y;
                    if(map[msg.x/50][msg.y/50]!=EMPTY&&map[msg.x/50][msg.y/50]!=BING)//���֮ǰûѡ�й�
                    {
                        msmode=map[msg.x/50][msg.y/50];
                    }
                    else if(map[msg.x/50][msg.y/50]==BING)//ѡ�б�
                    {
                        msmode=msg.x/50*10+msg.y/50;
                    }
                }
                else if(inrect(msg.x,msg.y,350,225,50,50))//��ѡ��ͼ
                {
                    msmode=0;
                    mapnum=0;
                    lstdir=-3;
                    *mapname=NULL;
                    choosemap();
                }
                else if(inrect(msg.x,msg.y,425,225,50,50))//������Ϸ
                {
                    msmode=0;
                    lstdir=-3;
                    loadmap(mapnum);
                }
                else if(inrect(msg.x,msg.y,350,150,50,50))//����һ��
                {
                    switch(lstdir)//�����ϴε��ƶ�����
                    {
						case -3:
							break;
						case 1:
						{
							move((BLOCK)msmode,0,-1);
							break;
						}
						case 2:
						{
							move((BLOCK)msmode,-1,0);
							break;
						}
						case -1:
						{
							move((BLOCK)msmode,1,0);
							break;
						}
						case -2:
						{
							move((BLOCK)msmode,1,0);
							break;
						}
                    }
                    msmode=0;
                }
                else if(inrect(msg.x,msg.y,425,150,50,50))//��Ϸ����
                {
					//����Դ�ﴴ������
                    DialogBox(GetModuleHandle(0),MAKEINTRESOURCE(HELPDLG),GetHWnd(),HelpDlg_Proc);
                }
            }
            else if(msg.uMsg==WM_LBUTTONUP)//��굯��
            {
				//��������϶��켣�ƶ�

				//���Ҷ�
                if(abs(msg.x-pmx)>=abs(msg.y-pmy)&&abs(msg.x-pmx)>30)
                {
                    if(msg.x-pmx>0)
                    {
                        move((BLOCK)msmode,1,0);
                    }
                    else
                    {
                        move((BLOCK)msmode,-1,0);
                    }
                }
                
				//���¶�
                if(abs(msg.x-pmx)<abs(msg.y-pmy)&&abs(msg.y-pmy)>30)
                {
                    if(msg.y-pmy>0)
                    {
                        move((BLOCK)msmode,0,1);
                    }
                    else
                    {
                        move((BLOCK)msmode,0,-1);
                    }
                }
            }
        }
		//��
        draw();
    }
}

//������Ϸ
void about()
{
    MOUSEMSG msg;
    putimage(0,0,&aboutitf);
    while(true)
    {
        if(MouseHit())
        {
            msg=GetMouseMsg();
            if(msg.uMsg==WM_LBUTTONDOWN)
            {
                if(msg.x>=450&&msg.x<=490&&msg.y>=300&&msg.y<=340)
                {
                    menu();
                }
            }
        }
    }
}

//ʤ��
void win()
{
    putimage(0,0,&winimg);
    msmode=0;
    Sleep(2000);
	//ʤ��������ѡ��ͼ
    choosemap();
}

//ѡ��ͼ
void choosemap()
{
    MOUSEMSG msg;
    putimage(0,0,&cmapitf);
    int x,y;
    while(true)
    {
        while(MouseHit())
        {
            msg=GetMouseMsg();
            if(msg.uMsg==WM_LBUTTONDOWN)
            {
                for(y=0; y<3; y++)
                    for(x=0; x<4; x++)
                    {
                        if(msg.x>=x*125+30&&msg.x<=x*125+100&&msg.y<=y*70+90&&msg.y>=y*70+60)
                        {
							//��ͼ��
                            mapnum=y*4+x+1;
							//ִ����Ϸ
                            game(mapnum);
                        }
                    }
                if(msg.x>=450&&msg.x<=490&&msg.y>=300&&msg.y<=340)
                {
					//���ز˵�
                    menu();    
                }
            }
        }
    }
}

//�˵�
void menu()
{
    MOUSEMSG mmsg;
    putimage(0,0,&menuitf);
    while(true)
    {
        while(MouseHit())
        {
            mmsg=GetMouseMsg();
            if(mmsg.uMsg==WM_LBUTTONDOWN)
            {
                if(mmsg.x>=150&&mmsg.x<=350)
                {
                    if(mmsg.y>=125&&mmsg.y<=175)
                    {
						//ѡ��ͼ
                        choosemap();   
                    }
                    if(mmsg.y>=225&&mmsg.y<=275)
                    {
						//������Ϸ
                        about();    
                    }
                }
            }
        }
    }
}

//ÿһ֡�Ļ���
void draw()
{
    int i,j;
    BLock BLOCK1;
    SetWorkingImage(&buffer);
    putimage(300,0,&gameinterface);

    //����������
    for(i=0; i<6; i++)
        for(j=0; j<7; j++)
        {
            if(map[i][j]==BORDER)
            {
                putimage(i*50,j*50,&border);
            }
            if(map[i][j]==EMPTY)
            {
                putimage(i*50,j*50,&empty);
            }
            if(map[i][j]==BING)
            {
                putimage(i*50,j*50,&bing);
            }
        }

    //��ÿ��ľ�黭һ��
    BLOCK1=FindBlock(CC);
    putimage(BLOCK1.x*50,BLOCK1.y*50,&cc);
    BLOCK1=FindBlock(GY);
    putimage(BLOCK1.x*50,BLOCK1.y*50,&gy);
    BLOCK1=FindBlock(ZF);
    putimage(BLOCK1.x*50,BLOCK1.y*50,&zf);
    BLOCK1=FindBlock(ZY);
    putimage(BLOCK1.x*50,BLOCK1.y*50,&zy);
    BLOCK1=FindBlock(MC);
    putimage(BLOCK1.x*50,BLOCK1.y*50,&mc);
    BLOCK1=FindBlock(HZ);
    putimage(BLOCK1.x*50,BLOCK1.y*50,&hz);

    //�����ںͻ��ݵ�
    putimage(100,300,&empty);
    putimage(150,300,&empty);
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(50,0,"����");
    outtextxy(100,300,"����");
    settextstyle(50,0,"����");
    outtextxy(150-textwidth("���ݵ�")/2,0,"���ݵ�");
	//д�ؿ����Ʊ��
    settextstyle(40,0,"����");
    char mapnumtxt[9];
    sprintf(mapnumtxt,"��%d��",mapnum);
    outtextxy(320,70,mapnumtxt);
    outtextxy(320,110,mapname);
    SetWorkingImage();
    putimage(0,0,&buffer);
}
