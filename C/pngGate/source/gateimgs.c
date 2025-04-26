/*
*	gateimgs.c
*	Kaden Gryphon
*	
*
*	This is a set of functions for creating the gate templates
*
*
*/

#include "gateimgs.h"

#define _DEBUG_MESSAGES
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


struct binimg_image_s * gateimgs_initAndOff()
{
	struct binimg_image_s *andGateOff;
	andGateOff = malloc(sizeof(struct binimg_image_s)*1);
	
	struct pixel_s trans = GATE_COLOR_TRANSPARENT;
	struct pixel_s off = GATE_COLOR_AND_OFF;
	
	binimg_initImage(16, 16, trans, andGateOff);
	binimg_drawCircle(8,7,8,1,off,andGateOff);
	binimg_drawRectangle(1,7,14,15,1,off,andGateOff);
	binimg_drawLine(0,0,0,15,1,-1,trans, andGateOff);
	binimg_drawLine(15,0,15,15,1,-1,trans, andGateOff);
	
	return andGateOff;
}

struct binimg_image_s * gateimgs_initAndOn()
{
	struct binimg_image_s *andGateOn;
	andGateOn = malloc(sizeof(struct binimg_image_s)*1);
	
	struct pixel_s trans = GATE_COLOR_TRANSPARENT;
	struct pixel_s off = GATE_COLOR_AND_ON;
	
	binimg_initImage(16, 16, trans, andGateOn);
	binimg_drawCircle(8,7,8,1,off,andGateOn);
	binimg_drawRectangle(1,7,14,15,1,off,andGateOn);
	binimg_drawLine(0,0,0,15,1,-1,trans, andGateOn);
	binimg_drawLine(15,0,15,15,1,-1,trans, andGateOn);
	
	return andGateOn;
}

struct binimg_image_s * gateimgs_initOrOff()
{
	struct binimg_image_s *orGateOff;
	orGateOff = malloc(sizeof(struct binimg_image_s)*1);
	struct pixel_s trans = GATE_COLOR_TRANSPARENT;
	struct pixel_s off = GATE_COLOR_OR_OFF;
	binimg_initImage(16, 16, trans, orGateOff);
	
	struct binimg_image_s bufimg;
	binimg_initImage(16, 16, trans, &bufimg);
	
	binimg_drawCircle(16, 12, 15, 1, off, &bufimg);
	binimg_drawLine(1,12,1,16,1,1,off,&bufimg);
	binimg_drawLine(15,0,15,15,14,-1,trans, &bufimg);
	binimg_drawCircle(10,20,9,-1,off,&bufimg);
	binimg_insertImage(0, 0, 0, &bufimg, orGateOff);
	
	binimg_drawLine(0,0,0,15,50,-1,off,&bufimg);
	binimg_drawCircle(-1, 12, 15, 1, off, &bufimg);
	binimg_drawLine(13,12,14,16,1,1,off,&bufimg);
	binimg_drawLine(0,0,0,15,14,-1,trans, &bufimg);
	binimg_drawCircle(5,20,9,-1,off,&bufimg);
	binimg_insertImage(1, 0, 0, &bufimg, orGateOff);
	
	
	return orGateOff;
}
struct binimg_image_s * gateimgs_initOrOn()
{
	struct binimg_image_s *orGateOn;
	orGateOn = malloc(sizeof(struct binimg_image_s)*1);
	struct pixel_s trans = GATE_COLOR_TRANSPARENT;
	struct pixel_s off = GATE_COLOR_OR_ON;
	binimg_initImage(16, 16, trans, orGateOn);
	
	struct binimg_image_s bufimg;
	binimg_initImage(16, 16, trans, &bufimg);
	
	binimg_drawCircle(16, 12, 15, 1, off, &bufimg);
	binimg_drawLine(1,12,1,16,1,1,off,&bufimg);
	binimg_drawLine(15,0,15,15,14,-1,trans, &bufimg);
	binimg_drawCircle(10,20,9,-1,off,&bufimg);
	binimg_insertImage(0, 0, 0, &bufimg, orGateOn);
	
	binimg_drawLine(0,0,0,15,50,-1,off,&bufimg);
	binimg_drawCircle(-1, 12, 15, 1, off, &bufimg);
	binimg_drawLine(13,12,14,16,1,1,off,&bufimg);
	binimg_drawLine(0,0,0,15,14,-1,trans, &bufimg);
	binimg_drawCircle(5,20,9,-1,off,&bufimg);
	binimg_insertImage(1, 0, 0, &bufimg, orGateOn);
	
	return orGateOn;
}

struct binimg_image_s * gateimgs_initNotOff()
{
	struct binimg_image_s *notGateOff;
	notGateOff = malloc(sizeof(struct binimg_image_s)*1);
	
	struct pixel_s trans = GATE_COLOR_TRANSPARENT;
	struct pixel_s off = GATE_COLOR_NOT_OFF;
	struct pixel_s on = GATE_COLOR_NOT_ON;
	
	binimg_initImage(16, 16, trans, notGateOff);
	binimg_drawTriangle(1,15,7,4,14,15,1,off,notGateOff);
	binimg_drawCircle(8,3,3,1,on,notGateOff);
	binimg_drawLine(6,6,6,6,1,-1,off,notGateOff);
	
	return notGateOff;
}

struct binimg_image_s * gateimgs_initNotOn()
{
	struct binimg_image_s *notGateOff;
	notGateOff = malloc(sizeof(struct binimg_image_s)*1);
	
	struct pixel_s trans = GATE_COLOR_TRANSPARENT;
	struct pixel_s off = GATE_COLOR_NOT_OFF;
	struct pixel_s on = GATE_COLOR_NOT_ON;
	
	binimg_initImage(16, 16, trans, notGateOff);
	binimg_drawTriangle(1,15,7,4,14,15,1,on,notGateOff);
	binimg_drawCircle(8,3,3,1,off,notGateOff);
	binimg_drawLine(6,6,6,6,1,-1,off,notGateOff);
	
	return notGateOff;
}
