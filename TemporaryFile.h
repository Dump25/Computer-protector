#pragma once
#include "global.h"
#include "MyString.h"
#include "Debug.h"

typedef LONG NTSTATUS;

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#endif

#ifndef STATUS_BUFFER_TOO_SMALL
#define STATUS_BUFFER_TOO_SMALL ((NTSTATUS)0xC0000023L)
#endif


int FileExists(char* filepath);

int GetTemporaryFilePath(char*  filePrefix, char*  fileExt, char* TmpFilePath, WCHAR* buffer);

void writhPathKeyToTempFile(HKEY input);
