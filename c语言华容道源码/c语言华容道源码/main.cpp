#include <iostream>
#include <cmath>
#include <graphics.h>
#include "resource.h"//对话框资源
using namespace std;

/* 【自学去】网站收集 http://www.zixue7.com */

enum BLOCK {BORDER=0,EMPTY=1,CC=2,GY=3,ZF=4,ZY=5,MC=6,HZ=7,BING=8}; //木块

IMAGE border,empty,cc,gy,zf,zy,mc,hz,bing,buffer(500,350),gameinterface,menuitf,aboutitf,cmapitf,winimg; //图片

BLOCK map[6][7];//地图

struct BLock//点结构体
{
    int x;
    int y;
};

int msmode,mapnum,movenum,lstdir=-3;
char mapname[11];

void about();//关于游戏
void win();//胜利
void game(int mapnum);//核心函数：执行游戏
void menu();//菜单
void choosemap();//地图菜单
void draw();//绘制

//窗口回调函数
BOOL WINAPI HelpDlg_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)// 处理 WM_XX 消息
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

//判断点与矩形位置算法
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

//加载地图
void loadmap(int number)
{
    FILE *fp;
    char filename[50];
    sprintf(filename,"关卡\\关卡%d.map",number);
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

//加载图片
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

//寻找五虎上将，曹操的位置
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

//核心函数：移动木块函数
bool move(BLOCK block,int dx,int dy)
{
    bool win=false,moved=false;

	//兵
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

    //竖着的将
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

    //关羽
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

    //曹操
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

	//移动成功处理
    if(moved)
    {
        lstdir=dx*2+dy;
    }

    return win;
}

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	//禁止本游戏同时运行
    if(FindWindow(NULL,"华容道——左慈编写")!=NULL)
    {
        exit(0);
    }
    loadres();
    initgraph(500,350);
	//修改标题
    SetWindowText(GetHWnd(),"华容道——左慈编写");
    menu();
    return 0;
}

//游戏函数
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
            if(msg.uMsg==WM_LBUTTONDOWN)//按下时
            {
				//在游戏区
                if(msg.x<250&&msg.x>=50&&msg.y>=50&&msg.y<300)
                {
					//记录下开始按下的坐标
                    pmx=msg.x;
                    pmy=msg.y;
                    if(map[msg.x/50][msg.y/50]!=EMPTY&&map[msg.x/50][msg.y/50]!=BING)//鼠标之前没选中过
                    {
                        msmode=map[msg.x/50][msg.y/50];
                    }
                    else if(map[msg.x/50][msg.y/50]==BING)//选中兵
                    {
                        msmode=msg.x/50*10+msg.y/50;
                    }
                }
                else if(inrect(msg.x,msg.y,350,225,50,50))//重选地图
                {
                    msmode=0;
                    mapnum=0;
                    lstdir=-3;
                    *mapname=NULL;
                    choosemap();
                }
                else if(inrect(msg.x,msg.y,425,225,50,50))//重置游戏
                {
                    msmode=0;
                    lstdir=-3;
                    loadmap(mapnum);
                }
                else if(inrect(msg.x,msg.y,350,150,50,50))//后退一步
                {
                    switch(lstdir)//根据上次的移动后退
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
                else if(inrect(msg.x,msg.y,425,150,50,50))//游戏帮助
                {
					//从资源里创建窗口
                    DialogBox(GetModuleHandle(0),MAKEINTRESOURCE(HELPDLG),GetHWnd(),HelpDlg_Proc);
                }
            }
            else if(msg.uMsg==WM_LBUTTONUP)//鼠标弹起
            {
				//根据鼠标拖动轨迹移动

				//左右动
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
                
				//上下动
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
		//画
        draw();
    }
}

//关于游戏
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

//胜利
void win()
{
    putimage(0,0,&winimg);
    msmode=0;
    Sleep(2000);
	//胜利后重新选地图
    choosemap();
}

//选地图
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
							//地图号
                            mapnum=y*4+x+1;
							//执行游戏
                            game(mapnum);
                        }
                    }
                if(msg.x>=450&&msg.x<=490&&msg.y>=300&&msg.y<=340)
                {
					//返回菜单
                    menu();    
                }
            }
        }
    }
}

//菜单
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
						//选地图
                        choosemap();   
                    }
                    if(mmsg.y>=225&&mmsg.y<=275)
                    {
						//关于游戏
                        about();    
                    }
                }
            }
        }
    }
}

//每一帧的绘制
void draw()
{
    int i,j;
    BLock BLOCK1;
    SetWorkingImage(&buffer);
    putimage(300,0,&gameinterface);

    //画兵，方格
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

    //把每个木块画一遍
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

    //画出口和华容道
    putimage(100,300,&empty);
    putimage(150,300,&empty);
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(50,0,"宋体");
    outtextxy(100,300,"出口");
    settextstyle(50,0,"楷体");
    outtextxy(150-textwidth("华容道")/2,0,"华容道");
	//写关卡名称编号
    settextstyle(40,0,"宋体");
    char mapnumtxt[9];
    sprintf(mapnumtxt,"第%d关",mapnum);
    outtextxy(320,70,mapnumtxt);
    outtextxy(320,110,mapname);
    SetWorkingImage();
    putimage(0,0,&buffer);
}
