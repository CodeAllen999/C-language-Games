#include"stdlib.h"
#include"stdio.h"
#include"graphics.h"
#include"string.h"
#include"conio.h"
#define file "c:\\bookdata.txt"
#define ufile "c:\\userdata.txt"
#define bfile "c:\\borrowdata.txt"
int bookcount;
int usercount;
int borrowcount;
int booksum;
int myborrow;

int flg=0;
int esc=0;
int flag=0;

/* 【自学去】网站收集 http://www.zixue7.com */

/************定义输出字符的函数*************/

void pchar(int x,int y,char c)
{
gotoxy(x,y);
putch(c);
}

/**********************定义画边框的函数*************/
void box(int x,int y,int w,int height)
{

int i;
pchar(x,y,218);/*left up*/
pchar(x+w-1,y,191); /*  right up*/
for(i=0;i<w-2;i++) /*witgh*/
{
	pchar(x+1+i,y,196);
	pchar(x+1+i,y+height-1,196);
}
pchar(x,y+height-1,192);
pchar(x+w-1,y+height-1,217);
for(i=0;i<height-2;i++)
{
	pchar(x,y+1+i,179);
	pchar(x+w-1,y+i+1,179);
}
}
/********************定义画横线的函数*************/
void h_line(int x,int y,int w)
{
int i;
for(i=0;i<w;i++)
	pchar(x+i,y,196);
}
void h_line_close(int x,int y,int w)
{

int i;
pchar(x,y,195);
h_line(x+1,y,w-2);
pchar(x+w-1,y,180);
}
/***********************定义画填充矩形的函数*************/
void bar_(int x,int y,int w,int height,int color)
{
int i,j;
textcolor(color);
textbackground(color);
for(i=0;i<height;i++)
{
	gotoxy(x,y+i);
	for(j=0;j<w;j++)
		putch(' ');
}
}
/*************************定义画竖线的函数*************/
void v_line(int x,int y,int height)
{
int i;
for(i=0;i<height;i++)
    pchar(x,y+i,179);
}
/****************模拟菜单条******************/
void menu()
{
 bar_(1,25,80,1,7);
}


typedef struct book/*图书结构体*/
{
char num[10];  /*书号*/
char name[10];  /*书名*/
char auth[10]; /*作者*/
int count;
int sum;
}Book;
/*定义节点*/
typedef struct node
{
Book data;
struct node *next;
}Bnode,*blink;
/*******保存图书*******/
/*******保存图书*******/
void save(blink l) 
{ 
 FILE* fp; 
 Bnode *p; 
 int flag=1,count=0; 
 fp=fopen(file,"wb"); 
 if(fp==NULL) 
 { 
      printf("\n=====>open error!\n"); 
      exit(1); 
 } 
 p=l->next; 
 while(p) 
 { 
      if(fwrite(p,sizeof(Bnode),1,fp)==1)
      { 
          p=p->next; 
          count++; 
      } 
      else 
      { 
          flag=0; 
          break; 
      } 
} 
if(flag) 
{ 
     /* printf("save success.(saved%d.)\n",count); */
}
fclose(fp); 
} 

 /*******图书定位******/
Bnode* locate(blink l,char findmess[],char nameornum[]) 
{ 
Bnode *r; 
if(strcmp(nameornum,"num")==0) 
{ 
  r=l->next; 
  while(r!=NULL) 
  { 
      if(strcmp(r->data.num,findmess)==0) 
      return r; 
      r=r->next; 
  } 
} 
else if(strcmp(nameornum,"name")==0) 
{ 
  r=l->next; 
  while(r!=NULL) 
  { 
     if(strcmp(r->data.name,findmess)==0) 
     return r; 
     r=r->next; 
  } 
} 
return 0; 
} 
 /*******图书的添加******/
void add(blink l)
{ 
Bnode *p,*r,*s; 
char num[10]; 
r=l; 
s=l->next; 
while(r->next!=NULL) 
	r=r->next; 
textcolor(RED);
gotoxy(25,4);
cputs("INPUT THE MESSAGE ABOUT BOOK");
gotoxy(31,10);
textcolor(YELLOW);
cputs("Book ID:");
scanf("%s",num); 
p=(Bnode *)malloc(sizeof(Bnode));  
while(s) 
{ 
	if(strcmp(s->data.num,num)==0) 
	{ 
		textcolor(WHITE);
		gotoxy(25,15);
		cputs("This ID:");
		printf("'%s'",num); 
		cputs("is exist!");    
		gotoxy(25,22);
		cputs("please Press any key to continue...");  
		gotoxy(255,252);
		getch();                    
		return; 
	} 
	s=s->next; 
} 
strcpy(p->data.num,num); 
gotoxy(31,12);
textcolor(YELLOW);
cputs("Input Book name:"); 
scanf("%s",p->data.name); 
gotoxy(31,14);
cputs("input your Book auth:"); 
scanf("%s",p->data.auth); 
gotoxy(31,16);
cputs("input your Book count:"); 
scanf("%d",&p->data.count); 
bookcount=p->data.count+bookcount;
p->data.sum=0;
p->next=NULL; 
r->next=p; 
r=p; 
gotoxy(30,22);
textcolor(RED);
cputs("Add Book Success !!!");
getch();
textcolor(YELLOW);
} 

/*******管理员查找图书*******/
void qur(blink l)
{ 
int sel; 
char findmess[20]; 
Bnode *p; 

if(!l->next) 
{ 
gotoxy(30,4);
textcolor(WHITE);
     cputs("Not Find Bookdata!!!"); 
	 getch();
    return; 
} 
textcolor(RED);
gotoxy(25,4);
cputs("Please Select Search  Type !");
gotoxy(10,8);
textcolor(WHITE);
cputs("1.Search by ID");
gotoxy(10,10);
cputs("2.Search by Name");
gotoxy(10,12);
cputs("Please Select 1 or 2:");
scanf("%d",&sel); 
if(sel==1) 
{
	gotoxy(36,8);
	textcolor(YELLOW);
	cputs("Input the search ID:"); 
	scanf("%s",findmess); 
	p=locate(l,findmess,"num"); 
	if(p) 
	{ 
		gotoxy(36,12);
		textcolor(WHITE);
		cputs("Book ID:");
		printf("%s",p->data.num);
		gotoxy(36,14);
		textcolor(WHITE);
		cputs("Book Name:");
		printf("%s",p->data.name);
		gotoxy(36,16);
		textcolor(WHITE);
		cputs("Book author:");
		printf("%s",p->data.auth);
		gotoxy(36,18);
		textcolor(WHITE);
		cputs("Book count:");
		printf("%d",p->data.count);
		getch();
		textcolor(YELLOW);
		gotoxy(30,21);
		cputs("Search Success !!");
	}
	else 
	{
		gotoxy(30,22);
		textcolor(RED);
		cputs("Not finde !!!"); 
		getch();
	}
}	
else if(sel==2) /* 姓名 */
{ 
	gotoxy(36,8);
	textcolor(YELLOW);
	cputs("Input the search name:");
	scanf("%s",findmess); 
	p=locate(l,findmess,"name"); 		
	if(p) 
	{ 
		gotoxy(36,12);
		textcolor(WHITE);
		cputs("Book ID:");
		printf("%s",p->data.num);
		gotoxy(36,14);
		textcolor(WHITE);
		cputs("Book Name:");
		printf("%s",p->data.name);
		gotoxy(36,16);
		textcolor(WHITE);
		cputs("Book author:");
		printf("%s",p->data.auth);
		gotoxy(36,18);
		textcolor(WHITE);
		cputs("Book count:");
		printf("%d",p->data.count);
		getch();
		textcolor(YELLOW);
	} 
	else 
	{
		textcolor(RED);
		gotoxy(30,22);
		cputs("Not finde !!!"); 
	}
} 
else 
{
	textcolor(RED);
	gotoxy(30,22); 
	cputs("Error !!"); 
	getch();
}
} 

/*******用户查找图书*******/
void usersearch()
{ 
int sel; 
char findmess[20]; 
Bnode *p; 
blink l;/* 连表 */ 
FILE *fp; /* 文件指针 */ 
int count=0; 
Bnode *P,*r;
l=(Bnode*)malloc(sizeof(Bnode)); 
l->next=NULL; 
r=l; 
fp=fopen(file,"rb"); 
if(fp==NULL) 
{ 
	fp=fopen(file,"wb"); 
 } 
while(!feof(fp)) 
{ 
    P=(Bnode*)malloc(sizeof(Bnode)); 
    if(fread(P,sizeof(Bnode),1,fp)) /* 将文件的内容放入接点中 */ 
    { 
        P->next=NULL; 
		bookcount=bookcount+P->data.count;
		booksum=booksum+P->data.sum;
        r->next=P; 
        r=P; /* 将该接点挂入连中 */ 
        count++; 
    }
} 
fclose(fp); /* 关闭文件 */ 


if(!l->next) 
{ 
gotoxy(30,4);
textcolor(WHITE);
     cputs("Not Find Bookdata!!!");
	 getch();
    return; 
} 
textcolor(RED);
gotoxy(25,4);
cputs("Please Select Delete  Type !");
gotoxy(10,8);
textcolor(WHITE);
cputs("1.Search by ID");
gotoxy(10,10);
cputs("2.Search by Name");
gotoxy(10,12);
cputs("Please Select 1 or 2:");
scanf("%d",&sel); 
if(sel==1) 
{
	gotoxy(36,8);
	textcolor(YELLOW);
	cputs("Input the search ID:"); 
	scanf("%s",findmess); 
	p=locate(l,findmess,"num"); 
	if(p) 
	{ 
		gotoxy(36,12);
		textcolor(WHITE);
		cputs("Book ID:");
		printf("%s",p->data.num);
		gotoxy(36,14);
		textcolor(WHITE);
		cputs("Book Name:");
		printf("%s",p->data.name);
		gotoxy(36,16);
		textcolor(WHITE);
		cputs("Book author:");
		printf("%s",p->data.auth);
		gotoxy(36,18);
		textcolor(WHITE);
		cputs("Book count:");
		printf("%d",p->data.count-p->data.sum);
		getch();
		textcolor(YELLOW);
	}
	else 
	{
		gotoxy(30,22);
		textcolor(RED);
		cputs("Not finde !!!"); 
		getch();
	}
}	
else if(sel==2)
{ 
	gotoxy(36,8);
	textcolor(YELLOW);
	cputs("Input the search name:");
	scanf("%s",findmess); 
	p=locate(l,findmess,"name"); 		
	if(p) 
	{ 
		gotoxy(36,12);
		textcolor(WHITE);
		cputs("Book ID:");
		printf("%s",p->data.num);
		gotoxy(36,14);
		textcolor(WHITE);
		cputs("Book Name:");
		printf("%s",p->data.name);
		gotoxy(36,16);
		textcolor(WHITE);
		cputs("Book author:");
		printf("%s",p->data.auth);
		gotoxy(36,18);
		textcolor(WHITE);
		cputs("Book count:");
		printf("%d",(p->data.count-p->data.sum));
		getch();
		textcolor(YELLOW);
	} 
	else 
	{
		textcolor(RED);
		gotoxy(30,22);
		cputs("Not finde !!!"); 
	}
} 
else 
{
	textcolor(RED);
	gotoxy(30,22); 
	cputs("Error !!"); 
	getch();
}
} 

/*******图书查找*******/
int cmpbook(blink l,char id[],char na[])
{ 
char findm[20];
Bnode *p; 
if(!l->next) 
{ 
	gotoxy(25,4);
	textcolor(RED);
     cputs("Not Find Book!!!"); 
	 getch();
    return 0; 
} 
strcpy(findm,id);
	p=locate(l,findm,"num"); 
	if(p) 
	{ 
		strcpy(findm,na);
		p=locate(l,findm,"name"); 		
		if(p) 
		{ 
			return 1;	
		} 
		else 
		{
			textcolor(RED);
			gotoxy(30,22);
			cputs("Book name is NULL !!!"); 
			getch();
			return 0;
		}
	}
	else 
	{
		gotoxy(30,22);
		textcolor(RED);
		cputs("Book id is NULL !!!"); 
		getch();
		return 0;
	}
	


	
	

} 

/*** 删除图书*** */ 
void del(blink l) 
{ 
	int sel; 
	Bnode *p,*r; 
	char findmess[20]; 
	if(!l->next) 
	{ 
		gotoxy(25,4);
		textcolor(RED);
		cputs("=====>not thing could delete!\n"); 
		getch();
		return; 
	} 
	textcolor(RED);
	gotoxy(25,4);
	puts("Please Select Delete  Type !");
	gotoxy(10,8);
	
	textcolor(WHITE);
	cputs("1.Delete by Book ID");
	gotoxy(10,10);
	cputs("2.Delete by Book Name");
	gotoxy(10,12);
	cputs("Please Select 1 or 2:");
	scanf("%d",&sel); 
	if(sel==1)     
	{ 
		gotoxy(36,8);
		textcolor(YELLOW);
		cputs("Input the delete ID:"); 
		scanf("%s",findmess); 
		p=locate(l,findmess,"num"); 
		if(p) 
		{ 
			bookcount=bookcount-p->data.count;
			r=l; 
			while(r->next!=p) 
				r=r->next; 
			r->next=p->next; 
			free(p); 
			gotoxy(30,22);
			textcolor(RED);
			cputs("Delete success!\n");     
			textcolor(YELLOW);  
		} 
		else 
		{
	textcolor(RED);
	gotoxy(30,22); 
	cputs("Error !!"); 
		}
	} 
	else if(sel==2) 
	{ 
		gotoxy(36,8);
		textcolor(YELLOW);
		cputs("Input the delete name:"); 
		scanf("%s",findmess); 
		p=locate(l,findmess,"name"); 
		if(p) 
		{ 
			r=l; 
			while(r->next!=p) 
				r=r->next; 
			r->next=p->next; 
			free(p); 
			gotoxy(30,22);
			textcolor(RED);
			cputs("Delete success!\n"); 
			bookcount--;
			textcolor(YELLOW);  
		} 
		else
		{
			gotoxy(25,18);
			cputs("Not find!!"); 
		}
	} 
	else
	{
	textcolor(RED);
	gotoxy(30,22); 
	cputs("Error !!");  
	}
	getch();
	textcolor(YELLOW);
} 
/**************************************************************/
 /* 本函数用于修改图书资料 */
void mod(blink l)
{ 
	int tmp;
	Bnode *p; 
	char findmess[20]; 
	if(!l->next) 
	{
		gotoxy(30,4);
		textcolor(RED);
		cputs("not thing could modify!"); 
		getch();
		return; 
	} 
	gotoxy(30,4);
	textcolor(RED);
	cputs("Modify Book Message");
	gotoxy(25,8);
	textcolor(YELLOW);
	cputs("input the Book Id:");
	scanf("%s",findmess); 
	p=locate(l,findmess,"num"); 
	if(p) 
	{ 
		gotoxy(25,10);
		printf("Inpute The New ID(old:%s):",p->data.num); 
		scanf("%s",p->data.num); 
		gotoxy(25,12);
		printf("Input The New Book Name(old:%s):",p->data.name); 
		scanf("%s",p->data.name); 
		gotoxy(25,14);
		printf("Input The New Book author(old:%s):",p->data.auth); 
		scanf("%s",p->data.auth); 
		gotoxy(25,16);
		printf("Input The New count(old:%d):",p->data.count); 
		scanf("%d",&tmp); 
		bookcount=bookcount-p->data.count;
		bookcount=bookcount+tmp;
		p->data.count=tmp;
		gotoxy(30,18);
		textcolor(RED);
		cputs("Modify Success !!!"); 
		getch();
		textcolor(YELLOW);
	} 
	else 
	{	
		gotoxy(30,16);
		textcolor(RED);
		cputs("Not Finde !!!"); 
		getch();
		textcolor(YELLOW);
	}
} 






struct user 
{ 
char num[10];/* 学号 */ 
char pass[15];
char name[15]; 
char sex[10]; 

}; 

typedef struct unode 
{ 
struct user data; 
struct unode *next; 
}Unode,*Ulink; 
Unode *os;
/*******借书结构定义*******/
typedef struct borrow
{
char id[20];
char user[20];
char book[20];
char bookid[20];
struct borrow *next;
}BBnode,*BBlink;

void Save(Ulink l) /*******用户信息保存*******/
{ 
 FILE* fp; 
 Unode *p; 
 int flag=1,count=0; 
 fp=fopen(ufile,"wb"); 
 if(fp==NULL) 
 { 
gotoxy(35,12);
	textcolor(RED);
      cputs("open error!"); 
      exit(1); 
 } 
 p=l->next; 
 while(p) 
 { 
      if(fwrite(p,sizeof(Unode),1,fp)==1) 
      { 
          p=p->next; 
          count++; 
      } 
      else 
      { 
          flag=0; 
          break; 
      } 
} 
if(flag) 
{ 
textcolor(RED);
gotoxy(30,24);
  printf("save success.(saved%d.)",count);
}
fclose(fp); 
} 

/*******借书信息保存*******/
void Save_borrow(BBlink l) 
{ 
 FILE* fp; 
 BBnode *p; 
 int flag=1,count=0; 
 fp=fopen(bfile,"wb"); 
 if(fp==NULL) 
 { 
gotoxy(35,12);
	textcolor(RED);
      cputs("open error!"); 
      exit(1); 
 } 
 p=l->next; 
 while(p) 
 { 
      if(fwrite(p,sizeof(BBnode),1,fp)==1) 
      { 
          p=p->next; 
          count++; 
      } 
      else 
      { 
          flag=0; 
          break; 
      } 
} 
if(flag) 
{ 
textcolor(RED);
gotoxy(30,24);
 /*** printf("save success.(saved%d.)",count);**调试的时候用的*/
}
fclose(fp); 
} 

/*******用户定位*******/
Unode* Locate(Ulink l,char findmess[],char nameornum[]) 
{ 
Unode *r; 
if(strcmp(nameornum,"num")==0) 
{ 
  r=l->next; 
  while(r!=NULL) 
  { 
      if(strcmp(r->data.num,findmess)==0) 
      return r; 
      r=r->next; 
  } 
} 
else if(strcmp(nameornum,"name")==0) 
{ 
  r=l->next; 
  while(r!=NULL) 
  { 
     if(strcmp(r->data.name,findmess)==0) 
     return r; 
     r=r->next; 
  } 
} 

else if(strcmp(nameornum,"pass")==0) 
{ 
  r=l->next; 
  while(r!=NULL) 
  { 
     if(strcmp(r->data.pass,findmess)==0) 
     return r; 
     r=r->next; 
  } 
} 
return 0; 
} 
/*******图书借书查找模块*******/
BBnode* Locate_borrow(BBlink l,char findmess[],char nameornum[]) 
{ 
BBnode *r; 
if(strcmp(nameornum,"num")==0) 
{ 
  r=l->next; 
  while(r!=NULL) 
  { 
      if(strcmp(r->id,findmess)==0) 
      return r; 
      r=r->next; 
  } 
} 
else if(strcmp(nameornum,"user")==0) 
{ 
  r=l->next; 
  while(r!=NULL) 
  { 
     if(strcmp(r->user,findmess)==0) 
     return r; 
     r=r->next; 
  } 
} 

else if(strcmp(nameornum,"book")==0) 
{ 
  r=l->next; 
  while(r!=NULL) 
  { 
     if(strcmp(r->book,findmess)==0) 
     return r; 
     r=r->next; 
  } 
} 
return 0; 
} 
 /*******管理员添加用户*******/
void Add(Ulink l)
{ 
Unode *p,*r,*s; 
char num[10]; 
r=l; 
s=l->next; 
while(r->next!=NULL) 
	r=r->next; 
textcolor(RED);
gotoxy(25,4);
cputs("INPUT THE MESSAGE ABOUT BOOK");
gotoxy(31,10);
textcolor(YELLOW);
cputs("User ID:");
scanf("%s",num); 
p=(Unode *)malloc(sizeof(Unode));  
while(s) 
{ 
	if(strcmp(s->data.num,num)==0) 
	{ 
		gotoxy(25,15);
		cputs("This ID:");
		printf("'%s'",num); 
		cputs("is exist!");    
		gotoxy(25,22);
		textcolor(RED);
		cputs("please Press any key to continue...");  
		gotoxy(255,252);
		getch();                    
		return; 
	} 
	s=s->next; 
} 
strcpy(p->data.num,num); 
gotoxy(31,12);
textcolor(YELLOW);
cputs("Input Password:"); 
scanf("%s",p->data.pass); 
gotoxy(31,14);
cputs("input your name:"); 
scanf("%s",p->data.name); 
gotoxy(31,16);
cputs("input the sex:"); 
scanf("%s",p->data.sex); 
p->next=NULL; 
r->next=p; 
r=p; 
gotoxy(30,22);
cputs("Add User Success !!!");
usercount++;
getch();
textcolor(YELLOW);
} 


/******查询用户信息*******/
void Qur(Ulink l)
{ 
int sel; 
char findmess[20]; 
Unode *p; 

if(!l->next) 
{
gotoxy(25,4);
textcolor(RED);
     cputs("Error!!!"); 
    return; 
} 
textcolor(RED);
gotoxy(25,4);
cputs("Please Select Search  Type !");
gotoxy(10,8);
textcolor(WHITE);
cputs("1.Search by ID");
gotoxy(10,10);
cputs("2.Search by Name");
gotoxy(10,12);
cputs("Please Select 1 or 2:");
scanf("%d",&sel); 
if(sel==1)/*学号 */ 
{
	gotoxy(36,8);
	textcolor(YELLOW);
	cputs("Input the User ID:"); 
	scanf("%s",findmess); 
	p=Locate(l,findmess,"num"); 
	if(p) 
	{ 
		gotoxy(36,12);
		textcolor(WHITE);
		cputs("User ID:");
		printf("%s",p->data.num);
		gotoxy(36,14);
		textcolor(WHITE);
		cputs("User Name:");
		printf("%s",p->data.name);
		gotoxy(36,16);
		textcolor(WHITE);
		cputs("User Sex:");
		printf("%s",p->data.sex);
		textcolor(WHITE);
		gotoxy(36,18);
		cputs("User password:");
		printf("%s",p->data.pass);
		getch();
		textcolor(YELLOW);
	}
	else 
	{
		gotoxy(30,22);
		textcolor(RED);
		cputs("Not finde !!!"); 
		getch();
	}
}	
else if(sel==2) /* 姓名 */
{ 
	gotoxy(36,8);
	textcolor(YELLOW);
	cputs("Input the User name:"); 
	scanf("%s",findmess); 
	p=Locate(l,findmess,"name"); 		
	if(p) 
	{ 
		gotoxy(36,10);
		printf("Search Resault\n");
		gotoxy(36,12);
		printf("User ID:%s",p->data.num);
		gotoxy(36,14);
		printf("User Name:%s",p->data.name);
		gotoxy(36,16);
		printf("User Sex:%s",p->data.sex);
		textcolor(WHITE);
		gotoxy(36,18);
		cputs("User passwordx:");
		printf("%s",p->data.pass);
		getch();
		textcolor(YELLOW);
	} 
	else 
	{
		textcolor(RED);
		gotoxy(30,22);
		cputs("Not finde !!!"); 
	}
} 
else 
{
	textcolor(RED);
	gotoxy(30,22); 
	cputs("Error !!"); 
	getch();
}
} 

int cmpuser(Ulink l,char id[])/*******用于登录模块查找用户账号*******/
{ 
Unode *p; 
if(!l->next) 
{
gotoxy(30,4);
textcolor(RED);
     cputs("Error!!!"); 
    return 0; 
} 
	p=Locate(l,id,"num"); 
	if(p) 
	{ 
		return 1;
	}
	else 
	{
		gotoxy(30,22);
		textcolor(RED);
		cputs(" User id Not finde !!!"); 
		getch();
		return 0;
	}

} 

/******查询用户借书*******/
void Qur_borrow(BBlink l)
{ 
int sel; 
char findmess[20]; 
BBnode *p; 

if(!l->next) 
{
gotoxy(25,4);
textcolor(RED);
     cputs("Error!!!"); 
    return; 
} 
textcolor(RED);
gotoxy(25,4);
cputs("Please Select Search  Type !");
gotoxy(10,8);
textcolor(WHITE);
cputs("1.Search by borrow ID");
gotoxy(10,10);
cputs("2.Search by book Name");
gotoxy(10,12);
cputs("Please Select 1 or 2:");
scanf("%d",&sel); 
if(sel==1)/*学号 */ 
{
	gotoxy(36,8);
	textcolor(YELLOW);
	cputs("Input the Borrow ID:"); 
	scanf("%s",findmess); 
	p=Locate_borrow(l,findmess,"num"); 
	if(p) 
	{ 
		gotoxy(36,12);
		textcolor(WHITE);
		cputs("Borrow ID:");
		printf("%s",p->id);
		gotoxy(36,14);
		textcolor(WHITE);
		cputs("Book Name:");
		printf("%s",p->book);
		gotoxy(36,16);
		textcolor(WHITE);
		cputs("User name:");
		printf("%s",p->user);
		getch();
		textcolor(YELLOW);
	}
	else 
	{
		gotoxy(30,22);
		textcolor(RED);
		cputs("Not finde !!!"); 
		getch();
	}
}	
else if(sel==2) /* 姓名 */
{ 
	gotoxy(36,8);
	textcolor(YELLOW);
	cputs("Input the Book name:"); 
	scanf("%s",findmess); 
	p=Locate_borrow(l,findmess,"book");
	if(p) 
	{ 
		gotoxy(36,12);
		printf("Borrow ID:%s",p->id);
		gotoxy(36,14);
		printf("Book Name:%s",p->book);
		gotoxy(36,16);
		printf("User name:%s",p->user);
		getch();
		textcolor(YELLOW);
	} 
	else 
	{
		textcolor(RED);
		gotoxy(30,22);
		cputs("Not finde !!!"); 
		getch();
	}
} 
else 
{
	textcolor(RED);
	gotoxy(30,22); 
	cputs("Error !!"); 
	getch();
}
} 
void Del(Ulink l) /* 删除用户 */ 
{ 
	int sel; 
	Unode *p,*r; 
	char findmess[20]; 
	if(!l->next) 
	{ 
		gotoxy(30,4);
		textcolor(RED);
		cputs("not thing could delete!\n"); 
		getch();
		return; 
	} 
	textcolor(RED);
	gotoxy(25,4);
	puts("Please Select Delete  Type !");
	gotoxy(10,8);
	
	textcolor(WHITE);
	cputs("1.Delete by User ID");
	gotoxy(10,10);
	cputs("2.Delete by name");
	gotoxy(10,12);
	cputs("Please Select 1 or 2:");
	scanf("%d",&sel); 
	if(sel==1)     
	{ 
		gotoxy(36,8);
		textcolor(YELLOW);
		cputs("Input the User ID:"); 
		scanf("%s",findmess); 
		p=Locate(l,findmess,"num"); 
		if(p) 
		{ 
			r=l; 
			while(r->next!=p) 
				r=r->next; 
			r->next=p->next; 
			free(p); 
			gotoxy(30,22);
			textcolor(RED);
			usercount--;
			cputs("Delete success!\n");
			getch();
			textcolor(YELLOW);  
		} 
		else 
		{
			gotoxy(30,22);
			textcolor(RED);
			cputs("Not find !!"); 
			getch();
			
		}
	} 
	else if(sel==2) 
	{ 
		gotoxy(36,8);
		textcolor(YELLOW);
		cputs("Input the User name:"); 
		scanf("%s",findmess); 
		p=Locate(l,findmess,"name"); 
		if(p) 
		{ 
			r=l; 
			while(r->next!=p) 
				r=r->next; 
			r->next=p->next; 
			free(p); 
			gotoxy(30,22);
			textcolor(RED);
			usercount--;
			cputs("Delete success!\n"); 
			getch();
			textcolor(YELLOW);  
		} 
		else
		{
			gotoxy(30,22);
			textcolor(RED);
			cputs("Not find!!"); 
			getch();
		}
	} 
	else
	{
		gotoxy(30,22);
		textcolor(RED);
		cputs("Not find !!"); 
		getch();
	}
	textcolor(YELLOW);
} 
/* 还书的操作 */ 
void Del_borrow(BBlink l) 
{ 
		int sel; 
	BBnode *p,*r; 
	Bnode *L;
	char findmess[20];
	FILE *fp; /* 文件指针 */
Bnode *P,*R,*Q;
L=(Bnode*)malloc(sizeof(Bnode)); 
L->next=NULL; 
R=L; 
fp=fopen(file,"rb"); 
if(fp==NULL) 
{ 
	fp=fopen(file,"wb");
 }
while(!feof(fp))
{
    P=(Bnode*)malloc(sizeof(Bnode));
    if(fread(P,sizeof(Bnode),1,fp)) /* 将文件的内容放入接点中 */
    {
        P->next=NULL;
        R->next=P;
        R=P; /* 将该接点挂入连中 */
    }
}
fclose(fp); /* 关闭文件 */

	if(!l->next)
	{
		gotoxy(30,4);
		textcolor(RED);
		cputs("not Book could Return!\n");
		getch();
		return;
	}
	textcolor(RED);
	gotoxy(25,4);
	puts("Please Select Return  Type !");
	gotoxy(10,8);

	textcolor(WHITE);
	cputs("1.Return by Borrow ID");
	gotoxy(10,10);
	cputs("2.Return by book name");
	gotoxy(10,12);
	cputs("Please Select 1 or 2:");
	scanf("%d",&sel);
	if(sel==1)
	{
		gotoxy(36,8);
		textcolor(YELLOW);
		cputs("Input the Borrow ID:");
		scanf("%s",findmess);
		p=Locate_borrow(l,findmess,"num");
		if(p)
		{

				Q=locate(L,findmess,"num");
				if(Q) 
				{ 
					Q->data.sum=Q->data.sum-1;
						save(L);
				} 
			r=l; 
			while(r->next!=p) 
				r=r->next; 
			r->next=p->next; 
			free(p); 
			gotoxy(30,22);
			textcolor(RED);
			cputs("Return success!\n"); 
			borrowcount--;
			getch();
			textcolor(YELLOW);  
		} 
		else 
		{
			gotoxy(30,22);
			textcolor(RED);
			cputs("Note find !!"); 
			getch();
			
		}
	} 
	else if(sel==2) 
	{ 
		gotoxy(36,8);
		textcolor(YELLOW);
		cputs("Input the Book name:"); 
		scanf("%s",findmess); 
		p=Locate_borrow(l,findmess,"book");
		if(p) 
		{ 
			
				Q=locate(L,findmess,"name"); 
				if(Q) 
				{ 
					Q->data.sum=Q->data.sum-1;
						save(L);
				} 
			
			r=l; 
			while(r->next!=p) 
				r=r->next; 
			r->next=p->next; 
			free(p); 
			gotoxy(30,22);
			textcolor(RED);
			cputs("Borrow success!\n"); 
			borrowcount--;
			getch();
			textcolor(YELLOW);  
		} 
		else
		{
			gotoxy(30,18);
			textcolor(RED);
			cputs("Not find!!"); 
			getch();
		}
	} 
		
	else
	{
		gotoxy(30,22);
		textcolor(RED);
		cputs("Not finde !!"); 
		getch();
	}
	textcolor(YELLOW);
} 
/* ****用于管理员修改用户资料 ***/
void Modify(Ulink l) 
{ 
	Unode *p; 
	char findmess[20]; 
	if(!l->next) 
	{
		gotoxy(30,4);
		textcolor(RED);
		cputs("not thing could modify!"); 
		getch();
		return; 
	} 
	gotoxy(30,4);
	textcolor(RED);
	cputs("Modify User Message");
	gotoxy(25,8);
	textcolor(YELLOW);
	cputs("input the User Id:");
	scanf("%s",findmess); 
	p=Locate(l,findmess,"num"); 
	if(p) 
	{ 
		textcolor(YELLOW);
		gotoxy(25,10);
		printf("Inpute The New ID(old:%s):",p->data.num); 
		scanf("%s",p->data.num); 
		gotoxy(25,12);
		printf("Input The New Password(old:%s):",p->data.pass); 
		scanf("%s",p->data.pass); 
		gotoxy(25,14);
		printf("Input The New Name(old:%s):",p->data.name); 
		scanf("%s",p->data.name); 
		gotoxy(25,16);
		printf("Input The New Sex(old:%s):",p->data.sex); 
		scanf("%s",p->data.sex); 
		gotoxy(30,20);
		textcolor(RED);
		cputs("Modify Success !!!"); 
		getch();
		textcolor(YELLOW);
	} 
	else 
	{	
		gotoxy(30,16);
		textcolor(RED);
		cputs("Not Finde !!!"); 
		getch();
	}
} 







 /****供用户修改用户自己资料 */
void Modify_user(Ulink l)
{ 
	Unode *p; 
	char findmess[20]; 
	if(!l->next) 
	{
		gotoxy(30,4);
		textcolor(RED);
		cputs("not thing could modify!"); 
		getch();
		return; 
	} 
	gotoxy(30,4);
	textcolor(RED);
	cputs("Modify User Message");
	gotoxy(33,8);
	textcolor(YELLOW);
	strcpy(findmess,os->data.num);
	printf("your id:%s",findmess);
	p=Locate(l,findmess,"num"); 
	if(p) 
	{ 
		textcolor(YELLOW);
		gotoxy(24,10);
		printf("Input The New Password(old:%s):",p->data.pass); 
		scanf("%s",p->data.pass); 
		gotoxy(24,12);
		printf("Input The New Name(old:%s):",p->data.name); 
		scanf("%s",p->data.name); 
		gotoxy(24,14);
		printf("Input The New Sex(old:%s):",p->data.sex); 
		scanf("%s",p->data.sex); 
		gotoxy(31,18);
		textcolor(RED);
		cputs("Modify Success !!!"); 
		getch();
		textcolor(YELLOW);
	} 
	else 
	{	
		gotoxy(30,16);
		textcolor(RED);
		cputs("Not Finde !!!"); 
		getch();
	}
} 







/*******用户账号密码匹配*******/
int cmps(Ulink l,char id[20],char passw[20])
{ 

Unode *p; 
if(!l->next) 
{ 
gotoxy(34,18);
textcolor(RED);
textbackground(179);

     cputs("Missing Datas !!!"); 
getch();
    return 0; 
}
p=Locate(l,id,"num"); 
if(p) 
{ 
	if(strcmp(p->data.pass,passw)==0)
	{
			os=p;
			return 1;

	}
	else
	{
		textcolor(RED);
		gotoxy(34,18);
		textbackground(179);
		cputs("Password Error !!!"); 
		getch();
		return 0;
	}

 	
}
else 
{
	gotoxy(34,18);
	textcolor(RED);
	textbackground(179);
	cputs("User NotFind !!!"); 
	getch();
	return 0;
}
}

 /* 用于修改图书资料 */
int changeb(blink l,char findmess[20])
{ 
int tmp;
Bnode *p; 
if(!l->next) 
{
	gotoxy(30,4);
	textcolor(RED);
	cputs("not thing could modify!"); 
	getch();
	return 0; 
} 	
p=locate(l,findmess,"num"); 
if(p) 
{ 
	if(p->data.sum<p->data.count)
	{				
		booksum=booksum+1;
		p->data.sum=p->data.sum+1;
		save(l);
		return 1;
	}
	else
	{
		textcolor(WHITE);
		gotoxy(25,20);
		cputs("Book  have not return !!"); 
		getch();
		return 0;

	}
} 
else 
{	
	gotoxy(20,16);
	textcolor(RED);
	cputs("Not Finde !!!"); 
	getch();
	textcolor(YELLOW);
	return 0;
}
} 






/*******添加借书*******/
void Add_borrow(BBlink l) 
{ 
Ulink H;/* 连表 */ 
FILE *Fp; /* 文件指针 */ 
Unode *Q,*T;
blink L;/* 连表 */ 
FILE *FP; /* 文件指针 */ 
int ttl;

Bnode *P,*R;
char bookid[20];
char bookname[20];
char userid[20];
BBnode *p,*r,*s; 
char num[10]; 
r=l; 
s=l->next; 
while(r->next!=NULL) 
	r=r->next; 
L=(Bnode*)malloc(sizeof(Bnode)); 
L->next=NULL; 
R=L; 
FP=fopen(file,"rb"); 
if(FP==NULL) 
{ 
	FP=fopen(file,"wb"); 
 } 
while(!feof(FP)) 
{ 
    P=(Bnode*)malloc(sizeof(Bnode)); 
    if(fread(P,sizeof(Bnode),1,FP)) /* 将文件的内容放入接点中 */ 
    { 
        P->next=NULL; 
		bookcount=bookcount+P->data.count;
        R->next=P; 
        R=P; /* 将该接点挂入连中 */ 

    } 
} 
fclose(FP); /* 关闭文件 */ 


H=(Unode*)malloc(sizeof(Unode)); 
H->next=NULL; 
T=H;
Fp=fopen(ufile,"rb"); 
if(Fp==NULL) 
{ 
	Fp=fopen(ufile,"wb"); 
 } 
while(!feof(Fp)) 
{ 
    Q=(Unode*)malloc(sizeof(Unode));
    if(fread(Q,sizeof(Unode),1,Fp)) /* 将文件的内容放入接点中 */ 
    { 
        Q->next=NULL; 
        T->next=Q; 
        T=Q; /* 将该接点挂入连中 */ 
    } 
} 
fclose(Fp); 
textcolor(RED);
gotoxy(25,4);
cputs("Please input thease message");
gotoxy(30,10);
textcolor(YELLOW);
cputs("Input Borrow ID:");
scanf("%d",&ttl);
itoa(ttl,num,10) ;
p=(BBnode *)malloc(sizeof(BBnode));
while(s) 
{ 
	if(strcmp(s->id,num)==0) 
	{ 
		gotoxy(30,15);
		cputs("Borrow ID:");
		printf("'%s'",num); 
		cputs("is exist!");    
		gotoxy(26,22);
		textcolor(RED);
		cputs("please Press any key to continue...");  
		gotoxy(255,252);
		getch();                    
		return; 
	} 
	s=s->next; 
} 
strcpy(p->id,num);
gotoxy(31,12);
textcolor(YELLOW);
cputs("Input book id:"); 
scanf("%s",bookid);
gotoxy(31,14);
textcolor(YELLOW);
cputs("Input book name:"); 
scanf("%s",bookname);/***************************************图书判断在否***************************************/ 
if(cmpbook(L,bookid,bookname))
{
	strcpy(p->bookid,bookid);
	strcpy(p->book,bookname);
	gotoxy(31,16);
cputs("input your ID:"); 
scanf("%s",userid); /**************************************用户判断在否********************************/
if(cmpuser(H,userid))
{
	strcpy(p->user,userid);
	p->next=NULL; 
r->next=p; 
r=p; 
if(changeb(L,bookid))
{
gotoxy(30,22);
cputs("Borrow Success !!!");
Save_borrow(l);
borrowcount++;

getch();
}
}

}

textcolor(YELLOW);
} 


/*******我借的书*******/
void Myborrow()
{
int i;

BBlink l,p,r;/* 连表 */ 
FILE *fp; /* 文件指针 */ 
int count=0; 
l=(BBnode*)malloc(sizeof(BBnode)); 
l->next=NULL; 
r=l; 
fp=fopen(bfile,"rb"); 
if(fp==NULL) 
{ 
	fp=fopen(bfile,"wb"); 
} 
i=6;
while(!feof(fp)) 
{


	
	p=(BBnode*)malloc(sizeof(BBnode)); 
	if(fread(p,sizeof(BBnode),1,fp)) /* 将文件的内容放入接点中 */ 
	{ 
		textcolor(WHITE);
		gotoxy(30,4);
		cputs("Your borrow book");
		
		if(strcmp(p->user,os->data.num)==0)
		{
			textcolor(YELLOW);

			gotoxy(20,i);
			printf("Borrow ID:%s\tBook id:%s\tBook name:%s",p->id,p->bookid,p->book);
			i++;

			p->next=NULL; 
			r->next=p; 
			r=p; /* 将该接点挂入连中 */ 
			count++; 
		}
    } 
	myborrow=count;
	if(myborrow==0)
	{
		textcolor(YELLOW);
		gotoxy(30,13);
		cputs("You  no borrow !!");


	}



}
fclose(fp);
textcolor(YELLOW);
	gotoxy(65,2);
	printf("(borrow=%d)",myborrow);
		
	getch();

}
/******用户登录界面*******/
int login(Ulink l)
{
 

/*****************登陆窗口初始化****************************/
while(!flag)
{
char User_id[10],password[10],tmp;
int i=0;
User_id[0]='\0';
password[0]='\0';
textbackground(179);
clrscr();
gotoxy(33,23);
textcolor(YELLOW);
cputs("ESC = EXIT");
textcolor(WHITE);
textbackground(179);
box(1,1,80,24);
h_line(2,3,78);
gotoxy(15,2);
cputs("Login now please input the User__ID  and Password");
bar_(30,10,23,5,5);
/******************账号过滤*********************/
while(User_id[0]=='\0')
{
gotoxy(31,11);
textcolor(YELLOW);
textbackground(5);
cputs("User__ID:");
gotoxy(31,13);
cputs("Password:");
textbackground(179);
textcolor(WHITE);
gotoxy(28,7);
cputs("please input the User__ID!");
textbackground(179);
textcolor(YELLOW);
gotoxy(27,11);
putch(272);
gotoxy(27,13);
putch(' ');
gotoxy(40,11);
tmp=getch();
if(tmp==27)
{
flg=27;
return 0;
}
while(tmp!='\r'&&i<=9&&(tmp>=64&&tmp<=90)||(tmp>=97&&tmp<=122||(tmp>=48&&tmp<=57)))
{
textcolor(YELLOW);
textbackground(5);
	putch(tmp);
	User_id[i]=tmp;
	i++;
	tmp=getch();
	if(tmp==27)
	{
flg=27;
return 0;
}
}
User_id[i]='\0';
}
/**********************密码过滤****************************/
while(password[0]=='\0')
{
gotoxy(28,7);
textbackground(179);
textcolor(WHITE);
cputs("  input the password now  ");
textbackground(179);
textcolor(YELLOW);
gotoxy(27,13);
putch(272);
gotoxy(27,11);
putch(' ');
gotoxy(40,13);
i=0;
tmp=getch();
if(tmp==27)
{
flg=27;
return 0;
}
while(tmp!='\r'&&i<=10&&(tmp>=64&&tmp<=90)||(tmp>=97&&tmp<=122||(tmp>=48&&tmp<=57)))
{
	textbackground(5);
	putch('*');

	password[i]=tmp;
	i++;
	tmp=getch();
	if(tmp==27)
	{
flg=27;
return 0;
}
}
password[i]='\0';
}
/*************把账号和密码进行对比验证**************/
if(!strcmp(User_id,"admin")&&!strcmp(password,"admin"))
	{
		return 2;
	}
if(cmps(l,User_id,password))
{	 
	return 1;
}
}
}



/*******图书管理*******/
void bookss()
{
bookcount=0;
booksum=0;
while(1)
{
int flag;
blink l;/* 连表 */ 
FILE *fp; /* 文件指针 */ 
int count=0; 
Bnode *p,*r;
l=(Bnode*)malloc(sizeof(Bnode)); 
l->next=NULL; 
r=l; 
fp=fopen(file,"rb"); 
if(fp==NULL) 
{ 
	fp=fopen(file,"wb"); 
 } 
while(!feof(fp)) 
{ 
    p=(Bnode*)malloc(sizeof(Bnode)); 
    if(fread(p,sizeof(Bnode),1,fp)) /* 将文件的内容放入接点中 */ 
    { 
        p->next=NULL; 
		bookcount=bookcount+p->data.count;
		booksum=booksum+p->data.sum;
        r->next=p; 
        r=p; /* 将该接点挂入连中 */ 
        count++; 
    } 
} 
fclose(fp); /* 关闭文件 */ 
gotoxy(30,4);
printf("Ok loading %ds.\n",count); 

while(1) 
{	
	textbackground(179);
	clrscr();
	textcolor(YELLOW);
	box(1,1,80,24);
	h_line(2,3,78);
	gotoxy(3,2);
	textcolor(RED);
	cputs("A");
	textcolor(BLUE);
	cputs("dd Book  ");
	textcolor(RED);
	cputs("D");
	textcolor(BLUE);
	cputs("el Book  ");
	textcolor(RED);
	cputs("S");
	textcolor(BLUE);
	cputs("earch Book  ");
	textcolor(RED);
	cputs("M");
	textcolor(BLUE);
	cputs("odify Book  ");
	textcolor(YELLOW);
	printf("(Book=%d/%d)",bookcount-booksum,bookcount);
	printf("%d",booksum);
	gotoxy(50,50);
	flag=getch(); 
    switch(flag)		
	{ 		
	case 'a':
		add(l);
		save(l);
		break; /*************添加图书*********/
	case 'd':
		del(l);
		save(l); 
		break;/*************删除图书**********/
	case 's':
		qur(l);
		break;
	case 'm':
		mod(l);
		save(l); /*************修改图书**********/
		break;
	case 27:
		return;
		
	} 

} 	

}

}

/*******用户管理*******/
void users()
{
while(1)
{
int flag;
Ulink l;/* 连表 */ 
FILE *fp; /* 文件指针 */ 
int count=0; 
Unode *p,*r;
l=(Unode*)malloc(sizeof(Unode)); 
l->next=NULL; 
r=l;
fp=fopen(ufile,"rb"); 
if(fp==NULL) 
{ 
	fp=fopen(ufile,"wb"); 
 } 
while(!feof(fp)) 
{ 
    p=(Unode*)malloc(sizeof(Unode)); 
    if(fread(p,sizeof(Unode),1,fp)) /* 将文件的内容放入接点中 */ 
    { 
        p->next=NULL; 
        r->next=p; 
        r=p; /* 将该接点挂入连中 */ 
        count++; 
    } 
	usercount=count;
} 
fclose(fp); /* 关闭文件 */ 
gotoxy(30,4);
printf("Ok loading %ds.\n",count); 

while(1) 
{	
	textbackground(179);
	clrscr();
	textcolor(YELLOW);
	box(1,1,80,24);
	h_line(2,3,78);
	gotoxy(3,2);
	textcolor(RED);
	cputs("A");
	textcolor(BLUE);
	cputs("dd user  ");
	textcolor(RED);
	cputs("D");
	textcolor(BLUE);
	cputs("el user  ");
	textcolor(RED);
	cputs("S");
	textcolor(BLUE);
	cputs("earch user  ");
	textcolor(RED);
	cputs("M");
	textcolor(BLUE);
	cputs("odify user  ");
	textcolor(YELLOW);
	printf("count: (user=%d)",usercount);
	gotoxy(50,50);
	flag=getch(); 
    switch(flag)		
	{ 		
	case 'a':
		Add(l);
		Save(l);
		break; /*************添加用户**********/
	case 'd':
		Del(l);
		Save(l); 
		break;/*************删除用户**********/
	case 's':
		Qur(l);
		break;
	case 'm':
		Modify(l);
		Save(l); /*************修改用户**********/
		break;
	case 27:
		return;
		
	} 

} 	

}

}

/*******借书管理*******/
void borrow()
{
while(1)
{
int flag;
BBlink l,p,r;/* 连表 */ 
FILE *fp; /* 文件指针 */ 
int count=0; 
l=(BBnode*)malloc(sizeof(BBnode)); 
l->next=NULL; 
r=l; 
fp=fopen(bfile,"rb"); 
if(fp==NULL) 
{ 
	fp=fopen(bfile,"wb"); 
} 
while(!feof(fp)) 
{
	p=(BBnode*)malloc(sizeof(BBnode)); 
	if(fread(p,sizeof(BBnode),1,fp)) /* 将文件的内容放入接点中 */ 
	{ 
		p->next=NULL; 
        r->next=p; 
        r=p; /* 将该接点挂入连中 */ 
        count++; 
    } 
	borrowcount=count;
} 
while(1) 
{	
	textbackground(179);
	clrscr();
	textcolor(YELLOW);
	box(1,1,80,24);
	h_line(2,3,78);
	gotoxy(3,2);
	textcolor(RED);
	cputs("B");
	textcolor(BLUE);
	cputs("orrow book  ");
	textcolor(RED);
	cputs("R");
	textcolor(BLUE);
	cputs("eturn book  ");
	textcolor(RED);
	cputs("S");
	textcolor(BLUE);
	cputs("earch borrow  ");
	textcolor(YELLOW);
	printf("count: (borrow=%d)",borrowcount);
	textcolor(RED);
	gotoxy(50,50);
	flag=getch(); 
    switch(flag)		
	{ 		
	case 'b':
		Add_borrow(l);
		
		break; /*************添加用户**********/
	case 'r':
		Del_borrow(l);
		Save_borrow(l);
		break;
	case 's':
		Qur_borrow(l);
		break;
	case 27:
		return;
		
	} 

} 	

}


}



/*******管理员选择界面*******/
void choose()
{
while(1)
{

textbackground(179);
clrscr();
gotoxy(33,2);
textcolor(WHITE);
cputs("Administrastor");
textcolor(YELLOW);
box(1,1,80,24);
h_line(2,3,78);
gotoxy(3,6);
cputs(">>>-------------------------1.User Management----------------------------<<<");
gotoxy(3,10);
cputs(">>>-------------------------2.Book Management----------------------------<<<");
	gotoxy(3,14);
cputs(">>>-------------------------3.Borrow Books-------------------------------<<<");
gotoxy(30,22);
textcolor(RED);
cputs("Please Select!!!");
flg=getch();
if(flg=='2')		
	bookss();									
if(flg=='1')
	users();
if(flg=='3')
	borrow();
if(flg==27)
{
	flg=-1;
	return;
}	
}		
}
void admin()
{
while(1)
{
choose();	
if(flg=='1')	
bookss();
if(flg=='2')
users();
if(flg=='3')
borrow();
if(flg==27)
{
return;
}
}
}
/******用户查询自己的信息*******/
void show(Ulink l)
{
if(l) 
	{ 
		gotoxy(30,8);
		textcolor(WHITE);
		cputs("User ID:");
		printf("%s",l->data.num);
		gotoxy(30,10);
		textcolor(WHITE);
		cputs("User Name:");
		printf("%s",l->data.name);
		gotoxy(30,12);
		textcolor(WHITE);
		cputs("User Sex:");
		printf("%s",l->data.sex);
		textcolor(WHITE);
		gotoxy(30,14);
		textcolor(WHITE);
		cputs("User password:");
		printf("%s",l->data.pass);
		getch();
		textcolor(YELLOW);
	}
	else 
	{
		gotoxy(30,22);
		textcolor(RED);
		cputs("Error !!!"); 
		getch();
	}


}
/*******用户操作界面*******/
void user(Ulink h)
{
int flag;
BBlink l,p,r;/* 连表 */ 
FILE *fp; /* 文件指针 */ 
int count=0; 
l=(BBnode*)malloc(sizeof(BBnode)); 
l->next=NULL; 
r=l; 
fp=fopen(bfile,"rb"); 
if(fp==NULL) 
{ 
	fp=fopen(bfile,"wb"); 
} 
while(!feof(fp)) 
{
	p=(BBnode*)malloc(sizeof(BBnode)); 
	if(fread(p,sizeof(BBnode),1,fp)) /* 将文件的内容放入接点中 */ 
	{ 
		p->next=NULL; 
        r->next=p; 
        r=p; /* 将该接点挂入连中 */ 
        count++; 
    } 
} 
	while(1) 
{	
	textbackground(179);
	clrscr();
	textcolor(YELLOW);
	box(1,1,80,24);
	h_line(2,3,78);
	gotoxy(3,2);
	textcolor(RED);
	cputs("A.");
	textcolor(BLUE);
	cputs("my message  ");
	textcolor(RED);
	cputs("B.");
	textcolor(BLUE);
	cputs("modyfy my message  ");
	textcolor(RED);
	cputs("C.");
	textcolor(BLUE);
	cputs("my borrow  ");
	textcolor(RED);
	cputs("D.");
	textcolor(BLUE);
	cputs("search book");
	textcolor(YELLOW);
	gotoxy(50,50);
	flag=getch(); 
    switch(flag)		
	{ 		
	case 'a':
		show(os);
		
		break; /*************添加用户**********/
	case 'b':
		Modify_user(h);
		Save(h);
		
		break;/*************删除用户**********/
	case 'c':
		Myborrow();
		break;
	case 'd':
		usersearch();

		
		break;
	case 27:
		return;
		
	} 

} 

}

main()
{

Ulink h,os;/* 连表 */ 
FILE *fp; /* 文件指针 */ 
Unode *p,*r;
h=(Unode*)malloc(sizeof(Unode)); 
h->next=NULL; 
r=h; 
fp=fopen(ufile,"rb"); 
if(fp==NULL) 
{ 
	fp=fopen(ufile,"wb"); 
 } 
while(!feof(fp)) 
{ 
    p=(Unode*)malloc(sizeof(Unode)); 
    if(fread(p,sizeof(Unode),1,fp)) /* 将文件的内容放入接点中 */
    {
        p->next=NULL;
        r->next=p;
        r=p; /* 将该接点挂入连中 */

    }
}
fclose(fp);
system("wellcome");
	if(flg==27)
	{
		flg=-1;
		return;
	}
		while(1)
		{
			flag=login(h);
			if(flg==27)
				{
					flg=-1;
					break;
				}

				if(flag==2)
				{
					choose();
					flag=0;
				}
				if(flag==1)
				{
					user(h);
					flag=0;
				}

		}

}
