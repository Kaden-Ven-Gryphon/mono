/****************************************************************************************
*
*	File:		kadenimgpng.h
*	Author:	kaden Noctua
*	
*	Program:	kadenimglib
*	
*	Use:		function to read and write png files
*			
*****************************************************************************************/
#ifndef kadenIMGPNG_H
#define kadenIMGPNG_H

#include <stdlib.h>
#include <string.h>
#include "kadenbinary.h"



struct pngRGBA8Pixel_s
{
	char r;
	char g;
	char b;
	char a;
};

struct pngData_s
{
	char* fileName;
	int width;
	int height;
	char bitDepth;
	char colorType;
	char compressionMethod;
	char filterMethod;
	char interlaceMethod;
	int backgroundColor[3];
	int pixelPerUnitX;
	int pixelPerUnitY;
	char pixelSizeUnit;
	int year;
	char month;
	char day;
	char hour;
	char minute;
	char second;
	int numberOfText;
	char** text;
	int numberOfIdat;
	struct pngRGBAPixel_s** pixels;
};

typedef int (*kadenimgpng_handler_ptr)(const unsigned char *buf, int len, struct pngData_s*);

struct kadenimgpng_handler
{
	const char *type;
	kadenimgpng_handler_ptr func;
};

unsigned long long kadenimgpng_fileSize(const char* filename);
int kadenimgpng_confirmPNG(const char* filename);

int kadenimgpng_headerhandler(const unsigned char* buf, int len, struct pngData_s* png);
int kadenimgpng_backgroundhandler(const unsigned char* buf, int len, struct pngData_s* png);
int kadenimgpng_pixelhandler(const unsigned char* buf, int len, struct pngData_s* png);
int kadenimgpng_timehandler(const unsigned char* buf, int len, struct pngData_s* png);
int kadenimgpng_texthandler(const unsigned char* buf, int len, struct pngData_s* png);
int kadenimgpng_datahandler(const unsigned char* buf, int len, struct pngData_s* png);
int kadenimgpng_endHandler(const unsigned char* buf, int len, struct pngData_s* png);

int kadenimgpng_textParser(const unsigned char* buf, int len, struct pngData_s* png);

int kadenimgpng_loadPNG(const char *filename, struct pngData_s* png);
int kadenimgpng_writePNG(const char *filename, struct pngData_s* png);

#endif



