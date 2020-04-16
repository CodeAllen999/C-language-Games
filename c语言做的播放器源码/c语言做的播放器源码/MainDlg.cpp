#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>		//�õ���time����������Ҫ�����ͷ�ļ�
#include <commdlg.h>
#include <mmsystem.h>  // mciSengString����������Ҫ�ȵ���#include <mmsystem.h>
#include <commctrl.h>  // TBM_SETPOSͷ�ļ�
#include "resource.h"
#include "MainDlg.h"
#include <shellapi.h>//�й�ϵͳ���̵�ͷ�ļ�
#define WM_HIDE WM_USER+100  
							//�����Լ�����ϢID��
							//Ϊ�˷�ֹ�û��������ϢID��ϵͳ����ϢID��ͻ
							//MS��Microsoft��������һ����WM_USER��С��WM_USER��ID��ϵͳʹ�ã�����WM_USER��ID���û�ʹ�á� 

/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

#define ORDER 0  //˳�򲥷�
#define SINGLELOOP 1  //����ѭ��
#define LISTLOOP 2  //�б�ѭ��
#define RANDOM 3  //�������

void Main_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos); //�������麯��

// ȫ�ֱ�������
TCHAR szFileNamePath[256][MAX_PATH];  //��������ȫ·������ά����     Path��·����
TCHAR szFileName[256][MAX_PATH];  // ������
TCHAR shortName[256]; //�����Ķ�·����
int num;   //���ڲ��Ÿ��������
int offset = 0;    //�򿪸���ʱ��¼�����ı�ţ�Ϊ�˶�δ�ʱ�����������������Ϊȫ�ֱ���
int count = 0;  //Ϊ�б��еĸ���������
int playStatus = 1;  //   ��ǰ��������״̬��1 ��ʾ���ڲ���״̬��0 ��ʾ��ͣ״̬
int minite;  // ��Ŀ����ʱ�䣬��
int second;  // ��Ŀ����ʱ�䣬��
long allLength;											//����ʲô��
long curLength;	//	   curLength = atoi(curTime);		//���ǵ�ǰʱ����ַ���ת��ΪINT��
TCHAR strTime[256] = "";  // ��Ŀ���ŵ�ǰʱ��
TCHAR strTimeAll[256] = "";  // ��Ŀ��ʱ��
TCHAR curTime[256] = "";								// ����ʲô��
int mode = ORDER;										// ����ʲô��
int n;													// ����ʲô��

// ����ԭ��
void addFiles(HWND hwnd);  // ��Ӹ���
void playMusic(HWND hwnd);  // ���Ÿ���
void pauseMusic(HWND hwnd);  // ��ͣ����
void stopPlay(HWND hwnd);  // ֹͣ���ŵ�ǰ���ڲ��ŵĸ���
void playLast(HWND hwnd);  // ������һ��
void playNext(HWND hwnd);  // ������һ��
void autoNext(HWND hwnd);  //�Զ�������һ��
void silence(HWND hwnd);  // ����
void getAllTime(HWND hwnd);  //  �õ�������ʱ��
void deleteAll(HWND hwnd);  // �Ƴ�������Ŀ
void deleteSel(HWND hwnd);  // �Ƴ�ѡ����Ŀ
void getSongMessage(HWND hwnd);							// ��ȡ��Ŀ��ϸ��Ϣ����

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////*******    �˺�����Ҫ���ڳ�ʼ���Ի����ж���TimerProc�������磺SetTimer(hwnd,1,1000,TimerProc);   *************//////

VOID CALLBACK TimerProc (HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime) //IDC_EDITSYST�༭��������ʾϵͳʱ��
{
	SYSTEMTIME stLocal;   //ϵͳ��ǰʱ��
	TCHAR time[256];     //����time������������Ҫ��IDC_EDITSYST�༭������ʾ������
	GetLocalTime(&stLocal);//�õ�ϵͳ��ǰʱ���ָ��
	wsprintf(time,"%d��%d��%d��  %d:%d:%d",stLocal.wYear,stLocal.wMonth,stLocal.wDay
		,stLocal.wHour,stLocal.wMinute,stLocal.wSecond);//�����������ݿ�����time������

	SetDlgItemText(hwnd,IDC_EDITSYST,time);//��time�������ݴ�ӡ��IDC_EDITSYST�༭����
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////              �˺�����Ҫ���ڳ�ʼ���Ի����ж���curTimePro�������磺SetTimer(hwnd, 0, 1000, curTimePro);      ///////


 
void CALLBACK curTimePro(HWND hwnd, UINT message, UINT iTemerID, DWORD dwTime)// �ص���������ȡ��ǰ����ʱ��,���û������ĵ�ǰֵ
{
	TCHAR str[256];
	wsprintf(str, "status %s position", shortName);
	//int wsprintf( ����LPTSTR lpOut, ��������������Ϊ1024�ֽ� ����LPCTSTR lpFmt,  ��ʽ�ַ��� ����... ������Ĳ���;��
	mciSendString(str, curTime, sizeof(curTime)/sizeof(TCHAR), NULL);//mciSendString(��play ***��,"",0,NULL);
	curLength = atoi(curTime);
	minite = curLength / 60000;//����ʱ����  ���֡�������
	second = (curLength / 1000) % 60;//����ʱ����  ���롱������
	wsprintf(strTime, "%.2d:%.2d", minite, second);// ��Ŀ���ŵ�ǰʱ�� ��ȷ��
	SetDlgItemText(hwnd, IDC_EDITTIME, strTime);//����ǰ����ʱ���ӡ��IDC_EDITTIME��


	// ���û�������ֵ����Сֵ�Լ���ʱλ��
	HWND hwSlider = GetDlgItem(hwnd, IDC_SLIDER);//IDC_SLIDER�ľ������ΪhwSlider
	SendMessage(hwSlider, TBM_SETRANGEMAX, (WPARAM)TRUE, allLength);//TBM_SETRANGEMAX�����û����߼�λ�õ����ֵ�����Ƿ��ػ�
	SendMessage(hwSlider, TBM_SETRANGEMIN, (WPARAM)TRUE, 0);//TBM_SETRANGEMIN�����û����߼�λ�õ���Сֵ�����Ƿ��ػ�
	SendMessage(hwSlider, TBM_SETPOS, (WPARAM)TRUE, curLength);//TBM_SETPOS�����û�����߼�λ�ã����Ƿ��ػ�


	TCHAR szCommand[MAX_PATH+10];
	TCHAR szReturn[MAX_PATH];
	ZeroMemory(szCommand, sizeof(szCommand)/sizeof(TCHAR));
	//C����������һ���ṹ�����֮����ʹ���������֮ǰҪ������memset���Ѹ���λ���㡣ʹ��C�������õĺ���memset����ɣ�
	//memset(&s1,sizeof(s1),0);
	//����������ʹ��ZeroMemory����������ZeroMemory��ʵ�����Ǻ�������ʵ��memset�ĺ궨��
	//ZeroMemory��ʵ����memset��ֽ�ϻ����ѣ�����һ��ȫ�µĺ�����


	wsprintf(szCommand, TEXT("status %s mode"), shortName);
	mciSendString(szCommand, szReturn, sizeof(szReturn)/sizeof(TCHAR), NULL);

//***********************************����ĺ������ܻ��IDC_STOP���������ͻ������***************************************//
	//strcmp�ٶȿ쵫�Ǵ����;lstrcmp�ٶ�����������ʵҲ������ôһ������������   �Ƽ�ʹ��lstrcmp
	//lstrcmp�ַ����Աȣ�����京���ǣ���szReturn==stoppedʱ�Զ�������һ��
	if (0 == lstrcmp(szReturn, TEXT("stopped")))
	{											
		autoNext(hwnd);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////              �˺�����Ҫ���ڳ�ʼ���Ի����ж���TimerProc1�������磺SetTimer(hwnd,2,1000,TimerProc1);         ///////

VOID CALLBACK TimerProc1(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime) //IDC_EDITSYST�༭��������ʾϵͳʱ��
{
	SYSTEMTIME stLocal;   //ϵͳ��ǰʱ��
	GetLocalTime(&stLocal);//�õ�ϵͳ��ǰʱ���ָ��
	TCHAR STR1[256],STR2[256];
	int hour,minute;
	GetDlgItemText(hwnd,IDC_EDIT1,STR1,sizeof(STR1));
	GetDlgItemText(hwnd,IDC_EDIT2,STR2,sizeof(STR2));
	hour = atoi(STR1);
	minute = atoi(STR2);
	if(hour == stLocal.wHour&&minute == stLocal.wMinute)
	{
		HWND hwList = GetDlgItem(hwnd,IDC_LIST1);
		TCHAR str1[256],str2[256];
		ListBox_GetText(hwList,0,str1);
		wsprintf(str2,"play %s",str1);
		mciSendString(str2,"",0,NULL);
	}

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////*****************************************���»���ϵͳ��������*************************************************////
/*     ypedef struct _NOTIFYICONDATAA {
        DWORD cbSize;                    //�ṹ��Ĵ�С�����ֽ�Ϊ��λ��
        HWND hWnd;						//���ڵľ������ʾ�Ĵ�����������������ͼ����ص���Ϣ��
        UINT uID;						//Ӧ�ó������������ͼ��ı�ʶ����
        UINT uFlags;					//�˳�Ա����������Щ������ԱΪ�Ϸ����ݣ�����Щ��Ա�����ã���
										//�˳�Ա����Ϊ����ֵ����ϣ� 
										//  NIF_ICON ����hIcon��Ա�����á� ��
										//��NIF_MESSAGE ��uCallbackMessage��Ա�����á� ��
										//��NIF_TIP ����  szTip��Ա�����á� ��
										//��NIF_STATE ����dwState��dwStateMask��Ա�����á� 
										//��NIF_INFO ���� ʹ��������ʾ������ͨ�Ĺ�����ʾ��szInfo, uTimeout, szInfoTitle��dwInfoFlags��Ա�����á� ��
										//��NIF_GUID ���� ������ 

        UINT uCallbackMessage;			//Ӧ�ó��������Ϣ��ʾ��������ͼ������������¼�����ʹ�ü���ѡ��򼤻�ͼ��ʱ��
										//ϵͳ��ʹ�ô˱�ʾ����hWnd��Ա��ʾ�Ĵ��ڷ�����Ϣ��
										//��Ϣ��Ӧ������wParam������ʾ����Ϣ�¼�������������ͼ�꣬lParam���������¼��Ĳ�ͬ��
										//������������̵ľ�����Ϣ�����統���ָ���ƹ�����ͼ��ʱ��lParam��ΪWM_MOUSEMOVE��
        HICON hIcon;					//���ӡ��޸Ļ�ɾ����ͼ��ľ����
        CHAR   szTip[64];				//ָ��һ����\0�������ַ�����ָ�롣�ַ���������Ϊ��׼������ʾ����Ϣ��
										//��������\0�ַ���szTip��ຬ��64���ַ��� 
} NOTIFYICONDATAA                         */
			
//*****************�����˽������NOTIFYICONDATA�ṹ��ĳ�Ա*****************//

void Minimized(HWND hwnd,int flag)
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = 1;
	nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
	nid.uCallbackMessage = WM_HIDE;				//�Զ�����Ϣ
	HINSTANCE hin = (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE);//��ó�����������
	nid.hIcon = LoadIcon(hin,MAKEINTRESOURCE(1));   //����һ��MAKEINTRESOURCE(1)��ͼ������MAKEINTRESOURCE(1)����Ӧ�ó���ͼ��
	lstrcpy(nid.szTip,TEXT("˫���ָ�����"));             //��С�������̣�����Ƶ�����������ʾ����Ϣ��ʾ����
	switch(flag)
	{
	case 0:
		{//�������ͼ�꣬���ش���
			Shell_NotifyIcon(NIM_ADD,&nid);
//BOOL Shell_NotifyIcon( DWORD dwMessage,PNOTIFYICONDATA lpdata);
//dwMessageΪ������������ݷ��͵���Ϣ������Ҫִ�еĲ�������ѡ��ֵ���£�
//NIM_ADD �������������һ��ͼ�ꡣ
//NIM_DELETE ɾ�����������һ��ͼ�ꡣ
//NIM_MODIFY  �޸����������һ��ͼ�ꡣ
//NIM_SETFOCUS ���ý��㡣���統�û���������ͼ�굯���˵������а���ESC�����˵������󣬳���Ӧ��ʹ�ô���Ϣ�����������õ�����ͼ���ϡ� 
//lpdata Ϊ�����������ָ��NOTIFYICONDATA�ṹ���ָ�룬�ṹ������������ϵ�һ������wMessage����ͼ�������
			ShowWindow(hwnd,SW_HIDE);//���ش���
		}
		break;
	case 1:
		{//ɾ������ͼ��
			ShowWindow(hwnd,SW_SHOWNORMAL);
			Shell_NotifyIcon(NIM_DELETE,&nid);
			SetForegroundWindow(hwnd);				//Foreground ǰ̨
//����ԭ�ͣ�BOOL SetForegroundWindow��HWND hWnd��
//�ú���������ָ�����ڵ��߳����õ�ǰ̨�����Ҽ���ô��ڡ�
//��������ת��ô��ڣ���Ϊ�û��ĸ��ֿ��ӵļǺš�ϵͳ������ǰ̨���ڵ��̷߳����Ȩ���Ը��������̡߳� 
		}
		break;
	default:
		break;
	}	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////***************************Main_Proc  �Ի������Ϣ������****************************************************////

BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {	
		//BEGIN MESSAGE CRACK
		HANDLE_MSG(hWnd,WM_HSCROLL, Main_OnHScroll);  // Slider������Ϣ
        HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);//��ʼ������Ϣ
        HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);//�����ؼ��ǵ���Ϣ
		HANDLE_MSG(hWnd,WM_CLOSE, Main_OnClose);//�رնԻ������Ϣ
		//END MESSAGE CRACK
		case WM_HIDE:						//#define WM_HIDE WM_USER+100 
		{
			if(lParam==WM_LBUTTONDBLCLK)//��ʾ���˫���¼�
			{
				Minimized(hWnd,1);			//Minimized��������Ҫ��Main_Proc����֮ǰ����
			}
			else if(lParam==WM_RBUTTONDOWN)//��ʾ�Ҽ������¼�
			{
				Minimized(hWnd,1);
			}

		}
		break;
		case WM_SIZE:
			{	
				if(SIZE_MINIMIZED==wParam)//�����С�� ������
				{
					Minimized(hWnd,0);
				}
			}

		}
    return FALSE;
}


//////////**********************************************************************************************************////
////////                                  �Ի���ĳ�ʼ����������												///////
 

BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{

	SetTimer(hwnd,1,1000,TimerProc);//SetTimer(HWND hWnd ,UINT nIDEvent,UINT uElapse,TIMERPROC lpTimerFunc)����
									//HWND hWnd���ھ�� ��
									//UINT nIDEvent ��ʱ��ID�������ʱ��ʱ������ͨ����ID�ж����ĸ���ʱ�� 
									//UINT uElapseʱ����,��λΪ���� ��
									//TIMERPROC lpTimerFunc  �ص����� ��
	SetTimer(hwnd, 0, 1000, curTimePro);
	SetTimer(hwnd,2,1000,TimerProc1);//����
// ��SetTimer����Ļص��������������Main_OnInitDialog֮ǰ������������


	// ��ʼ��ʱ�䣬����ʱ�����Ŀ��ʱ�䶼Ϊ��
	strcpy(strTime, "00:00");
	strcpy(strTimeAll, "00:00");
	SetDlgItemText(hwnd, IDC_EDITTIME, strTime);
	SetDlgItemText(hwnd, IDC_EDITTIMEALL, strTimeAll);

	// ��ʼ������
	HWND hwSliderVolume = GetDlgItem(hwnd, IDC_SLIDERVOLUME);
	SendMessage(hwSliderVolume, TBM_SETRANGEMAX, (WPARAM)TRUE, 1000);  // �������Ϊ100
	SendMessage(hwSliderVolume, TBM_SETRANGEMIN, (WPARAM)TRUE, 0);  // ��СֵΪ0
	SendMessage(hwSliderVolume, TBM_SETPOS, (WPARAM)TRUE, 500);   // ��ʼ��Ϊ����50

	//ѭ��ģʽ
	HWND hwCombo1 = GetDlgItem(hwnd, IDC_COMBO1);
	ComboBox_InsertString(hwCombo1, -1, TEXT("˳�򲥷�"));//indexΪ-1ʱָ����˳�򲥷Ų��뵽�б�ĩβ 
	ComboBox_InsertString(hwCombo1, -1, TEXT("����ѭ��"));//indexΪ-1ʱָ��������ѭ�����뵽�б�ĩβ
	ComboBox_InsertString(hwCombo1, -1, TEXT("�б�ѭ��"));//indexΪ-1ʱָ�����б�ѭ�����뵽�б�ĩβ
	ComboBox_InsertString(hwCombo1, -1, TEXT("�������"));//indexΪ-1ʱָ����������Ų��뵽�б�ĩβ
	ComboBox_SetCurSel(hwCombo1, 0);  //Ĭ��ѡ��˳�򲥷�ģʽ
	SetDlgItemText(hwnd,IDC_STATUS,TEXT("Ready!......"));  //��ʼ������״̬ΪREADY

    return TRUE;
}



//*******************************  Main_OnCommand  ����Ի���ؼ���Ϣ�ĺ���********************************//

void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch(id)
    {	
		// ����ļ����б�
		case ID_MENUITEMADD:
        case IDC_ADD:
		{
			addFiles(hwnd);  
			HWND hwList = GetDlgItem(hwnd, IDC_LIST);
			ListBox_SetCurSel(hwList, 0);
			
		}
        break;

		// ����ѡ�еĸ���
		case ID_MENUITEMPLAY:
		case IDC_PLAY:
		{
			playMusic(hwnd);  
			SetDlgItemText(hwnd,IDC_STATUS,TEXT("playing!......."));

		}
		break;

		// ��ͣѡ�еĸ���
		case ID_MENUITEMPAUSE:
		case IDC_PAUSE:
		{
			pauseMusic(hwnd);  
			
		}
		break;

		// ֹͣ���ڲ��ŵ�����
		case ID_MENUITEMSTOP:
		case IDC_STOP:
		{
			stopPlay(hwnd);  
			SetDlgItemText(hwnd,IDC_STATUS,TEXT("stopping!........"));
		}
		break;

		//�б��IDC_LIST����Ϣ����
		case IDC_LIST:
		{
			switch(codeNotify)
			{

			// ����˫��ѡ�еĸ���
			case LBN_DBLCLK:  //˫��ѡ���� 
				{
					playMusic(hwnd);  
					SetDlgItemText(hwnd,IDC_STATUS,TEXT("playing!......."));
				}
				break;
			}
		}
		break;

		// ������һ��
		case ID_MENUITEMLAST:
		case IDC_LAST:
		{
			playLast(hwnd);   
			SetDlgItemText(hwnd,IDC_STATUS,TEXT("playing!......."));
		}
		break;

		// ������һ��
		case ID_MENUITEMNEXT:
		case IDC_NEXT:
		{
			playNext(hwnd);  
			SetDlgItemText(hwnd,IDC_STATUS,TEXT("playing!......."));
		}
		break;

		// ������ָ�
		case IDC_CHECK:
		{
			silence(hwnd);  
		}
		break;

		// ɾ���б���������Ŀ
		case ID_MENUITEMCLEAN:		
		case IDC_DELETEALL:
		{
			deleteAll(hwnd);  
			SetDlgItemText(hwnd,IDC_STATUS,TEXT("Ready!......")); 
		}
		break;

		//ɾ���б��еĵ�����Ŀ
		case ID_MENUITEMDEL:
		case IDC_DELETESEL:
		{
			deleteSel(hwnd);
			SetDlgItemText(hwnd,IDC_STATUS,TEXT("Ready!......")); 
		}
		break;

		//��ʾ������
		case ID_MENUITEMSLEEP:
        case IDC_SLEEP:
		{
			SendMessage(hwnd,WM_SYSCOMMAND,SC_MONITORPOWER,2);
		}
        break;

		//����
		case ID_MENUITEMABOUT:
		{
			MessageBox(hwnd,TEXT("���һ��ѧϰ̽��!QQ:983572133������ʱ˵��������������"),TEXT("����"),MB_OK);
		}
		break;

		//�˳�
		case ID_MENUITEMEXIT:
		{
			int i=MessageBox(hwnd,TEXT("ȷ���˳���"),TEXT("ѯ��"),MB_YESNO|MB_ICONQUESTION);
			if(i==6)
			{
				Main_OnClose(hwnd);
			}
		}
		
		//�������
		case IDC_BUTTON1:
		{
		HWND hwList = GetDlgItem(hwnd, IDC_LIST1);
		TCHAR szFile[256*MAX_PATH] = "";  
		TCHAR szPath[256] = "";  
		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(ofn));  
		ofn.lStructSize = sizeof(ofn);  
		ofn.hwndOwner = hwnd;  
		ofn.lpstrFilter = "�����ļ�(mp3��wma��wav)\0*.wma;*.mp3;*.wav\0�����ļ�(*.*)\0*.*\0";
		ofn.lpstrCustomFilter = NULL;
		ofn.nFilterIndex = 1;  
		ofn.lpstrFile = szFile;  
		ofn.nMaxFile = sizeof(szFile) / sizeof(TCHAR);  
		ofn.lpstrFile[0] = TEXT('\0');	
		ofn.lpstrTitle = TEXT("�������");  
		ofn.nMaxFileTitle = NULL;  
		ofn.Flags = OFN_HIDEREADONLY   |   OFN_FILEMUSTEXIST   |   OFN_PATHMUSTEXIST   |   OFN_EXPLORER ;
		ofn.lpstrDefExt = "*.mp3";
		if (GetOpenFileName(&ofn))
			{	
			TCHAR getShort[MAX_PATH];
			GetShortPathName(szFile, getShort, sizeof(getShort));	
			HWND hwList = GetDlgItem(hwnd, IDC_LIST1);
			ListBox_InsertString(hwList, 0 ,getShort);
			}
		}
		break;

		//�ػ�
		case ID_MENUITEMOFF:
		case IDC_BUTTONOFF:
		{
			system("shutdown -s -t 0");
		}
		break;

		//����˵��
		case ID_MENUITEMCLOCK:
		{
			MessageBox(hwnd,TEXT("����ʱ���ʽΪ Сʱ:���� "),TEXT("����˵��"),MB_OK);
		}

        default:
		break;
    }
}

//******************************************���������Ķ���************************************************************//
////**************************************************************************************************************//////

//******************************************* ��Ӹ��� ************************************************//
void addFiles(HWND hwnd)
{
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);  // �õ�ListBox���

	TCHAR szFile[256*MAX_PATH] = "";  // �ļ������֣�*MaxPath�ܽ����Ӷ��ļ�ʱ���ֵ�����
	TCHAR szPath[256] = "";  // ������·��
	TCHAR *p;  // ָ�����������
	// int i;  // ���ڼ���

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));  // ����(memset�����ĺ궨��)
	ofn.lStructSize = sizeof(ofn);  // lStructSizeָ������ṹ�Ĵ�С�����ֽ�Ϊ��λ��
	ofn.hwndOwner = hwnd;  // ָ�������߶Ի��򴰿ڵľ���������Ա������������Ч���ھ����������Ի���û��������������ΪNULL��
	ofn.lpstrFilter = "�����ļ�(mp3��wma��wav)\0*.wma;*.mp3;*.wav\0�����ļ�(*.*)\0*.*\0";
	ofn.lpstrCustomFilter = NULL;//ָ��һ����̬���壬��������һ���Կ��ַ������Ĺ������ַ���������ַ�����Ϊ�˱����û�ѡ��Ĺ�����ʽ��
								 //��������Ա��NULL���Ի����ܱ����û��Զ����������ʽ��
								 //��������Ա����NULL��nMaxCustFilter��Ա��ֵ����ָ����TCHARsΪ��λ��lpstrCustomFilter����Ĵ�С��

	ofn.nFilterIndex = 1;  // ָ�����ļ����Ϳؼ��е�ǰѡ��Ĺ������������������ļ�(mp3��wma��wav)  ��1��ʼ����
	ofn.lpstrFile = szFile;  // lpstrFileָ�������ʼ���ļ����༭�ؼ�ʹ�õ��ļ����Ļ��塣
	ofn.nMaxFile = sizeof(szFile) / sizeof(TCHAR);  // ָ��lpstrFile����Ĵ�С����TCHARsΪ��λ��

	ofn.lpstrFile[0] = TEXT('\0');	//��֪����ʲô��

	ofn.lpstrTitle = TEXT("�������");  // ָ�����ѡ����ļ����ļ�������չ���Ļ��壨����·����Ϣ���������Ա������NULL��
	ofn.nMaxFileTitle = NULL;  // ָ��lpstrFileTitle����Ĵ�С����TCHARsΪ��λ��

	ofn.Flags = OFN_HIDEREADONLY   |   OFN_FILEMUSTEXIST   |   OFN_PATHMUSTEXIST   |   OFN_EXPLORER  |  OFN_ALLOWMULTISELECT;
//OFN_ALLOWMULTISELECT ָ���ļ����б�������ѡ
//OFN_EXPLORER ָ���κδ򿪻����Ϊ�Ի���ʹ���µ�Explorer�����û���ģ�顣
//OFN_HIDEREADONLY ����ֻ����ѡ��
//OFN_FILEMUSTEXIST ָ���û����������ļ�����¼�ֶ��������Ѵ��ڵ��ļ������֡�
//OFN_PATHMUSTEXIST ָ���û����������·�����ļ�����

	ofn.lpstrDefExt = "*.mp3";
//ָ�����Ĭ����չ���Ļ��塣����û�����������չ����GetOpenFileName��GetSaveFileName���������չ�����ļ����С�
//����ַ�����������һ���ȣ�����ֻ��ͷ�����ַ������ӡ��ַ�����Ӧ�ð���һ����㣨.����
//��������Ա��NULL�����û�����������һ����չ������ô��û����չ�������ӡ�

	if (GetOpenFileName(&ofn))//����򿪵��ļ���TRUE����.....
	{
		int nLength = 0;  // �ļ�·�����ַ�����

		lstrcpyn(szPath, szFile, ofn.nFileOffset);// �ѵ�һ���ļ���ǰ��·�����Ƶ�szPath
												  //lstrcpyn   - �����ַ���, ͬʱָ��Ҫ���Ƶĳ���
												  //nFileOffsetָ��һ���ļ���ǰ��·��
//nFileOffset:
//ָ����·����ʼ��ͨ��lpstrFileָ�����ļ����ַ�������0��ƫ�ƣ���TCHARsΪ��λ��
//����ANSI�汾�����ֽڵĸ���������Unicode�汾�����ַ��ĸ�����
//���磬���lpstrFileָ�����е��ַ�������c:\dir1\dir2\file.ext���������Ա����ָ����file.ext���ַ���ƫ�Ƶ�λ��ֵ13�� 

		szPath[ofn.nFileOffset] = '\0';  //(���Ͻ������)ȡ���ļ�·��
		nLength = lstrlen(szPath);

//???????????????????????????????????????????�����?????????????????????????????????????????????????????????//
		if (szPath[nLength-1] != '\\')  // ���ѡ���˶���ļ����������'\\'									//
		{																									//
			lstrcat(szPath, TEXT("\\"));																	//
		}																									//
//??????????????????????????????????????????????????????????????????????????????????????????????????????????//

		p = szFile + ofn.nFileOffset;  //��ָ���Ƶ���һ���ļ����ļ���
		while (*p)
		{
			lstrcpy(szFileNamePath[offset], szPath);  // ��·�����Ƹ�szFileNamePath[offset]
			lstrcat(szFileNamePath[offset], p);  // �����ļ���

			SendMessage(hwList, LB_ADDSTRING, 0, (LPARAM)p);	//���б������ļ�����(LPARAM)p���ļ���ָ��

			lstrcat(szFileName[offset], p);      //�ļ������Ƹ�szfilename,������ʾ��ʾ���ڲ��ŵ��ļ��� 

//??????????????????????????????????????�����??????????????????????????????????//
			p += lstrlen(p) +1;   //������һ���ļ�								//
//??????????????????????????????????????????????????????????????????????????????//
			offset++;
		}
	}
}

//******************************************* ���Ÿ��� *******************************************//
void playMusic(HWND hwnd)
{
	stopPlay(hwnd);  // ֹͣ���ڲ��ŵĸ���
	TCHAR str1[256] = "";
	TCHAR str2[256] = "";
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);  // �õ�ListBox���
	int index = ListBox_GetCurSel(hwList);
	ListBox_GetText(hwList, index, str1);  // �õ�������

	int count;
	for (count = 0; count < offset; count++)
	{
		if (0 == strcmp(str1, szFileName[count]))
		{
			GetShortPathName(szFileNamePath[count], shortName, sizeof(shortName));  // ��ö�·��
			if (2 == mode)
			{
				wsprintf(str2, "play %s repeat", shortName);
			}
			else
			{
				wsprintf(str2, "play %s", shortName);
			}
			break;
		}
	}
	num = count;
	SetDlgItemText(hwnd, IDC_EDITMUSIC, szFileName[num]);
	mciSendString(str2, "", 0, NULL);  // ����ѡ�и���
	getAllTime(hwnd);
}


//******************************************* ɾ���б���ȫ���� *******************************************//
void deleteAll(HWND hwnd)
{
	stopPlay(hwnd);
	int i;
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);
	int icount = ListBox_GetCount(hwList);
	for (i = icount - 1; i >= 0; i--)
	{
		ListBox_DeleteString(hwList, i);
		strcpy(szFileName[i], "");//szFileNameȫ�ֱ���
		strcpy(szFileNamePath[i], "");//szFileNamePathȫ�ֱ���
	}
	offset = 0;//�򿪸���ʱ��¼�����ı�ţ�Ϊ�˶�δ�ʱ�����������������Ϊȫ�ֱ���
	num = 0;//���ڲ��Ÿ��������
}

//******************************************* �Ƴ�ѡ�е���Ŀ *******************************************//
void deleteSel(HWND hwnd)
{
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);
	int selCount = ListBox_GetCurSel(hwList);
	if (selCount == num)  // ���ɾ�����ǵ�ǰ���ڲ��ŵģ�ֹͣ�������֣�ѡ����һ��
	{
		stopPlay(hwnd);
	}
	int i;
	for (i = selCount; i < ListBox_GetCount(hwList) - 1; i++)  // ����ŵ�·����Ϣ����ǰ��
	{
		strcpy(szFileNamePath[i], szFileNamePath[i+1]);
		strcpy(szFileName[i], szFileName[i+1]);
	}
	strcpy(szFileName[i], "");  // ��ԭ��������Ϊ��
	strcpy(szFileNamePath[i], "");// ��ԭ��������Ϊ��
	ListBox_DeleteString(hwList, selCount);  // ���б���ɾ��ѡ����
	if(num == selCount)//���ڲ��ŵĸ�����ŵ���Ҫɾ���ĸ�����ţ�ѡ���б��е�һ������
	{
		num=0;
	}
	if (num > selCount)//���ڲ��ŵĸ�����Ŵ���Ҫɾ���ĸ�����ţ���Ȼѡ���б������ڲ��ŵĸ���
	{
		num--;
	}
	ListBox_SetCurSel(hwList, num);  // ѡ���б������ڲ��ŵĸ���
	offset--;
}




//******************************************* ��ͣ���� *******************************************//
void pauseMusic(HWND hwnd)
{
	TCHAR str1[256] = "";
	TCHAR str2[256] = "";
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);  // �õ�ListBox���
	int index = ListBox_GetCurSel(hwList);
	ListBox_GetText(hwList, index, str1);  // �õ�������
	HWND hwButtonPause = GetDlgItem(hwnd, IDC_PAUSE);  // �õ�IDC_PAUSE��ť�ľ��
	if(strcmp(str1, szFileName[num]) != 0)//ѡ�еĸ����������ڲ��ŵĸ������޷���ͣ
	{
		MessageBox(hwnd,TEXT("�޷���ͣδ���ŵĸ�����"),TEXT("����"),MB_OK|MB_ICONERROR);

	}
	else
	{
		int count;
		for (count = 0; count < offset; count++)
		{
			if (0 == strcmp(str1, szFileName[count]))
			{
				GetShortPathName(szFileNamePath[count], shortName, sizeof(shortName));  // ��ö�·��
				if (1 == playStatus)  // ����״̬
				{
					SetWindowText(hwButtonPause, TEXT("����"));  // ����ť�ϵ����ָ�Ϊ��������
					wsprintf(str2, "pause %s", shortName);  // pause����
					playStatus--;
					SetDlgItemText(hwnd,IDC_STATUS,TEXT("pausing!......."));
				}
				else
				{
					SetWindowText(hwButtonPause, TEXT("��ͣ"));  // ����ť�ϵ����ָ�Ϊ����ͣ��
					wsprintf(str2, "resume %s", shortName);  // resume����
					playStatus++;
					SetDlgItemText(hwnd,IDC_STATUS,TEXT("playing!......."));
				}
			}
		}
	}
	mciSendString(str2, "", 0, NULL);  // ����������ͣ���Ÿ���
}

//******************************************* �Զ�תΪ��һ�� *******************************************//
void autoNext(HWND hwnd)
{
	srand(time(0));
	mode = ComboBox_GetCurSel(GetDlgItem(hwnd, IDC_COMBO1));  // ��ȡ��ǰ�Ĳ���ģʽ
	stopPlay(hwnd);
	TCHAR str1[256] = "";
	TCHAR str2[256] = "";
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);  // �õ�ListBox���
	int index = ListBox_GetCurSel(hwList);  //�õ��������ڲ��ŵĸ���
	int all = ListBox_GetCount(hwList);  // �б�������
	if (1 == mode)
	{
		ListBox_SetCurSel(hwList, index);
	}

	if (0 == mode || 2 == mode)
	{
		ListBox_GetText(hwList, (index+1)%all, str1);  // �õ�������
		ListBox_SetCurSel(hwList, (index+1)%all);  //ѡ����һ�׸���
		if (0 == mode && all == index+1)
		{
			stopPlay(hwnd);
		}
	}
	if (3 == mode)
	{
		int iRand = rand()%all;
		ListBox_GetText(hwList, iRand, str1);
		ListBox_SetCurSel(hwList, iRand);
	}

	int count;
	for (count = 0; count < offset; count++)
	{
		if (0 == strcmp(str1, szFileName[count]))
		{
			GetShortPathName(szFileNamePath[count], shortName, sizeof(shortName));  // ��ö�·��
			wsprintf(str2, "play %s", shortName);
			break;
		}
	}
	num = count;
	SetDlgItemText(hwnd, IDC_EDITMUSIC, szFileName[num]);  // ����ڴ˴��Ļ���ʲô������
	mciSendString(str2, "", 0, NULL);  // ����ѡ�и���
	getAllTime(hwnd);
}

//******************************************* ������һ�� *******************************************//
void playLast(HWND hwnd)
{
	stopPlay(hwnd);
	TCHAR str1[256] = "";
	TCHAR str2[256] = "";
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);  // �õ�ListBox���
	int index = ListBox_GetCurSel(hwList);
	int all = ListBox_GetCount(hwList);  // �б�������
	if (index > 0)
	{
		ListBox_GetText(hwList, index-1, str1);  // �õ�������
		ListBox_SetCurSel(hwList, index-1);
	}
	else//��Ϊ��һ�׸裬��index==0ʱ���������һ��
	{
		ListBox_GetText(hwList, all-1, str1);  // �õ�������
		ListBox_SetCurSel(hwList, all-1);
	}
	int count;
	for (count = 0; count < offset; count++)
	{
		if (0 == strcmp(str1, szFileName[count]))
		{
			GetShortPathName(szFileNamePath[count], shortName, sizeof(shortName));  // ��ö�·��
			wsprintf(str2, "play %s", shortName);
			break;
		}
	}
	num = count;
	SetDlgItemText(hwnd, IDC_EDITMUSIC, szFileName[num]);  //��IDC_EDITMUSIC�༭����ʾ��Ҫ���ŵĸ����ļ���
	mciSendString(str2, "", 0, NULL);  // ����ѡ�и���
	getAllTime(hwnd);
}

//******************************************* ������һ�� *******************************************//
void playNext(HWND hwnd)
{
	stopPlay(hwnd);
	TCHAR str1[256] = "";
	TCHAR str2[256] = "";
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);  // �õ�ListBox���
	int index = ListBox_GetCurSel(hwList);
	int all = ListBox_GetCount(hwList);  // �б�������

	ListBox_GetText(hwList, (index+1)%all, str1);  // �õ�������
	ListBox_SetCurSel(hwList, (index+1)%all);
	int count;
	for (count = 0; count < offset; count++)
	{
		if (0 == strcmp(str1, szFileName[count]))
		{
			GetShortPathName(szFileNamePath[count], shortName, sizeof(shortName));  // ��ö�·��
			wsprintf(str2, "play %s", shortName);
			break;
		}
	}
	num = count;
	SetDlgItemText(hwnd, IDC_EDITMUSIC, szFileName[num]);  // ��IDC_EDITMUSIC�༭����ʾ��Ҫ���ŵĸ����ļ���
	mciSendString(str2, "", 0, NULL);  // ����ѡ�и���
	getAllTime(hwnd);
}

//****************************** ֹͣ���ŵ�ǰ���ڲ��ŵĸ��� *****************************************//
void stopPlay(HWND hwnd)
{
	TCHAR str[256];
	GetShortPathName(szFileNamePath[num], shortName, sizeof(shortName));
	wsprintf(str, "close %s", shortName);
	mciSendString(str, "", 0, NULL);
}

//******************************************* ���� *************************************************//
void silence(HWND hwnd)
{
	TCHAR str[256] = "";
	TCHAR szCommand[MAX_PATH + 10];
	HWND hwCheck = GetDlgItem(hwnd,IDC_CHECK);  // �õ�CheckBox�ľ��
	HWND hwndList = GetDlgItem(hwnd, IDC_LIST);  // �õ�ListBox�ľ��
	int index = ListBox_GetCurSel(hwndList);
	ListBox_GetText(hwndList, index, str);  // �õ�������
	
	int count;
	for (count = 0; count < offset; count++)
	{
		if (0 == strcmp(str, szFileName[count]))
		{
			GetShortPathName(szFileNamePath[count], shortName, sizeof(shortName));  // ��ö�·��
			if(BST_CHECKED == Button_GetCheck(hwCheck))  // �����ѡ�У�����
			{
				wsprintf(szCommand, TEXT("setaudio %s off"), shortName);
			}
			if (BST_UNCHECKED == Button_GetCheck(hwCheck))  // δ��ѡ�У��ظ�����
			{
				wsprintf(szCommand, TEXT("setaudio %s on"), shortName);
			}
			mciSendString(szCommand, NULL, 0, NULL);
		}  // end if
	}  // end for
}

//****************************************************** ��ȡ��Ŀ�ܳ��� *******************************************//
void getAllTime(HWND hwnd)
{
	TCHAR sPosition[256];
	TCHAR str[256];
	wsprintf(str, "status %s length", shortName);
	mciSendString(str, sPosition, 255, 0);
	allLength = strtol(sPosition, NULL, 0);

/*strtol��atoi����ǿ�棬��Ҫ�������⼸���棺 ����
1.��������ʶ��ʮ����������������ʶ���������Ƶ�������ȡ����base������
����strtol("0XDEADbeE~~", NULL, 16)����0xdeadbee��ֵ��strtol("0777~~", NULL, 8)����0777��ֵ�� ����
2.endptr��һ��������������������ʱָ�����δ��ʶ��ĵ�һ���ַ���
����char *pos; strtol("123abc", &pos, 10);��strtol����123��posָ���ַ����е���ĸa��
����ַ�����ͷû�п�ʶ�������������char *pos; strtol("ABCabc", &pos, 10);����strtol����0��posָ���ַ�����ͷ��
���Ծݴ��ж����ֳ���������������atoi�����˵ġ� */

	minite = allLength / 60000;
	second = (allLength / 1000) % 60;
	wsprintf(strTimeAll, "%.2d:%.2d", minite, second);
	SetDlgItemText(hwnd, IDC_EDITTIMEALL, strTimeAll);
}


//******************************************** ��ȡ��������ϸ��Ϣ��δ��ɣ����� ********************************//
void getSongMessage(HWND hwnd)
{
	struct tagID3V1
	{
		char Header[4];  // ��ǩͷ�����ǡ�TAG��������Ϊû�б�ǩ
		char Title[31];  // ����
		char Artist[31];  // ����
		char Album[31];  // ר��
		char Comment[31];  // ��ע
	}ID3V1;

	FILE *fp;
	fp = fopen(szFileNamePath[num], "r");
	fseek(fp,-128L,SEEK_END);
	fread(ID3V1.Header, 3, 1, fp);

	// �жϱ�ǩͷ���ޡ�TAG����û������Ϊû�б�ǩ
	if (0 == memcmp(ID3V1.Header, "TAG", 3))
	{
		ID3V1.Header[3] = '\0';

		fread(ID3V1.Title, 30, 1, fp);
		ID3V1.Title[30]='\0';

		fread(ID3V1.Artist, 30, 1, fp);
		ID3V1.Artist[30]='\0';

		fread(ID3V1.Album, 30, 1, fp);
		ID3V1.Album[30]='\0';

		fread(ID3V1.Comment,30, 1, fp);
        ID3V1.Comment[30]='\0';

		TCHAR str[256];
		wsprintf(str, "���� %s\n\n���� %s\n\nר�� %s\n\n��ע %s", ID3V1.Title, ID3V1.Artist, ID3V1.Album, ID3V1.Comment);
		MessageBox(hwnd, str, TEXT("��Ŀ��Ϣ"), MB_OK);
	}
	else
	{
		MessageBox(hwnd, TEXT("�˸�����δ����ID3V1��ǩ"), TEXT("��Ŀ��Ϣ"), MB_OK);
	}
}

//********************************** ���麯�� ���������ͽ��� *****************************************//

void Main_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
{        
	switch(GetDlgCtrlID(hwndCtl)) //�õ��ؼ�ID
	{ 
		//������������
	case IDC_SLIDERVOLUME:
		{        
			int voice = SendMessage(GetDlgItem(hwnd, IDC_SLIDERVOLUME), TBM_GETPOS, 0, 0); //�õ���ǰ���������ֵ
				//TBM_GETPOS�����ص�ǰ����λ���������ֵ���߼�λ�ã�
			TCHAR szVoice[256];
			wsprintf(szVoice, "setaudio %s volume to %d", shortName, voice); //���������õ������ֵ
			mciSendString(szVoice, (LPTSTR)NULL, 0, 0);	
		}
		break;
	case IDC_SLIDER: //�����Ľ�����
		{
			if(SB_ENDSCROLL == code)
			{
				long lPosition = SendMessage(GetDlgItem(hwnd, IDC_SLIDER), TBM_GETPOS, 0, 0); //�õ���ǰ�Ľ���ֵ
				//itoa(lPosition, curTime, 10);
				TCHAR strPos[256];
				wsprintf(strPos, "play %s from %ld", shortName, lPosition);

//???????????????????????????????????????????�����????????????????????????????????????????????????????????//
				mciSendString(strPos, (LPTSTR)NULL, 0, 0);												   //
				mciSendString(strPos, (LPTSTR)NULL, 0, 0);  // ΪʲôҪ������һ�����Ҳ�����				   //
//?????????????????????????????????????????????????????????????????????????????????????????????????????????//
				
			}
        }
		break;
	}
}


void Main_OnClose(HWND hwnd)
{

    EndDialog(hwnd, 0);
}