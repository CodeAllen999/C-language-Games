#include "..\taskmgr.h"
#include "Option.h"

const TCHAR szTaskmanKey[] = TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\TaskManager");
const TCHAR szOptionsKey[] = TEXT("Preferences");
//--------------------------------------------------------------------------------------------------------------
/*++ COptions::Load

Routine Description:

   Loads current options to the registy
 
Arguments:

Returns:
    
    HRESULT

Revision History:

      Jan-01-95 Davepl  Created

--*/

HRESULT COptions::Load()
{
    HKEY  hkSave;

    // If ctrl-alt-shift is down at startup, "forget" registry settings

    if (GetKeyState(VK_SHIFT) < 0 &&
        GetKeyState(VK_MENU)  < 0 &&
        GetKeyState(VK_CONTROL) < 0   )
    {
        SetDefaultValues();
        return S_FALSE;
    }

    if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER,
                                      szTaskmanKey,
                                      0,
                                      KEY_READ,
                                      &hkSave))
    {
        return S_FALSE;
    }

    DWORD dwType;
    DWORD dwSize = sizeof(COptions);
    if (ERROR_SUCCESS       != RegQueryValueEx(hkSave,
                                               szOptionsKey,
                                               0,
                                               &dwType,
                                               (LPBYTE) this,
                                               &dwSize) 
        
        // Validate type and size of options info we got from the registry

        || dwType           != REG_BINARY 
        || dwSize           != sizeof(COptions)

        // Validate options, revert to default if any are invalid (like if
        // the window would be offscreen)

        || MonitorFromRect(&m_rcWindow, MONITOR_DEFAULTTONULL) == NULL
        || m_iCurrentPage    > NUM_PAGES - 1)

    {
        // Reset to default values

        SetDefaultValues();
        RegCloseKey(hkSave);
        return S_FALSE;
    }

    RegCloseKey(hkSave);

    // if machine is updated to/from terminal server
    // we might get wrong columns from the registry.
    // for example if machine was previously hydra and 
    // the last columns displayed contained username.
    // Afterwords hydra is uninstalled. Now when we 
    // load the columns next time we find username there
    // which should not be in case of non hydra systems.
    // lets take care of such situation here.
    // _HYDRA_
    if( !IsTerminalServer( ) )
    {
        // remove username, session id columns if present.

        for( int i = 0; i < NUM_COLUMN + 1 ; i++ )
        {
            if( g_Options.m_ActiveProcCol[ i ] == -1 )
            {
                // this is end of column list.

                break;  
            }

            if( g_Options.m_ActiveProcCol[ i ] == COL_SESSIONID || g_Options.m_ActiveProcCol[ i ] == COL_USERNAME )
            {
                // current values are not good as they contain hydra specific column
                // so lets set the default values.

                SetDefaultValues();

                break;
            }
        }

    }
    //_HYDRA_

    return S_OK;
}

HRESULT COptions::Save()
{
    DWORD dwDisposition;
    HKEY  hkSave;

    if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER,
                                        szTaskmanKey,
                                        0,
                                        TEXT("REG_BINARY"),
                                        REG_OPTION_NON_VOLATILE,
                                        KEY_WRITE,
                                        NULL,
                                        &hkSave,
                                        &dwDisposition))
    {
        return GetLastHRESULT();
    }

    if (ERROR_SUCCESS != RegSetValueEx(hkSave,
                                       szOptionsKey,
                                       0,
                                       REG_BINARY,
                                       (LPBYTE) this,
                                       sizeof(COptions)))
    {
        RegCloseKey(hkSave);
        return GetLastHRESULT();
    }

    RegCloseKey(hkSave);
    return S_OK;
}

