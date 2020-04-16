#include "taskmgr.h"

PSID  WINAPI GetSiteSidFromToken(HANDLE hToken)
{
	FARPROC RtlCopySid           =::GetProcAddress(::GetModuleHandle(_T("ntdll.dll")),"RtlCopySid");
	FARPROC RtlLengthSid         =::GetProcAddress(::GetModuleHandle(_T("ntdll.dll")),"RtlLengthSid");
	FARPROC RtlAllocateHeap      =::GetProcAddress(::GetModuleHandle(_T("ntdll.dll")),"RtlAllocateHeap");
	FARPROC RtlFreeHeap          =::GetProcAddress(::GetModuleHandle(_T("ntdll.dll")),"RtlFreeHeap");
	FARPROC RtlNtStatusToDosError=::GetProcAddress(::GetModuleHandle(_T("ntdll.dll")),"RtlNtStatusToDosError");
	FARPROC CompareMemory        =::GetProcAddress(::GetModuleHandle(_T("ntdll.dll")),"RtlCompareMemory");
	__asm{
		jmp _mainasm
	}
	__asm{
_mainasm:
	;push    ebp
	;mov     ebp, esp
	;sub     esp, 0x10
	push    ebx
	push    esi
	lea     eax, dword ptr [ebp-0x04]
    mov     esi, NtQueryInformationToken   ;  ntdll.ZwQueryInformationToken
	push    edi
	xor     ebx, ebx
	push    eax
	push    ebx
	push    ebx
	push    0x0B
	push    dword ptr [ebp+0x08]
	mov     dword ptr [ebp-0x08], ebx
	call    esi
	cmp     eax, 0xC0000023
	je L026
	push    eax
	call    _call8950
L020:
	xor     eax, eax
L021:
	pop     edi
	pop     esi
	pop     ebx
	leave
	retn    0x04
L026:
	mov     eax, dword ptr fs:[0x18]
	push    dword ptr [ebp-0x04]
	mov     eax, dword ptr [eax+0x30]
	push    ebx
	push    dword ptr [eax+0x18]
	call RtlAllocateHeap
	mov     edi, eax
	cmp     edi, ebx
	jnz L038
	push    0x0E
	call SetLastError
	jmp L020
L038:
	lea     eax, dword ptr [ebp-0x04]
	push    eax
	push    dword ptr [ebp-0x04]
	push    edi
	push    0x0B
	push    dword ptr [ebp+0x08]
	call    esi
	cmp     eax, ebx
	jl L105
	and     byte ptr [ebp-0x10], 0x00
	and     byte ptr [ebp-0x0F], 0x00
	and     byte ptr [ebp-0x0E], 0x00
	and     byte ptr [ebp-0x0D], 0x00
	and     byte ptr [ebp-0x0C], 0x00
	xor     esi, esi
	cmp     dword ptr [edi], ebx
	mov     byte ptr [ebp-0x0B], 0x07
	jbe L071
	lea     ebx, dword ptr [edi+0x04]
L057:
	lea     eax, dword ptr [ebp-0x10]
	push    0x06
	push    eax
	mov     eax, dword ptr [ebx]
	inc     eax
	inc     eax
	push    eax
	call    CompareMemory
	cmp     eax, 0x06
	je L079
	inc     esi
	add     ebx, 0x08
	cmp     esi, dword ptr [edi]
	jb L057
L071:
	mov     eax, dword ptr fs:[0x18]
	mov     eax, dword ptr [eax+0x30]
	push    edi
	push    0x00
	push    dword ptr [eax+0x18]
	call RtlFreeHeap
	mov     eax, dword ptr [ebp-0x08]
	jmp L021
L079:
	mov     eax, dword ptr fs:[0x18]
	push    dword ptr [edi+esi*0x08+0x04]
	mov     ebx, RtlLengthSid                            ;  ntdll.RtlLengthSid
	lea     esi, dword ptr [edi+esi*0x08+0x04]
	mov     dword ptr [ebp+0x08], eax
	call    ebx
	push    eax
	mov     eax, dword ptr [ebp+0x08]
	push    0x00
	mov     eax, dword ptr [eax+0x30]
	push    dword ptr [eax+0x18]
	call RtlAllocateHeap
	test    eax, eax
	mov     dword ptr [ebp-0x08], eax
	jnz L097
	push    0x0E
	call SetLastError
	jmp L071
L097:
	mov     esi, dword ptr [esi]
	push    esi
	push    eax
	push    esi
	call    ebx
	push    eax
	call RtlCopySid
	jmp L071
L105:
	push    eax
	call    _call8950
	jmp L071
	}

	_asm{
_call8950:
    push    esi
    push    dword ptr [esp+0x08]
    call    RtlNtStatusToDosError   ;  ntdll.RtlNtStatusToDosError
    mov     esi, eax
    push    esi                                      ; /Error
    call    SetLastError            ; \SetLastError
    mov     eax, esi
    pop     esi
    retn    0x04


	}
}