#pragma once
#include <Windows.h>
#include "MyString.h"
//#include "TemporaryFile.h"


/**********************************
* For debug
***********************************/

//#define _Debug
#define _Gelobal
#define _EncryptDecrypt
#define _Main
#define _TemporaryFile

#ifdef _Debug
#include <stdio.h>
#endif


#define sizeBuffer 32
#define kEY_PATH_STR TEXT("SOFTWARE\\Init")
#define kEY_PATH_STR_C "SOFTWARE\\Init"

typedef wchar_t WCHAR;

// Continue loop condition
HANDLE g_StopEvent;

// save data of number and name of hard drive
typedef union
{
	struct _Data
	{
		WCHAR nameDrive[sizeBuffer];
		UINT16 numberOfDrive;
	}data;

	CHAR buffer[sizeBuffer * 2 + 2];
}Data;

// writh unicod string to registery
void SetStringWValueToRegistery(HKEY hkey, LPCTSTR name, WCHAR* data);

// read value's key in registery
HKEY ReadStringKey(LPCSTR address, LPCSTR keyName, char *outPut);
HKEY ReadNumberKey(LPCSTR address, LPCSTR keyName, DWORD *outPut);

void *_memset(void *dst, int val, int size);
void *_memcpy(void *dst, const void *src, size_t n);
