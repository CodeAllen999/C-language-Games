/* 【自学去】网站收集 http://www.zixue7.com */

#include "stdafx.h"

#include"stdio.h"
#include"conio.h"
#include"string.h"
#include"stdlib.h"
int N;
char mima[20]="mm";
/**********定义图书结构体类型book*******/
struct book
{
    long num;
    char name[20];
    char publish[20];/*出版社*/
    struct time
    {
        int day;
        int month;
        int year;
    }t;
    int jie;/*借阅*/
}bk[20];
/********建立图书信息库********/
void xinxi()
{
    int i;
    system("CLS");
    printf("\t\t         =====================        \n");
    printf("\t\t               录入图书信息              \n");
    printf("\t\t         =====================        \n\n");
	printf("\t\t请输入您要录入的数量:");
	scanf("%d",&N);
    for(i=0;i<N;i++)
    {
		printf("\t\t请输入第%d本书的编号:",i+1);
        scanf("%d",&bk[i].num);
        printf("\t\t请输入第%d本书的名称:",i+1);
        scanf("%s",bk[i].name);
        printf("\t\t请输入第%d本书的出版社:",i+1);
        scanf("%s",bk[i].publish);
        printf("\t\t请输入第%d本书的出版时间(用逗号隔开):",i+1);
        scanf("%d,%d,%d",&bk[i].t.year,&bk[i].t.month,&bk[i].t.day);
        printf("\t\t该书是否已经被借阅,已被借阅输入'1'，未被借阅输入'0':");
        scanf("%d",&bk[i].jie);
		printf("--------------------------------------------------------------------------------\n");
    }
	system("CLS");
    printf("\t\t         =====================        \n");
    printf("\t\t               信息录入完成              \n");
    printf("\t\t         =====================        \n");
    printf("\n\t\t             按任意键继续...\n");
}
/******主菜单******/
int mymainmenu()
{
    int x;
	printf("\n\n\n\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|           欢迎光临图书管理系统          |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|           1.管理员模式                   |\n");
    printf("\t\t|           2.客户模式                     |\n");
    printf("\t\t|           3.退出系统                     |\n");
    printf("\t\t|--------------------------------------------------------------|\n");
    printf("\n\t\t请输入您的选择:");
    scanf("%d",&x);
    return x;
}
/**************管理员密码验证*****************/
int mimayanzheng()
{
	char temp_mima[20];/*用来存放用户输入的密码*/
    printf("\n");
    printf("\t\t         ======================        \n");
    printf("\t\t            欢迎使用管理员模式            \n");
    printf("\t\t         ======================        \n");
    printf("\n");
    printf("\t\t          请输入密码:");
    scanf("%s",temp_mima);
	if(strcmp(temp_mima,mima)==0)/*比较密码*/
		return 1;
	else
		return 0;
}
/**************修改密码***********/
void xiugaimima()
{
	char temp_mima[20],temp1[20],temp2[20];/* temp_mima[20]用来存放用户输入的密码，temp1[20],temp2[
20]分别用来存放用户输入的两次修改的密码*/    
printf("\n");
    printf("\t\t         ======================        \n");
    printf("\t\t                 修改密码                 \n");
    printf("\t\t         ======================        \n");
    printf("\n");
	printf("\t\t           请输入原始密码:");
	scanf("\t\t%s",temp_mima);
    while(1)
    {
	if(strcmp(temp_mima,mima)==0)/*比较密码*/
	{
		printf("\t请输入新密码:");
		scanf("%s",temp1);
		printf("\t请再输入一次:");
		scanf("%s",temp2);
		if(strcmp(temp1,temp2)==0)/*如果输入的两次新密码都相同*/
		{
			printf("\t修改密码成功!!请记牢密码,任意键返回...");
			strcpy(mima,temp1);
			getch();break;
		}
		else
		{
			printf("\t输入两次密码不相同，修改失败!任意键返回...");
			getch();
			break;
		}
	}
	else
	{
		printf("\t密码错误!您不能进行密码修改!任意键返回...");
		getch();
		break;
	}
}
}	
/**************管理员模式****************/
int adm()
{
    int x;
	printf("\n\n\n\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|               管理员模式                |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|           1.录入图书信息                |\n");
    printf("\t\t|           2.查看图书信息                |\n");
    printf("\t\t|           3.修改图书信息                |\n");
    printf("\t\t|           4.修改管理密码                |\n");
    printf("\t\t|           5.退出系统                    |\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\n\t\t请输入您的选择:");
    scanf("%d",&x);
    return x;
}
/******************客户模式********************/
int peo()
{
    int x;
	printf("\n\n\n\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|               欢迎光临                  |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|           1.查看图书信息                |\n");
    printf("\t\t|           2.借阅图书                    |\n");
    printf("\t\t|           3.退出系统                    |\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\n\t\t请输入您的选择:");
    scanf("%d",&x);
    return x;
}
/*********查看所有图书*******/
void show_all_book()
{
	int i;
	if(bk[0].num==0&&bk[0].t.year==0||N==0)/*当bk[0].num，bk[0].t.year，结构体数组等值同时为零时表示无图书信息*/
		printf("\t数据不存在，请先录入数据!\n\t\t按任意键返回...");
	else
	{
		printf("\t编号    图书名称     出版社        出版时间     状态\n");
		for(i=0;i<N;i++)
		{
			printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
			if(bk[i].jie==0)
				printf("未借阅\n");
			else
				printf("已借阅\n");
		}
	}
}
/*********按书名查看********/
void showbook_name()
{
    int i,k=0,n;/*k用来标记是否存在该书*/
    char book_name[20];
    printf("\t\t         =====================        \n");
    printf("\t\t               按书名查看                \n");
    printf("\t\t         =====================        \n");
    printf("\n\t\t请输入您要查看的图书名称:");
    scanf("%s",book_name);
    for(i=0;i<N;i++)
        if(strcmp(book_name,bk[i].name)==0)
		{
			n=i;
			if(k==0)/* "项目"只输出一次*/
			    printf("\t编号    图书名称     出版社        出版时间     状态\n");
            printf("\t%-7d %-8s %12s   %4d年%2d月%2d日 ",bk[n].num,bk[n].name,bk[n].publish,bk[n].t.year,bk[n].t.month,bk[n].t.day);
		    if(bk[n].jie==1)
                printf("已被借阅\n");
            else
                printf("可以借阅\n");
	            printf("按任意键返回...");
			k++; /*k值不为零则表示找到图书*/
		}
		if(k==0)  /*k值为零则表示未找到图书*/
			printf("\t不存在该书!按任意键返回...");
}
/*********按书号查看********/
void showbook_num()
{
    int n,book_num,i,k=0;/*k用来标记是否存在该书*/
    printf("\t\t         =====================        \n");
    printf("\t\t               按书号查看                \n");
    printf("\t\t         =====================        \n");
    printf("\n\t\t请输入您要查看的图书编号:");
    scanf("%d",&book_num);
    for(i=0;i<N;i++)
        if(book_num==bk[i].num)
		{
			n=i;
			if(k==0)/*项目只输出一次*/
			    printf("\t编号    图书名称     出版社        出版时间     状态\n");
            printf("\t%-7d %-8s %12s   %4d年%2d月%2d日 ",bk[n].num,bk[n].name,bk[n].publish,bk[n].t.year,bk[n].t.month,bk[n].t.day);
		    if(bk[n].jie==1)
                printf("已被借阅\n");
            else
                printf("可以借阅\n");
			k++;
			printf("\t按任意键返回...");
		}
	if(k==0) /*k为零则表示未找到图书*/
		printf("\t不存在该书!按任意键返回...");    	
}

/********显示全部已借阅的图书**********/
void yijieyue()
{
    int i,k=0;
	if(bk[0].num==0&&bk[0].t.year==0||N==0)
		 printf("\t数据不存在，请先录入数据!\n\t\t按任意键返回...");
	else
	{
	    for(i=0;i<N;i++)
			if(bk[i].jie==1)
			{
				if(k==0)
				    printf("\t编号    图书名称     出版社        出版时间     \n");
				printf("\t%-7d %-8s %12s   %4d年%2d月%2d日 \n",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
                k++;			
			}
            if(k==0)
				printf("\n\t\t目前没有任何书借出。按任意键继续...");
	}
}
/********显示全部未借阅的图书********/
void weijieyue()
{
    int i,k=0;
	if(bk[0].num==0&&bk[0].t.year==0||N==0)
		 printf("\t数据不存在，请先录入数据!\n\t\t按任意键返回...");
	else
	{
	    for(i=0;i<N;i++)
			if(bk[i].jie==0)
			{
				if(k==0)
				    printf("\t编号    图书名称     出版社        出版时间     \n");
				printf("\t%-7d %-8s %12s   %4d年%2d月%2d日 \n",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
			    k++;
			}
			if(k==0)
               printf("\n\t很遗憾！目前所有的书都被借出了。按任意键继续...");
	}
}
/*****查看图书菜单******/
void show()
{
    int x;
	do
	{
		 system("cls");
		 printf("\n\n\n\n");
    	 printf("\t\t|-------------------------------------------------------------|\n");
    	 printf("\t\t|                                         |\n");
    	 printf("\t\t|         =====================        |\n");
    	 printf("\t\t|              查看图书信息               |\n");
    	 printf("\t\t|         =====================        |\n");
    	 printf("\t\t|                                         |\n");
    	 printf("\t\t|           1.按书名查找                  |\n");
    	 printf("\t\t|           2.按书号查找                  |\n");
    	 printf("\t\t|           3.查看所有未借阅图书          |\n");
    	 printf("\t\t|           4.查看所有已借阅图书          |\n");
    	 printf("\t\t|           5.查看所有图书                |\n");
    	 printf("\t\t|           6.返回主菜单                  |\n");
    	 printf("\t\t|-------------------------------------------------------------|\n");
    	 printf("\n\t\t请输入您的选择:");
    	 scanf("%d",&x);
    	 switch(x)
    	 {
         	 case 1:system("cls");showbook_name();getch();break;/*按书名查看*/
        	 case 2:system("cls");showbook_num();getch();break;/*按书号查看*/
       	   	 case 3:system("cls");weijieyue();getch();break;/*查看未借阅图书*/
       	   	 case 4:system("cls");yijieyue();getch();break;/*查看已借阅图书*/
		 	 case 5:system("cls");show_all_book();getch();break;/*查看所有图书*/	
    	 }                                    
	}while(x!=6);
}
/*********按书名借阅*******/
void jie_name()
{
	char jy[2],name[20];/*jy用来表示是否确定借阅*/
	int i,book_xb,k=0;/*k用来标记是否存在该书*/
	printf("\t\t         ======================       \n");
    printf("\t\t                按书名借阅               \n");
    printf("\t\t         ======================       \n");
	while(1)
	{
    printf("\n\t\t请输入书名:");
    scanf("%s",name);
    for(i=0;i<N;i++)
        if(strcmp(bk[i].name,name)==0&&bk[i].jie!=1)/*找到图书并确认图书没有被借出，记录图书下标*/
		{
		    book_xb=i;
			k++;
		}
	if(k==0)
	{
		printf("\t不存在该书，或该书已经借出!请正确输入图书名称!\n\t\t按任意键返回...");
		getch();
        break;
	}
	if(k==1)
	    printf("\t编号    图书名称     出版社        出版时间     状态\n");
    printf("\t%-7d %-8s %12s   %4d年%2d月%2d日 ",bk[book_xb].num,bk[book_xb].name,bk[book_xb].publish,bk[book_xb].t.year,bk[book_xb].t.month,bk[book_xb].t.day);
    if(bk[book_xb].jie==1)
        printf("已被借阅\n");
    else
        {
           printf("可以借阅\n\t是否借阅？(是：'y'，否：'n')：");
           scanf("%s",jy);
           if(strcmp(jy,"n")==0)
           {
                printf("\t借阅取消，按任意键返回....");
                getch();
                break;
           }
           else if(strcmp(jy,"y")==0)
           {
                printf("\t借阅成功！按任意键返回...");
				bk[book_xb].jie=1;
                getch();
                break;
           }
           else
           {
                printf("\t输入有错！按任意键重新输入...");
				getch();
                break;
           }           
		}
	}
}
/*********按书号借阅*******/
void jie_num()
{
	long i,k=0,book_xb,book_num;/*k用来标记是否存在该书*/
	char jy[2];/*jy用来表示是否确定借阅*/
	printf("\t\t         ======================       \n");
    printf("\t\t                按书号借阅               \n");
    printf("\t\t         ======================       \n");
    while(1)
	{
    printf("\n\t\t请输入书号:");
    scanf("%d",&book_num);
    for(i=0;i<N;i++)
        if(bk[i].num==book_num&&bk[i].jie!=1)
		{
			book_xb=i;
			k++;
		}
        if(k==0)
		{
			printf("\t不存在该书，或该书已经借出!请正确输入图书名称!\n\t\t按任意键返回...");
			getch();
            break;
		}
	printf("\t编号    图书名称     出版社        出版时间     状态\n");
    printf("\t%-7d %-8s %12s   %4d年%2d月%2d日 ",bk[book_xb].num,bk[book_xb].name,bk[book_xb].publish,bk[book_xb].t.year,bk[book_xb].t.month,bk[book_xb].t.day);
    if(bk[book_xb].jie==1)
        printf("已被借阅\n");
    else
    {
        printf("可以借阅\n\t是否借阅？(是：'y'，否：'n')：");
        scanf("%s",jy);
        if(strcmp(jy,"n")==0)
        {
             printf("\t借阅取消，按任意键返回....");
             getch();
             break;
        }
        else if(strcmp(jy,"y")==0)
        {
             printf("\t借阅成功！按任意键返回...");
             bk[book_xb].jie=1;
             getch();
             break;
        }
        else
        {
             printf("\t输入有错！按任意键重新输入...");
			 getch();
             break;
        }       
    }
	}
}
/*********借阅图书********/
void jieyue()
{
    int x;
    do
    {
    system("cls");
	printf("\n\n\n\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\t\t|         =====================        |\n");
    printf("\t\t|                借阅图书                 |\n");
    printf("\t\t|         =====================        |\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|            1.按书名借阅                 |\n");
    printf("\t\t|            2.按书号借阅                 |\n");
    printf("\t\t|            3.查看所有图书               |\n");
    printf("\t\t|            4.返回主菜单                 |\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\t\t请输入您的选择:");
    scanf("%d",&x);
    switch(x)
    {
        case 1:system("CLS");jie_name();getch();break;/*按书名借阅*/
        case 2:system("CLS");jie_num();getch();break;/*按书号借阅*/
		case 3:system("cls");show_all_book();getch();break;/*查看所有图书*/
    }
    }while(x!=4);
}
/***************按书名进行查找并修改信息*************/
void xiugai_name()
{
	int i,book_xb,k=0;/*book_xb用来记录下标,k用来判断是否找到该书*/
	char temp[20];/*temp[20]用来存放用户输入的查找的书名*/
	while(1)
	{
		system("cls");
		printf("\n");
    	printf("\t\t|         =====================        |\n");
    	printf("\t\t|             按书名进行修改              |\n");
    	printf("\t\t|         =====================        |\n");
		printf("\t\t请输入您准备修改的图书的名称,输入'exit'退出:");
    	scanf("%s",temp);
		if(strcmp(temp,"exit")==0)
		break;
		else
		{
			for(i=0;i<N;i++)
		    if(strcmp(temp,bk[i].name)==0)
			{
				book_xb=i;
			    printf("\t该书的信息为:\n");
			    printf("\t编号    图书名称     出版社        出版时间     状态\n");
                printf("\t%-7d %-8s %12s   %4d年%2d月%2d日 ",bk[book_xb].num,bk[book_xb].name,bk[book_xb].publish,bk[book_xb].t.year,bk[book_xb].t.month,bk[book_xb].t.day);
				if(bk[book_xb].jie==1)
                    printf("已被借阅\n");
                else
                    printf("可以借阅\n");
				k++;
				printf("\t\t现在请输入新信息:\n");
				printf("\t\t请输入本书的编号:");
                scanf("%d",&bk[book_xb].num);
                printf("\t\t请输入本书的名称:");
                scanf("%s",bk[book_xb].name);
                printf("\t\t请输入本书的出版社:");
                scanf("%s",bk[book_xb].publish);
                printf("\t\t请输入本书的出版时间(用逗号隔开):");
                scanf("%d,%d,%d",&bk[book_xb].t.year,&bk[book_xb].t.month,&bk[book_xb].t.day);
                printf("\t\t该书是否已经被借阅,已被借阅输入'1'，未被借阅输入'0':");
                scanf("%d",&bk[book_xb].jie);
            }
			if(k==0)
			{
				printf("\t您输入的书名不存在!按任意键继续...");
				getch();
				continue;
			}
			printf("\t恭喜!信息修改成功!任意键返回...");getch();break;
		}
	}
}
/***************按书号进行查找并修改信息*************/
void xiugai_num()
{
	int i,book_xb,k=0;/*book_xb用来记录下标,k用来判断是否找到该书*/
	long temp;/*temp用来存放用户输入的查找的书号*/
	do
	{
		system("cls");
	printf("\n");
    printf("\t\t|         =====================        |\n");
    printf("\t\t|             按书号进行修改              |\n");
    printf("\t\t|         =====================        |\n");
	printf("\t\t请输入您准备修改的图书的图书号,输入'0'退出:");
    scanf("%ld",&temp);
	if(temp==0)	break;
	else
	{
		for(i=0;i<N;i++)
		    if(temp==bk[i].num)
			{
				book_xb=i;
			    printf("\t该书的信息为:\n");
			    printf("\t编号    图书名称     出版社        出版时间     状态\n");
                printf("\t%-7d %-8s %12s   %4d年%2d月%2d日 ",bk[book_xb].num,bk[book_xb].name,bk[book_xb].publish,bk[book_xb].t.year,bk[book_xb].t.month,bk[book_xb].t.day);
				k++;
				if(bk[book_xb].jie==1)
                    printf("已被借阅\n");
                else
                    printf("可以借阅\n");
				printf("现在请输入新信息:\n");
				printf("\t\t请输入本书的编号:");
                scanf("%d",&bk[book_xb].num);
                printf("\t\t请输入本书的名称:");
                scanf("%s",bk[book_xb].name);
                printf("\t\t请输入本书的出版社:");
                scanf("%s",bk[book_xb].publish);
                printf("\t\t请输入本书的出版时间(用逗号隔开):");
                scanf("%d,%d,%d",&bk[book_xb].t.year,&bk[book_xb].t.month,&bk[book_xb].t.day);
                printf("\t\t该书是否已经被借阅,已被借阅输入'1'，未被借阅输入'0':");
                scanf("%d",&bk[book_xb].jie);
            }
			if(k==0)
			{
				printf("\t您输入的书名不存在!按任意键继续...");
				getch();continue;
			}
			printf("\t恭喜!信息修改成功!任意键返回...");getch();break;
	}
	}while(temp!=0);
}
/**************删除所有图书***********/
void dele_all()
{
	char queren[4];
	printf("\t继续操作会删除所有信息，是否继续?'y'继续，'n'撤销...");
	scanf("%s",queren);
	if(strcmp(queren,"y")==0)
	{
		N=0;
		printf("\t删除成功!\n");
	}
	else
	{
		printf("\t操作被用户取消!任意键返回...");
		getch();
	}
}
/******************按书名删除************/
void dele_name()
{
	int i,book_xb,k=0;/*book_xb用来存放图书下标，k用标记是否找到书*/
	char queren[4],temp_name[20];/*queren[2]用来存放'是否'确认删除,temp_name[20]用来存放查找时输入的图书名称*/
	printf("\t输入你要删除的书的名称,输入'0'退出:");
	scanf("%s",temp_name);
	if(strcmp(temp_name,"0")!=0)
	{
	for(i=0;i<N;i++)
	   if(strcmp(temp_name,bk[i].name)==0)
	   {
			book_xb=i;
			printf("\t该书的信息为:\n");
			printf("\t编号    图书名称     出版社        出版时间     状态\n");
            printf("\t%-7d %-8s %12s   %4d年%2d月%2d日 ",bk[book_xb].num,bk[book_xb].name,bk[book_xb].publish,bk[book_xb].t.year,bk[book_xb].t.month,bk[book_xb].t.day);
		    if(bk[i].jie==0)
				printf("未借阅\n");
			else
				printf("已借阅\n");
			k++;
			printf("\t是否要删除该书?是'y',否'n'");
			scanf("%s",queren);
			if(strcmp(queren,"y")==0)
			{
				if(book_xb==N-1)
					N--;
				else
				{
					for(i=0;i<N;i++)
		        		bk[book_xb+i]=bk[book_xb+i+1];
					N--;
				}
		        printf("\t删除成功!\n");
	        }
	        else
	        	printf("\t操作被用户取消!任意键返回...");
	    }
	    if(k==0)
	        printf("\t未找到该书,请核实以后再操作!,按任意键返回....");getch();
    }	
}
/***************按书号查找并删除***********/
void dele_num()
{
	int i,book_xb,k=0,temp_num;/*book_xb用来存放图书下标，k用标记是否找到书,temp_num用来存放查找时输入的图书名称*/
	char queren[4];/*queren[2]用来存放'是否'确认删除*/
	while(1)
	{
	printf("\t输入你要删除的书的书号,输入'0'退出:");
	scanf("%d",&temp_num);
	if(temp_num==0)
		break;
	else
	{
	for(i=0;i<N;i++)
	   if(temp_num==bk[i].num)
	   {
			book_xb=i;
			printf("该书的信息为:\n");
			printf("\t编号    图书名称     出版社        出版时间     状态\n");
            printf("\t%-7d %-8s %12s   %4d年%2d月%2d日 ",bk[book_xb].num,bk[book_xb].name,bk[book_xb].publish,bk[book_xb].t.year,bk[book_xb].t.month,bk[book_xb].t.day);
		    if(bk[i].jie==0)
				printf("未借阅\n");
			else
				printf("已借阅\n");
			k++;
			printf("\t是否要删除该书?是'y',否'n'");
			scanf("%s",queren);
			if(strcmp(queren,"y")==0)
			{
				if(book_xb==N-1)
					N--;
				else
				{
					for(i=0;i<N;i++)
		        		bk[book_xb+i]=bk[book_xb+i+1];
					N--;
				}
		        printf("\t删除成功!\n");
	        }
	        else
	        	printf("\t操作被用户取消!任意键返回...");
	           }
	        if(k==0)
	        	printf("\t未找到该书,请核实以后再操作!,按任意键返回....");getch();break;
       	}	
	}
}
void dele()
{
	int x;	
	do
	{
		system("cls");
		printf("\t\t|-------------------------------------------------------------|\n");
    	printf("\t\t|         =====================        |\n");
    	printf("\t\t|              删除图书信息               |\n");
    	printf("\t\t|         =====================        |\n");
    	printf("\t\t|                                         |\n");
    	printf("\t\t|            1.按书名删除                 |\n");
    	printf("\t\t|            2.按书号删除                 |\n");
    	printf("\t\t|            3.删除所有图书               |\n");
    	printf("\t\t|            4.返回主菜单                 |\n");
    	printf("\t\t|-------------------------------------------------------------|\n");
		printf("\t\t请输入您的选项：");
		scanf("%d",&x);
		switch(x)
		{
			case 1:system("cls");dele_name();break;
			case 2:system("cls");dele_num();break;
			case 3:system("cls");dele_all();getch();break;
		}
	}while(x!=4);
}

/***************修改图书**************/
void xiugai()
{
    int x;
    do
    {
		system("cls");
		printf("\n\n\n\n");
   	 	printf("\t\t|-------------------------------------------------------------|\n");
   	 	printf("\t\t|         =====================        |\n");
    	printf("\t\t|               修改图书信息              |\n");
    	printf("\t\t|         =====================        |\n");
    	printf("\t\t|                                         |\n");
    	printf("\t\t|            1.按书名查找                 |\n");
    	printf("\t\t|            2.按书号查找                 |\n");
    	printf("\t\t|            3.删除图书                   |\n");
    	printf("\t\t|            4.返回主菜单                 |\n");
    	printf("\t\t|-------------------------------------------------------------|\n");
    	printf("\t\t请输入您的选择:");
    	scanf("%d",&x);
    	switch(x)
    	{
      	  	case 1:system("CLS");xiugai_name();break;/*按书名查找名修改信息*/
      	  	case 2:system("CLS");xiugai_num();break;/*按书号查找并修改信息*/
			case 3:system("cls");dele();break;							
    	}
    }while(x!=4);
}

/**************主函数**************/             
void main()
{
    int x,x2,s;/*s用来判断密码验证的结果*/
    do
    {
        system("cls"); x=mymainmenu();
        switch(x)
        {
            case 1:/************调用管理员模式函数***********/
				   system("cls");
                   s=mimayanzheng();/*密码验证*/
				   do
				   {				    
						if(s==1)
						{
							system("cls");
							x2=adm();
							switch(x2)
							{
								case 1:system("cls");xinxi();getch();break;/*录入信息*/
								case 2:system("cls");show();break;/*查看信息*/				           
								case 3:system("cls");xiugai();break;/*修改信息*/
								case 4:system("cls");xiugaimima();break;/*修改密码*/
							}	
						}
						else
						{
							printf("\t密码错误！按任意键返回...");
							getch();
							break;
						}
				   }while(x2!=5);break;
            case 2:/*调用客户模式函数*/
				  do
				  {
					  system("cls");
					  x2=peo();
					  switch(x2)
					  {
					  case 1:system("cls");show();getch();break;/*查看图书信息*/
					  case 2:system("cls");jieyue();getch();break;/*借阅图书*/
					  }        
				  }while(x2!=3);
        }
    }while(x!=3);
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t谢谢使用！\n\t\t\t");
	getch();
}


