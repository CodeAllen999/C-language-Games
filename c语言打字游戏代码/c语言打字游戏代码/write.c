#include<stdio.h>
#include<time.h> 
char *kw[]={"Q W E R T Y U I O P [ ]","A S D F G H J K L ; '","Z X C V B N M , . / "}; 
long AllCounter=0,RightCounter=0,WrongCounter=0; 

/* it—ßœ∞Õ¯ ’ºØ http://www.zixue7.com */

main() 
{ 
	int i,j; 
	int fun_Esc(); 
	
	clrscr(); 
	gotoxy(18,1); 
	printf("%s\n",kw[0]); 
	gotoxy(20,3); 
	printf("%s\n",kw[1]); 
	gotoxy(22,5); 
	printf("%s\n",kw[2]); 
	gotoxy(11,25); 
	for(i=0;i<60;i++) 
	{ 
		printf("="); 
	} 
	gotoxy(1,1); 
	printf("AllCh: %ld\nRight: %ld\nWrong: %ld",AllCounter,RightCounter,WrongCounter); 
	gotoxy(50,1); 
	printf("Press Esc to exit"); 
	gotoxy(50,2);
	printf("Enter to pause"); 
	gotoxy(26,12); 
	printf("* * * * * * * * * * * * * * "); 
	gotoxy(26,13); 
	printf("* Press any key to start! *"); 
	gotoxy(26,14); 
	printf("* * * * * * * * * * * * * * "); 
	gotoxy(51,13); 
	if(getch()==27) 
	{ 
		if(fun_Esc()==1) 
		{ 
			clrscr(); 
			exit(0); 
		} 
	} 
	gotoxy(23,12); 
	printf(" "); 
	gotoxy(23,13); 
	printf(" "); 
	gotoxy(23,14); 
	printf(" "); 
	while(1)
        fun_Play();	
} 



int fun_Play()
{
	int x,y,i,j; 
	unsigned int Timer; 
	char ch; 
	char cur; 
	
	time_t t; 
	srand((unsigned)time(&t)); 
	gotoxy(26,12); 
	printf("                              "); 
	gotoxy(26,13); 
	printf("                              "); 
	gotoxy(26,14); 
	printf("                              "); 
	
	y = 6; 
	Timer = 100000; 
	i = rand()%3; 
	j = rand()%(9-i); 
	ch = kw[i][j*4]; 
	x = 18+i*2+j*4; 
	while(y<=24) 
	{ 
		if(kbhit()) 
		{ 
			cur = getch(); 
			if(cur==ch || cur==ch+32) 
			{ 
				ch = '*'; Timer = 1000; 
			} 
			else if(cur==27) 
			{ 
				if(fun_Esc()==1) 
				{ 
					clrscr(); 
					exit(0); 
				} 
			} 
			else if(cur=='\r') 
			{ 
				gotoxy(x,y-1); 
				printf(" "); 
				gotoxy(26,12); 
				printf("* * * * * * * * * * * * * * *"); 
				gotoxy(26,13); 
				printf("* Press any key to continue *"); 
				gotoxy(26,14); 
				printf("* * * * * * * * * * * * * * * "); 
				getch(); 
				gotoxy(28,13); 
				printf(" "); 
			} 
			else 
			{ 
				WrongCounter++; 
			} 
		} 
		if(y>6) 
		{ 
			gotoxy(x,y-1); 
			printf(" "); 
		} 
		gotoxy(x,y); 
		printf("%c",ch); 
		gotoxy(1,1); 
		printf("AllCh: %ld\nRight: %ld\nWrong: %ld",AllCounter,RightCounter,WrongCounter); 
		delay(Timer); 
		y++; 
	} 
	AllCounter++; 
	if(ch == '*') 
	{ 
		RightCounter++; 
	} 
	
}
int fun_Esc() 
{ 
	int key = '#'; 
	gotoxy(26,12); 
	printf("* * * * * * * * * * * * * * * * "); 
	gotoxy(26,13); 
	printf("* Are you sure to exit? (Y/N) *"); 
	gotoxy(26,14); 
	printf("* * * * * * * * * * * * * * * * "); 
	gotoxy(51,13); 
	while(key!='Y' && key!='y' && key!='N' && key!='n') 
	{ 
		key = getch(); 
		if(key=='Y' || key=='y') 
		{ 
			return 1; 
		} 
		if(key=='N' || key=='n') 
		{ 
			gotoxy(24,12); 
			printf(" "); 
			gotoxy(24,13); 
			printf(" "); 
			gotoxy(24,14); 
			printf(" "); 
			return 0; 
		} 
	} 
}

