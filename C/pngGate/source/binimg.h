/*
*	binimg.c
*	Kaden Gryphon
*	
*
*	This is a set of functions for creating and manipulate raw binary image data
*
*
*/


#ifndef BINIMG_H
#define BINIMG_H

#include <stdlib.h>
#include <math.h>

#define PI 3.141592654



struct pixel_s
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};


struct binimg_image_s
{
	int width;
	int hight;
	struct pixel_s** rawimg;
};

struct gradiant_s
{
	struct pixel_s *colors;
	double *pos;
	int numColors;
};



//init structures
int binimg_initImage(int width, int hight, struct pixel_s bgcolor, struct binimg_image_s* image);
int binimg_initGradiant(int numColor, struct gradiant_s* grad);

int binimg_deconImage(struct binimg_image_s* imgae);//imp

//pixel color modes
struct pixel_s binimg_colorNormal(struct pixel_s old, struct pixel_s new);
struct pixel_s binimg_colorFromGradiant(struct gradiant_s grad, double x);

//basic drawing funcs
int binimg_drawLine(int x1, int y1, int x2, int y2, int width, int fill, struct pixel_s color, struct binimg_image_s* image);
int binimg_drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int fill, struct pixel_s color, struct binimg_image_s* image);
int binimg_drawRectangle(int x, int y, int width, int hight, int fill, struct pixel_s color, struct binimg_image_s* image);
int binimg_drawCircle(int x, int y, int radius, int fill, struct pixel_s color, struct binimg_image_s* image);
int binimg_drawBitmapText(int x, int y, struct pixel_s color, char *text, int font[45][7][8], int size, struct binimg_image_s* image);

//more drawing funcs
int binimg_insertImage(int x, int y, int r, struct binimg_image_s* child, struct binimg_image_s* image);

//test draws
int binimg_testGradiant(struct binimg_image_s* image);



#endif
