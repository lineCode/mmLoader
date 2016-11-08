//
// This file is generated by the mmLoaderShellCode Generator
// https://github.com/tishion
//
#ifndef __MMLOADERSHELLCODE_H_INCLUDED_
#define __MMLOADERSHELLCODE_H_INCLUDED_
#pragma once
#include <windows.h>

/// <summary>
/// Function table. These function will be used in the mmLoader.
/// </summary>
typedef struct __NTFUNCPTRS
{
	LPVOID pfnCreateFileW;			// CreateFileW
	LPVOID pfnGetFileSize;			// GetFileSize
	LPVOID pfnCreateFileMappingW;	// CreateFileMappingW
	LPVOID pfnMapViewOfFile;		// MapViewOfFile
	LPVOID pfnUnmapViewOfFile;		// UnmapViewOfFile
	LPVOID pfnCloseHandle;			// CloseHandle
	LPVOID pfnGetModuleHandleA;		// GetModuleHandleA
	LPVOID pfnLoadLibraryA;			// LoadLibraryA
	LPVOID pfnGetProcAddress;		// GetProcAddress
	LPVOID pfnVirtualAlloc;			// VirtualAlloc
	LPVOID pfnVirtualFree;			// VirtualFree
	LPVOID pfnVirtualProtect;		// VirtualProtect
	LPVOID pfnReversed_0;
	LPVOID pfnReversed_1;
	LPVOID pfnReversed_2;
	LPVOID pfnReversed_3;
	LPVOID pfnReversed_4;
} NTFUNCPTRSTABLE, *PNTFUNCPTRSTABLE;

/// <summary>
/// Represents the memory module instance.
/// </summary>
typedef struct __MEMMODULE
{
	union								// MemModule base
	{
		ULONGLONG ulBase;
		HMODULE	hModule;
		LPVOID	lpBase;
		PIMAGE_DOS_HEADER pImageDosHeader;
	};
	DWORD dwSizeOfImage;				// MemModule size
	DWORD dwCrc;						// MemModule crc32
	DWORD dwPageSize;					// System page size

	BOOL  bLoadOk;						// MemModule is load ok?

	PNTFUNCPTRSTABLE pNtFuncptrsTable;	// Pointer to NT function pointers table 

	struct								// Raw file resource data
	{
		HANDLE	h;
		HANDLE	hMapping;
		LPVOID	pBuffer;
	} RawFile;

	WCHAR wszModuleName[MAX_PATH];		// MemModule Name (or full file path name)
   __MEMMODULE()
	{
		ulBase = 0;
		dwSizeOfImage = 0;
		dwCrc = 0;
		bLoadOk = 0;
		pNtFuncptrsTable = 0;
		RawFile.h = 0;
		RawFile.hMapping = 0;
		RawFile.pBuffer = 0;

		SYSTEM_INFO sysInfo;
		::GetNativeSystemInfo(&sysInfo);
		dwPageSize = sysInfo.dwPageSize;
		for (int i = 0; i < MAX_PATH; i++) wszModuleName[i] = 0;
	}
} MEM_MODULE, *PMEM_MODULE;

/// <summary>
/// Enums for MemModuleHelper.
/// </summary>
typedef enum _MMHELPER_METHOD
{
	MHM_BOOL_LOAD,
	MHM_VOID_FREE,
	MHM_FARPROC_GETPROC,
} MMHELPER_METHOD;

/// <summary>
/// Type of the MemModuleHlper function.
/// </summary>
typedef LPVOID(__stdcall * Type_MemModuleHelper)(PMEM_MODULE, MMHELPER_METHOD, LPCWSTR, LPCSTR, BOOL);

/************************************************************************\
 *
 * Auxiliary Function:
 *		use the mmLoader through this function after it is loaded from shell code.
 *
 * Parameters:
 *		pMmeModule:
 *
 *		method:
 *			Function to be used
 *
 *		lpModuleName:
 *			name of the module to be loaded, only valid when method == MHM_BOOL_LOAD
 *			
 *		lpProcName:
 *			name of the proc to be retrieved, only valid when MHM_FARPROC_GETPROC
 *			
 *		bCallEntry:
 *			need to call the module entry point?
 *
 *	return value:
 *		when method == MHM_BOOL_LOAD
 *			return the resulT of loading, TRUE or FALSE
 *
 *		when method MHM_VOID_FREE:
 *			no return value
 *
 *		when method == MHM_FARPROC_GETPROC
 *			return the address of the target proc, return NULL when failed to get the address
 *
 *
 *
\************************************************************************/

/// <summary>
/// The byte array of the mmLoader shell code.
/// </summary>
unsigned char mmLoaderShellCode[] =
{
	0x55, 0x8B, 0xEC, 0x51, 0x8B, 0x45, 0x0C, 0x89, 0x45, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 0x74, 0x0E, 
	0x83, 0x7D, 0xFC, 0x01, 0x74, 0x1D, 0x83, 0x7D, 0xFC, 0x02, 0x74, 0x22, 0xEB, 0x2F, 0x8B, 0x4D, 
	0x18, 0x51, 0x8B, 0x55, 0x10, 0x52, 0x8B, 0x45, 0x08, 0x50, 0xE8, 0x31, 0x00, 0x00, 0x00, 0xEB, 
	0x1E, 0xEB, 0x1A, 0x8B, 0x4D, 0x08, 0x51, 0xE8, 0xC4, 0x01, 0x00, 0x00, 0xEB, 0x0F, 0x8B, 0x55, 
	0x14, 0x52, 0x8B, 0x45, 0x08, 0x50, 0xE8, 0x85, 0x01, 0x00, 0x00, 0xEB, 0x02, 0x33, 0xC0, 0x8B, 
	0xE5, 0x5D, 0xC2, 0x14, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0x7D, 0x08, 0x00, 0x74, 0x0F, 0x8B, 0x45, 0x08, 0x83, 0x78, 0x18, 0x00, 
	0x74, 0x06, 0x83, 0x7D, 0x0C, 0x00, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0x3F, 0x01, 0x00, 0x00, 0x8B, 
	0x4D, 0x08, 0x51, 0x8B, 0x55, 0x0C, 0x52, 0xE8, 0xA4, 0x01, 0x00, 0x00, 0x83, 0xC4, 0x08, 0x85, 
	0xC0, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0x24, 0x01, 0x00, 0x00, 0x8B, 0x45, 0x08, 0x8B, 0x48, 0x24, 
	0x51, 0xE8, 0x3A, 0x03, 0x00, 0x00, 0x83, 0xC4, 0x04, 0x85, 0xC0, 0x75, 0x07, 0x33, 0xC0, 0xE9, 
	0x0A, 0x01, 0x00, 0x00, 0x8B, 0x55, 0x08, 0x52, 0xE8, 0x13, 0x04, 0x00, 0x00, 0x83, 0xC4, 0x04, 
	0x85, 0xC0, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0xF3, 0x00, 0x00, 0x00, 0x8B, 0x45, 0x08, 0x50, 0xE8, 
	0xDC, 0x06, 0x00, 0x00, 0x83, 0xC4, 0x04, 0x85, 0xC0, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0xDC, 0x00, 
	0x00, 0x00, 0x8B, 0x4D, 0x08, 0x51, 0xE8, 0x65, 0x07, 0x00, 0x00, 0x83, 0xC4, 0x04, 0x85, 0xC0, 
	0x75, 0x13, 0x8B, 0x55, 0x08, 0x52, 0xE8, 0xC5, 0x0E, 0x00, 0x00, 0x83, 0xC4, 0x04, 0x33, 0xC0, 
	0xE9, 0xB9, 0x00, 0x00, 0x00, 0x8B, 0x45, 0x08, 0x50, 0xE8, 0xB2, 0x08, 0x00, 0x00, 0x83, 0xC4, 
	0x04, 0x85, 0xC0, 0x75, 0x13, 0x8B, 0x4D, 0x08, 0x51, 0xE8, 0xA2, 0x0E, 0x00, 0x00, 0x83, 0xC4, 
	0x04, 0x33, 0xC0, 0xE9, 0x96, 0x00, 0x00, 0x00, 0x8B, 0x55, 0x08, 0x8B, 0x42, 0x08, 0x50, 0x8B, 
	0x4D, 0x08, 0x8B, 0x11, 0x52, 0x6A, 0x00, 0xE8, 0x14, 0x0F, 0x00, 0x00, 0x83, 0xC4, 0x0C, 0x8B, 
	0x4D, 0x08, 0x89, 0x41, 0x0C, 0x68, 0x04, 0x01, 0x00, 0x00, 0x8B, 0x55, 0x0C, 0x52, 0x8B, 0x45, 
	0x08, 0x83, 0xC0, 0x28, 0x50, 0xE8, 0xE6, 0x10, 0x00, 0x00, 0x83, 0xC4, 0x0C, 0x8B, 0x4D, 0x08, 
	0x51, 0xE8, 0x1A, 0x0A, 0x00, 0x00, 0x83, 0xC4, 0x04, 0x85, 0xC0, 0x75, 0x10, 0x8B, 0x55, 0x08, 
	0x52, 0xE8, 0x4A, 0x0E, 0x00, 0x00, 0x83, 0xC4, 0x04, 0x33, 0xC0, 0xEB, 0x41, 0x8B, 0x45, 0x08, 
	0x50, 0xE8, 0xFA, 0x0B, 0x00, 0x00, 0x83, 0xC4, 0x04, 0x85, 0xC0, 0x75, 0x04, 0x33, 0xC0, 0xEB, 
	0x2D, 0x83, 0x7D, 0x10, 0x00, 0x74, 0x22, 0x6A, 0x01, 0x8B, 0x4D, 0x08, 0x51, 0xE8, 0x8E, 0x0C, 
	0x00, 0x00, 0x83, 0xC4, 0x08, 0x85, 0xC0, 0x75, 0x10, 0x8B, 0x55, 0x08, 0x52, 0xE8, 0x0E, 0x0E, 
	0x00, 0x00, 0x83, 0xC4, 0x04, 0x33, 0xC0, 0xEB, 0x05, 0xB8, 0x01, 0x00, 0x00, 0x00, 0x5D, 0xC2, 
	0x0C, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0x7D, 0x08, 0x00, 0x74, 0x18, 0x83, 0x7D, 0x0C, 0x00, 0x74, 0x12, 0x8B, 
	0x45, 0x0C, 0x50, 0x8B, 0x4D, 0x08, 0x51, 0xE8, 0xB4, 0x0C, 0x00, 0x00, 0x83, 0xC4, 0x08, 0xEB, 
	0x02, 0x33, 0xC0, 0x5D, 0xC2, 0x08, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0x7D, 0x08, 0x00, 0x74, 0x1A, 0x6A, 0x00, 0x8B, 0x45, 0x08, 0x50, 0xE8, 
	0x1C, 0x0C, 0x00, 0x00, 0x83, 0xC4, 0x08, 0x8B, 0x4D, 0x08, 0x51, 0xE8, 0xA0, 0x0D, 0x00, 0x00, 
	0x83, 0xC4, 0x04, 0x5D, 0xC2, 0x04, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x30, 0x83, 0x7D, 0x0C, 0x00, 0x74, 0x09, 0x8B, 0x45, 0x0C, 0x83, 
	0x78, 0x18, 0x00, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0x8E, 0x01, 0x00, 0x00, 0x8B, 0x4D, 0x0C, 0x8B, 
	0x51, 0x18, 0x8B, 0x02, 0x89, 0x45, 0xDC, 0x8B, 0x4D, 0x0C, 0x8B, 0x51, 0x18, 0x8B, 0x42, 0x04, 
	0x89, 0x45, 0xD8, 0x8B, 0x4D, 0x0C, 0x8B, 0x51, 0x18, 0x8B, 0x42, 0x08, 0x89, 0x45, 0xD4, 0x8B, 
	0x4D, 0x0C, 0x8B, 0x51, 0x18, 0x8B, 0x42, 0x0C, 0x89, 0x45, 0xD0, 0xC7, 0x45, 0xFC, 0x00, 0x00, 
	0x00, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x03, 0x6A, 0x00, 0x6A, 0x01, 0x68, 0x00, 0x00, 0x00, 
	0x80, 0x8B, 0x4D, 0x08, 0x51, 0xFF, 0x55, 0xDC, 0x8B, 0x55, 0x0C, 0x89, 0x42, 0x1C, 0x8B, 0x45, 
	0x0C, 0x83, 0x78, 0x1C, 0xFF, 0x74, 0x09, 0xC7, 0x45, 0xF8, 0x01, 0x00, 0x00, 0x00, 0xEB, 0x07, 
	0xC7, 0x45, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0xF8, 0x89, 0x4D, 0xFC, 0x83, 0x7D, 0xFC, 
	0x00, 0x75, 0x0A, 0xE9, 0x0F, 0x01, 0x00, 0x00, 0xE9, 0x0A, 0x01, 0x00, 0x00, 0x8B, 0x55, 0x0C, 
	0x83, 0x7A, 0x1C, 0x00, 0x74, 0x09, 0xC7, 0x45, 0xF4, 0x01, 0x00, 0x00, 0x00, 0xEB, 0x07, 0xC7, 
	0x45, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x45, 0xF4, 0x89, 0x45, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 
	0x75, 0x0A, 0xE9, 0xE0, 0x00, 0x00, 0x00, 0xE9, 0xDB, 0x00, 0x00, 0x00, 0x6A, 0x00, 0x8B, 0x4D, 
	0x0C, 0x8B, 0x51, 0x1C, 0x52, 0xFF, 0x55, 0xD8, 0x89, 0x45, 0xEC, 0x83, 0x7D, 0xEC, 0xFF, 0x74, 
	0x09, 0xC7, 0x45, 0xF0, 0x01, 0x00, 0x00, 0x00, 0xEB, 0x07, 0xC7, 0x45, 0xF0, 0x00, 0x00, 0x00, 
	0x00, 0x8B, 0x45, 0xF0, 0x89, 0x45, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 0x75, 0x0A, 0xE9, 0xA5, 0x00, 
	0x00, 0x00, 0xE9, 0xA0, 0x00, 0x00, 0x00, 0x83, 0x7D, 0xEC, 0x40, 0x76, 0x09, 0xC7, 0x45, 0xE8, 
	0x01, 0x00, 0x00, 0x00, 0xEB, 0x07, 0xC7, 0x45, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0xE8, 
	0x89, 0x4D, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 0x75, 0x04, 0xEB, 0x7C, 0xEB, 0x7A, 0x6A, 0x00, 0x6A, 
	0x00, 0x6A, 0x00, 0x6A, 0x02, 0x6A, 0x00, 0x8B, 0x55, 0x0C, 0x8B, 0x42, 0x1C, 0x50, 0xFF, 0x55, 
	0xD4, 0x8B, 0x4D, 0x0C, 0x89, 0x41, 0x20, 0x8B, 0x55, 0x0C, 0x83, 0x7A, 0x20, 0x00, 0x74, 0x09, 
	0xC7, 0x45, 0xE4, 0x01, 0x00, 0x00, 0x00, 0xEB, 0x07, 0xC7, 0x45, 0xE4, 0x00, 0x00, 0x00, 0x00, 
	0x8B, 0x45, 0xE4, 0x89, 0x45, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 0x75, 0x04, 0xEB, 0x39, 0xEB, 0x37, 
	0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x04, 0x8B, 0x4D, 0x0C, 0x8B, 0x51, 0x20, 0x52, 0xFF, 
	0x55, 0xD0, 0x8B, 0x4D, 0x0C, 0x89, 0x41, 0x24, 0x8B, 0x55, 0x0C, 0x83, 0x7A, 0x24, 0x00, 0x74, 
	0x09, 0xC7, 0x45, 0xE0, 0x01, 0x00, 0x00, 0x00, 0xEB, 0x07, 0xC7, 0x45, 0xE0, 0x00, 0x00, 0x00, 
	0x00, 0x8B, 0x45, 0xE0, 0x89, 0x45, 0xFC, 0x8B, 0x45, 0xFC, 0x8B, 0xE5, 0x5D, 0xC3, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x18, 0x56, 0x83, 0x7D, 0x08, 0x00, 0x75, 0x07, 0x33, 0xC0, 0xE9, 
	0xCB, 0x00, 0x00, 0x00, 0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x45, 0x08, 0x89, 0x45, 
	0xF0, 0x8B, 0x4D, 0xF0, 0x0F, 0xB7, 0x11, 0x81, 0xFA, 0x4D, 0x5A, 0x00, 0x00, 0x75, 0x09, 0xC7, 
	0x45, 0xF4, 0x01, 0x00, 0x00, 0x00, 0xEB, 0x07, 0xC7, 0x45, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x8B, 
	0x45, 0xF4, 0x89, 0x45, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 0x75, 0x0A, 0xE9, 0x8C, 0x00, 0x00, 0x00, 
	0xE9, 0x87, 0x00, 0x00, 0x00, 0x8B, 0x45, 0x08, 0x99, 0x8B, 0xC8, 0x8B, 0xF2, 0x8B, 0x55, 0xF0, 
	0x8B, 0x42, 0x3C, 0x99, 0x03, 0xC8, 0x13, 0xF2, 0x89, 0x4D, 0xF8, 0x8B, 0x45, 0xF8, 0x81, 0x38, 
	0x50, 0x45, 0x00, 0x00, 0x75, 0x09, 0xC7, 0x45, 0xEC, 0x01, 0x00, 0x00, 0x00, 0xEB, 0x07, 0xC7, 
	0x45, 0xEC, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0xEC, 0x89, 0x4D, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 
	0x75, 0x04, 0xEB, 0x48, 0xEB, 0x46, 0x8B, 0x55, 0xF8, 0x0F, 0xB7, 0x42, 0x04, 0x3D, 0x4C, 0x01, 
	0x00, 0x00, 0x75, 0x31, 0x8B, 0x4D, 0xF8, 0x0F, 0xB7, 0x51, 0x18, 0x81, 0xFA, 0x0B, 0x01, 0x00, 
	0x00, 0x75, 0x09, 0xC7, 0x45, 0xE8, 0x01, 0x00, 0x00, 0x00, 0xEB, 0x07, 0xC7, 0x45, 0xE8, 0x00, 
	0x00, 0x00, 0x00, 0x8B, 0x45, 0xE8, 0x89, 0x45, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 0x75, 0x04, 0xEB, 
	0x0B, 0xEB, 0x09, 0xEB, 0x07, 0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x45, 0xFC, 0x5E, 
	0x8B, 0xE5, 0x5D, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x34, 0x56, 0x57, 0x83, 0x7D, 0x08, 0x00, 0x74, 0x12, 0x8B, 0x45, 
	0x08, 0x83, 0x78, 0x18, 0x00, 0x74, 0x09, 0x8B, 0x4D, 0x08, 0x83, 0x79, 0x24, 0x00, 0x75, 0x07, 
	0x33, 0xC0, 0xE9, 0xAC, 0x02, 0x00, 0x00, 0x8B, 0x55, 0x08, 0x8B, 0x42, 0x18, 0x8B, 0x48, 0x24, 
	0x89, 0x4D, 0xDC, 0x8B, 0x55, 0x08, 0x8B, 0x42, 0x18, 0x8B, 0x48, 0x28, 0x89, 0x4D, 0xD4, 0x8B, 
	0x55, 0x08, 0x8B, 0x42, 0x24, 0x89, 0x45, 0xE4, 0x8B, 0x45, 0xE4, 0x99, 0x8B, 0xC8, 0x8B, 0xF2, 
	0x8B, 0x55, 0xE4, 0x8B, 0x42, 0x3C, 0x99, 0x03, 0xC8, 0x13, 0xF2, 0x89, 0x4D, 0xF8, 0x8B, 0x45, 
	0xF8, 0x0F, 0xB7, 0x48, 0x06, 0x89, 0x4D, 0xD8, 0x8B, 0x45, 0xF8, 0x99, 0x05, 0xF8, 0x00, 0x00, 
	0x00, 0x83, 0xD2, 0x00, 0x89, 0x45, 0xFC, 0xC7, 0x45, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x45, 
	0xEC, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x09, 0x8B, 0x55, 0xEC, 0x83, 0xC2, 0x01, 0x89, 0x55, 0xEC, 
	0x8B, 0x45, 0xEC, 0x3B, 0x45, 0xD8, 0x7D, 0x44, 0x6B, 0x4D, 0xEC, 0x28, 0x8B, 0x55, 0xFC, 0x83, 
	0x7C, 0x0A, 0x0C, 0x00, 0x74, 0x34, 0x6B, 0x45, 0xEC, 0x28, 0x6B, 0x4D, 0xEC, 0x28, 0x8B, 0x55, 
	0xFC, 0x8B, 0x44, 0x02, 0x0C, 0x8B, 0x55, 0xFC, 0x03, 0x44, 0x0A, 0x10, 0x39, 0x45, 0xE8, 0x73, 
	0x19, 0x6B, 0x45, 0xEC, 0x28, 0x6B, 0x4D, 0xEC, 0x28, 0x8B, 0x55, 0xFC, 0x8B, 0x44, 0x02, 0x0C, 
	0x8B, 0x55, 0xFC, 0x03, 0x44, 0x0A, 0x10, 0x89, 0x45, 0xE8, 0xEB, 0xAB, 0x8B, 0x45, 0x08, 0x8B, 
	0x48, 0x10, 0x8B, 0x55, 0xE8, 0x8D, 0x44, 0x0A, 0xFF, 0x8B, 0x4D, 0x08, 0x8B, 0x51, 0x10, 0x83, 
	0xEA, 0x01, 0xF7, 0xD2, 0x23, 0xC2, 0x89, 0x45, 0xE8, 0x6A, 0x04, 0x68, 0x00, 0x30, 0x00, 0x00, 
	0x8B, 0x45, 0xE8, 0x50, 0x8B, 0x4D, 0xF8, 0x8B, 0x51, 0x34, 0x52, 0xFF, 0x55, 0xDC, 0x89, 0x45, 
	0xE0, 0x83, 0x7D, 0xE0, 0x00, 0x75, 0x20, 0x6A, 0x04, 0x68, 0x00, 0x30, 0x00, 0x00, 0x8B, 0x45, 
	0xE8, 0x50, 0x6A, 0x00, 0xFF, 0x55, 0xDC, 0x89, 0x45, 0xE0, 0x83, 0x7D, 0xE0, 0x00, 0x75, 0x07, 
	0x33, 0xC0, 0xE9, 0x9C, 0x01, 0x00, 0x00, 0x6A, 0x04, 0x68, 0x00, 0x10, 0x00, 0x00, 0x8B, 0x4D, 
	0xF8, 0x8B, 0x51, 0x54, 0x52, 0x8B, 0x45, 0xE0, 0x50, 0xFF, 0x55, 0xDC, 0x89, 0x45, 0xF0, 0x83, 
	0x7D, 0xF0, 0x00, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0x77, 0x01, 0x00, 0x00, 0x8B, 0x4D, 0xF8, 0x8B, 
	0x51, 0x54, 0x52, 0x8B, 0x45, 0x08, 0x8B, 0x48, 0x24, 0x51, 0x8B, 0x55, 0xF0, 0x52, 0xE8, 0x0D, 
	0x0B, 0x00, 0x00, 0x83, 0xC4, 0x0C, 0x8B, 0x45, 0x08, 0x8B, 0x4D, 0xF0, 0x89, 0x08, 0x8B, 0x55, 
	0x08, 0x8B, 0x45, 0xF8, 0x8B, 0x48, 0x50, 0x89, 0x4A, 0x08, 0x8B, 0x55, 0x08, 0xC7, 0x42, 0x14, 
	0x01, 0x00, 0x00, 0x00, 0x8B, 0x45, 0xF0, 0x89, 0x45, 0xE4, 0x8B, 0x45, 0xE4, 0x99, 0x8B, 0xC8, 
	0x8B, 0xF2, 0x8B, 0x55, 0xE4, 0x8B, 0x42, 0x3C, 0x99, 0x03, 0xC8, 0x13, 0xF2, 0x89, 0x4D, 0xF8, 
	0x8B, 0x45, 0xF8, 0x99, 0x05, 0xF8, 0x00, 0x00, 0x00, 0x83, 0xD2, 0x00, 0x89, 0x45, 0xFC, 0x0F, 
	0x57, 0xC0, 0x66, 0x0F, 0x13, 0x45, 0xCC, 0xC7, 0x45, 0xF4, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x09, 
	0x8B, 0x45, 0xF4, 0x83, 0xC0, 0x01, 0x89, 0x45, 0xF4, 0x8B, 0x4D, 0xF4, 0x3B, 0x4D, 0xD8, 0x0F, 
	0x8D, 0xE9, 0x00, 0x00, 0x00, 0x6B, 0x55, 0xF4, 0x28, 0x8B, 0x45, 0xFC, 0x83, 0x7C, 0x10, 0x0C, 
	0x00, 0x0F, 0x84, 0xD2, 0x00, 0x00, 0x00, 0x6B, 0x4D, 0xF4, 0x28, 0x8B, 0x55, 0xFC, 0x8B, 0x4C, 
	0x0A, 0x0C, 0x33, 0xF6, 0x8B, 0x45, 0xE0, 0x99, 0x03, 0xC8, 0x13, 0xF2, 0x89, 0x4D, 0xCC, 0x89, 
	0x75, 0xD0, 0x6B, 0x55, 0xF4, 0x28, 0x8B, 0x45, 0xFC, 0x83, 0x7C, 0x10, 0x10, 0x00, 0x75, 0x45, 
	0x8B, 0x4D, 0xF8, 0x83, 0x79, 0x38, 0x00, 0x76, 0x3A, 0x6A, 0x04, 0x68, 0x00, 0x10, 0x00, 0x00, 
	0x8B, 0x55, 0xF8, 0x8B, 0x42, 0x38, 0x50, 0x8B, 0x4D, 0xCC, 0x51, 0xFF, 0x55, 0xDC, 0x89, 0x45, 
	0xF0, 0x83, 0x7D, 0xF0, 0x00, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0x85, 0x00, 0x00, 0x00, 0x8B, 0x55, 
	0xF8, 0x8B, 0x42, 0x38, 0x50, 0x6A, 0x00, 0x8B, 0x4D, 0xCC, 0x51, 0xE8, 0x76, 0x0A, 0x00, 0x00, 
	0x83, 0xC4, 0x0C, 0xEB, 0x56, 0x6A, 0x04, 0x68, 0x00, 0x10, 0x00, 0x00, 0x6B, 0x55, 0xF4, 0x28, 
	0x8B, 0x45, 0xFC, 0x8B, 0x4C, 0x10, 0x10, 0x51, 0x8B, 0x55, 0xCC, 0x52, 0xFF, 0x55, 0xDC, 0x89, 
	0x45, 0xF0, 0x83, 0x7D, 0xF0, 0x00, 0x75, 0x04, 0x33, 0xC0, 0xEB, 0x47, 0x6B, 0x45, 0xF4, 0x28, 
	0x8B, 0x4D, 0xFC, 0x8B, 0x54, 0x01, 0x10, 0x52, 0x8B, 0x45, 0x08, 0x8B, 0x40, 0x24, 0x99, 0x6B, 
	0x4D, 0xF4, 0x28, 0x8B, 0x75, 0xFC, 0x33, 0xFF, 0x03, 0x44, 0x0E, 0x14, 0x13, 0xD7, 0x50, 0x8B, 
	0x55, 0xF0, 0x52, 0xE8, 0xC8, 0x09, 0x00, 0x00, 0x83, 0xC4, 0x0C, 0x6B, 0x45, 0xF4, 0x28, 0x8B, 
	0x4D, 0xFC, 0x8B, 0x55, 0xF0, 0x89, 0x54, 0x01, 0x08, 0xE9, 0x02, 0xFF, 0xFF, 0xFF, 0xB8, 0x01, 
	0x00, 0x00, 0x00, 0x5F, 0x5E, 0x8B, 0xE5, 0x5D, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08, 0x83, 0x7D, 0x08, 0x00, 0x74, 0x09, 0x8B, 0x45, 0x08, 0x83, 
	0x78, 0x18, 0x00, 0x75, 0x04, 0x33, 0xC0, 0xEB, 0x74, 0x8B, 0x4D, 0x08, 0x8B, 0x51, 0x18, 0x8B, 
	0x42, 0x10, 0x89, 0x45, 0xF8, 0x8B, 0x4D, 0x08, 0x8B, 0x51, 0x18, 0x8B, 0x42, 0x14, 0x89, 0x45, 
	0xFC, 0x8B, 0x4D, 0x08, 0x83, 0x79, 0x24, 0x00, 0x74, 0x14, 0x8B, 0x55, 0x08, 0x8B, 0x42, 0x24, 
	0x50, 0xFF, 0x55, 0xF8, 0x8B, 0x4D, 0x08, 0xC7, 0x41, 0x24, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x55, 
	0x08, 0x83, 0x7A, 0x20, 0x00, 0x74, 0x14, 0x8B, 0x45, 0x08, 0x8B, 0x48, 0x20, 0x51, 0xFF, 0x55, 
	0xFC, 0x8B, 0x55, 0x08, 0xC7, 0x42, 0x20, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x45, 0x08, 0x83, 0x78, 
	0x1C, 0x00, 0x74, 0x14, 0x8B, 0x4D, 0x08, 0x8B, 0x51, 0x1C, 0x52, 0xFF, 0x55, 0xFC, 0x8B, 0x45, 
	0x08, 0xC7, 0x40, 0x1C, 0xFF, 0xFF, 0xFF, 0xFF, 0xB8, 0x01, 0x00, 0x00, 0x00, 0x8B, 0xE5, 0x5D, 
	0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x20, 0x56, 0x57, 0x83, 0x7D, 0x08, 0x00, 0x74, 0x08, 0x8B, 0x45, 
	0x08, 0x83, 0x38, 0x00, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0x44, 0x01, 0x00, 0x00, 0x8B, 0x4D, 0x08, 
	0x8B, 0x01, 0x99, 0x8B, 0xC8, 0x8B, 0xF2, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x8B, 0x40, 0x3C, 0x99, 
	0x03, 0xC8, 0x13, 0xF2, 0x89, 0x4D, 0xF4, 0x8B, 0x4D, 0xF4, 0x8B, 0x51, 0x34, 0x33, 0xC0, 0x8B, 
	0x4D, 0x08, 0x8B, 0x31, 0x2B, 0xF2, 0x8B, 0x51, 0x04, 0x1B, 0xD0, 0x89, 0x75, 0xE0, 0x89, 0x55, 
	0xE4, 0x83, 0x7D, 0xE0, 0x00, 0x75, 0x10, 0x83, 0x7D, 0xE4, 0x00, 0x75, 0x0A, 0xB8, 0x01, 0x00, 
	0x00, 0x00, 0xE9, 0xFA, 0x00, 0x00, 0x00, 0xB8, 0x08, 0x00, 0x00, 0x00, 0x6B, 0xC8, 0x05, 0x8B, 
	0x55, 0xF4, 0x83, 0x7C, 0x0A, 0x78, 0x00, 0x74, 0x12, 0xB8, 0x08, 0x00, 0x00, 0x00, 0x6B, 0xC8, 
	0x05, 0x8B, 0x55, 0xF4, 0x83, 0x7C, 0x0A, 0x7C, 0x00, 0x75, 0x0A, 0xB8, 0x01, 0x00, 0x00, 0x00, 
	0xE9, 0xCC, 0x00, 0x00, 0x00, 0x8B, 0x45, 0x08, 0x8B, 0x00, 0x99, 0xB9, 0x08, 0x00, 0x00, 0x00, 
	0x6B, 0xC9, 0x05, 0x8B, 0x75, 0xF4, 0x33, 0xFF, 0x03, 0x44, 0x0E, 0x78, 0x13, 0xD7, 0x89, 0x45, 
	0xFC, 0x83, 0x7D, 0xFC, 0x00, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0xA3, 0x00, 0x00, 0x00, 0x8B, 0x55, 
	0xFC, 0x8B, 0x02, 0x8B, 0x4D, 0xFC, 0x03, 0x41, 0x04, 0x0F, 0x84, 0x8D, 0x00, 0x00, 0x00, 0x8B, 
	0x45, 0xFC, 0x99, 0x83, 0xC0, 0x08, 0x83, 0xD2, 0x00, 0x89, 0x45, 0xF0, 0x8B, 0x55, 0xFC, 0x8B, 
	0x42, 0x04, 0x83, 0xE8, 0x08, 0xD1, 0xE8, 0x89, 0x45, 0xE8, 0xC7, 0x45, 0xF8, 0x00, 0x00, 0x00, 
	0x00, 0xEB, 0x09, 0x8B, 0x4D, 0xF8, 0x83, 0xC1, 0x01, 0x89, 0x4D, 0xF8, 0x8B, 0x55, 0xF8, 0x3B, 
	0x55, 0xE8, 0x7D, 0x47, 0x8B, 0x45, 0xF8, 0x8B, 0x4D, 0xF0, 0x0F, 0xB7, 0x14, 0x41, 0xC1, 0xFA, 
	0x0C, 0x83, 0xFA, 0x03, 0x75, 0x33, 0x8B, 0x45, 0xFC, 0x8B, 0x08, 0x33, 0xF6, 0x8B, 0x55, 0x08, 
	0x03, 0x0A, 0x13, 0x72, 0x04, 0x8B, 0x45, 0xF8, 0x8B, 0x55, 0xF0, 0x0F, 0xB7, 0x04, 0x42, 0x25, 
	0xFF, 0x0F, 0x00, 0x00, 0x99, 0x03, 0xC8, 0x13, 0xF2, 0x89, 0x4D, 0xEC, 0x8B, 0x45, 0xE0, 0x8B, 
	0x4D, 0xEC, 0x03, 0x01, 0x8B, 0x55, 0xEC, 0x89, 0x02, 0xEB, 0xA8, 0x8B, 0x45, 0xFC, 0x8B, 0x4D, 
	0xFC, 0x03, 0x48, 0x04, 0x89, 0x4D, 0xFC, 0xE9, 0x62, 0xFF, 0xFF, 0xFF, 0xB8, 0x01, 0x00, 0x00, 
	0x00, 0x5F, 0x5E, 0x8B, 0xE5, 0x5D, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x34, 0x56, 0x57, 0x83, 0x7D, 0x08, 0x00, 0x74, 0x11, 0x8B, 0x45, 
	0x08, 0x83, 0x78, 0x18, 0x00, 0x74, 0x08, 0x8B, 0x4D, 0x08, 0x83, 0x39, 0x00, 0x75, 0x07, 0x33, 
	0xC0, 0xE9, 0x93, 0x01, 0x00, 0x00, 0x8B, 0x55, 0x08, 0x8B, 0x42, 0x18, 0x8B, 0x48, 0x18, 0x89, 
	0x4D, 0xDC, 0x8B, 0x55, 0x08, 0x8B, 0x42, 0x18, 0x8B, 0x48, 0x1C, 0x89, 0x4D, 0xD8, 0x8B, 0x55, 
	0x08, 0x8B, 0x42, 0x18, 0x8B, 0x48, 0x20, 0x89, 0x4D, 0xE0, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x99, 
	0x8B, 0xC8, 0x8B, 0xF2, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x8B, 0x40, 0x3C, 0x99, 0x03, 0xC8, 0x13, 
	0xF2, 0x89, 0x4D, 0xF0, 0xB9, 0x08, 0x00, 0x00, 0x00, 0xC1, 0xE1, 0x00, 0x8B, 0x55, 0xF0, 0x83, 
	0x7C, 0x0A, 0x78, 0x00, 0x74, 0x12, 0xB8, 0x08, 0x00, 0x00, 0x00, 0xC1, 0xE0, 0x00, 0x8B, 0x4D, 
	0xF0, 0x83, 0x7C, 0x01, 0x7C, 0x00, 0x75, 0x0A, 0xB8, 0x01, 0x00, 0x00, 0x00, 0xE9, 0x27, 0x01, 
	0x00, 0x00, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x99, 0xB9, 0x08, 0x00, 0x00, 0x00, 0xC1, 0xE1, 0x00, 
	0x8B, 0x75, 0xF0, 0x33, 0xFF, 0x03, 0x44, 0x0E, 0x78, 0x13, 0xD7, 0x89, 0x45, 0xF8, 0x8B, 0x55, 
	0xF8, 0x83, 0x3A, 0x00, 0x0F, 0x84, 0xFA, 0x00, 0x00, 0x00, 0x8B, 0x45, 0x08, 0x8B, 0x00, 0x99, 
	0x8B, 0x4D, 0xF8, 0x33, 0xF6, 0x03, 0x41, 0x0C, 0x13, 0xD6, 0x89, 0x45, 0xE4, 0x8B, 0x55, 0xE4, 
	0x52, 0xFF, 0x55, 0xDC, 0x89, 0x45, 0xF4, 0x83, 0x7D, 0xF4, 0x00, 0x75, 0x0A, 0x8B, 0x45, 0xE4, 
	0x50, 0xFF, 0x55, 0xD8, 0x89, 0x45, 0xF4, 0x83, 0x7D, 0xF4, 0x00, 0x0F, 0x84, 0xAD, 0x00, 0x00, 
	0x00, 0x8B, 0x4D, 0xF8, 0x8B, 0x11, 0x89, 0x55, 0xD4, 0x8B, 0x45, 0xF8, 0x8B, 0x48, 0x10, 0x89, 
	0x4D, 0xD0, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x99, 0x33, 0xC9, 0x03, 0x45, 0xD4, 0x13, 0xD1, 0x89, 
	0x45, 0xFC, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x99, 0x33, 0xC9, 0x03, 0x45, 0xD0, 0x13, 0xD1, 0x89, 
	0x45, 0xE8, 0x8B, 0x55, 0xFC, 0x83, 0x3A, 0x00, 0x74, 0x72, 0xC7, 0x45, 0xEC, 0x00, 0x00, 0x00, 
	0x00, 0x8B, 0x45, 0xFC, 0x8B, 0x08, 0x81, 0xE1, 0x00, 0x00, 0x00, 0x80, 0x74, 0x17, 0x8B, 0x55, 
	0xFC, 0x8B, 0x02, 0x25, 0xFF, 0xFF, 0x00, 0x00, 0x50, 0x8B, 0x4D, 0xF4, 0x51, 0xFF, 0x55, 0xE0, 
	0x89, 0x45, 0xEC, 0xEB, 0x23, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x99, 0x8B, 0x4D, 0xFC, 0x33, 0xF6, 
	0x03, 0x01, 0x13, 0xD6, 0x89, 0x45, 0xCC, 0x8B, 0x55, 0xCC, 0x83, 0xC2, 0x02, 0x52, 0x8B, 0x45, 
	0xF4, 0x50, 0xFF, 0x55, 0xE0, 0x89, 0x45, 0xEC, 0x8B, 0x4D, 0xE8, 0x8B, 0x55, 0xEC, 0x89, 0x11, 
	0x8B, 0x45, 0xFC, 0x99, 0x83, 0xC0, 0x04, 0x83, 0xD2, 0x00, 0x89, 0x45, 0xFC, 0x8B, 0x45, 0xE8, 
	0x99, 0x83, 0xC0, 0x04, 0x83, 0xD2, 0x00, 0x89, 0x45, 0xE8, 0xEB, 0x86, 0xEB, 0x04, 0x33, 0xC0, 
	0xEB, 0x17, 0x8B, 0x45, 0xF8, 0x99, 0x83, 0xC0, 0x14, 0x83, 0xD2, 0x00, 0x89, 0x45, 0xF8, 0xE9, 
	0xFA, 0xFE, 0xFF, 0xFF, 0xB8, 0x01, 0x00, 0x00, 0x00, 0x5F, 0x5E, 0x8B, 0xE5, 0x5D, 0xC3, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x6C, 0x56, 0x83, 0x7D, 0x08, 0x00, 0x74, 0x09, 0x8B, 0x45, 0x08, 
	0x83, 0x78, 0x18, 0x00, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0xD5, 0x01, 0x00, 0x00, 0xC7, 0x45, 0x94, 
	0x01, 0x00, 0x00, 0x00, 0xC7, 0x45, 0x98, 0x08, 0x00, 0x00, 0x00, 0xC7, 0x45, 0x9C, 0x02, 0x00, 
	0x00, 0x00, 0xC7, 0x45, 0xA0, 0x04, 0x00, 0x00, 0x00, 0xC7, 0x45, 0xA4, 0x10, 0x00, 0x00, 0x00, 
	0xC7, 0x45, 0xA8, 0x80, 0x00, 0x00, 0x00, 0xC7, 0x45, 0xAC, 0x20, 0x00, 0x00, 0x00, 0xC7, 0x45, 
	0xB0, 0x40, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0x08, 0x8B, 0x51, 0x18, 0x8B, 0x42, 0x2C, 0x89, 0x45, 
	0xC4, 0x8B, 0x4D, 0x08, 0x8B, 0x51, 0x18, 0x8B, 0x42, 0x28, 0x89, 0x45, 0xCC, 0x8B, 0x4D, 0x08, 
	0x8B, 0x11, 0x89, 0x55, 0xE8, 0x0F, 0x57, 0xC0, 0x66, 0x0F, 0x13, 0x45, 0xB4, 0x8B, 0x45, 0xE8, 
	0x99, 0x8B, 0xC8, 0x8B, 0xF2, 0x8B, 0x55, 0xE8, 0x8B, 0x42, 0x3C, 0x99, 0x03, 0xC8, 0x13, 0xF2, 
	0x89, 0x4D, 0xE4, 0x8B, 0x45, 0xE4, 0x0F, 0xB7, 0x48, 0x06, 0x89, 0x4D, 0xD0, 0x8B, 0x45, 0xE4, 
	0x99, 0x05, 0xF8, 0x00, 0x00, 0x00, 0x83, 0xD2, 0x00, 0x89, 0x45, 0xF0, 0xC7, 0x45, 0xFC, 0x00, 
	0x00, 0x00, 0x00, 0xEB, 0x09, 0x8B, 0x55, 0xFC, 0x83, 0xC2, 0x01, 0x89, 0x55, 0xFC, 0x8B, 0x45, 
	0xFC, 0x3B, 0x45, 0xD0, 0x0F, 0x8D, 0x23, 0x01, 0x00, 0x00, 0xC7, 0x45, 0xF4, 0x00, 0x00, 0x00, 
	0x00, 0xC7, 0x45, 0xC8, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x45, 0xE0, 0x00, 0x00, 0x00, 0x00, 0xC7, 
	0x45, 0xDC, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x45, 0xD8, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x45, 0xD4, 
	0x00, 0x00, 0x00, 0x00, 0x6B, 0x4D, 0xFC, 0x28, 0x8B, 0x55, 0xF0, 0x8B, 0x44, 0x0A, 0x08, 0x33, 
	0xC9, 0x0B, 0x45, 0xB4, 0x0B, 0x4D, 0xB8, 0x89, 0x45, 0xBC, 0x89, 0x4D, 0xC0, 0x6B, 0x55, 0xFC, 
	0x28, 0x8B, 0x45, 0xF0, 0x8B, 0x4C, 0x10, 0x10, 0x89, 0x4D, 0xEC, 0x83, 0x7D, 0xEC, 0x00, 0x75, 
	0x02, 0xEB, 0x92, 0x6B, 0x55, 0xFC, 0x28, 0x8B, 0x45, 0xF0, 0x8B, 0x4C, 0x10, 0x24, 0x89, 0x4D, 
	0xF8, 0x8B, 0x55, 0xF8, 0x81, 0xE2, 0x00, 0x00, 0x00, 0x02, 0x74, 0x20, 0x68, 0x00, 0x40, 0x00, 
	0x00, 0x8B, 0x45, 0xEC, 0x50, 0x8B, 0x4D, 0xBC, 0x51, 0xFF, 0x55, 0xCC, 0x85, 0xC0, 0x75, 0x07, 
	0x33, 0xC0, 0xE9, 0x9B, 0x00, 0x00, 0x00, 0xE9, 0x59, 0xFF, 0xFF, 0xFF, 0x8B, 0x55, 0xF8, 0x81, 
	0xE2, 0x00, 0x00, 0x00, 0x20, 0x74, 0x07, 0xC7, 0x45, 0xE0, 0x01, 0x00, 0x00, 0x00, 0x8B, 0x45, 
	0xF8, 0x25, 0x00, 0x00, 0x00, 0x40, 0x74, 0x07, 0xC7, 0x45, 0xDC, 0x01, 0x00, 0x00, 0x00, 0x8B, 
	0x4D, 0xF8, 0x81, 0xE1, 0x00, 0x00, 0x00, 0x80, 0x74, 0x07, 0xC7, 0x45, 0xD8, 0x01, 0x00, 0x00, 
	0x00, 0x8B, 0x55, 0xF8, 0x81, 0xE2, 0x00, 0x00, 0x00, 0x04, 0x74, 0x07, 0xC7, 0x45, 0xD4, 0x01, 
	0x00, 0x00, 0x00, 0x8B, 0x45, 0xE0, 0xC1, 0xE0, 0x04, 0x8D, 0x4C, 0x05, 0x94, 0x8B, 0x55, 0xDC, 
	0x8D, 0x04, 0xD1, 0x8B, 0x4D, 0xD8, 0x8B, 0x14, 0x88, 0x89, 0x55, 0xF4, 0x83, 0x7D, 0xD4, 0x00, 
	0x74, 0x0B, 0x8B, 0x45, 0xF4, 0x0D, 0x00, 0x02, 0x00, 0x00, 0x89, 0x45, 0xF4, 0x8D, 0x4D, 0xC8, 
	0x51, 0x8B, 0x55, 0xF4, 0x52, 0x8B, 0x45, 0xEC, 0x50, 0x8B, 0x4D, 0xBC, 0x51, 0xFF, 0x55, 0xC4, 
	0x85, 0xC0, 0x75, 0x04, 0x33, 0xC0, 0xEB, 0x0A, 0xE9, 0xC8, 0xFE, 0xFF, 0xFF, 0xB8, 0x01, 0x00, 
	0x00, 0x00, 0x5E, 0x8B, 0xE5, 0x5D, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x14, 0x56, 0x83, 0x7D, 0x08, 0x00, 0x74, 0x08, 0x8B, 0x45, 0x08, 
	0x83, 0x38, 0x00, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0x88, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0x08, 0x8B, 
	0x01, 0x99, 0x8B, 0xC8, 0x8B, 0xF2, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x8B, 0x40, 0x3C, 0x99, 0x03, 
	0xC8, 0x13, 0xF2, 0x89, 0x4D, 0xF8, 0xB9, 0x08, 0x00, 0x00, 0x00, 0x6B, 0xD1, 0x09, 0x8B, 0x45, 
	0xF8, 0x8B, 0x4C, 0x10, 0x78, 0x8B, 0x54, 0x10, 0x7C, 0x89, 0x4D, 0xEC, 0x89, 0x55, 0xF0, 0x83, 
	0x7D, 0xEC, 0x00, 0x75, 0x07, 0xB8, 0x01, 0x00, 0x00, 0x00, 0xEB, 0x48, 0x8B, 0x45, 0xEC, 0x33, 
	0xC9, 0x8B, 0x55, 0x08, 0x03, 0x02, 0x13, 0x4A, 0x04, 0x89, 0x45, 0xF4, 0x8B, 0x45, 0xF4, 0x8B, 
	0x48, 0x0C, 0x89, 0x4D, 0xFC, 0x83, 0x7D, 0xFC, 0x00, 0x74, 0x24, 0x8B, 0x55, 0xFC, 0x83, 0x3A, 
	0x00, 0x74, 0x1C, 0x6A, 0x00, 0x6A, 0x01, 0x8B, 0x45, 0x08, 0x8B, 0x08, 0x51, 0x8B, 0x55, 0xFC, 
	0x8B, 0x02, 0xFF, 0xD0, 0x8B, 0x4D, 0xFC, 0x83, 0xC1, 0x04, 0x89, 0x4D, 0xFC, 0xEB, 0xDC, 0xB8, 
	0x01, 0x00, 0x00, 0x00, 0x5E, 0x8B, 0xE5, 0x5D, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08, 0x56, 0x83, 0x7D, 0x08, 0x00, 0x74, 0x08, 0x8B, 0x45, 0x08, 
	0x83, 0x38, 0x00, 0x75, 0x04, 0x33, 0xC0, 0xEB, 0x4D, 0x8B, 0x4D, 0x08, 0x8B, 0x01, 0x99, 0x8B, 
	0xC8, 0x8B, 0xF2, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x8B, 0x40, 0x3C, 0x99, 0x03, 0xC8, 0x13, 0xF2, 
	0x89, 0x4D, 0xF8, 0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0x08, 0x8B, 0x01, 0x99, 
	0x8B, 0x4D, 0xF8, 0x33, 0xF6, 0x03, 0x41, 0x28, 0x13, 0xD6, 0x89, 0x45, 0xFC, 0x83, 0x7D, 0xFC, 
	0x00, 0x75, 0x04, 0x33, 0xC0, 0xEB, 0x0F, 0x6A, 0x00, 0x8B, 0x55, 0x0C, 0x52, 0x8B, 0x45, 0x08, 
	0x8B, 0x08, 0x51, 0xFF, 0x55, 0xFC, 0x5E, 0x8B, 0xE5, 0x5D, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x30, 0x56, 0x57, 0x83, 0x7D, 0x08, 0x00, 0x74, 0x08, 0x8B, 0x45, 
	0x08, 0x83, 0x38, 0x00, 0x75, 0x07, 0x33, 0xC0, 0xE9, 0xF6, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0x08, 
	0x8B, 0x01, 0x99, 0x8B, 0xC8, 0x8B, 0xF2, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x8B, 0x40, 0x3C, 0x99, 
	0x03, 0xC8, 0x13, 0xF2, 0x89, 0x4D, 0xF0, 0x8B, 0x4D, 0x08, 0x8B, 0x01, 0x99, 0xB9, 0x08, 0x00, 
	0x00, 0x00, 0x6B, 0xC9, 0x00, 0x8B, 0x75, 0xF0, 0x33, 0xFF, 0x03, 0x44, 0x0E, 0x78, 0x13, 0xD7, 
	0x89, 0x45, 0xF4, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x99, 0x8B, 0x4D, 0xF4, 0x33, 0xF6, 0x03, 0x41, 
	0x20, 0x13, 0xD6, 0x89, 0x45, 0xE8, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x99, 0x8B, 0x4D, 0xF4, 0x33, 
	0xF6, 0x03, 0x41, 0x24, 0x13, 0xD6, 0x89, 0x45, 0xDC, 0x8B, 0x55, 0x08, 0x8B, 0x02, 0x99, 0x8B, 
	0x4D, 0xF4, 0x33, 0xF6, 0x03, 0x41, 0x1C, 0x13, 0xD6, 0x89, 0x45, 0xD8, 0x8B, 0x55, 0xF4, 0x8B, 
	0x42, 0x14, 0x89, 0x45, 0xEC, 0xC7, 0x45, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x09, 0x8B, 0x4D, 
	0xF8, 0x83, 0xC1, 0x01, 0x89, 0x4D, 0xF8, 0x8B, 0x55, 0xF8, 0x3B, 0x55, 0xEC, 0x7D, 0x62, 0x8B, 
	0x45, 0xF8, 0x8B, 0x4D, 0xE8, 0x8B, 0x14, 0x81, 0x89, 0x55, 0xE4, 0x8B, 0x45, 0x08, 0x8B, 0x00, 
	0x99, 0x33, 0xC9, 0x03, 0x45, 0xE4, 0x13, 0xD1, 0x89, 0x45, 0xE0, 0x8B, 0x55, 0xE0, 0x52, 0x8B, 
	0x45, 0x0C, 0x50, 0xE8, 0x68, 0x02, 0x00, 0x00, 0x83, 0xC4, 0x08, 0x85, 0xC0, 0x75, 0x30, 0x8B, 
	0x4D, 0xF8, 0x8B, 0x55, 0xDC, 0x66, 0x8B, 0x04, 0x4A, 0x66, 0x89, 0x45, 0xFC, 0x0F, 0xB7, 0x4D, 
	0xFC, 0x8B, 0x55, 0xD8, 0x8B, 0x04, 0x8A, 0x89, 0x45, 0xD4, 0x8B, 0x4D, 0x08, 0x8B, 0x01, 0x99, 
	0x33, 0xC9, 0x03, 0x45, 0xD4, 0x13, 0xD1, 0x89, 0x45, 0xD0, 0x8B, 0x45, 0xD0, 0xEB, 0x04, 0xEB, 
	0x8D, 0x33, 0xC0, 0x5F, 0x5E, 0x8B, 0xE5, 0x5D, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x51, 0x83, 0x7D, 0x08, 0x00, 0x74, 0x1A, 0x8B, 0x45, 0x08, 0x83, 0x78, 0x18, 
	0x00, 0x74, 0x11, 0x8B, 0x4D, 0x08, 0x83, 0x79, 0x14, 0x00, 0x74, 0x08, 0x8B, 0x55, 0x08, 0x83, 
	0x3A, 0x00, 0x75, 0x02, 0xEB, 0x59, 0x8B, 0x45, 0x08, 0x8B, 0x48, 0x18, 0x8B, 0x51, 0x28, 0x89, 
	0x55, 0xFC, 0x68, 0x00, 0x80, 0x00, 0x00, 0x6A, 0x00, 0x8B, 0x45, 0x08, 0x8B, 0x08, 0x51, 0xFF, 
	0x55, 0xFC, 0x8B, 0x55, 0x08, 0xC7, 0x02, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x45, 0x08, 0xC7, 0x40, 
	0x0C, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x4D, 0x08, 0xC7, 0x41, 0x08, 0x00, 0x00, 0x00, 0x00, 0x8B, 
	0x55, 0x08, 0xC7, 0x42, 0x14, 0x00, 0x00, 0x00, 0x00, 0x68, 0x08, 0x02, 0x00, 0x00, 0x6A, 0x00, 
	0x8B, 0x45, 0x08, 0x83, 0xC0, 0x28, 0x50, 0xE8, 0x6A, 0x01, 0x00, 0x00, 0x83, 0xC4, 0x0C, 0x8B, 
	0xE5, 0x5D, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x81, 0xEC, 0x00, 0x04, 0x00, 0x00, 0x33, 0xC9, 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x8B, 0xC1, 0xC1, 0xE0, 0x18, 0x3D, 0x00, 0x00, 0x00, 0x80, 0x72, 0x09, 0x03, 0xC0, 0x35, 0xB7, 
	0x0D, 0xC1, 0x04, 0xEB, 0x02, 0x03, 0xC0, 0x3D, 0x00, 0x00, 0x00, 0x80, 0x72, 0x09, 0x03, 0xC0, 
	0x35, 0xB7, 0x0D, 0xC1, 0x04, 0xEB, 0x02, 0x03, 0xC0, 0x3D, 0x00, 0x00, 0x00, 0x80, 0x72, 0x09, 
	0x03, 0xC0, 0x35, 0xB7, 0x0D, 0xC1, 0x04, 0xEB, 0x02, 0x03, 0xC0, 0x3D, 0x00, 0x00, 0x00, 0x80, 
	0x72, 0x09, 0x03, 0xC0, 0x35, 0xB7, 0x0D, 0xC1, 0x04, 0xEB, 0x02, 0x03, 0xC0, 0x3D, 0x00, 0x00, 
	0x00, 0x80, 0x72, 0x09, 0x03, 0xC0, 0x35, 0xB7, 0x0D, 0xC1, 0x04, 0xEB, 0x02, 0x03, 0xC0, 0x3D, 
	0x00, 0x00, 0x00, 0x80, 0x72, 0x09, 0x03, 0xC0, 0x35, 0xB7, 0x0D, 0xC1, 0x04, 0xEB, 0x02, 0x03, 
	0xC0, 0x3D, 0x00, 0x00, 0x00, 0x80, 0x72, 0x09, 0x03, 0xC0, 0x35, 0xB7, 0x0D, 0xC1, 0x04, 0xEB, 
	0x02, 0x03, 0xC0, 0x3D, 0x00, 0x00, 0x00, 0x80, 0x72, 0x09, 0x03, 0xC0, 0x35, 0xB7, 0x0D, 0xC1, 
	0x04, 0xEB, 0x02, 0x03, 0xC0, 0x89, 0x04, 0x8C, 0x41, 0x81, 0xF9, 0x00, 0x01, 0x00, 0x00, 0x0F, 
	0x8C, 0x5B, 0xFF, 0xFF, 0xFF, 0x8B, 0x94, 0x24, 0x04, 0x04, 0x00, 0x00, 0x56, 0x8B, 0xB4, 0x24, 
	0x10, 0x04, 0x00, 0x00, 0x57, 0x8B, 0xBC, 0x24, 0x10, 0x04, 0x00, 0x00, 0x85, 0xF6, 0x74, 0x19, 
	0x0F, 0xB6, 0x07, 0x8D, 0x7F, 0x01, 0x8B, 0xCA, 0xC1, 0xE2, 0x08, 0xC1, 0xE9, 0x18, 0x33, 0xC8, 
	0x33, 0x54, 0x8C, 0x08, 0x83, 0xEE, 0x01, 0x75, 0xE7, 0x5F, 0x8B, 0xC2, 0x5E, 0x81, 0xC4, 0x00, 
	0x04, 0x00, 0x00, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x8B, 0x54, 0x24, 0x04, 0x56, 0x8B, 0x74, 0x24, 0x0C, 0x57, 0x3B, 0xF2, 0x73, 0x27, 0x8B, 0x7C, 
	0x24, 0x14, 0x4E, 0x03, 0xF7, 0x8D, 0x47, 0xFF, 0x03, 0xC2, 0x85, 0xFF, 0x74, 0x33, 0x66, 0x90, 
	0x8A, 0x0E, 0x8D, 0x40, 0xFF, 0x88, 0x48, 0x01, 0x8D, 0x76, 0xFF, 0x83, 0xEF, 0x01, 0x75, 0xF0, 
	0x5F, 0x8B, 0xC2, 0x5E, 0xC3, 0x76, 0x1A, 0x8B, 0x7C, 0x24, 0x14, 0x8B, 0xCA, 0x85, 0xFF, 0x74, 
	0x10, 0x2B, 0xF2, 0x8A, 0x04, 0x0E, 0x8D, 0x49, 0x01, 0x88, 0x41, 0xFF, 0x83, 0xEF, 0x01, 0x75, 
	0xF2, 0x5F, 0x8B, 0xC2, 0x5E, 0xC3, 0x55, 0x8B, 0xEC, 0x51, 0x83, 0x65, 0xFC, 0x00, 0xEB, 0x07, 
	0x8B, 0x45, 0xFC, 0x40, 0x89, 0x45, 0xFC, 0x8B, 0x45, 0xFC, 0x3B, 0x45, 0x10, 0x73, 0x0D, 0x8B, 
	0x45, 0x08, 0x03, 0x45, 0xFC, 0x8A, 0x4D, 0x0C, 0x88, 0x08, 0xEB, 0xE4, 0x8B, 0x45, 0x08, 0x8B, 
	0xE5, 0x5D, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x51, 0xC6, 0x45, 0xFF, 0x00, 0xC6, 0x45, 0xFE, 0x00, 0x8B, 0x45, 0x08, 0x8A, 
	0x08, 0x88, 0x4D, 0xFF, 0x8B, 0x55, 0x08, 0x83, 0xC2, 0x01, 0x89, 0x55, 0x08, 0x8B, 0x45, 0x0C, 
	0x8A, 0x08, 0x88, 0x4D, 0xFE, 0x8B, 0x55, 0x0C, 0x83, 0xC2, 0x01, 0x89, 0x55, 0x0C, 0x0F, 0xB6, 
	0x45, 0xFF, 0x85, 0xC0, 0x75, 0x0C, 0x0F, 0xB6, 0x45, 0xFF, 0x0F, 0xB6, 0x4D, 0xFE, 0x2B, 0xC1, 
	0xEB, 0x16, 0x0F, 0xB6, 0x55, 0xFF, 0x0F, 0xB6, 0x45, 0xFE, 0x3B, 0xD0, 0x74, 0xBE, 0x0F, 0xB6, 
	0x45, 0xFF, 0x0F, 0xB6, 0x4D, 0xFE, 0x2B, 0xC1, 0x8B, 0xE5, 0x5D, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 
	0x55, 0x8B, 0xEC, 0x51, 0x8B, 0x45, 0x10, 0x89, 0x45, 0xFC, 0x8B, 0x4D, 0x10, 0x83, 0xE9, 0x01, 
	0x89, 0x4D, 0x10, 0x83, 0x7D, 0xFC, 0x00, 0x74, 0x2C, 0x8B, 0x55, 0x08, 0x8B, 0x45, 0x0C, 0x66, 
	0x8B, 0x08, 0x66, 0x89, 0x0A, 0x8B, 0x55, 0x08, 0x83, 0xC2, 0x02, 0x89, 0x55, 0x08, 0x8B, 0x45, 
	0x0C, 0x83, 0xC0, 0x02, 0x89, 0x45, 0x0C, 0x8B, 0x4D, 0x0C, 0x0F, 0xB7, 0x11, 0x85, 0xD2, 0x75, 
	0x02, 0xEB, 0x02, 0xEB, 0xBF, 0x8B, 0x45, 0x08, 0x8B, 0xE5, 0x5D, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 

};

/************************************************************************
#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "mmLoaderShellCode.h"

int main()
{
	// Function table
	NTFUNCPTRSTABLE sNtFuncPtrsTable;
	sNtFuncPtrsTable.pfnCreateFileW = CreateFileW;
	sNtFuncPtrsTable.pfnGetFileSize = GetFileSize;
	sNtFuncPtrsTable.pfnCreateFileMappingW = CreateFileMappingW;
	sNtFuncPtrsTable.pfnMapViewOfFile = MapViewOfFile;
	sNtFuncPtrsTable.pfnUnmapViewOfFile = UnmapViewOfFile;
	sNtFuncPtrsTable.pfnCloseHandle = CloseHandle;
	sNtFuncPtrsTable.pfnGetModuleHandleA = GetModuleHandleA;
	sNtFuncPtrsTable.pfnLoadLibraryA = LoadLibraryA;
	sNtFuncPtrsTable.pfnGetProcAddress = GetProcAddress;
	sNtFuncPtrsTable.pfnVirtualAlloc = VirtualAlloc;
	sNtFuncPtrsTable.pfnVirtualFree = VirtualFree;
	sNtFuncPtrsTable.pfnVirtualProtect = VirtualProtect;

	// Memory module
	MEM_MODULE sMemModule;
	::RtlZeroMemory(&sMemModule, sizeof(sMemModule));
	sMemModule.RawFile.h = INVALID_HANDLE_VALUE;
	sMemModule.pNtFuncptrsTable = &sNtFuncPtrsTable;

	// Allocate memory buffer for shell code with EXECUTE privilege
	LPVOID  lpShellCodeBase = ::VirtualAlloc(
		NULL,
		sizeof(mmLoaderShellCode),
		MEM_RESERVE | MEM_COMMIT,
		PAGE_EXECUTE_READWRITE);

	if (NULL == lpShellCodeBase)
	{
		::_tprintf(_T("Failed to allocate space for ShellCode!\r\n"));
		return FALSE;
	}

	// Copy shell code to the executable memory buffer
	::RtlCopyMemory(lpShellCodeBase, mmLoaderShellCode, sizeof(mmLoaderShellCode));

	// Get the helper function 
	Type_MemModuleHelper pfnMemModuleHelper = (Type_MemModuleHelper)lpShellCodeBase;

	// Load the module
	WCHAR wszDllPath[] = L"demo-module.dll";
	if (pfnMemModuleHelper(&sMemModule, MHM_BOOL_LOAD, wszDllPath, NULL, FALSE))
	{
		_tprintf(_T("Module was load user32.dll successfully.Module Base : 0x%p!\r\n"), sMemModule.lpBase);

		// Get address of function demoFunction
		LPVOID lpAddr = (LPVOID)pfnMemModuleHelper(&sMemModule, MHM_FARPROC_GETPROC, NULL, "demoFunction", FALSE);\r\n		if (lpAddr)
		{
			_tprintf(_T("Get address of demoFunction successfully.Address: 0x%p!\r\n"), lpAddr);

			// Function pointer type of demoFunction
			typedef int (WINAPI * Type_TargetFunction)(HWND, LPCSTR, LPCSTR, UINT);

			// Call the demoFunction
			Type_TargetFunction pfnFunction = (Type_TargetFunction)lpAddr;
			pfnFunction();
		}
		else
			_tprintf(_T("Failed to get address of demoFunction from memory module\r\n."));

		// Free the module
		pfnMemModuleHelper(&sMemModule, MHM_VOID_FREE, NULL, NULL, FALSE);
	}
	else
		_tprintf(_T("Failed to load the module!\r\n"));

	// Free the memory buffer of the shell code
	::VirtualFree(lpShellCodeBase, 0, MEM_RELEASE);

	return 0;
}
************************************************************************/

#endif // __MMLOADERSHELLCODE_H_INCLUDED_