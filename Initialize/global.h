#pragma once
#include <Windows.h>
#include "TemporaryFile.h"


/**********************************
* For debug
***********************************/
#define _Debug
//#define _Gelobal
#define _EncryptDecrypt
//#define _Main
//#define _TemporaryFile

#ifdef _Debug
#include <stdio.h>
#endif



#define ERORE_IN_SIZE 0;
#define SIZE_IS_TRUE 0;
#define sizeBuffer 32
#define kEY_PATH_STR TEXT("SOFTWARE\\Init")

typedef wchar_t WCHAR;

// save data of number and name of hard drive
typedef struct _Data
{
	WCHAR nameDrive[sizeBuffer];
	WCHAR OSDrive[sizeBuffer];
	UINT16 numberOfDrive;
}Data;

// Finde lable name drive hard drive
void FindeDrive(Data *input);

// writh unicod string to registery
void SetStringWValueToRegistery(HKEY hkey, LPCTSTR name, WCHAR* data);

// writh number to registery
void SetNumberValueToRegistery(HKEY hkey, LPCTSTR name, DWORD data);

// create key in registery
HKEY CreateKey(HKEY hkey, LPCSTR address);

void *_memset(void *dst, int val, int size);

void *_memcpy(void *dst, const void *src, size_t n);
