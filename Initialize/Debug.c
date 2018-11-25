#include "Debug.h"

void initDbg()
{
	hfile = NULL;
}

void cleanDbg()
{
	CloseHandle(hfile);
}

void swFilePrint(WCHAR *input)
{
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;

	if (!hfile)
	{
		hfile = CreateFile("dbgResult.txt", GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	bErrorFlag = WriteFile(hfile, input, strWLen(input)*sizeof(WCHAR), &dwBytesWritten, NULL);

	//char *endLine = "\r\n";
	//bErrorFlag = WriteFile(hfile, endLine, strCLen(endLine), &dwBytesWritten, NULL);

	//CloseHandle(hfile);
}

void scFilePrint(char *input)
{
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;

	if (!hfile)
	{
		hfile = CreateFile("dbgResult.txt", GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	bErrorFlag = WriteFile(hfile, input, strCLen(input)*sizeof(char), &dwBytesWritten, NULL);

	//char *endLine = "\r\n";
	//bErrorFlag = WriteFile(hfile, endLine, strCLen(endLine), &dwBytesWritten, NULL);

	//CloseHandle(hfile);
}

void iFilePrint(int input)
{
	/*
	HANDLE out = CreateFile("test.txt", FILE_WRITE_DATA, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	int i = 12;
	int n;

	WriteFile(out, &i, sizeof i, &n, NULL);
	CloseHandle(out);
	*/

	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;

	char output = input + 48;
	if (!hfile)
	{
		hfile = CreateFile("dbgResult.txt", GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	bErrorFlag = WriteFile(hfile, &output, sizeof(output), &dwBytesWritten, NULL);
	
	//char *endLine = "\r\n";
	//bErrorFlag = WriteFile(hfile, endLine, strCLen(endLine), &dwBytesWritten, NULL);

	
	//CloseHandle(hfile);
}

void endLine()
{
	char *endLine = "\r\n";
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;

	bErrorFlag = WriteFile(hfile, endLine, strCLen(endLine), &dwBytesWritten, NULL);
}