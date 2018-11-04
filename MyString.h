#pragma once
#include "global.h"

void strWCopy(wchar_t *input1, wchar_t *input2);

void strCCopy(char *input1, char *input2);

UINT strWLen(wchar_t *input);

UINT strCLen(char *input);

void _strCCat(char *arg1, char *arg2);

void _strWCat(WCHAR *arg1, WCHAR *arg2);
