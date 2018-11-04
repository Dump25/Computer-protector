#pragma once
#include <Windows.h>
#include "MyString.h"

HANDLE hfile;

void initDbg();

void cleanDbg();

void swFilePrint(WCHAR *input);

void scFilePrint(char *input);

void iFilePrint(int input);

void endLine();