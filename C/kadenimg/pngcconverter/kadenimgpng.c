/****************************************************************************************
*
*	File:		kadenimgpng.c
*	Author:	kaden Noctua
*	
*	Program:	kadenimglib
*	
*	Use:		function to read and write png files
*			
*	Source:	png parsing info: https://www.rfc-editor.org/rfc/rfc2083.html
*****************************************************************************************/
#include "kadenimgpng.h"

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

//Look up tables ###########################################################################
const char PNGSIG[] = { 0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A };

struct kadenimgpng_handler HANDLERS[] = {
	{ "IHDR", kadenimgpng_headerhandler },
	{ "bKGD", kadenimgpng_backgroundhandler },
	{ "pHYs", kadenimgpng_pixelhandler },
	{ "tIME", kadenimgpng_timehandler },
	{ "iTXt", kadenimgpng_texthandler },
	{ "IDAT", kadenimgpng_datahandler },
	{ "IEND", kadenimgpng_endHandler },
	{ NULL, NULL }
};

//CRCs
int _CRC_TABLE_COMPUTED = 0;
unsigned long _CRC_TABLE[256];

//Private functions
//populate crc table
void _make_crc_table(void)
{
	unsigned long c;
	for (int i = 0; i < 256; i++)
	{
		c = (unsigned long) i;
		for(int j = 0; j < 8; j++)
		{
			if (c & 1) c = 0xedb88320L ^ (c >> 1);
			else c = c >> 1;
		}
		_CRC_TABLE[i] = c;
	}
	_CRC_TABLE_COMPUTED = 1;
}

unsigned long _update_crc(unsigned long crc, const unsigned char *buf, int len)
{
	unsigned long c = crc;
	
	if(!_CRC_TABLE_COMPUTED) _make_crc_table();
	
	for(int i = 0; i < len; i++)
	{
		c = _CRC_TABLE[(c ^ buf[i]) & 0xff] ^ (c >> 8);
	}
	return c;
}

unsigned long _crc(const unsigned char* buf, int len)
{
	return _update_crc(0xffffffffL, buf, len) ^ 0xffffffffffffffffL;
}

//public functions ########################################################################
unsigned long long kadenimgpng_fileSize(const char* filename)
{
	FILE *fp = NULL;
	unsigned long long fileSize = 0;
	
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		ERROR_LOG(stderr, "ERROR kadenimgpng_fileSize: failed to fopen %s\n", filename);
		return 0;
	}
	if (fseek(fp, 0, SEEK_END) == -1)
	{
		ERROR_LOG(stderr, "ERROR kadenimgpng_fileSize: failed to fseek %s\n", filename);
		return 0;
	}
	fileSize = ftell(fp);
	if (fileSize == -1)
	{
		ERROR_LOG(stderr, "ERROR kadenimgpng_fileSize: failed to ftell %s\n", filename);
		return 0;
	}
	
	DEBUG_LOG("fileSize for file: %s, size: %llu\n", filename, fileSize);
	
	if(fclose(fp) != 0)
	{
		ERROR_LOG(stderr, "ERROR kadenimgpng_fileSize: failed to fclose %s\n", filename);
		return 0;
	}
	
	return fileSize;
}


int kadenimgpng_confirmPNG(const char* filename)
{	
	FILE *fp;
	char *buf = (char *)malloc(8);
	if(!buf)
	{
		ERROR_LOG(stderr, "ERROR kadenimgpng_confirmPNG: Couldn't allocate memory\n");
		return 0;
	}
	
	fp = fopen(filename, "r");
	if(!fp) {
		ERROR_LOG(stderr, "ERROR kadenimgpng_confirmPNG: failed to fopen %s\n", filename);
		free(buf);
		return 0;
	}
	int size = fread(buf, 1, 8, fp);
	if(size == 8)
	{
		size = 0;
		for(int i = 0; i < 8; i++)
		{
			if(buf[i] != PNGSIG[i])
			{
				DEBUG_LOG("signature byte %d failed\n", i);
			}
			else
			{
				size++;
			}
		}
	}
	else
	{
		size = 0;
		ERROR_LOG(stderr, "ERROR kadenimgpng_confirmPNG: failed to fread %s\n", filename);
	}
	
	
	
	if(fclose(fp) != 0)
	{
		ERROR_LOG(stderr, "ERROR kadenimgpng_fileSize: failed to fclose %s\n", filename);
		return 0;
	}
	
	if(size != 8)
	{
		DEBUG_LOG("could not confirm that %s was a PNG\n", filename);
	}
	else
	{
		DEBUG_LOG("%s confirmed to be a PNG\n", filename);
	}
	return size;
}


//handlers ################################################################################
int kadenimgpng_headerhandler(const unsigned char* buf, int len, struct pngData_s* png)
{
	DEBUG_LOG("START header handler\n");
	unsigned long crcTest = _crc(buf, len+4);
	DEBUG_LOG("check crc found: 0x%lx expected 0x%lx\n", crcTest, kadenbinary_toulong(buf+len+4, 4));
	if(crcTest == kadenbinary_toulong(buf+len+4, 4) || (crcTest & 0xffffffffL) == kadenbinary_toulong(buf+len+4, 4))
	{
		DEBUG_LOG("CRC: OK\n");
	}
	else
	{
		DEBUG_LOG("CRC: FAIL\n");
		return 1;
	}

	png->width = kadenbinary_toint(buf+4, 4);
	DEBUG_LOG("width: %d\n", png->width);
	
	png->height = kadenbinary_toint(buf+8, 4);
	DEBUG_LOG("height: %d\n", png->height);
	
	png->bitDepth = *(buf + 12);
	DEBUG_LOG("bit depth: %d\n", (int)png->bitDepth);
	
	png->colorType = *(buf + 13);
	DEBUG_LOG("color type: %d\n", (int)png->colorType);
	
	png->compressionMethod = *(buf + 14);
	DEBUG_LOG("compression method: %d\n", (int)png->compressionMethod);
	
	png->filterMethod = *(buf + 15);
	DEBUG_LOG("filter method: %d\n", (int)png->filterMethod);
	
	png->interlaceMethod = *(buf + 16);
	DEBUG_LOG("interlace method: %d\n", (int)png->interlaceMethod);
	
	
	return 0;
}


int kadenimgpng_backgroundhandler(const unsigned char* buf, int len, struct pngData_s* png)
{
	DEBUG_LOG("START background handler\n");
	unsigned long crcTest = _crc(buf, len+4);
	DEBUG_LOG("check crc found: 0x%lx expected 0x%lx\n", crcTest, kadenbinary_toulong(buf+len+4, 4));
	if(crcTest == kadenbinary_toulong(buf+len+4, 4) || (crcTest & 0xffffffffL) == kadenbinary_toulong(buf+len+4, 4))
	{
		DEBUG_LOG("CRC: OK\n");
	}
	else
	{
		DEBUG_LOG("CRC: FAIL\n");
		return 1;
	}
	switch(png->colorType)
	{
	case 3:
		png->backgroundColor[0] = (int)*(buf+4);
		DEBUG_LOG("Palette index %d\n", png->backgroundColor[0]);
		break;
	case 0:
	case 4:
		png->backgroundColor[0] = kadenbinary_toint(buf+4, 2);
		DEBUG_LOG("Gray index %d\n", png->backgroundColor[0]);
		break;
	case 2:
	case 6:
		png->backgroundColor[0] = kadenbinary_toint(buf+4, 2);
		png->backgroundColor[1] = kadenbinary_toint(buf+6, 2);
		png->backgroundColor[2] = kadenbinary_toint(buf+8, 2);
		DEBUG_LOG("Red index %d\n", png->backgroundColor[0]);
		DEBUG_LOG("Green index %d\n", png->backgroundColor[1]);
		DEBUG_LOG("Blue index %d\n", png->backgroundColor[2]);
		break; 
	}
	
	return 0;
}


int kadenimgpng_pixelhandler(const unsigned char* buf, int len, struct pngData_s* png)
{
	DEBUG_LOG("START pixel handler\n");
	unsigned long crcTest = _crc(buf, len+4);
	DEBUG_LOG("check crc found: 0x%lx expected 0x%lx\n", crcTest, kadenbinary_toulong(buf+len+4, 4));
	if(crcTest == kadenbinary_toulong(buf+len+4, 4) || (crcTest & 0xffffffffL) == kadenbinary_toulong(buf+len+4, 4))
	{
		DEBUG_LOG("CRC: OK\n");
	}
	else
	{
		DEBUG_LOG("CRC: FAIL\n");
		return 1;
	}
	
	png->pixelPerUnitX = kadenbinary_toint(buf+4, 4);
	png->pixelPerUnitY = kadenbinary_toint(buf+8, 4);
	png->pixelSizeUnit = *(buf+9);
	
	
	DEBUG_LOG("Pixel Per Unit X: %d\n", png->pixelPerUnitX);
	DEBUG_LOG("Pixel Per Unit Y: %d\n", png->pixelPerUnitY);
	DEBUG_LOG("Pixel Size Unit: %d\n", (int)png->pixelSizeUnit);
	
	return 0;
}


int kadenimgpng_timehandler(const unsigned char* buf, int len, struct pngData_s* png)
{
	DEBUG_LOG("START time handler\n");
	unsigned long crcTest = _crc(buf, len+4);
	DEBUG_LOG("check crc found: 0x%lx expected 0x%lx\n", crcTest, kadenbinary_toulong(buf+len+4, 4));
	if(crcTest == kadenbinary_toulong(buf+len+4, 4) || (crcTest & 0xffffffffL) == kadenbinary_toulong(buf+len+4, 4))
	{
		DEBUG_LOG("CRC: OK\n");
	}
	else
	{
		DEBUG_LOG("CRC: FAIL\n");
		return 1;
	}
	png->year = kadenbinary_toint(buf+4, 2);
	png->month = *(buf+5);
	png->day = *(buf+6);
	png->hour = *(buf+7);
	png->minute = *(buf+8);
	png->second = *(buf+9);
	
	return 0;
}


int kadenimgpng_texthandler(const unsigned char* buf, int len, struct pngData_s* png)
{
	DEBUG_LOG("START text handler\n");
	unsigned long crcTest = _crc(buf, len+4);
	DEBUG_LOG("check crc found: 0x%lx expected 0x%lx\n", crcTest, kadenbinary_toulong(buf+len+4, 4));
	if(crcTest == kadenbinary_toulong(buf+len+4, 4) || (crcTest & 0xffffffffL) == kadenbinary_toulong(buf+len+4, 4))
	{
		DEBUG_LOG("CRC: OK\n");
	}
	else
	{
		DEBUG_LOG("CRC: FAIL\n");
		return 1;
	}
	png->numberOfText++;
	DEBUG_LOG("text: ");
	for(int i = 4; i < len+4; i++)
	{
		DEBUG_LOG("%c",*(buf+i));
	}
	DEBUG_LOG("\n");
	return 0;
}


int kadenimgpng_datahandler(const unsigned char* buf, int len, struct pngData_s* png)
{
	DEBUG_LOG("START data handler\n");
	unsigned long crcTest = _crc(buf, len+4);
	DEBUG_LOG("check crc found: 0x%lx expected 0x%lx\n", crcTest, kadenbinary_toulong(buf+len+4, 4));
	if(crcTest == kadenbinary_toulong(buf+len+4, 4) || (crcTest & 0xffffffffL) == kadenbinary_toulong(buf+len+4, 4))
	{
		DEBUG_LOG("CRC: OK\n");
	}
	else
	{
		DEBUG_LOG("CRC: FAIL\n");
		return 1;
	}
	return 0;
}

int kadenimgpng_endHandler(const unsigned char* buf, int len, struct pngData_s* png)
{
	DEBUG_LOG("START end handler\n");
	unsigned long crcTest = _crc(buf, len+4);
	DEBUG_LOG("check crc found: 0x%lx expected 0x%lx\n", crcTest, kadenbinary_toulong(buf+len+4, 4));
	if(crcTest == kadenbinary_toulong(buf+len+4, 4) || (crcTest & 0xffffffffL) == kadenbinary_toulong(buf+len+4, 4))
	{
		DEBUG_LOG("CRC: OK\n");
	}
	else
	{
		DEBUG_LOG("CRC: FAIL\n");
		return 1;
	}
	return 0;
}


//Load PNG from file
int kadenimgpng_loadPNG(const char *filename, struct pngData_s* png)
{
	DEBUG_LOG("START loadPNG\n");

	FILE *fp;
	unsigned long long filesize = 0;
	unsigned char *buf = NULL;
	
	//check that the file is a png
	if(kadenimgpng_confirmPNG(filename) != 8)
	{
		ERROR_LOG(stderr, "ERROR kadenimgpng_loadPNG: failed confirmPNG %s\n", filename);
		return 0;
	}
	
	//find the file size
	if( (filesize = kadenimgpng_fileSize(filename)) == 0)
	{
		ERROR_LOG(stderr, "ERROR kadenimgpng_loadPNG: failed fileSize %s\n", filename);
		return 0;
	}
	
	//open the file
	fp = fopen(filename, "r");
	if(!fp) {
		ERROR_LOG(stderr, "ERROR kadenimgpng_loadPNG: failed to fopen %s\n", filename);
		return 0;
	}
	
	//allcate a buffer for the file data
	buf = (unsigned char *)malloc(filesize);
	if(!buf)
	{
		ERROR_LOG(stderr, "ERROR kadenimgpng_loadPNG: Couldn't allocate memory\n");
		return 0;
	}
	
	//copy the file into buffer
	unsigned long long bufsize = fread(buf, 1, filesize, fp);
	unsigned long long bufpos = 8;
	
	DEBUG_LOG("close file\n");
	
	if(fclose(fp) != 0)
	{
		ERROR_LOG(stderr, "ERROR kadenimgpng_loadPNG: failed to fclose %s\n", filename);
		free(buf);
		return 0;
	}
	
	DEBUG_LOG("set pngdata filename len: %d\n",(int)strlen(filename));
	
	//set png info
	png = (struct pngData_s*)malloc(sizeof(struct pngData_s));
	png->numberOfText = 0;
	png->fileName = (char*)malloc(sizeof(char) * ((int)strlen(filename)+1));
	DEBUG_LOG("verify malloc\n");
	if(!png->fileName)
	{
		ERROR_LOG(stderr, "ERROR kadenimgpng_loadPNG: Couldn't allocate memory\n");
		return 0;
	}
	DEBUG_LOG("cpy file name\n");
	strcpy(png->fileName, filename);
	
	DEBUG_LOG("start chunks\n");
	
	//read chunks
	while(bufpos < bufsize)
	{
		unsigned char lenbuf[4];
		memcpy(lenbuf, buf+bufpos, 4);
		int len = kadenbinary_toint(lenbuf, 4);
		char chunktypebuf[5];
		memcpy(chunktypebuf, buf+bufpos+4, 4);
		chunktypebuf[4] = '\0';
		
		DEBUG_LOG("chunk: %s - len: %d (%llu)\n", chunktypebuf, len, bufsize - (bufpos + len + 12));
		
		int identifiedChunk = 0;
		int crcErrors = 0;
		for(int i = 0; HANDLERS[i].type != NULL; i++)
		{
			if(!strcmp(chunktypebuf, HANDLERS[i].type))
			{
				crcErrors += HANDLERS[i].func(buf + bufpos + 4, len, png);
				identifiedChunk = 1;
				break;
			}
		}
		if(!strcmp(chunktypebuf, "IEND"))
		{
			break;
		}
		if(identifiedChunk == 0)
		{
			if((chunktypebuf[0] & 0x20) != 0x20)
			{
				ERROR_LOG(stderr, "ERROR kadenimgpng_loadPNG: encountered unknown chunk that is critical\n");
				free(buf);
				return 0;
			}
		}
		bufpos += 12+len;
	}
	
	
	//clean up
	free(buf);
	return 0;
}


int kadenimgpng_writePNG(const char *filename, struct pngData_s* png)
{
	
}


