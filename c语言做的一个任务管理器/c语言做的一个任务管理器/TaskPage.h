#pragma once

#include "Page.h"
#include "PtrArray.h"
#include ".\main\Option.h"

class CTaskPage : public CPage
{
public:
	CTaskPage(void);
	virtual ~CTaskPage(void);

private:

    HWND        m_hPage;                    // Handle to this page's dlg
    HWND        m_hwndTabs;                 // Parent window
    CPtrArray * m_pTaskArray;               // Array of active tasks
    BOOL        m_fPaused;                  // BOOL, is display refresh paused for menu
    HIMAGELIST  m_himlSmall;                // Image lists
    HIMAGELIST  m_himlLarge;
    VIEWMODE    m_vmViewMode;               // Large or small icon mode
    UINT        m_cSelected;                // Count of items selected
    THREADPARAM m_tp;
    HANDLE      m_hEventChild;                   
    HANDLE      m_hEventParent;
    HANDLE      m_hThread;

protected:
    void    RemoveAllTasks();
    HRESULT LoadDefaultIcons();

public:
    HRESULT     Initialize(HWND hwndParent);
    HRESULT     Activate();
    void        Deactivate();
    HRESULT     Destroy();
    void        GetTitle(LPTSTR pszText, size_t bufsize);
    void        TimerEvent();

    HWND        GetPageWindow()
    {
        return m_hPage;
    }

    void        SizeTaskPage();
    HRESULT     SetupColumns();
    void        GetRunningTasks(TASK_LIST_ENUM * te);
    void        HandleWMCOMMAND(INT id);
    
    HRESULT     UpdateTaskListview();
    INT         HandleTaskPageNotify(HWND hWnd, LPNMHDR pnmhdr);
    void        HandleTaskListContextMenu(INT xPos, INT yPos);
    BOOL        CreateNewDesktop();
    CPtrArray * GetSelectedTasks();
    void        UpdateUIState();
    HWND      * GetHWNDS(BOOL fSelectedOnly, DWORD * pdwCount);
    void        EnsureWindowsNotMinimized(HWND aHwnds[], DWORD dwCount);
    BOOL        DoEnumWindowStations(WINSTAENUMPROC lpEnumFunc, LPARAM lParam);

    void OnSettingsChange();
    
    void        Pause()
    {
                m_fPaused = TRUE;
    }        

    void        Unpause()
    {
                m_fPaused = FALSE;
    }

    // The dialog proc needs to be able to set the m_hPage member, so
    // make it a friend

    friend INT_PTR CALLBACK TaskPageProc(
                HWND        hwnd,   	        // handle to dialog box
                UINT        uMsg,	            // message
                WPARAM      wParam,	            // first message parameter
                LPARAM      lParam 	            // second message parameter
                );

    // The enum callback needs to get at our imagelists as it encounters
    // new tasls, so it can add their icons to the lists

    friend BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

};

//----------------------------------------------------------------------------------------------------------------------
/*++ class CTaskInfo

Class Description:

    Represents the last known information about a running task

Arguments:

Return Value:

Revision History:

      Nov-29-95 Davepl  Created

--*/

class CTaskInfo
{
public:

    HWND            m_hwnd;
    LPTSTR          m_pszWindowTitle;
    LPTSTR          m_lpWinsta;
    LPTSTR          m_lpDesktop;
    BOOL            m_fHung;
    LARGE_INTEGER   m_uPassCount;
    INT             m_iSmallIcon;
    HICON           m_hSmallIcon;
    INT             m_iLargeIcon;
    HICON           m_hLargeIcon;

    //
    // This is a union of which attribute is dirty.  You can look at
    // or set any particular column's bit, or just inspect m_fDirty
    // to see if anyone at all is dirty.  Used to optimize listview
    // painting
    //

    union
    {
        DWORD                m_fDirty;
        struct 
        {
            DWORD            m_fDirty_COL_HWND           :1;
            DWORD            m_fDirty_COL_TITLE          :1;
            DWORD            m_fDirty_COL_STATUS         :1;
            DWORD            m_fDirty_COL_WINSTA         :1;
            DWORD            m_fDirty_COL_DESKTOP        :1;
        };                                                
    };

    HRESULT        SetData(HWND                         hwnd,
                           LPTSTR                       lpTitle,
                           LPTSTR                       lpWinsta,
                           LPTSTR                       lpDesktop,
                           LARGE_INTEGER                uPassCount,
                           BOOL                         fUpdateOnly);

    CTaskInfo()
    {
        ZeroMemory(this, sizeof(*this));
    }

    ~CTaskInfo()
    {
        if (m_pszWindowTitle)
        {
            LocalFree(m_pszWindowTitle);
        }

        if (m_lpWinsta)
        {
            LocalFree(m_lpWinsta);
        }

        if (m_lpDesktop)
        {
            LocalFree(m_lpDesktop);
        }
    }

    INT Compare(CTaskInfo * pOther);

};


//
// Column ID enumeration
//

typedef enum TASKCOLUMNID
{
    COL_TASKNAME            = 0,
    COL_TASKSTATUS          = 1,
    COL_TASKWINSTATION      = 2,
    COL_TASKDESKTOP         = 3,
};

#define MAX_TASK_COLUMN      3
#define NUM_TASK_COLUMN      (MAX_TASK_COLUMN + 1)

#define IDS_FIRSTTASKCOL    21000       // 21000 is first column name ID in rc file

//----------------------------------------------------------------------------------------------------------------------
extern DWORD       g_cTasks;
//----------------------------------------------------------------------------------------------------------------------


DWORD WorkerThread(LPVOID pv);


BOOL CALLBACK EnumWindowStationsFunc(LPTSTR  lpstr, LPARAM lParam);
BOOL CALLBACK EnumDesktopsFunc(LPTSTR  lpstr, LPARAM lParam);
BOOL CALLBACK EnumWindowsProc(HWND    hwnd, LPARAM   lParam);
INT_PTR CALLBACK TaskPageProc(
                HWND        hwnd,               // handle to dialog box
                UINT        uMsg,                   // message
                WPARAM      wParam,                 // first message parameter
                LPARAM      lParam                  // second message parameter
                );