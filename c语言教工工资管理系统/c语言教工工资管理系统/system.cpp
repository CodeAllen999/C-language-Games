#include<iostream.h>
#include<string.h>
#include<fstream.h>
#include<stdlib.h>  

/* 【自学去】网站收集 http://www.zixue7.com */

const int EMP=1000;//学院教工总人数（跟据需要可以放缩）************************
void numbertochar(char*,double);

//定义基类教工类employee******************************************************
class employee{
private:
	//   姓名     教工号     职位     性别     电话号码************************
	char name[10],number[10],post[10],sex[10],telephone[15];
	int age;//年龄*************************************************************
	double monthwages;//月工资*************************************************
	static long employees;//学院教工人数***************************************
public:
	long getemployees()
	{
		return employees;
	}
	char*getnumber()
	{
		return number;
	}
	char*getname()
	{
		return name;
	}
	char*getpost()
	{
		return post;
	}
	char*getsex()
	{
		return sex;
	}
	char*gettelephone()
	{
		return telephone;
	}
	int getage()
	{
		return age;
	}
	double getmonthwages()
	{
		return monthwages;
	}
	void setnumber(char temp[])
	{
renumber:	if(strlen(temp)>15)
			{
				cout<<"输入错误(不能多余15个字母或5个汉字)！请重新输入。\n";
				char temp1[15];
				cout<<"教    工    号:\t";
				cin>>temp1;
				if(strlen(temp1)>15)
					goto renumber;
				else 
					strcpy(number,temp1);
			}
			else
				strcpy(number,temp);
	}
	void setname(char temp[])
	{
renumber:	if(strlen(temp)>15)
			{
				cout<<"输入错误(不能多余15个字母或5个汉字)！请重新输入。\n";
				char temp1[10];
				cout<<"姓          名:\t";
				cin>>temp1;
				if(strlen(temp1)>15)
					goto renumber;
				else 
					strcpy(name,temp1);
			}
			else
				strcpy(name,temp);
			employees++;
	}
	void setpost(char temp[])
	{
renumber:	if(strlen(temp)>10)
			{
				cout<<"输入错误(不能多余十个字母或五个汉字)！请重新输入。\n";
				char temp1[10];
				cout<<"职           位\t";
				cin>>temp1;
				if(strlen(temp1)>10)
					goto renumber;
				else 
					strcpy(post,temp1);
			}
			else
				strcpy(post,temp);
	}
	void setsex()
	{
		cout<<"性别(1、男；2、女):";
resex:		char temp1[5];
			cin>>temp1;
			if(strlen(temp1)==1)
			{
				switch(temp1[0])
				{
				case '1':
					strcpy(sex,"男");
					break;
				case '2':
					strcpy(sex,"女");
					break;
				default:
					cout<<"错误（请选择1或2）";
					goto resex;
				}
			}
			else
			{
				cout<<"错误（请选择1或2）";
				goto resex;
			}
	}
	void settelephone(char temp[])
	{
retelephone:	if(strlen(temp)>20)
				{
					cout<<"输入错误(不能多余二十个数字)！请重新输入。\n";
					char temp1[20];
					cout<<"电  话  号  码:\t";
					cin>>temp1;
					if(strlen(temp1)>20)
						goto retelephone;
					else 
						strcpy(telephone,temp1);
				}
				else
					strcpy(telephone,temp);
	}
	void setage(int temp)
	{
renumber:	if(temp<=18||temp>65)
			{
				cout<<"输入错误！请重新输入。\n";
				int temp1;
				cout<<"年          龄:\t";
				cin>>temp1;
				if(temp1<=0||temp1>120)
					goto renumber;
				else 
					age=temp1;
			}
			else
				age=temp;
	}
	void setmonthwages(double temp)
	{
		monthwages=temp;
	}
};
long employee::employees=0;
//讲师类的定义*****************************************************************
class technician: public  employee{
protected:
	static int technicians;//用来记数讲师的数量********************************
public:
	int gettechnicians()
	{
		return technicians;
	}
    void setnumber(char temp[])
	{
		technicians++;
		employee::setnumber(temp);
	}
    void monthly_wages(double temp)
	{
		setmonthwages(temp*100);
		//讲师的工资为课程量*课时工资100每课时**************************
	}
};
int technician::technicians=0;
//辅导员类的定义***************************************************************
class manager:public employee{
	static int managers;//辅导员的数量*****************************************
public:
	int getmanagers()
	{
		return managers;
	}
	void monthly_wages()
	{
        setmonthwages(5000);//辅导员的工资为五千固定***************************
		managers++;
	}
};
int manager::managers=0;
//教授类的定义*****************************************************************
class seller:public employee{
protected:
	static double sellroom;
	static double sellrooms;
	static int sellers;
public:
	int getsellers()
	{
		return sellers;
	}
	double getsellroom()
	{
		return sellroom;
	}
	double getsellrooms()
	{
		return sellrooms;
	}
	void setsellroom(double temp)
	{
		sellroom=temp;
		sellrooms=sellrooms+temp;
	}	
	void monthly_wages()
	{
		setmonthwages(sellroom*0.04);
		sellers++;
	}	
};
double seller::sellroom=0;
double seller::sellrooms=0;
int seller::sellers=0;
//行政人员类的定义*************************************************************
class sellermanager:public seller{
	static int sellermanagers;//行政人员的数量*********************************
public:
	int getsellermanagers()
	{
		return sellermanagers;
	}
	double getsellrooms()
	{
		return sellrooms;
	}
	void monthly_wages()
	{
		setmonthwages(sellrooms*0.005+5000);
		sellermanagers++;
	}
};
int sellermanager::sellermanagers=0;

//各数据输入的原函数声明*******************************************************
void inputtechnician(employee&);
void inputmanager(employee&);
void inputseller(employee&);
void inputsellermanager(employee&);

void compositorall(employee*);//对所有教工的工资降序排列***********************
int printfile();//把文件中的资料显示到显示器上*********************************
void outputtofile(employee*);//把资料保存到文件中******************************

//主函数***********************************************************************
int main()
{
	employee employeeall[EMP];
	int i=0;
	while(i<EMP)
	{
		system("cls"); //刷新屏幕**********************************************
		cout<<"***  本系统能存入"<<EMP<<"个教工的资料  ***\n";
		cout<<"   ***  已经输入了"<<employeeall[0].getemployees()
<<"教工的资料  ****\n";
		cout<<"   ********************************\n";
		cout<<"   ***  1、输入讲    师的资料;  ***\n";
		cout<<"   ***  2、输入辅 导 员的资料;  ***\n";
		cout<<"   ***  3、输入教    授的资料;  ***\n";
		cout<<"   ***  4、输入行政人员的资料;  ***\n";
		cout<<"   ***  5、退出输入!            ***\n";
		cout<<"   ********************************\n";
		cout<<"请选择:";
		char n[5];
		cin>>n;
		if(strlen(n)==1)
		{
			switch(n[0])
			{
			case '1': 
				inputtechnician(employeeall[i]);
				i++;
				break;
			case '2':
				inputmanager(employeeall[i]); 
				i++;
				break;
			case '3': 
				inputseller(employeeall[i]); 
				i++;
				break;
			case '4':
				inputsellermanager(employeeall[i]);
				i++;
				break;
			case '5': 
				system("cls"); //刷新屏幕**************************************
				compositorall(employeeall);//对所有教工的工资降序排列**********
				outputtofile(employeeall);//把资料保存到文件中*****************
				cout<<"是否打印资料（y/n）";
				char a[5];
				cin>>a;
				if(a[0]=='y'||a[0]=='Y')
					printfile();//把文件中的资料显示到显示器上*****************
				return 1;
			default: 
				cout<<"\t错误！请重新输入！\n";			
			}
		}
		else
			cout<<"\t错误！请重新输入！\n";
	}
	compositorall(employeeall);//对所有教工的工资降序排列**********************
	outputtofile(employeeall);//把资料保存到文件中*****************************
	printfile();//把文件中的资料显示到显示器上*********************************
	return 0;
}
//教工基本信息的输入函数*******************************************************
void inputtechnician(employee &empl)
{
	technician tech;
	cout<<"\n★★教工资料：\n";
	char temp[20];
	cout<<"姓          名:\t";
	cin>>temp;
	empl.setname(temp);         
	cout<<"教    工    号:\t";
	cin>>temp;
	empl.setnumber(temp);        
	empl.setpost("讲  师");      
	empl.setsex();               
	cout<<"电  话  号  码:\t";
	cin>>temp;
	empl.settelephone(temp);     
	int tempq=0;
	cout<<"年          龄:\t";
	cin>>tempq;
	empl.setage(tempq);            
	double tempp=0;
	cout<<"工作时间(课时):\t";
	cin>>tempp;
	tech.monthly_wages(tempp);             
	empl.setmonthwages(tech.getmonthwages());      
	
}
//辅导员的基本信息的输入函数***************************************************
void inputmanager(employee &empl)
{
	manager mana;
	cout<<"\n★★辅导员资料：\n";
	char temp[20];
	cout<<"姓          名:\t";
	cin>>temp;
	empl.setname(temp);
	cout<<"教    工    号:\t";
	cin>>temp;
	empl.setnumber(temp);
	empl.setpost("辅  导  员");
	empl.setsex();
	cout<<"电  话  号  码:\t";
	cin>>temp;
	empl.settelephone(temp);
	int tempq=0;
	cout<<"年          龄:\t";
	cin>>tempq;
	empl.setage(tempq);
	mana.monthly_wages();
	empl.setmonthwages(mana.getmonthwages());
}
//教授的基本信息的输入函数*****************************************************
void inputseller(employee &empl)
{
	seller sell;
	cout<<"\n★★教授资料：\n";
	char temp[20];
	cout<<"姓          名:\t";
	cin>>temp;
	empl.setname(temp);
	cout<<"教    工    号:\t";
	cin>>temp;
	empl.setnumber(temp);
	empl.setpost("教  授");
	empl.setsex();
	cout<<"电  话  号  码:\t";
	cin>>temp;
	empl.settelephone(temp);
	int tempq=0;
	cout<<"年          龄:\t";
	cin>>tempq;
	empl.setage(tempq);
	double tempp=0;
	cout<<"课    程    量:\t";
	cin>>tempp;
	sell.setsellroom(tempp);
	sell.monthly_wages();
	empl.setmonthwages(sell.getmonthwages());
}
//行政人员的基本信息的输入函数*************************************************
void inputsellermanager(employee &empl)
{
	sellermanager sellmana;
	cout<<"\n★★行政人员资料：\n";
	char temp[20];
	cout<<"姓          名:\t";
	cin>>temp;
	empl.setname(temp);
	cout<<"教    工    号:\t";
	cin>>temp;
	empl.setnumber(temp);
	empl.setpost("行政人员");
	empl.setsex();
	cout<<"电  话  号  码:\t";
	cin>>temp;
	empl.settelephone(temp);
	int tempq=0;
	cout<<"年          龄:\t";
	cin>>tempq;
	empl.setage(tempq);
	sellmana.setsellroom(sellmana.getsellrooms());
	sellmana.monthly_wages();
	empl.setmonthwages(sellmana.getmonthwages());	
}
//把资料保存到文件中***********************************************************
void outputtofile(employee *empl)
{
	ofstream fout;
	fout.open("E:\\ 计算机与通信学院教师工资管理系统文档.txt");
	if(!fout)
		cout<<"Open file error!";
	else
	{
		fout<<"姓  名"<<"\t";
		fout<<"教工号"<<"\t";
		fout<<"职    位"<<"\t";
		fout<<"性别"<<"\t";
		fout<<"年龄"<<"\t";
		fout<<"电话号码"<<"\t";
		fout<<"月工资"<<"\n";
		for(int i=0;i<empl[0].getemployees();i++)
		{		
			fout<<empl[i].getname()<<"\t";
			fout<<empl[i].getnumber()<<"\t";
			fout<<empl[i].getpost()<<"\t";
			fout<<empl[i].getsex()<<"\t";
			fout<<empl[i].getage()<<"\t";
			fout<<empl[i].gettelephone()<<"\t";
			fout<<empl[i].getmonthwages()<<"\n";
		}
	}
}	

//把文件中的资料显示到显示器上*************************************************
int printfile()
{
	system("cls"); 
	ifstream fcin;
	fcin.open("E:\\计算机与通信学院教师工资管理系统文档.txt");
	if(!fcin)
	{
		cout<<"打开文件失败，系统自动退出！";
		return 4;
	}
	char ch;
	while(fcin.get(ch))
	{		
		cout<<ch;
	}
	fcin.close();
	return 0;
}

//用冒泡法对所有教工的工资降序排列*********************************************
void compositorall(employee *temp)
{
	employee temp1;
	for(int j=0;j<temp[0].getemployees();j++)
		for(int i=temp[0].getemployees()-1;i>j;i--)
		{
			if(temp[i].getmonthwages()>temp[i-1].getmonthwages())
			{
				temp1=temp[i];
				temp[i]=temp[i-1];
				temp[i-1]=temp1;
			}
		}
}

