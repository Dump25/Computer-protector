#include "MyString.h"


void strWCopy(wchar_t *str1, wchar_t *str2)
{
	int i;

	for (i = 0; str2[i] != '\0'; i++)
	{
		str1[i] = str2[i];
	}
	str1[i] = '\0';
}

void strCCopy(char *str1, char *str2)
{
	int i;

	for (i = 0; str2[i] != '\0'; i++)
	{
		str1[i] = str2[i];
	}
	str1[i] = '\0';
}

UINT strWLen(wchar_t *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++);

	return i;
}

UINT strCLen(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++);

	return i;
}

void _strCCat(char *arg1, char *arg2)
{
	int size1, size2, i, j;

	size1 = strCLen(arg1);
	size2 = strCLen(arg2);

	for (i = size1, j = 0; j < size2; i++, j++)
	{
		arg1[i] = arg2[j];
	}
}

void _strWCat(WCHAR *arg1, WCHAR *arg2)
{
	int size1, size2, i, j;

	size1 = strWLen(arg1);
	size2 = strWLen(arg2);

	for (i = size1, j = 0; j < size2; i++, j++)
	{
		arg1[i] = arg2[j];
	}
}

void wcharToChar(const WCHAR* src, char* dest, int dest_len)
{
	int i = 0;
	wchar_t code;

	while (i < (dest_len))
	{
		code = src[i];
		if (code < 128)
		{
			dest[i] = (char)code;
		}
		else
		{
			dest[i] = '?';
			if (code >= 0xD800 && code <= 0xD8FF)
				// lead surrogate, skip the next code unit, which is the trail
				i++;
		}
		i++;
	}

	dest[i] = '\0';
}

void charToWchar(const char* src, WCHAR* dest, int dest_len)
{
	int i;

	for (i = 0; i <= dest_len; i++)
	{
		dest[i] = (wchar_t)src[i];
	}
}

