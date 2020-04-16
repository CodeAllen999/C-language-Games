#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#define LEN sizeof(struct student)
#define FORMAT "%-8d%-15s%-12.1lf%-12.1lf%-12.1lf%-12.1lf\n"
#define DATA stu[i].num,stu[i].name,stu[i].elec,stu[i].expe,stu[i].requ,stu[i].sum

/* 【自学去】网站收集 http://www.zixue7.com */

struct student/*定义学生成绩结构体*/
{ int num;/*学号*/
  char name[15];/*姓名*/
  double elec;/*选修课*/
  double expe;/*实验课*/
  double requ;/*必修课*/
  double sum;/*总分*/
};
struct student stu[50];/*定义结构体数组*/
void in();/*录入学生成绩信息*/
void show();/*显示学生信息*/
void order();/*按总分排序*/
void del();/*删除学生成绩信息*/
void modify();/*修改学生成绩信息*/
void menu();/*主菜单*/
void insert();/*插入学生信息*/
void total();/*计算总人数*/
void search();/*查找学生信息*/
void main()/*主函数*/
{ int n;
  menu();
  scanf("%d",&n);/*输入选择功能的编号*/
  while(n)
  { switch(n)
     { case 1: in();break;
       case 2: search();break;
       case 3: del();break;
       case 4: modify();break;
       case 5: insert();break;
       case 6: order();break;
       case 7: total();break;
       default:break;
     }
    getch();
    menu();/*执行完功能再次显示菜单界面*/
    scanf("%d",&n);
  }
}

void in()/*录入学生信息*/
{ int i,m=0;/*m是记录的条数*/
  char ch[2];
  FILE *fp;/*定义文件指针*/
  if((fp=fopen("data.txt","a+"))==NULL)/*打开指定文件*/
     { printf("can not open\n");return;}
  while(!feof(fp)) { 
	  if(fread(&stu[m] ,LEN,1,fp)==1)
		  m++;/*统计当前记录条数*/
  }
  fclose(fp);
  if(m==0) 
	  printf("No record!\n");
  else 
  {
	  system("cls");
          show();/*调用show函数，显示原有信息*/
  }
  if((fp=fopen("data.txt","wb"))==NULL)
     { printf("can not open\n");return;}
  for(i=0;i<m;i++) fwrite(&stu[i] ,LEN,1,fp);/*向指定的磁盘文件写入信息*/
  printf("please input(y/n):");
  scanf("%s",ch);
while(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*判断是否要录入新信息*/
    {
    printf("number:");scanf("%d",&stu[m].num);/*输入学生学号*/
    for(i=0;i<m;i++)
	    if(stu[i].num==stu[m].num)
	    {
	    printf("the number is existing,press any to continue!");
	    getch();
	    fclose(fp);
	    return;
	    }
     printf("name:");scanf("%s",stu[m].name);/*输入学生姓名*/
     printf("elective:");scanf("%lf",&stu[m].elec);/*输入选修课成绩*/
     printf("experiment:");scanf("%lf",&stu[m].expe);/*输入实验课成绩*/
     printf("required course:");scanf("%lf",&stu[m].requ);/*输入必修课成绩*/
     stu[m].sum=stu[m].elec+stu[m].expe+stu[m].requ;/*计算出总成绩*/
     if(fwrite(&stu[m],LEN,1,fp)!=1)/*将新录入的信息写入指定的磁盘文件*/
       { printf("can not save!"); getch(); }
     else { printf("%s saved!\n",stu[m].name);m++;}
     printf("continue?(y/n):");/*询问是否继续*/
     scanf("%s",ch);
  }
  fclose(fp);
  printf("OK!\n");
 }

void show()
 { FILE *fp;
   int i,m=0;
   fp=fopen("data.txt","rb");
   while(!feof(fp))
   {
   if(fread(&stu[m] ,LEN,1,fp)==1) 
   m++;
   }  
   fclose(fp);
   printf("number  name           elective    experiment  required    sum\t\n");
   for(i=0;i<m;i++)
       { 
	   printf(FORMAT,DATA);/*将信息按指定格式打印*/
       }
     }
 
void menu()/*自定义函数实现菜单功能*/
{
  system("cls");
  printf("\n\n\n\n\n");
  printf("\t\t|---------------------STUDENT-------------------|\n");
  printf("\t\t|\t 0. exit                                |\n");
  printf("\t\t|\t 1. input record                        |\n");
  printf("\t\t|\t 2. search record                       |\n");
  printf("\t\t|\t 3. delete record                       |\n");
  printf("\t\t|\t 4. modify record                       |\n");
  printf("\t\t|\t 5. insert record                       |\n");
  printf("\t\t|\t 6. order                               |\n");
  printf("\t\t|\t 7. number                              |\n");
  printf("\t\t|-----------------------------------------------|\n\n");
  printf("\t\t\tchoose(0-7):");
}

void order()/*自定义排序函数*/
{ FILE *fp;
  struct student t;
  int i=0,j=0,m=0;
  if((fp=fopen("data.txt","r+"))==NULL)
     { 
	printf("can not open!\n");
        return;
  }
  while(!feof(fp)) 
  if(fread(&stu[m] ,LEN,1,fp)==1) 
	  m++;
  fclose(fp);
  if(m==0) 
  {
	  printf("no record!\n");
	  return;
  }
  if((fp=fopen("data.txt","wb"))==NULL)
     {
	  printf("can not open\n");
	  return;}
  for(i=0;i<m-1;i++)
      for(j=i+1;j<m;j++)/*双重循环实现成绩比较并交换*/
          if(stu[i].sum<stu[j].sum)
          { t=stu[i];stu[i]=stu[j];stu[j]=t;}
	  if((fp=fopen("data.txt","wb"))==NULL)
     { printf("can not open\n");return;}
  for(i=0;i<m;i++)/*将重新排好序的内容重新写入指定的磁盘文件中*/
      if(fwrite(&stu[i] ,LEN,1,fp)!=1)
       { 
        printf("%s can not save!\n"); 
        getch();
      }
  fclose(fp);
  printf("save successfully\n");
}
void del()/*自定义删除函数*/
{FILE *fp;
  int snum,i,j,m=0;
  char ch[2];
  if((fp=fopen("data.txt","r+"))==NULL)
     { printf("can not open\n");return;}
  while(!feof(fp))  if(fread(&stu[m],LEN,1,fp)==1) m++;
  fclose(fp);
  if(m==0) 
  {
	  printf("no record!\n");
	  return;
  }
  printf("please input the number:");
  scanf("%d",&snum);
    for(i=0;i<m;i++)
     if(snum==stu[i].num)
	     break;
     printf("find the student,delete?(y/n)");
     scanf("%s",ch);
      if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*判断是否要进行删除*/
      for(j=i;j<m;j++)
	      stu[j]=stu[j+1];/*将后一个记录移到前一个记录的位置*/
      m--;/*记录的总个数减1*/
      if((fp=fopen("data.txt","wb"))==NULL)
     { printf("can not open\n");return;}
  for(j=0;j<m;j++)/*将更改后的记录重新写入指定的磁盘文件中*/
      if(fwrite(&stu[j] ,LEN,1,fp)!=1)
       { printf("can not save!\n");
      getch();}
  fclose(fp);
  printf("delete successfully!\n");
}

void search()/*自定义查找函数*/
{ FILE *fp;
  int snum,i,m=0;
  char ch[2];
  if((fp=fopen("data.txt","rb"))==NULL)
     { printf("can not open\n");return;}
  while(!feof(fp))  if(fread(&stu[m],LEN,1,fp)==1) m++;
  fclose(fp);
  if(m==0) {printf("no record!\n");return;}
  printf("please input the number:");
  scanf("%d",&snum);
  for(i=0;i<m;i++)
     if(snum==stu[i].num)/*查找输入的学号是否在记录中*/
     { printf("find the student,show?(y/n)");
     scanf("%s",ch);
      if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0) 
        {
          printf("number  name           elective    experiment  required    sum\t\n");
          printf(FORMAT,DATA);/*将查找出的结果按指定格式输出*/
	  break;
     }
     }   
  if(i==m) printf("can not find the student!\n");/*未找到要查找的信息*/
}

void modify()/*自定义修改函数*/
{ FILE *fp;
  int i,j,m=0,snum;
  if((fp=fopen("data.txt","r+"))==NULL)
     { printf("can not open\n");return;}
  while(!feof(fp))  
 if(fread(&stu[m],LEN,1,fp)==1) m++;
  if(m==0) {printf("no record!\n");
  fclose(fp);
  return;
  }
  printf("please input the number of the student which do you want to modify!\n");
  scanf("%d",&snum);
  for(i=0;i<m;i++)
	  if(snum==stu[i].num)/*检索记录中是否有要修改的信息*/
		  break;
	  printf("find the student!you can modify!\n");
	  printf("name:\n");
	  scanf("%s",stu[i].name);/*输入名字*/
          printf("\nelective:");
	  scanf("%lf",&stu[i].elec);/*输入选修课成绩*/
          printf("\nexperiment:");
	  scanf("%lf",&stu[i].expe);/*输入实验课成绩*/
          printf("\nrequired course:");
	  scanf("%lf",&stu[i].requ);/*输入必修课成绩*/
	  stu[i].sum=stu[i].elec+stu[i].expe+stu[i].requ;
	  if((fp=fopen("data.txt","wb"))==NULL)
     { printf("can not open\n");return;}
	  for(j=0;j<m;j++)/*将新修改的信息写入指定的磁盘文件中*/
	  if(fwrite(&stu[j] ,LEN,1,fp)!=1)
       { printf("can not save!"); getch(); }
  fclose(fp);
 }

void insert()/*自定义插入函数*/
{ FILE *fp;
  int i,j,k,m=0,snum;
  if((fp=fopen("data.txt","r+"))==NULL)
     { printf("can not open\n");return;}
  while(!feof(fp))  
 if(fread(&stu[m],LEN,1,fp)==1) m++;
  if(m==0) {printf("no record!\n");
  fclose(fp);
  return;
  }
  printf("please input position where do you want to insert!(input the number)\n");
  scanf("%d",&snum);/*输入要插入的位置*/
  for(i=0;i<m;i++)
	  if(snum==stu[i].num)
		  break;
	  for(j=m-1;j>i;j--)
           stu[j+1]=stu[j];/*从最后一条记录开始均向后移一位*/
	  printf("now please input the new information.\n");
          printf("number:");
	  scanf("%d",&stu[i+1].num);
	  for(k=0;k<m;k++)
	    if(stu[k].num==stu[i+1].num)
	    {
	    printf("the number is existing,press any to continue!");
	    getch();
	    fclose(fp);
	    return;
	    }
	  printf("name:\n");
	  scanf("%s",stu[i+1].name);
          printf("\nelective:");
	  scanf("%lf",&stu[i+1].elec);
          printf("\nexperiment:");
	  scanf("%lf",&stu[i+1].expe);
          printf("\nrequired course:");
	  scanf("%lf",&stu[i+1].requ);
	  stu[i+1].sum=stu[i+1].elec+stu[i+1].expe+stu[i+1].requ;
	  if((fp=fopen("data.txt","wb"))==NULL)
     { printf("can not open\n");return;}
	  for(k=0;k<=m;k++)
	  if(fwrite(&stu[k] ,LEN,1,fp)!=1)/*将修改后的记录写入磁盘文件中*/
       { printf("can not save!"); getch(); }
  fclose(fp);
 }

void total()
{ FILE *fp;
  int m=0;
  if((fp=fopen("data.txt","r+"))==NULL)
     { printf("can not open\n");return;}
  while(!feof(fp))  
	  if(fread(&stu[m],LEN,1,fp)==1) 
		  m++;/*统计记录个数即学生个数*/
  if(m==0) {printf("no record!\n");fclose(fp);return;}
  printf("the class are %d students!\n",m);/*将统计的个数输出*/
  fclose(fp);
 }
