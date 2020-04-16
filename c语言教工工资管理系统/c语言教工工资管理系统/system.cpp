#include<iostream.h>
#include<string.h>
#include<fstream.h>
#include<stdlib.h>  

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

const int EMP=1000;//ѧԺ�̹���������������Ҫ���Է�����************************
void numbertochar(char*,double);

//�������̹���employee******************************************************
class employee{
private:
	//   ����     �̹���     ְλ     �Ա�     �绰����************************
	char name[10],number[10],post[10],sex[10],telephone[15];
	int age;//����*************************************************************
	double monthwages;//�¹���*************************************************
	static long employees;//ѧԺ�̹�����***************************************
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
				cout<<"�������(���ܶ���15����ĸ��5������)�����������롣\n";
				char temp1[15];
				cout<<"��    ��    ��:\t";
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
				cout<<"�������(���ܶ���15����ĸ��5������)�����������롣\n";
				char temp1[10];
				cout<<"��          ��:\t";
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
				cout<<"�������(���ܶ���ʮ����ĸ���������)�����������롣\n";
				char temp1[10];
				cout<<"ְ           λ\t";
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
		cout<<"�Ա�(1���У�2��Ů):";
resex:		char temp1[5];
			cin>>temp1;
			if(strlen(temp1)==1)
			{
				switch(temp1[0])
				{
				case '1':
					strcpy(sex,"��");
					break;
				case '2':
					strcpy(sex,"Ů");
					break;
				default:
					cout<<"������ѡ��1��2��";
					goto resex;
				}
			}
			else
			{
				cout<<"������ѡ��1��2��";
				goto resex;
			}
	}
	void settelephone(char temp[])
	{
retelephone:	if(strlen(temp)>20)
				{
					cout<<"�������(���ܶ����ʮ������)�����������롣\n";
					char temp1[20];
					cout<<"��  ��  ��  ��:\t";
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
				cout<<"����������������롣\n";
				int temp1;
				cout<<"��          ��:\t";
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
//��ʦ��Ķ���*****************************************************************
class technician: public  employee{
protected:
	static int technicians;//����������ʦ������********************************
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
		//��ʦ�Ĺ���Ϊ�γ���*��ʱ����100ÿ��ʱ**************************
	}
};
int technician::technicians=0;
//����Ա��Ķ���***************************************************************
class manager:public employee{
	static int managers;//����Ա������*****************************************
public:
	int getmanagers()
	{
		return managers;
	}
	void monthly_wages()
	{
        setmonthwages(5000);//����Ա�Ĺ���Ϊ��ǧ�̶�***************************
		managers++;
	}
};
int manager::managers=0;
//������Ķ���*****************************************************************
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
//������Ա��Ķ���*************************************************************
class sellermanager:public seller{
	static int sellermanagers;//������Ա������*********************************
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

//�����������ԭ��������*******************************************************
void inputtechnician(employee&);
void inputmanager(employee&);
void inputseller(employee&);
void inputsellermanager(employee&);

void compositorall(employee*);//�����н̹��Ĺ��ʽ�������***********************
int printfile();//���ļ��е�������ʾ����ʾ����*********************************
void outputtofile(employee*);//�����ϱ��浽�ļ���******************************

//������***********************************************************************
int main()
{
	employee employeeall[EMP];
	int i=0;
	while(i<EMP)
	{
		system("cls"); //ˢ����Ļ**********************************************
		cout<<"***  ��ϵͳ�ܴ���"<<EMP<<"���̹�������  ***\n";
		cout<<"   ***  �Ѿ�������"<<employeeall[0].getemployees()
<<"�̹�������  ****\n";
		cout<<"   ********************************\n";
		cout<<"   ***  1�����뽲    ʦ������;  ***\n";
		cout<<"   ***  2�����븨 �� Ա������;  ***\n";
		cout<<"   ***  3�������    �ڵ�����;  ***\n";
		cout<<"   ***  4������������Ա������;  ***\n";
		cout<<"   ***  5���˳�����!            ***\n";
		cout<<"   ********************************\n";
		cout<<"��ѡ��:";
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
				system("cls"); //ˢ����Ļ**************************************
				compositorall(employeeall);//�����н̹��Ĺ��ʽ�������**********
				outputtofile(employeeall);//�����ϱ��浽�ļ���*****************
				cout<<"�Ƿ��ӡ���ϣ�y/n��";
				char a[5];
				cin>>a;
				if(a[0]=='y'||a[0]=='Y')
					printfile();//���ļ��е�������ʾ����ʾ����*****************
				return 1;
			default: 
				cout<<"\t�������������룡\n";			
			}
		}
		else
			cout<<"\t�������������룡\n";
	}
	compositorall(employeeall);//�����н̹��Ĺ��ʽ�������**********************
	outputtofile(employeeall);//�����ϱ��浽�ļ���*****************************
	printfile();//���ļ��е�������ʾ����ʾ����*********************************
	return 0;
}
//�̹�������Ϣ�����뺯��*******************************************************
void inputtechnician(employee &empl)
{
	technician tech;
	cout<<"\n���̹����ϣ�\n";
	char temp[20];
	cout<<"��          ��:\t";
	cin>>temp;
	empl.setname(temp);         
	cout<<"��    ��    ��:\t";
	cin>>temp;
	empl.setnumber(temp);        
	empl.setpost("��  ʦ");      
	empl.setsex();               
	cout<<"��  ��  ��  ��:\t";
	cin>>temp;
	empl.settelephone(temp);     
	int tempq=0;
	cout<<"��          ��:\t";
	cin>>tempq;
	empl.setage(tempq);            
	double tempp=0;
	cout<<"����ʱ��(��ʱ):\t";
	cin>>tempp;
	tech.monthly_wages(tempp);             
	empl.setmonthwages(tech.getmonthwages());      
	
}
//����Ա�Ļ�����Ϣ�����뺯��***************************************************
void inputmanager(employee &empl)
{
	manager mana;
	cout<<"\n��︨��Ա���ϣ�\n";
	char temp[20];
	cout<<"��          ��:\t";
	cin>>temp;
	empl.setname(temp);
	cout<<"��    ��    ��:\t";
	cin>>temp;
	empl.setnumber(temp);
	empl.setpost("��  ��  Ա");
	empl.setsex();
	cout<<"��  ��  ��  ��:\t";
	cin>>temp;
	empl.settelephone(temp);
	int tempq=0;
	cout<<"��          ��:\t";
	cin>>tempq;
	empl.setage(tempq);
	mana.monthly_wages();
	empl.setmonthwages(mana.getmonthwages());
}
//���ڵĻ�����Ϣ�����뺯��*****************************************************
void inputseller(employee &empl)
{
	seller sell;
	cout<<"\n���������ϣ�\n";
	char temp[20];
	cout<<"��          ��:\t";
	cin>>temp;
	empl.setname(temp);
	cout<<"��    ��    ��:\t";
	cin>>temp;
	empl.setnumber(temp);
	empl.setpost("��  ��");
	empl.setsex();
	cout<<"��  ��  ��  ��:\t";
	cin>>temp;
	empl.settelephone(temp);
	int tempq=0;
	cout<<"��          ��:\t";
	cin>>tempq;
	empl.setage(tempq);
	double tempp=0;
	cout<<"��    ��    ��:\t";
	cin>>tempp;
	sell.setsellroom(tempp);
	sell.monthly_wages();
	empl.setmonthwages(sell.getmonthwages());
}
//������Ա�Ļ�����Ϣ�����뺯��*************************************************
void inputsellermanager(employee &empl)
{
	sellermanager sellmana;
	cout<<"\n���������Ա���ϣ�\n";
	char temp[20];
	cout<<"��          ��:\t";
	cin>>temp;
	empl.setname(temp);
	cout<<"��    ��    ��:\t";
	cin>>temp;
	empl.setnumber(temp);
	empl.setpost("������Ա");
	empl.setsex();
	cout<<"��  ��  ��  ��:\t";
	cin>>temp;
	empl.settelephone(temp);
	int tempq=0;
	cout<<"��          ��:\t";
	cin>>tempq;
	empl.setage(tempq);
	sellmana.setsellroom(sellmana.getsellrooms());
	sellmana.monthly_wages();
	empl.setmonthwages(sellmana.getmonthwages());	
}
//�����ϱ��浽�ļ���***********************************************************
void outputtofile(employee *empl)
{
	ofstream fout;
	fout.open("E:\\ �������ͨ��ѧԺ��ʦ���ʹ���ϵͳ�ĵ�.txt");
	if(!fout)
		cout<<"Open file error!";
	else
	{
		fout<<"��  ��"<<"\t";
		fout<<"�̹���"<<"\t";
		fout<<"ְ    λ"<<"\t";
		fout<<"�Ա�"<<"\t";
		fout<<"����"<<"\t";
		fout<<"�绰����"<<"\t";
		fout<<"�¹���"<<"\n";
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

//���ļ��е�������ʾ����ʾ����*************************************************
int printfile()
{
	system("cls"); 
	ifstream fcin;
	fcin.open("E:\\�������ͨ��ѧԺ��ʦ���ʹ���ϵͳ�ĵ�.txt");
	if(!fcin)
	{
		cout<<"���ļ�ʧ�ܣ�ϵͳ�Զ��˳���";
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

//��ð�ݷ������н̹��Ĺ��ʽ�������*********************************************
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

