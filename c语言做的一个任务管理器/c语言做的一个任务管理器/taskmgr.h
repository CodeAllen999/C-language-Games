#pragma once

#include "resource.h"
#include "define.h"


//常量声明:
#define IDC_STATUSWND   100

#define RFD_USEFULLPATHDIR   0x10
#define RFD_WOW_APP          0x04

#define DEFSPACING_BASE      3
#define INNERSPACING_BASE    2
#define TOPSPACING_BASE      10

#define MIN_DLG_SIZE_X 203
#define MIN_DLG_SIZE_Y 224
#define DLG_SCALE_X    4
#define DLG_SCALE_Y    8

//变量声明:
//对象声明:
extern    CRITICAL_SECTION    g_CSTrayThread;

class     CPtrArray;
class     CTrayNotification;
class     CPage;
class     COptions;
extern    COptions          g_Options;
//WinMain相关函数声明:
typedef   void (__cdecl *_PVFV)(void);

#define   IS_MIRRORING_ENABLED()          Mirror_IsEnabledOS();
#define   FINDME_TIMEOUT                  10000

STDAPI_(BOOL) staticIsOS(DWORD dwOS);

#define   NtCurrentProcess() ( (HANDLE) -1 )
#define   InitializeObjectAttributes( p, n, a, r, s ) { \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
    (p)->RootDirectory = r;                             \
    (p)->Attributes = a;                                \
    (p)->ObjectName = n;                                \
    (p)->SecurityDescriptor = s;                        \
    (p)->SecurityQualityOfService = NULL;               \
    }

#define   STATUS_INFO_LENGTH_MISMATCH             ((NTSTATUS)0xC0000004L)
#define   STATUS_SUCCESS                          ((NTSTATUS)0x00000000L)
#define   STATUS_BUFFER_TOO_SMALL                 ((NTSTATUS)0xC0000023L)

//经反汇编得到,原来的宏未知:
#define   IS_WINDOW_RTL_MIRRORED(hwnd) (GetWindowLong((HWND)hwnd,GWL_EXSTYLE))
//-----------------------------------------------------------------------------------------------------

// PtrToFns for RPC calls

typedef BOOLEAN ( WINAPI *pfnWinStationGetProcessSid )( HANDLE hServer, DWORD ProcessId , FILETIME ProcessStartTime , PBYTE pProcessUserSid , PDWORD dwSidSize );
typedef void ( WINAPI *pfnCachedGetUserFromSid )( PSID pSid , PWCHAR pUserName , PULONG cbUserName );
typedef BOOLEAN (WINAPI *pfnWinStationTerminateProcess)( HANDLE hServer, ULONG ProcessId, ULONG ExitCode);
typedef LRESULT (CALLBACK *ListView)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef NTSTATUS (_stdcall *pnNtQuerySystemInformation)(IN SYSTEM_INFORMATION_CLASS,OUT PVOID,IN ULONG,OUT PULONG);
//typedef PSID     (_stdcall *pnGetSiteSidFromToken)(HANDLE hToken);
typedef NTSTATUS (_stdcall *pnNtClose )(IN HANDLE);
typedef NTSTATUS (_stdcall *pnNtOpenThread)(HANDLE,DWORD,POBJECT_ATTRIBUTES,PCLIENT_ID);
typedef NTSTATUS (_stdcall *pnRtlLargeIntegerToChar)(LARGE_INTEGER*,ULONG,DWORD,LPVOID);
typedef NTSTATUS (_stdcall *pnRtlAnsiStringToUnicodeString)(PUNICODE_STRING,PCANSI_STRING, BOOLEAN);
typedef NTSTATUS (_stdcall *pnRtlUnicodeStringToInteger)(PUNICODE_STRING,DWORD,LPVOID);
typedef NTSTATUS (_stdcall *pnRtlTimeToElapsedTimeFields)(LARGE_INTEGER*,PTIME_FIELDS);
typedef VOID     (_stdcall *pnRtlInitUnicodeString) (PUNICODE_STRING,PCWSTR);
typedef NTSTATUS (_stdcall *pnNtQueryInformationToken)(HANDLE,DWORD,LPVOID,DWORD,PDWORD);
typedef LRESULT  (_stdcall *pnEndTask)(HWND,BOOL,BOOL);
typedef LRESULT  (_stdcall *pnRunFileDlg)(HWND,HICON,LPTSTR,LPTSTR,LPTSTR,UINT);
typedef BOOL     (_stdcall *pnIsHungAppWindow)(HWND);


//函数指针声明:
extern pfnWinStationGetProcessSid gpfnWinStationGetProcessSid;
extern pfnCachedGetUserFromSid gpfnCachedGetUserFromSid;
extern pfnWinStationTerminateProcess gpfnWinStationTerminateProcess;
extern ListView gfnListView;

extern pnNtQuerySystemInformation      NtQuerySystemInformation;
//extern pnGetSiteSidFromToken           GetSiteSidFromToken;
extern pnNtClose                       NtClose;
extern pnNtOpenThread                  NtOpenThread;
extern pnRtlLargeIntegerToChar         RtlLargeIntegerToChar;
extern pnRtlAnsiStringToUnicodeString  RtlAnsiStringToUnicodeString;
extern pnRtlUnicodeStringToInteger     RtlUnicodeStringToInteger;
extern pnRtlTimeToElapsedTimeFields    RtlTimeToElapsedTimeFields;
extern pnRtlInitUnicodeString          RtlInitUnicodeString;
extern pnNtQueryInformationToken       NtQueryInformationToken;
extern pnEndTask                       EndTask;
extern pnRunFileDlg                    RunFileDlg;
extern pnIsHungAppWindow               fpnIsHungAppWindow;
//------------------------------------------------------------------------------------------------------
PSID  WINAPI GetSiteSidFromToken(HANDLE hToken);

//------------------------------------------------------------------------------------------------------
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow);
static void __cdecl _initterm ( _PVFV * pfbegin,_PVFV * pfend );
BOOL   Mirror_IsEnabledOS( void );
void   LoadFunc(void);

//---------------------------------------------------加载函数部分-----------------------------------------
void   InitDavesControls();
void   ShowRunningInstance();
HMENU  LoadPopupMenu(HINSTANCE hinst, UINT id);
BOOL   LoadGlobalResources();
inline void MyShowWindow(HWND hwnd, UINT nShowCmd);
inline void MyDestroyWindow(HWND hwnd);
void   DisplayFailureMsg(HWND hWnd, UINT idTitle, DWORD dwError);
BOOL   CheckParentDeferrals(UINT uMsg, WPARAM wParam, LPARAM lParam);
void   SubclassListView(HWND hwnd);
void   inline _SetRectRgnIndirect(HRGN hrgn, LPRECT prc);
void   LV_GetViewRgn(HWND hwnd);

void   MainWnd_OnPaint(HWND hwnd);
void   MainWnd_Draw(HWND hwnd, HDC hdc);
BOOL   MainWnd_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void   MainWnd_OnSize(HWND hwnd, UINT state, int cx, int cy);
void   MainWnd_OnTimer(HWND hwnd, UINT id);
void   MainWnd_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags);
void   MainWnd_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
BOOL   MainWnd_OnTabCtrlNotify(LPNMHDR pnmhdr);
void   MainWnd_OnPrintClient(HWND hwnd, HDC hdc);

void   UpdateMenuStates();
void   SizeChildPage(HWND hwndMain);
void   UpdateStatusBar();
void   SetTitle();
DWORD  RunDlg();
//---------------------------------------------------回调函数部分-----------------------------------------
LRESULT DavesFrameWndProc(HWND hWnd, 
						  UINT msg, 
						  WPARAM wParam, 
						  LPARAM lParam);
INT_PTR CALLBACK MainWindowProc(
                HWND        hwnd,               // handle to dialog box
                UINT        uMsg,                   // message
                WPARAM      wParam,                 // first message parameter
                LPARAM      lParam                  // second message parameter
                );
LRESULT CALLBACK ListViewWndProc(
								 HWND hwnd, 
								 UINT msg, 
								 WPARAM wParam, 
								 LPARAM lParam);
//-----------------------------------------------------------------------------------------------------------
#include "Page.h"

//#include ".\main\TaskNot.h"
#include ".\main\TaskIcon.h"
#include ".\main\Option.h"
#include "PtrArray.h"