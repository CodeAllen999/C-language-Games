/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

#include "stdafx.h"

#include"stdio.h"
#include"conio.h"
#include"string.h"
#include"stdlib.h"
int N;
char mima[20]="mm";
/**********����ͼ��ṹ������book*******/
struct book
{
    long num;
    char name[20];
    char publish[20];/*������*/
    struct time
    {
        int day;
        int month;
        int year;
    }t;
    int jie;/*����*/
}bk[20];
/********����ͼ����Ϣ��********/
void xinxi()
{
    int i;
    system("CLS");
    printf("\t\t         =====================        \n");
    printf("\t\t               ¼��ͼ����Ϣ              \n");
    printf("\t\t         =====================        \n\n");
	printf("\t\t��������Ҫ¼�������:");
	scanf("%d",&N);
    for(i=0;i<N;i++)
    {
		printf("\t\t�������%d����ı��:",i+1);
        scanf("%d",&bk[i].num);
        printf("\t\t�������%d���������:",i+1);
        scanf("%s",bk[i].name);
        printf("\t\t�������%d����ĳ�����:",i+1);
        scanf("%s",bk[i].publish);
        printf("\t\t�������%d����ĳ���ʱ��(�ö��Ÿ���):",i+1);
        scanf("%d,%d,%d",&bk[i].t.year,&bk[i].t.month,&bk[i].t.day);
        printf("\t\t�����Ƿ��Ѿ�������,�ѱ���������'1'��δ����������'0':");
        scanf("%d",&bk[i].jie);
		printf("--------------------------------------------------------------------------------\n");
    }
	system("CLS");
    printf("\t\t         =====================        \n");
    printf("\t\t               ��Ϣ¼�����              \n");
    printf("\t\t         =====================        \n");
    printf("\n\t\t             �����������...\n");
}
/******���˵�******/
int mymainmenu()
{
    int x;
	printf("\n\n\n\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|           ��ӭ����ͼ�����ϵͳ          |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|           1.����Աģʽ                   |\n");
    printf("\t\t|           2.�ͻ�ģʽ                     |\n");
    printf("\t\t|           3.�˳�ϵͳ                     |\n");
    printf("\t\t|--------------------------------------------------------------|\n");
    printf("\n\t\t����������ѡ��:");
    scanf("%d",&x);
    return x;
}
/**************����Ա������֤*****************/
int mimayanzheng()
{
	char temp_mima[20];/*��������û����������*/
    printf("\n");
    printf("\t\t         ======================        \n");
    printf("\t\t            ��ӭʹ�ù���Աģʽ            \n");
    printf("\t\t         ======================        \n");
    printf("\n");
    printf("\t\t          ����������:");
    scanf("%s",temp_mima);
	if(strcmp(temp_mima,mima)==0)/*�Ƚ�����*/
		return 1;
	else
		return 0;
}
/**************�޸�����***********/
void xiugaimima()
{
	char temp_mima[20],temp1[20],temp2[20];/* temp_mima[20]��������û���������룬temp1[20],temp2[
20]�ֱ���������û�����������޸ĵ�����*/    
printf("\n");
    printf("\t\t         ======================        \n");
    printf("\t\t                 �޸�����                 \n");
    printf("\t\t         ======================        \n");
    printf("\n");
	printf("\t\t           ������ԭʼ����:");
	scanf("\t\t%s",temp_mima);
    while(1)
    {
	if(strcmp(temp_mima,mima)==0)/*�Ƚ�����*/
	{
		printf("\t������������:");
		scanf("%s",temp1);
		printf("\t��������һ��:");
		scanf("%s",temp2);
		if(strcmp(temp1,temp2)==0)/*�����������������붼��ͬ*/
		{
			printf("\t�޸�����ɹ�!!���������,���������...");
			strcpy(mima,temp1);
			getch();break;
		}
		else
		{
			printf("\t�����������벻��ͬ���޸�ʧ��!���������...");
			getch();
			break;
		}
	}
	else
	{
		printf("\t�������!�����ܽ��������޸�!���������...");
		getch();
		break;
	}
}
}	
/**************����Աģʽ****************/
int adm()
{
    int x;
	printf("\n\n\n\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|               ����Աģʽ                |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|           1.¼��ͼ����Ϣ                |\n");
    printf("\t\t|           2.�鿴ͼ����Ϣ                |\n");
    printf("\t\t|           3.�޸�ͼ����Ϣ                |\n");
    printf("\t\t|           4.�޸Ĺ�������                |\n");
    printf("\t\t|           5.�˳�ϵͳ                    |\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\n\t\t����������ѡ��:");
    scanf("%d",&x);
    return x;
}
/******************�ͻ�ģʽ********************/
int peo()
{
    int x;
	printf("\n\n\n\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|               ��ӭ����                  |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|           1.�鿴ͼ����Ϣ                |\n");
    printf("\t\t|           2.����ͼ��                    |\n");
    printf("\t\t|           3.�˳�ϵͳ                    |\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\n\t\t����������ѡ��:");
    scanf("%d",&x);
    return x;
}
/*********�鿴����ͼ��*******/
void show_all_book()
{
	int i;
	if(bk[0].num==0&&bk[0].t.year==0||N==0)/*��bk[0].num��bk[0].t.year���ṹ�������ֵͬʱΪ��ʱ��ʾ��ͼ����Ϣ*/
		printf("\t���ݲ����ڣ�����¼������!\n\t\t�����������...");
	else
	{
		printf("\t���    ͼ������     ������        ����ʱ��     ״̬\n");
		for(i=0;i<N;i++)
		{
			printf("\t%-7d %-8s %-12s   %4d��%2d��%2d�� ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
			if(bk[i].jie==0)
				printf("δ����\n");
			else
				printf("�ѽ���\n");
		}
	}
}
/*********�������鿴********/
void showbook_name()
{
    int i,k=0,n;/*k��������Ƿ���ڸ���*/
    char book_name[20];
    printf("\t\t         =====================        \n");
    printf("\t\t               �������鿴                \n");
    printf("\t\t         =====================        \n");
    printf("\n\t\t��������Ҫ�鿴��ͼ������:");
    scanf("%s",book_name);
    for(i=0;i<N;i++)
        if(strcmp(book_name,bk[i].name)==0)
		{
			n=i;
			if(k==0)/* "��Ŀ"ֻ���һ��*/
			    printf("\t���    ͼ������     ������        ����ʱ��     ״̬\n");
            printf("\t%-7d %-8s %12s   %4d��%2d��%2d�� ",bk[n].num,bk[n].name,bk[n].publish,bk[n].t.year,bk[n].t.month,bk[n].t.day);
		    if(bk[n].jie==1)
                printf("�ѱ�����\n");
            else
                printf("���Խ���\n");
	            printf("�����������...");
			k++; /*kֵ��Ϊ�����ʾ�ҵ�ͼ��*/
		}
		if(k==0)  /*kֵΪ�����ʾδ�ҵ�ͼ��*/
			printf("\t�����ڸ���!�����������...");
}
/*********����Ų鿴********/
void showbook_num()
{
    int n,book_num,i,k=0;/*k��������Ƿ���ڸ���*/
    printf("\t\t         =====================        \n");
    printf("\t\t               ����Ų鿴                \n");
    printf("\t\t         =====================        \n");
    printf("\n\t\t��������Ҫ�鿴��ͼ����:");
    scanf("%d",&book_num);
    for(i=0;i<N;i++)
        if(book_num==bk[i].num)
		{
			n=i;
			if(k==0)/*��Ŀֻ���һ��*/
			    printf("\t���    ͼ������     ������        ����ʱ��     ״̬\n");
            printf("\t%-7d %-8s %12s   %4d��%2d��%2d�� ",bk[n].num,bk[n].name,bk[n].publish,bk[n].t.year,bk[n].t.month,bk[n].t.day);
		    if(bk[n].jie==1)
                printf("�ѱ�����\n");
            else
                printf("���Խ���\n");
			k++;
			printf("\t�����������...");
		}
	if(k==0) /*kΪ�����ʾδ�ҵ�ͼ��*/
		printf("\t�����ڸ���!�����������...");    	
}

/********��ʾȫ���ѽ��ĵ�ͼ��**********/
void yijieyue()
{
    int i,k=0;
	if(bk[0].num==0&&bk[0].t.year==0||N==0)
		 printf("\t���ݲ����ڣ�����¼������!\n\t\t�����������...");
	else
	{
	    for(i=0;i<N;i++)
			if(bk[i].jie==1)
			{
				if(k==0)
				    printf("\t���    ͼ������     ������        ����ʱ��     \n");
				printf("\t%-7d %-8s %12s   %4d��%2d��%2d�� \n",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
                k++;			
			}
            if(k==0)
				printf("\n\t\tĿǰû���κ������������������...");
	}
}
/********��ʾȫ��δ���ĵ�ͼ��********/
void weijieyue()
{
    int i,k=0;
	if(bk[0].num==0&&bk[0].t.year==0||N==0)
		 printf("\t���ݲ����ڣ�����¼������!\n\t\t�����������...");
	else
	{
	    for(i=0;i<N;i++)
			if(bk[i].jie==0)
			{
				if(k==0)
				    printf("\t���    ͼ������     ������        ����ʱ��     \n");
				printf("\t%-7d %-8s %12s   %4d��%2d��%2d�� \n",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
			    k++;
			}
			if(k==0)
               printf("\n\t���ź���Ŀǰ���е��鶼������ˡ������������...");
	}
}
/*****�鿴ͼ��˵�******/
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
    	 printf("\t\t|              �鿴ͼ����Ϣ               |\n");
    	 printf("\t\t|         =====================        |\n");
    	 printf("\t\t|                                         |\n");
    	 printf("\t\t|           1.����������                  |\n");
    	 printf("\t\t|           2.����Ų���                  |\n");
    	 printf("\t\t|           3.�鿴����δ����ͼ��          |\n");
    	 printf("\t\t|           4.�鿴�����ѽ���ͼ��          |\n");
    	 printf("\t\t|           5.�鿴����ͼ��                |\n");
    	 printf("\t\t|           6.�������˵�                  |\n");
    	 printf("\t\t|-------------------------------------------------------------|\n");
    	 printf("\n\t\t����������ѡ��:");
    	 scanf("%d",&x);
    	 switch(x)
    	 {
         	 case 1:system("cls");showbook_name();getch();break;/*�������鿴*/
        	 case 2:system("cls");showbook_num();getch();break;/*����Ų鿴*/
       	   	 case 3:system("cls");weijieyue();getch();break;/*�鿴δ����ͼ��*/
       	   	 case 4:system("cls");yijieyue();getch();break;/*�鿴�ѽ���ͼ��*/
		 	 case 5:system("cls");show_all_book();getch();break;/*�鿴����ͼ��*/	
    	 }                                    
	}while(x!=6);
}
/*********����������*******/
void jie_name()
{
	char jy[2],name[20];/*jy������ʾ�Ƿ�ȷ������*/
	int i,book_xb,k=0;/*k��������Ƿ���ڸ���*/
	printf("\t\t         ======================       \n");
    printf("\t\t                ����������               \n");
    printf("\t\t         ======================       \n");
	while(1)
	{
    printf("\n\t\t����������:");
    scanf("%s",name);
    for(i=0;i<N;i++)
        if(strcmp(bk[i].name,name)==0&&bk[i].jie!=1)/*�ҵ�ͼ�鲢ȷ��ͼ��û�б��������¼ͼ���±�*/
		{
		    book_xb=i;
			k++;
		}
	if(k==0)
	{
		printf("\t�����ڸ��飬������Ѿ����!����ȷ����ͼ������!\n\t\t�����������...");
		getch();
        break;
	}
	if(k==1)
	    printf("\t���    ͼ������     ������        ����ʱ��     ״̬\n");
    printf("\t%-7d %-8s %12s   %4d��%2d��%2d�� ",bk[book_xb].num,bk[book_xb].name,bk[book_xb].publish,bk[book_xb].t.year,bk[book_xb].t.month,bk[book_xb].t.day);
    if(bk[book_xb].jie==1)
        printf("�ѱ�����\n");
    else
        {
           printf("���Խ���\n\t�Ƿ���ģ�(�ǣ�'y'����'n')��");
           scanf("%s",jy);
           if(strcmp(jy,"n")==0)
           {
                printf("\t����ȡ���������������....");
                getch();
                break;
           }
           else if(strcmp(jy,"y")==0)
           {
                printf("\t���ĳɹ��������������...");
				bk[book_xb].jie=1;
                getch();
                break;
           }
           else
           {
                printf("\t�����д����������������...");
				getch();
                break;
           }           
		}
	}
}
/*********����Ž���*******/
void jie_num()
{
	long i,k=0,book_xb,book_num;/*k��������Ƿ���ڸ���*/
	char jy[2];/*jy������ʾ�Ƿ�ȷ������*/
	printf("\t\t         ======================       \n");
    printf("\t\t                ����Ž���               \n");
    printf("\t\t         ======================       \n");
    while(1)
	{
    printf("\n\t\t���������:");
    scanf("%d",&book_num);
    for(i=0;i<N;i++)
        if(bk[i].num==book_num&&bk[i].jie!=1)
		{
			book_xb=i;
			k++;
		}
        if(k==0)
		{
			printf("\t�����ڸ��飬������Ѿ����!����ȷ����ͼ������!\n\t\t�����������...");
			getch();
            break;
		}
	printf("\t���    ͼ������     ������        ����ʱ��     ״̬\n");
    printf("\t%-7d %-8s %12s   %4d��%2d��%2d�� ",bk[book_xb].num,bk[book_xb].name,bk[book_xb].publish,bk[book_xb].t.year,bk[book_xb].t.month,bk[book_xb].t.day);
    if(bk[book_xb].jie==1)
        printf("�ѱ�����\n");
    else
    {
        printf("���Խ���\n\t�Ƿ���ģ�(�ǣ�'y'����'n')��");
        scanf("%s",jy);
        if(strcmp(jy,"n")==0)
        {
             printf("\t����ȡ���������������....");
             getch();
             break;
        }
        else if(strcmp(jy,"y")==0)
        {
             printf("\t���ĳɹ��������������...");
             bk[book_xb].jie=1;
             getch();
             break;
        }
        else
        {
             printf("\t�����д����������������...");
			 getch();
             break;
        }       
    }
	}
}
/*********����ͼ��********/
void jieyue()
{
    int x;
    do
    {
    system("cls");
	printf("\n\n\n\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\t\t|         =====================        |\n");
    printf("\t\t|                ����ͼ��                 |\n");
    printf("\t\t|         =====================        |\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|            1.����������                 |\n");
    printf("\t\t|            2.����Ž���                 |\n");
    printf("\t\t|            3.�鿴����ͼ��               |\n");
    printf("\t\t|            4.�������˵�                 |\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\t\t����������ѡ��:");
    scanf("%d",&x);
    switch(x)
    {
        case 1:system("CLS");jie_name();getch();break;/*����������*/
        case 2:system("CLS");jie_num();getch();break;/*����Ž���*/
		case 3:system("cls");show_all_book();getch();break;/*�鿴����ͼ��*/
    }
    }while(x!=4);
}
/***************���������в��Ҳ��޸���Ϣ*************/
void xiugai_name()
{
	int i,book_xb,k=0;/*book_xb������¼�±�,k�����ж��Ƿ��ҵ�����*/
	char temp[20];/*temp[20]��������û�����Ĳ��ҵ�����*/
	while(1)
	{
		system("cls");
		printf("\n");
    	printf("\t\t|         =====================        |\n");
    	printf("\t\t|             �����������޸�              |\n");
    	printf("\t\t|         =====================        |\n");
		printf("\t\t��������׼���޸ĵ�ͼ�������,����'exit'�˳�:");
    	scanf("%s",temp);
		if(strcmp(temp,"exit")==0)
		break;
		else
		{
			for(i=0;i<N;i++)
		    if(strcmp(temp,bk[i].name)==0)
			{
				book_xb=i;
			    printf("\t�������ϢΪ:\n");
			    printf("\t���    ͼ������     ������        ����ʱ��     ״̬\n");
                printf("\t%-7d %-8s %12s   %4d��%2d��%2d�� ",bk[book_xb].num,bk[book_xb].name,bk[book_xb].publish,bk[book_xb].t.year,bk[book_xb].t.month,bk[book_xb].t.day);
				if(bk[book_xb].jie==1)
                    printf("�ѱ�����\n");
                else
                    printf("���Խ���\n");
				k++;
				printf("\t\t��������������Ϣ:\n");
				printf("\t\t�����뱾��ı��:");
                scanf("%d",&bk[book_xb].num);
                printf("\t\t�����뱾�������:");
                scanf("%s",bk[book_xb].name);
                printf("\t\t�����뱾��ĳ�����:");
                scanf("%s",bk[book_xb].publish);
                printf("\t\t�����뱾��ĳ���ʱ��(�ö��Ÿ���):");
                scanf("%d,%d,%d",&bk[book_xb].t.year,&bk[book_xb].t.month,&bk[book_xb].t.day);
                printf("\t\t�����Ƿ��Ѿ�������,�ѱ���������'1'��δ����������'0':");
                scanf("%d",&bk[book_xb].jie);
            }
			if(k==0)
			{
				printf("\t�����������������!�����������...");
				getch();
				continue;
			}
			printf("\t��ϲ!��Ϣ�޸ĳɹ�!���������...");getch();break;
		}
	}
}
/***************����Ž��в��Ҳ��޸���Ϣ*************/
void xiugai_num()
{
	int i,book_xb,k=0;/*book_xb������¼�±�,k�����ж��Ƿ��ҵ�����*/
	long temp;/*temp��������û�����Ĳ��ҵ����*/
	do
	{
		system("cls");
	printf("\n");
    printf("\t\t|         =====================        |\n");
    printf("\t\t|             ����Ž����޸�              |\n");
    printf("\t\t|         =====================        |\n");
	printf("\t\t��������׼���޸ĵ�ͼ���ͼ���,����'0'�˳�:");
    scanf("%ld",&temp);
	if(temp==0)	break;
	else
	{
		for(i=0;i<N;i++)
		    if(temp==bk[i].num)
			{
				book_xb=i;
			    printf("\t�������ϢΪ:\n");
			    printf("\t���    ͼ������     ������        ����ʱ��     ״̬\n");
                printf("\t%-7d %-8s %12s   %4d��%2d��%2d�� ",bk[book_xb].num,bk[book_xb].name,bk[book_xb].publish,bk[book_xb].t.year,bk[book_xb].t.month,bk[book_xb].t.day);
				k++;
				if(bk[book_xb].jie==1)
                    printf("�ѱ�����\n");
                else
                    printf("���Խ���\n");
				printf("��������������Ϣ:\n");
				printf("\t\t�����뱾��ı��:");
                scanf("%d",&bk[book_xb].num);
                printf("\t\t�����뱾�������:");
                scanf("%s",bk[book_xb].name);
                printf("\t\t�����뱾��ĳ�����:");
                scanf("%s",bk[book_xb].publish);
                printf("\t\t�����뱾��ĳ���ʱ��(�ö��Ÿ���):");
                scanf("%d,%d,%d",&bk[book_xb].t.year,&bk[book_xb].t.month,&bk[book_xb].t.day);
                printf("\t\t�����Ƿ��Ѿ�������,�ѱ���������'1'��δ����������'0':");
                scanf("%d",&bk[book_xb].jie);
            }
			if(k==0)
			{
				printf("\t�����������������!�����������...");
				getch();continue;
			}
			printf("\t��ϲ!��Ϣ�޸ĳɹ�!���������...");getch();break;
	}
	}while(temp!=0);
}
/**************ɾ������ͼ��***********/
void dele_all()
{
	char queren[4];
	printf("\t����������ɾ��������Ϣ���Ƿ����?'y'������'n'����...");
	scanf("%s",queren);
	if(strcmp(queren,"y")==0)
	{
		N=0;
		printf("\tɾ���ɹ�!\n");
	}
	else
	{
		printf("\t�������û�ȡ��!���������...");
		getch();
	}
}
/******************������ɾ��************/
void dele_name()
{
	int i,book_xb,k=0;/*book_xb�������ͼ���±꣬k�ñ���Ƿ��ҵ���*/
	char queren[4],temp_name[20];/*queren[2]�������'�Ƿ�'ȷ��ɾ��,temp_name[20]������Ų���ʱ�����ͼ������*/
	printf("\t������Ҫɾ�����������,����'0'�˳�:");
	scanf("%s",temp_name);
	if(strcmp(temp_name,"0")!=0)
	{
	for(i=0;i<N;i++)
	   if(strcmp(temp_name,bk[i].name)==0)
	   {
			book_xb=i;
			printf("\t�������ϢΪ:\n");
			printf("\t���    ͼ������     ������        ����ʱ��     ״̬\n");
            printf("\t%-7d %-8s %12s   %4d��%2d��%2d�� ",bk[book_xb].num,bk[book_xb].name,bk[book_xb].publish,bk[book_xb].t.year,bk[book_xb].t.month,bk[book_xb].t.day);
		    if(bk[i].jie==0)
				printf("δ����\n");
			else
				printf("�ѽ���\n");
			k++;
			printf("\t�Ƿ�Ҫɾ������?��'y',��'n'");
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
		        printf("\tɾ���ɹ�!\n");
	        }
	        else
	        	printf("\t�������û�ȡ��!���������...");
	    }
	    if(k==0)
	        printf("\tδ�ҵ�����,���ʵ�Ժ��ٲ���!,�����������....");getch();
    }	
}
/***************����Ų��Ҳ�ɾ��***********/
void dele_num()
{
	int i,book_xb,k=0,temp_num;/*book_xb�������ͼ���±꣬k�ñ���Ƿ��ҵ���,temp_num������Ų���ʱ�����ͼ������*/
	char queren[4];/*queren[2]�������'�Ƿ�'ȷ��ɾ��*/
	while(1)
	{
	printf("\t������Ҫɾ����������,����'0'�˳�:");
	scanf("%d",&temp_num);
	if(temp_num==0)
		break;
	else
	{
	for(i=0;i<N;i++)
	   if(temp_num==bk[i].num)
	   {
			book_xb=i;
			printf("�������ϢΪ:\n");
			printf("\t���    ͼ������     ������        ����ʱ��     ״̬\n");
            printf("\t%-7d %-8s %12s   %4d��%2d��%2d�� ",bk[book_xb].num,bk[book_xb].name,bk[book_xb].publish,bk[book_xb].t.year,bk[book_xb].t.month,bk[book_xb].t.day);
		    if(bk[i].jie==0)
				printf("δ����\n");
			else
				printf("�ѽ���\n");
			k++;
			printf("\t�Ƿ�Ҫɾ������?��'y',��'n'");
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
		        printf("\tɾ���ɹ�!\n");
	        }
	        else
	        	printf("\t�������û�ȡ��!���������...");
	           }
	        if(k==0)
	        	printf("\tδ�ҵ�����,���ʵ�Ժ��ٲ���!,�����������....");getch();break;
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
    	printf("\t\t|              ɾ��ͼ����Ϣ               |\n");
    	printf("\t\t|         =====================        |\n");
    	printf("\t\t|                                         |\n");
    	printf("\t\t|            1.������ɾ��                 |\n");
    	printf("\t\t|            2.�����ɾ��                 |\n");
    	printf("\t\t|            3.ɾ������ͼ��               |\n");
    	printf("\t\t|            4.�������˵�                 |\n");
    	printf("\t\t|-------------------------------------------------------------|\n");
		printf("\t\t����������ѡ�");
		scanf("%d",&x);
		switch(x)
		{
			case 1:system("cls");dele_name();break;
			case 2:system("cls");dele_num();break;
			case 3:system("cls");dele_all();getch();break;
		}
	}while(x!=4);
}

/***************�޸�ͼ��**************/
void xiugai()
{
    int x;
    do
    {
		system("cls");
		printf("\n\n\n\n");
   	 	printf("\t\t|-------------------------------------------------------------|\n");
   	 	printf("\t\t|         =====================        |\n");
    	printf("\t\t|               �޸�ͼ����Ϣ              |\n");
    	printf("\t\t|         =====================        |\n");
    	printf("\t\t|                                         |\n");
    	printf("\t\t|            1.����������                 |\n");
    	printf("\t\t|            2.����Ų���                 |\n");
    	printf("\t\t|            3.ɾ��ͼ��                   |\n");
    	printf("\t\t|            4.�������˵�                 |\n");
    	printf("\t\t|-------------------------------------------------------------|\n");
    	printf("\t\t����������ѡ��:");
    	scanf("%d",&x);
    	switch(x)
    	{
      	  	case 1:system("CLS");xiugai_name();break;/*�������������޸���Ϣ*/
      	  	case 2:system("CLS");xiugai_num();break;/*����Ų��Ҳ��޸���Ϣ*/
			case 3:system("cls");dele();break;							
    	}
    }while(x!=4);
}

/**************������**************/             
void main()
{
    int x,x2,s;/*s�����ж�������֤�Ľ��*/
    do
    {
        system("cls"); x=mymainmenu();
        switch(x)
        {
            case 1:/************���ù���Աģʽ����***********/
				   system("cls");
                   s=mimayanzheng();/*������֤*/
				   do
				   {				    
						if(s==1)
						{
							system("cls");
							x2=adm();
							switch(x2)
							{
								case 1:system("cls");xinxi();getch();break;/*¼����Ϣ*/
								case 2:system("cls");show();break;/*�鿴��Ϣ*/				           
								case 3:system("cls");xiugai();break;/*�޸���Ϣ*/
								case 4:system("cls");xiugaimima();break;/*�޸�����*/
							}	
						}
						else
						{
							printf("\t������󣡰����������...");
							getch();
							break;
						}
				   }while(x2!=5);break;
            case 2:/*���ÿͻ�ģʽ����*/
				  do
				  {
					  system("cls");
					  x2=peo();
					  switch(x2)
					  {
					  case 1:system("cls");show();getch();break;/*�鿴ͼ����Ϣ*/
					  case 2:system("cls");jieyue();getch();break;/*����ͼ��*/
					  }        
				  }while(x2!=3);
        }
    }while(x!=3);
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tллʹ�ã�\n\t\t\t");
	getch();
}


