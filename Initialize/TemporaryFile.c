#include "TemporaryFile.h"

int FileExists(char* filepath)
{
	DWORD dwAttrib = GetFileAttributes(filepath);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

int GetTemporaryFilePath(char* filePrefix, char* fileExt, char* TmpFilePath, WCHAR* buffer)
{
	char TempPath[MAX_PATH] = { 0 };
	HANDLE hFile;

	if (!GetTempPath(MAX_PATH, TempPath))
	{
		return -1;
	}

	_strCCat(TmpFilePath, TempPath);
	_strCCat(TmpFilePath, filePrefix);
	_strCCat(TmpFilePath, fileExt);


	if (!FileExists(TmpFilePath))
	{
		hFile = CreateFile(TmpFilePath, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, 0, NULL);

		DWORD bytes;
		WriteFile(hFile, buffer, strWLen(buffer)*sizeof(WCHAR), &bytes, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
#if defined(_Debug) && defined(_TemporaryFile)
			scFilePrint("unable to open file for read.\n");
			endLine();
#endif
			return 0;
		}
		CloseHandle(hFile);
	}
	else
	{
		ZeroMemory(TmpFilePath, strCLen(TmpFilePath));
		_strCCat(TmpFilePath, "File alredy is createded.");
	}

	return 0;
}

void writhPathKeyToTempFile(HKEY input)
{
	HKEY key = input;
	LONG ret = ERROR_SUCCESS;
	WCHAR *buffer = NULL;

	if (key != NULL)
	{
		HMODULE dll = LoadLibrary(TEXT("ntdll.dll"));
		if (dll != NULL)
		{
			typedef DWORD(__stdcall *NtQueryKeyType)(HANDLE  KeyHandle, int KeyInformationClass,
				PVOID  KeyInformation, ULONG  Length, PULONG  ResultLength);

			NtQueryKeyType func = (NtQueryKeyType)(GetProcAddress(dll, "NtQueryKey"));

			if (func != NULL)
			{
				DWORD size = 0;
				DWORD result = 0;
				result = func(key, 3, 0, 0, &size);
				if (result == STATUS_BUFFER_TOO_SMALL)
				{
					size = size + 2;
					int t = size / sizeof(WCHAR);

					//size is in bytes
					buffer = (WCHAR*)malloc(t + t + 200); //(!)
					if (buffer != NULL)
					{
						result = func(key, 3, buffer, size, &size);
						if (result == STATUS_SUCCESS)
						{
							buffer[size / sizeof(WCHAR)] = L'\0';
						}
					}
				}
			}
			FreeLibrary(dll);
		}
	}

	char tempFilePath[MAX_PATH] = { '\0' };
	GetTemporaryFilePath("initDataFile", ".txt", tempFilePath, buffer + 2);


#if defined(_Debug) && defined(_TemporaryFile)
	scFilePrint("*Address of REG of data save : ");
	swFilePrint(buffer + 2);
	endLine();
#endif

	free(buffer);
	buffer = NULL;
}
