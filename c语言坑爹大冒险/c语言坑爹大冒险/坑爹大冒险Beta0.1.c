#include<conio.h>
#include<windows.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

/* 【自学去】网站收集 http://www.zixue7.com */

struct player
{
	char name[10];
	int power,speed,wisdom;
	int att,def;
	int HPmax,HP;
	float burst,dodge;
	int EXP,EXPmax,LV,spot;
}player1;
struct monster
{
	char name[10];
	int HP;
	int att,def;
	int	EXP;
	float burst,dodge;
}monster1;
main()
{
	int i=1,j=0,m=28,n=12;
	char c1;
	void play1();
	int bug1(int sli);
	void help();
	void HideCursor();
	void gotoxy(int x,int y);
	void start();
	void wait();
    void initp1();
	void initm1();
	void boundary();
	void play();
	void addspot();
	void sure();
	void p1order();
	void p1die();
S:	m=28,n=12;
	start();
	system("color 2B");
	HideCursor();
	gotoxy(m,n);
    while(1)//{gotoxy(28,12);}
	{
		
		c1=getch();
		switch(c1)
		{
		case'w':
		case'W':
			printf("  ");
			n-=3;
			if(n<12)n=18;
			gotoxy(m,n);
			printf("★");
			gotoxy(m-1,n);
			break;
		case's':
		case'S':
   			printf("  ");
			n+=3;
			if(n>18)n=12;
			gotoxy(m,n);
			printf("★");
			gotoxy(m-1,n);
			break;
		case'j':
		case'J':
			if(18==n)
				exit(0);
			if(15==n)
			{
				system("cls");
			    help();
				while(getch()){system("cls");goto S;}
			}
			if(12==n)
			{	
				system("cls");
			    wait();
				initp1();
				initm1();
				while(1)
				{
					printf("请输入你的名字:(请少于10个字符)\n");
					sprintf(player1.name,"%s","\0");
		            gets(player1.name);
		            if(strlen(player1.name)<=9)break;
				}
				system("cls");
                boundary();
				while(1){
				initm1();
				play();
				Sleep(1000);
				addspot();
				sure();
             	Sleep(1000);
				p1order();}

			}
			break;
		}
	}
			


    



}
void gotoxy(int x,int y)       //将光标移动到坐标为(x,y)的地方
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;                            
    HANDLE hConsoleOut;
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
    csbiInfo.dwCursorPosition.X = x;                                    
    csbiInfo.dwCursorPosition.Y = y;                                    
    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);   
}

void HideCursor()//隐藏光标
{
CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

int bug1(int sli)
{
    if(sli<0)sli=0;
	return sli;
}

void play1()
{
	int t=0,i=1;
	int LV=1,EXPmax=10,EXP=0,HPmax=30,HP=30,power=0,speed=0,wisdom=0,att=10,def=5,spot=0;
	float dodge=5,burst=5;
	int AI1_HP,AI1_att,AI1_def,AI1_exp;
    int AI2_HP,AI2_att,AI2_def,AI2_exp;
	char yc1,yc2;
	char enter1,enter2;
	char name[10];
	srand(time(NULL));
	power=rand()%8+7;
	speed=rand()%8+7;
	wisdom=rand()%8+7;
	spot=45-power-speed-wisdom;
NO3:printf("你的名字是？\n");
	scanf(" %s",name);
NO2:while(1)
	{
    printf("请分配你的属性点。（a.力量b.速度c.智力）（最大HP%d,力量%d,速度%d,智力%d,攻击%d,防御%d,闪避率%f,暴击率%f,剩余%d点）\n",HPmax=30+power*2,power,speed,wisdom,att=10+power*1.5,def=5+wisdom*1.5,dodge=5+speed*0.4,burst=5+speed*0.4,spot);
	scanf(" %c",&yc1);
	switch(yc1)
	{
	case'a':power+=1,spot-=1;break;
	case'b':speed+=1,spot-=1;break;
	case'c':wisdom+=1,spot-=1;break;
	default:printf("操作错误，请重新输入。\n");
	}
    if(spot==0)break;
	}
	printf("昵称：%s\n状态：LV：%d\nEXP：%d/%d\n最大HP：%d\nHP：%d\n攻击力：%d\n防御力：%d\n闪避率：%f\n暴击率：%f\n",name,LV,EXP,EXPmax,HPmax,HP=HPmax,att,def,dodge,burst);
NO1:printf("按y继续\n");
	while(1)
	{
	scanf(" %c",&enter1);
	if(enter1!='y')printf("按y继续\n");
    if(enter1=='y')break;
	}
    AI1_HP=rand()%20+30;
    AI1_att=rand()%15+25;
    AI1_def=50-AI1_att;
	AI1_exp=15;
    printf("遇到怪物，准备进入战斗。\n怪物信息：\nHP：%d\n攻击：%d\n防御：%d\n",AI1_HP,AI1_att,AI1_def);
	while(1)
	{
	if(HP<=0)break;
	printf("a.攻击b.逃跑\n");
    scanf(" %c",&yc2);
	switch(yc2)
	{
	case'a':if(rand()%100+1<=5)printf("%s攻击，miss!\n",name);
		    else if((rand()%100+1)*10<=burst*10)
				printf("%s攻击，暴击，怪物损失%dHP,怪物剩余%dHP\n",name,att,bug1(AI1_HP-=att));
			else
				printf("%s攻击，怪物损失%dHP,怪物剩余%dHP\n",name,bug1(att-AI1_def),bug1(AI1_HP-=bug1(att-AI1_def)));
            if(AI1_HP<=0)break;
            if((rand()%100+1)*10<=dodge*10)printf("怪物攻击，miss!\n");
		    else if(rand()%100+1<=5)
				printf("怪物攻击，暴击，%s损失%dHP,%s剩余%dHP\n",name,AI1_att,name,bug1(HP-=AI1_att));
			else 
				printf("怪物攻击，%s损失%dHP,%s剩余%dHP\n",name,bug1(AI1_att-def),name,bug1(HP-=bug1(AI1_att-def)));break;
	case'b':if(rand()%2==0)goto NO1;
		    else if((rand()%100+1)*10<=dodge*10)printf("逃跑失败，怪物攻击，miss!\n");
			else if(rand()%100+1<=5)
				printf("逃跑失败，怪物攻击，暴击，%s损失%dHP,%s剩余%dHP\n",name,AI1_att,name,bug1(HP-=AI1_att));
			else 
				printf("逃跑失败，怪物攻击，%s损失%dHP,%s剩余%dHP\n",name,bug1(AI1_att-def),name,bug1(HP-=bug1(AI1_att-def)));break;
	default:printf("操作错误，请重新输入。\n");
	}
	if(AI1_HP<=0)break;
	}
    if(HP<=0)goto END;
    EXP+=AI1_exp;
	if(EXP>=EXPmax)LV+=1,spot+=5,EXP-=EXPmax,EXPmax+=20*(LV-1),printf("打败怪物，%s升级了。\n",name);
	else printf("打败怪物，输入y继续遇怪,输入q查看属性。\n");
    if(spot!=0)goto NO2;
    while(1)
	{
	scanf(" %c",&enter2);
	if(enter2!='y')printf("按y继续\n");
    if(enter2=='q')printf("昵称：%s\n状态：最大HP：%d\nHP：%d\n攻击力：%d\n防御力：%d\n闪避率：%f\n暴击率：%f\n",name,HPmax,HP=HPmax,att,def,dodge,burst);
	if(enter2=='y')goto NO1;
	}
END:printf("角色死亡，游戏结束。\n");



}

void wait()
{
    int i=0,m=4,n=3;
	void HideCursor();
	void gotoxy(int x,int y);
	printf("╔══════════════════════════════════════╗");
    printf("║                                                                            ║");
    printf("║  ╱▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏▔◥║");
    printf("║  ▏                                                                  ▏%%  ║");
    printf("║  ╲▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▏▁◢║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║            ┐╭─┼─┐　　　┌┬┌┐┐┐　　　┌─╮┬─╮                ║");
    printf("║            ┐　─┼─┐　　　┌┼┌┴┴┐　　　│└╮└└╮                ║");
    printf("║            │┌─┴──　　　╭┤│　　│　　　　──┼─　                ║");
    printf("║            │　├──┤　　　│├├──┤　　　┌──┴─┐                ║");
    printf("║            │　├──┤　　　││├──┤　　　┌─┬─┼┐                ║");
    printf("║            └╰┘　　┘      └└└　　╯      　└──╯　                ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("║                                                                            ║");
    printf("╚══════════════════════════════════════╝");
    while(1)
	{

		  Sleep(50);
		  gotoxy(m+=2,n);
		  printf("■");
		  gotoxy(76,n);
		  printf("%2d",i+=3);
		  if(i==99)
		  {
			  Sleep(2000);
			  break;
		  }
	}
	system("cls");
}

void start()
{
    printf("╔══════════════════════════════════════╗");
	printf("║Beta0.1                                                                     ║");
	printf("║                                                                            ║");
	printf("║    　╗═╩═╗　╭╦═　╦╗　　　　╗　　　╔════╗　╔╗╭══╗    ║");
	printf("║    ╔╠╔═╗　　╔╩══╯╗　╚══╠═╝　║════║　║║║　　║    ║");
	printf("║    　║║　║　　　╯╦══╗　　　　║　　　╔═══╗║　║╯╝══╚    ║");
	printf("║    　║║　║╗　╚════╯　　　　║　　　╠═══╣║　║║╔╔　╗    ║");
	printf("║    　║║　║║　╚╯╦══╗　　　　║═╮　╠═══╣║　╠╯╰╰╔╯    ║");
	printf("║    ╚╩╯　╚╯  ╚════╯  ╚══╯　╝  ╚═══╯╰  ╚　══╩╝    ║");
	printf("║                                                                            ║");
	printf("║                                                                            ║");
	printf("║                              ┏━━━━┓                                  ║");
	printf("║                          ★  ┃开    始┃                                  ║");
	printf("║                              ┗━━━━┛                                  ║");
	printf("║                              ┏━━━━┓                                  ║");
	printf("║                              ┃帮    助┃                                  ║");
	printf("║                              ┗━━━━┛                                  ║");
	printf("║                              ┏━━━━┓                                  ║");
	printf("║                              ┃退    出┃                                  ║");
	printf("║                              ┗━━━━┛                                  ║");
	printf("║                                                                            ║");
	printf("║                                                             作者QQ993107057║");
	printf("║                                                             百度ID:佳砾三千║");
	printf("╚══════════════════════════════════════╝");
}

void initp1()
{
    player1.power=player1.speed=player1.wisdom=0;
	player1.att=10+player1.power*1.5;
    player1.def=5+player1.wisdom*1.5;
    player1.HPmax=30+player1.power*2;
	player1.HP=player1.HPmax;
    player1.burst=player1.dodge=5+player1.speed*0.4;
	player1.LV=1;
	player1.EXPmax=15+20*player1.LV*(player1.LV-1);
	player1.EXP=0;
	player1.spot=30;
}

void initm1()
{
	srand(time(0));
	sprintf(monster1.name,"%s","老鼠");
    monster1.HP=rand()%20+30;
    monster1.att=rand()%15+25;
    monster1.def=50-monster1.att;
    monster1.EXP=15;
	monster1.burst=monster1.dodge=5;
}

void play()
{
	int bug1(int x);
	player1.att=10+player1.power*1.5;
	player1.def=5+player1.wisdom*1.5;
	player1.HPmax=30+player1.power*2;
	player1.burst=player1.dodge=5+player1.speed*0.4;
	gotoxy(11,2);
	printf("%s",player1.name);
	gotoxy(11,3);
	printf("%3d/%3d",bug1(player1.HP),player1.HPmax);
	gotoxy(11,4);
	printf("%3d",player1.att);
	gotoxy(11,5);
	printf("%3d",player1.def);
	gotoxy(11,6);
	printf("%2.1f",player1.burst);
	gotoxy(11,7);
	printf("%2.1f",player1.dodge);
	gotoxy(11,8);
    printf("%3d",player1.power);
	gotoxy(11,9);
	printf("%3d",player1.speed);
	gotoxy(11,10);
	printf("%3d",player1.wisdom);
	gotoxy(11,11);
	printf("%3d/%3d",player1.EXP,player1.EXPmax);
	gotoxy(11,12);
	printf("%2d",player1.LV);
	gotoxy(35,5);
	printf("%2d",player1.spot);
	gotoxy(67,2);
	printf("%s",monster1.name);
	gotoxy(67,3);
	printf("%3d",bug1(monster1.HP));
	gotoxy(67,4);
	printf("%3d",monster1.att);
    gotoxy(67,5);
	printf("%3d",monster1.def);
	gotoxy(67,6);
	printf("%2.1f",monster1.burst);
	gotoxy(67,7);
	printf("%2.1f",monster1.dodge);
	gotoxy(67,8);
	printf("%3d",monster1.EXP);
}

void boundary()
{
	printf("╔══════════════════════════════════════╗");
	printf("║┌────────┐┌────────┐                ┌────────┐║");
	printf("║│  name:         ││          ┼力量│╭╮╭╮╭══╮│  name:         │║");
	printf("║│    HP:         ││          ┼速度│║║║║║╭═╯│    HP:         │║");
	printf("║│攻击力:         ││          ┼智力│║║║║║╰═╮│攻击力:         │║");
	printf("║│防御力:         ││剩余加点数:     │║║║║╰═╮║│防御力:         │║");
	printf("║│暴击率:         ││▔▔▔▔▔▔▔▔│╰╮╭╯╭═╯║│暴击率:         │║");
	printf("║│闪避率:         ││            攻击│  ╰╯　╰══╯│闪避率:         │║");
	printf("║│  力量:         ││            逃跑│                │   EXP:         │║");
	printf("║│  速度:         ││  ╭︿︿︿╮    │                │      ____()()  │║");
	printf("║│  智力:         ││  {/-●●-/}    │                │     /      @@  │║");
	printf("║│   EXP:         ││   ( (oo) )     │                │~~~~~\\_;m__m._>o│║");
	printf("║│    LV:         ││    ︶︶︶      │                │                │║");
	printf("║━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━║");
	printf("║                                                                            ║");
	printf("║                                                                            ║");
	printf("║                                                                            ║");
	printf("║                                                                            ║");
	printf("║                                                                            ║");
	printf("║                                                                            ║");
	printf("║                                                                            ║");
	printf("║                                                                            ║");
	printf("║                                                                            ║");
	printf("╚══════════════════════════════════════╝");
}


void addspot()
{        
        char c2;
	    int m=28,n=2;
		if(player1.spot>0){
	    gotoxy(2,14);
        printf("                                                   ");
		gotoxy(2,14);
		printf("请加点!");
	    gotoxy(m,n);
		printf("☆");
		gotoxy(27,2);
		while(1)
		{
			c2=getch();
			switch(c2)
			{
		case'w':
		case'W':
			printf("  ");
			n-=1;
			if(n<2)n=4;
			gotoxy(m,n);
			printf("☆");
			gotoxy(m-1,n);
			break;
		case's':
		case'S':
   			printf("  ");
			n+=1;
			if(n>4)n=2;
			gotoxy(m,n);
			printf("☆");
			gotoxy(m-1,n);
			break;
		case'j':
		case'J':
			if(n==2)player1.power+=1,player1.spot-=1;
		    if(n==3)player1.speed+=1,player1.spot-=1;
            if(n==4)player1.wisdom+=1,player1.spot-=1;
			play();
			gotoxy(m,n);
			break;
			}
			if(player1.spot==0)
			{
				gotoxy(27,2);
					printf("  ");
				gotoxy(27,3);
				printf("  ");
				gotoxy(27,4);
				printf("  ");
					break;}}
		}
}

void sure()
{
    char c3;
	int m,n;
A:  m=45,n=9;
	gotoxy(42,8);
	printf("╔══════╗");
	gotoxy(42,9);
	printf("║            ║");
	gotoxy(42,10);
	printf("║            ║");
	gotoxy(42,11);
    printf("║            ║");
	gotoxy(42,12);
    printf("╚══════╝");
	gotoxy(51,9);
	printf("继续");
	gotoxy(51,11);
	printf("退出");
	gotoxy(45,9);
	printf("★");
	gotoxy(45,9);
	while(1)
	{
		c3=getch();
		switch(c3)
		{
		case'w':
		case'W':
			printf("  ");
			n-=2;
			if(n<9)n=11;
			gotoxy(m,n);
			printf("★");
			gotoxy(m-1,n);
			break;
		case's':
		case'S':
   			printf("  ");
			n+=2;
			if(n>11)n=9;
			gotoxy(m,n);
			printf("★");
			gotoxy(m-1,n);
			break;
		case'j':
		case'J':
			if(n==9)
			{
	gotoxy(42,8);
	printf("                ");
	gotoxy(42,9);
	printf("                ");
	gotoxy(42,10);
	printf("                ");
	gotoxy(42,11);
    printf("                ");
	gotoxy(42,12);
    printf("                ");
	goto B;
			}
			if(n==11)
			{
    gotoxy(42,8);
	printf("╔══════╗");
	gotoxy(42,9);
	printf("║            ║");
	gotoxy(42,10);
	printf("║            ║");
	gotoxy(42,11);
    printf("║            ║");
	gotoxy(42,12);
    printf("╚══════╝");
	gotoxy(46,9);
	printf("否   是");
	gotoxy(46,10);
	printf("★");
	gotoxy(46,10);
	m=46,n=10;
	while(1)
	{
	    c3=getch();
		switch(c3)
		{
		case'a':
		case'A':
			printf("  ");
			m-=5;
			if(m<46)m=51;
			gotoxy(m,n);
			printf("★");
			gotoxy(m-1,n);
			break;
		case'd':
		case'D':
   			printf("  ");
			m+=5;
			if(m>51)m=46;
			gotoxy(m,n);
			printf("★");
			gotoxy(m-1,n);
			break;
		case'j':
		case'J':
			if(m==51)exit(0);
			if(m==46)goto A;
		}
	}
			}
		}
	}
B:gotoxy(28,7);
}

void p1die()
{
printf("╔══════════════════════════════════════╗");
printf("║                                                                            ║");
printf("║                           .-\"      \"-.                                     ║");	
printf("║                          /            \\                                    ║");
printf("║                         |      ★      |                                   ║");
printf("║                         |,  .-.  .-.  ,|                                   ║");
printf("║                         | )(__/  \\__)( |                                   ║");
printf("║                         |/     /\\     \\|                                   ║");
printf("║               (@_       (_     ^^     _)                                   ║");
printf("║          _     ) \\_______\\__|IIIIII|__/__________________________          ║");
printf("║         (_)@8@8{}<________|-\\IIIIII/-|___________________________>         ║");
printf("║                )_/        \\          /                                     ║");
printf("║               (@           `--------`                                      ║");
printf("║                                                                            ║");
printf("║                                                                            ║");
printf("║    ┣━━━━┓　┣━━━━┓　┏┳━━┳┓　　━━╮　　                  ║");
printf("║    ┏━━┳━┓　╯━━┳━┓　　┣━┓┃　　┳━━┻━╯                  ║");
printf("║    ┃　　┃　┃　┃　　┃　┃　┏╯　┃┃　　┃　　　　　                  ║");
printf("║    ┣━━┣━┫　┃　　┃　┃　　╰━┫┣┛　┃　　　　　                  ║");
printf("║    ┣━━┣━┫　┣━━┻━╯　　　　┃┃　　┃　　　　┃                  ║");
printf("║    ╯　　┛┗╯  ╰━━━━╯  ┗━━╯┗╯  ┗━━━━╯                  ║");
printf("║                                                                            ║");
printf("║                                                                            ║");
printf("╚══════════════════════════════════════╝");
Sleep(5000);
system("cls");
gotoxy(0,0);
exit(0);
}       

void p1order()
{
	char c4;
	int m,n;
	void addspot();
	void p1att();
	void m1att();
	void play();
	int p1run();
	gotoxy(28,7);
	printf("  ");
	gotoxy(28,8);
	printf("  ");
	gotoxy(28,7);
	printf("★");
	gotoxy(28,7);
	m=28,n=7;
	while(1)
	{
		c4=getch();
		switch(c4)
		{
		case'w':
		case'W':
			gotoxy(28,7);
            printf("  ");
	        gotoxy(28,8);
	        printf("  ");
			n-=1;
			if(n<7)n=8;
			gotoxy(m,n);
			printf("★");
			gotoxy(m-1,n);
			break;
		case's':
		case'S':
   				gotoxy(28,7);
	        printf("  ");
	       gotoxy(28,8);
	         printf("  ");
			n+=1;
			if(n>8)n=7;
			gotoxy(m,n);
			printf("★");
			gotoxy(m-1,n);
			break;
		case'j':
		case'J':
			if(n==7){p1att();addspot();if(monster1.HP<=0){sure();initm1();play();}}
			if(n==8)
			{
				p1run();
				if(player1.HP<=0)
			{
				system("cls");
				gotoxy(0,0);
				p1die();
				Sleep(3);
			}
			
			}
			
		}
	}
		

}

void p1att()
{
	void gotoxy();
	void play();
	void sure();
	int bug1(int x);
	srand(time(0));
	gotoxy(2,16);
    printf("                                                   ");
	gotoxy(2,14);
	printf("                                                   ");
    gotoxy(2,14);
	Sleep(1000);
			if(rand()%100+1<=5)printf("%s攻击，miss!\n",player1.name);
		    else if((rand()%100+1)*10<=player1.burst*10)
				printf("%s攻击，暴击，怪物损失%dHP,怪物剩余%dHP\n",player1.name,player1.att,bug1(monster1.HP-=player1.att));
			else
				printf("%s攻击，怪物损失%dHP,怪物剩余%dHP\n",player1.name,bug1(player1.att-monster1.def),bug1(monster1.HP-=bug1(player1.att-monster1.def)));
        play(); 
	gotoxy(2,15);
	printf("                                                   ");
	gotoxy(2,15);

			if(monster1.HP<=0)
			{
				player1.EXP+=monster1.EXP;
				gotoxy(2,16);
				printf("打败怪物，获得%d经验.",monster1.EXP);
				if(player1.EXP>=player1.EXPmax)
				player1.LV+=1,player1.spot+=5,player1.EXP-=player1.EXPmax,player1.EXPmax+=20*(player1.LV-1),player1.HP=player1.HPmax,printf("升级了!");
				play();
				goto NEXT;
			}
           Sleep(1000);
		    gotoxy(2,16);
            if((rand()%100+1)*10<=player1.dodge*10)printf("怪物攻击，miss!\n");
		    else if(rand()%100+1<=5)
				printf("怪物攻击，暴击，%s损失%dHP,%s剩余%dHP\n",player1.name,monster1.att,player1.name,bug1(player1.HP-=monster1.att));
			else 
				printf("怪物攻击，%s损失%dHP,%s剩余%dHP\n",player1.name,bug1(monster1.att-player1.def),player1.name,bug1(player1.HP-=bug1(monster1.att-player1.def)));
			play();
			gotoxy(28,7);
            if(player1.HP<=0)
			{
				system("cls");
				gotoxy(0,0);
				p1die();
				Sleep(3);
			}
    NEXT:;
}			

int p1run()
{

	        if(rand()%2==0)
			{
				gotoxy(2,14);
				printf("                                                   ");
				gotoxy(2,14);
				printf("逃跑成功!");
				sure();
				p1order();
			}
		    else if((rand()%100+1)*10<=player1.dodge*10)
			{
				gotoxy(2,14);
				printf("                                                   ");
				gotoxy(2,14);
				printf("逃跑失败，怪物攻击，miss!\n");
			}
			else if(rand()%100+1<=5)
			{
				gotoxy(2,14);
				printf("                                                   ");
				gotoxy(2,14);
				printf("逃跑失败，怪物攻击，暴击，%s损失%dHP,%s剩余%dHP\n",player1.name,monster1.att,player1.name,bug1(player1.HP-=monster1.att));
				play();
			}
			else 
			{
				gotoxy(2,14);
				printf("                                                   ");
				gotoxy(2,14);
				printf("逃跑失败，怪物攻击，%s损失%dHP,%s剩余%dHP\n",player1.name,bug1(monster1.att-player1.def),player1.name,bug1(player1.HP-=bug1(monster1.att-player1.def)));
				play();
			}
   return player1.HP;
}

void help()
{
printf("                    ★☆★☆★☆★☆★☆★☆★☆★☆★☆              \n");
printf("                    ☆       坑 爹 大 冒 险           ★              \n");
printf("                    ★                                ☆              \n");
printf("                    ☆     帮               助        ★              \n");
printf("                    ★                                ☆              \n");
printf("                    ☆★☆★☆★☆★☆★☆★☆★☆★☆★              \n");
printf("+力量：攻击力+1.5，HPmax+2；+速度：暴击和闪避各+0.4；+智力：防御力+1.5\n");
printf("                                                                      \n");
printf("                          因为这是第一次测试版，                      \n");
printf("         W              所以游戏还不具有坑爹元素。                    \n");
printf("         ↑               而且游戏可玩性还不高，                      \n");
printf("                        主要是因为没想好初始属性。                    \n");
printf("                     ┌──────────────┐    ┏━━┓     \n");
printf("  S←          →D   │感谢百度吧友ID6210001的指导!│    ┃确认┃     \n");
printf("                     └──────────────┘    ┗━━┛     \n");
printf("                       作者也只是个刚上大一的学生，                   \n");
printf("         ↓               刚学C语言，能力有限。             J         \n");
printf("         S                   现在是期末期间，                         \n");
printf("                         所以要做各科的复习突击，                     \n");
printf("                             没时间更新游戏，                         \n");
printf("                                 望见谅。                             \n");
printf("                                                           佳砾三千   \n");
printf("                                                        2012年12月10日\n");
}



                                     

                                     
                                                                 
                                                                 
                                                                 
                                                                               
         
