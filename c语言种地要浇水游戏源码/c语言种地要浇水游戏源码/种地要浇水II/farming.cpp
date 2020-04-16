/* ����ѧȥ����վ�ռ� http://www.zixue7.com */
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string>
using namespace std;

#define PI 3.1415926535
int coin = 10;			// ��ʼ10ö��ң�Ӯ׬5��������ÿ�2��������3����Ҳ��㲻�����������������������ҽ�ҹ��㣩
int row = 0, col = 0;	// ��ǰѡ�е���ؿ�


int my_rand()	// ����1��11�������
{
	return (rand()%11)+1;
}


//11���������Ӧ��11�������
//		1��    2��    3��   4��     5��      6��      7��      8��      9��     10��     11��
//0�գ�1��2�� 3��4�� 5��6�� 7��8�� 9��10�� 11��12�� 13��14�� 15��16�� 17��18�� 19��20�� 21��22
//��һ��ÿ������ǰ��Ϊ��ˮ��������������Ϊ�ɺԣ�ż�������Ƕ�11�������ϸ��
bool tongchang[11][4] = {
  //��������ͨ�����(�������11���������ؿ�)
	1,1,1,1,/* �� */		1,1,1,0,/* �� */

	1,1,0,1,/* �� */		1,0,1,1,/* �� */
	
	0,1,1,1,/* �� */		0,1,0,1,/* �� */
	
	1,0,0,1,/* �� */		0,1,1,0,/* �� */
	
	1,0,1,0,/* �� */		0,0,1,1,/* �� */
	
	1,1,0,0/* �� */
};


int map[6][6]={0};//0��22,����6*6�������Ϣ


/*******************23�������ӦͼƬ********************/
IMAGE img[23];
//����ͼƬ
void load_field_img()
{
	IMAGE field_img;//���ڼ�������ͼ
	loadimage(&field_img, ".\\img\\img1.jpg", 0, 0, false);	
 	SetWorkingImage(&field_img);
	int height = field_img.getheight() / 9;
	int width  = field_img.getwidth();
	getimage(&img[0],  0, 0 * height, width, height);	// �յ�
	getimage(&img[22], 0, 1 * height, width, height);	// �ɺԩ�
	getimage(&img[16], 0, 2 * height, width, height);	// �ɺԩ�
	getimage(&img[4],  0, 3 * height, width, height);	// �ɺԩ�
	getimage(&img[1],  0, 4 * height, width, height);	// ��ˮ��
	getimage(&img[17], 0, 5 * height, width, height);	// ��ˮ��
	getimage(&img[21], 0, 6 * height, width, height);	// ��ˮ��
	getimage(&img[7],  0, 7 * height, width, height);	// ��ˮ��
	getimage(&img[2],  0, 8 * height, width, height);	// �ɺԩ�
	SetWorkingImage();
	//����9�ֿ�ֱ�Ӽ���ͼƬ�ֿ飬����14�ֿ���ʱ����תǰ9�ֻ�ȡ
	rotateimage(&img[3],  &img[7],  PI / 2);		// ��ˮ��
	rotateimage(&img[5],  &img[7],  3 * PI / 2);	// ��ˮ��
	rotateimage(&img[6],  &img[4],  PI);			// �ɺԩ�
	rotateimage(&img[8],  &img[4],  3 * PI / 2);	// �ɺԩ�
	rotateimage(&img[9],  &img[7],  PI);			// ��ˮ��
	rotateimage(&img[10], &img[4],  PI / 2);		// �ɺԩ�
	rotateimage(&img[11], &img[17], PI);			// ��ˮ��
	rotateimage(&img[12], &img[16], PI / 2);		// �ɺԩ�
	rotateimage(&img[13], &img[17], 3 * PI/2);		// ��ˮ��
	rotateimage(&img[14], &img[16], PI);			// �ɺԩ�
	rotateimage(&img[15], &img[17], PI / 2);		// ��ˮ��
	rotateimage(&img[18], &img[16], 3 * PI/2);		// �ɺԩ�
	rotateimage(&img[19], &img[21], PI / 2);		// ��ˮ��
	rotateimage(&img[20], &img[22], PI / 2);		// �ɺԩ�
}


/**************ˮ�������������������************************/
int sq_buff[4];//ˮ�����������������,����β�����ȳ�����11���������


void init_sq_buff()//��ʼˮ��������
{
	for(int i=3;i>=0;i--)
	{
		sq_buff[i]=my_rand();
	}
}


int get_sq_buff()//�仯ˮ��������
{
	int result=sq_buff[3];
	for(int i=2;i>=0;i--)
	{
		sq_buff[i+1]=sq_buff[i];
	}
	sq_buff[0]=my_rand();
	return result;
}


void print_sq_buff()//��ʾˮ��������
{//����31,35;31,99;31,162;31,233;
	putimage(31,35,&img[sq_buff[0]*2]);
	putimage(31,99,&img[sq_buff[1]*2]);
	putimage(31,162,&img[sq_buff[2]*2]);
	putimage(31,233,&img[sq_buff[3]*2]);
}


/*******************  11�������תӳ��(�����˳)****************************/
int rotated_list[][2]={
	-1,-1,//������ռλ
	1,1,		5,4,
	4,5,		2,3,
	3,2,		7,8,
	9,6,		6,9,
	8,7,		11,11,
	10,10
};


/*******************************************************/
//ˮ��ͨˮ����ĵݹ��жϣ�֮ǰ�����������ˮ���ɺԣ���map������Ϊ������Ԫ�ؼ�1��
void judge(int i,int j,int direction)//����Ϊmap���к��С��Լ�ˮԴ���ĸ����������0��1��2��3��
{
	if(i<0 || j<0 || map[i][j]==0 || map[i][j]%2==1)
	{
		//�ݹ����������Խ�硢�������Ѿ���ˮ
		return;
	}
	int type=(map[i][j]+1)/2;//�õ�1��11�����֣���Ӧ��������
	if(tongchang[type-1][direction])//������ˮԴ��ͨ
	{
		map[i][j]-=1;//����עˮ
		//�����򱾿��������������ݹ�
		for(int n=0;n<4;n++)
		{
			if(n==direction)
			{
				continue;//����ˮԴ����
			}
			if(tongchang[type-1][n]==1)//�������������ĳһ��ͨ��
			{
				if(n==0)//��ͨ��
				{
					judge(i-1,j,1);//��һ���ݹ��ˮԴ����
				}
				else if(n==1)//��ͨ��
				{
					judge(i+1,j,0);//��һ���ݹ��ˮԴ����
				}
				else if(n==2)//��ͨ��
				{
					judge(i,j-1,3);//��һ���ݹ��ˮԴ����
				}
				else if(n==3)//��ͨ��
				{
					judge(i,j+1,2);//��һ���ݹ��ˮԴ����
				}
			}
		}
	}
	else
	{
		return;
	}
}


//�ܵĵ�������
void check_water()
{
	//��������ˮ���ɺ�
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(map[i][j]%2==1)//�ÿ���ˮ
				map[i][j]+=1;
		}
	}
	//�ٵݹ��ж�
	judge(0,3,0);
}


/***************��������*********************/
//����ת�ַ����������ж�λ��
//����a��b�η�
int pw(int a,int b)
{
	int result=1;
	for(int i=0;i<b;i++)
		result*=a;
	return result;
}


void int_str(char str[11],int num,int jinzhi)
{
	if(num==0){str[0]='0';str[1]='\0';return;}
	int i=0,temp;
	while(num>=pw(jinzhi,i))i++;
	//��ʱ�����i+1λ����'\0'�������ַ���
	str[10]='\0';
	for(int n=i;n<10;n++)
	{
		str[n]=' ';
	}
	for(int k=i-1;k>=0;k--)
	{
		temp=num%jinzhi;//��ǰ���һλ
		num/=jinzhi;
		if(temp>=10 && temp<=15)temp+=('A'-10);
		else if(temp>=0 && temp<=9)temp+='0';
		else//�쳣����
		{
			str[0]='\0';
			return;
		}
		str[k]=(char)temp;
	}
}


void print_coin()
{
	char coin_str[11];
	int_str(coin_str,coin,10);
	setcolor(BLACK);
	outtextxy(552, 32, coin_str);
}


/**********************�����ػ����********************/
void draw_field(int i,int j)//׼������һ��i��j����0��5��������Ӧĳ����أ����仭��
{
	putimage(169+j*54,98+i*54,&img[map[i][j]]);
}


void draw_frame()//׼��������������ɫ��ѡ�п�
{
	setcolor(YELLOW);
	int a = col * 54, b = row * 54;
	rectangle(170 + a, 99  + b, 220 + a, 149 + b);
	rectangle(171 + a, 100 + b, 219 + a, 148 + b);
	rectangle(172 + a, 101 + b, 218 + a, 147 + b);
}


void refresh_all()//����������ؿ�
{
	//����ɫ0xCACEB7
	//����������31,35;31,99;31,162;31,233;
	//�������168,97;������222,97;������168,151;����493,422
	print_sq_buff();
	check_water();
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			draw_field(i,j);
		}
	}
	draw_frame();	
}


/******************ʤ���ж�********************/
void check_win()
{
	int water_num=0;

	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(map[i][j]==0)
			{
				return;//��û������
			}
			if(map[i][j]%2==1)
			{
				water_num++;
			}
		}
	}
	if(water_num==36)
	{
		string temp="��ɽ�����5���\n";
		int add=5;
		if(my_rand()%3==0)
		{
			temp+="��Ʒ׷�ӣ�2���\n";
			add+=2;
		}
		if(row==0 && col==3)
		{
			temp+="��ɳɾ͡�˲Ϣ��ͨ����׷��10���\n";
			add+=10;
		}
		int n;
		bool feishui=true;//����ˮ����������ɾ��ж�
		for(n=0;n<6;n++)
		{
			if(tongchang[ map[0][n]/2 ][0] && n!=3)//���г��ڣ��ж�ʧ��
			{
				feishui=false;
				break;
			}
			else if(tongchang[ map[n][0]/2 ][2])//���г��ڣ��ж�ʧ��
			{
				feishui=false;
				break;
			}
			else if(tongchang[ map[5][n]/2 ][1])//���г��ڣ��ж�ʧ��
			{
				feishui=false;
				break;
			}
			else if(tongchang[ map[n][5]/2 ][3])//���г��ڣ��ж�ʧ��
			{
				feishui=false;
				break;
			}
		}
		if(feishui)
		{
			temp+="��ɳɾ͡���ˮ�����������׷��15���\n";
			add+=15;
		}
		coin+=add;
		char str[11];
		int_str(str,add,10);
		str[3]='\0';
		temp+="�ܼƣ�";
		temp+=str;
		temp+="���";
		MessageBox(NULL,temp.c_str(),"������뷨",MB_SYSTEMMODAL);
	}
	else
	{
		coin-=2;
		if(coin<=0)
		{
			coin=0;
			MessageBox(NULL,"����ʧ�ܣ�Ǯ����0�󲻻��ٿ�","���ʱ�",MB_SYSTEMMODAL);
		}
		else
		{
			MessageBox(NULL,"����ʧ�ܣ�ʧȥ���2","���ʱ�",MB_SYSTEMMODAL); 
		}		
	}
	//��������
	init_sq_buff();
	memset(map, 0, sizeof(int)*36);
	row=0,col=0;
	print_coin();
	print_sq_buff();
	refresh_all();
	FlushBatchDraw();
}


int main()
{
	srand((unsigned)time(NULL));
	init_sq_buff();
	char c;
	// ��ͼ������ʼ��
	initgraph(640, 480);	
	load_field_img();
	setbkcolor(0xcaceb7);
	BeginBatchDraw();
	// ���ؽ���
	IMAGE img_main;	
	loadimage(&img_main, _T(".\\img\\main.jpg"));
	putimage(0, 0, &img_main);
	//������ʼ����
	print_coin();
	init_sq_buff();
	print_sq_buff();
	refresh_all();
	FlushBatchDraw();

	// ɨ�谴��
	while(1)
	{//�����-32and��72��80��75��77���������ң��ո�32��
		c = _getch();
		if(c == -32)
		{
			c = _getch();
			if(c == 72)//��
			{
				if(row==0)//����������
					continue;
				else
				{
					row--;
					refresh_all();
					FlushBatchDraw();
				}
			}
			else if(c == 80)//��
			{
				if(row==5)//����������
					continue;
				else
				{
					row++;
					refresh_all();
					FlushBatchDraw();
				}
			}
			else if(c == 75)//��
			{
				if(col==0)//����������
					continue;
				else
				{
					col--;
					refresh_all();
					FlushBatchDraw();
				}
			}
			else if(c == 77)//��
			{
				if(col==5)//����������
					continue;
				else
				{
					col++;
					refresh_all();
					FlushBatchDraw();
				}
			}
		}
		else if(c==32)//�ո�
		{
			if(map[row][col]==0)
			{
				map[row][col]=get_sq_buff()*2;
				print_sq_buff();
				check_water();
				refresh_all();
				FlushBatchDraw();
				check_win();
			}
			else
			{
				MessageBox(NULL,"�������ѷ���ˮ�������ɸ���","��",MB_SYSTEMMODAL);
			}
		}
		else if(c=='R' || c=='r')//����
		{
			if(coin>1)
			{
				coin-=2;
				init_sq_buff();
				memset(map, 0, sizeof(int)*36);
				row=0,col=0;
				print_coin();
				print_sq_buff();
				refresh_all();
				FlushBatchDraw();
			}
			else
			{
				MessageBox(NULL,"��Ҳ���2������ʹ�ø��ؼ�","��",MB_SYSTEMMODAL);
			}
		}
		else if(c=='S' || c=='s')//˳ʱ��
		{
			if(coin>2)
			{
				sq_buff[3]=rotated_list[sq_buff[3]][1];
				putimage(31,233,&img[sq_buff[3]*2]);
				coin-=3;
				print_coin();
				FlushBatchDraw();
			}
			else
			{
				MessageBox(NULL,"��Ҳ���3������ʹ�ø��ؼ�","��",MB_SYSTEMMODAL);
			}
		}
		else if(c=='N' || c=='n')//��ʱ��
		{
			if(coin>2)
			{
				sq_buff[3]=rotated_list[sq_buff[3]][0];
				putimage(31,233,&img[sq_buff[3]*2]);
				coin-=3;
				print_coin();
				FlushBatchDraw();
			}
			else
			{
				MessageBox(NULL,"��Ҳ���3������ʹ�ø��ؼ�","��",MB_SYSTEMMODAL);
			}
		}
		else if(c=='T' || c=='t')//����һ��
		{
			if(coin>2)
			{
				get_sq_buff();
				print_sq_buff();
				coin-=3;
				print_coin();
				FlushBatchDraw();
			}
			else
			{
				MessageBox(NULL,"��Ҳ���3������ʹ�ø��ؼ�","��",MB_SYSTEMMODAL);
			}
		}
		else if(c=='H' || c=='h')//����
		{
			MessageBox(NULL,"Ӯ׬5����Ʒ��׷��2����������ÿ�2�������ؼ���3��\n��Ҳ��㲻����ʹ���ؼ����䵽���0�Ժ����Ǯ��\n����ɾͣ�\n��˲Ϣ��ͨ������������ˮ��ˮ����׷��10��ң�\n����ˮ�����������ˮ����գ�׷��15��ҡ�","����",MB_SYSTEMMODAL|MB_ICONINFORMATION);
		}
		else if(c==27)//esc
		{
			break;
		}
	}
	EndBatchDraw();
	closegraph();
	return 0;
}