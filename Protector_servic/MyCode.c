#include "MyCode.h"

DWORD WINAPI searchFunc(CHAR nameDrive)
{
	CHAR strNameDrive[3];
	strNameDrive[0] = nameDrive;
	strNameDrive[1] = ':';
	strNameDrive[2] = '\\';

	HANDLE handle = FindFirstChangeNotification("D:\\", 1, FILE_NOTIFY_CHANGE_FILE_NAME);

	while (1)
	{
		WaitForSingleObject(handle, INFINITE);
		//printf("File name is change\n");
		FindNextChangeNotification(handle);
	}
}

void MyCode()
{
	initDbg();

	int i, threadCounter = 0, NumberOfDrive = 0;
	HANDLE hThread[sizeBuffer] = { NULL };
	CHAR nameDrive[sizeBuffer] = { '\0' };

	// Get data from registery
	ReadStringKey(kEY_PATH_STR_C, "Name_Drive", nameDrive);
	ReadNumberKey(kEY_PATH_STR_C, "Number_Of_Drive", &NumberOfDrive);
	
	for (i = 0; i < NumberOfDrive - 1; i++)
	{
		hThread[threadCounter] = CreateThread(NULL, 0, searchFunc, nameDrive[i], 0, NULL);
		threadCounter++;
	}
	
	// For debug
	swFilePrint(nameDrive);

	// Waiting ...
	while (WaitForSingleObject(g_StopEvent, 3000) != WAIT_OBJECT_0)
	{
		Sleep(6000);
		//Place Your Code for processing here....
	}

	// Terminate all Thread
	for (i = 0; i < threadCounter; i++)
	{
		TerminateThread(hThread[i], 0);
	}

	// Close all thread handles upon completion.
	for (i = 0; i < threadCounter; i++)
	{
		CloseHandle(hThread[i]);
	}

	cleanDbg();
}