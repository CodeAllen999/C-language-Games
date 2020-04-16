#pragma once

//
// Process Page Column ID enumeration
//

typedef enum COLUMNID
{
    COL_IMAGENAME           = 0,
    COL_PID                 = 1,

    // _HYDRA

    COL_USERNAME            = 2,

    COL_SESSIONID           = 3,

    //
    COL_CPU                 = 4,
    COL_CPUTIME             = 5,
    COL_MEMUSAGE            = 6,
    COL_MEMPEAK             = 7,
    COL_MEMUSAGEDIFF        = 8,
    COL_PAGEFAULTS          = 9,
    COL_PAGEFAULTSDIFF      = 10,
    COL_COMMITCHARGE        = 11,
    COL_PAGEDPOOL           = 12,
    COL_NONPAGEDPOOL        = 13,
    COL_BASEPRIORITY        = 14,
    COL_HANDLECOUNT         = 15,
    COL_THREADCOUNT         = 16,
    COL_USEROBJECTS         = 17,
    COL_GDIOBJECTS          = 18,
    COL_READOPERCOUNT       = 19,
    COL_WRITEOPERCOUNT      = 20,
    COL_OTHEROPERCOUNT      = 21,
    COL_READXFERCOUNT       = 22,
    COL_WRITEXFERCOUNT      = 23,
    COL_OTHERXFERCOUNT      = 24
};

#define MAX_COLUMN      24
#define NUM_COLUMN      (MAX_COLUMN + 1)

#define IDS_FIRSTCOL    20001       // 20000 is first column name ID in rc file

// Possible values for the viewmode

typedef enum
{
    VM_LARGEICON,
    VM_SMALLICON,
    VM_DETAILS,
    VM_INVALID
} VIEWMODE;
#define VM_FIRST IDM_LARGEICONS
#define VM_LAST  IDM_DETAILS


// Possible values for the cpu history mode

typedef enum
{
    CM_SUM,
    CM_PANES
} CPUHISTMODE;
#define CM_FIRST IDM_ALLCPUS
#define CM_LAST  IDM_MULTIGRAPH

// Possible values for the update speed option

typedef enum
{
    US_HIGH,
    US_NORMAL,
    US_LOW,
    US_PAUSED
} UPDATESPEED;
#define US_FIRST IDM_HIGH
#define US_LAST  IDM_PAUSED

#include "..\ProcPage.h"

class COptions
{
public:

    DWORD       m_cbSize;
    DWORD       m_dwTimerInterval;
    VIEWMODE    m_vmViewMode;
    CPUHISTMODE m_cmHistMode;
    UPDATESPEED m_usUpdateSpeed;
    RECT        m_rcWindow;
    INT         m_iCurrentPage;

    COLUMNID    m_ActiveProcCol[NUM_COLUMN + 1];
    INT         m_ColumnWidths[NUM_COLUMN + 1];
    INT         m_ColumnPositions[NUM_COLUMN + 1];

    BOOL        m_fMinimizeOnUse    : 1;
    BOOL        m_fConfirmations    : 1;
    BOOL        m_fAlwaysOnTop      : 1;
    BOOL        m_fKernelTimes      : 1;
    BOOL        m_fNoTitle          : 1;
    BOOL        m_fHideWhenMin      : 1;
    BOOL        m_fShow16Bit        : 1;
    BOOL        m_fShowSandboxNames : 1;
    BOOL        bUnused;
    BOOL        bUnused2;
    BOOL        m_bShowAllProcess;

    HRESULT     Load();
    HRESULT     Save();

    // SetDefaultValues
    //
    // Uses to init the options to a default state when the saved copy
    // cannot be found, is damaged, or is not the correct version

    void SetDefaultValues()
    {
        ZeroMemory(this, sizeof(COptions));

        m_cbSize           = sizeof(COptions);

        BOOL bScreenReader = FALSE;
        if (SystemParametersInfo(SPI_GETSCREENREADER, 0, (PVOID) &bScreenReader, 0) && bScreenReader)
        {
            // No automatic updates for machines with screen readers
            m_dwTimerInterval = 0;
        }
        else
        {
            m_dwTimerInterval  = 1000;
        }

        m_vmViewMode       = VM_DETAILS;
        m_cmHistMode       = CM_PANES;
        m_usUpdateSpeed    = US_NORMAL;
        m_fMinimizeOnUse   = TRUE;
        m_fConfirmations   = TRUE;
        m_fAlwaysOnTop     = TRUE;
        m_fShow16Bit       = TRUE;
        m_fShowSandboxNames= TRUE;

        m_iCurrentPage     = -1;
        m_rcWindow.top     = 10;
        m_rcWindow.left    = 10;
        m_rcWindow.bottom  = 10 + g_minHeight;
        m_rcWindow.right   = 10 + g_minWidth;

        // Columns which are visible, by default, in the process view
        //#ifdef _HYDRA_

        m_bShowAllProcess = FALSE;

        if( IsTerminalServer( ) )
        {
            m_ActiveProcCol[ 0 ] = COL_IMAGENAME;
            
            m_ActiveProcCol[ 1 ] = COL_USERNAME;

            m_ActiveProcCol[ 2 ] = COL_SESSIONID;

            m_ActiveProcCol[ 3 ] = COL_PID;

            m_ActiveProcCol[ 4 ] = COL_CPU;

            m_ActiveProcCol[ 5 ] = COL_CPUTIME;

            m_ActiveProcCol[ 6 ] = COL_MEMUSAGE;

            m_ActiveProcCol[ 7 ] = (COLUMNID) -1;

        }
        else
        {
            m_ActiveProcCol[ 0 ] = COL_IMAGENAME;

            m_ActiveProcCol[ 1 ] = COL_PID;

            m_ActiveProcCol[ 2 ] = COL_CPU;

            m_ActiveProcCol[ 3 ] = COL_CPUTIME;

            m_ActiveProcCol[ 4 ] = COL_MEMUSAGE;

            m_ActiveProcCol[ 5 ] = (COLUMNID) -1;
        }
        //#endif _HYDRA_


        // Set all of the columns widths to -1

        FillMemory(m_ColumnWidths, sizeof(m_ColumnWidths), 0xFF);
        FillMemory(m_ColumnPositions, sizeof(m_ColumnPositions), 0xFF);
    }

    COptions()
    {
        SetDefaultValues();
    }
};

// GetLastHRESULT
//
// Little wrapper func that returns the GetLastError value as an HRESULT

inline HRESULT GetLastHRESULT()
{
    return HRESULT_FROM_WIN32(GetLastError());
}