/* 电子时钟程序 */

/* 【自学去】网站收集 http://www.zixue7.com */

#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 
#include <time.h> 
typedef struct 
{ 
     int x; 
     int y; 
}Point; 
time_t now; 
struct tm *pt,t1,t2; 
int printpoint(Point p) 
{ 
     Point p1; 
     p1.x=p.x+2;  p1.y=p.y+4; 
     gotoxy(p1.x,p1.y);     printf("%c%c",2,2); 
     gotoxy(p1.x, p1.y+1);   printf("%c%c",2,2); 
     p1.y+=4; 
     gotoxy(p1.x,p1.y);     printf("%c%c",2,2); 
     gotoxy(p1.x,p1.y+1);   printf("%c%c",2,2); 
     return 0; 
} 
int print0(Point p) 
{ 
     int i=0; 
     for(;i<13;i++) 
     { 
          gotoxy(p.x+1, p.y+i); 
          if(i==0||i==12) 
                printf("%c%c%c%c%c%c",2,2,2,2,2,2); 
          else 
                printf("%c%4s%c",2," ",2); 
     } 
     return 0; 
} 
int print1(Point p) 
{ 
     int i=0; 
     for(;i<13;i++) 
     { 
          gotoxy(p.x+1, p.y+i); 
          printf("%5s%c"," ",2); 
     } 
     return 0; 
} 
int print2(Point p) 
{ 
     int i=0; 
     for(;i<13;i++) 
     { 
          gotoxy(p.x+1, p.y+i); 
          if(i==0||i==6||i==12) 
                printf("%c%c%c%c%c%c",2,2,2,2,2,2); 
          else if(i>0&&i<6) 
               printf("%5s%c"," ",2); 
               else 
                printf("%c",2); 
     } 
     return 0; 
} 
int print3(Point p) 
{ 
     int i=0; 
     for(;i<13;i++) 
     { 
          gotoxy(p.x+1, p.y+i); 
          if(i==0||i==6||i==12) 
                printf("%c%c%c%c%c%c",2,2,2,2,2,2); 
          else 
                printf("%5s%c"," ",2); 
     } 
     return 0; 
} 
int print4(Point p) 
{ 
     int i=0; 
     for(;i<13;i++) 
     { 
          gotoxy(p.x+1, p.y+i); 
          if(i<6)  printf("%c%4s%c",2," ",2); 
          else if(i==6) 
                    printf("%c%c%c%c%c%c",2,2,2,2,2,2); 
               else printf("%5s%c"," ",2); 
     } 
     return 0; 
} 
int print5(Point p) 
{ 
     int i=0; 
     for(;i<13;i++) 
     { 
          gotoxy(p.x+1, p.y+i); 
          if(i==0||i==6||i==12) 
                printf("%c%c%c%c%c%c",2,2,2,2,2,2); 
          else if(i>0&&i<6) 
                printf("%c",2); 
               else 
                printf("%5s%c"," ",2); 
     } 
     return 0; 
} 
int print6(Point p) 
{ 
     int i=0; 
     for(;i<13;i++) 
     { 
          gotoxy(p.x+1, p.y+i); 
          if(i==0||i==6||i==12) 
                printf("%c%c%c%c%c%c",2,2,2,2,2,2); 
          else if(i>0&&i<6) 
                printf("%c",2); 
               else 
                printf("%c%4s%c",2," ",2); 
     } 
     return 0; 
} 
int print7(Point p) 
{ 
     int i=0; 
     for(;i<13;i++) 
     { 
          gotoxy(p.x+1, p.y+i); 
          if(i==0)   printf("%c%c%c%c%c%c",2,2,2,2,2,2); 
          else       printf("%5s%c"," ",2); 
     } 
     return 0; 
} 
int print8(Point p) 
{ 
     int i=0; 
     for(;i<13;i++) 
     { 
          gotoxy(p.x+1, p.y+i); 
          if(i==0||i==6||i==12) 
                printf("%c%c%c%c%c%c",2,2,2,2,2,2); 
           else  printf("%c%4s%c",2," ",2); 
     } 
     return 0; 
} 
int print9(Point p) 
{ 
     int i=0; 
     for(;i<13;i++) 
     { 
          gotoxy(p.x+1, p.y+i); 
          if(i==0||i==6||i==12) 
                printf("%c%c%c%c%c%c",2,2,2,2,2,2); 
          else if(i>0&&i<6) 
                printf("%c%4s%c",2," ",2); 
               else 
                printf("%5s%c"," ",2); 
     } 
     return 0; 
} 
int clear(Point p) 
{ 
     int i=0; 
     for(;i<13;i++) 
     gotoxy(p.x,p.y+i); printf("%16s"," "); 
     return 0; 
} 
int printtime(Point p, int n) 
{ 
     int a,b; 
     Point pp; 
     a=n/10, b=n%10; 
     pp.x=p.x+8, pp.y=p.y; 
     switch(a) 
     { 
         case 0: print0(p); break; 
         case 1: print1(p); break; 
         case 2: print2(p); break; 
         case 3: print3(p); break; 
         case 4: print4(p); break; 
         case 5: print5(p); break; 
    } 
    switch(b) 
    { 
         case 0: print0(pp); break; 
         case 1: print1(pp); break; 
         case 2: print2(pp); break; 
         case 3: print3(pp); break; 
         case 4: print4(pp); break; 
         case 5: print5(pp); break; 
         case 6: print6(pp); break; 
         case 7: print7(pp); break; 
         case 8: print8(pp); break; 
         case 9: print9(pp); break; 
    } 
    return 0; 
} 
int main() 
{ 
      Point phour, pmin, psec,point1,point2; 
      phour.x=9, pmin.x=32, psec.x=55; 
      phour.y=pmin.y=psec.y=7; 
      point1.x=25, point2.x=49; 
      point1.y=point2.y=7; 
      clrscr(); 
      textbackground(YELLOW);         /* 设置背景颜色*/
      textcolor(RED);      /* 设置数字显示颜色*/
      now=time(0); 
      pt=localtime(&now); 
      t1=*pt; 
      printtime(phour, t1.tm_hour); 
      printpoint(point1); 
      printtime(pmin, t1.tm_min); 
      printpoint(point2); 
      printtime(psec, t1.tm_sec); 
      while(1) 
      { 
           now=time(0); 
       pt=localtime(&now); 
           t2=*pt; 
           if(t2.tm_sec!=t1.tm_sec) 
           { 
             t1=t2; 
             clrscr(); 
             printtime(phour, t1.tm_hour); 
             printpoint(point1); 
             printtime(pmin, t1.tm_min); 
             printpoint(point2); 
             printtime(psec, t1.tm_sec); 
           } 
           if(bioskey(1)==0) continue; 
           else exit(0); 
      } 
      return 0; 
}  
