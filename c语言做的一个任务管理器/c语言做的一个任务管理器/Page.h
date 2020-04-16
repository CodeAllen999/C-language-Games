#pragma once
#include "define.h"

#define TASK_PAGE   0
#define PROC_PAGE   1
#define PERF_PAGE   2
#define NUM_PAGES   3

class CTaskPage;
class CProcPage;
class CPerfPage;
class CPtrArray;

class CPage
{
public:
	CPage(void);
	~CPage(void);

public:
    // Sent when page is being created

    virtual HRESULT     Initialize(HWND hwndParent)                 PURE;
    
    // Sent when page is being displayed

    virtual HRESULT     Activate()                                  PURE;
    
    // Sent when page is being hidden
    
    virtual void        Deactivate()                                PURE;
    
    // Send when page is being shut down
    
    virtual HRESULT     Destroy()                                   PURE;
    
    // Returns the title of the page for use on the tab control

    virtual void        GetTitle(LPTSTR pszText, size_t bufsize)    PURE;
    
    // Returns the handle to the page's main dialog
    
    virtual HWND        GetPageWindow()                             PURE;

    // Sent when a timer event (update display) occurs

    virtual void        TimerEvent()                                PURE;

};

// THREADPARAM 
//
// Uses as a communication struct between task page and its worker thread

class THREADPARAM
{
public:

    WINSTAENUMPROC  m_lpEnumFunc;
    LPARAM          m_lParam;

    HANDLE          m_hEventChild;
    HANDLE          m_hEventParent;
    BOOL            m_fThreadExit;
    BOOL            m_fSuccess;

    THREADPARAM::THREADPARAM()
    {
        ZeroMemory(this, sizeof(THREADPARAM));
    }
};

// TASK_LIST_ENUM
//
// Object passed around during window enumeration

class TASK_LIST_ENUM 
{
public:
    CPtrArray *     m_pTasks;
    LPTSTR          lpWinsta;
    LPTSTR          lpDesk;
    LARGE_INTEGER   uPassCount;
    CTaskPage *     m_pPage;

    TASK_LIST_ENUM()
    {
        ZeroMemory(this, sizeof(TASK_LIST_ENUM));
    }
};
typedef TASK_LIST_ENUM *PTASK_LIST_ENUM;

// CSysInfo
//
// Some misc global info about the system

class CSysInfo
{
public:

    // These fields MUST all be DWORDS because we manually index into
    // them individually in procperf.cpp
        
    DWORD   m_cHandles;
    DWORD   m_cThreads;
    DWORD   m_cProcesses;
    DWORD   m_dwPhysicalMemory;
    DWORD   m_dwPhysAvail;
    DWORD   m_dwFileCache;
    DWORD   m_dwKernelPaged;
    DWORD   m_dwKernelNP;
    DWORD   m_dwKernelTotal;
    DWORD   m_dwCommitTotal;
    DWORD   m_dwCommitLimit;
    DWORD   m_dwCommitPeak;

    CSysInfo()
    {
        ZeroMemory(this, sizeof(CSysInfo));
    }
};

#include "TaskPage.h"
#include "ProcPage.h"
#include "PerfPage.h"
#include "PtrArray.h"
