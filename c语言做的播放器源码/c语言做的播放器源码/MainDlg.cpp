#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <time.h>		//用到了time函数，所以要有这个头文件
#include <commdlg.h>
#include <mmsystem.h>  // mciSengString函数调用需要先调用#include <mmsystem.h>
#include <commctrl.h>  // TBM_SETPOS头文件
#include "resource.h"
#include "MainDlg.h"
#include <shellapi.h>//有关系统托盘的头文件
#define WM_HIDE WM_USER+100  
							//定制自己的消息ID。
							//为了防止用户定义的消息ID与系统的消息ID冲突
							//MS（Microsoft）定义了一个宏WM_USER，小于WM_USER的ID被系统使用，大于WM_USER的ID被用户使用。 

/* 【自学去】网站收集 http://www.zixue7.com */

#define ORDER 0  //顺序播放
#define SINGLELOOP 1  //单曲循环
#define LISTLOOP 2  //列表循环
#define RANDOM 3  //随机播放

void Main_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos); //声明滑块函数

// 全局变量定义
TCHAR szFileNamePath[256][MAX_PATH];  //歌曲的完全路径，二维数组     Path（路径）
TCHAR szFileName[256][MAX_PATH];  // 歌曲名
TCHAR shortName[256]; //歌曲的短路径名
int num;   //正在播放歌曲的序号
int offset = 0;    //打开歌曲时记录歌曲的编号，为了多次打开时编号能连续，所以设为全局变量
int count = 0;  //为列表中的歌曲添加序号
int playStatus = 1;  //   当前歌曲播放状态，1 表示正在播放状态，0 表示暂停状态
int minite;  // 曲目播放时间，分
int second;  // 曲目播放时间，秒
long allLength;											//这是什么？
long curLength;	//	   curLength = atoi(curTime);		//这是但前时间的字符串转化为INT型
TCHAR strTime[256] = "";  // 曲目播放当前时间
TCHAR strTimeAll[256] = "";  // 曲目总时间
TCHAR curTime[256] = "";								// 这是什么？
int mode = ORDER;										// 这是什么？
int n;													// 这是什么？

// 函数原型
void addFiles(HWND hwnd);  // 添加歌曲
void playMusic(HWND hwnd);  // 播放歌曲
void pauseMusic(HWND hwnd);  // 暂停播放
void stopPlay(HWND hwnd);  // 停止播放当前正在播放的歌曲
void playLast(HWND hwnd);  // 播放上一曲
void playNext(HWND hwnd);  // 播放下一曲
void autoNext(HWND hwnd);  //自动播放下一曲
void silence(HWND hwnd);  // 静音
void getAllTime(HWND hwnd);  //  得到歌曲总时间
void deleteAll(HWND hwnd);  // 移除所有曲目
void deleteSel(HWND hwnd);  // 移除选中曲目
void getSongMessage(HWND hwnd);							// 获取曲目详细信息？？

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////*******    此函数需要现在初始化对话框中定义TimerProc！！！如：SetTimer(hwnd,1,1000,TimerProc);   *************//////

VOID CALLBACK TimerProc (HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime) //IDC_EDITSYST编辑框中在显示系统时间
{
	SYSTEMTIME stLocal;   //系统当前时间
	TCHAR time[256];     //定义time数组来保存需要在IDC_EDITSYST编辑框中显示的内容
	GetLocalTime(&stLocal);//得到系统当前时间的指针
	wsprintf(time,"%d年%d月%d日  %d:%d:%d",stLocal.wYear,stLocal.wMonth,stLocal.wDay
		,stLocal.wHour,stLocal.wMinute,stLocal.wSecond);//将“”中内容拷贝到time数组中

	SetDlgItemText(hwnd,IDC_EDITSYST,time);//将time数组内容打印到IDC_EDITSYST编辑框中
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////              此函数需要现在初始化对话框中定义curTimePro！！！如：SetTimer(hwnd, 0, 1000, curTimePro);      ///////


 
void CALLBACK curTimePro(HWND hwnd, UINT message, UINT iTemerID, DWORD dwTime)// 回调函数，读取当前播放时间,设置滑动条的当前值
{
	TCHAR str[256];
	wsprintf(str, "status %s position", shortName);
	//int wsprintf( 　　LPTSTR lpOut, 输出缓冲区，最大为1024字节 　　LPCTSTR lpFmt,  格式字符串 　　... 需输出的参数;）
	mciSendString(str, curTime, sizeof(curTime)/sizeof(TCHAR), NULL);//mciSendString(“play ***”,"",0,NULL);
	curLength = atoi(curTime);
	minite = curLength / 60000;//定义时间中  “分”的由来
	second = (curLength / 1000) % 60;//定义时间中  “秒”的由来
	wsprintf(strTime, "%.2d:%.2d", minite, second);// 曲目播放当前时间 的确定
	SetDlgItemText(hwnd, IDC_EDITTIME, strTime);//将当前播放时间打印到IDC_EDITTIME中


	// 设置滑块的最大值，最小值以及当时位置
	HWND hwSlider = GetDlgItem(hwnd, IDC_SLIDER);//IDC_SLIDER的句柄定义为hwSlider
	SendMessage(hwSlider, TBM_SETRANGEMAX, (WPARAM)TRUE, allLength);//TBM_SETRANGEMAX：设置滑块逻辑位置的最大值，及是否重画
	SendMessage(hwSlider, TBM_SETRANGEMIN, (WPARAM)TRUE, 0);//TBM_SETRANGEMIN：设置滑块逻辑位置的最小值，及是否重画
	SendMessage(hwSlider, TBM_SETPOS, (WPARAM)TRUE, curLength);//TBM_SETPOS：设置滑块的逻辑位置，及是否重画


	TCHAR szCommand[MAX_PATH+10];
	TCHAR szReturn[MAX_PATH];
	ZeroMemory(szCommand, sizeof(szCommand)/sizeof(TCHAR));
	//C语言中声明一个结构体变量之后，在使用这个变量之前要首先用memset来把各个位清零。使用C语言内置的函数memset来完成：
	//memset(&s1,sizeof(s1),0);
	//在这里我们使用ZeroMemory“函数”，ZeroMemory其实并不是函数，其实是memset的宏定义
	//ZeroMemory其实就是memset，纸老虎而已，不是一个全新的函数。


	wsprintf(szCommand, TEXT("status %s mode"), shortName);
	mciSendString(szCommand, szReturn, sizeof(szReturn)/sizeof(TCHAR), NULL);

//***********************************下面的函数功能会和IDC_STOP点击函数冲突！！！***************************************//
	//strcmp速度快但是代码多;lstrcmp速度慢但精简，其实也就慢那么一丁丁丁丁点啦   推荐使用lstrcmp
	//lstrcmp字符串对比，本语句含义是：当szReturn==stopped时自动播放下一曲
	if (0 == lstrcmp(szReturn, TEXT("stopped")))
	{											
		autoNext(hwnd);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////              此函数需要现在初始化对话框中定义TimerProc1！！！如：SetTimer(hwnd,2,1000,TimerProc1);         ///////

VOID CALLBACK TimerProc1(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime) //IDC_EDITSYST编辑框中在显示系统时间
{
	SYSTEMTIME stLocal;   //系统当前时间
	GetLocalTime(&stLocal);//得到系统当前时间的指针
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
//////*****************************************最下化到系统托盘问题*************************************************////
/*     ypedef struct _NOTIFYICONDATAA {
        DWORD cbSize;                    //结构体的大小，以字节为单位。
        HWND hWnd;						//窗口的句柄。标示的窗口用来接收与托盘图标相关的消息。
        UINT uID;						//应用程序定义的任务栏图标的标识符。
        UINT uFlags;					//此成员表明具体哪些其他成员为合法数据（即哪些成员起作用）。
										//此成员可以为以下值的组合： 
										//  NIF_ICON 　　hIcon成员起作用。 　
										//　NIF_MESSAGE 　uCallbackMessage成员起作用。 　
										//　NIF_TIP 　　  szTip成员起作用。 　
										//　NIF_STATE 　　dwState和dwStateMask成员起作用。 
										//　NIF_INFO 　　 使用气球提示代替普通的工具提示框。szInfo, uTimeout, szInfoTitle和dwInfoFlags成员起作用。 　
										//　NIF_GUID 　　 保留。 

        UINT uCallbackMessage;			//应用程序定义的消息标示。当托盘图标区域发生鼠标事件或者使用键盘选择或激活图标时，
										//系统将使用此标示向由hWnd成员标示的窗口发送消息。
										//消息响应函数的wParam参数标示了消息事件发生的任务栏图标，lParam参数根据事件的不同，
										//包含了鼠标或键盘的具体消息，例如当鼠标指针移过托盘图标时，lParam将为WM_MOUSEMOVE。
        HICON hIcon;					//增加、修改或删除的图标的句柄。
        CHAR   szTip[64];				//指向一个以\0结束的字符串的指针。字符串的内容为标准工具提示的信息。
										//包含最后的\0字符，szTip最多含有64个字符。 
} NOTIFYICONDATAA                         */
			
//*****************首先了解上面的NOTIFYICONDATA结构体的成员*****************//

void Minimized(HWND hwnd,int flag)
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = 1;
	nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
	nid.uCallbackMessage = WM_HIDE;				//自定义消息
	HINSTANCE hin = (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE);//获得程序句柄！！！
	nid.hIcon = LoadIcon(hin,MAKEINTRESOURCE(1));   //增加一个MAKEINTRESOURCE(1)的图标句柄，MAKEINTRESOURCE(1)即：应用程序图标
	lstrcpy(nid.szTip,TEXT("双击恢复窗口"));             //最小化到托盘，鼠标移到托盘上面显示的信息提示条。
	switch(flag)
	{
	case 0:
		{//添加托盘图标，隐藏窗口
			Shell_NotifyIcon(NIM_ADD,&nid);
//BOOL Shell_NotifyIcon( DWORD dwMessage,PNOTIFYICONDATA lpdata);
//dwMessage为输入参数，传递发送的消息，表明要执行的操作。可选的值如下：
//NIM_ADD 向托盘区域添加一个图标。
//NIM_DELETE 删除托盘区域的一个图标。
//NIM_MODIFY  修改托盘区域的一个图标。
//NIM_SETFOCUS 设置焦点。比如当用户操作托盘图标弹出菜单，而有按下ESC键将菜单消除后，程序应该使用此消息来将焦点设置到托盘图标上。 
//lpdata 为输入参数，是指向NOTIFYICONDATA结构体的指针，结构体内容用来配合第一个参数wMessage进行图标操作。
			ShowWindow(hwnd,SW_HIDE);//隐藏窗口
		}
		break;
	case 1:
		{//删除托盘图标
			ShowWindow(hwnd,SW_SHOWNORMAL);
			Shell_NotifyIcon(NIM_DELETE,&nid);
			SetForegroundWindow(hwnd);				//Foreground 前台
//函数原型：BOOL SetForegroundWindow（HWND hWnd）
//该函数将创建指定窗口的线程设置到前台，并且激活该窗口。
//键盘输入转向该窗口，并为用户改各种可视的记号。系统给创建前台窗口的线程分配的权限稍高于其他线程。 
		}
		break;
	default:
		break;
	}	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////***************************Main_Proc  对话框的消息处理函数****************************************************////

BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {	
		//BEGIN MESSAGE CRACK
		HANDLE_MSG(hWnd,WM_HSCROLL, Main_OnHScroll);  // Slider滑块消息
        HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);//初始化的消息
        HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);//发给控件们的消息
		HANDLE_MSG(hWnd,WM_CLOSE, Main_OnClose);//关闭对话框的消息
		//END MESSAGE CRACK
		case WM_HIDE:						//#define WM_HIDE WM_USER+100 
		{
			if(lParam==WM_LBUTTONDBLCLK)//表示左键双击事件
			{
				Minimized(hWnd,1);			//Minimized函数就需要这Main_Proc函数之前定义
			}
			else if(lParam==WM_RBUTTONDOWN)//表示右键单击事件
			{
				Minimized(hWnd,1);
			}

		}
		break;
		case WM_SIZE:
			{	
				if(SIZE_MINIMIZED==wParam)//点击最小化 到托盘
				{
					Minimized(hWnd,0);
				}
			}

		}
    return FALSE;
}


//////////**********************************************************************************************************////
////////                                  对话框的初始化！！！！												///////
 

BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{

	SetTimer(hwnd,1,1000,TimerProc);//SetTimer(HWND hWnd ,UINT nIDEvent,UINT uElapse,TIMERPROC lpTimerFunc)函数
									//HWND hWnd窗口句柄 ；
									//UINT nIDEvent 定时器ID，多个定时器时，可以通过该ID判断是哪个定时器 
									//UINT uElapse时间间隔,单位为毫秒 ；
									//TIMERPROC lpTimerFunc  回调函数 。
	SetTimer(hwnd, 0, 1000, curTimePro);
	SetTimer(hwnd,2,1000,TimerProc1);//闹钟
// 在SetTimer定义的回调函数定义必须在Main_OnInitDialog之前！！！！！！


	// 初始化时间，播放时间和曲目总时间都为零
	strcpy(strTime, "00:00");
	strcpy(strTimeAll, "00:00");
	SetDlgItemText(hwnd, IDC_EDITTIME, strTime);
	SetDlgItemText(hwnd, IDC_EDITTIMEALL, strTimeAll);

	// 初始化音量
	HWND hwSliderVolume = GetDlgItem(hwnd, IDC_SLIDERVOLUME);
	SendMessage(hwSliderVolume, TBM_SETRANGEMAX, (WPARAM)TRUE, 1000);  // 音量最大为100
	SendMessage(hwSliderVolume, TBM_SETRANGEMIN, (WPARAM)TRUE, 0);  // 最小值为0
	SendMessage(hwSliderVolume, TBM_SETPOS, (WPARAM)TRUE, 500);   // 初始化为音量50

	//循环模式
	HWND hwCombo1 = GetDlgItem(hwnd, IDC_COMBO1);
	ComboBox_InsertString(hwCombo1, -1, TEXT("顺序播放"));//index为-1时指：将顺序播放插入到列表末尾 
	ComboBox_InsertString(hwCombo1, -1, TEXT("单曲循环"));//index为-1时指：将单曲循环插入到列表末尾
	ComboBox_InsertString(hwCombo1, -1, TEXT("列表循环"));//index为-1时指：将列表循环插入到列表末尾
	ComboBox_InsertString(hwCombo1, -1, TEXT("随机播放"));//index为-1时指：将随机播放插入到列表末尾
	ComboBox_SetCurSel(hwCombo1, 0);  //默认选择顺序播放模式
	SetDlgItemText(hwnd,IDC_STATUS,TEXT("Ready!......"));  //初始化播放状态为READY

    return TRUE;
}



//*******************************  Main_OnCommand  处理对话框控件消息的函数********************************//

void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch(id)
    {	
		// 添加文件到列表
		case ID_MENUITEMADD:
        case IDC_ADD:
		{
			addFiles(hwnd);  
			HWND hwList = GetDlgItem(hwnd, IDC_LIST);
			ListBox_SetCurSel(hwList, 0);
			
		}
        break;

		// 播放选中的歌曲
		case ID_MENUITEMPLAY:
		case IDC_PLAY:
		{
			playMusic(hwnd);  
			SetDlgItemText(hwnd,IDC_STATUS,TEXT("playing!......."));

		}
		break;

		// 暂停选中的歌曲
		case ID_MENUITEMPAUSE:
		case IDC_PAUSE:
		{
			pauseMusic(hwnd);  
			
		}
		break;

		// 停止正在播放的音乐
		case ID_MENUITEMSTOP:
		case IDC_STOP:
		{
			stopPlay(hwnd);  
			SetDlgItemText(hwnd,IDC_STATUS,TEXT("stopping!........"));
		}
		break;

		//列表框IDC_LIST的信息处理
		case IDC_LIST:
		{
			switch(codeNotify)
			{

			// 播放双击选中的歌曲
			case LBN_DBLCLK:  //双击选中项 
				{
					playMusic(hwnd);  
					SetDlgItemText(hwnd,IDC_STATUS,TEXT("playing!......."));
				}
				break;
			}
		}
		break;

		// 播放上一曲
		case ID_MENUITEMLAST:
		case IDC_LAST:
		{
			playLast(hwnd);   
			SetDlgItemText(hwnd,IDC_STATUS,TEXT("playing!......."));
		}
		break;

		// 播放下一曲
		case ID_MENUITEMNEXT:
		case IDC_NEXT:
		{
			playNext(hwnd);  
			SetDlgItemText(hwnd,IDC_STATUS,TEXT("playing!......."));
		}
		break;

		// 静音与恢复
		case IDC_CHECK:
		{
			silence(hwnd);  
		}
		break;

		// 删除列表中所有曲目
		case ID_MENUITEMCLEAN:		
		case IDC_DELETEALL:
		{
			deleteAll(hwnd);  
			SetDlgItemText(hwnd,IDC_STATUS,TEXT("Ready!......")); 
		}
		break;

		//删除列表中的单个曲目
		case ID_MENUITEMDEL:
		case IDC_DELETESEL:
		{
			deleteSel(hwnd);
			SetDlgItemText(hwnd,IDC_STATUS,TEXT("Ready!......")); 
		}
		break;

		//显示器休眠
		case ID_MENUITEMSLEEP:
        case IDC_SLEEP:
		{
			SendMessage(hwnd,WM_SYSCOMMAND,SC_MONITORPOWER,2);
		}
        break;

		//关于
		case ID_MENUITEMABOUT:
		{
			MessageBox(hwnd,TEXT("大家一起学习探讨!QQ:983572133，加我时说明来自如鹏网！"),TEXT("关于"),MB_OK);
		}
		break;

		//退出
		case ID_MENUITEMEXIT:
		{
			int i=MessageBox(hwnd,TEXT("确认退出吗？"),TEXT("询问"),MB_YESNO|MB_ICONQUESTION);
			if(i==6)
			{
				Main_OnClose(hwnd);
			}
		}
		
		//添加闹钟
		case IDC_BUTTON1:
		{
		HWND hwList = GetDlgItem(hwnd, IDC_LIST1);
		TCHAR szFile[256*MAX_PATH] = "";  
		TCHAR szPath[256] = "";  
		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(ofn));  
		ofn.lStructSize = sizeof(ofn);  
		ofn.hwndOwner = hwnd;  
		ofn.lpstrFilter = "音乐文件(mp3、wma、wav)\0*.wma;*.mp3;*.wav\0所有文件(*.*)\0*.*\0";
		ofn.lpstrCustomFilter = NULL;
		ofn.nFilterIndex = 1;  
		ofn.lpstrFile = szFile;  
		ofn.nMaxFile = sizeof(szFile) / sizeof(TCHAR);  
		ofn.lpstrFile[0] = TEXT('\0');	
		ofn.lpstrTitle = TEXT("添加闹铃");  
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

		//关机
		case ID_MENUITEMOFF:
		case IDC_BUTTONOFF:
		{
			system("shutdown -s -t 0");
		}
		break;

		//闹钟说明
		case ID_MENUITEMCLOCK:
		{
			MessageBox(hwnd,TEXT("闹钟时间格式为 小时:分钟 "),TEXT("闹钟说明"),MB_OK);
		}

        default:
		break;
    }
}

//******************************************各个函数的定义************************************************************//
////**************************************************************************************************************//////

//******************************************* 添加歌曲 ************************************************//
void addFiles(HWND hwnd)
{
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);  // 得到ListBox句柄

	TCHAR szFile[256*MAX_PATH] = "";  // 文件的名字，*MaxPath能解决添加多文件时出现的问题
	TCHAR szPath[256] = "";  // 歌曲的路径
	TCHAR *p;  // 指向歌曲的名字
	// int i;  // 用于计数

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));  // 清零(memset函数的宏定义)
	ofn.lStructSize = sizeof(ofn);  // lStructSize指定这个结构的大小，以字节为单位。
	ofn.hwndOwner = hwnd;  // 指向所有者对话框窗口的句柄。这个成员可以是任意有效窗口句柄，或如果对话框没有所有者它可以为NULL。
	ofn.lpstrFilter = "音乐文件(mp3、wma、wav)\0*.wma;*.mp3;*.wav\0所有文件(*.*)\0*.*\0";
	ofn.lpstrCustomFilter = NULL;//指向一个静态缓冲，它包含了一对以空字符结束的过滤器字符串，这个字符串是为了保留用户选择的过滤样式。
								 //如果这个成员是NULL，对话框不能保留用户自定义过滤器样式。
								 //如果这个成员不是NULL，nMaxCustFilter成员的值必须指定以TCHARs为单位的lpstrCustomFilter缓冲的大小。

	ofn.nFilterIndex = 1;  // 指定在文件类型控件中当前选择的过滤器的索引。音乐文件(mp3、wma、wav)  从1开始！！
	ofn.lpstrFile = szFile;  // lpstrFile指向包含初始化文件名编辑控件使用的文件名的缓冲。
	ofn.nMaxFile = sizeof(szFile) / sizeof(TCHAR);  // 指定lpstrFile缓冲的大小，以TCHARs为单位。

	ofn.lpstrFile[0] = TEXT('\0');	//不知道是什么？

	ofn.lpstrTitle = TEXT("添加音乐");  // 指向接收选择的文件的文件名和扩展名的缓冲（不带路径信息）。这个成员可以是NULL。
	ofn.nMaxFileTitle = NULL;  // 指定lpstrFileTitle缓冲的大小，以TCHARs为单位。

	ofn.Flags = OFN_HIDEREADONLY   |   OFN_FILEMUSTEXIST   |   OFN_PATHMUSTEXIST   |   OFN_EXPLORER  |  OFN_ALLOWMULTISELECT;
//OFN_ALLOWMULTISELECT 指定文件名列表框允许多选
//OFN_EXPLORER 指出任何打开或另存为对话框使用新的Explorer风格的用户化模块。
//OFN_HIDEREADONLY 隐藏只读复选框。
//OFN_FILEMUSTEXIST 指定用户仅可以在文件名登录字段中输入已存在的文件的名字。
//OFN_PATHMUSTEXIST 指定用户仅能输入的路径和文件名。

	ofn.lpstrDefExt = "*.mp3";
//指向包含默认扩展名的缓冲。如果用户忘记输入扩展名，GetOpenFileName和GetSaveFileName附加这个扩展名到文件名中。
//这个字符串可以是任一长度，但但只有头三个字符被附加。字符串不应该包含一个句点（.）。
//如果这个成员是NULL并且用户忘记了输入一个扩展名，那么将没有扩展名被附加。

	if (GetOpenFileName(&ofn))//如果打开的文件是TRUE则有.....
	{
		int nLength = 0;  // 文件路径的字符长度

		lstrcpyn(szPath, szFile, ofn.nFileOffset);// 把第一个文件名前的路径复制到szPath
												  //lstrcpyn   - 复制字符串, 同时指定要复制的长度
												  //nFileOffset指第一个文件名前的路径
//nFileOffset:
//指定从路径开始到通过lpstrFile指定的文件名字符串基于0的偏移，以TCHARs为单位。
//对于ANSI版本，是字节的个数；对于Unicode版本，是字符的个数。
//例如，如果lpstrFile指向下列的字符串，“c:\dir1\dir2\file.ext”，这个成员包含指出“file.ext”字符串偏移的位置值13。 

		szPath[ofn.nFileOffset] = '\0';  //(加上结束标记)取得文件路径
		nLength = lstrlen(szPath);

//???????????????????????????????????????????不理解?????????????????????????????????????????????????????????//
		if (szPath[nLength-1] != '\\')  // 如果选择了多个文件，必须加上'\\'									//
		{																									//
			lstrcat(szPath, TEXT("\\"));																	//
		}																									//
//??????????????????????????????????????????????????????????????????????????????????????????????????????????//

		p = szFile + ofn.nFileOffset;  //把指针移到第一个文件的文件名
		while (*p)
		{
			lstrcpy(szFileNamePath[offset], szPath);  // 将路径复制给szFileNamePath[offset]
			lstrcat(szFileNamePath[offset], p);  // 加上文件名

			SendMessage(hwList, LB_ADDSTRING, 0, (LPARAM)p);	//向列表框添加文件名，(LPARAM)p即文件名指针

			lstrcat(szFileName[offset], p);      //文件名复制给szfilename,用于显示显示正在播放的文件名 

//??????????????????????????????????????不理解??????????????????????????????????//
			p += lstrlen(p) +1;   //移至下一个文件								//
//??????????????????????????????????????????????????????????????????????????????//
			offset++;
		}
	}
}

//******************************************* 播放歌曲 *******************************************//
void playMusic(HWND hwnd)
{
	stopPlay(hwnd);  // 停止正在播放的歌曲
	TCHAR str1[256] = "";
	TCHAR str2[256] = "";
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);  // 得到ListBox句柄
	int index = ListBox_GetCurSel(hwList);
	ListBox_GetText(hwList, index, str1);  // 得到歌曲名

	int count;
	for (count = 0; count < offset; count++)
	{
		if (0 == strcmp(str1, szFileName[count]))
		{
			GetShortPathName(szFileNamePath[count], shortName, sizeof(shortName));  // 获得短路径
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
	mciSendString(str2, "", 0, NULL);  // 播放选中歌曲
	getAllTime(hwnd);
}


//******************************************* 删除列表中全部项 *******************************************//
void deleteAll(HWND hwnd)
{
	stopPlay(hwnd);
	int i;
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);
	int icount = ListBox_GetCount(hwList);
	for (i = icount - 1; i >= 0; i--)
	{
		ListBox_DeleteString(hwList, i);
		strcpy(szFileName[i], "");//szFileName全局变量
		strcpy(szFileNamePath[i], "");//szFileNamePath全局变量
	}
	offset = 0;//打开歌曲时记录歌曲的编号，为了多次打开时编号能连续，所以设为全局变量
	num = 0;//正在播放歌曲的序号
}

//******************************************* 移除选中的曲目 *******************************************//
void deleteSel(HWND hwnd)
{
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);
	int selCount = ListBox_GetCurSel(hwList);
	if (selCount == num)  // 如果删除的是当前正在播放的，停止播放音乐，选中下一首
	{
		stopPlay(hwnd);
	}
	int i;
	for (i = selCount; i < ListBox_GetCount(hwList) - 1; i++)  // 将存放的路径信息依次前移
	{
		strcpy(szFileNamePath[i], szFileNamePath[i+1]);
		strcpy(szFileName[i], szFileName[i+1]);
	}
	strcpy(szFileName[i], "");  // 将原来最后的设为空
	strcpy(szFileNamePath[i], "");// 将原来最后的设为空
	ListBox_DeleteString(hwList, selCount);  // 从列表中删除选中项
	if(num == selCount)//正在播放的歌曲序号等于要删除的歌曲序号，选中列表中第一个歌曲
	{
		num=0;
	}
	if (num > selCount)//正在播放的歌曲序号大于要删除的歌曲序号，依然选中列表中正在播放的歌曲
	{
		num--;
	}
	ListBox_SetCurSel(hwList, num);  // 选中列表中正在播放的歌曲
	offset--;
}




//******************************************* 暂停播放 *******************************************//
void pauseMusic(HWND hwnd)
{
	TCHAR str1[256] = "";
	TCHAR str2[256] = "";
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);  // 得到ListBox句柄
	int index = ListBox_GetCurSel(hwList);
	ListBox_GetText(hwList, index, str1);  // 得到歌曲名
	HWND hwButtonPause = GetDlgItem(hwnd, IDC_PAUSE);  // 得到IDC_PAUSE按钮的句柄
	if(strcmp(str1, szFileName[num]) != 0)//选中的歌曲不是正在播放的歌曲就无法暂停
	{
		MessageBox(hwnd,TEXT("无法暂停未播放的歌曲！"),TEXT("错误"),MB_OK|MB_ICONERROR);

	}
	else
	{
		int count;
		for (count = 0; count < offset; count++)
		{
			if (0 == strcmp(str1, szFileName[count]))
			{
				GetShortPathName(szFileNamePath[count], shortName, sizeof(shortName));  // 获得短路径
				if (1 == playStatus)  // 播放状态
				{
					SetWindowText(hwButtonPause, TEXT("继续"));  // 将按钮上的文字改为“继续”
					wsprintf(str2, "pause %s", shortName);  // pause命令
					playStatus--;
					SetDlgItemText(hwnd,IDC_STATUS,TEXT("pausing!......."));
				}
				else
				{
					SetWindowText(hwButtonPause, TEXT("暂停"));  // 将按钮上的文字改为“暂停”
					wsprintf(str2, "resume %s", shortName);  // resume命令
					playStatus++;
					SetDlgItemText(hwnd,IDC_STATUS,TEXT("playing!......."));
				}
			}
		}
	}
	mciSendString(str2, "", 0, NULL);  // 继续或是暂停播放歌曲
}

//******************************************* 自动转为下一曲 *******************************************//
void autoNext(HWND hwnd)
{
	srand(time(0));
	mode = ComboBox_GetCurSel(GetDlgItem(hwnd, IDC_COMBO1));  // 获取当前的播放模式
	stopPlay(hwnd);
	TCHAR str1[256] = "";
	TCHAR str2[256] = "";
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);  // 得到ListBox句柄
	int index = ListBox_GetCurSel(hwList);  //得到现在正在播放的歌曲
	int all = ListBox_GetCount(hwList);  // 列表中总项
	if (1 == mode)
	{
		ListBox_SetCurSel(hwList, index);
	}

	if (0 == mode || 2 == mode)
	{
		ListBox_GetText(hwList, (index+1)%all, str1);  // 得到歌曲名
		ListBox_SetCurSel(hwList, (index+1)%all);  //选中下一首歌曲
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
			GetShortPathName(szFileNamePath[count], shortName, sizeof(shortName));  // 获得短路径
			wsprintf(str2, "play %s", shortName);
			break;
		}
	}
	num = count;
	SetDlgItemText(hwnd, IDC_EDITMUSIC, szFileName[num]);  // 如果在此处的话，什么都不显
	mciSendString(str2, "", 0, NULL);  // 播放选中歌曲
	getAllTime(hwnd);
}

//******************************************* 播放上一曲 *******************************************//
void playLast(HWND hwnd)
{
	stopPlay(hwnd);
	TCHAR str1[256] = "";
	TCHAR str2[256] = "";
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);  // 得到ListBox句柄
	int index = ListBox_GetCurSel(hwList);
	int all = ListBox_GetCount(hwList);  // 列表中总项
	if (index > 0)
	{
		ListBox_GetText(hwList, index-1, str1);  // 得到歌曲名
		ListBox_SetCurSel(hwList, index-1);
	}
	else//当为第一首歌，即index==0时，跳到最后一首
	{
		ListBox_GetText(hwList, all-1, str1);  // 得到歌曲名
		ListBox_SetCurSel(hwList, all-1);
	}
	int count;
	for (count = 0; count < offset; count++)
	{
		if (0 == strcmp(str1, szFileName[count]))
		{
			GetShortPathName(szFileNamePath[count], shortName, sizeof(shortName));  // 获得短路径
			wsprintf(str2, "play %s", shortName);
			break;
		}
	}
	num = count;
	SetDlgItemText(hwnd, IDC_EDITMUSIC, szFileName[num]);  //在IDC_EDITMUSIC编辑框显示将要播放的歌曲文件名
	mciSendString(str2, "", 0, NULL);  // 播放选中歌曲
	getAllTime(hwnd);
}

//******************************************* 播放下一曲 *******************************************//
void playNext(HWND hwnd)
{
	stopPlay(hwnd);
	TCHAR str1[256] = "";
	TCHAR str2[256] = "";
	HWND hwList = GetDlgItem(hwnd, IDC_LIST);  // 得到ListBox句柄
	int index = ListBox_GetCurSel(hwList);
	int all = ListBox_GetCount(hwList);  // 列表中总项

	ListBox_GetText(hwList, (index+1)%all, str1);  // 得到歌曲名
	ListBox_SetCurSel(hwList, (index+1)%all);
	int count;
	for (count = 0; count < offset; count++)
	{
		if (0 == strcmp(str1, szFileName[count]))
		{
			GetShortPathName(szFileNamePath[count], shortName, sizeof(shortName));  // 获得短路径
			wsprintf(str2, "play %s", shortName);
			break;
		}
	}
	num = count;
	SetDlgItemText(hwnd, IDC_EDITMUSIC, szFileName[num]);  // 在IDC_EDITMUSIC编辑框显示将要播放的歌曲文件名
	mciSendString(str2, "", 0, NULL);  // 播放选中歌曲
	getAllTime(hwnd);
}

//****************************** 停止播放当前正在播放的歌曲 *****************************************//
void stopPlay(HWND hwnd)
{
	TCHAR str[256];
	GetShortPathName(szFileNamePath[num], shortName, sizeof(shortName));
	wsprintf(str, "close %s", shortName);
	mciSendString(str, "", 0, NULL);
}

//******************************************* 静音 *************************************************//
void silence(HWND hwnd)
{
	TCHAR str[256] = "";
	TCHAR szCommand[MAX_PATH + 10];
	HWND hwCheck = GetDlgItem(hwnd,IDC_CHECK);  // 得到CheckBox的句柄
	HWND hwndList = GetDlgItem(hwnd, IDC_LIST);  // 得到ListBox的句柄
	int index = ListBox_GetCurSel(hwndList);
	ListBox_GetText(hwndList, index, str);  // 得到歌曲名
	
	int count;
	for (count = 0; count < offset; count++)
	{
		if (0 == strcmp(str, szFileName[count]))
		{
			GetShortPathName(szFileNamePath[count], shortName, sizeof(shortName));  // 获得短路径
			if(BST_CHECKED == Button_GetCheck(hwCheck))  // 如果被选中，则静音
			{
				wsprintf(szCommand, TEXT("setaudio %s off"), shortName);
			}
			if (BST_UNCHECKED == Button_GetCheck(hwCheck))  // 未被选中，回复正常
			{
				wsprintf(szCommand, TEXT("setaudio %s on"), shortName);
			}
			mciSendString(szCommand, NULL, 0, NULL);
		}  // end if
	}  // end for
}

//****************************************************** 获取曲目总长度 *******************************************//
void getAllTime(HWND hwnd)
{
	TCHAR sPosition[256];
	TCHAR str[256];
	wsprintf(str, "status %s length", shortName);
	mciSendString(str, sPosition, 255, 0);
	allLength = strtol(sPosition, NULL, 0);

/*strtol是atoi的增强版，主要体现在这几方面： 　　
1.不仅可以识别十进制整数，还可以识别其它进制的整数，取决于base参数，
比如strtol("0XDEADbeE~~", NULL, 16)返回0xdeadbee的值，strtol("0777~~", NULL, 8)返回0777的值。 　　
2.endptr是一个传出参数，函数返回时指向后面未被识别的第一个字符。
例如char *pos; strtol("123abc", &pos, 10);，strtol返回123，pos指向字符串中的字母a。
如果字符串开头没有可识别的整数，例如char *pos; strtol("ABCabc", &pos, 10);，则strtol返回0，pos指向字符串开头，
可以据此判断这种出错的情况，而这是atoi处理不了的。 */

	minite = allLength / 60000;
	second = (allLength / 1000) % 60;
	wsprintf(strTimeAll, "%.2d:%.2d", minite, second);
	SetDlgItemText(hwnd, IDC_EDITTIMEALL, strTimeAll);
}


//******************************************** 获取歌曲的详细信息（未完成！！） ********************************//
void getSongMessage(HWND hwnd)
{
	struct tagID3V1
	{
		char Header[4];  // 标签头必须是“TAG”否则认为没有标签
		char Title[31];  // 标题
		char Artist[31];  // 作者
		char Album[31];  // 专辑
		char Comment[31];  // 备注
	}ID3V1;

	FILE *fp;
	fp = fopen(szFileNamePath[num], "r");
	fseek(fp,-128L,SEEK_END);
	fread(ID3V1.Header, 3, 1, fp);

	// 判断标签头有无“TAG”，没有则认为没有标签
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
		wsprintf(str, "标题 %s\n\n作者 %s\n\n专辑 %s\n\n备注 %s", ID3V1.Title, ID3V1.Artist, ID3V1.Album, ID3V1.Comment);
		MessageBox(hwnd, str, TEXT("曲目信息"), MB_OK);
	}
	else
	{
		MessageBox(hwnd, TEXT("此歌曲里未包含ID3V1标签"), TEXT("曲目信息"), MB_OK);
	}
}

//********************************** 滑块函数 控制声音和进度 *****************************************//

void Main_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
{        
	switch(GetDlgCtrlID(hwndCtl)) //得到控件ID
	{ 
		//控制音量滑块
	case IDC_SLIDERVOLUME:
		{        
			int voice = SendMessage(GetDlgItem(hwnd, IDC_SLIDERVOLUME), TBM_GETPOS, 0, 0); //得到当前滑块的音量值
				//TBM_GETPOS：返回当前滑块位置所代表的值（逻辑位置）
			TCHAR szVoice[256];
			wsprintf(szVoice, "setaudio %s volume to %d", shortName, voice); //将音量设置到滑块的值
			mciSendString(szVoice, (LPTSTR)NULL, 0, 0);	
		}
		break;
	case IDC_SLIDER: //歌曲的进度条
		{
			if(SB_ENDSCROLL == code)
			{
				long lPosition = SendMessage(GetDlgItem(hwnd, IDC_SLIDER), TBM_GETPOS, 0, 0); //得到当前的进度值
				//itoa(lPosition, curTime, 10);
				TCHAR strPos[256];
				wsprintf(strPos, "play %s from %ld", shortName, lPosition);

//???????????????????????????????????????????不理解????????????????????????????????????????????????????????//
				mciSendString(strPos, (LPTSTR)NULL, 0, 0);												   //
				mciSendString(strPos, (LPTSTR)NULL, 0, 0);  // 为什么要用两个一样的我不明白				   //
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