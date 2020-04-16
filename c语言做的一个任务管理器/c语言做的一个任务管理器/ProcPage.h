#pragma once

#include "Page.h"
#include "PtrArray.h"
#include ".\main\Option.h"

//---------------------------------------------------------------------------------------------
class CProcPage;
class CProcInfo;

#define MAX_TASKS 4096

inline DWORD GetCurrentSessionID( );
inline VOID  SetCurrentSessionID( DWORD dwSessionId );

typedef struct
{
    LARGE_INTEGER               uPassCount;
    CProcPage *                 pProcPage;
    CProcInfo *                 pParentProcInfo;
    LARGE_INTEGER               TotalTime;
    LARGE_INTEGER               TimeLeft;
} WOWTASKCALLBACKPARMS, *PWOWTASKCALLBACKPARMS;

extern  INT         g_iProcSortDirection;
extern	COLUMNID    g_iProcSortColumnID;
extern  int         g_aDlgColIDs[];
extern  DWORD       g_cProcesses;
//---------------------------------------------------------------------------------------------

class CProcPage : public CPage
{
public:
	CProcPage(void);
	~CProcPage(void);
private:
    HWND        m_hPage;                    // Handle to this page's dlg
    HWND        m_hwndTabs;                 // Parent window
    CPtrArray * m_pProcArray;               // Ptr array of running processes
    LPVOID      m_pvBuffer;                 // Buffer for NtQuerySystemInfo
    size_t      m_cbBuffer;                 // Size of the above buffer, in bytes
    CSysInfo    m_SysInfo;
    BOOL        m_fPaused;                  // Updates paused (during trackpopupmenu)
    LPTSTR      m_pszDebugger;              // Debugger command in registry
    TCHAR       m_szTimeSep[8];
    WCHAR       m_wszGroupSep[8];
    WCHAR       m_wszGroupThousSep[8]; 

public:

    typedef struct _TASK_LIST {
        DWORD       dwProcessId;
        DWORD       dwInheritedFromProcessId;
        ULARGE_INTEGER CreateTime;
        BOOL        flags;
    } TASK_LIST, *PTASK_LIST;
public:
    // Constructor
    void OnSettingsChange()
    {
        GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIME, m_szTimeSep, ARRAYSIZE(m_szTimeSep));
        GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SGROUPING, m_wszGroupSep, ARRAYSIZE(m_wszGroupSep));
        GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_STHOUSAND, m_wszGroupThousSep, ARRAYSIZE(m_wszGroupThousSep));
    }
    HWND        GetPageWindow()
    {
        return m_hPage;
    }
public:

    HRESULT     Initialize(HWND hwndParent);
    HRESULT     Activate();
    void        Deactivate();
    HRESULT     Destroy();
    void        GetTitle(LPTSTR pszText, size_t bufsize);
    void        TimerEvent();

    void        PickColumns();
    void        SaveColumnWidths();
    void        SizeProcPage();
    HRESULT     SetupColumns();
    HRESULT     UpdateProcInfoArray();
    HRESULT     UpdateProcListview();
    HRESULT     GetProcessInfo();
    INT         HandleProcPageNotify(HWND, LPNMHDR);
    void        HandleProcListContextMenu(INT xPos, INT yPos);
    CProcInfo * GetSelectedProcess();
    //void        HandleWMCOMMAND(INT id);
    void        HandleWMCOMMAND( WORD , HWND );
    BOOL        IsSystemProcess(DWORD pid, CProcInfo * pProcInfo);
    BOOL        KillProcess(DWORD pid, BOOL bBatch = FALSE);
    BOOL        SetPriority(DWORD pid, DWORD idCmd);
    BOOL        AttachDebugger(DWORD pid);
    UINT        QuickConfirm(UINT idTitle, UINT idBody);
    BOOL        SetAffinity(DWORD pid);

    BOOL        RecursiveKill(DWORD pid);
    void        WalkUpTaskTree(DWORD pid, DWORD Array[], PDWORD NArray, PTASK_LIST  pTask, DWORD n);
    void        SetupToKillChildren(DWORD id, TASK_LIST * pTask, DWORD dwNumTasks);
    DWORD       GetTaskListEx(TASK_LIST * pTask, DWORD dwNumTasks);
    BOOL        DetectOrphans(TASK_LIST * pTask, DWORD dwNumTasks);
private:
    void Int64ToCommaSepString(LONGLONG n, LPTSTR pszOut, int cchOut);
    void Int64ToCommaSepKString(LONGLONG n, LPTSTR pszOut, int cchOut);
public:
    void RememberColumnOrder(HWND hwndList);
    void RestoreColumnOrder(HWND hwndList);

public:
    // The dialog proc needs to be able to set the m_hPage member, so
    // make it a friend

    friend INT_PTR CALLBACK ProcPageProc(
                HWND        hwnd,   	        // handle to dialog box
                UINT        uMsg,	            // message
                WPARAM      wParam,	            // first message parameter
                LPARAM      lParam 	            // second message parameter
                );

    // The WOW task callback proc needs to be able to get m_pProcArray,
    // so make it a friend.

    friend BOOL WINAPI WowTaskCallback(
                           DWORD dwThreadId,
                           WORD hMod16,
                           WORD hTask16,
                           PSZ pszModName,
                           PSZ pszFileName,
                           LPARAM lparam
                           );
};
//--------------------------------------------------------------------------------------------------------------
/*++ class CProcInfo

Class Description:

    Represents the last known information about a running process

Arguments:

Return Value:

Revision History:

      Nov-16-95 Davepl  Created

--*/

class CProcInfo
{
public:

    LARGE_INTEGER     m_uPassCount;
    DWORD             m_UniqueProcessId;
// #ifdef _HYDRA_
    LPTSTR            m_pszUserName;
    ULONG             m_SessionId;
// #endif
    BYTE              m_CPU;
    BYTE              m_DisplayCPU;
    LARGE_INTEGER     m_CPUTime;
    LARGE_INTEGER     m_DisplayCPUTime;
    ULONG             m_MemUsage;
    LONG              m_MemDiff;
    ULONG             m_PageFaults;
    LONG              m_PageFaultsDiff;
    ULONG_PTR         m_CommitCharge;
    ULONG_PTR         m_PagedPool;
    ULONG_PTR         m_NonPagedPool;
    KPRIORITY         m_PriClass;
    ULONG             m_HandleCount;
    ULONG             m_ThreadCount;
    ULONG             m_GDIObjectCount;
    ULONG             m_USERObjectCount;
    LONGLONG          m_IoReadOperCount;
    LONGLONG          m_IoWriteOperCount;
    LONGLONG          m_IoOtherOperCount;
    LONGLONG          m_IoReadXferCount;
    LONGLONG          m_IoWriteXferCount;
    LONGLONG          m_IoOtherXferCount;
    LPTSTR            m_pszImageName;
    CProcInfo *       m_pWowParentProcInfo;    // non-NULL for WOW tasks
    WORD              m_htaskWow;              // non-zero for WOW tasks
    BOOL              m_fWowProcess:1;         // TRUE for real WOW process
    BOOL              m_fWowProcessTested:1;   // TRUE once fWowProcess is valid
    ULONG             m_MemPeak;


    //
    // This is a union of who (which column) is dirty.  You can look at
    // or set any particular column's bit, or just inspect m_fDirty
    // to see if anyone at all is dirty.  Used to optimize listview
    // painting
    //

    union
    {
        DWORD                m_fDirty;
        struct
        {
            DWORD            m_fDirty_COL_CPU            :1;
            DWORD            m_fDirty_COL_CPUTIME        :1;
            DWORD            m_fDirty_COL_MEMUSAGE       :1;
            DWORD            m_fDirty_COL_MEMUSAGEDIFF   :1;
            DWORD            m_fDirty_COL_PAGEFAULTS     :1;
            DWORD            m_fDirty_COL_PAGEFAULTSDIFF :1;
            DWORD            m_fDirty_COL_COMMITCHARGE   :1;
            DWORD            m_fDirty_COL_PAGEDPOOL      :1;
            DWORD            m_fDirty_COL_NONPAGEDPOOL   :1;
            DWORD            m_fDirty_COL_BASEPRIORITY   :1;
            DWORD            m_fDirty_COL_HANDLECOUNT    :1;
            DWORD            m_fDirty_COL_IMAGENAME      :1;
            DWORD            m_fDirty_COL_PID            :1;
// #ifdef _HYDRA_
            DWORD            m_fDirty_COL_SESSIONID      :1;
            DWORD            m_fDirty_COL_USERNAME       :1;
// #endif
            DWORD            m_fDirty_COL_THREADCOUNT    :1;
            DWORD            m_fDirty_COL_GDIOBJECTS     :1;
            DWORD            m_fDirty_COL_USEROBJECTS    :1;
            DWORD            m_fDirty_COL_MEMPEAK        :1;
            DWORD            m_fDirty_COL_READOPERCOUNT  :1;
            DWORD            m_fDirty_COL_WRITEOPERCOUNT :1;
            DWORD            m_fDirty_COL_OTHEROPERCOUNT :1;
            DWORD            m_fDirty_COL_READXFERCOUNT  :1;
            DWORD            m_fDirty_COL_WRITEXFERCOUNT :1;
            DWORD            m_fDirty_COL_OTHERXFERCOUNT :1;
        };
    };

    HRESULT SetData(LARGE_INTEGER                TotalTime,
                    PSYSTEM_PROCESS_INFORMATION   pInfo,
                    LARGE_INTEGER                uPassCount,
                    CProcPage *                  pProcPage,
                    BOOL                         fUpdateOnly);

//#ifdef _HYDRA_
    HRESULT SetProcessUsername(const FILETIME *CreationTime);
//#endif

    HRESULT SetDataWowTask(LARGE_INTEGER  TotalTime,
                           DWORD          dwThreadId,
                           CHAR *         pszFilePath,
                           LARGE_INTEGER  uPassCount,
                           CProcInfo *    pParentProcInfo,
                           LARGE_INTEGER *pTimeLeft,
                           WORD           htask,
                           BOOL           fUpdateOnly);

    CProcInfo()
    {
        ZeroMemory(this, sizeof(*this));

// #ifdef _HYDRA_

        m_pszUserName = 0;

        m_SessionId = 832;

// #endif
    }

    ~CProcInfo()
    {
        if (m_pszImageName)
        {
            delete [] m_pszImageName;
        }

// #ifdef _HYDRA_

        if( m_pszUserName != NULL )
        {
            delete [] m_pszUserName;
        }
// #endif

    }

    BOOL OkToShowThisProcess ()
    {
        // this function determines if the process should be listed in the view.

        return GetCurrentSessionID() == m_SessionId;
    }


    // Invalidate() marks this proc with a bogus pid so that it is removed
    // on the next cleanup pass

    void Invalidate()
    {
        m_UniqueProcessId = PtrToUlong(INVALID_HANDLE_VALUE);
    }

    LONGLONG GetCPUTime() const
    {
        return m_CPUTime.QuadPart;
    }

    INT Compare(CProcInfo * pOther);

    //
    // Is this a WOW task psuedo-process?
    //

    INT_PTR IsWowTask(void) const
    {
        return (INT_PTR) m_pWowParentProcInfo;
    }

    //
    // Get the Win32 PID for this task
    //

    DWORD GetRealPID(void) const
    {
        return m_pWowParentProcInfo
               ? m_pWowParentProcInfo->m_UniqueProcessId
               : m_UniqueProcessId;
    }

    void SetCPU(LARGE_INTEGER CPUTimeDelta,
                LARGE_INTEGER TotalTime,
                BOOL          fDisplayOnly);
};

//--------------------------------------------------------------------------------------------------------------
DWORD       GetPriRanking(DWORD dwClass);
BOOL        IsTerminalServer();
BOOL        ValidateProductSuite();
int         Compare64(unsigned __int64 First, unsigned __int64 Second);
CProcInfo * FindProcInArrayByPID(CPtrArray * pArray, DWORD pid);
BOOL        TestUserForAdmin( VOID );
BOOL        IsUserAdmin( );
NTSTATUS    MyMoBettaRtlInt64ToUnicodeString (IN LONGLONG Value,IN ULONG Base OPTIONAL,IN OUT PUNICODE_STRING String);

//-------------------------------------------------------»Øµ÷º¯Êý------------------------------------------------
INT_PTR CALLBACK ProcPageProc(
                HWND        hwnd,               // handle to dialog box
                UINT        uMsg,                   // message
                WPARAM      wParam,                 // first message parameter
                LPARAM      lParam                  // second message parameter
                );
BOOL WINAPI WowTaskCallback(
    DWORD dwThreadId,
    WORD hMod16,
    WORD hTask16,
    CHAR *pszModName,
    CHAR *pszFileName,
    LPARAM lparam);
INT_PTR CALLBACK ColSelectDlgProc(
								  HWND hwndDlg, 
								  UINT uMsg, 
								  WPARAM wParam, 
								  LPARAM lParam);
INT_PTR CALLBACK AffinityDlgProc(
								 HWND hwndDlg, 
								 UINT uMsg, 
								 WPARAM wParam, 
								 LPARAM lParam);

