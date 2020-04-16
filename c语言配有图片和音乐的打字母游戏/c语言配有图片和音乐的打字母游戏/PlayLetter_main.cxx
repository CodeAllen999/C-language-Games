/***********************************************
//�������ƣ�PlayLetter_main
//����˵��������ĸ������
//�������ߣ��ٶ�:haha1111111113
//�����汾��1.1.4
//���ʱ�䣺2013.4.25
//����޸�ʱ�䣺2013.5.19
//��Ȩ��GPL��׼
//���뻷����VS2008 , EasyX_v20130610(beta)
***********************************************/

#include "Cla_PlayLetter.h"//��PlayLetter���Ŀ��ļ�
#include <easyx.h>//EasyXͼ�ο�( �汾:EasyX_v20130610(beta) )
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#pragma comment(lib,"winmm.lib")

#define LetterNumber 8
int GameStatus = 1;
int SPEED = 70;
#define SLOW_S 1
#define QUICK_S 2
void RunGame(Cla_PlayLetter *PL);
void WelcomeGame();

void main()
{
	Cla_PLGLSMC PL_Msg[LetterNumber];
	srand(time(0)); 
	for(int i=0;i<LetterNumber;i++)//���Letter������Ϣ
	{
		bool chose = true;
		while(chose)
		{
			chose = false;
			PL_Msg[i].ActionSpaceBegin_x_coo = 0;
			PL_Msg[i].ActionSpaceBegin_y_coo = -400;
			PL_Msg[i].ActionSpaceEnd_x_coo = 640;
			PL_Msg[i].ActionSpaceEnd_y_coo = 480;
			PL_Msg[i].LivingThings_x_coo = rand() % 600 + 10; 
			PL_Msg[i].LivingThings_y_coo = rand() % 401 - 400;
			PL_Msg[i].LivingThings_y_coo_increment = rand() % 2 + 2;
			PL_Msg[i].letter = rand() % 26 + 'A'; 
			PL_Msg[i].LetterSize = 36;
			for(int j=0;j<i;j++)//��������ظ�λ�ú���ĸ
				if(PL_Msg[i].letter == PL_Msg[j].letter ||
				   PL_Msg[i].LivingThings_x_coo == PL_Msg[j].LivingThings_x_coo)
				{
					chose = true;
					break;
				}
		}
	}
	Cla_PlayLetter PL[LetterNumber] = { 
										Cla_PlayLetter(PL_Msg[0]),
										Cla_PlayLetter(PL_Msg[1]),
										Cla_PlayLetter(PL_Msg[2]),
										Cla_PlayLetter(PL_Msg[3]),
										Cla_PlayLetter(PL_Msg[4]),
										Cla_PlayLetter(PL_Msg[5]),
										Cla_PlayLetter(PL_Msg[6]),
										Cla_PlayLetter(PL_Msg[7]),
									  };//����Letter��Ϣ�������

	initgraph(640,540);//EasyX��������

	WelcomeGame();//��ӭ����
	RunGame(PL);//������Ϸ

	closegraph();//EasyX�رմ���

}

void RunGame(Cla_PlayLetter *PL)
{		
	int SuccessNumber = 0;
	TCHAR TxtSN[1];//����EasyX���
	int UnsuccessNumber = 0;
	TCHAR TxtUN[1];//����EasyX���
	int TotalNumber = 0;
	TCHAR TxtTN[1];//����EasyX���
	char TN_note[] = "��������ĸ:";
	char SN_note[] = "�ɹ�:";
	char UN_note[] = "ʧ��:";
	Stru_PLSLF plslf;
	Cla_PLGLSMC APLMsg;
	int GetKey;
	setbkmode(TRANSPARENT);
	IMAGE RG_BK;	
	loadimage(&RG_BK,_T("res\\image\\RunGame_BK.jpg"),640,540,true);
	IMAGE Carota,Carota_Zhao;
	loadimage(&Carota,_T("res\\image\\Carota.jpg"),28,59,true);
	loadimage(&Carota_Zhao,_T("res\\image\\Carota_Zhao.jpg"),28,59,true);
	mciSendString(_T("play res\\music\\RunGame_SlowStatus.mp3 repeat"), NULL, 0, NULL);
	
	while(true)
	{
		
		putimage(0,0,&RG_BK);
		line(0,480,640,480);
		settextcolor(BLACK);
		settextstyle(22, 0,_T("�����п�"));
		outtextxy( 40,500,_T("�汾:1.0.0"));
		outtextxy(300,500,_T("haha��Ʒ")); 
		outtextxy(530,500,_T("ʧ��:")); 
		outtextxy(580,500,TxtUN);
		settextcolor(YELLOW);
		settextstyle(18, 0,_T(""));
		
		for(int i=0;i<LetterNumber;i++)
		{
			PL[i].LivingThingsAction();
			plslf = PL[i].SendLetterFeature();
			BeginBatchDraw();//����ͼ��ʼ,ΪʲôҪ������ͼ����Ϊ�˷�ֹ��ҫ
			if(plslf.life == true)
			{
				
				putimage(plslf.now_x_coo - 11,plslf.now_y_coo - 28,&Carota_Zhao,SRCPAINT);
				putimage(plslf.now_x_coo - 11,plslf.now_y_coo - 28,&Carota,SRCAND);
				outtextxy(plslf.now_x_coo,plslf.now_y_coo,plslf.letter);
			}
			
			if(plslf.now_x_coo >= 640|| plslf.now_y_coo >= 480)
			{
				int chose = 1;
				while(chose)
				{
					chose = 0;
					APLMsg.ActionSpaceBegin_x_coo = 0;
					APLMsg.ActionSpaceBegin_y_coo = 0;
					APLMsg.ActionSpaceEnd_x_coo = 640;
					APLMsg.ActionSpaceEnd_y_coo = 480;
					APLMsg.LivingThings_x_coo = rand() % 600 + 10;
					APLMsg.LivingThings_y_coo_increment = rand() % 2 + 2;
					if(GameStatus == QUICK_S) 
							APLMsg.LivingThings_y_coo_increment += 2;
					APLMsg.letter = rand() % 26 + 'A';
					APLMsg.LetterSize = 36;
					for(int j=0;j<LetterNumber;j++)//��������ظ�λ�ú���ĸ
					{
						Stru_PLSLF Record= PL[j].SendLetterFeature();
						if(APLMsg.letter == Record.letter ||
							APLMsg.LivingThings_x_coo == Record.now_x_coo)
						{
							chose = 1;
							break;
						}
					}
				}
				PL[i].AgainGaveFeature(APLMsg);
			}
		}
		FlushBatchDraw();//����ͼ�����ʹ������ͼ��������ϸ������ο�EasyX����
		if(_kbhit()==1)
		{
			GetKey = _getch();
			if(GetKey == 27) break;
			if(GetKey == '0')
			{
				static bool status = true;
				switch(GameStatus)
				{
					case SLOW_S:
						if(status == true)
						{
							mciSendString(_T("pause res\\music\\RunGame_SlowStatus.mp3"), NULL, 0, NULL);
							status = false;
						}
						else
						{
							mciSendString(_T("resume res\\music\\RunGame_SlowStatus.mp3"), NULL, 0, NULL);
							status = true;
						}
						break;
					case QUICK_S:
						if(status == true)
						{
							mciSendString(_T("pause res\\music\\RunGame_QuickStatus.mp3"), NULL, 0, NULL); 
							status = false;
						}
						else
						{
							mciSendString(_T("resume res\\music\\RunGame_QuickStatus.mp3"), NULL, 0, NULL); 
							status = true;
						}
						break;
				}
			}
			if(GetKey == '1')
			{
				if(GameStatus != SLOW_S)
				{
					GameStatus = SLOW_S;
					mciSendString(_T("close res\\music\\RunGame_QuickStatus.mp3"), NULL, 0, NULL);
					mciSendString(_T("play res\\music\\RunGame_SlowStatus.mp3 repeat"), NULL, 0, NULL);
					for(int i=0;i<8;i++)
					{
						PL[i].sqecial(-2);
					} 
						
				}
			}
			if(GetKey == '2')
			{
				if(GameStatus != QUICK_S)
				{
					GameStatus = QUICK_S;
					mciSendString(_T("close res\\music\\RunGame_SlowStatus.mp3"), NULL, 0, NULL);
					mciSendString(_T("play res\\music\\RunGame_QuickStatus.mp3 repeat"), NULL, 0, NULL);
					for(int i=0;i<8;i++)
					{
						PL[i].sqecial(2);
					}
				}			
			}			
			if(GetKey >= 'a' && GetKey <= 'z') GetKey -= 32;
			for(int i=0;i<LetterNumber;i++)
			{
				plslf = PL[i].SendLetterFeature();
				if(GetKey == plslf.letter)
				{
					PL[i].LivingThingsAccident();
					++SuccessNumber;
				}
			}
		}

		TotalNumber = plslf.CreateLifeTotalNumber;
		UnsuccessNumber = 0;
		for(int j=0;j<LetterNumber;j++)
		{
			plslf = PL[j].SendLetterFeature();
			UnsuccessNumber += plslf.NaturalDeath;	
		}
		if(UnsuccessNumber < 0) UnsuccessNumber = 0;
		_stprintf(TxtSN, _T("%d"), SuccessNumber);
		_stprintf(TxtTN, _T("%d"), TotalNumber);
		_stprintf(TxtUN, _T("%d"), UnsuccessNumber);
		
		
		Sleep(33);	

	}
}

void WelcomeGame()
{
	mciSendString(_T("play res\\music\\WelcomeGame_BK.mp3 repeat"), NULL, 0, NULL); 
	MOUSEMSG mousemsg;
	IMAGE start_bg;
	loadimage(&start_bg,_T("res\\image\\WelcomeGame_BK.jpg"));
	putimage(0,0,&start_bg);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(72, 0,_T("�����п�"));
	outtextxy(200, 200,_T("����ĸ"));
	settextstyle(36, 0,_T("�����п�"));
	outtextxy(100, 360,_T("״̬ѡ�񰴼���Esc,0,1,2"));
	outtextxy(100, 410,_T("����:"));
	outtextxy(200, 410,_T("haha1111111113"));
	while(true)
	{
		if(_kbhit()==1)
		{
			mciSendString(_T("close res\\music\\WelcomeGame_BK.mp3"), NULL, 0, NULL); 
			break;
		}
		mousemsg=GetMouseMsg();
		if(mousemsg.uMsg == WM_LBUTTONDOWN)
		{
			mciSendString(_T("close res\\music\\WelcomeGame_BK.mp3"), NULL, 0, NULL); 
			break;
		}
	}
}
