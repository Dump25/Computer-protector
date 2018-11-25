#include "global.h"


int pow(int a, int b)
{
	int val = 1;
	for (int i = 0; i < b; i++)
	{
		val *= a;
	}
	return val;
}

int cp_length(char* cp)
{
	int i = 0;
	while (cp[i] != '\0')
	{
		i++;
	}
	return i;
}

int charToInt(char* cp)
{
	int val = 0;
	for (int j = cp_length(cp) - 1, i = 0; j >= 0; j--, i++)
	{
		if (cp[i] < 0x30 || cp[i] > 0x39) // if the character is not a digit                                                                                                                                                                                                                      
		{
			continue;
		}
		else
		{
			val += (cp[0] == '-' ? -(cp[i] - 0x30) * pow(10, j) : +(cp[i] - 0x30) * pow(10, j));
		}
	}
	return val;
}


HKEY ReadStringKey(LPCSTR address, LPCSTR keyName, char *outPut)
{
	char value[sizeBuffer + 2];
	DWORD BufferSize = 8192;
	LONG error = RegGetValue(HKEY_LOCAL_MACHINE, address, keyName,
		RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);

	strCCopy(outPut, value);

	if (error)
	{
#if defined(_Debug) && defined(_Gelobal)
		scFilePrint("Error, Could not creat key");
		endLine();
#endif
	}
	//std::cout << value << std::endl;
}

HKEY ReadNumberKey(LPCSTR address, LPCSTR keyName, DWORD *outPut)
{
	char value[32 + 2];
	DWORD BufferSize = 8192;
	LONG error = RegGetValue(HKEY_LOCAL_MACHINE, kEY_PATH_STR_C, "Number_Of_Drive"/*"Name_Drive",*//*"Number_Of_Drive"*/,
		RRF_RT_REG_BINARY, NULL, (PVOID)&value, &BufferSize);

	*outPut = charToInt(value);
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
