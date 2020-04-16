#pragma once

// CTrayNotification
//
// Class to encapsulate all of the info needed to do a tray notification

class CTrayNotification
{
public:

    CTrayNotification()
    {
        ASSERT(0 && "Some bozo is using the default constuctor for CTrayNotification");
        ZeroMemory(this, sizeof(*this));
    }

    CTrayNotification(HWND    hWnd,
                      UINT    uCallbackMessage,
                      DWORD   Message,
                      HICON   hIcon,
                      LPTSTR  pszTip)
    {
        m_hWnd              = hWnd;
        m_uCallbackMessage  = uCallbackMessage;
        m_Message           = Message;
        m_hIcon             = hIcon;

        if (pszTip)
            lstrcpyn(m_szTip, pszTip, ARRAYSIZE(m_szTip));
        else
            m_szTip[0] = TEXT('\0');
    }

    HWND    m_hWnd;
    UINT    m_uCallbackMessage;
    DWORD   m_Message;
    HICON   m_hIcon;
    TCHAR   m_szTip[MAX_PATH];
};