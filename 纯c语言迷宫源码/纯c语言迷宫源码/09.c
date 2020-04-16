
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

/*�Թ�������*/
int maze[100][100];

/*�Թ�������������*/
int m=0,n=0;
/*
*���Թ����г�ʼ����������������Թ�
*/
void InitMaze()
{
      int i,j,temp;
      srand((unsigned)time(NULL));
      for(i=1;i<=m;i++)
          for(j=1;j<=n;j++)
          {
              temp=rand()%100;
              if(temp>30)
              {
                  maze[i-1][j-1]=0;
              }else
              {
                  maze[i-1][j-1]=1;
              }
          }
      maze[0][0]=0;
      maze[m-1][n-1]=9;
}
/*
*����ջ��ջ�Ľڵ�
*/
typedef struct Node
{
int x;
int y;
struct Node *next;
}Node,*Stack;
/*
*��ʼ��Stack
*/
void InitStack(Node *Stack)
{
Stack=(Node *)malloc(sizeof(Node));
if(Stack==NULL)
{
    printf("����ռ�ʧ��\n");
    exit(0);
}else
{
    Stack->next=NULL;
}
}
/*
*ѹջ
*/
void push(Node *Stack,int x,int y)
{
Node *temp;
temp=(Node *)malloc(sizeof(Node));
if (!temp)
{
    printf("�����ڴ�ռ����");
    return;
}
else
{
    temp->x=x;
    temp->y=y;
    temp->next=Stack->next;
    Stack->next=temp;
}
}

/*
*��ջ
*/
void pop(Node *Stack,int *x,int *y)
{
Node *temp;
temp=Stack->next;
if(!temp){
    return;
}else{
    *x=temp->x;
    *y=temp->y;
}
Stack->next=temp->next;
free(temp);
}
/*
*�ж�ջ�Ƿ�Ϊ��
*/
int isEmpty(Node *Stasck)
{
    return ((Stasck->next)==NULL);
}

/*
*�жϴӸõ�ʱ����������������ƶ����������ƶ��ķ���
*/
int pass(int i,int j)
{
           /*�ҷ���*/
          if(j<n-1&&(maze[i][j+1]==0||maze[i][j+1]==9))
          {
              return 2;
          }
          /*�·���*/
          if(i<m-1&&(maze[i+1][j]==0||maze[i+1][j]==9))
          {
                return 3;
           }
           /*����*/
           if(j>=1&&(maze[i][j-1]==0||maze[i][j-1]==9))
           {
               return 4;
           }
           /*�Ϸ���*/
           if(i>=1&&(maze[i-1][j]==0||maze[i-1][j]==9))
           {
               return 5;
           }
           return -1;
}

/*
*���Թ����д�ӡ
*/
void drawMaze()
{
     int i=0,j=0;
     for(i=0;i<m;i++){
          for(j=0;j<n;j++)
          {
              if(maze[i][j]==0||maze[i][j]==9||maze[i][j]==-1)
              {
                  printf("a");
              }
              else if(maze[i][j]==1)
              {
                   printf("b");
              }
              else if(maze[i][j]==2)
              {
                   printf("D");
              }else if(maze[i][j]==3)
              {
                    printf("X");
              }else if(maze[i][j]==4)
              {
                    printf("A");
              }else if(maze[i][j]==5)
              {
                    printf("W");
              }
          }
          printf("\n");
      }
}
/*
*���Թ�����·������
*��������������º���
*0.�õ�û�б�̽�������ҿ���
*1.�õ㲻����
*2.�õ��ǿ��еģ��ҽ������򶫵�̽��
*3.�õ��ǿ��еģ��ҽ��������ϵ�̽��
*4.�õ��ǿ��еģ��ҽ�����������̽��
*5.�õ��ǿ��еģ��ҽ������򱱵�̽��
*6.�õ������
*9.�õ��ǳ���
*-1.�õ��Ѿ���������ĸ����򣬲����ҵ���Ч��·��������Ϊ��1
*/
void ShowPath()
{
int curx=0,cury=0;
int count=0;
int flag=0;
Node *Stacks=NULL;
InitStack(Stacks);
do{
    if(maze[curx][cury]==9)
    {
     flag=1;
    }
    switch(pass(curx,cury)){
    case 2:
     maze[curx][cury]=2;
     push(Stacks,curx,cury);
     cury++;
     break;
    case 3:
     maze[curx][cury]=3;
     push(Stacks,curx,cury);
     curx++;
     break;
    case 4:
     maze[curx][cury]=4;
     push(Stacks,curx,cury);
     cury--;
     break;
    case 5:
     maze[curx][cury]=5;
     push(Stacks,curx,cury);
     curx--;
     break;
    case -1:
     maze[curx][cury]=-1;
     if(!isEmpty(Stacks))
      pop(Stacks,&curx,&cury);
     break;
    }
    count++;
}while(!isEmpty(Stacks)&&flag==0);
if(flag==1)
{
    printf("The path is :\n");
    printf("\n");
    drawMaze();
}else
{
    printf("\nSorry,you fail\n");
}
}
/*
*������
*/
int main()
{
    loop:
    printf("plase input the number of row m(m>0,m<100):");
    scanf("%d",&m);
    printf("plase input the number of line n(n>0,n<100):");
    scanf("%d",&n);
    if(m<0||m>100||n<0||n>100){
    printf("The number is error,process will exit !\n");
    exit(-1);
    }
    printf("The character is 'a',it is area.\n");
    printf("The character is 'b',it is wall.\n");
    printf("\n");
    InitMaze();
    printf("The oid Maze:\n");
    printf("\n");
    drawMaze();
    printf("\n show the path ?(y/n)");
    fflush(stdin);
    if(toupper(getch())=='Y')
    {
               printf("\n");
               ShowPath(); 
               printf("\n go on play ?(y/n)");
               fflush(stdin);
               if(toupper(getch())=='Y')
               {
                   goto loop;                 
               }
               else
               {
                   exit(1);
               }                
    }
    else
    {
             exit(1);
    }
    getch();
    return 0;
}
