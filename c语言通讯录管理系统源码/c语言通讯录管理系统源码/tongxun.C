#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<string.h>

/* 【自学去】网站收集 http://www.zixue7.com */

typedef struct Info
{
char name[15];/*姓名*/
char city[10];/*城市*/
char province[10];/*省*/
char state[10];/*国家*/
char tel[15];/*电话*/
};
typedef struct node/*定义通讯录链表的结点结构*/
{
struct Info data;
struct node *next;
}Node,*link;

void stringinput(char *t,int lens,char *notice)
{
   char n[50];
   do{
      printf(notice); /*显示提示信息*/
      scanf("%s",n); /*输入字符串*/
      if(strlen(n)>lens)printf("\n exceed the required length! \n"); /*超过lens值重新输入*/
     }while(strlen(n)>lens);
   strcpy(t,n); /*将输入的字符串拷贝到字符串t中*/
}
void enter(link l)/*输入记录*/
{
Node *p,*q;
q=l;
while(1)
{
p=(Node*)malloc(sizeof(Node));/*申请结点空间*/
if(!p)/*未申请成功输出提示信息*/
{
printf("memory malloc fail\n");
return;
}
stringinput(p->data.name,15,"enter name:");/*输入姓名*/
if(strcmp(p->data.name,"0")==0)/*检测输入的姓名是否为0*/
break;
stringinput(p->data.city,10,"enter city:");/*输入城市*/
stringinput(p->data.province,10,"enter province:");/*输入省*/
stringinput(p->data.state,10,"enter status:");/*输入国家*/
stringinput(p->data.tel,15,"enter telephone:");/*输入电话号码*/
p->next=NULL;
 q->next=p;
 q=p;
}
}

void del(link l)
{
Node *p,*q;
char s[20];
q=l;
p=q->next;
printf("enter name:");
scanf("%s",s);/*输入要删除的姓名*/
while(p)
{
if(strcmp(s,p->data.name)==0)/*查找记录中与输入名字匹配的记录*/
{q->next=p->next;/*删除p结点*/
free(p);/*将p结点空间释放*/
printf("delete successfully!");
break;
}
else
{
q=p;
p=q->next;
}
}
getch();
}
void display(Node *p)
{
printf("MESSAGE \n");
	printf("name:%15s\n",p->data.name);
	printf("city:    %10s\n",p->data.city);
	printf("province:%10s\n",p->data.province);
	printf("state:   %10s\n",p->data.state);
	printf("telphone:%15s\n",p->data.tel);

}
void search(link l)
{
char name[20];
Node *p;
p=l->next;
printf("enter name to find:");
scanf("%s",name);/*输入要查找的名字*/
while(p)
{if(strcmp(p->data.name,name)==0)/*查找与输入的名字相匹配的记录*/
{
display(p);/*调用函数显示信息*/
getch();
break;
}
else
p=p->next;
}
}
void list(link l)
{
Node *p;
p=l->next;
while(p!=NULL)/*从首节点一直遍历到链表最后*/
{
display(p);
p=p->next;
}
getch();
}

void save(link l)
{
Node *p;
FILE *fp;
p=l->next;
if((fp=fopen("f:\\adresslist","wb"))==NULL)
{
printf("can not open file\n");
exit(1);
}
printf("\nSaving file\n");
while(p)/*将节点内容逐个写入磁盘文件中*/
{
fwrite(p,sizeof(Node),1,fp);
p=p->next;
}
fclose(fp);
getch();
}
void load(link l)
{
Node *p,*r;
FILE *fp;
l->next=NULL;
r=l;
if((fp=fopen("f:\\adresslist","rb"))==NULL)
{
printf("can not open file\n");
exit(1);
};
printf("\nLoading file\n");
while(!feof(fp))
{
p=(Node*)malloc(sizeof(Node));/*申请节点空间*/
if(!p)
{
printf("memory malloc fail!");
return;
}
if(fread(p,sizeof(Node),1,fp)!=1)/*读记录到节点p中*/
break;
else
{
	p->next=NULL;
	r->next=p;/*插入链表中*/
	r=p;
	}
}
fclose(fp);
getch();
}
menu_select()
{
int i;
printf("\n\n\t *************************ADDRESS LIST*************************\n");
printf("\t|*			1.input record			      *|\n");
printf("\t|*			2.delete record			      *|\n");
printf("\t|*			3.list record			      *|\n");
printf("\t|*			4.search record			      *|\n");
printf("\t|*			5.save record			      *|\n");
printf("\t|*			6.load record			      *|\n");
printf("\t|*			7.Quit                                *|\n");
printf("\t **************************************************************\n");
do
{
printf("\n\tEnter your choice:");
scanf("%d",&i);
}while(i<0||i>7);
return i;
}
main()
{
link l;
l=(Node*)malloc(sizeof(Node));
if(!l)
   {
      printf("\n allocate memory failure "); /*如没有申请到，输出提示信息*/
      return ;             /*返回主界面*/
   }
l->next=NULL;
system("cls");
while(1)
{
system("cls");
switch(menu_select())
{
case 1:
enter(l);
break;
case 2:
del(l);
break;
case 3:
list(l);
break;
case 4:
search(l);
break;
case 5:
save(l);
break;
case 6:
load(l);
break;
case 7:
exit(0);
}
}
}
