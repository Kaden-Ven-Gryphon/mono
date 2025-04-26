#include "binimg.h"
#include "binpypng.h"
#include "gateimgs.h"



int main()
{
	struct binimg_image_s* andOff = gateimgs_initAndOff();
	struct binimg_image_s* andOn = gateimgs_initAndOn();
	struct binimg_image_s* orOff = gateimgs_initOrOff();
	struct binimg_image_s* orOn = gateimgs_initOrOn();
	struct binimg_image_s* notOff = gateimgs_initNotOff();
	struct binimg_image_s* notOn = gateimgs_initNotOn();
	struct pixel_s black = {0,0,0,255};
	struct pixel_s cWireOn = GATE_COLOR_WIRE_ON;
	struct pixel_s cWireOff = GATE_COLOR_WIRE_OFF;
	
	char *imgFileName = "testimg\0";
	char *imgAndOffName = "andoff\0";
	char *imgAndOnName = "andon\0";
	char *imgOrOffName = "oroff\0";
	char *imgOrOnName = "oron\0";
	char *imgNotOffName = "notoff\0";
	char *imgNotOnName = "noton\0";
	struct binimg_image_s testImg;
	binimg_initImage(512, 512, black, &testImg);

	binimg_insertImage(16,16,0,andOff,&testImg);
	binimg_insertImage(32,16,0,andOn,&testImg);
	binimg_insertImage(48,16,1,andOff,&testImg);
	binimg_insertImage(64,16,2,andOff,&testImg);
	binimg_insertImage(80,16,3,andOff,&testImg);
	binimg_insertImage(96,16,0,orOff, &testImg);
	binimg_insertImage(112,16,0,orOn, &testImg);
	binimg_insertImage(128,16,0,notOff, &testImg);
	binimg_insertImage(144,16,0,notOn, &testImg);
	
	binimg_drawLine(16,40,144,40,1,1,cWireOff,&testImg);
	binimg_drawLine(16,56,144,56,1,1,cWireOn,&testImg);
	
	
	binpypng_writebin(imgFileName, &testImg);
	binpypng_convert(imgFileName);
	/*
	binpypng_writebin(imgAndOffName, andOff);
	binpypng_convert(imgAndOffName);
	binpypng_writebin(imgAndOnName, andOn);
	binpypng_convert(imgAndOnName);
	binpypng_writebin(imgOrOffName, orOff);
	binpypng_convert(imgOrOffName);
	binpypng_writebin(imgOrOnName, orOn);
	binpypng_convert(imgOrOnName);
	binpypng_writebin(imgNotOffName, notOff);
	binpypng_convert(imgNotOffName);
	binpypng_writebin(imgNotOnName, notOn);
	binpypng_convert(imgNotOnName);
	*/
	


	return 0;
}
