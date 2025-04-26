/*
*	binimg.c
*	Kaden Gryphon
*	
*
*	This is a set of functions for creating and manipulate raw binary image data
*
*
*/

#include "binimg.h"

//#define _DEBUG_MESSAGES
#ifdef _DEBUG_MESSAGES
	#include <stdio.h>
	#define DEBUG_LOG(fmt, ...) fprintf(stdout, "DEBUG:%s:%d:%s()" fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
	#define DEBUG_LOG(...) {}
#endif
#define _ERROR_MESSAGES
#ifdef _ERROR_MESSAGES
	#include <stdio.h>
	#define ERROR_LOG(fmt, ...) fprintf(stderr, "DEBUG:%s:%d:%s()" fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
	#define ERROR_LOG(...) {}
#endif



int binimg_initImage(int width, int hight, struct pixel_s bgcolor, struct binimg_image_s* image)
{
	DEBUG_LOG("DEBUG: start initImage\n");
	
	image->width = width;
	image->hight = hight;
	
	image->rawimg = (struct pixel_s**) malloc(sizeof(struct pixel_s*) * width);
	if(image->rawimg == NULL)
		{
			ERROR_LOG("ERROR: binimg_initImage malloc failed\n");
			return 1;
		}
	
	for(int i = 0; i < width; i++)
	{
		image->rawimg[i] = (struct pixel_s*) malloc(sizeof(struct pixel_s) * hight);
		if(image->rawimg[i] == NULL)
		{
			ERROR_LOG("ERROR: binimg_initImage malloc failed\n");
			return 1;
		}
	}
	
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < hight; j++)
		{
			
			image->rawimg[i][j] = bgcolor;
		}
	}
	
	DEBUG_LOG("DEBUG: end initImage\n");
	return 0;
}


int binimg_initGradiant(int numColor, struct gradiant_s* grad)
{
	grad->colors = (struct pixel_s*)malloc(sizeof(struct pixel_s)*numColor);
	grad->pos = (double*)malloc(sizeof(double)*numColor);
	grad->numColors = numColor;
	if(grad->colors == NULL)
	{
		ERROR_LOG("ERROR: binimg_initGradiant malloc failed\n");
		return -1;
	}
	if(grad->pos == NULL)
	{
		ERROR_LOG("ERROR: binimg_initGradiant malloc failed\n");
		return -1;
	}
	return 0;
}




struct pixel_s binimg_colorNormal(struct pixel_s old, struct pixel_s new)
{
	struct pixel_s retVal;
	double a0;
	double aa = (double)new.a / (double)255;
	double ab = (double)old.a / (double)255;
	a0 = aa + ab*(1 - aa);
	retVal.r =(unsigned char) (((double)new.r * aa + (double)old.r*ab*(1 - aa))/a0);
	retVal.g =(unsigned char) (((double)new.g * aa + (double)old.g*ab*(1 - aa))/a0);
	retVal.b =(unsigned char) (((double)new.b * aa + (double)old.b*ab*(1 - aa))/a0);
	retVal.a = (unsigned char) a0*255;
	//DEBUG_LOG("new color: %3d,%3d,%d,%3d\n", (unsigned int)retVal.r, (unsigned int)retVal.g, (unsigned int)retVal.b, (unsigned int)retVal.a);
	return retVal;
}



struct pixel_s binimg_colorFromGradiant(struct gradiant_s grad, double x)
{
	struct pixel_s retVal = {0,0,0,0};
	int color1 = 0;
	int color2 = 0;
	for(int i = 0; i < grad.numColors; i++)
	{
		if(grad.pos[i] < x) color1 = i;
		if(grad.pos[i] > x) { color2 = i; break; }
	}
	if(x == 1) color2=grad.numColors-1;
	
	if(grad.pos[color2] - grad.pos[color1] <= 0)
	{
		ERROR_LOG("ERROR: binimg_colorFromGradiant bad gradiant pos: %f\n", x);
		return retVal;
	}
	
	double percent = (x - grad.pos[color1]) / (grad.pos[color2] - grad.pos[color1]);
	retVal.r = grad.colors[color1].r + ((int)(((double)(grad.colors[color2].r-grad.colors[color1].r))*percent));
	retVal.g = grad.colors[color1].g + ((int)(((double)(grad.colors[color2].g-grad.colors[color1].g))*percent));
	retVal.b = grad.colors[color1].b + ((int)(((double)(grad.colors[color2].b-grad.colors[color1].b))*percent));
	retVal.a = grad.colors[color1].a + ((int)(((double)(grad.colors[color2].a-grad.colors[color1].a))*percent));
	
	DEBUG_LOG("color from gradiant: %d,%d,%d\n", retVal.r, retVal.g, retVal.b);
	
	
	return retVal;
}



int binimg_drawLine(int x1, int y1, int x2, int y2, int width, int fill, struct pixel_s color, struct binimg_image_s* image)
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	
	
	if(abs(dx) > abs(dy))
	//line is horizontal ish
	{
		if(x1 > x2)
		{
			int buf = x1;
			x1 = x2;
			x2 = buf;
			buf = y1;
			y1 = y2;
			y2 = buf;
		}
		double a = dy/dx;
		double j = y1;
		for(int i = x1; i <= x2; i++)
		{
			int k = -width/2;
			do 
			{
				if(i >= 0 && (int)j+k >= 0 && i < image->width && (int)j+k < image->hight)
				{
					if(fill == -1)
					{
						image->rawimg[i][(int)j+k].a = 0;
					}
					else
					{
						image->rawimg[i][(int)j+k] = binimg_colorNormal(image->rawimg[i][(int)j+k], color);
					}
					
				}
				j+=a;
				k++;
			} while(k < width/2);
		}
	}
	//else line is vertiacal ish
	else
	{
		if(y1 > y2)
		{
			int buf = x1;
			x1 = x2;
			x2 = buf;
			buf = y1;
			y1 = y2;
			y2 = buf;
		}
		double a = dx/dy;
		double i = x1;
		for(int j = y1; j <= y2; j++)
		{
			int k = -(width / 2);
			do
			{
				if((int)i+k >= 0 && j >= 0 && (int)i+k < image->width && j < image->hight)
				{
					if(fill == -1)
					{
						image->rawimg[(int)i+k][j].a = 0;	
					}
					else
					{
						image->rawimg[(int)i+k][j] = binimg_colorNormal(image->rawimg[(int)i+k][j], color);
					}
				}
				i+=a;
				k++;
			} while(k < width/2);
		}
	}
	
	
	return 0;
}



int binimg_drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int fill, struct pixel_s color, struct binimg_image_s* image)
{
	DEBUG_LOG("drawTriangle color: %3d,%3d,%d,%3d\n", (unsigned int)color.r, (unsigned int)color.g, (unsigned int)color.b, (unsigned int)color.a);
	int xPoints[3] = {x1, x2, x3};
	int yPoints[3] = {y1, y2, y3};
	
	int buf = 0;
	
	//check if the points are ccw, if so swap points so the are cw
	if((xPoints[1] - xPoints[0]) * (yPoints[2] - yPoints[0]) - (xPoints[2] - xPoints[0]) * (yPoints[1] - yPoints[0]) < 0)
	{
		DEBUG_LOG("Is CCW\n");
		buf = xPoints[0];
		xPoints[0] = xPoints[1];
		xPoints[1] = buf;
		buf = yPoints[0];
		yPoints[0] = yPoints[1];
		yPoints[1] = buf;
	}
	
	//find the bounding box for the triange
	int xStart = image->width;
	int xEnd = 0;
	int yStart = image->hight;
	int yEnd = 0;
	
	for(int i = 0; i < 3; i++)
	{
		if(xPoints[i] < xStart) xStart = xPoints[i];
		if(xPoints[i] > xEnd) xEnd = xPoints[i];
		if(yPoints[i] < yStart) yStart = yPoints[i];
		if(yPoints[i] > yEnd) yEnd = yPoints[i];
	}
	
	//draw skellton for debuging
	/*
	double thetas[3] = {0.0,0.0,0.0,};
	int xCenter = (x1+x2+x3)/3;
	int yCenter = (y1+y2+y3)/3;
	struct pixel_s red = {255,0,0,255};
	struct pixel_s green = {0,255,0,255};
	struct pixel_s blue = {0,0,255,255};
	binimg_drawLine(xPoints[0], yPoints[0], xPoints[1], yPoints[1], 1, red, image);
	binimg_drawLine(xPoints[1], yPoints[1], xPoints[2], yPoints[2], 1, green, image);
	binimg_drawLine(xPoints[2], yPoints[2], xPoints[0], yPoints[0], 1, blue, image);
	binimg_drawCircle(xPoints[0], yPoints[0], 3, 1, red, image);
	binimg_drawCircle(xPoints[1], yPoints[1], 3, 1, green, image);	
	binimg_drawCircle(xPoints[2], yPoints[2], 3, 1, blue, image);
	binimg_drawCircle(xCenter, yCenter, 3, 1, color, image);
	binimg_drawCircle(xStart, yStart, 3, 1, color, image);
	binimg_drawCircle(xEnd, yEnd, 3, 1, color, image);
	*/
	
	for(int i = xStart; i <= xEnd; i++)
	{
		for(int j = yStart; j <= yEnd; j++)
		{
			int inside = 1;
			if( (( (xPoints[1] - xPoints[0])*(j - yPoints[0]) )-( (yPoints[1] - yPoints[0])*(i - xPoints[0]) )) < 0)
			{
				inside = 0;
			}
			if( (( (xPoints[2] - xPoints[1])*(j - yPoints[1]) )-( (yPoints[2] - yPoints[1])*(i - xPoints[1]) )) < 0)
			{
				inside = 0;
			}
			if( (( (xPoints[0] - xPoints[2])*(j - yPoints[2]) )-( (yPoints[0] - yPoints[2])*(i - xPoints[2]) )) < 0)
			{
				inside = 0;
			}
			
			if(inside)
			{
				//DEBUG_LOG("Inside %d, %d\n", i,j);
				image->rawimg[i][j] = binimg_colorNormal(image->rawimg[i][j], color);
			}
		}
	}
	
	
	
	
	return 0;
}





int binimg_drawRectangle(int x, int y, int width, int hight, int fill, struct pixel_s color, struct binimg_image_s* image)
{
	DEBUG_LOG("drawRectangle color: %3d,%3d,%d,%3d\n", (unsigned int)color.r, (unsigned int)color.g, (unsigned int)color.b, (unsigned int)color.a);
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < hight; j++)
		{
			
			if(x+i >= 0 && y+j >= 0 && x+i < image->width && y+j < image->hight) image->rawimg[x+i][y+j] = binimg_colorNormal(image->rawimg[x+i][y+j], color);
		}
	}
	return 0;
}




int binimg_drawCircle(int x, int y, int radius, int fill, struct pixel_s color, struct binimg_image_s* image)
{
	DEBUG_LOG("drawCircle color: %3d,%3d,%d,%3d\n", (unsigned int)color.r, (unsigned int)color.g, (unsigned int)color.b, (unsigned int)color.a);
	
	for(int j = -radius; j < radius; j++)
	{
		int rowWidth = (int) sqrt((double)(radius*radius-j*j));
		for(int i = -rowWidth; i < rowWidth; i++)
		{
			if(x+i >= 0 && y+j >= 0 && x+i < image->width && y+j < image->hight)
			{
				if(fill == -1)
				{
					image->rawimg[x+i][y+j].a = 0; 
				}
				else
				{
					image->rawimg[x+i][y+j] = binimg_colorNormal(image->rawimg[x+i][y+j], color);
				}
			}
		}
	}
	
	
	
	return 0;
}


int binimg_drawBitmapText(int x, int y, struct pixel_s color, char *text, int font[45][7][8], int size, struct binimg_image_s* image)
{
	DEBUG_LOG("START drawText: %s\n", text);
	int i = 0;
	int letterOffset = 0;
	//untill the end of string is reached
	while(text[i] != '\0')
	{
		DEBUG_LOG("before: %c\n",text[i]);
		//convert to index for font array
		int fontNum = 0;
		if(text[i] <= 90 && text[i] >= 46) fontNum = text[i]-46;
		else if(text[i] == 32) {letterOffset += 7*size; i++; continue;}
		else {i++; continue;}
		DEBUG_LOG("%d : %d\n",text[i], fontNum);
		
		
		//loop through the letter 2d bit map
		int letterWidth = 0;
		for(int j = 0; j < 8; j++)
		{
			for(int k = 0; k < 7; k++)
			{
				//if the bit map is marked with a one paint pixel
				if(font[fontNum][k][j] == 1)
				{
					//keep track of the width of the letter
					if(j > letterWidth) {letterWidth = j;}
					//draw the pixel
					binimg_drawRectangle(x+(j*size)+letterOffset, y+(k*size), size, size, 1, color, image);
				}
			}
		}
		
		//move the "typehead" over the letterwidth +2 space
		i++;
		letterOffset += (letterWidth+2)*size;
	}
	DEBUG_LOG("END drawText\n");
	return 0;
}


int binimg_insertImage(int x, int y, int r, struct binimg_image_s* child, struct binimg_image_s* image)
{
	switch(r) {
	case 0:
		for(int i = 0; i < child->width; i++)
		{
			for(int j = 0; j < child->hight; j++)
			{
				if(x+i >= 0 && y+j >= 0 && x+i < image->width && y+j < image->hight) image->rawimg[x+i][y+j] = binimg_colorNormal(image->rawimg[x+i][y+j], child->rawimg[i][j]);
			}
		}
		break;
	case 1:
		for(int i = 0; i < child->width; i++)
		{
			for(int j = 0; j < child->hight; j++)
			{
				if(x+i >= 0 && y+j >= 0 && x+i < image->width && y+j < image->hight) image->rawimg[x+child->width-j][y+i] = binimg_colorNormal(image->rawimg[x+child->width-j][y+i], child->rawimg[i][j]);
			}
		}
		break;
	case 2:
		for(int i = 0; i < child->width; i++)
		{
			for(int j = 0; j < child->hight; j++)
			{
				if(x+i >= 0 && y+j >= 0 && x+i < image->width && y+j < image->hight) image->rawimg[x+child->width-i][y+child->hight-j] = binimg_colorNormal(image->rawimg[x+child->width-i][y+child->hight-j], child->rawimg[i][j]);
			}
		}
		break;
	case 3:
		for(int i = 0; i < child->width; i++)
		{
			for(int j = 0; j < child->hight; j++)
			{
				if(x+i >= 0 && y+j >= 0 && x+i < image->width && y+j < image->hight) image->rawimg[x+j][y+child->hight-i] = binimg_colorNormal(image->rawimg[x+j][y+child->hight-i], child->rawimg[i][j]);
			}
		}
		break;
	}
	
	return 0;
}





int binimg_testGradiant(struct binimg_image_s* image)
{
	DEBUG_LOG("DEBUG: start testGradiant\n");
	
	int w = image->width;
	int h = image->hight;
	
	
	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			image->rawimg[i][j].r = (unsigned char) (((double) i / (double) w) * 255);
			image->rawimg[i][j].g = (unsigned char) (((double) j / (double) h) * 255);
			image->rawimg[i][j].b = 0;
			image->rawimg[i][j].a = 255;			
		}
	}
	DEBUG_LOG("DEBUG: end testGradiant\n");
	return 0;
}
