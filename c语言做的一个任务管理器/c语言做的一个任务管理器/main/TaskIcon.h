#pragma once

#include "TaskNot.h"

//extern CRITICAL_SECTION    g_CSTrayThread;
//----------------------------------------------º¯ÊýÉùÃ÷-------------------------------------------------
DWORD TrayThreadMessageLoop(LPVOID);
void  Tray_Notify(HWND hWnd, WPARAM wParam, LPARAM lParam);
void  Tray_NotifyIcon(HWND    hWnd,
                     UINT    uCallbackMessage,
                     DWORD   Message,
                     HICON   hIcon,            
                     LPCTSTR lpTip);
BOOL DeliverTrayNotification(CTrayNotification * pNot);