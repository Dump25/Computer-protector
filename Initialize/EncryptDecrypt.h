#pragma once
#include "global.h"
#include "AES.h"
#include "MyString.h"
#include "Debug.h"


#define CBC 1
#define ECB 1
#define sizeKey    16

// show string to hex
void phex(UCHAR* str);

// encrypt data
void encryptEcb(UCHAR*, UCHAR*, UCHAR*);

// dencrypt data
void decryptEcb(UCHAR*, UCHAR*);
