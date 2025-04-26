/*
*	gateimgs.h
*	Kaden Gryphon
*	
*
*	This is a set of functions to draw basic gates
*
*
*/

#include "binimg.h"

#define GATE_COLOR_WHITE {255, 255, 255, 255}
#define GATE_COLOR_TRANSPARENT {0, 0, 0, 0}
#define GATE_COLOR_AND_OFF {10, 10, 50, 255}
#define GATE_COLOR_AND_ON {0, 0, 200, 255}
#define GATE_COLOR_OR_OFF {10, 50, 10, 255}
#define GATE_COLOR_OR_ON {0, 170, 0, 255}
#define GATE_COLOR_NOT_OFF {50, 10, 10, 255}
#define GATE_COLOR_NOT_ON {170, 0, 0, 255}
#define GATE_COLOR_WIRE_OFF {110,80,18,255}
#define GATE_COLOR_WIRE_ON {255,201,23,255}


struct binimg_image_s * gateimgs_initAndOff();
struct binimg_image_s * gateimgs_initAndOn();
struct binimg_image_s * gateimgs_initOrOff();
struct binimg_image_s * gateimgs_initOrOn();
struct binimg_image_s * gateimgs_initNotOff();
struct binimg_image_s * gateimgs_initNotOn();

