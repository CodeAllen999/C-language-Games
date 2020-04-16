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
	printf("     欢迎进入超市管理系统\n");
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
			printf("感谢使用，再见!\n");
			exit(0);
		}
	}
}

int menu()
{
	char str[5];
	int  select;
	printf("\n\n请选择数字进行操作\n");
	printf("1.建立库存信息\n");
	printf("2.显示所有信息\n");
	printf("3.购物车\n");
	printf("4.结算\n");
	printf("5.退出\n");
	printf("请选择对应数字1--5");
	while(1)
	{
		fflush(stdin);
		gets(str);
		select=atoi(str);
		if(select<1||select>5)
			printf("输入错误，请重新输入:");
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
		printf("货品 品名  单价       库存量\n");
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
	printf("\n请选择操作\n");
	printf("-----------------------\n");
	printf("1.显示当前购物列表\n");
	printf("2.添加商品\n");
	printf("3.退出\n");
	printf("-----------------------\n\n");
	while(1)
	{
		fflush(stdin);
		gets(str);
		select=atoi(str);
		if(select<1||select>3)
			printf("输入错误，请重新输入:");
		else
			break;
	}
	return select;
}

void display()
{
	struct item_node *p=cart;
	if(p==NULL){
		printf("购物车为空\n");
		return ;
	}
	while(p!=NULL){
		printf("----------------------------------\n");
		printf("货号                品名  单价   数量\n");
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
		printf("输入所需物品的名称或货号: ");
		fflush(stdin);
		gets(str);
		if((fp=fopen("goods","r"))==NULL){
			printf("打开文件失败\n");
			continue;
		}
		for(i=0;fread(goods+i,sizeof(struct item),1,fp)!=0;i++){
			if((strcmp(goods[i].brand,str)==0||strcmp(goods[i].id,str)==0)&&goods[i].storage!=0){
				printf("已经找到所需物品:  \n");
				printf("---------------------\n");
				printf("货号  品名  单价  库存量\n");
				printf("%s%6s%3.2f%4d\n",goods[i].id,goods[i].brand,goods[i].out_price,goods[i].storage);
				printf("请输入所需数量: ");
				scanf("%d",&n);
				if(n>goods[i].storage){
					printf("库存不足\n");
					break;
				}
				printf("\n是否购买?(Y/N)");
				fflush(stdin);
				choice1=getchar();
				if(choice1=='Y'||choice1=='y'){
					p1=(struct item_node*)malloc(sizeof(struct item_node));
					if(p1==NULL){
						printf("内存申请失败!\n");
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
			printf("未找到所需物品\n");
		fclose(fp);
		printf("是否继续购物?(Y/N)");
		fflush(stdin);
		choice2=getchar();
	}while(choice2=='Y'||choice2=='y');
}


void  establish(){
	FILE *fp;
	int   i;
	printf("请依次输入货物信息:\n");
	printf("----------------------------\n");
	for(i=0;i<NUM;i++)
	{
		printf("品名: ");
		fflush(stdin);
		gets(goods[i].brand);
		printf("货号: ");
		fflush(stdin);
		gets(goods[i].id);
		printf("进价: ");
		fflush(stdin);
		scanf("%f",&goods[i].in_price);
		printf("哨价: ");
		fflush(stdin);
		scanf("%f",&goods[i].out_price);
		printf("数量: ");
		fflush(stdin);
		scanf("%d",&goods[i].storage);
		printf("\n");
	}
	if((fp=fopen("goods","w"))==NULL){
		printf("创建文件失败.\n");
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
	printf("以下是购物清单:  \n");
	display();
	if((fp=fopen("goods","r"))==NULL){
		printf("打开文件失败:  \n");
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
	printf("总计 %7.2f",total);
	printf("\n输入实付金额: ");
	scanf("%f",&pay);
	printf("实付:         %7.2f    找零:          %7.2f",pay,pay-total);
	if((fp=fopen("goods","w"))==NULL){
		printf("打开文件失败.\n");
		return;
	}
	fwrite(goods,sizeof(struct item),NUM,fp);
	fclose(fp);
}

