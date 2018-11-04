#include "global.h"

// (Internal) Finde lable name hard drive from volume Name 
void DisplayVolumePaths(PWCHAR volumeName, PWCHAR NameIdx)
{
	DWORD  charCount = MAX_PATH + 1;
	PWCHAR names = NULL;
	BOOL   success = FALSE;
	static int counterDrive = 0;
	int i;

	while (1)
	{
		//Allocate a buffer to hold the paths.
		names = (PWCHAR)malloc(charCount * sizeof(WCHAR));

		if (!names)
		{
			//If memory can't be allocated, return.
			return;
		}

		//Obtain all of the paths for this volume.
		success = GetVolumePathNamesForVolumeNameW(volumeName, names, charCount, &charCount);

		if (success)
		{
			break;
		}

		if (GetLastError() != ERROR_MORE_DATA)
		{
			break;
		}

		//Try again with the new suggested size.
		free(names);
		names = NULL;
	}

	if (success)
	{
		for (i = 0; names[i] != L':' && names[i] != NULL; i++)
		{
			NameIdx[counterDrive] = names[i];
			counterDrive++;
		}
		NameIdx[counterDrive] = NULL;
	}

	if (names != NULL)
	{
		free(names);
		names = NULL;
	}

	return;
}

void FindeDrive(WCHAR *NameDrive)
{
	DWORD  charCount = 0;
	WCHAR  deviceName[MAX_PATH] = L"";
	DWORD  error = ERROR_SUCCESS;
	HANDLE findHandle = INVALID_HANDLE_VALUE;
	size_t index = 0;
	BOOL   success = FALSE;
	WCHAR  volumeName[MAX_PATH] = L"";


	//  Enumerate all volumes in the system.
	findHandle = FindFirstVolumeW(volumeName, ARRAYSIZE(volumeName));

	if (findHandle == INVALID_HANDLE_VALUE)
	{
		error = GetLastError();

#if defined(_Debug) && defined(_Gelobal)
		scFilePrint("FindFirstVolumeW failed with error code");
		endLine();
#endif

		return;
	}

	while (1)
	{
		//  Skip the \\?\ prefix and remove the trailing backslash.
		index = wcslen(volumeName) - 1;

		if (volumeName[0] != L'\\' || volumeName[1] != L'\\' ||
			volumeName[2] != L'?' || volumeName[3] != L'\\' ||
			volumeName[index] != L'\\')
		{
			error = ERROR_BAD_PATHNAME;

#if defined(_Debug) && defined(_Gelobal)
			scFilePrint("FindFirstVolumeW/FindNextVolumeW returned a bad path: ");
			swFilePrint(volumeName);
			endLine();
#endif
			break;
		}

		//  QueryDosDeviceW does not allow a trailing backslash, so temporarily remove it.
		volumeName[index] = L'\0';
		charCount = QueryDosDeviceW(&volumeName[4], deviceName, ARRAYSIZE(deviceName));
		volumeName[index] = L'\\';

		if (charCount == 0)
		{
			error = GetLastError();
#if defined(_Debug) && defined(_Gelobal)
			scFilePrint("QueryDosDeviceW failed with error code");
#endif
			break;
		}


#if defined(_Debug) && defined(_Gelobal)
		scFilePrint("Found a device: ");
		swFilePrint(deviceName);
		endLine();

		scFilePrint("Volume name: ");
		swFilePrint(volumeName);
		endLine();
		//scFilePrint("Paths: ");
#endif
		DisplayVolumePaths(volumeName, NameDrive);

		//  Move on to the next volume.
		success = FindNextVolumeW(findHandle, volumeName, ARRAYSIZE(volumeName));

		if (!success)
		{
			error = GetLastError();

			if (error != ERROR_NO_MORE_FILES)
			{
#if defined(_Debug) && defined(_Gelobal)
				swFilePrint("FindNextVolumeW failed with error code");
#endif
				break;
			}

			// Finished iterating through all the volumes.
			error = ERROR_SUCCESS;
			break;
		}
	}

	FindVolumeClose(findHandle);
	findHandle = INVALID_HANDLE_VALUE;

	endLine();
	endLine();

	return;
}

HKEY CreateKey(HKEY hkey, LPCSTR address)
{
	DWORD displosition;
	LONG error;
	error = RegCreateKeyEx(HKEY_LOCAL_MACHINE, address, 0, NULL, REG_OPTION_VOLATILE,
		KEY_ALL_ACCESS, NULL, &hkey, &displosition);

	if (error)
	{
#if defined(_Debug) && defined(_Gelobal)
		scFilePrint("Error, Could not creat key");
		endLine();
#endif
	}

	return hkey;
}

void SetStringWValueToRegistery(HKEY hkey, LPCTSTR name, WCHAR* data)
{
	LONG error = RegSetValueEx(hkey, name, NULL, REG_SZ, data, strWLen(data)*sizeof(WCHAR));
	
	if (error)
	{
#if defined(_Debug) && defined(_Gelobal)
		scFilePrint("error, Could not set registry value: ");
		endLine();
#endif
	}
}

void  *_memset(void *dst, int val, int size)
{
	int i = 0;
	unsigned char *ptr = dst;

	while (size > 0)
	{
		*ptr = val;
		ptr++;
		size--;
	}

	return dst;
}

void *_memcpy(void *s1, const void *s2, size_t n)
{
	char *ptr1 = s1;
	const char *ptr2 = s2;

	if (n) 
	{
		n++;
		while (--n > 0) 
		{
			*ptr1++ = *ptr2++;
		}
	}
	return s1;
}
