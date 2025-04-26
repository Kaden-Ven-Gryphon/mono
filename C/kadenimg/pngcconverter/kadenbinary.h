/****************************************************************************************
*
*	File:		kadenbinary.h
*	Author:	kaden Noctua
*	
*	Program:	kadenstdlib
*	
*	Use:		functions to manipulate binary strings
*			
*****************************************************************************************/
#ifndef kadenBINARY_H
#define kadenBINARY_H

#include<stdlib.h>

#define kadenBINARY_NEWBITREADER (struct kadenbinary_bitReader_s*)malloc(sizeof(struct kadenbinary_bitReader_s))

struct kadenbinary_bitReader_s
{
	unsigned char* mem;
	unsigned long long memLength;
	unsigned long long bytePos;
	int bitPos;
};

int kadenbinary_openFile(struct kadenbinary_bitReader_s* br, const char* fileName);
int kadenvinary_closeFile(struct kadenbinary_bitReader_s* br);

int kadenbinary_toint(const unsigned char* buf, int len);
int kadenbinary_tointRByte(const unsigned char* buf, int len);
unsigned long kadenbinary_toulong(const unsigned char* buf, int len);

char kadenbinary_readbit(struct kadenbinary_bitReader_s* br);
int kadenbinary_readbits(struct kadenbinary_bitReader_s* br, int n);


int kadenbinary_hexdump(struct kadenbinary_bitReader_s* br, char mode);
int kadenbinary_bindump(struct kadenbinary_bitReader_s* br, char mode);
#endif
