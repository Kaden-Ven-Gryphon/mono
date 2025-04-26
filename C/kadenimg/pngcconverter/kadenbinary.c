/****************************************************************************************
*
*	File:		kadenbinary.c
*	Author:	kaden Noctua
*	
*	Program:	kadenstdlib
*	
*	Use:		functions to work with biary data
*			
*****************************************************************************************/
#include "kadenbinary.h"
#define _DEBUG_MESSAGES
#ifdef _DEBUG_MESSAGES
	#include <stdio.h>
	#define DEBUG_LOG printf
#else
	#define DEBUG_LOG(...) {}
#endif

#define _ERROR_MESSAGES
#ifdef _ERROR_MESSAGES
	#include <stdio.h>
	#define ERROR_LOG fprintf
#else
	#define ERROR_LOG(...) {}
#endif





///////////////////////////////////////////////////////////////////////////////////////////////////////////

int kadenbinary_openFile(struct kadenbinary_bitReader_s* br, const char* fileName)
{
	DEBUG_LOG("START: kadenbinary_openFile\n");
	//clean up br
	if(br->mem != NULL) free(br->mem);


	FILE *fp;
	
	//find the file size
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		ERROR_LOG(stderr, "ERROR kadenbinary_openFile: failed to fopen %s\n", fileName);
		return 0;
	}
	if (fseek(fp, 0, SEEK_END) == -1)
	{
		ERROR_LOG(stderr, "ERROR kadenbinary_openFile: failed to fseek %s\n", fileName);
		return 0;
	}
	br->memLength = ftell(fp);
	if (br->memLength == -1)
	{
		ERROR_LOG(stderr, "ERROR kadenbinary_openFile: failed to ftell %s\n", fileName);
		return 0;
	}
	
	DEBUG_LOG("fileSize for file: %s, size: %llu\n", fileName, br->memLength);
	
	if(fclose(fp) != 0)
	{
		ERROR_LOG(stderr, "ERROR kadenbinary_openFile: failed to fclose %s\n", fileName);
		return 0;
	}
	
	
	//open the file
	fp = fopen(fileName, "r");
	if(!fp) {
		ERROR_LOG(stderr, "ERROR kadenbinary_openFile: failed to fopen %s\n", fileName);
		return 0;
	}
	
	//allcate a buffer for the file data
	br->mem = (unsigned char *)malloc(br->memLength);
	if(!br->mem)
	{
		ERROR_LOG(stderr, "ERROR kadenbinary_openFile: Couldn't allocate memory\n");
		return 0;
	}
	
	//copy the file into buffer
	unsigned long long bufsize = fread(br->mem, 1, br->memLength, fp);
	
	DEBUG_LOG("close file\n");
	
	if(fclose(fp) != 0)
	{
		ERROR_LOG(stderr, "ERROR kadenbinary_openFile: failed to fclose %s\n", fileName);
		free(br->mem);
		return 0;
	}
	br->bytePos = 0;
	br->bitPos = 0;
	return bufsize;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int kadenvinary_closeFile(struct kadenbinary_bitReader_s* br)
{
	if(br->mem != NULL) free(br->mem);
	return 0;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////

int kadenbinary_toint(const unsigned char* buf, int len)
{
	int retVal = 0;
	int offSet = 8*(len-1);
	for(int i = 0; i < len; i++)
	{
		retVal |= ((unsigned char)buf[i] << offSet);
		offSet -= 8;
	}
	return retVal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int kadenbinary_tointRByte(const unsigned char* buf, int len)
{
	int retVal = 0;
	int offSet = 8*(len-1);
	for(int i = len-1; i >= 0; i--)
	{
		retVal |= ((unsigned char)buf[i] << offSet);
		offSet -= 8;
	}
	return retVal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned long kadenbinary_toulong(const unsigned char* buf, int len)
{
	unsigned long retVal = 0;
	int offSet = 8*(len-1);
	for(int i = 0; i < len; i++)
	{
		retVal |= ((unsigned char)buf[i] << offSet);
		offSet -= 8;
	}
	return retVal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

char kadenbinary_readbit(struct kadenbinary_bitReader_s* br)
{
	if(br->bytePos < br->memLength)
	{
		char retVal = 0;
		retVal = br->mem[br->bytePos] & (0x1 << (br->bitPos));
		br->bitPos++;
		if(br->bitPos > 7)
		{
			br->bitPos = 0;
			br->bytePos++;
		}
		if(retVal) return 1;
		else return 0;
	}
	return 2;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int kadenbinary_readbits(struct kadenbinary_bitReader_s* br, int n)
{
	int retVal = 0;
	for(int i = 0; i < n; i++)
	{
		retVal |= kadenbinary_readbit(br) << i;
	}
	return retVal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int kadenbinary_hexdump(struct kadenbinary_bitReader_s* br, char mode)
{
	DEBUG_LOG("START hexdump\n\n");
	int width = 8;
	for(int i = 0; i < br->memLength; i++)
	{
		if(i % width == 0) DEBUG_LOG("\n");
		DEBUG_LOG("%02x ", br->mem[i]);
		
	}
	DEBUG_LOG("\n\nEND hexdump\n\n");
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int kadenbinary_bindump(struct kadenbinary_bitReader_s* br, char mode)
{
	DEBUG_LOG("START bindump\n\n");
	int width = 8;
	for(int i = 0; i < br->memLength; i++)
	{
		if(i % width == 0) DEBUG_LOG("\n");
		int bit = 1;
		for(int j = 0; j < 8; j++)
		{
			if(br->mem[i] & bit << j)
			{
				DEBUG_LOG("1");
			}
			else
			{
				DEBUG_LOG("0");
			}
			if(j == 3) DEBUG_LOG(" ");
		}
		DEBUG_LOG("\t");
	}
	DEBUG_LOG("\n\nEND bindump\n\n");
	return 0;
}

