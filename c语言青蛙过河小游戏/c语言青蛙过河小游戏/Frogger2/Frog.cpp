#include "stdafx.h"
#define PI 3.1415926535
#define UNIT PI/180
#include<math.h>//��ת���ٶ��õ�xƽ��

void initFrog(FrogType *frog)
{
	frog->ch=-1;
	frog->x=WINDOW_LEN/2;
	frog->speed=8;
	frog->life=5;
	frog->passed=0;
	frog->state=NORMAL;//����
	frog->coin=0;
	frog->score=0;
	frog->esc=0;


}
void resetFrog(FrogType *frog)
{
	frog->ch=-1;
	frog->x=WINDOW_LEN/2;
	frog->state=NORMAL;
	while(_kbhit()){_getch();}//����̻����ֹ��������������ʱ������
}

void moveFrog(FrogType *frog,int ChannelSpeed[])
{
	if(frog->state==NORMAL){//�����������������Ҳ�����ź�Ʈ��
		//��ģ��ͬ���������ƶ�
		if(frog->ch>-1&&frog->ch<CHANNEL_AMOUNT)
		{
			if(1==((frog->ch+1)%2))
			{frog->x-=ChannelSpeed[frog->ch];}
			else
			{frog->x+=ChannelSpeed[frog->ch];}
		}
		//ͨ�����̵��ƶ�

		if(GetAsyncKeyState('A'))//��ȡ����״̬�����¼���
		{
			if(!((-1==(frog->ch))&&((frog->x)-(frog->speed)<2)))//-1�����ҳ��籣��
			{
				frog->x-=frog->speed;
			}
		}
		if(GetAsyncKeyState('D'))
		{
			if(!((-1==(frog->ch))&&((frog->x)+(frog->speed)>WINDOW_LEN-2)))//-1�����ҳ��籣��
			{frog->x+=frog->speed;}

		}
		if(GetAsyncKeyState(27))
		{frog->esc=1;}

		int key;
		if(_kbhit())//�����̰����¼�ʱ
		{
			key=_getch();
			switch(key)
			{
			case 'w':frog->ch+=1;
				break;
			case 's':
				{
					if((frog->ch)>-1)//�³��籣��
					{
						frog->ch-=1;
					}
					break;
				}
			}
		}
	}
}





void frogOutRange(FrogType *frog,BoardType board[])//���ܳ��磨�����������أ��ж�
{
	int ch=frog->ch;

	if((frog->x)<0||(frog->x)>WINDOW_LEN)//1234������
	{frog->state=DEAD;}


	if((ch>-1)&&(ch<CHANNEL_AMOUNT))//�ںӵ���
	{
		int fall=1;//��ˮ�ж�
		int boardPosi;//ľ�����Ͻ�����
		for(int i=0;i<BOARD_AMOUNT;i++)//��ˮ�ж�
		{
			boardPosi=board[ch].b[i].x;
			if(frog->x>boardPosi&&frog->x<boardPosi+BOARD_LEN)//��ľ����
			{
				fall=0;
				break;
			}
		}
		if(1==fall)
		{
			frog->state=DEAD;

		}//��ˮ������
	}


	if(CHANNEL_AMOUNT==ch)//�ϰ��ж�,�ӵ��������Ǻӵ��±�+1��ʵ���������һ��
	{frog->state=PASSED;}//�ϰ�


}

void excuteFrogFunc(FrogType *frog,int ChannelSpeed[],BoardType board[])//���ܲ����ۺ�
{
	moveFrog(frog,ChannelSpeed);
	frogOutRange(frog,board);
}
void channelSpeedUp(int ChannelSpeed[])//�Ӽ���
{
	static int channel=0;
	if(4==channel){channel=0;}//����

	ChannelSpeed[channel]+=2;//2���ٶ���������
	channel++;
}

void drawFrog(FrogType *frog,ImageType *img)
{
	int x1=frog->x;//���Ͻǣ��ж��ã�����
	int y1=WINDOW_WID-(CHANNEL_WID/2)-(frog->ch+1)*CHANNEL_WID;

	int x2=x1-FROG_LEN/2;
	int y2=y1-FROG_WID/2;

	static double radian;//��ת�õĻ���
	static double var=1;//����,����log10x��x
	static double x=0;//���������ص�sin�����õ�

	static IMAGE f,fm;

	if(frog->state==NORMAL){
	//��Ԫ��դ�����㱳��͸��ɫ
	putimage(x2,y2,&(img->frog0Mask),SRCAND);//����ͱ�����λ��
	putimage(x2,y2,&(img->frog0),SRCPAINT);//ͼ����(����ͱ�����λ��Ľ��)��λ��
	var=1;//��������
	x=0;
	}
	else if(frog->state==DEAD){//��ת
			
		radian=UNIT*(pow(var,2.4));//�����������ϵ��,�õ���ƽ��ͼ��
		var+=0.2;

		rotateimage(&f,&img->frog0,radian,BLACK);//�ڱ���
		rotateimage(&fm,&img->frog0Mask,radian,WHITE);//����ױ���

		putimage(x2,y2,&fm,SRCAND);//����ͱ�����λ��
		putimage(x2,y2,&f,SRCPAINT);//ͼ����(����ͱ�����λ��Ľ��)��λ��
	}
	else if(frog->state==PASSED)//����
	{
		radian=(PI/1.5)*sin(1.5*x);
		x+=PI/30;

		rotateimage(&f,&img->frog0,radian,BLACK);//�ڱ���
		rotateimage(&fm,&img->frog0Mask,radian,WHITE);//����ױ���
		
		putimage(x2,y2,&fm,SRCAND);//����ͱ�����λ��
		putimage(x2,y2,&f,SRCPAINT);//ͼ����(����ͱ�����λ��Ľ��)��λ��
	}

}


void excuteEvent(FrogType *frog,int ChannelSpeed[],ImageType *img)//ִ�й��ػ����õ�EVENT
{
	int state=frog->state;
	switch(state)
	{
	case DEAD:
		{

			static int dTimer=0;//����ʱ��ʾλ��
			if(DEATH_DELAY==dTimer){
				
				resetFrog(frog);
				dTimer=0;
				frog->life-=1;
				frog->score-=10;
				int flag=1;//�Ƿ����
				for(int i=0;i<CHANNEL_AMOUNT;i++)
				{
					if(1==ChannelSpeed[i])
					{
						flag=0;//���ٶ���1�ĺӵ�
						break;
					}
				}
				if(flag)//����
				{
					for(int i=0;i<CHANNEL_AMOUNT;i++)//�������º�������
					{ChannelSpeed[i]-=1;}
				}
			}
			else
			{dTimer++;}
			if(0==frog->life){frog->esc=1;}//����Ϊ0���˳�
			break;//switch case��break
		}
	case PASSED:
		{
			static int pTimer=0;//����ʱ��ʾλ��
			if(PASS_DELAY==pTimer){
		
				pTimer=0;//��ʱ������
				int CSSum=0;
				for(int i=0;i<CHANNEL_AMOUNT;i++)//�����ٶ��ܺ�
				{CSSum+=ChannelSpeed[i];}
				frog->passed+=1;
				frog->coin+=CSSum;
				frog->score+=(CSSum);
				channelSpeedUp(ChannelSpeed);
				resetFrog(frog);
			}
			else
			{pTimer++;}
			break;
		}
	}
}

