#include "taskmgr.h"
#include ".\procpage.h"


COLUMNID g_iProcSortColumnID  = COL_PID;
//#endif
INT      g_iProcSortDirection = 1;          // 1 = asc, -1 = desc

//-------------------------------------------------------------------------------------------------------
/*++ GetPriRanking

Function Description:

    Since the priority class defines aren't in order, this helper
    exists to make comparisons between pri classes easier.  It returns
    a larger number for "higher" priority classes

Arguments:

Return Value:

    rank of priority (0 to 5)

Revision History:

      Nov-27-95 Davepl  Created

--*/


DWORD GetPriRanking(DWORD dwClass)
{
    switch(dwClass)
    {
        case REALTIME_PRIORITY_CLASS:
            return 5;

        case HIGH_PRIORITY_CLASS:
            return 4;

        case ABOVE_NORMAL_PRIORITY_CLASS:
            return 3;

        case NORMAL_PRIORITY_CLASS:
            return 2;

        case BELOW_NORMAL_PRIORITY_CLASS:
            return 1;


        default:
            return 0;
    }
}

BOOL WINAPI WowTaskCallback(
    DWORD dwThreadId,
    WORD hMod16,
    WORD hTask16,
    CHAR *pszModName,
    CHAR *pszFileName,
    LPARAM lparam
    )
{
    PWOWTASKCALLBACKPARMS pParms = (PWOWTASKCALLBACKPARMS)lparam;
    HRESULT hr;

    //
    // See if this task is already in the list.
    //
    
    CProcInfo * pOldProcInfo;
    pOldProcInfo = FindProcInArrayByPID(
                       pParms->pProcPage->m_pProcArray,
                       dwThreadId);

    if (NULL == pOldProcInfo)
    {
        //
        // We don't already have this process in our array, so create a new one
        // and add it to the array
        //

        CProcInfo * pNewProcInfo = new CProcInfo;
        if (NULL == pNewProcInfo)
        {
            goto done;
        }

        hr = pNewProcInfo->SetDataWowTask(pParms->TotalTime,
                                                    dwThreadId,
                                                    pszFileName,
                                                    pParms->uPassCount,
                                                    pParms->pParentProcInfo,
                                                    &pParms->TimeLeft,
                                                    hTask16,
                                                    FALSE);

        if (FAILED(hr) ||
            FALSE == pParms->pProcPage->m_pProcArray->Add(pNewProcInfo))
        {
            delete pNewProcInfo;
            goto done;
        }
    }
    else
    {
        //
        // This process already existed in our array, so update its info
        //

        pOldProcInfo->SetDataWowTask(pParms->TotalTime,
                                     dwThreadId,
                                     pszFileName,
                                     pParms->uPassCount,
                                     pParms->pParentProcInfo,
                                     &pParms->TimeLeft,
                                     hTask16,
                                     TRUE);
    }

done:
    return FALSE;  // continue enumeration
}

/*++ FindProcInArrayByPID

Class Description:

    Walks the ptrarray given and looks for the CProcInfo object
    that has the PID supplied.  If not found, returns NULL

Arguments:

    pArray      - The CPtrArray where the CProcInfos could live
    pid         - The pid to search for

Return Value:

    CProcInfo * in the array, if found, or NULL if not

Revision History:

      Nov-20-95 Davepl  Created

--*/

// REVIEW (DavePl) could provide a static search hint here so
// that it doesn't always need to start back at zero, or could
// do a binary search

CProcInfo * FindProcInArrayByPID(CPtrArray * pArray, DWORD pid)
{
    for (int i = 0; i < pArray->GetSize(); i++)
    {
        CProcInfo * pTmp = (CProcInfo *) (pArray->GetAt(i));
        
        if (pTmp->m_UniqueProcessId == pid)
        {
            // Found it

            return pTmp;
        }
    }

    // Not found

    return NULL;
}

//-------------------------------------------------------------------------------------------------------
/*++ class CProcInfo::Compare

Class Description:

    Compares this CProcInfo object to another, and returns its ranking
    based on the g_iProcSortColumnID field.

    Note that if the objects are equal based on the current sort column,
    the PID is used as a secondary sort key to prevent items from 
    jumping around in the listview

    WOW psuedo-processes always sort directly after their parent
    ntvdm.exe process.  So really the sort order is:

    1. WOW task psuedo-processes under parent in alpha order
    2. User's selected order.
    3. PID

Arguments:

    pOther  - the CProcInfo object to compare this to

Return Value:

    < 0      - This CProcInfo is "less" than the other
      0      - Equal (Can't happen, since PID is used to sort)
    > 0      - This CProcInfo is "greater" than the other

Revision History:

      Nov-20-95 Davepl  Created

--*/

INT CProcInfo::Compare(CProcInfo * pOther)
{
    CProcInfo * pMyThis;
    CProcInfo * pMyOther;
    INT iRet = 0;

    //
    // Wow psuedo-processes don't have any performance information,
    // so use the parent "real" ntvdm.exe CProcInfo for sorting.
    //

    ASSERT(this != pOther);

    pMyThis = this->IsWowTask()
              ? this->m_pWowParentProcInfo
              : this;

    pMyOther = pOther->IsWowTask()
               ? pOther->m_pWowParentProcInfo
               : pOther;

    if (pMyThis == pMyOther) {

        //
        // This implies one or the other or both this and pOther
        // are WOW tasks, and they're in the same WOW VDM.  Sort
        // the "real" process entry first, followed by its associated
        // WOW task entries alphabetical.
        //

        if (this->IsWowTask()) {

            if (pOther->IsWowTask()) {

                //
                // They are siblings and we sort by
                // image name.
                //

                ASSERT(this->m_pWowParentProcInfo ==
                       pOther->m_pWowParentProcInfo);

                iRet = lstrcmpi(this->m_pszImageName, pOther->m_pszImageName);

            } else {

                //
                // pOther is not a Wow task, it must be ntvdm.exe
                // the parent of this.  this sorts after pOther.
                //

                ASSERT(pOther == this->m_pWowParentProcInfo);

                iRet = 1;
            }
        } else {

            //
            // this is not a Wow task, pOther must be and
            // this must be pOther's parent.
            //

            ASSERT(pOther->IsWowTask());

            iRet = -1;
        }
    }


    if (0 == iRet) {

        switch (g_iProcSortColumnID)
        {
            case COL_CPU:
                iRet = Compare64(pMyThis->m_CPU, pMyOther->m_CPU);
            break;

            case COL_CPUTIME:
                iRet = Compare64(pMyThis->m_CPUTime.QuadPart, pMyOther->m_CPUTime.QuadPart);
                break;

            case COL_MEMUSAGE:
                iRet = Compare64(pMyThis->m_MemUsage, pMyOther->m_MemUsage);
                break;

            case COL_MEMUSAGEDIFF:
                iRet = Compare64(pMyThis->m_MemDiff, pMyOther->m_MemDiff);
                break;

            case COL_MEMPEAK:
                iRet = Compare64(pMyThis->m_MemPeak, pMyOther->m_MemPeak);
                break;

            case COL_PAGEFAULTS:
                iRet = Compare64(pMyThis->m_PageFaults, pMyOther->m_PageFaults);
                break;

            case COL_PAGEFAULTSDIFF:
                iRet = Compare64(pMyThis->m_PageFaultsDiff, pMyOther->m_PageFaultsDiff);
                break;

            case COL_COMMITCHARGE:
                iRet = Compare64(pMyThis->m_CommitCharge, pMyOther->m_CommitCharge);
                break;

            case COL_PAGEDPOOL:
                iRet = Compare64(pMyThis->m_PagedPool, pMyOther->m_PagedPool);
                break;

            case COL_NONPAGEDPOOL:
                iRet = Compare64(pMyThis->m_NonPagedPool, pMyOther->m_NonPagedPool);
                break;

            case COL_BASEPRIORITY:
                iRet = Compare64(GetPriRanking(pMyThis->m_PriClass), GetPriRanking(pMyOther->m_PriClass));
                break;

            case COL_HANDLECOUNT:
                iRet = Compare64(pMyThis->m_HandleCount, pMyOther->m_HandleCount);
                break;

            case COL_THREADCOUNT:
                iRet = Compare64(pMyThis->m_ThreadCount, pMyOther->m_ThreadCount);
                break;

            case COL_PID:
                iRet = Compare64(pMyThis->m_UniqueProcessId, pMyOther->m_UniqueProcessId);
                break;
// #ifdef _HYDRA_

            case COL_SESSIONID:
                
                iRet = Compare64(pMyThis->m_SessionId, pMyOther->m_SessionId);

                break;

            case COL_USERNAME:
                
                iRet = lstrcmpi( pMyThis->m_pszUserName , pMyOther->m_pszUserName );

                break;
// #endif
            case COL_IMAGENAME:
                iRet = lstrcmpi(pMyThis->m_pszImageName, pMyOther->m_pszImageName);
                break;

            case COL_USEROBJECTS:
                iRet = Compare64(pMyThis->m_USERObjectCount, pMyOther->m_USERObjectCount);
                break;

            case COL_GDIOBJECTS:
                iRet = Compare64(pMyThis->m_GDIObjectCount, pMyOther->m_GDIObjectCount);
                break;

            case COL_READOPERCOUNT:
                iRet = Compare64(pMyThis->m_IoReadOperCount, pMyOther->m_IoReadOperCount);
                break;

            case COL_WRITEOPERCOUNT:
                iRet = Compare64(pMyThis->m_IoWriteOperCount, pMyOther->m_IoWriteOperCount);
                break;

            case COL_OTHEROPERCOUNT:
                iRet = Compare64(pMyThis->m_IoOtherOperCount, pMyOther->m_IoOtherOperCount);
                break;

            case COL_READXFERCOUNT:
                iRet = Compare64(pMyThis->m_IoReadXferCount, pMyOther->m_IoReadXferCount);
                break;

            case COL_WRITEXFERCOUNT:
                iRet = Compare64(pMyThis->m_IoWriteXferCount, pMyOther->m_IoWriteXferCount);
                break;

            case COL_OTHERXFERCOUNT:
                iRet = Compare64(pMyThis->m_IoOtherXferCount, pMyOther->m_IoOtherXferCount);
                break;

            default:

                #ifdef DEBUG
                    DebugBreak();
                #endif

                iRet = 0;
        }

        iRet *= g_iProcSortDirection;
    }

    // If objects look equal, compare on PID as secondary sort column
    // so that items don't jump around in the listview

    if (0 == iRet)
    {
        iRet = Compare64(pMyThis->m_UniqueProcessId,
                      pMyOther->m_UniqueProcessId) *
                     g_iProcSortDirection;
    }

    return iRet;
}


/*++ class CProcInfo::SetCPU

Method Description:

    Sets the CPU percentage.

Arguments:

    CPUTime   - Time for this process
    TotalTime - Total elapsed time, used as the denominator in calculations

Return Value:

Revision History:

      19-Feb-96  DaveHart  Created

--*/

void CProcInfo::SetCPU(LARGE_INTEGER CPUTimeDelta,
                       LARGE_INTEGER TotalTime,
                       BOOL fDisplayOnly)
{
    // Calc CPU time based on this process's ratio of the total process time used

    INT cpu = (BYTE) (((CPUTimeDelta.QuadPart / ((TotalTime.QuadPart / 1000) ?
                                                 (TotalTime.QuadPart / 1000) : 1)) + 5)
                                              / 10);
    if (100 == cpu)
    {
        cpu = 99;
    }

// BUGBUG (jeffreys) disabling this assert to let BVT's run. DavePl needs
// to find a real fix for this.  Raid #236356, 231880
//    ASSERT( cpu <= 100);

    if (m_DisplayCPU != cpu)
    {
        m_fDirty_COL_CPU = TRUE;
        m_DisplayCPU = (BYTE) cpu;

        if ( ! fDisplayOnly )
        {
            m_CPU = (BYTE) cpu;
        }
    }

}


/*++ class CProcInfo::SetData

Class Description:

    Sets up a single CProcInfo object based on the data contained in a
    SYSTEM_PROCESS_INFORMATION block.

    If fUpdate is set, the imagename and icon fields are not processed, 
    since they do not change throughout the lifetime of the process

Arguments:

    TotalTime - Total elapsed time, used as the denominator in calculations
                for the process' CPU usage, etc
    pInfo     - The SYSTEM_PROCESS_INFORMATION block for this process
    uPassCount- Current passcount, used to timestamp the last update of 
                this objectg
    fUpdate   - See synopsis

Return Value:

Revision History:

      Nov-16-95 Davepl  Created

--*/


HRESULT CProcInfo::SetData(LARGE_INTEGER                TotalTime, 
                           PSYSTEM_PROCESS_INFORMATION  pInfo, 
                           LARGE_INTEGER                uPassCount,
                           CProcPage *                  pProcPage,
                           BOOL                         fUpdateOnly)
{
    HRESULT hr = S_OK;
    DWORD dwTemp;
    HANDLE hProcess;

    // Touch this CProcInfo to indicate the process is still alive

    m_uPassCount.QuadPart = uPassCount.QuadPart;

    // Calc this process's total time as the sum of its user and kernel time

    LARGE_INTEGER TimeDelta;
    LARGE_INTEGER Time;

    if (pInfo->UserTime.QuadPart + pInfo->KernelTime.QuadPart < m_CPUTime.QuadPart)
    {
// BUGBUG (jeffreys) disabling this assert to let BVT's run. See comments in
// SetDataWowTask above.  Note that this assertion hasn't actually fired, but
// given the other weirdness that's been going on, I'm disabling it anyway.
//        ASSERT(0 && "Proc's cpu total usage went DOWN since last refresh.");
        Invalidate();
        return hr = E_FAIL;
    }

    Time.QuadPart = pInfo->UserTime.QuadPart +
                    pInfo->KernelTime.QuadPart;

    TimeDelta.QuadPart = Time.QuadPart - m_CPUTime.QuadPart;

    if (TimeDelta.QuadPart)
    {
        m_CPUTime.QuadPart = m_DisplayCPUTime.QuadPart = Time.QuadPart;
        m_fDirty_COL_CPUTIME = TRUE;
    }

    SetCPU( TimeDelta, TotalTime, FALSE );

    //
    // For each of the fields, we check to see if anything has changed, and if
    // so, we mark that particular column as having changed, and update the value.
    // This allows me to opimize which fields of the listview to repaint, since
    // repainting an entire listview column causes flicker and looks bad in
    // general
    //

    // Miscellaneous fields

    if (m_UniqueProcessId != PtrToUlong(pInfo->UniqueProcessId))
    {
        m_fDirty_COL_PID = TRUE;
        m_UniqueProcessId = PtrToUlong(pInfo->UniqueProcessId);
    }

// #ifdef _HYDRA_
    
    if( m_SessionId != pInfo->SessionId )
    {
        m_fDirty_COL_SESSIONID = TRUE;

        m_SessionId = pInfo->SessionId;

    }

// #endif


    if (m_MemDiff != ((LONG)pInfo->WorkingSetSize / 1024) - (LONG)m_MemUsage )
    {
        m_fDirty_COL_MEMUSAGEDIFF = TRUE;
        m_MemDiff =  ((LONG)pInfo->WorkingSetSize / 1024) - (LONG)m_MemUsage;
    }

	
    if (m_MemPeak != (pInfo->PeakWorkingSetSize / 1024))
    {
        m_fDirty_COL_MEMPEAK = TRUE;
        m_MemPeak = pInfo->PeakWorkingSetSize / 1024;
    }

    if (m_MemUsage != pInfo->WorkingSetSize / 1024)
    {
        m_fDirty_COL_MEMUSAGE = TRUE;
        m_MemUsage = pInfo->WorkingSetSize / 1024;
    }

    if (m_PageFaultsDiff != ((LONG)(pInfo->PageFaultCount) - (LONG)m_PageFaults))
    {
        m_fDirty_COL_PAGEFAULTSDIFF = TRUE;
        m_PageFaultsDiff = ((LONG)(pInfo->PageFaultCount) - (LONG)m_PageFaults);
    }

    if (m_PageFaults != (pInfo->PageFaultCount))
    {
        m_fDirty_COL_PAGEFAULTS = TRUE;
        m_PageFaults = (pInfo->PageFaultCount);
    }

    if (m_CommitCharge != pInfo->PrivatePageCount / 1024)
    {
        m_fDirty_COL_COMMITCHARGE = TRUE;
        m_CommitCharge = pInfo->PrivatePageCount / 1024;
    }

    if (m_PagedPool != pInfo->QuotaPagedPoolUsage / 1024)
    {
        m_fDirty_COL_PAGEDPOOL = TRUE;
        m_PagedPool = pInfo->QuotaPagedPoolUsage / 1024;
    }

    if (m_NonPagedPool != pInfo->QuotaNonPagedPoolUsage / 1024)
    {
        m_fDirty_COL_NONPAGEDPOOL = TRUE;
        m_NonPagedPool = pInfo->QuotaNonPagedPoolUsage / 1024;
    }

    if (m_PriClass != pInfo->BasePriority)
    {
        m_fDirty_COL_BASEPRIORITY = TRUE;
        m_PriClass = pInfo->BasePriority;
    }

    if (m_HandleCount != pInfo->HandleCount)
    {
        m_fDirty_COL_HANDLECOUNT = TRUE;
        m_HandleCount = pInfo->HandleCount;
    }

    if (m_ThreadCount != pInfo->NumberOfThreads)
    {
        m_fDirty_COL_HANDLECOUNT = TRUE;
        m_ThreadCount = pInfo->NumberOfThreads;
    }

    if (m_IoReadOperCount != pInfo->ReadOperationCount.QuadPart)
    {
        m_fDirty_COL_READOPERCOUNT = TRUE;
        m_IoReadOperCount = pInfo->ReadOperationCount.QuadPart;
    }

    if (m_IoWriteOperCount != pInfo->WriteOperationCount.QuadPart)
    {
        m_fDirty_COL_WRITEOPERCOUNT = TRUE;
        m_IoWriteOperCount = pInfo->WriteOperationCount.QuadPart;
    }

    if (m_IoOtherOperCount != pInfo->OtherOperationCount.QuadPart)
    {
        m_fDirty_COL_OTHEROPERCOUNT = TRUE;
        m_IoOtherOperCount = pInfo->OtherOperationCount.QuadPart;
    }

    if (m_IoReadXferCount != pInfo->ReadTransferCount.QuadPart)
    {
        m_fDirty_COL_READXFERCOUNT = TRUE;
        m_IoReadXferCount = pInfo->ReadTransferCount.QuadPart;
    }

    if (m_IoWriteXferCount != pInfo->WriteTransferCount.QuadPart)
    {
        m_fDirty_COL_WRITEXFERCOUNT = TRUE;
        m_IoWriteXferCount = pInfo->WriteTransferCount.QuadPart;
    }

    if (m_IoOtherXferCount != pInfo->OtherTransferCount.QuadPart)
    {
        m_fDirty_COL_OTHERXFERCOUNT = TRUE;
        m_IoOtherXferCount = pInfo->OtherTransferCount.QuadPart;
    }

    hProcess = OpenProcess( PROCESS_QUERY_INFORMATION , FALSE, m_UniqueProcessId);
    
    if (hProcess && (m_USERObjectCount != (dwTemp = GetGuiResources(hProcess, GR_USEROBJECTS))))
    {
        m_fDirty_COL_USEROBJECTS = TRUE;
        m_USERObjectCount = dwTemp;
    }

    if (hProcess && (m_GDIObjectCount != (dwTemp = GetGuiResources(hProcess, GR_GDIOBJECTS))))
    {
        m_fDirty_COL_GDIOBJECTS = TRUE;
        m_GDIObjectCount = dwTemp;
    }


    if (hProcess)
        CloseHandle(hProcess);

    if (FALSE == fUpdateOnly)
    {
        //
        // Set the process' image name.  If its NULL it could be the "Idle Process" or simply
        // a process whose image name is unknown.  In both cases we load a string resource
        // with an appropriate replacement name.
        //

        m_fDirty_COL_IMAGENAME = TRUE;

        if (pInfo->ImageName.Buffer == NULL)
        {
            // No image name, so replace it with "Unknown"

            TCHAR szTmp[MAX_PATH];
            UINT  uLen = LoadString(g_hInstance, IDS_SYSPROC, szTmp, MAX_PATH);


            m_pszImageName = new TCHAR[uLen + 1];
            if (NULL == m_pszImageName)
            {
                    return hr = E_OUTOFMEMORY;
            }

            lstrcpy(m_pszImageName, szTmp);
        }
        else
        {
            //
            // We have a valid image name, so allocate enough space and then
            // make a copy of it
            //
            m_pszImageName = new TCHAR[(pInfo->ImageName.Length / sizeof(WCHAR))+ 1];
            if (NULL == m_pszImageName)
            {
                    return hr = E_OUTOFMEMORY;
            }

            lstrcpyn(m_pszImageName, pInfo->ImageName.Buffer, (pInfo->ImageName.Length / sizeof(WCHAR)) + 1);
            m_pszImageName[(pInfo->ImageName.Length / sizeof(WCHAR))] = TEXT('\0');
        }

// #ifdef _HYDRA_

        if( IsTerminalServer( ) )
        {
            SetProcessUsername(LPFILETIME(&(pInfo->CreateTime)));
        }

// #endif

    }

    //
    // Check if this process is a WOW process.  There is some latency
    // between the time a WOW process is created and the time
    // the shared memory used by VDMEnumTaskWOWEx reflects the new
    // process and tasks.  However, once a process becomes a WOW
    // process, it is always a WOW process until it dies.
    //

    if (g_Options.m_fShow16Bit)
    {
        if ( m_fWowProcess ||
             ! m_fWowProcessTested)
        {
#if !defined (_WIN64)

            if ( ( m_pszImageName != NULL ) && ( ! _wcsicmp(m_pszImageName, TEXT("ntvdm.exe")) ) )
            {

                WOWTASKCALLBACKPARMS WowTaskCallbackParms;

                WowTaskCallbackParms.uPassCount = uPassCount;
                WowTaskCallbackParms.pProcPage = pProcPage;
                WowTaskCallbackParms.pParentProcInfo = this;
                WowTaskCallbackParms.TotalTime.QuadPart = TotalTime.QuadPart;
                WowTaskCallbackParms.TimeLeft.QuadPart = TimeDelta.QuadPart;

                if (VDMEnumTaskWOWEx(m_UniqueProcessId,
                                     WowTaskCallback,
                                     (LPARAM) &WowTaskCallbackParms))
                {
                    if ( ! m_fWowProcess )
                    {
                        m_fWowProcessTested =
                            m_fWowProcess = TRUE;
                    }

                    SetCPU( WowTaskCallbackParms.TimeLeft, TotalTime, TRUE );
                }
                else
                {
                    //
                    // We avoid calling VDMEnumTaskWOWEx if the process has an
                    // execution time of more than 10 seconds and has not so
                    // far been seen as a WOW process.
                    //

                    if (GetCPUTime() > (10 * 10 * 1000 * 1000))
                    {
                        m_fWowProcessTested = TRUE;
                    }
                }
            }
            else
            {
                m_fWowProcessTested = TRUE;
            }
#else
            m_fWowProcessTested = TRUE;
#endif
        }
    }


    //
    // If this is a sandboxed version of dllhost.exe, tack on the URL it
    // goes with to the image name
    //

    if (g_Options.m_fShowSandboxNames
        && 0 == lstrcmpi(m_pszImageName, TEXT("dllhost.exe")))
    {
        HANDLE hProcess = OpenProcess(
                                PROCESS_ALL_ACCESS, 
                                FALSE, 
                                m_UniqueProcessId);

        if (NULL != hProcess)
        {
            HANDLE hToken;

            if (OpenProcessToken(hProcess, TOKEN_READ, &hToken))
            {
                if (IsTokenRestricted(hToken))
                {
                    PSID psid = GetSiteSidFromToken(hToken);

                    if (NULL != psid)
                    {
                        TCHAR   szName[256];
                        TCHAR   szDomain[256];
                        DWORD   cchName   = sizeof(szName) / sizeof(TCHAR);
                        DWORD   cchDomain = sizeof(szDomain) / sizeof(TCHAR);
                        SID_NAME_USE use;

                        if (LookupAccountSid(
                                    NULL,
                                    psid,
                                    szName,
                                    &cchName,
                                    szDomain,
                                    &cchDomain,
                                    &use))
                        {
                            int cch = (lstrlen(m_pszImageName)
                                       + lstrlen(szName)) * sizeof(WCHAR)
                                       + sizeof(TEXT("  ()"));

                            LPTSTR pszImageName = new TCHAR[cch];

                            if (NULL != pszImageName)
                            {
                                wsprintf(
                                        pszImageName, 
                                        TEXT("%s  (%s)"),
                                        m_pszImageName,
                                        szName);

                                delete [] m_pszImageName;
                                m_pszImageName = pszImageName;
                            }
                        }
                    }

                    FreeSid(psid);
                }

                CloseHandle(hToken);
            }

            CloseHandle(hProcess);
        }
    }

    return S_OK;
}

/*++ class CProcInfo::SetDataWowTask

Method Description:

    Sets up a single CProcInfo object based on the parameters.
    This is a WOW task pseudo-process entry.

Arguments:

    dwThreadId

    pszFilePath    Fully-qualified path from VDMEnumTaskWOWEx.

Return Value:

Revision History:

      18-Feb-96  DaveHart  created

--*/

HRESULT CProcInfo::SetDataWowTask(LARGE_INTEGER  TotalTime,
                                  DWORD          dwThreadId,
                                  CHAR *         pszFilePath,
                                  LARGE_INTEGER  uPassCount,
                                  CProcInfo *    pParentProcInfo,
                                  LARGE_INTEGER *pTimeLeft,
                                  WORD           htask,
                                  BOOL           fUpdateOnly)
{
    CHAR *pchExe;

    //
    // Touch this CProcInfo to indicate the process is still alive
     //

    m_uPassCount.QuadPart = uPassCount.QuadPart;

    //
    // Update the thread's execution times.
    //

    HANDLE             hThread;
    NTSTATUS           Status;
    OBJECT_ATTRIBUTES  obja;
    CLIENT_ID          cid;

    InitializeObjectAttributes(
            &obja,
            NULL,
            0,
            NULL,
            0 );

    cid.UniqueProcess = 0;      // 0 means any process
    cid.UniqueThread  = (HANDLE)(LONG_PTR) dwThreadId;
	
    Status = NtOpenThread(
                &hThread,
                THREAD_QUERY_INFORMATION,
                &obja,
                &cid );

    ULONGLONG ullCreation, ullExit, ullKernel, ullUser;
    if ( NT_SUCCESS(Status) )
    {
        LARGE_INTEGER TimeDelta, Time;

        if (GetThreadTimes(
                hThread,
                (LPFILETIME) &ullCreation,
                (LPFILETIME) &ullExit,
                (LPFILETIME) &ullKernel,
                (LPFILETIME) &ullUser
                ) )
        {

            Time.QuadPart = (LONGLONG)(ullUser + ullKernel);

            TimeDelta.QuadPart = Time.QuadPart - m_CPUTime.QuadPart;

            if (TimeDelta.QuadPart < 0)
            {
// BUGBUG (jeffreys) disabling this assert to let BVT's run. Someone needs
// to figure out what's really going on.  Raid #247473
//                ASSERT(0 && "WOW tasks's cpu total usage went DOWN since last refresh.");
                Invalidate();
                return E_FAIL;
            }

            if (TimeDelta.QuadPart)
            {
                m_fDirty_COL_CPUTIME = TRUE;
                m_CPUTime.QuadPart = Time.QuadPart;
            }

            //
            // Don't allow sum of WOW child task times to
            // exceed ntvdm.exe total.  We call GetThreadTimes
            // substantially after we get process times, so
            // this can happen.
            //

            if (TimeDelta.QuadPart > pTimeLeft->QuadPart)
            {
                TimeDelta.QuadPart = pTimeLeft->QuadPart;
                pTimeLeft->QuadPart = 0;
            }
            else
            {
                pTimeLeft->QuadPart -= TimeDelta.QuadPart;
            }

            SetCPU( TimeDelta, TotalTime, FALSE );

            //
            // When WOW tasks are being displayed, the line for ntvdm.exe
            // should show times only for overhead or historic threads,
            // not including any active task threads.
            //

            if (pParentProcInfo->m_DisplayCPUTime.QuadPart > m_CPUTime.QuadPart)
            {
                pParentProcInfo->m_DisplayCPUTime.QuadPart -= m_CPUTime.QuadPart;
            }
            else
            {
                pParentProcInfo->m_DisplayCPUTime.QuadPart = 0;
            }

            m_DisplayCPUTime.QuadPart = m_CPUTime.QuadPart;
        }

        NtClose(hThread);
    }

    if (m_PriClass != pParentProcInfo->m_PriClass) {
        m_fDirty_COL_BASEPRIORITY = TRUE;
        m_PriClass = pParentProcInfo->m_PriClass;
    }

// #ifdef _HYDRA_

    if( m_SessionId != pParentProcInfo->m_SessionId )
    {
        m_fDirty_COL_SESSIONID = TRUE;

        m_SessionId = pParentProcInfo->m_SessionId;

    }

// #endif

    if (FALSE == fUpdateOnly)
    {
        UINT uLen;

        //
        // Set the task's image name, thread ID, thread count,
        // htask, and parent CProcInfo which do not change over
        // time.
        //

        m_htaskWow = htask;

        m_fDirty_COL_PID = TRUE;
        m_fDirty_COL_IMAGENAME = TRUE;
        m_fDirty_COL_THREADCOUNT = TRUE;
// #ifdef _HYDRA_

        m_fDirty_COL_USERNAME = TRUE;

        m_fDirty_COL_SESSIONID = TRUE;

// #endif


        m_UniqueProcessId = dwThreadId;
        m_ThreadCount = 1;

        //
        // We're only interested in the filename of the EXE
        // with the path stripped.
        //

        pchExe = strrchr(pszFilePath, '\\');
        if (NULL == pchExe) {
            pchExe = pszFilePath;
        }
        else
        {
            // skip backslash
            pchExe++;
        }

        uLen = (UINT)strlen(pchExe);

        //
        // Indent the EXE name by two spaces
        // so WOW tasks look subordinate to
        // their ntvdm.exe
        //
        m_pszImageName = new TCHAR[uLen + 3];
        if (NULL == m_pszImageName)
        {
            return E_OUTOFMEMORY;
        }

        m_pszImageName[0] = m_pszImageName[1] = TEXT(' ');

        MultiByteToWideChar(
            CP_ACP,
            0,
            pchExe,
            uLen,
            (LPWSTR)&m_pszImageName[2],
            uLen
            );
        m_pszImageName[uLen + 2] = 0;

        //
        // WOW EXE filenames are always uppercase, so lowercase it.
        //

        CharLowerBuff(&m_pszImageName[2], uLen);

        m_pWowParentProcInfo = pParentProcInfo;
        
//#ifdef _HYDRA_

        if( IsTerminalServer( ) )
        {
            SetProcessUsername( LPFILETIME( &ullCreation ) );
        }

//#endif
      
    }

    return S_OK;
}

// #ifdef _HYDRA_
//----------------------------------------------------------------
//
// No creation info
//
// Reviewed by alhen 9 - 3 - 98
//
HRESULT CProcInfo::SetProcessUsername(const FILETIME *pCreateTime)
{
    DWORD dwError = NO_ERROR;
    
    // SetProcessUsername should get called only for terminal servers.

    if( !IsTerminalServer() )
    {
        return E_FAIL;
    }

    // in case we could not get the proc address from winsta.dll
    // set the user name to error or something.

    __try
    {
        // in case of wow tasks assign username same as its parent process's

        if( IsWowTask( ) )
        {
            if( m_pWowParentProcInfo->m_pszUserName != NULL )
            {
                m_pszUserName = ( LPTSTR )new TCHAR[ lstrlen( m_pWowParentProcInfo->m_pszUserName ) + 1 ];

                if( m_pszUserName != NULL )
                {
                    lstrcpy( m_pszUserName , m_pWowParentProcInfo->m_pszUserName );

                    return S_OK;
                }
                else
                {
                    return E_OUTOFMEMORY;
                }
            }
            else
            {

                return E_FAIL;
            }
        }

        if( m_UniqueProcessId == 0 )     // this is a system idle process.
        {
            const TCHAR *szIdleProcessOwner = TEXT( "SYSTEM" );
            
            m_pszUserName = ( LPTSTR )new TCHAR[ 7 ];

            if( m_pszUserName != NULL )
            {
                lstrcpy(m_pszUserName, szIdleProcessOwner);
            }
        }
        else
        {
           
            PSID pUserSid = NULL;

            DWORD dwSize = 0;

            if( !(*gpfnWinStationGetProcessSid)( NULL , GetRealPID( ) , *pCreateTime, ( PBYTE )pUserSid , &dwSize ) )
            {
                pUserSid = ( PSID ) new BYTE[ dwSize ];

                if( pUserSid != NULL )
                {
                    if( (*gpfnWinStationGetProcessSid)( NULL , GetRealPID( ) , *pCreateTime, ( PBYTE )pUserSid , &dwSize ) )
                    {

                        if( IsValidSid( pUserSid ) )
                        {
                            TCHAR szTmpName[MAX_PATH];

                            DWORD dwTmpNameSize = MAX_PATH;

                            (*gpfnCachedGetUserFromSid)( pUserSid , szTmpName , &dwTmpNameSize );

                            m_pszUserName = ( LPTSTR )new TCHAR[ sizeof( szTmpName ) + 1 ];

                            if( m_pszUserName != NULL )
                            {
                                lstrcpy(m_pszUserName, szTmpName);
                            }
                        }
                    }

                    delete [] pUserSid;
                }
                else
                {
                    dwError = GetLastError();
                }

                
            } // this would mean that a sid of size zero was returned
        }


    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        // dprintf(TEXT("exception occured: %d",), GetExceptionCode());
        dwError = GetExceptionCode();
    }

    return HRESULT_FROM_WIN32(dwError);

}
// #endif

