#include "vigenere.h"

//debuging: comment out line below to turn debuging off
#define _DEBUG_MESSAGES
#ifdef _DEBUG_MESSAGES
	#include <stdio.h>
	#define DEBUG_LOG printf
#else
	#define DEBUG_LOG(...) {}
#endif


int vigenere_encode(char* plainText, char* key, char* cipherText, int ctLength)
{
	DEBUG_LOG("%s, %s, %s, %d\n", plainText, key, cipherText, ctLength);
	return 0;
}
