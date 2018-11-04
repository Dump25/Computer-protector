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
	UINT8 crypedData[sizeBuffer];

	_memset(&objData, 0, sizeof(Data));
	_memset(crypedData, 0, sizeBuffer);

	// copy drive name to struct
	FindeDrive(objData.data.nameDrive);

	// get noumbr of drive	
	objData.data.numberOfDrive = strWLen(objData.data.nameDrive);

	
#if defined(_Debug) && defined(_Main)
	scFilePrint("*Number of drive : ");
	iFilePrint(objData.data.numberOfDrive);
	endLine();
	scFilePrint("*Name drive : ");
	swFilePrint(objData.data.nameDrive);
	endLine();
	endLine();
#endif

	// write on registery
	HKEY hkey = NULL;
	hkey = CreateKey(hkey, kEY_PATH_STR);
	encryptEcb(key, objData.data.nameDrive, crypedData);
	SetStringWValueToRegistery(hkey, (LPCTSTR)"Name Drive", crypedData);
	
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