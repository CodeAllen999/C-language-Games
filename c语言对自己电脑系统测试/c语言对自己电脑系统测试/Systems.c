#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <dos.h>
#include <graphics.h> 												
/* 【自学去】网站收集 http://www.zixue7.com */

/*引用头文件*/
/*struct dfree
{
    unsigned df_avail;//可使用的簇数
    unsigned df_total;//每个磁盘驱动器的簇数
    unsigned df_bsec;//每个扇区的字节数
    unsigned df_sclus;//每个簇的扇区数(出错时返回0xFFFF)
} * dfreep;
struct fatinfo
{
    char fi_sclus;//每个簇扇区数
    char fi_fatid;//文件分配表字节数
    int fi_nclus;//簇的数目
    int fi_bysec;//每个扇区字节数
} * fatblkp;*/
  int choise;
/*显示系统时间*/
struct SYSTEMINFO
{
	 unsigned char current_second;      /*当前系统时间（秒）*/
	 unsigned char alarm_second;        /*闹钟时间（秒）*/
	 unsigned char current_minute;      /*当前系统时间（分）*/
	 unsigned char alarm_minute;        /*闹钟时间（分）*/
	 unsigned char current_hour;        /*当前系统时间（小时）*/
	 unsigned char alarm_hour;          /*闹钟时间（小时）*/
	 unsigned char current_day_of_week; /*当前系统时间（星期几）*/
	 unsigned char current_day;         /*当前系统时间（日）*/
	 unsigned char current_month;       /*当前系统时间（月）*/
	 unsigned char current_year;        /*当前系统时间（年）*/
	 unsigned char status_registers[4]; /*寄存器状态*/
	 unsigned char diagnostic_status;   /*诊断位*/
	 unsigned char shutdown_code;		/*关机代码*/
	 unsigned char drive_types;			/*驱动类型*/
	 unsigned char reserved_x;          /*保留位*/
	 unsigned char disk_1_type;			/*硬盘类型*/
	 unsigned char reserved;			/*保留位*/
	 unsigned char equipment;			/*设备号*/
	 unsigned char lo_mem_base;					
	 unsigned char hi_mem_base;
	 unsigned char hi_exp_base;
	 unsigned char lo_exp_base;
	 unsigned char fdisk_0_type;		/*软盘驱动器0类型*/
	 unsigned char fdisk_1_type;		/*软盘驱动器1类型*/
	 unsigned char reserved_2[19];		/*保留位*/
	 unsigned char hi_check_sum;
	 unsigned char lo_check_sum;
	 unsigned char lo_actual_exp;
	 unsigned char hi_actual_exp;
	 unsigned char century;				/*世纪信息*/
	 unsigned char information;
	 unsigned char reserved3[12];		/*保留位*/
};
Systeminof()
{
	struct SYSTEMINFO systeminfo;		/*声明SYSTEMINFO结构变量*/
	int i,size;							/*声明整型变量*/
	char *ptr_sysinfo,byte;				/*声明字符指针变量与字符变量*/
	clrscr();							/*清屏	*/							
	puts("********************************************");
	puts("* Get configure information of your system *");
	puts("********************************************");
	size=sizeof(systeminfo);			/*结构占用字节数*/
	ptr_sysinfo=(char*)&systeminfo;		/*将结构地址转换为字符指针*/
	for(i=0;i<size;i++)
	{
	    outportb(0x70,(char)i);				/*输出整数到硬件端口中*/
	    byte=inportb(0x71);				/*从硬件端口中输入*/
	    *ptr_sysinfo++=byte;			/*以字节为单位依次为变量SYSTEMINFO赋值*/
	}
	printf("--The hard disk type is: %d.\n", systeminfo.disk_1_type);/*硬盘类型*/
	printf("--The drive type     is: %d.\n", systeminfo.drive_types);/*驱动类型*/
	printf("--The equipment_num  is: %d.\n", systeminfo.equipment);	/*设备号*/
	/*当前日期*/
	printf("--The current date   is: %x/%x/0%x.\n",systeminfo.current_day,systeminfo.current_month,systeminfo.current_year);
	/*当前时间*/
	printf("--The current time   is: %x:%x:%x.\n", systeminfo.current_hour,systeminfo.current_minute,systeminfo.current_second);
	/*警报时间*/
	printf("--The alarm time     is: %x:%x:%x.\n", systeminfo.alarm_hour,systeminfo.alarm_minute,systeminfo.alarm_second);
	
}
Paths(void)
{
    char *path,  *ptr;
    int i = 0;
    puts(" This program is to get the information of environ.");
    /* 获得当前环境变量中的path信息 */
    while (environ[i])								/*循环输出所有的环境变量*/
        printf(" >> %s\n", environ[i++]);
}

Stime(){
        time_t now;					            /*声明time_t类型变量*/
	    time(&now);					            /*获取当前系统日期与时间*/
	    printf("\nNow is:%s",ctime(&now));	    /*输出当前系统日期与时间*/

        }
void DetectHDD()											/*测试当前磁盘驱动器*/
{
    struct dfree diskfree; 										/*定义结构体变量*/
    struct fatinfo fatinfo;
    puts("The information of the current disk is :\n");					/*送一字符串到流中,用于显示程序功能*/
    													
    getdfree(0,&diskfree);										/*获取当前磁盘驱动器信息*/
    getfat(0,&fatinfo);											/*获取文件分配表信息*/
    puts("----------------- hard disk space ------------------");				/*送一字符串到流中,用于对即将显示的*/
    														/*内容进行说明*/
    printf(">>The num of avaible clusters is : %d\n",diskfree.df_avail);		/*输出可使用的簇数*/
    printf(">>The num of all clusters is : %d\n",diskfree.df_total);			/*输出磁盘驱动器的簇数*/
    printf(">>The num of bytes of every sector is : %d\n",diskfree.df_bsec);	/*输出每个扇区的字节数字节数*/
    printf(">>The num of sectors of every cluster is : %d\n",diskfree.df_sclus);	/*输出每个簇的扇区数*/
    puts("----------- file allocation table -------------");					/*送一字符串到流中,用于对即将显示的*/
    printf(">>The num of sectors of every cluster is : %d\n",fatinfo.fi_sclus);	/*输出每个簇扇区数*/
    printf(">>The num of bytes of file allocation table is : %d\n",fatinfo.fi_fatid);	/*文件分配表字节数*/
    printf(">>The num of clusters is : %d\n",fatinfo.fi_nclus); 			/*簇的数目*/
    printf(">>The num of ytes of every sector is : %d\n",fatinfo.fi_bysec); 		/*每个扇区字节数*/
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
