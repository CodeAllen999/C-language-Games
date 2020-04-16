#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NUM 5


struct item{
	char brand[20];
	char id[10];
	float in_price;
	float out_price;
	int   storage;
};
struct item_node{
	struct item wanted;
	int    amount;
	struct item_node *next;
};

int menu();
void establish();
void dis_all();
void shop_cart();
int  cart_menu();
void add();
void display();
void calculate();

struct item goods[NUM];
struct item_node *cart;


void main()
{
	printf("***********************************\n");
	printf("     ��ӭ���볬�й���ϵͳ\n");
	printf("***********************************\n");
	while(1)
	{
		switch(menu())
		{
		case 1:
			establish();break;
		case 2:
			dis_all();break;
		case 3:
			shop_cart();break;
		case 4:
			calculate();break;
		case 5:
			printf("��лʹ�ã��ټ�!\n");
			exit(0);
		}
	}
}

int menu()
{
	char str[5];
	int  select;
	printf("\n\n��ѡ�����ֽ��в���\n");
	printf("1.���������Ϣ\n");
	printf("2.��ʾ������Ϣ\n");
	printf("3.���ﳵ\n");
	printf("4.����\n");
	printf("5.�˳�\n");
	printf("��ѡ���Ӧ����1--5");
	while(1)
	{
		fflush(stdin);
		gets(str);
		select=atoi(str);
		if(select<1||select>5)
			printf("�����������������:");
		else
			break;
		
	}
	return select;
	
}

void dis_all()
{
	int i;
	FILE  *fp;
	fp=fopen("goods","r");
	for(i=0;(fread(goods+i,sizeof(struct item),1,fp))!=0;i++)
	{
		printf("---------------------------------\n");
		printf("��Ʒ Ʒ��  ����       �����\n");
		printf("%s%7s%7.2f%8d\n",goods[i].id,goods[i].brand,goods[i].out_price,goods[i].storage);
		
	}
	fclose(fp);
}


void shop_cart()
{
	while(1)
	{
		switch(cart_menu())
		{
		case 1:
			display();break;
		case 2:
			add();break;
		case 3:
			return;
		}
	}
}
int  cart_menu()
{
	char  str[5];
	int   select;
	printf("\n��ѡ�����\n");
	printf("-----------------------\n");
	printf("1.��ʾ��ǰ�����б�\n");
	printf("2.�����Ʒ\n");
	printf("3.�˳�\n");
	printf("-----------------------\n\n");
	while(1)
	{
		fflush(stdin);
		gets(str);
		select=atoi(str);
		if(select<1||select>3)
			printf("�����������������:");
		else
			break;
	}
	return select;
}

void display()
{
	struct item_node *p=cart;
	if(p==NULL){
		printf("���ﳵΪ��\n");
		return ;
	}
	while(p!=NULL){
		printf("----------------------------------\n");
		printf("����                Ʒ��  ����   ����\n");
		printf("%10s%20s%7.2f%8d\n",p->wanted.id,p->wanted.brand,p->wanted.out_price,p->amount);
		p=p->next;
	}
}

void add()
{
	FILE *fp;
	int   i,n;
	char  str[20];
	char  choice1,choice2;
	struct item_node *p,*p1;
	do
	{
		printf("����������Ʒ�����ƻ����: ");
		fflush(stdin);
		gets(str);
		if((fp=fopen("goods","r"))==NULL){
			printf("���ļ�ʧ��\n");
			continue;
		}
		for(i=0;fread(goods+i,sizeof(struct item),1,fp)!=0;i++){
			if((strcmp(goods[i].brand,str)==0||strcmp(goods[i].id,str)==0)&&goods[i].storage!=0){
				printf("�Ѿ��ҵ�������Ʒ:  \n");
				printf("---------------------\n");
				printf("����  Ʒ��  ����  �����\n");
				printf("%s%6s%3.2f%4d\n",goods[i].id,goods[i].brand,goods[i].out_price,goods[i].storage);
				printf("��������������: ");
				scanf("%d",&n);
				if(n>goods[i].storage){
					printf("��治��\n");
					break;
				}
				printf("\n�Ƿ���?(Y/N)");
				fflush(stdin);
				choice1=getchar();
				if(choice1=='Y'||choice1=='y'){
					p1=(struct item_node*)malloc(sizeof(struct item_node));
					if(p1==NULL){
						printf("�ڴ�����ʧ��!\n");
						exit(1);
					}
					p1->amount=n;
					p1->wanted=goods[i];
					p1->next=NULL;
					p=cart;
					if(cart==NULL)
						cart=p1;
					else{
						while(p->next!=NULL)
							p=p->next;
						p1->next=p->next;
						p->next=p1;
					}
				}
				break;
			}
		}
		if(i==NUM)
			printf("δ�ҵ�������Ʒ\n");
		fclose(fp);
		printf("�Ƿ��������?(Y/N)");
		fflush(stdin);
		choice2=getchar();
	}while(choice2=='Y'||choice2=='y');
}


void  establish(){
	FILE *fp;
	int   i;
	printf("���������������Ϣ:\n");
	printf("----------------------------\n");
	for(i=0;i<NUM;i++)
	{
		printf("Ʒ��: ");
		fflush(stdin);
		gets(goods[i].brand);
		printf("����: ");
		fflush(stdin);
		gets(goods[i].id);
		printf("����: ");
		fflush(stdin);
		scanf("%f",&goods[i].in_price);
		printf("�ڼ�: ");
		fflush(stdin);
		scanf("%f",&goods[i].out_price);
		printf("����: ");
		fflush(stdin);
		scanf("%d",&goods[i].storage);
		printf("\n");
	}
	if((fp=fopen("goods","w"))==NULL){
		printf("�����ļ�ʧ��.\n");
		return;
	}
	fwrite(goods,sizeof(struct item),NUM,fp);
	fclose(fp);
}

void calculate()
{
	float total=0,pay;
	struct item_node *p;
	int   i;
	FILE   *fp;
	printf("�����ǹ����嵥:  \n");
	display();
	if((fp=fopen("goods","r"))==NULL){
		printf("���ļ�ʧ��:  \n");
		return;
	}
	for(i=0;(fread(goods+i,sizeof(struct item),1,fp))!=0;i++);
	fclose(fp);
	p=cart;
	while(p!=NULL){
		total+=p->wanted.out_price*p->amount;
		for(i=0;strcmp(goods[i].id,p->wanted.id)!=0;i++);
		goods[i].storage-=p->amount;
		p=p->next;
	}
	printf("�ܼ� %7.2f",total);
	printf("\n����ʵ�����: ");
	scanf("%f",&pay);
	printf("ʵ��:         %7.2f    ����:          %7.2f",pay,pay-total);
	if((fp=fopen("goods","w"))==NULL){
		printf("���ļ�ʧ��.\n");
		return;
	}
	fwrite(goods,sizeof(struct item),NUM,fp);
	fclose(fp);
}

