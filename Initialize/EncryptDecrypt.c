#include "EncryptDecrypt.h"

// prints string as hex
void phex(UCHAR* str)
{
	UCHAR len = 16;
	UCHAR i;
#if defined(_Debug) && defined(_EncryptDecrypt)
//	for (i = 0; i < len; ++i)
//		printf("%.2x", str[i]);
	scFilePrint(str);
	endLine();
//	printf("\n");
#endif
}

void encryptEcb(UCHAR* key, UCHAR* buffer, UCHAR* crypedData)
{
	// Example of more verbose verification
	UCHAR i, buf[sizeBuffer];

	//memset(buf, 0, sizeBuffer);
	_memset(buf, 0, sizeBuffer);

	// print text to encrypt, key and IV
#if defined(_Debug) && defined(_EncryptDecrypt)
	scFilePrint("*ECB encrypt verbose: ");
	endLine();
	endLine();
#endif

	// print the resulting cipher as 4 x 16 byte strings
#if defined(_Debug) && defined(_EncryptDecrypt)
	scFilePrint("*ciphertext: ");
	endLine();
#endif

	for (i = 0; i < (sizeBuffer - 1) / sizeKey; ++i)
	{
		AES_ECB_encrypt(buffer + (i * sizeKey), key, buf + (i * sizeKey), sizeKey);
		//memcpy(crypedData + (i * sizeKey), buf + (i * sizeKey), sizeKey);
		_memcpy(crypedData + (i * sizeKey), buf + (i * sizeKey), sizeKey);
		phex(buf + (i * sizeKey));
	}

	crypedData[i * sizeKey] = '\0';

#if defined(_Debug) && defined(_EncryptDecrypt)
	endLine();
#endif
}

void decryptEcb(UCHAR* key, UCHAR* buffer)
{
	// Example of more verbose verification

	UCHAR i, buf[sizeBuffer];

	//memset(buf, 0, sizeBuffer);
	_memset(buf, 0, sizeBuffer);

	// print text to encrypt, key and IV
#if defined(_Debug) && defined(_EncryptDecrypt)
	scFilePrint("ECB decrypt verbose: ");
	endLine();
	endLine();
#endif

	// print the resulting cipher as 4 x 16 byte strings
#if defined(_Debug) && defined(_EncryptDecrypt)
	scFilePrint("decrypText: ");
#endif

	for (i = 0; i < (sizeBuffer - 1) / sizeKey; i++)
	{
		AES_ECB_decrypt(buffer + (i * sizeKey), key, buf + (i * sizeKey), sizeKey);
		phex(buf + (i * sizeKey));
		if (strWLen(buf + (i * sizeKey)) != 0)
		{
			break;
		}
	}
	_memcpy(buffer, buf, sizeof(buf));

#if defined(_Debug) && defined(_EncryptDecrypt)
	endLine();
#endif
}
