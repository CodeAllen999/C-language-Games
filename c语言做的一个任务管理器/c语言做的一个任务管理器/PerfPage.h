#pragma once

#include "Page.h"

#define CPU_PENS 8
#define CUSTOM_PENS 1

#define MEM_PEN                0x08
#define NUM_PENS (CPU_PENS + CUSTOM_PENS)
#define GRAPH_BRUSH         BLACK_BRUSH

// WARNING: CPU pane IDs must be contiguous in resource.h
#define ID_FIRSTPANE IDC_CPUGRAPH
#define ID_LASTPANE  IDC_CPUGRAPH32
#define NUMPANES     32


extern BYTE                g_CPUUsage;
extern BYTE                g_KernelUsage;
extern DWORD               g_MEMUsage;
extern DWORD               g_MEMMax;
extern COLORREF            aColors[];
//--------------------------------------------------------------------------------------
// Size macros for the bitmap we use to draw LED digits

#define DIGITS_STRIP_WIDTH  96
#define DIGITS_STRIP_HEIGHT 11
#define DIGIT_WIDTH         8
#define DIGIT_HEIGHT        (DIGITS_STRIP_HEIGHT)
#define PERCENT_SIGN_INDEX  10  // Index into bitmap strip where % sign lives
#define K_INDEX             11  // Index into bitmap strip where "K" lives
#define BLANK_INDEX         12  // Index into bitmap where blank digit lives

#define ID_FIRSTPANE IDC_CPUGRAPH
#define ID_LASTPANE  IDC_CPUGRAPH32
#define NUMPANES     32

//#define GRAPH_BRUSH         BLACK_BRUSH
#define GRAPH_LINE_COLOR    RGB(0, 128, 64)

#define STRIP_HEIGHT        75
#define STRIP_WIDTH         33

#define RTL_MIRRORED_WINDOW             dwExStyleRTLMirrorWnd
#define RTL_NOINHERITLAYOUT             dwExStyleNoInheritLayout

//-----------------------------------------------------------------

class CPerfPage : public CPage
{
public:
	CPerfPage(void);
	~CPerfPage(void);
public:
    HWND        GetPageWindow()
    {
        return m_hPage;
    }
private:
    HWND        m_hPage;                    // Handle to this page's dlg
    HWND        m_hwndTabs;                 // Parent window
    HBITMAP     m_hDigits;                  // Digits bitmap
    HBITMAP     m_hStripUnlit;              // Digits bitmap
    HBITMAP     m_hStripLitRed;             // Digits bitmap
    HBITMAP     m_hStripLit;                // Digits bitmap
    HDC         m_hdcGraph;                 // Inmemory dc for cpu hist
    HBITMAP     m_hbmpGraph;                // Inmemory bmp for cpu hist
    HPEN        m_hPens[NUM_PENS];          // Our box of crayons
    RECT        m_rcGraph;
public:
    HRESULT     Initialize(HWND hwndParent);
    HRESULT     Activate();
    void        Deactivate();
    HRESULT     Destroy();
    void        GetTitle(LPTSTR pszText, size_t bufsize);
    void        SizePerfPage();
    void        TimerEvent();
    void		DrawLegend(LPDRAWITEMSTRUCT lpdi);
    void        DrawCPUGraph(LPDRAWITEMSTRUCT lpdi, UINT iPane);
    void        DrawMEMGraph(LPDRAWITEMSTRUCT lpdi);
    void        DrawCPUDigits(LPDRAWITEMSTRUCT lpdi);
    void        DrawMEMMeter(LPDRAWITEMSTRUCT lpdi);
    void        UpdateCPUHistory();
    void        FreeMemoryBitmaps();
    HRESULT     CreateMemoryBitmaps(int x, int y);
    void        SetTimer(HWND hwnd, UINT milliseconds);
    void        CreatePens();
    void        ReleasePens();
    void        UpdateGraphs();
    int         TextToLegend(HDC hDC, int xPos, int yPos, LPCTSTR szCPUName);
};


void ReleasePerfInfo();
BYTE InitPerfInfo();
void CalcCpuTime(BOOL fUpdateHistory);