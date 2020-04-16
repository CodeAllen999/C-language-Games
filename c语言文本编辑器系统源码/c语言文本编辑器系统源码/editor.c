/*�ı��༭��editorԴ����*/

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

#include <stdio.h>
#include <conio.h>
#include <bios.h>
#include <math.h>
#define LEFT 0x4b00   /*�����������*/
#define RIGHT 0x4d00  /*�����������*/
#define DOWN 0x5000   /*�������������*/
#define UP 0x4800     /*�������������*/
#define ESC 0x011b    /*ESC����ȡ���˵��򿪲���*/
#define ENTER 0x1c0d  /*�س���������*/
#define DEL 21248     /*DEL����ɾ����ǰ�ַ�*/
#define BACK 3592     /*BackSpace����ɾ����ǰ���λ��ǰһ���ַ�*/
#define CL 29440      /*ctrl+��������������ѡ���ı�*/
#define CR 29696      /*ctrl+�����������ң�ѡ���ı�*/
#define Cc 11779      /*ctrl+c������ѡ���ı�������һ�ݵ���������*/
#define Cv 12054      /*ctrl+v�������������е����ݸ��Ƶ���ǰλ��*/
#define Cx 11544      /*ctrl+x������ѡ���ı���ִ�м��в���*/
#define F1 15104      /*F1�������ļ��˵�*/
#define F2 15360      /*F2�����򿪱༭�˵�*/
#define F3 15616      /*F3�����򿪰����˵�*/
#define F10 17408     /*F10��:�����ı�����Ԥ��ģʽ*/
int value,backup,NUM;
/*value������ֵ����Ԫ�ص�����±�ֵ��backup����value�ĸ�����NUM���浱ǰ���е��û�������ַ�����*/
typedef struct record
 {
       char ch;  /*����һ�ַ�*/
       int col, line;  /*x���y������*/
 }record;
record r[500]; /*����һ����500��Ԫ�صĽṹ�����飬����ѡ�����ı��ַ�������*/

typedef struct node /*���屣�����еĵ����ַ��Ľṹ*/
 {
        char ch; /*�����򣺱���һ�ַ�*/
        struct node *next; /*ָ����ָ����һ������ָ��*/
 }node;/*�ɴ����ͽڵ㹹�ɵĵ���������Ϊ���е�����*/


  typedef struct Hnode /*���屣�������е������׽ڵ��ָ��Ľṹ*/
 {
         node *next; /*ָ���е�������׽ڵ�ĵ�ַ*/
         struct Hnode *nextl; /*ָ����һ���ڵ��ָ��*/
 }Hnode;/*�ɴ����ͽڵ㹹�ɵĵ���������Ϊ���е�����*/




void drawmain() /*�������ں���*/
 {
          int i,j;
          gotoxy(1,1);       /*���ı����������ù����(1,1)��*/
          textbackground(7); /*ѡ���µ��ı�������ɫ,7ΪLIGHTGRAY����ɫ*/
          textcolor(0);      /*���ı�ģʽ��ѡ���µ��ַ���ɫ0ΪBLACK��*/
          insline();         /*���ı����ڵ�(1,1)λ�ô��в���һ������*/
          for(i=1;i<=24;i++)
         {
              gotoxy(1,1+i);     /*��x,y)��x���䣬y++*/
              cprintf("%c",196); /*�ڴ���������-,�����������ڵ���߽� */
              gotoxy(80,1+i);
              cprintf("%c",196); /*�ڴ����ұߣ����-�������������ڵ��ұ߽�*/
         }
          for(i=1;i<=79;i++)
         {
               gotoxy(1+i,2);     /*�ڵ�2�У���2�п�ʼ*/
               cprintf("%c",196); /*�ڴ��ڶ��ˣ����-*/
               gotoxy(1+i,25);    /*�ڵ�25�У���2�п�ʼ*/
               cprintf("%c",196); /*�ڴ��ڵ׶ˣ����-*/
         }
          gotoxy(1,1);   cprintf("%c",196); /*�ڴ������Ͻǣ����-*/
          gotoxy(1,24);  cprintf("%c",196); /*�ڴ������½ǣ����-*/
          gotoxy(80,1);  cprintf("%c",196); /*�ڴ������Ͻǣ����-*/
          gotoxy(80,24); cprintf("%c",196); /*�ڴ������½ǣ����-*/
          gotoxy(7,1); cprintf("%c  %c File %c  %c",179,17,16,179);  /* | < > |*/
          gotoxy(27,1); cprintf("%c  %c Edit %c  %c",179,17,16,179); /* | < > |*/
          gotoxy(47,1); cprintf("%c  %c Help %c  %c",179,17,16,179); /* | < > |*/
          gotoxy(5,25); /*�������ڵ׶�*/
          textcolor(1);
          cprintf(" Row:1         Col:1");
          gotoxy(68,25);
          cprintf("Version 2.0");
 }




void qview(Hnode *q) /*����Ԥ���ı�����ͷ��#���س���* */
 {
       void view(Hnode *q); /*view()��������*/
       node *p;
       int i;
       window(1,1,80,25); /*�����ı����ڴ�С*/
       clrscr(); /*����*/
       /*ѭ����ȡ�����������е�ֵ��q��һ��ָ���е������׽ڵ��ָ�룬
       �˵������������ֵΪʵ�ʱ�������ַ����е�����p�е��׽ڵ��ַ*/
       do{
              p=q->next;    /*pָ�򱣴������ݵ��е�������׽ڵ�ĵ�ַ*/
              cprintf("#"); /*ÿ�п�ͷ����ӡ���ַ�������ǰ���Ƿ��лس���*/
              while(p!=NULL) /*ѭ����ȡ������p�е�ֵ*/
             {
                    if(p->ch==13)  putch('*'); /*��Ϊ�س�������ӡ��*��*/
                    else
                    putch(p->ch);  /*��������е��ַ���Ԥ������*/
                    p=p->next; /*ָ����һ���ڵ�*/
             }
             q=q->nextl; /*ָ����һ���ڵ�*/
             printf("\n");/*���һ���س�*/
         }while(q!=NULL);

       getch();
       clrscr();
       drawmain();/*��������󣬻ص������ڽ���*/
       window(2,2,79,23);
       textbackground(9);
       for(i=0;i<24;i++)
            insline(); /*����24������*/
       window(3,3,78,23);
       textcolor(10);
  }



void view(Hnode *q)  /*������ʾ�����ڵ������е��ı��ַ�,qΪָ���е������е�һ���ڵ��ָ��*/
 {
       node *p; /*pΪ�����е�����ڵ�Ԫ�ص�ַ��ָ��*/
       clrscr(); /*����*/
       /*˫��ѭ������ȡ����ʾ�����ڵ��������ַ�*/
       do{
              p=q->next;
              while(p!=NULL&&p->ch>=32&&p->ch<127&&p->ch!=13&&p->ch!=-1)  /*ָ��p����Ϊ�գ������������Ϊ�����ַ�*/
             {
                    putch(p->ch);/*���ı�������������ַ�*/
                    p=p->next;  /*ָ����һ���ڵ�*/
             }
             q=q->nextl; /*ָ����һ���ڵ�*/
             if((p->ch==13||p->ch==-1)&&q!=NULL)  gotoxy(1,wherey()+1); /*��chΪ�س���EOF��ǣ�����������еĿ�ʼ��*/
         }while(q!=NULL); /*����������ʾ�ı��ַ�*/
 }
 
int check(Hnode *Hhead,int m,int n) /*check():�ڵ������м���m�е�n��λ�õ��ַ�����Ϊ�����ַ����򷵻ظ��ַ�*/
 {
        int i;
        Hnode *q;
        node *p;
        q=Hhead;
        for(i=1;i<m;i++) /*��λ���е������еĵ�m��Ԫ��*/
            q=q->nextl;
        p=q->next;/*��ȡ��m���ڵ��������*/
        for(i=1;i<n;i++) /*��λ���е������еĵ�n��Ԫ��*/
            p=p->next;
        if(p->ch==13)  return -1; /*����m�У���n�е��ַ�Ϊ�س������򷵻�-1*/
        if(p->ch>=32&&p->ch<127)  return p->ch; /*����m�У���n�е��ַ�Ϊ�����ַ�,�򷵻ظ��ַ�*/
        else return 0; /*����m�У���n�е��ַ��ȷǻس����ַǳ����ַ����򷵻�0*/
  }



int judge(Hnode *Hhead,int m) /*judge():���ص�m���еĳ����ַ��ܵĸ������������س���*/
  {
        Hnode *q;
        node *p;
        int i,num=0;
        q=Hhead;
        for(i=1;i<m;i++) /*��λ���е������еĵ�m��Ԫ��*/
            q=q->nextl;

        if(q==NULL)  return -1; /*����-1,��ʾ��m�в�����*/
        p=q->next;
        while(p->next!=NULL)
       {
                p=p->next;
                num++;       /*ͳ�Ƶ�m�е��ַ�����*/
       }
        /*��β�ַ���û���жϣ��������ж���β�ַ�*/
        if(p->ch==13&&num==0)  return 0;    /*����0,��ʾ��ǰ��ֻ��һ���س��ַ�*/
        if(p->ch>=32&&p->ch<127)  return num+1; /*����num+1,��ʾ��ǰ�е����һ���ַ�Ϊ�����ַ�*/
        if(p->ch==13&&num!=0)  return num; /*����num,��ʾ��ǰ�е����һ���ַ�Ϊ�س���������������*/
        else return 1;/*����num,��ʾ��ǰ����ֻ��һ���ַ�����û�лس���*/
  }






  int del(Hnode *Hhead,int m,int n)  /*del():ɾ����m�У���n��λ�õ��ַ�*/
 {
        Hnode *q,*q1;
        node *p1,*p2,*tail;
        int i,num=0,j,flag=0;
        q=Hhead;
        if(n==0&&m==1)  return; /*��1�У���0�в�����*/
        if(n==0&&m>1) /*��Ϊ��0���ַ������б������1,ִ���������ƴ���*/
         {
               n=76;
               m=m-1;
               gotoxy(n,m);/*������m-1�У���76��*/
               flag=1; /*��λ�ı�־��1*/
         }

        for(i=1;i<m;i++) /*��λ���е������еĵ�m��Ԫ��*/
            q=q->nextl;
        p1=q->next;

        for(i=1;i<n-1;i++) /*��λ���е������еĵ�n-1��Ԫ��*/
            p1=p1->next;
        p2=p1->next; /*p2ָ���е������еĵ�n��Ԫ��*/

             if(n==1) /*����ɾ����m�е�1�е��ַ�*/
               {
                    q->next=p1->next;
                    free(p1);
               }
                else
               {
                    p1->next=p2->next; /*�ڵ�������ɾ����m�е�n�е�Ԫ��*/
                    free(p2);
               }

                /*ɾ������m�е�n�е�Ԫ�غ󣬴����е������е�m���ڵ���������ǰ�Ƶ�����*/
                 while((num=judge(Hhead,m++))>0) /*ִ��һ��judge(Head,m)��m�ż�1.������������г����ַ�����Ϊ0������*/
                {
                         p1=q->next; q1=q;
                         if(p1!=NULL) /*����ǰ�зǿ�*/
                        {
                                while(p1->next!=NULL)
                                    p1=p1->next;
                                tail=p1;/*tail�����е��������һ��Ԫ�صĵ�ַ*/
                                q=q->nextl; /*ָ����һ�е�Ԫ�صĵ�ַ*/
                                p1=p2=q->next;
                                tail->next=p1; /*tail��ָ����ָ����һ�еĵ�һ��Ԫ�صĵ�ַ*/
                         }
                          else  /*����ǰ�е��ַ�����Ϊ0,��ɾ�����ַ���ֻʣ�»س���������һ���е������нڵ������������ǰһ�½ڵ��������*/
                         {
                                 q=q->nextl;   p1=p2=q->next;
                                 q1->next=p1;/*q1->nextָ����һ�еĵ�һ��Ԫ�صĵ�ַ*/
                          }

                         for(i=0;i<76-num;i++)
                         /*��ǰ�л���76-num����λû���ַ�������һ�еĵ������ж�ȡ�ַ���ֱ�������س���Ϊֹ*/
                        {
                                p1=p2; /*p1ָ��p2��ǰһ���ڵ�,p2ָ���е���������һ���ڵ�*/
                                p2=p2->next;
                                if(p2->ch==13)  break; /*��Ϊ�س�������ѭ��*/
                         }
                          q->next=p2;   /*���е�������ȥ���������е�Ԫ��*/
                          p1->next=NULL;/*�����������е����һ��Ԫ�أ�ָ���ÿ�*/
                }
           return flag; /*����0����ʾû�л�λ������1����ʾ�л�λ*/
  }

 /*ִ��insert()�󣬼����n�м���������ݣ�ʹ���������*/
 int test(Hnode *Hhead,int n)
 {
       int i=0,num1=1;
       node *p1,*p2,*tail,*temp1,*temp2;
       Hnode *q;
       q=Hhead;
       for(i=1;i<n;i++) /*��λ���е������еĵ�n��Ԫ��*/
            q=q->nextl;
       tail=p1=q->next;
       if(p1==NULL) return; /*������û���κ��ַ����򷵻�*/
       while(tail->next!=NULL) /*��λ���е������е����һ��Ԫ��*/
            tail=tail->next;

       /*���˵�������û�лس������г���76���ڵ�ʱ����p1��ָ����е������еĵ�76���ڵ�*/
       for(i=0;i<75;i++)
      {
             if(p1->ch==13||p1->next==NULL)  break;
             p1=p1->next;
      }

       p2=p1->next;
       p1->next=NULL; /*�ڴ��е����һ���ַ���ǰһ���ַ�������,��Ϊ�����ڴ��в�����һ���µ��ַ�*/
       if(tail->ch!=13) /*��������β���ǻس���*/
      {
             if(p1->ch==13&&q->nextl==NULL)/*��p1��������Ϊ�س������е�������ֻ��n���ڵ�*/
            {
                       q->nextl=(Hnode *)malloc(sizeof(Hnode)); /*�½�һ���е�����ڵ㣬�൱�����һ������*/
                       q->nextl->nextl=NULL;
                       tail->next=(node *)malloc(sizeof(node));/*��tail��ָ�ڵ�λ�ÿ�ʼ����׼������ַ�*/
                       tail->next->ch=13;   tail->next->next=NULL;
                       q->nextl->next=p2; /*���е�����ڵ㱣����ж�����ַ�*/
             }
             else /*��������β�����ж�û�лس���,����q->nextl��Ϊ��*/
            {
                   q=q->nextl;/*q->nextl�п���Ϊ��*/
                   tail->next=q->next;/*��������ַ�����һ�е��ַ�����*/
                   q->next=p2;/**/
                   if(q!=NULL)  test(Hhead,++n); /*���е������n���ڵ���нڵ㣬����test()����ͬ����*/
            }

      }
       else  /*�����е��������һ��Ԫ��Ϊ�س���*/
      {
            temp2=p2; /*p2ָ���77���ַ�������Ϊ��(Ϊ�ձ�ʾ���в���һ���ַ���û�г�����Χ*/
            while(q!=NULL&&p2!=NULL) /*qָ�����б��еĵ�n���ڵ�.����:�е������е�n���ڵ�������е�77���ַ�*/
             {  /*���������е�������ֻ��n���ڵ�,���ַ�������һ�й涨��76������num1��־Ϊ1*/
                 if((q->nextl==NULL)&&(p1!=tail||p2!=NULL)&&(num1==1))
                {
                       num1++;
                       q->nextl=(Hnode *)malloc(sizeof(Hnode)); /*�½�һ���е�����ڵ�,׼���洢�����ж�����ַ�*/
                       q->nextl->nextl=NULL;   q->nextl->next=NULL; /*��ʼ��ֵ*/

                }
                /*�е������е�n+1���ڵ��Ѿ����ڣ�����Ϊ���е������в���һ���µĽڵ�*/
                 q=q->nextl; /*qָ�����б��еĵ�n+1���ڵ�*/
                 temp1=q->next;
                 q->next=temp2; /*q��������Ϊ�����ж�����ַ����ڵ��е������еĽڵ��ַ*/
                 temp2=temp1;
           }
      }
 }

void insert(Hnode *Hhead,int m,int n, char a) /*��m�У���n�е�λ��֮ǰһ��λ�ã����뵥�ַ�*/
 {
        int i;
        Hnode *q;
        node *p,*p1,*p2;
        q=Hhead;
        for(i=1;i<m;i++) /*��λ���е������еĵ�m��Ԫ��*/
            q=q->nextl;
        p1=q->next;
        for(i=1;i<n-1;i++) /*��λ���е������еĵ�n-1��Ԫ��*/
            p1=p1->next;
        p=(node *)malloc(sizeof(node)); /*����һ���µ��е�����ڵ�*/
        p->ch=a; /*���˽ڵ��������ֵ*/
        if(n==1) /*����֮ǰ����ֻ��һ���ַ������У�����ڴ˽ڵ�֮ǰ*/
       {
               p->next=q->next;
               q->next=p;
       }
        else
       {
                 p->next=p1->next; /*�ڵ�m�У���n�е��ַ�ǰ������һ�ַ�*/
                 p1->next=p;
       }
    test(Hhead,m); /*�ڲ�����Ԫ�غ󣬼��鲢���������е�m�п�ʼ��Ԫ�أ�ʹ���������*/

 }

/*�Կ��Ƽ�������Ӧ��A������������ֵ��Hhead:�е�������׵�ַ*/
void control(int A, Hnode *Hhead)
   {
           void colorview(Hnode *,int,int); /*��������*/
           int x,y,flag=0;
           x=wherex();   y=wherey(); /*�õ���ǰ��������ֵ*/
           if((A==CL)&&(x!=1)) /*ctrl+������ǰ��겻��������,����ƶ�*/
                gotoxy(wherex()-1,wherey());

           if((A==CL)&&(x==1)) /*ctrl+����������*/
                gotoxy(abs(judge(Hhead,wherey()-1)),wherey()-1); /*judge(Hhead,wherey()-1)��һ�е��ַ�������Ϊxֵ������ƶ�*/

           if((A==CR)&&check(Hhead,wherey(),wherex())>0) /*ctrl+��,��ǰ�����ұ����ַ�������ƶ�*/
          {    flag=1;  gotoxy(wherex()+1,wherey()); }

           if((A==CR)&&check(Hhead,wherey()+1,1)>0&&check(Hhead,y,x)==0) /*ctrl+��,��ǰ��괦û���ַ�����һ�еĵ�һ�����ַ�������ƶ�*/
          {    flag=1;  gotoxy(1,wherey()+1);  }

           if((A==CR)&&x==76) /*ctrl+������ǰ����ڵ�ǰ�е���β������ƶ�*/
          {    flag=1;      gotoxy(1,wherey()+1);  }

           if(A==CR&&flag==1) /*ctrl+��������Ѿ������´�������ǰ�������λ�õ��ַ��������ֵ������r������*/
          {
             r[abs(value)].col=wherex();
             r[abs(value)].line=wherey();
             r[abs(value)].ch=check(Hhead,r[abs(value)].line,r[abs(value)].col);
             if(r[abs(value)].ch==-1)   r[abs(value)].ch=13; /*����line�У���col�е��ַ�Ϊ�س������򷵻�-1*/
             value--;

          }

           if(A==CL&&(x!=1||y!=1))   /*ctrl+��,��ǰ��겢���ڴ������Ͻ�,����ǰ�������λ�õ��ַ��������ֵ������r������*/
          {

             r[abs(value)].col=wherex();
             r[abs(value)].line=wherey();
             r[abs(value)].ch=check(Hhead,r[abs(value)].line,r[abs(value)].col);
             value++;
          }

           colorview(Hhead,wherex(),wherey());

  }

/*�ò�ͬ��ǰ����ɫ��ʾѡ����ַ�*/
void colorview(Hnode *Hhead,int x,int y)
  {

           int i;
           view(Hhead);/*������ʾ�����ı��ַ�*/
           for(i=0;i<abs(value);i++)   /*valueΪ�����±�*/
          {
                    gotoxy(r[i].col,r[i].line);
                    textbackground(7);
                    textcolor(0);
                    if(r[i].ch!=13&&r[i].ch!=-1)
                        cprintf("%c",r[i].ch);
                    if(r[i].ch==13||r[i].ch==-1)
                        cprintf(" ");
          }

           gotoxy(x,y);

  }

void drawmenu(int m,int n) /*���˵�,m:�ڼ���˵���n����m��ĵ�n���Ӳ˵�*/
 {
       int i;
      if(m%3==0) /*��File�˵���*/
     {
            window(8,2,19,9);
            textcolor(0);
            textbackground(7);
            for(i=0;i<7;i++) /*�����涨����ı������������7������*/
           {
                gotoxy(1,1+i);
                insline();
           }
            window(1,1,80,25);
            gotoxy(7,1);
            for(i=1;i<=7;i++)
           {
                gotoxy(8,1+i);
                cprintf("%c",179); /*�������ı�������������ڴ��������� | */
                gotoxy(19,1+i);
                cprintf("%c",179); /*�������ı�������������ڴ����ұ���� | */
            }
            for(i=1;i<=11;i++)
           {
                  gotoxy(8+i,2);
                  cprintf("%c",196);  /*�������ı�������������ڴ����ϱ���� - */
                  gotoxy(8+i,9);
                  cprintf("%c",196);  /*�������ı�������������ڴ����±���� - */
            }
            textbackground(0);
            gotoxy(10,10); cprintf("            "); /*����±ߵ���ӰЧ��*/
            for(i=0;i<9;i++)
           {
                  gotoxy(20,2+i);
                  cprintf("   "); /*����ұߵ���ӰЧ��*/
           }
            /*����Ϊ��ʾ�˵�������*/
            textbackground(7);
            gotoxy(8,2);  cprintf("%c",218); /*����ĸ��߽Ǳ���*/
            gotoxy(8,9);  cprintf("%c",192);
            gotoxy(19,2); cprintf("%c",191);
            gotoxy(19,9); cprintf("%c",217);
            gotoxy(9,3);  cprintf(" New    ");
            gotoxy(9,4);  cprintf(" Open   ");
            gotoxy(9,5);  cprintf(" Save   ");
            gotoxy(9,6);  cprintf(" Save as");
            for(i=1;i<=10;i++)
           {
                  gotoxy(8+i,7);
                  cprintf("%c",196); /*��Save as�����һ�зָ���*/
           }
            gotoxy(9,8);  cprintf(" Exit");
            textcolor(15);  textbackground(0);
            gotoxy(7,1);
            cprintf("%c  %c File %c  %c",179,17,16,179);
            switch(n%5)
           {
                case 0:gotoxy(9,3);  cprintf(" New      "); break;
                case 1:gotoxy(9,4);  cprintf(" Open     "); break;
                case 2:gotoxy(9,5);  cprintf(" Save     "); break;
                case 3:gotoxy(9,6);  cprintf(" Save as  "); break;
                case 4:gotoxy(9,8);  cprintf(" Exit     "); break;
           }
      }

     /********************************************************/
     if(m%3==1) /*��Edit�˵���*/
    {
            window(28,2,38,7);
            textcolor(0);
            textbackground(7);
            for(i=0;i<5;i++)
           {
                gotoxy(1,1+i);
                insline();
            }
            window(1,1,80,25);
            gotoxy(27,1);
            for(i=1;i<=5;i++)
           {
                gotoxy(28,1+i);
                cprintf("%c",179);
                gotoxy(39,1+i);
                cprintf("%c",179);
            }
            for(i=1;i<=11;i++)
           {
                  gotoxy(28+i,2);
                  cprintf("%c",196);
                  gotoxy(28+i,7);
                  cprintf("%c",196);
            }

            textbackground(0);
            gotoxy(30,8); cprintf("            ");
            for(i=0;i<7;i++)
           {
                  gotoxy(40,2+i);
                  cprintf("   ");
           }
            textbackground(7);
            gotoxy(28,2);  cprintf("%c",218);
            gotoxy(28,7);  cprintf("%c",192);
            gotoxy(39,2);  cprintf("%c",191);
            gotoxy(39,7);  cprintf("%c",217);
            gotoxy(29,3);  cprintf("  Cut     ");
            gotoxy(29,4);  cprintf("  Copy    ");
            gotoxy(29,5);  cprintf("  Paste   ");
            gotoxy(29,6);  cprintf("  Clear   ");
            textcolor(15);  textbackground(0);
            gotoxy(27,1);
            cprintf("%c  %c Edit %c  %c",179,17,16,179);
            switch(n%4)
            {
                    case 0:gotoxy(29,3);  cprintf("  Cut     "); break;
                    case 1:gotoxy(29,4);  cprintf("  Copy    "); break;
                    case 2:gotoxy(29,5);  cprintf("  Paste   "); break;
                    case 3:gotoxy(29,6);  cprintf("  Clear   "); break;
            }
      }

    /*********************************************************/
     if(m%3==2) /*��Help�˵���3*/
    {
            window(48,2,48,6);
            textcolor(0);
            textbackground(7);
            for(i=0;i<3;i++)
            {
                    gotoxy(1,1+i);
                    insline();
            }
            window(1,1,80,25);
            gotoxy(47,1);
            for(i=1;i<=5;i++)
            {
                    gotoxy(48,1+i);
                    cprintf("%c",179);
                    gotoxy(59,1+i);
                    cprintf("%c",179);
            }
            for(i=1;i<=11;i++)
            {
                    gotoxy(48+i,2);
                    cprintf("%c",196);
                    gotoxy(48+i,6);
                    cprintf("%c",196);
            }

            textbackground(0);
            gotoxy(50,7); cprintf("            ");
            for(i=0;i<6;i++)
           {
                  gotoxy(60,2+i);
                  cprintf("   ");
           }
            textbackground(7);
            gotoxy(48,2);   cprintf("%c",218);
            gotoxy(48,6);   cprintf("%c",192);
            gotoxy(59,2);   cprintf("%c",191);
            gotoxy(59,6);   cprintf("%c",217);
            gotoxy(49,3);   cprintf("Help...   ");
            gotoxy(49,5);   cprintf("About...  ");
            for(i=1;i<=10;i++)
            {
                    gotoxy(48+i,4);
                    cprintf("%c",196);
            }
            textcolor(15);  textbackground(0);
            gotoxy(47,1);
            cprintf("%c  %c Help %c  %c",179,17,16,179);
            switch(n%2)
            {
                    case 0:gotoxy(49,3);  cprintf("Help...   "); break;
                    case 1:gotoxy(49,5);  cprintf("About...  "); break;
            }
    }
 }

int menuctrl(Hnode *Hhead,int A) /*�˵�����*/
  {
        int x,y,i,B,value,flag=100,a,b;
        x=wherex();  y=wherey();
        if(A==F1) {  drawmenu(0,flag);   value=300;  } /*��ʾFile�����Ӳ˵�,���������ʾ�ڵ�һ���Ӳ˵���*/
        if(A==F2) {  drawmenu(1,flag);   value=301;  } /*��ʾEdit�����Ӳ˵�,���������ʾ�ڵ�һ���Ӳ˵���*/
        if(A==F3) {  drawmenu(2,flag);   value=302;  } /*��ʾHelp�����Ӳ˵�,���������ʾ�ڵ�һ���Ӳ˵���*/

        if(A==F1||A==F2||A==F3)
       {
                while((B=bioskey(0))!=ESC) /*ѡ���û�����*/
               {
                      if(flag==0)   flag=100;
                      if(value==0)  value=300;  /*��valueΪ�ֲ�����*/

                      if(B==UP)     drawmenu(value,--flag); /*ѭ��������*/
                      if(B==DOWN)   drawmenu(value,++flag); /*ѭ��������*/

                      if(B==LEFT) /*�˵���֮��ѭ��ѡ�����ƣ�*/
                     {
                            flag=100;
                            drawmain();
                            window(2,2,79,23);
                            textbackground(9);
                            for(i=0;i<24;i++)
                                insline();
                            window(3,3,78,23);
                            textcolor(10);
                            view(Hhead);
                            drawmenu(--value,flag);

                      }
                       if(B==RIGHT)/*�˵���֮��ѭ��ѡ�����ƣ�*/
                     {
                            flag=100;
                            drawmain();
                            window(2,2,79,23);
                            textbackground(9);
                            for(i=0;i<24;i++)
                                insline();
                            window(3,3,78,23);
                            textcolor(10);
                            view(Hhead);
                            drawmenu(++value,flag);

                     }
                       if(B==ENTER) /*ѡ��ĳ���˵�����Ӳ˵��ѡ��ĳ�*/
                      {
                            if(value%3==0)  b=5; /*File����5���Ӳ˵���*/
                            if(value%3==1)  b=4; /*Edit����4���Ӳ˵���*/
                            if(value%3==2)  b=2; /*Help����2���Ӳ˵���*/
                            a=(value%3)*10+flag%b;/*a��ʾѡ���Ӳ˵��ı��*/
                            drawmain();
                            window(2,2,79,23);
                            textbackground(9);
                            for(i=0;i<24;i++)
                                   insline();
                            window(3,3,78,23);
                            textcolor(10);
                            view(Hhead);
                            gotoxy(x,y);
                            if(a==0)   return 100; /*New*/
                            if(a==1)   return 101; /*Open*/
                            if(a==2)   return 102; /*Save*/
                            if(a==3)   return 103; /*Save As*/
                            if(a==4)   exit(0);    /*Exit*/

                            if(a==10)  return Cx; /*Cut*/
                            if(a==11)  return Cc; /*Copy*/
                            if(a==12)  return Cv; /*Paste*/
                            if(a==13)  return DEL;/*Clear*/

                            if(a==20)  return 120; /*Help... */
                            if(a==21)  return 121; /*About...*/
                      }

                       gotoxy(x+2,y+2);

              }
              /*��������F1��F2��F3*/
                drawmain();
                window(2,2,79,23);
                textbackground(9);
                for(i=0;i<24;i++)
                     insline();
                window(3,3,78,23);
                textcolor(10);
                view(Hhead);
                gotoxy(x,y);



       }
        return A;


  }


/*��head��ָ���е���������ָ�ĸ����е������е��������ֵд���ļ����ļ�·�����ļ������û�ָ��*/
void save(Hnode *head)
{
FILE* fp;
Hnode *q;
node *p;
int count=0,x,y;
char filename[10]; /*�����ļ���*/
q=head;
clrscr();/*����*/
printf("Enter infile name,for example [c:\\wb.txt]:");/*�����ļ�����ʽ*/
scanf("%s",filename); /*�����ļ���*/
fp=fopen(filename,"w");
if(fp==NULL) /*���ļ�ʧ��*/
{
  printf("\n=====>open file error!\n");
  getchar();
  return ;
}
       do{
           p=q->next; /*ָ��node���͵�����*/
           while(p!=NULL)
             {      if((int)p->ch==13)
                    {
                      fputc('\n',fp);p=p->next; count++;
                     }
                    else
                    {fputc(p->ch, fp);
                     p=p->next;
                     count++;}
             }
           q=q->nextl;
         }while(q!=NULL);

fclose(fp); /*�رմ��ļ�*/
return ;
}

/*�ļ����Ϊ:��head��ָ���е���������ָ�ĸ����е������е��������ֵд���ļ����ļ�·�����ļ������û�ָ��*/
void saveas(Hnode *head)
{
FILE* fp;
Hnode *q;
node *p;
int count=0,x,y;
char filename[10]; /*�����ļ���*/
q=head;
clrscr();/*����*/
printf("Enter infile name,for example [c:\\wb.txt]:");/*�����ļ�����ʽ*/
scanf("%s",filename); /*�����ļ���*/
fp=fopen(filename,"w");
if(fp==NULL) /*���ļ�ʧ��*/
{
  printf("\n=====>open file error!\n");
  getchar();
  return ;
}
       do{
           p=q->next; /*ָ��node���͵�����*/
           while(p!=NULL)
             {       if((int)p->ch==13)
                    {
                      fputc('\n',fp);p=p->next; count++;
                     }
                    else
                    {fputc(p->ch, fp);
                     p=p->next;
                     count++;}

             }
           q=q->nextl;
         }while(q!=NULL);

fclose(fp); /*�رմ��ļ�*/
return ;
}

/*�������ı��ļ��ж�ȡ�ļ����ݣ��������е�������е�������ʽ�����ݽṹ��*/
void opens(Hnode *Hp)
{
FILE* fp;
Hnode *q11,*q22;
node *p11,*p22,*hp;
char temp;
int count=0,flags=1;
char filename[10]; /*�����ļ���*/
clrscr();/*����*/
printf("Enter infile name,for example [c:\\wb.txt]:");/*�����ļ�����ʽ*/
scanf("%s",filename); /*�����ļ���*/
fp=fopen(filename,"r");/*��ֻ����ʽ���ļ���filename����Ҫ����*/
if(fp==NULL)/*���ļ�ʧ��*/
{  textbackground(2);
   textcolor(13);
   cprintf("open file error!");
   getchar();
   exit(0) ;
}
q11=Hp;
while(!feof(fp))
{   count=0;flags=1;
    q22=(Hnode *)malloc(sizeof(Hnode));/*�½�һ���е������еĽڵ�*/
    p11=(node *)malloc(sizeof(node));  /*�½�һ���е������еĽڵ�*/
    while((temp=fgetc(fp))!=10&&count<=76&&!feof(fp)) /*ѭ����������ʾ�ڵ�������һ�д�����ϣ���ʼ����*/
    {  p22=(node *)malloc(sizeof(node));/*�½�һ���е������еĽڵ�*/
       if(flags==1) {hp=p22;flags=0;} /*hp�����е������е��׽ڵ�ĵ�ַ*/
       p22->ch=temp;  p22->next=NULL;
       p11->next=p22; p11=p22;
       count++;
    }
    if(temp==10){ /*��Ϊ���з�������ת��Ϊ�س�������Ϊ�ڳ����У��ǰ��س��������*/
       p22=(node *)malloc(sizeof(node));p22->ch=13; p22->next=NULL;
       p11->next=p22; p11=p22;
    }
    if(!feof(fp))/*��û���������ļ����һ�лᴦ������.*/
    {q22->next=hp;q22->nextl=NULL; /*���洢���ַ������е��������е������е��½ڵ㽨������*/
     q11->nextl=q22;q11=q22;}
}
fclose(fp);
Hp=Hp->nextl;/*��ΪHp�����ڽڵ��������Ϊ�գ�����Hp=Hp->nextl*/
return ;
}


void main()
 {
          char a;
          int i,A,x,y,flag=0,b;
          Hnode *Hhead,*q;
          node *p1,*p2;
          Hhead=(Hnode *)malloc(sizeof(Hnode)); /*Ϊ�е��������׽ڵ�����ڴ�ռ�*/
          q=Hhead;      Hhead->nextl=NULL;
          p1=p2=q->next=(node *)malloc(sizeof(node)); /*Ϊ�е��������׽ڵ�����ڴ�ռ�*/
          p1->ch=13; p1->next=NULL;
          drawmain();     /*��ʾ������*/
          window(2,2,79,23);
          textbackground(9);
          for(i=0;i<24;i++)
                insline();
          window(3,3,78,23);
          textcolor(10);

          while(1)
         {
                while(bioskey(1)==0) continue; /*�ȴ��û�����*/
                a=A=bioskey(0); /*����������ַ��ļ�ֵ*/
                if(a>=32&&a<127) /*������Ϊ�����ַ���س���*/
               {

                     if(check(Hhead,wherey(),wherex())<=0)/*��ǰλ��û���ַ��������ǳ����ַ�����ִ������ַ�����*/
                    {
                            NUM++;
                            p2->ch=a;
                            putch(a);
                            if(NUM==76) /*�����������У��ֱ�����һ���µ��е�������е�����ڵ�*/
                           {
                                p2->next=NULL;
                                q->nextl=(Hnode *)malloc(sizeof(Hnode));
                                q=q->nextl;   q->nextl=NULL;  q->next=NULL;
                                p1=p2=q->next=(node *)malloc(sizeof(node));
                                p1->ch=13;  p1->next=NULL;
                                NUM=0;
                           }
                            else /*��������δ��һ��,����һ���µ��е�����ڵ�*/
                           {
                                 p2->next=(node *)malloc(sizeof(node));
                                 p2=p2->next;
                                 p2->ch=13;
                                 p2->next=NULL;

                           }
                     }

                      else /*��ǰλ�����ַ��������ǳ����ַ�,��ִ�в����ַ�����*/
                     {
                             x=wherex();  y=wherey();
                             insert(Hhead,wherey(),wherex(),a);
                             NUM++;
                             view(Hhead);
                             gotoxy(x,y);
                     }



                }

                /*������Ϊ�س���*/
                if(a==13)
               {
                       gotoxy(1,wherey()+1);
                       q->nextl=(Hnode *)malloc(sizeof(Hnode));
                       q=q->nextl;    q->nextl=NULL;   q->next=NULL;
                       p1=p2=q->next=(node *)malloc(sizeof(node));
                       p1->ch=13; p1->next=NULL;
                       NUM=0;
               }

                 x=wherex();   y=wherey();
                /*�ı�����������,��ǰ��겻�ڴ��ڵĵ�1��*/
                if((A==LEFT)&&(x!=1))  gotoxy(wherex()-1,wherey());
                /*�ı�����������,��ǰ����ڴ��ڵĵ�1��*/
                if((A==LEFT)&&(x==1))  gotoxy(abs(judge(Hhead,wherey()-1)),wherey()-1);
                /*�ı�����������,����ǰ�����ұ�һλ���ַ�*/
                if((A==RIGHT)&&check(Hhead,wherey(),wherex())>0)  gotoxy(wherex()+1,wherey());
                /*�ı����������������еĵ�1��,����ǰ���λ��û���ַ������еĵ�1�����ַ�*/
                if((A==RIGHT)&&check(Hhead,wherey()+1,1)!=0&&check(Hhead,y,x)<=0)  gotoxy(1,wherey()+1);
                 /*����*/
                if((A==RIGHT)&&x==76)    gotoxy(1,wherey()+1);
                 /*����*/
                if((A==UP)&&check(Hhead,wherey()-1,wherex())!=0)  gotoxy(wherex(),wherey()-1);
                 /*����*/
                if((A==UP)&&check(Hhead,wherey()-1,wherex())<=0)
               {
                    if(judge(Hhead,wherey()-1)==0)
                        gotoxy(-judge(Hhead,wherey()-1)+1,wherey()-1);
                    else
                        gotoxy(-judge(Hhead,wherey()-1),wherey()-1);
               }

                /*����*/
                if((A==DOWN)&&check(Hhead,wherey()+1,wherex())!=0)
                    gotoxy(wherex(),wherey()+1);

                /*����BackSpace��*/
                if(A==BACK) /*����BackSpace��*/
               {
                       flag=del(Hhead,wherey(),wherex()-1);
                       x=wherex()-1;    y=wherey();
                       view(Hhead);
                       if(flag==0)
                      {
                            if(x!=0)  gotoxy(x,y);
                            else  gotoxy(x+1,y);
                      }
                       if(flag==1)
                      {
                           gotoxy(x+1,y);
                           flag=0;
                      }
               }
               /*����˵�����F1 F2 F3*/
               if((A==F1)||(A==F2)||(A==F3)||(a<32||a>127))
               {   A=menuctrl(Hhead,A);
                  if(A==100){main();} /*�½��ļ�*/

                  if(A==101){ /*���ļ�*/
                    Hhead=(Hnode *)malloc(sizeof(Hnode));
                    opens(Hhead);
                    getchar();clrscr();gotoxy(3,3);view(Hhead);
                    }
                /*�����ļ�*/
                 if(A==102){save(Hhead);clrscr();cprintf("save successfully!");getch();gotoxy(3,3);view(Hhead);}
                /*�ļ����Ϊ*/
                 if(A==103){saveas(Hhead);clrscr();cprintf("save as successfully!");getch();gotoxy(3,3);view(Hhead);}
                /*����*/
                 if(A==120){clrscr();cprintf("<Help> F1:File  F2:Edit F3:Help ");
                           getch();gotoxy(3,3);view(Hhead);}
                 if(A==121){clrscr();cprintf("Abort:Version 2.0 Tel:XXXXXXXXXX");getch();gotoxy(3,3);view(Hhead);}
               }

                /*����DEL��,ɾ����ǰλ�õĵ����ַ�*/
               if(A==DEL)
               {
                      x=wherex();    y=wherey();
                      del(Hhead,wherey(),wherex());
                      view(Hhead);
                      gotoxy(x,y);
               }
               /*�����Ѿ�ѡ���ı��ַ��󣬰�DEL�������*/
               if(A==DEL&&value!=0)
                {
                      if(value>0)
                            x=wherex(),    y=wherey();
                      else
                            x=r[0].col, y=r[0].line;
                      for(i=0;i<abs(value);i++)
                     {
                           if(value>0)
                              del(Hhead,r[i].line,r[i].col);
                           if(value<0)
                              del(Hhead,r[abs(value)-1-i].line,r[abs(value)-1-i].col);
                     }
                      value=0; /*��valueΪȫ�ֱ���*/
                      view(Hhead);
                      gotoxy(x,y);
               }
              /*����Ctrl+x����*/
              if(A==Cx&&value!=0)
               {
                      if(value>0)
                            x=wherex(),    y=wherey();
                      else
                            x=r[0].col, y=r[i].line;
                      for(i=0;i<abs(value);i++)
                     {
                           if(value>0)
                              del(Hhead,r[i].line,r[i].col);
                           if(value<0)
                              del(Hhead,r[abs(value)-1-i].line,r[abs(value)-1-i].col);
                     }
                           backup=value; /*����r�������ֵԪ�ص�����±�ֵ*/
                           value=0; /*��valueΪȫ�ֱ���*/
                           view(Hhead);
                           gotoxy(x,y);
               }

               /*����Ctrl+c����*/
                if(A==Cc&&value!=0)
               {
                     x=wherex();      y=wherey();
                     backup=value;    value=0; /*��valueΪȫ�ֱ���*/
                     view(Hhead);
                     gotoxy(x,y);
               }

               /*����Ctrl+v����*/
                if(A==Cv&&backup!=0)
               {
                     x=wherex();    y=wherey();
                     if(backup<0) /*Ctrl+���Ƽ�ѡ�����ı������д˵�ǰλ��*/
                            for(i=0;i<abs(backup);i++)
                                insert(Hhead,y,x+i,r[i].ch);/*�������*/


                     if(backup>0) /*Ctrl+���Ƽ�ѡ�����ı������д˵�ǰλ��*/
                            for(i=0;i<backup;i++)
                                insert(Hhead,y,x+i,r[backup-1-i].ch);

                     view(Hhead);
                     gotoxy(x,y);
               }
               /*����Ԥ��*/
                if(A==F10)
               {
                        qview(Hhead);
                        view(Hhead);
                        gotoxy(x,y);
               }

                /*����Ctrl+���Ƽ������Ƽ�*/
                if(A==CL||A==CR)    control(A,Hhead);
                /*��ʾ��ǰ���к�*/
                x=wherex();   y=wherey();
                window(1,1,80,25);
                textcolor(0);
                textbackground(7);
                gotoxy(10,25); /*��25�У���10��,�����ǰ�к�wherey()*/
                cprintf("%-3d",y);
                gotoxy(24,25); /*��25�У���24��*/
                cprintf("%-3d",x);
                window(3,3,78,23);
                textcolor(10);
                gotoxy(x,y);
                textcolor(10);
                textbackground(1);
        }
  }
