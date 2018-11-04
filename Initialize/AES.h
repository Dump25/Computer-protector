#ifndef _AES_H_
#define _AES_H_

#include "global.h"

#define sizeKey    16
UCHAR key[sizeKey];

// #define the macros below to 1/0 to enable/disable the mode of operation.
//
// CBC enables AES encryption in CBC-mode of operation.
// ECB enables the basic ECB 16-byte block algorithm. Both can be enabled simultaneously.

// The #ifndef-guard allows it to be configured before #include'ing or at compile time.
#ifndef CBC
  #define CBC 1
#endif

#ifndef ECB
  #define ECB 1
#endif

#if defined(ECB) && ECB

void AES_ECB_encrypt(const UCHAR* input, const UCHAR* key, UCHAR *output, const UINT length);
void AES_ECB_decrypt(const UCHAR* input, const UCHAR* key, UCHAR *output, const UINT length);

#endif // #if defined(ECB) && ECB


#if defined(CBC) && CBC

void AES_CBC_encrypt_buffer(UCHAR* output, UCHAR* input, UINT length, const UCHAR* key, const UCHAR* iv);
void AES_CBC_decrypt_buffer(UCHAR* output, UCHAR* input, UINT length, const UCHAR* key, const UCHAR* iv);

#endif // #if defined(CBC) && CBC


#endif //_AES_H_
