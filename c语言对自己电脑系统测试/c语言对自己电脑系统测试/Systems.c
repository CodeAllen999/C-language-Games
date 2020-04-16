#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <dos.h>
#include <graphics.h> 												
/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

/*����ͷ�ļ�*/
/*struct dfree
{
    unsigned df_avail;//��ʹ�õĴ���
    unsigned df_total;//ÿ�������������Ĵ���
    unsigned df_bsec;//ÿ���������ֽ���
    unsigned df_sclus;//ÿ���ص�������(����ʱ����0xFFFF)
} * dfreep;
struct fatinfo
{
    char fi_sclus;//ÿ����������
    char fi_fatid;//�ļ�������ֽ���
    int fi_nclus;//�ص���Ŀ
    int fi_bysec;//ÿ�������ֽ���
} * fatblkp;*/
  int choise;
/*��ʾϵͳʱ��*/
struct SYSTEMINFO
{
	 unsigned char current_second;      /*��ǰϵͳʱ�䣨�룩*/
	 unsigned char alarm_second;        /*����ʱ�䣨�룩*/
	 unsigned char current_minute;      /*��ǰϵͳʱ�䣨�֣�*/
	 unsigned char alarm_minute;        /*����ʱ�䣨�֣�*/
	 unsigned char current_hour;        /*��ǰϵͳʱ�䣨Сʱ��*/
	 unsigned char alarm_hour;          /*����ʱ�䣨Сʱ��*/
	 unsigned char current_day_of_week; /*��ǰϵͳʱ�䣨���ڼ���*/
	 unsigned char current_day;         /*��ǰϵͳʱ�䣨�գ�*/
	 unsigned char current_month;       /*��ǰϵͳʱ�䣨�£�*/
	 unsigned char current_year;        /*��ǰϵͳʱ�䣨�꣩*/
	 unsigned char status_registers[4]; /*�Ĵ���״̬*/
	 unsigned char diagnostic_status;   /*���λ*/
	 unsigned char shutdown_code;		/*�ػ�����*/
	 unsigned char drive_types;			/*��������*/
	 unsigned char reserved_x;          /*����λ*/
	 unsigned char disk_1_type;			/*Ӳ������*/
	 unsigned char reserved;			/*����λ*/
	 unsigned char equipment;			/*�豸��*/
	 unsigned char lo_mem_base;					
	 unsigned char hi_mem_base;
	 unsigned char hi_exp_base;
	 unsigned char lo_exp_base;
	 unsigned char fdisk_0_type;		/*����������0����*/
	 unsigned char fdisk_1_type;		/*����������1����*/
	 unsigned char reserved_2[19];		/*����λ*/
	 unsigned char hi_check_sum;
	 unsigned char lo_check_sum;
	 unsigned char lo_actual_exp;
	 unsigned char hi_actual_exp;
	 unsigned char century;				/*������Ϣ*/
	 unsigned char information;
	 unsigned char reserved3[12];		/*����λ*/
};
Systeminof()
{
	struct SYSTEMINFO systeminfo;		/*����SYSTEMINFO�ṹ����*/
	int i,size;							/*�������ͱ���*/
	char *ptr_sysinfo,byte;				/*�����ַ�ָ��������ַ�����*/
	clrscr();							/*����	*/							
	puts("********************************************");
	puts("* Get configure information of your system *");
	puts("********************************************");
	size=sizeof(systeminfo);			/*�ṹռ���ֽ���*/
	ptr_sysinfo=(char*)&systeminfo;		/*���ṹ��ַת��Ϊ�ַ�ָ��*/
	for(i=0;i<size;i++)
	{
	    outportb(0x70,(char)i);				/*���������Ӳ���˿���*/
	    byte=inportb(0x71);				/*��Ӳ���˿�������*/
	    *ptr_sysinfo++=byte;			/*���ֽ�Ϊ��λ����Ϊ����SYSTEMINFO��ֵ*/
	}
	printf("--The hard disk type is: %d.\n", systeminfo.disk_1_type);/*Ӳ������*/
	printf("--The drive type     is: %d.\n", systeminfo.drive_types);/*��������*/
	printf("--The equipment_num  is: %d.\n", systeminfo.equipment);	/*�豸��*/
	/*��ǰ����*/
	printf("--The current date   is: %x/%x/0%x.\n",systeminfo.current_day,systeminfo.current_month,systeminfo.current_year);
	/*��ǰʱ��*/
	printf("--The current time   is: %x:%x:%x.\n", systeminfo.current_hour,systeminfo.current_minute,systeminfo.current_second);
	/*����ʱ��*/
	printf("--The alarm time     is: %x:%x:%x.\n", systeminfo.alarm_hour,systeminfo.alarm_minute,systeminfo.alarm_second);
	
}
Paths(void)
{
    char *path,  *ptr;
    int i = 0;
    puts(" This program is to get the information of environ.");
    /* ��õ�ǰ���������е�path��Ϣ */
    while (environ[i])								/*ѭ��������еĻ�������*/
        printf(" >> %s\n", environ[i++]);
}

Stime(){
        time_t now;					            /*����time_t���ͱ���*/
	    time(&now);					            /*��ȡ��ǰϵͳ������ʱ��*/
	    printf("\nNow is:%s",ctime(&now));	    /*�����ǰϵͳ������ʱ��*/

        }
void DetectHDD()											/*���Ե�ǰ����������*/
{
    struct dfree diskfree; 										/*����ṹ�����*/
    struct fatinfo fatinfo;
    puts("The information of the current disk is :\n");					/*��һ�ַ���������,������ʾ������*/
    													
    getdfree(0,&diskfree);										/*��ȡ��ǰ������������Ϣ*/
    getfat(0,&fatinfo);											/*��ȡ�ļ��������Ϣ*/
    puts("----------------- hard disk space ------------------");				/*��һ�ַ���������,���ڶԼ�����ʾ��*/
    														/*���ݽ���˵��*/
    printf(">>The num of avaible clusters is : %d\n",diskfree.df_avail);		/*�����ʹ�õĴ���*/
    printf(">>The num of all clusters is : %d\n",diskfree.df_total);			/*��������������Ĵ���*/
    printf(">>The num of bytes of every sector is : %d\n",diskfree.df_bsec);	/*���ÿ���������ֽ����ֽ���*/
    printf(">>The num of sectors of every cluster is : %d\n",diskfree.df_sclus);	/*���ÿ���ص�������*/
    puts("----------- file allocation table -------------");					/*��һ�ַ���������,���ڶԼ�����ʾ��*/
    printf(">>The num of sectors of every cluster is : %d\n",fatinfo.fi_sclus);	/*���ÿ����������*/
    printf(">>The num of bytes of file allocation table is : %d\n",fatinfo.fi_fatid);	/*�ļ�������ֽ���*/
    printf(">>The num of clusters is : %d\n",fatinfo.fi_nclus); 			/*�ص���Ŀ*/
    printf(">>The num of ytes of every sector is : %d\n",fatinfo.fi_bysec); 		/*ÿ�������ֽ���*/
}
Xcar() 
{ 
char *dvrname[] = {
"requests detection", 
"a CGA", 
"an MCGA", 
"an EGA", 
"a 64K EGA", 
"a monochrome EGA", 
"an IBM 8514", 
"a Hercules monochrome", 
"an AT&T 6300 PC", 
"a VGA", 
"an IBM 3270 PC" 
}; 

int gdriver, gmode, errorcode; 
detectgraph(&gdriver, &gmode); 
errorcode = graphresult(); 
if (errorcode != 0)
	{
	printf("Graphics error: %s\n", grapherrormsg(errorcode));
	} 

clrscr(); 
printf("You have %s video display card.\n", dvrname[gdriver]);
} 

inits(){
    printf("1.Show the time !\n");
    printf("2.Show the information of the current disk\n");
    printf("3.Show the inof of sytem! \n");
    printf("4.Show the path inof! \n"); 
    printf("5.Show the of inofmation of display card!\n");
       
        }
int main()
{
    inits();
    loop:
    printf("\n");
    printf("input your choise:"); 
    scanf("%d",&choise); 
    switch(choise){
        case 1:   inits();
                  Stime();
                  goto loop;  
        case 2:   inits();
                  DetectHDD();
                  goto loop;  
        case 3:   inits();
                  Systeminof();
                  goto loop;  
        case 4:   inits();
                  Paths();
                  goto loop;  
        case 5:   inits();
                  Xcar();
                  goto loop;  
                                  
  }
  system("PAUSE");	
  return 0;
}
