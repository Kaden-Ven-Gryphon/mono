#ifndef GATECIRCUITS_H
#define GATECIRCUITS_H

#include "gategraph.h"


int gategraph_addFullAdder(struct gategraph_fullGraph_s* fgg, int x, int y);
int gategraph_8bitAdder(struct gategraph_fullGraph_s* fgg, int x, int y);
int gategraph_dFlipFlop(struct gategraph_fullGraph_s* fgg, int x, int y);
int gategraph_8bitReg(struct gategraph_fullGraph_s* fgg, int x, int y);

#endif
