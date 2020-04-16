#pragma once

#ifndef WINVER				// 允许使用特定于 Windows XP 或更高版本的功能。
#define WINVER 0x0501		// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

#ifndef _WIN32_WINNT		// 允许使用特定于 Windows XP 或更高版本的功能。
#define _WIN32_WINNT 0x0501	// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif	

//加载头文件:
#include "windows.h"
#include "windowsx.h"

#include "htmlhelp.h"
#include "commctrl.h"
#include "shlobj.h"
#include "NTSecAPI.h"
#include "Stierr.h"
#include "vdmdbg.h"

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>

//加载LIB库:
#pragma comment(lib,"htmlhelp.lib")
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"VdmDbg.Lib")
#pragma comment(lib,"ksuser.lib")

//未公开类型声明:
typedef LONG KPRIORITY;
typedef short CSHORT;
typedef CCHAR *PCCHAR;
typedef CSHORT *PCSHORT;

//未公开结构声明:
#include "struct.h"

//系统类型声明:
#define OS_WINDOWS      0           // windows vs. NT
#define OS_NT           1           // windows vs. NT
#define OS_WIN95        2           // Win95 or greater
#define OS_NT4          3           // NT4 or greater
#define OS_NT5          4           // NT5 or greater
#define OS_MEMPHIS      5           // Win98 or greater
#define OS_MEMPHIS_GOLD 6           // Win98 Gold

//自定义消息:
#define PWM_TRAYICON    WM_USER + 10
#define PWM_ACTIVATE    WM_USER + 11
#define WM_FINDPROC       (WM_USER +1)
#define PM_NOTIFYWAITING  (WM_USER +2)
#define PM_QUITTRAYTHREAD (WM_USER +3)

//最大进程数:
#define   MAX_PROCESSOR   32
#define   HIST_SIZE       2000  

//-----------------------------------------声明变量------------------------------------------------------------------------

//=========================taskmgr.cpp===================================
extern HWND      g_hMainWnd;
extern HDESK     g_hMainDesktop;
extern HINSTANCE g_hInstance;
extern BYTE      g_cProcessors;

extern HANDLE    g_hTrayThread;
extern HICON     g_aTrayIcons[];
extern UINT      g_cTrayIcons;
extern DWORD     g_idTrayThread;

extern LONG      g_minWidth;
extern LONG      g_minHeight;

extern BOOL      g_fInPopup;
extern BOOL      g_fCantHide;

extern HACCEL    g_hAccel;
extern TCHAR     g_szK[];
extern TCHAR     g_szRealtime[];
extern TCHAR     g_szNormal[];
extern TCHAR     g_szHigh[];
extern TCHAR     g_szLow[];
extern TCHAR     g_szUnknown[];
extern TCHAR     g_szAboveNormal[];
extern TCHAR     g_szBelowNormal[];
extern TCHAR     g_szHung[];
extern TCHAR     g_szRunning[];
extern TCHAR     g_szfmtCPUNum[];
extern TCHAR     g_szfmtCPU[];
extern TCHAR     g_szTotalCPU[];
extern TCHAR     g_szKernelCPU[];
extern TCHAR     g_szMemUsage[];

extern HBITMAP   g_hbmpBack;
extern HBITMAP   g_hbmpForward;

extern HMENU     g_hMenu; 
extern LONG      g_DefSpacing;
extern LONG      g_InnerSpacing;
extern LONG      g_TopSpacing;
extern LONG      g_cxEdge;
extern HRGN      g_hrgnView;
extern HRGN      g_hrgnClip;

extern HBRUSH    g_hbrWindow;
extern HWND      g_hStatusWnd;
extern BOOL      g_fMenuTracking;
//----------------------------------------------------------------------------
// ASSERT(f)
//
//   Generates a "Assert file.c, line x (eval)" message if f is NOT true.
//
//   Use ASSERT() to check for logic invariance.  These are typically considered
//   fatal problems, and falls into the 'this should never ever happen' 
//   category.
//
//   Do *not* use ASSERT() to verify successful API calls if the APIs can 
//   legitimately fail due to low resources.  For example, LocalAlloc can 
//   legally fail, so you shouldn't assert that it will never fail.
//
//   The BF_ASSERT bit in g_dwBreakFlags governs whether the function 
//   performs a DebugBreak().
//
//   Default Behavior-
//      Retail builds:      nothing
//      Debug builds:       spew and break
//      Full debug builds:  spew and break
//
#ifdef DEBUG

BOOL CcshellAssertFailedA(LPCSTR szFile, int line, LPCSTR pszEval, BOOL bBreakInside);
BOOL CcshellAssertFailedW(LPCWSTR szFile, int line, LPCWSTR pwszEval, BOOL bBreakInside);
#ifdef UNICODE
#define CcshellAssertFailed     CcshellAssertFailedW
#else
#define CcshellAssertFailed     CcshellAssertFailedA
#endif

#define ASSERT(f)                                 \
    {                                             \
        DEBUGTEXT(szFile, TEXT(__FILE__));              \
        if (!(f) && CcshellAssertFailed(szFile, __LINE__, TEXT(#f), FALSE)) \
            DEBUG_BREAK;       \
    }

// The old Win95 code used to use "Assert()".  We discourage the use
// of this macro now because it is not msdev-friendly.
#ifdef DISALLOW_Assert
#define Assert(f)        Dont_use_Assert___Use_ASSERT
#else
#define Assert(f)           ASSERT(f)
#endif

#else  // DEBUG

#define ASSERT(f)
#define Assert(f)

#endif // DEBUG

//-----------------------------------------------------------------------------
//
// Verify
//

#if DEBUG
    
    #define VERIFY(x) Assert(x)
	  
#else   
    
    #define VERIFY(x) (x)

#endif
//-----------------------------------------------------------------------------
//  Member:     dprintf
//
//  Synopsis:   Dumps a printf style string to the debugger.
//
//  Notes:
//
//  History:    2-07-95   davepl   Created
//
//-----------------------------------------------------------------------------

#if DBG
#define DEBUG 1
#endif

#ifdef DEBUG

inline int dprintf(LPCTSTR szFormat, ...)
{
    TCHAR szBuffer[MAX_PATH];

    va_list  vaList;
    va_start(vaList, szFormat);

    int retval = wvsprintf(szBuffer, szFormat, vaList);
    OutputDebugString(szBuffer);

    va_end  (vaList);
    return retval;
}

#else

inline int dprintf(LPCTSTR, ...)
{
    return 0;
}

#endif
//---------------------------------------------------------------------------------------------

#ifndef ARRAYSIZE
    #define ARRAYSIZE(x) ((sizeof(x) / sizeof(x[0])))
#endif

//------------------------------------------------------------------------------------------------------

/*++ ShiftArrayWorker

Routine Description:

    Shifts a section of an array up or down.  If shifting
    down, the given element is lost.  For up, an empty slot
    (with an undefined value) is opened.

Arguments:

    pArray        - Array starting address
    cbArraySize   - Size of Array (in BYTES)
    cElementSize  - Size of array elements
    iFirstElement - First element to move
    Direction     - SHIFT_UP or SHIFT_DOWN

Return Value:

    None.  No error checking either.  Should compile out to
    a movememory

Notes:
    
    Call this with the ShiftArray macro which does the size
    calcs for you

Revision History:

    Jan-26-95 Davepl  Created

--*/

#define ShiftArray(array, index, direction) \
					    \
	ShiftArrayWorker((LPBYTE) array, sizeof(array), sizeof(array[0]), index, direction)

typedef enum SHIFT_DIRECTION { SHIFT_UP, SHIFT_DOWN };

static inline void ShiftArrayWorker(const LPBYTE          pArray, 
				    const size_t          cbArraySize, 
				    const size_t          cElementSize, 
				    const UINT            iFirstElement,
				    const SHIFT_DIRECTION Direction)
{
    ASSERT( ((cbArraySize / cElementSize) * cElementSize) == cbArraySize);
    ASSERT( (iFirstElement + 1) * cElementSize <= cbArraySize );

    const LPBYTE pFirst       = pArray + (iFirstElement * cElementSize);
    const LPBYTE pLast        = pArray + cbArraySize - cElementSize;
    const UINT   cBytesToMove = (UINT)(pLast - pFirst);

    ASSERT (pLast >= pFirst);

    if (cBytesToMove)
    {
	if (SHIFT_DOWN == Direction)
	{
	    CopyMemory(pFirst, pFirst + cElementSize, cBytesToMove);
	}    
	else
	{
	    ASSERT(Direction == SHIFT_UP);

	    CopyMemory(pFirst + cElementSize, pFirst, cBytesToMove);
	}
    }
}