#include "EncryptDecrypt.h"
#include "global.h"
#include "TemporaryFile.h"
#include "Debug.h"

void main(void)
{
#if defined(_Debug)
	initDbg();
#endif

	Data objData;
	
	_memset(&objData, 0, sizeof(Data));
	
	// copy drive name to struct
	FindeDrive(&objData);

	// get noumbr of drive	
	objData.numberOfDrive = strWLen(objData.nameDrive);
	objData.numberOfDrive = objData.numberOfDrive + 1; // For OS drive
	
#if defined(_Debug) && defined(_Main)
	scFilePrint("*Number of drive : ");
	iFilePrint(objData.numberOfDrive);
	endLine();
	scFilePrint("*Name drive : ");
	swFilePrint(objData.nameDrive);
	endLine();
	endLine();
#endif

	// write on registery
	HKEY hkey = NULL;
	hkey = CreateKey(hkey, kEY_PATH_STR);

	char *temp[sizeBuffer];
	wcharToChar(objData.nameDrive, temp, strWLen(objData.nameDrive));

	SetStringWValueToRegistery(hkey, (LPCTSTR)"Name_Drive", temp);
	
	_memset(temp, NULL, strCLen(temp));
	wcharToChar(objData.OSDrive, temp, strWLen(objData.OSDrive));

	SetStringWValueToRegistery(hkey, (LPCTSTR)"Name_OS_Drive", temp);
	SetNumberValueToRegistery(hkey, (LPCTSTR)"Number_Of_Drive", objData.numberOfDrive);


	writhPathKeyToTempFile(hkey);

	RegCloseKey(hkey);

//#if defined(_Debug) && defined(_Main)
	system("pause");
//#endif

#if defined(_Debug)
	cleanDbg();
#endif

	return;
}