#include "gatecircuits.h"

#define _DEBUG_MESSAGES
#ifdef _DEBUG_MESSAGES
	#include <stdio.h>
	#define DEBUG_LOG(fmt, ...) fprintf(stdout, "DEBUG:%s:%d:%-30s()" fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
	#define DEBUG_LOG(...) {}
#endif
#define _ERROR_MESSAGES
#ifdef _ERROR_MESSAGES
	#include <stdio.h>
	#define ERROR_LOG(fmt, ...) fprintf(stderr, "DEBUG:%s:%d:%-30s()" fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
	#define ERROR_LOG(...) {}
#endif






int gategraph_addFullAdder(struct gategraph_fullGraph_s* fgg, int x, int y)
{
	DEBUG_LOG("ADD FULL ADDER\n");
	int offset = fgg->numberOfGates;
	int woffset = fgg->numberOfWires;
	
	gategraph_addGateToGraph(fgg, 'p', 26+x, 180+y, 0, -1, 1, 2);//0
	gategraph_addGateToGraph(fgg, 'p', 37+x, 180+y, 0, -1, 1, 2);//1
	gategraph_addGateToGraph(fgg, 'p', 57+x, 180+y, 0, -1, 1, 2);//2
	
	gategraph_addGateToGraph(fgg, 'o', 24+x, 156+y, 0, -1, 2, 1);//3
	gategraph_addGateToGraph(fgg, 'a', 40+x, 156+y, 0, -1, 2, 1);//4
	
	gategraph_addGateToGraph(fgg, 'n', 40+x, 132+y, 0, -1, 1, 2);//5
	
	gategraph_addGateToGraph(fgg, 'a', 24+x, 110+y, 0, -1, 2, 2);//6
	gategraph_addGateToGraph(fgg, 'n', 40+x, 110+y, 0, -1, 1, 1);//7
	
	gategraph_addGateToGraph(fgg, 'o', 29+x, 80+y, 0, -1, 2, 1);//8
	gategraph_addGateToGraph(fgg, 'a', 45+x, 80+y, 0, -1, 2, 2);//9
	
	gategraph_addGateToGraph(fgg, 'n', 29+x, 57+y, 0, -1, 1, 1);//10
	
	gategraph_addGateToGraph(fgg, 'o', 34+x, 36+y, 0, -1, 2, 1);//11
	gategraph_addGateToGraph(fgg, 'o', 52+x, 36+y, 0, -1, 2, 1);//12
	
	gategraph_addGateToGraph(fgg, 'n', 34+x, 16+y, 0, -1, 1, 1);//13
	
	DEBUG_LOG("FULL ADDER add wires\n");
	gategraph_addWireToGraph(fgg, 2,0+offset,-1);//0
	gategraph_addWireToGraph(fgg, 4,0+offset,-1);//1
	
	gategraph_addWireToGraph(fgg, 2,1+offset,-1);//2
	gategraph_addWireToGraph(fgg, 4,1+offset,-1);//3
	
	gategraph_addWireToGraph(fgg, 4,3+offset,-1);//4
	
	gategraph_addWireToGraph(fgg, 2,4+offset,-1);//5
	
	gategraph_addWireToGraph(fgg, 4,5+offset,-1);//6
	gategraph_addWireToGraph(fgg, 2,5+offset,-1);//7
	
	gategraph_addWireToGraph(fgg, 4,6+offset,-1);//8
	gategraph_addWireToGraph(fgg, 4,6+offset,-1);//9
	
	gategraph_addWireToGraph(fgg, 4,7+offset,-1);//10
	
	gategraph_addWireToGraph(fgg, 4,2+offset,-1);//11
	gategraph_addWireToGraph(fgg, 4,2+offset,-1);//12
	
	gategraph_addWireToGraph(fgg, 2,8+offset,-1);//13
	
	gategraph_addWireToGraph(fgg, 4,9+offset,-1);//14
	gategraph_addWireToGraph(fgg, 4,9+offset,-1);//15
	
	gategraph_addWireToGraph(fgg, 4,10+offset,-1);//16
	
	gategraph_addWireToGraph(fgg, 2,11+offset,-1);//17
	
	gategraph_addWireToGraph(fgg, 2,13+offset,-1);//18
	
	gategraph_addWireToGraph(fgg, 2,12+offset,-1);//19
	
	DEBUG_LOG("FULL ADDER make connections\n");
	//add gate connections
	fgg->gateArray[0+offset].outputids[0] = 3+offset;
	fgg->gateArray[3+offset].inputids[0] = 0+offset;
	fgg->wireArray[0+woffset].xs[0] = 26+x;
	fgg->wireArray[0+woffset].ys[0] = 180+y;
	fgg->wireArray[0+woffset].xs[1] = 26+x;
	fgg->wireArray[0+woffset].ys[1] = 170+y;
	DEBUG_LOG("A\n");
	fgg->gateArray[0+offset].outputids[1] = 4+offset;
	fgg->gateArray[4+offset].inputids[0] = 0+offset;
	fgg->wireArray[1+woffset].xs[0] = 26+x;
	fgg->wireArray[1+woffset].ys[0] = 180+y;
	fgg->wireArray[1+woffset].xs[1] = 26+x;
	fgg->wireArray[1+woffset].ys[1] = 175+y;
	fgg->wireArray[1+woffset].xs[2] = 43+x;
	fgg->wireArray[1+woffset].ys[2] = 175+y;
	fgg->wireArray[1+woffset].xs[3] = 43+x;
	fgg->wireArray[1+woffset].ys[3] = 170+y;
	DEBUG_LOG("B\n");
	fgg->gateArray[1+offset].outputids[0] = 3+offset;
	fgg->gateArray[3+offset].inputids[1] = 1+offset;
	fgg->wireArray[2+woffset].xs[0] = 37+x;
	fgg->wireArray[2+woffset].ys[0] = 180+y;
	fgg->wireArray[2+woffset].xs[1] = 37+x;
	fgg->wireArray[2+woffset].ys[1] = 170+y;
	DEBUG_LOG("C\n");
	fgg->gateArray[1+offset].outputids[1] = 4+offset;
	fgg->gateArray[4+offset].inputids[1] = 1+offset;
	fgg->wireArray[3+woffset].xs[0] = 37+x;
	fgg->wireArray[3+woffset].ys[0] = 180+y;
	fgg->wireArray[3+woffset].xs[1] = 37+x;
	fgg->wireArray[3+woffset].ys[1] = 177+y;
	fgg->wireArray[3+woffset].xs[2] = 51+x;
	fgg->wireArray[3+woffset].ys[2] = 177+y;
	fgg->wireArray[3+woffset].xs[3] = 51+x;
	fgg->wireArray[3+woffset].ys[3] = 170+y;
	DEBUG_LOG("D\n");
	fgg->gateArray[3+offset].outputids[0] = 6+offset;
	fgg->gateArray[6+offset].inputids[0] = 3+offset;
	fgg->wireArray[4+woffset].xs[0] = 31+x;
	fgg->wireArray[4+woffset].ys[0] = 160+y;
	fgg->wireArray[4+woffset].xs[1] = 31+x;
	fgg->wireArray[4+woffset].ys[1] = 140+y;
	fgg->wireArray[4+woffset].xs[2] = 27+x;
	fgg->wireArray[4+woffset].ys[2] = 140+y;
	fgg->wireArray[4+woffset].xs[3] = 27+x;
	fgg->wireArray[4+woffset].ys[3] = 120+y;
	DEBUG_LOG("E\n");
	fgg->gateArray[4+offset].outputids[0] = 5+offset;
	fgg->gateArray[5+offset].inputids[0] = 4+offset;
	fgg->wireArray[5+woffset].xs[0] = 47+x;
	fgg->wireArray[5+woffset].ys[0] = 160+y;
	fgg->wireArray[5+woffset].xs[1] = 47+x;
	fgg->wireArray[5+woffset].ys[1] = 140+y;
	DEBUG_LOG("F\n");
	fgg->gateArray[5+offset].outputids[0] = 6+offset;
	fgg->gateArray[6+offset].inputids[1] = 5+offset;
	fgg->wireArray[6+woffset].xs[0] = 47+x;
	fgg->wireArray[6+woffset].ys[0] = 135+y;
	fgg->wireArray[6+woffset].xs[1] = 47+x;
	fgg->wireArray[6+woffset].ys[1] = 130+y;
	fgg->wireArray[6+woffset].xs[2] = 36+x;
	fgg->wireArray[6+woffset].ys[2] = 130+y;
	fgg->wireArray[6+woffset].xs[3] = 36+x;
	fgg->wireArray[6+woffset].ys[3] = 120+y;
	DEBUG_LOG("G\n");
	fgg->gateArray[5+offset].outputids[1] = 7+offset;
	fgg->gateArray[7+offset].inputids[0] = 5+offset;
	fgg->wireArray[7+woffset].xs[0] = 47+x;
	fgg->wireArray[7+woffset].ys[0] = 135+y;
	fgg->wireArray[7+woffset].xs[1] = 47+x;
	fgg->wireArray[7+woffset].ys[1] = 120+y;
	DEBUG_LOG("H\n");
	fgg->gateArray[6+offset].outputids[0] = 8+offset;
	fgg->gateArray[8+offset].inputids[0] = 6+offset;
	fgg->wireArray[8+woffset].xs[0] = 31+x;
	fgg->wireArray[8+woffset].ys[0] = 110+y;
	fgg->wireArray[8+woffset].xs[1] = 31+x;
	fgg->wireArray[8+woffset].ys[1] = 101+y;
	fgg->wireArray[8+woffset].xs[2] = 31+x;
	fgg->wireArray[8+woffset].ys[2] = 101+y;
	fgg->wireArray[8+woffset].xs[3] = 31+x;
	fgg->wireArray[8+woffset].ys[3] = 90+y;
	DEBUG_LOG("I\n");
	fgg->gateArray[6+offset].outputids[1] = 9+offset;
	fgg->gateArray[9+offset].inputids[0] = 6+offset;
	fgg->wireArray[9+woffset].xs[0] = 31+x;
	fgg->wireArray[9+woffset].ys[0] = 110+y;
	fgg->wireArray[9+woffset].xs[1] = 31+x;
	fgg->wireArray[9+woffset].ys[1] = 101+y;
	fgg->wireArray[9+woffset].xs[2] = 48+x;
	fgg->wireArray[9+woffset].ys[2] = 101+y;
	fgg->wireArray[9+woffset].xs[3] = 48+x;
	fgg->wireArray[9+woffset].ys[3] = 90+y;
	DEBUG_LOG("J\n");
	fgg->gateArray[7+offset].outputids[0] = 12+offset;
	fgg->gateArray[12+offset].inputids[1] = 7+offset;
	fgg->wireArray[10+woffset].xs[0] = 47+x;
	fgg->wireArray[10+woffset].ys[0] = 110+y;
	fgg->wireArray[10+woffset].xs[1] = 47+x;
	fgg->wireArray[10+woffset].ys[1] = 108+y;
	fgg->wireArray[10+woffset].xs[2] = 64+x;
	fgg->wireArray[10+woffset].ys[2] = 108+y;
	fgg->wireArray[10+woffset].xs[3] = 64+x;
	fgg->wireArray[10+woffset].ys[3] = 50+y;
	DEBUG_LOG("K\n");
	fgg->gateArray[2+offset].outputids[0] = 9+offset;
	fgg->gateArray[9+offset].inputids[1] = 2+offset;
	fgg->wireArray[11+woffset].xs[0] = 57+x;
	fgg->wireArray[11+woffset].ys[0] = 180+y;
	fgg->wireArray[11+woffset].xs[1] = 57+x;
	fgg->wireArray[11+woffset].ys[1] = 104+y;
	fgg->wireArray[11+woffset].xs[2] = 57+x;
	fgg->wireArray[11+woffset].ys[2] = 104+y;
	fgg->wireArray[11+woffset].xs[3] = 57+x;
	fgg->wireArray[11+woffset].ys[3] = 90+y;
	DEBUG_LOG("L\n");
	fgg->gateArray[2+offset].outputids[1] = 8+offset;
	fgg->gateArray[8+offset].inputids[1] = 2+offset;
	fgg->wireArray[12+woffset].xs[0] = 57+x;
	fgg->wireArray[12+woffset].ys[0] = 180+y;
	fgg->wireArray[12+woffset].xs[1] = 57+x;
	fgg->wireArray[12+woffset].ys[1] = 104+y;
	fgg->wireArray[12+woffset].xs[2] = 42+x;
	fgg->wireArray[12+woffset].ys[2] = 104+y;
	fgg->wireArray[12+woffset].xs[3] = 42+x;
	fgg->wireArray[12+woffset].ys[3] = 90+y;
	DEBUG_LOG("M\n");
	fgg->gateArray[8+offset].outputids[0] = 10+offset;
	fgg->gateArray[10+offset].inputids[0] = 8+offset;
	fgg->wireArray[13+woffset].xs[0] = 37+x;
	fgg->wireArray[13+woffset].ys[0] = 80+y;
	fgg->wireArray[13+woffset].xs[1] = 37+x;
	fgg->wireArray[13+woffset].ys[1] = 70+y;
	DEBUG_LOG("N\n");
	fgg->gateArray[9+offset].outputids[0] = 11+offset;
	fgg->gateArray[11+offset].inputids[1] = 9+offset;
	fgg->wireArray[14+woffset].xs[0] = 52+x;
	fgg->wireArray[14+woffset].ys[0] = 80+y;
	fgg->wireArray[14+woffset].xs[1] = 52+x;
	fgg->wireArray[14+woffset].ys[1] = 70+y;
	fgg->wireArray[14+woffset].xs[2] = 46+x;
	fgg->wireArray[14+woffset].ys[2] = 70+y;
	fgg->wireArray[14+woffset].xs[3] = 46+x;
	fgg->wireArray[14+woffset].ys[3] = 43+y;
	DEBUG_LOG("O\n");
	fgg->gateArray[9+offset].outputids[1] = 12+offset;
	fgg->gateArray[12+offset].inputids[0] = 9+offset;
	fgg->wireArray[15+woffset].xs[0] = 52+x;
	fgg->wireArray[15+woffset].ys[0] = 80+y;
	fgg->wireArray[15+woffset].xs[1] = 52+x;
	fgg->wireArray[15+woffset].ys[1] = 70+y;
	fgg->wireArray[15+woffset].xs[2] = 55+x;
	fgg->wireArray[15+woffset].ys[2] = 70+y;
	fgg->wireArray[15+woffset].xs[3] = 55+x;
	fgg->wireArray[15+woffset].ys[3] = 43+y;
	DEBUG_LOG("P\n");
	fgg->gateArray[10+offset].outputids[0] = 11+offset;
	fgg->gateArray[11+offset].inputids[0] = 10+offset;
	fgg->wireArray[16+woffset].xs[0] = 37+x;
	fgg->wireArray[16+woffset].ys[0] = 60+y;
	fgg->wireArray[16+woffset].xs[1] = 37+x;
	fgg->wireArray[16+woffset].ys[1] = 56+y;
	fgg->wireArray[16+woffset].xs[2] = 37+x;
	fgg->wireArray[16+woffset].ys[2] = 56+y;
	fgg->wireArray[16+woffset].xs[3] = 37+x;
	fgg->wireArray[16+woffset].ys[3] = 45+y;
	DEBUG_LOG("Q\n");
	fgg->gateArray[11+offset].outputids[0] = 13+offset;
	fgg->gateArray[13+offset].inputids[0] = 11+offset;
	fgg->wireArray[17+woffset].xs[0] = 41+x;
	fgg->wireArray[17+woffset].ys[0] = 35+y;
	fgg->wireArray[17+woffset].xs[1] = 41+x;
	fgg->wireArray[17+woffset].ys[1] = 30+y;
	DEBUG_LOG("R\n");
	fgg->gateArray[13+offset].outputids[0] = -1;
	fgg->wireArray[18+woffset].xs[0] = 41+x;
	fgg->wireArray[18+woffset].ys[0] = 30+y;
	fgg->wireArray[18+woffset].xs[1] = 41+x;
	fgg->wireArray[18+woffset].ys[1] = 10+y;
	DEBUG_LOG("S\n");
	fgg->gateArray[12+offset].outputids[0] = -1;
	fgg->wireArray[19+woffset].xs[0] = 59+x;
	fgg->wireArray[19+woffset].ys[0] = 35+y;
	fgg->wireArray[19+woffset].xs[1] = 59+x;
	fgg->wireArray[19+woffset].ys[1] = 10+y;
	
	DEBUG_LOG("END OF ADD FULL ADDER\n");
	return offset;
}

int gategraph_8bitAdder(struct gategraph_fullGraph_s* fgg, int x, int y)
{
	DEBUG_LOG("ADD FULL ADDER\n");
	int offset = fgg->numberOfGates;
	int woffset = fgg->numberOfWires;
	
	//byte out
	gategraph_addGateToGraph(fgg, 'p', 10+x, 0+y, 0, -1, 1, 1);//0
	gategraph_addGateToGraph(fgg, 'p', 15+x, 0+y, 0, -1, 1, 1);//1
	gategraph_addGateToGraph(fgg, 'p', 20+x, 0+y, 0, -1, 1, 1);//2
	gategraph_addGateToGraph(fgg, 'p', 25+x, 0+y, 0, -1, 1, 1);//3
	gategraph_addGateToGraph(fgg, 'p', 30+x, 0+y, 0, -1, 1, 1);//4
	gategraph_addGateToGraph(fgg, 'p', 35+x, 0+y, 0, -1, 1, 1);//5
	gategraph_addGateToGraph(fgg, 'p', 40+x, 0+y, 0, -1, 1, 1);//6
	gategraph_addGateToGraph(fgg, 'p', 45+x, 0+y, 0, -1, 1, 1);//7
	//byte one in
	gategraph_addGateToGraph(fgg, 'p', 10+x, 240+y, 0, -1, 1, 2);//8
	gategraph_addGateToGraph(fgg, 'p', 15+x, 240+y, 0, -1, 1, 2);//9
	gategraph_addGateToGraph(fgg, 'p', 20+x, 240+y, 0, -1, 1, 2);//10
	gategraph_addGateToGraph(fgg, 'p', 25+x, 240+y, 0, -1, 1, 2);//11
	gategraph_addGateToGraph(fgg, 'p', 30+x, 240+y, 0, -1, 1, 2);//12
	gategraph_addGateToGraph(fgg, 'p', 35+x, 240+y, 0, -1, 1, 2);//13
	gategraph_addGateToGraph(fgg, 'p', 40+x, 240+y, 0, -1, 1, 2);//14
	gategraph_addGateToGraph(fgg, 'p', 45+x, 240+y, 0, -1, 1, 2);//15
	//byte two in
	gategraph_addGateToGraph(fgg, 'p', 60+x, 240+y, 0, -1, 1, 2);//16
	gategraph_addGateToGraph(fgg, 'p', 65+x, 240+y, 0, -1, 1, 2);//17
	gategraph_addGateToGraph(fgg, 'p', 70+x, 240+y, 0, -1, 1, 2);//18
	gategraph_addGateToGraph(fgg, 'p', 75+x, 240+y, 0, -1, 1, 2);//19
	gategraph_addGateToGraph(fgg, 'p', 80+x, 240+y, 0, -1, 1, 2);//20
	gategraph_addGateToGraph(fgg, 'p', 85+x, 240+y, 0, -1, 1, 2);//21
	gategraph_addGateToGraph(fgg, 'p', 90+x, 240+y, 0, -1, 1, 2);//22
	gategraph_addGateToGraph(fgg, 'p', 95+x, 240+y, 0, -1, 1, 2);//23
	//overflow and +1
	gategraph_addGateToGraph(fgg, 'p', 0+x, 0+y, 0, -1, 1, 2);//24
	gategraph_addGateToGraph(fgg, 'p', 110+x, 240+y, 0, -1, 1, 2);//25
	
	
	
	
	int sectionStart = 0;
	int lastwire = 0;
	
	//first adder
	sectionStart = gategraph_addFullAdder(fgg,318+x,10+y);
	//output wire
	fgg->gateArray[sectionStart+13].outputids[0] = offset+7;
	fgg->gateArray[offset+7].inputids[0] = sectionStart+13;
	lastwire = gategraph_addWireToGraph(fgg, 4,sectionStart+13,-1);
	fgg->wireArray[lastwire].xs[0] = 359+x;
	fgg->wireArray[lastwire].ys[0] = 40+y;
	fgg->wireArray[lastwire].xs[1] = 359+x;
	fgg->wireArray[lastwire].ys[1] = 4+y;
	fgg->wireArray[lastwire].xs[2] = 45+x;
	fgg->wireArray[lastwire].ys[2] = 4+y;
	fgg->wireArray[lastwire].xs[3] = 45+x;
	fgg->wireArray[lastwire].ys[3] = 0+y;
	//input 1
	fgg->gateArray[offset+15].outputids[0] = sectionStart+0;
	fgg->gateArray[sectionStart+0].inputids[0] = offset+15;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+15,-1);
	fgg->wireArray[lastwire].xs[0] = 45+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 45+x;
	fgg->wireArray[lastwire].ys[1] = 219+y;
	fgg->wireArray[lastwire].xs[2] = 344+x;
	fgg->wireArray[lastwire].ys[2] = 219+y;
	fgg->wireArray[lastwire].xs[3] = 344+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	//input 2
	fgg->gateArray[offset+23].outputids[0] = sectionStart+1;
	fgg->gateArray[sectionStart+1].inputids[0] = offset+23;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+23,-1);
	fgg->wireArray[lastwire].xs[0] = 95+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 95+x;
	fgg->wireArray[lastwire].ys[1] = 235+y;
	fgg->wireArray[lastwire].xs[2] = 355+x;
	fgg->wireArray[lastwire].ys[2] = 235+y;
	fgg->wireArray[lastwire].xs[3] = 355+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	//extra
	fgg->gateArray[offset+25].outputids[0] = sectionStart+2;
	fgg->gateArray[sectionStart+2].inputids[0] = offset+25;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+25,-1);
	fgg->wireArray[lastwire].xs[0] = 110+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 110+x;
	fgg->wireArray[lastwire].ys[1] = 237+y;
	fgg->wireArray[lastwire].xs[2] = 375+x;
	fgg->wireArray[lastwire].ys[2] = 237+y;
	fgg->wireArray[lastwire].xs[3] = 375+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	
	//second adder
	sectionStart = gategraph_addFullAdder(fgg,268+x,10+y);
	//carry
	fgg->gateArray[sectionStart-2].outputids[0] = sectionStart+2;
	fgg->gateArray[sectionStart+2].inputids[0] = sectionStart-2;
	lastwire = gategraph_addWireToGraph(fgg, 5,sectionStart-2,-1);
	fgg->wireArray[lastwire].xs[0] = 377+x;
	fgg->wireArray[lastwire].ys[0] = 45+y;
	fgg->wireArray[lastwire].xs[1] = 377+x;
	fgg->wireArray[lastwire].ys[1] = 20+y;
	fgg->wireArray[lastwire].xs[2] = 338+x;
	fgg->wireArray[lastwire].ys[2] = 20+y;
	fgg->wireArray[lastwire].xs[3] = 338+x;
	fgg->wireArray[lastwire].ys[3] = 190+y;
	fgg->wireArray[lastwire].xs[4] = 323+x;
	fgg->wireArray[lastwire].ys[4] = 190+y;
	//output
	fgg->gateArray[sectionStart+13].outputids[0] = offset+6;
	fgg->gateArray[offset+6].inputids[0] = sectionStart+13;
	lastwire = gategraph_addWireToGraph(fgg, 4,sectionStart+13,-1);
	fgg->wireArray[lastwire].xs[0] = 309+x;
	fgg->wireArray[lastwire].ys[0] = 40+y;
	fgg->wireArray[lastwire].xs[1] = 309+x;
	fgg->wireArray[lastwire].ys[1] = 6+y;
	fgg->wireArray[lastwire].xs[2] = 40+x;
	fgg->wireArray[lastwire].ys[2] = 6+y;
	fgg->wireArray[lastwire].xs[3] = 40+x;
	fgg->wireArray[lastwire].ys[3] = 0+y;
	//input 1
	fgg->gateArray[offset+14].outputids[0] = sectionStart+0;
	fgg->gateArray[sectionStart+0].inputids[0] = offset+14;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+14,-1);
	fgg->wireArray[lastwire].xs[0] = 40+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 40+x;
	fgg->wireArray[lastwire].ys[1] = 217+y;
	fgg->wireArray[lastwire].xs[2] = 294+x;
	fgg->wireArray[lastwire].ys[2] = 217+y;
	fgg->wireArray[lastwire].xs[3] = 294+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	//input 2
	fgg->gateArray[offset+22].outputids[0] = sectionStart+1;
	fgg->gateArray[sectionStart+1].inputids[0] = offset+22;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+22,-1);
	fgg->wireArray[lastwire].xs[0] = 90+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 90+x;
	fgg->wireArray[lastwire].ys[1] = 233+y;
	fgg->wireArray[lastwire].xs[2] = 305+x;
	fgg->wireArray[lastwire].ys[2] = 233+y;
	fgg->wireArray[lastwire].xs[3] = 305+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	
	//third adder
	sectionStart = gategraph_addFullAdder(fgg,218+x,10+y);
	//carry
	fgg->gateArray[sectionStart-2].outputids[0] = sectionStart+2;
	fgg->gateArray[sectionStart+2].inputids[0] = sectionStart-2;
	lastwire = gategraph_addWireToGraph(fgg, 5,sectionStart-2,-1);
	fgg->wireArray[lastwire].xs[0] = 327+x;
	fgg->wireArray[lastwire].ys[0] = 45+y;
	fgg->wireArray[lastwire].xs[1] = 327+x;
	fgg->wireArray[lastwire].ys[1] = 20+y;
	fgg->wireArray[lastwire].xs[2] = 288+x;
	fgg->wireArray[lastwire].ys[2] = 20+y;
	fgg->wireArray[lastwire].xs[3] = 288+x;
	fgg->wireArray[lastwire].ys[3] = 190+y;
	fgg->wireArray[lastwire].xs[4] = 273+x;
	fgg->wireArray[lastwire].ys[4] = 190+y;
	//output
	fgg->gateArray[sectionStart+13].outputids[0] = offset+5;
	fgg->gateArray[offset+5].inputids[0] = sectionStart+13;
	lastwire = gategraph_addWireToGraph(fgg, 4,sectionStart+13,-1);
	fgg->wireArray[lastwire].xs[0] = 259+x;
	fgg->wireArray[lastwire].ys[0] = 40+y;
	fgg->wireArray[lastwire].xs[1] = 259+x;
	fgg->wireArray[lastwire].ys[1] = 8+y;
	fgg->wireArray[lastwire].xs[2] = 35+x;
	fgg->wireArray[lastwire].ys[2] = 8+y;
	fgg->wireArray[lastwire].xs[3] = 35+x;
	fgg->wireArray[lastwire].ys[3] = 0+y;
	//input 1
	fgg->gateArray[offset+13].outputids[0] = sectionStart+0;
	fgg->gateArray[sectionStart+0].inputids[0] = offset+13;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+13,-1);
	fgg->wireArray[lastwire].xs[0] = 35+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 35+x;
	fgg->wireArray[lastwire].ys[1] = 215+y;
	fgg->wireArray[lastwire].xs[2] = 244+x;
	fgg->wireArray[lastwire].ys[2] = 215+y;
	fgg->wireArray[lastwire].xs[3] = 244+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	//input 2
	fgg->gateArray[offset+21].outputids[0] = sectionStart+1;
	fgg->gateArray[sectionStart+1].inputids[0] = offset+21;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+21,-1);
	fgg->wireArray[lastwire].xs[0] = 85+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 85+x;
	fgg->wireArray[lastwire].ys[1] = 231+y;
	fgg->wireArray[lastwire].xs[2] = 255+x;
	fgg->wireArray[lastwire].ys[2] = 231+y;
	fgg->wireArray[lastwire].xs[3] = 255+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	
	//forth adder
	sectionStart = gategraph_addFullAdder(fgg,168+x,10+y);
	//carry
	fgg->gateArray[sectionStart-2].outputids[0] = sectionStart+2;
	fgg->gateArray[sectionStart+2].inputids[0] = sectionStart-2;
	lastwire = gategraph_addWireToGraph(fgg, 5,sectionStart-2,-1);
	fgg->wireArray[lastwire].xs[0] = 277+x;
	fgg->wireArray[lastwire].ys[0] = 45+y;
	fgg->wireArray[lastwire].xs[1] = 277+x;
	fgg->wireArray[lastwire].ys[1] = 20+y;
	fgg->wireArray[lastwire].xs[2] = 238+x;
	fgg->wireArray[lastwire].ys[2] = 20+y;
	fgg->wireArray[lastwire].xs[3] = 238+x;
	fgg->wireArray[lastwire].ys[3] = 190+y;
	fgg->wireArray[lastwire].xs[4] = 223+x;
	fgg->wireArray[lastwire].ys[4] = 190+y;
	//output
	fgg->gateArray[sectionStart+13].outputids[0] = offset+4;
	fgg->gateArray[offset+4].inputids[0] = sectionStart+13;
	lastwire = gategraph_addWireToGraph(fgg, 4,sectionStart+13,-1);
	fgg->wireArray[lastwire].xs[0] = 209+x;
	fgg->wireArray[lastwire].ys[0] = 40+y;
	fgg->wireArray[lastwire].xs[1] = 209+x;
	fgg->wireArray[lastwire].ys[1] = 10+y;
	fgg->wireArray[lastwire].xs[2] = 30+x;
	fgg->wireArray[lastwire].ys[2] = 10+y;
	fgg->wireArray[lastwire].xs[3] = 30+x;
	fgg->wireArray[lastwire].ys[3] = 0+y;
	//input 1
	fgg->gateArray[offset+12].outputids[0] = sectionStart+0;
	fgg->gateArray[sectionStart+0].inputids[0] = offset+12;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+12,-1);
	fgg->wireArray[lastwire].xs[0] = 30+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 30+x;
	fgg->wireArray[lastwire].ys[1] = 213+y;
	fgg->wireArray[lastwire].xs[2] = 194+x;
	fgg->wireArray[lastwire].ys[2] = 213+y;
	fgg->wireArray[lastwire].xs[3] = 194+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	//input 2
	fgg->gateArray[offset+20].outputids[0] = sectionStart+1;
	fgg->gateArray[sectionStart+1].inputids[0] = offset+20;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+20,-1);
	fgg->wireArray[lastwire].xs[0] = 80+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 80+x;
	fgg->wireArray[lastwire].ys[1] = 229+y;
	fgg->wireArray[lastwire].xs[2] = 205+x;
	fgg->wireArray[lastwire].ys[2] = 229+y;
	fgg->wireArray[lastwire].xs[3] = 205+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	
	//fifth adder
	sectionStart = gategraph_addFullAdder(fgg,118+x,10+y);
	//carry
	fgg->gateArray[sectionStart-2].outputids[0] = sectionStart+2;
	fgg->gateArray[sectionStart+2].inputids[0] = sectionStart-2;
	lastwire = gategraph_addWireToGraph(fgg, 5,sectionStart-2,-1);
	fgg->wireArray[lastwire].xs[0] = 227+x;
	fgg->wireArray[lastwire].ys[0] = 45+y;
	fgg->wireArray[lastwire].xs[1] = 227+x;
	fgg->wireArray[lastwire].ys[1] = 20+y;
	fgg->wireArray[lastwire].xs[2] = 188+x;
	fgg->wireArray[lastwire].ys[2] = 20+y;
	fgg->wireArray[lastwire].xs[3] = 188+x;
	fgg->wireArray[lastwire].ys[3] = 190+y;
	fgg->wireArray[lastwire].xs[4] = 173+x;
	fgg->wireArray[lastwire].ys[4] = 190+y;
	//output
	fgg->gateArray[sectionStart+13].outputids[0] = offset+3;
	fgg->gateArray[offset+3].inputids[0] = sectionStart+13;
	lastwire = gategraph_addWireToGraph(fgg, 4,sectionStart+13,-1);
	fgg->wireArray[lastwire].xs[0] = 159+x;
	fgg->wireArray[lastwire].ys[0] = 40+y;
	fgg->wireArray[lastwire].xs[1] = 159+x;
	fgg->wireArray[lastwire].ys[1] = 12+y;
	fgg->wireArray[lastwire].xs[2] = 25+x;
	fgg->wireArray[lastwire].ys[2] = 12+y;
	fgg->wireArray[lastwire].xs[3] = 25+x;
	fgg->wireArray[lastwire].ys[3] = 0+y;
	//input 1
	fgg->gateArray[offset+11].outputids[0] = sectionStart+0;
	fgg->gateArray[sectionStart+0].inputids[0] = offset+11;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+11,-1);
	fgg->wireArray[lastwire].xs[0] = 25+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 25+x;
	fgg->wireArray[lastwire].ys[1] = 211+y;
	fgg->wireArray[lastwire].xs[2] = 144+x;
	fgg->wireArray[lastwire].ys[2] = 211+y;
	fgg->wireArray[lastwire].xs[3] = 144+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	//input 2
	fgg->gateArray[offset+19].outputids[0] = sectionStart+1;
	fgg->gateArray[sectionStart+1].inputids[0] = offset+19;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+19,-1);
	fgg->wireArray[lastwire].xs[0] = 75+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 75+x;
	fgg->wireArray[lastwire].ys[1] = 227+y;
	fgg->wireArray[lastwire].xs[2] = 155+x;
	fgg->wireArray[lastwire].ys[2] = 227+y;
	fgg->wireArray[lastwire].xs[3] = 155+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	
	//sixth adder
	sectionStart = gategraph_addFullAdder(fgg,68+x,10+y);
	//carry
	fgg->gateArray[sectionStart-2].outputids[0] = sectionStart+2;
	fgg->gateArray[sectionStart+2].inputids[0] = sectionStart-2;
	lastwire = gategraph_addWireToGraph(fgg, 5,sectionStart-2,-1);
	fgg->wireArray[lastwire].xs[0] = 177+x;
	fgg->wireArray[lastwire].ys[0] = 45+y;
	fgg->wireArray[lastwire].xs[1] = 177+x;
	fgg->wireArray[lastwire].ys[1] = 20+y;
	fgg->wireArray[lastwire].xs[2] = 138+x;
	fgg->wireArray[lastwire].ys[2] = 20+y;
	fgg->wireArray[lastwire].xs[3] = 138+x;
	fgg->wireArray[lastwire].ys[3] = 190+y;
	fgg->wireArray[lastwire].xs[4] = 123+x;
	fgg->wireArray[lastwire].ys[4] = 190+y;
	//output
	fgg->gateArray[sectionStart+13].outputids[0] = offset+2;
	fgg->gateArray[offset+2].inputids[0] = sectionStart+13;
	lastwire = gategraph_addWireToGraph(fgg, 4,sectionStart+13,-1);
	fgg->wireArray[lastwire].xs[0] = 109+x;
	fgg->wireArray[lastwire].ys[0] = 40+y;
	fgg->wireArray[lastwire].xs[1] = 109+x;
	fgg->wireArray[lastwire].ys[1] = 14+y;
	fgg->wireArray[lastwire].xs[2] = 20+x;
	fgg->wireArray[lastwire].ys[2] = 14+y;
	fgg->wireArray[lastwire].xs[3] = 20+x;
	fgg->wireArray[lastwire].ys[3] = 0+y;
	//input 1
	fgg->gateArray[offset+10].outputids[0] = sectionStart+0;
	fgg->gateArray[sectionStart+0].inputids[0] = offset+10;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+10,-1);
	fgg->wireArray[lastwire].xs[0] = 20+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 20+x;
	fgg->wireArray[lastwire].ys[1] = 209+y;
	fgg->wireArray[lastwire].xs[2] = 94+x;
	fgg->wireArray[lastwire].ys[2] = 209+y;
	fgg->wireArray[lastwire].xs[3] = 94+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	//input 2
	fgg->gateArray[offset+18].outputids[0] = sectionStart+1;
	fgg->gateArray[sectionStart+1].inputids[0] = offset+18;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+18,-1);
	fgg->wireArray[lastwire].xs[0] = 70+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 70+x;
	fgg->wireArray[lastwire].ys[1] = 225+y;
	fgg->wireArray[lastwire].xs[2] = 105+x;
	fgg->wireArray[lastwire].ys[2] = 225+y;
	fgg->wireArray[lastwire].xs[3] = 105+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	
	//seventh adder
	sectionStart = gategraph_addFullAdder(fgg,18+x,10+y);
	//carry
	fgg->gateArray[sectionStart-2].outputids[0] = sectionStart+2;
	fgg->gateArray[sectionStart+2].inputids[0] = sectionStart-2;
	lastwire = gategraph_addWireToGraph(fgg, 5,sectionStart-2,-1);
	fgg->wireArray[lastwire].xs[0] = 127+x;
	fgg->wireArray[lastwire].ys[0] = 45+y;
	fgg->wireArray[lastwire].xs[1] = 127+x;
	fgg->wireArray[lastwire].ys[1] = 20+y;
	fgg->wireArray[lastwire].xs[2] = 88+x;
	fgg->wireArray[lastwire].ys[2] = 20+y;
	fgg->wireArray[lastwire].xs[3] = 88+x;
	fgg->wireArray[lastwire].ys[3] = 190+y;
	fgg->wireArray[lastwire].xs[4] = 73+x;
	fgg->wireArray[lastwire].ys[4] = 190+y;
	//output
	fgg->gateArray[sectionStart+13].outputids[0] = offset+1;
	fgg->gateArray[offset+1].inputids[0] = sectionStart+13;
	lastwire = gategraph_addWireToGraph(fgg, 4,sectionStart+13,-1);
	fgg->wireArray[lastwire].xs[0] = 59+x;
	fgg->wireArray[lastwire].ys[0] = 40+y;
	fgg->wireArray[lastwire].xs[1] = 59+x;
	fgg->wireArray[lastwire].ys[1] = 16+y;
	fgg->wireArray[lastwire].xs[2] = 15+x;
	fgg->wireArray[lastwire].ys[2] = 16+y;
	fgg->wireArray[lastwire].xs[3] = 15+x;
	fgg->wireArray[lastwire].ys[3] = 0+y;
	//input 1
	fgg->gateArray[offset+9].outputids[0] = sectionStart+0;
	fgg->gateArray[sectionStart+0].inputids[0] = offset+9;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+9,-1);
	fgg->wireArray[lastwire].xs[0] = 15+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 15+x;
	fgg->wireArray[lastwire].ys[1] = 207+y;
	fgg->wireArray[lastwire].xs[2] = 44+x;
	fgg->wireArray[lastwire].ys[2] = 207+y;
	fgg->wireArray[lastwire].xs[3] = 44+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	//input 2
	fgg->gateArray[offset+17].outputids[0] = sectionStart+1;
	fgg->gateArray[sectionStart+1].inputids[0] = offset+17;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+17,-1);
	fgg->wireArray[lastwire].xs[0] = 65+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 65+x;
	fgg->wireArray[lastwire].ys[1] = 221+y;
	fgg->wireArray[lastwire].xs[2] = 55+x;
	fgg->wireArray[lastwire].ys[2] = 221+y;
	fgg->wireArray[lastwire].xs[3] = 55+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	
	//eighth adder
	sectionStart = gategraph_addFullAdder(fgg,-32+x,10+y);
	//carry
	fgg->gateArray[sectionStart-2].outputids[0] = sectionStart+2;
	fgg->gateArray[sectionStart+2].inputids[0] = sectionStart-2;
	lastwire = gategraph_addWireToGraph(fgg, 5,sectionStart-2,-1);
	fgg->wireArray[lastwire].xs[0] = 77+x;
	fgg->wireArray[lastwire].ys[0] = 45+y;
	fgg->wireArray[lastwire].xs[1] = 77+x;
	fgg->wireArray[lastwire].ys[1] = 20+y;
	fgg->wireArray[lastwire].xs[2] = 38+x;
	fgg->wireArray[lastwire].ys[2] = 20+y;
	fgg->wireArray[lastwire].xs[3] = 38+x;
	fgg->wireArray[lastwire].ys[3] = 190+y;
	fgg->wireArray[lastwire].xs[4] = 23+x;
	fgg->wireArray[lastwire].ys[4] = 190+y;
	//output
	fgg->gateArray[sectionStart+13].outputids[0] = offset+0;
	fgg->gateArray[offset+0].inputids[0] = sectionStart+13;
	lastwire = gategraph_addWireToGraph(fgg, 4,sectionStart+13,-1);
	fgg->wireArray[lastwire].xs[0] = 9+x;
	fgg->wireArray[lastwire].ys[0] = 40+y;
	fgg->wireArray[lastwire].xs[1] = 9+x;
	fgg->wireArray[lastwire].ys[1] = 16+y;
	fgg->wireArray[lastwire].xs[2] = 9+x;
	fgg->wireArray[lastwire].ys[2] = 16+y;
	fgg->wireArray[lastwire].xs[3] = 9+x;
	fgg->wireArray[lastwire].ys[3] = 0+y;
	//input 1
	fgg->gateArray[offset+8].outputids[0] = sectionStart+0;
	fgg->gateArray[sectionStart+0].inputids[0] = offset+8;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+8,-1);
	fgg->wireArray[lastwire].xs[0] = 10+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 10+x;
	fgg->wireArray[lastwire].ys[1] = 205+y;
	fgg->wireArray[lastwire].xs[2] = -6+x;
	fgg->wireArray[lastwire].ys[2] = 205+y;
	fgg->wireArray[lastwire].xs[3] = -6+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	//input 2
	fgg->gateArray[offset+16].outputids[0] = sectionStart+1;
	fgg->gateArray[sectionStart+1].inputids[0] = offset+16;
	lastwire = gategraph_addWireToGraph(fgg, 4,offset+16,-1);
	fgg->wireArray[lastwire].xs[0] = 60+x;
	fgg->wireArray[lastwire].ys[0] = 240+y;
	fgg->wireArray[lastwire].xs[1] = 60+x;
	fgg->wireArray[lastwire].ys[1] = 223+y;
	fgg->wireArray[lastwire].xs[2] = 5+x;
	fgg->wireArray[lastwire].ys[2] = 223+y;
	fgg->wireArray[lastwire].xs[3] = 5+x;
	fgg->wireArray[lastwire].ys[3] = 180+y;
	
	//overflow
	fgg->gateArray[sectionStart+12].outputids[0] = offset+24;
	fgg->gateArray[offset+24].inputids[0] = sectionStart+12;
	lastwire = gategraph_addWireToGraph(fgg, 4,sectionStart+12,-1);
	fgg->wireArray[lastwire].xs[0] = 27+x;
	fgg->wireArray[lastwire].ys[0] = 45+y;
	fgg->wireArray[lastwire].xs[1] = 27+x;
	fgg->wireArray[lastwire].ys[1] = 20+y;
	fgg->wireArray[lastwire].xs[2] = 0+x;
	fgg->wireArray[lastwire].ys[2] = 20+y;
	fgg->wireArray[lastwire].xs[3] = 0+x;
	fgg->wireArray[lastwire].ys[3] = 0+y;
	
	return offset;
}

int gategraph_dFlipFlop(struct gategraph_fullGraph_s* fgg, int x, int y)
{
	DEBUG_LOG("ADD D FLIP FLOP\n");
	int offset = fgg->numberOfGates;
	int woffset = fgg->numberOfWires;
	
	gategraph_addGateToGraph(fgg, 'p', 0+x, 3+y, 1, -1, 1, 1);//0
	gategraph_addGateToGraph(fgg, 'p', 0+x, 44+y, 1, -1, 1, 3);//1
	gategraph_addGateToGraph(fgg, 'a', 32+x, 0+y, 1, -1, 2, 1);//2
	gategraph_addGateToGraph(fgg, 'a', 32+x, 32+y, 1, -1, 2, 1);//3
	gategraph_addGateToGraph(fgg, 'n', 49+x, 0+y, 1, -1, 1, 2);//4
	gategraph_addGateToGraph(fgg, 'n', 49+x, 32+y, 1, -1, 1, 1);//5
	gategraph_addGateToGraph(fgg, 'a', 80+x, 0+y, 1, -1, 2, 1);//6
	gategraph_addGateToGraph(fgg, 'a', 80+x, 32+y, 1, -1, 2, 1);//7
	gategraph_addGateToGraph(fgg, 'n', 97+x, 0+y, 1, -1, 1, 2);//8
	gategraph_addGateToGraph(fgg, 'n', 97+x, 32+y, 1, -1, 1, 2);//9
	gategraph_addGateToGraph(fgg, 'a', 128+x, 0+y, 1, -1, 2, 1);//10
	gategraph_addGateToGraph(fgg, 'a', 128+x, 32+y, 1, -1, 2, 1);//11
	gategraph_addGateToGraph(fgg, 'n', 145+x, 0+y, 1, -1, 1, 1);//12
	gategraph_addGateToGraph(fgg, 'n', 145+x, 32+y, 1, -1, 1, 1);//13
	gategraph_addGateToGraph(fgg, 'a', 176+x, 0+y, 1, -1, 2, 1);//14
	gategraph_addGateToGraph(fgg, 'a', 176+x, 32+y, 1, -1, 2, 1);//15
	gategraph_addGateToGraph(fgg, 'n', 193+x, 0+y, 1, -1, 1, 2);//16
	gategraph_addGateToGraph(fgg, 'n', 193+x, 32+y, 1, -1, 1, 2);//17
	gategraph_addGateToGraph(fgg, 'n', 105+x, 48+y, 1, -1, 1, 2);//18
	
	DEBUG_LOG("D FLIP FLOP add wires\n");
	gategraph_addWireToGraph(fgg, 2,0+offset,-1);//0
	gategraph_addWireToGraph(fgg, 4,1+offset,-1);//1
	gategraph_addWireToGraph(fgg, 2,1+offset,-1);//2
	gategraph_addWireToGraph(fgg, 4,1+offset,-1);//3
	gategraph_addWireToGraph(fgg, 2,2+offset,-1);//4
	gategraph_addWireToGraph(fgg, 2,3+offset,-1);//5
	gategraph_addWireToGraph(fgg, 4,4+offset,-1);//6
	gategraph_addWireToGraph(fgg, 6,4+offset,-1);//7
	gategraph_addWireToGraph(fgg, 4,5+offset,-1);//8
	gategraph_addWireToGraph(fgg, 2,6+offset,-1);//9
	gategraph_addWireToGraph(fgg, 2,7+offset,-1);//10
	gategraph_addWireToGraph(fgg, 4,8+offset,-1);//11
	gategraph_addWireToGraph(fgg, 6,8+offset,-1);//12
	gategraph_addWireToGraph(fgg, 6,9+offset,-1);//13
	gategraph_addWireToGraph(fgg, 4,9+offset,-1);//14
	gategraph_addWireToGraph(fgg, 4,18+offset,-1);//15
	gategraph_addWireToGraph(fgg, 4,18+offset,-1);//16
	gategraph_addWireToGraph(fgg, 2,10+offset,-1);//17
	gategraph_addWireToGraph(fgg, 2,11+offset,-1);//18
	gategraph_addWireToGraph(fgg, 4,12+offset,-1);//19
	gategraph_addWireToGraph(fgg, 4,13+offset,-1);//20
	gategraph_addWireToGraph(fgg, 2,14+offset,-1);//21
	gategraph_addWireToGraph(fgg, 2,15+offset,-1);//22
	gategraph_addWireToGraph(fgg, 6,16+offset,-1);//23
	gategraph_addWireToGraph(fgg, 6,17+offset,-1);//24
	gategraph_addWireToGraph(fgg, 2,16+offset,-1);//25
	gategraph_addWireToGraph(fgg, 2,17+offset,-1);//26
	
	
	
	
	//0
	fgg->gateArray[0+offset].outputids[0] = 2+offset;
	fgg->gateArray[2+offset].inputids[0] = 0+offset;
	fgg->wireArray[0+woffset].xs[0] = 0+x;
	fgg->wireArray[0+woffset].ys[0] = 3+y;
	fgg->wireArray[0+woffset].xs[1] = 32+x;
	fgg->wireArray[0+woffset].ys[1] = 3+y;
	//1
	fgg->gateArray[1+offset].outputids[0] = 2+offset;
	fgg->gateArray[2+offset].inputids[1] = 1+offset;
	fgg->wireArray[1+woffset].xs[0] = 0+x;
	fgg->wireArray[1+woffset].ys[0] = 44+y;
	fgg->wireArray[1+woffset].xs[1] = 16+x;
	fgg->wireArray[1+woffset].ys[1] = 44+y;
	fgg->wireArray[1+woffset].xs[2] = 16+x;
	fgg->wireArray[1+woffset].ys[2] = 12+y;
	fgg->wireArray[1+woffset].xs[3] = 32+x;
	fgg->wireArray[1+woffset].ys[3] = 12+y;
	//2
	fgg->gateArray[1+offset].outputids[1] = 3+offset;
	fgg->gateArray[3+offset].inputids[1] = 1+offset;
	fgg->wireArray[2+woffset].xs[0] = 0+x;
	fgg->wireArray[2+woffset].ys[0] = 44+y;
	fgg->wireArray[2+woffset].xs[1] = 45+x;
	fgg->wireArray[2+woffset].ys[1] = 44+y;
	//3
	fgg->gateArray[1+offset].outputids[2] = 18+offset;
	fgg->gateArray[18+offset].inputids[0] = 1+offset;
	fgg->wireArray[3+woffset].xs[0] = 0+x;
	fgg->wireArray[3+woffset].ys[0] = 44+y;
	fgg->wireArray[3+woffset].xs[1] = 16+x;
	fgg->wireArray[3+woffset].ys[1] = 44+y;
	fgg->wireArray[3+woffset].xs[2] = 16+x;
	fgg->wireArray[3+woffset].ys[2] = 56+y;
	fgg->wireArray[3+woffset].xs[3] = 108+x;
	fgg->wireArray[3+woffset].ys[3] = 56+y;
	//4
	fgg->gateArray[2+offset].outputids[0] = 4+offset;
	fgg->gateArray[4+offset].inputids[0] = 2+offset;
	fgg->wireArray[4+woffset].xs[0] = 40+x;
	fgg->wireArray[4+woffset].ys[0] = 8+y;
	fgg->wireArray[4+woffset].xs[1] = 50+x;
	fgg->wireArray[4+woffset].ys[1] = 8+y;
	//5
	fgg->gateArray[3+offset].outputids[0] = 5+offset;
	fgg->gateArray[5+offset].inputids[0] = 3+offset;
	fgg->wireArray[5+woffset].xs[0] = 40+x;
	fgg->wireArray[5+woffset].ys[0] = 40+y;
	fgg->wireArray[5+woffset].xs[1] = 50+x;
	fgg->wireArray[5+woffset].ys[1] = 40+y;
	//6
	fgg->gateArray[4+offset].outputids[0] = 6+offset;
	fgg->gateArray[6+offset].inputids[0] = 4+offset;
	fgg->wireArray[6+woffset].xs[0] = 56+x;
	fgg->wireArray[6+woffset].ys[0] = 8+y;
	fgg->wireArray[6+woffset].xs[1] = 68+x;
	fgg->wireArray[6+woffset].ys[1] = 8+y;
	fgg->wireArray[6+woffset].xs[2] = 68+x;
	fgg->wireArray[6+woffset].ys[2] = 4+y;
	fgg->wireArray[6+woffset].xs[3] = 80+x;
	fgg->wireArray[6+woffset].ys[3] = 4+y;
	//7
	fgg->gateArray[4+offset].outputids[1] = 3+offset;
	fgg->gateArray[3+offset].inputids[0] = 4+offset;
	fgg->wireArray[7+woffset].xs[0] = 56+x;
	fgg->wireArray[7+woffset].ys[0] = 8+y;
	fgg->wireArray[7+woffset].xs[1] = 68+x;
	fgg->wireArray[7+woffset].ys[1] = 8+y;
	fgg->wireArray[7+woffset].xs[2] = 68+x;
	fgg->wireArray[7+woffset].ys[2] = 14+y;
	fgg->wireArray[7+woffset].xs[3] = 29+x;
	fgg->wireArray[7+woffset].ys[3] = 29+y;
	fgg->wireArray[7+woffset].xs[4] = 29+x;
	fgg->wireArray[7+woffset].ys[4] = 35+y;
	fgg->wireArray[7+woffset].xs[5] = 34+x;
	fgg->wireArray[7+woffset].ys[5] = 35+y;
	//8
	fgg->gateArray[5+offset].outputids[0] = 7+offset;
	fgg->gateArray[7+offset].inputids[1] = 5+offset;
	fgg->wireArray[8+woffset].xs[0] = 56+x;
	fgg->wireArray[8+woffset].ys[0] = 40+y;
	fgg->wireArray[8+woffset].xs[1] = 68+x;
	fgg->wireArray[8+woffset].ys[1] = 40+y;
	fgg->wireArray[8+woffset].xs[2] = 68+x;
	fgg->wireArray[8+woffset].ys[2] = 44+y;
	fgg->wireArray[8+woffset].xs[3] = 80+x;
	fgg->wireArray[8+woffset].ys[3] = 44+y;
	
	//9
	fgg->gateArray[6+offset].outputids[0] = 8+offset;
	fgg->gateArray[8+offset].inputids[0] = 6+offset;
	fgg->wireArray[9+woffset].xs[0] = 90+x;
	fgg->wireArray[9+woffset].ys[0] = 8+y;
	fgg->wireArray[9+woffset].xs[1] = 104+x;
	fgg->wireArray[9+woffset].ys[1] = 8+y;
	
	//10
	fgg->gateArray[7+offset].outputids[0] = 9+offset;
	fgg->gateArray[9+offset].inputids[0] = 7+offset;
	fgg->wireArray[10+woffset].xs[0] = 90+x;
	fgg->wireArray[10+woffset].ys[0] = 40+y;
	fgg->wireArray[10+woffset].xs[1] = 104+x;
	fgg->wireArray[10+woffset].ys[1] = 40+y;
	
	//11
	fgg->gateArray[8+offset].outputids[0] = 10+offset;
	fgg->gateArray[10+offset].inputids[0] = 8+offset;
	fgg->wireArray[11+woffset].xs[0] = 104+x;
	fgg->wireArray[11+woffset].ys[0] = 8+y;
	fgg->wireArray[11+woffset].xs[1] = 116+x;
	fgg->wireArray[11+woffset].ys[1] = 8+y;
	fgg->wireArray[11+woffset].xs[2] = 116+x;
	fgg->wireArray[11+woffset].ys[2] = 4+y;
	fgg->wireArray[11+woffset].xs[3] = 128+x;
	fgg->wireArray[11+woffset].ys[3] = 4+y;
	
	//12
	fgg->gateArray[8+offset].outputids[1] = 7+offset;
	fgg->gateArray[7+offset].inputids[0] = 8+offset;
	fgg->wireArray[12+woffset].xs[0] = 104+x;
	fgg->wireArray[12+woffset].ys[0] = 8+y;
	fgg->wireArray[12+woffset].xs[1] = 116+x;
	fgg->wireArray[12+woffset].ys[1] = 8+y;
	fgg->wireArray[12+woffset].xs[2] = 116+x;
	fgg->wireArray[12+woffset].ys[2] = 14+y;
	fgg->wireArray[12+woffset].xs[3] = 77+x;
	fgg->wireArray[12+woffset].ys[3] = 29+y;
	fgg->wireArray[12+woffset].xs[4] = 77+x;
	fgg->wireArray[12+woffset].ys[4] = 35+y;
	fgg->wireArray[12+woffset].xs[5] = 82+x;
	fgg->wireArray[12+woffset].ys[5] = 35+y;
	//13
	fgg->gateArray[9+offset].outputids[0] = 6+offset;
	fgg->gateArray[6+offset].inputids[1] = 9+offset;
	fgg->wireArray[13+woffset].xs[0] = 104+x;
	fgg->wireArray[13+woffset].ys[0] = 40+y;
	fgg->wireArray[13+woffset].xs[1] = 116+x;
	fgg->wireArray[13+woffset].ys[1] = 40+y;
	fgg->wireArray[13+woffset].xs[2] = 116+x;
	fgg->wireArray[13+woffset].ys[2] = 34+y;
	fgg->wireArray[13+woffset].xs[3] = 77+x;
	fgg->wireArray[13+woffset].ys[3] = 19+y;
	fgg->wireArray[13+woffset].xs[4] = 77+x;
	fgg->wireArray[13+woffset].ys[4] = 12+y;
	fgg->wireArray[13+woffset].xs[5] = 82+x;
	fgg->wireArray[13+woffset].ys[5] = 12+y;
	//14
	fgg->gateArray[9+offset].outputids[1] = 11+offset;
	fgg->gateArray[11+offset].inputids[1] = 9+offset;
	fgg->wireArray[14+woffset].xs[0] = 104+x;
	fgg->wireArray[14+woffset].ys[0] = 40+y;
	fgg->wireArray[14+woffset].xs[1] = 116+x;
	fgg->wireArray[14+woffset].ys[1] = 40+y;
	fgg->wireArray[14+woffset].xs[2] = 116+x;
	fgg->wireArray[14+woffset].ys[2] = 44+y;
	fgg->wireArray[14+woffset].xs[3] = 128+x;
	fgg->wireArray[14+woffset].ys[3] = 44+y;
	//15
	fgg->gateArray[18+offset].outputids[0] = 10+offset;
	fgg->gateArray[10+offset].inputids[1] = 18+offset;
	fgg->wireArray[15+woffset].xs[0] = 113+x;
	fgg->wireArray[15+woffset].ys[0] = 56+y;
	fgg->wireArray[15+woffset].xs[1] = 122+x;
	fgg->wireArray[15+woffset].ys[1] = 56+y;
	fgg->wireArray[15+woffset].xs[2] = 122+x;
	fgg->wireArray[15+woffset].ys[2] = 12+y;
	fgg->wireArray[15+woffset].xs[3] = 128+x;
	fgg->wireArray[15+woffset].ys[3] = 12+y;
	//16
	fgg->gateArray[18+offset].outputids[1] = 11+offset;
	fgg->gateArray[11+offset].inputids[0] = 18+offset;
	fgg->wireArray[16+woffset].xs[0] = 113+x;
	fgg->wireArray[16+woffset].ys[0] = 56+y;
	fgg->wireArray[16+woffset].xs[1] = 122+x;
	fgg->wireArray[16+woffset].ys[1] = 56+y;
	fgg->wireArray[16+woffset].xs[2] = 122+x;
	fgg->wireArray[16+woffset].ys[2] = 35+y;
	fgg->wireArray[16+woffset].xs[3] = 128+x;
	fgg->wireArray[16+woffset].ys[3] = 35+y;
	//17
	fgg->gateArray[10+offset].outputids[0] = 12+offset;
	fgg->gateArray[12+offset].inputids[0] = 10+offset;
	fgg->wireArray[17+woffset].xs[0] = 138+x;
	fgg->wireArray[17+woffset].ys[0] = 8+y;
	fgg->wireArray[17+woffset].xs[1] = 152+x;
	fgg->wireArray[17+woffset].ys[1] = 8+y;
	//18
	fgg->gateArray[11+offset].outputids[0] = 13+offset;
	fgg->gateArray[13+offset].inputids[0] = 11+offset;
	fgg->wireArray[18+woffset].xs[0] = 138+x;
	fgg->wireArray[18+woffset].ys[0] = 40+y;
	fgg->wireArray[18+woffset].xs[1] = 152+x;
	fgg->wireArray[18+woffset].ys[1] = 40+y;
	//19
	fgg->gateArray[12+offset].outputids[0] = 14+offset;
	fgg->gateArray[14+offset].inputids[0] = 12+offset;
	fgg->wireArray[19+woffset].xs[0] = 156+x;
	fgg->wireArray[19+woffset].ys[0] = 8+y;
	fgg->wireArray[19+woffset].xs[1] = 164+x;
	fgg->wireArray[19+woffset].ys[1] = 8+y;
	fgg->wireArray[19+woffset].xs[2] = 164+x;
	fgg->wireArray[19+woffset].ys[2] = 4+y;
	fgg->wireArray[19+woffset].xs[3] = 176+x;
	fgg->wireArray[19+woffset].ys[3] = 4+y;
	//20
	fgg->gateArray[13+offset].outputids[0] = 15+offset;
	fgg->gateArray[15+offset].inputids[1] = 13+offset;
	fgg->wireArray[20+woffset].xs[0] = 152+x;
	fgg->wireArray[20+woffset].ys[0] = 40+y;
	fgg->wireArray[20+woffset].xs[1] = 164+x;
	fgg->wireArray[20+woffset].ys[1] = 40+y;
	fgg->wireArray[20+woffset].xs[2] = 164+x;
	fgg->wireArray[20+woffset].ys[2] = 44+y;
	fgg->wireArray[20+woffset].xs[3] = 176+x;
	fgg->wireArray[20+woffset].ys[3] = 44+y;
	//21
	fgg->gateArray[14+offset].outputids[0] = 16+offset;
	fgg->gateArray[16+offset].inputids[0] = 14+offset;
	fgg->wireArray[21+woffset].xs[0] = 186+x;
	fgg->wireArray[21+woffset].ys[0] = 8+y;
	fgg->wireArray[21+woffset].xs[1] = 202+x;
	fgg->wireArray[21+woffset].ys[1] = 8+y;
	//22
	fgg->gateArray[15+offset].outputids[0] = 17+offset;
	fgg->gateArray[17+offset].inputids[0] = 15+offset;
	fgg->wireArray[22+woffset].xs[0] = 186+x;
	fgg->wireArray[22+woffset].ys[0] = 40+y;
	fgg->wireArray[22+woffset].xs[1] = 202+x;
	fgg->wireArray[22+woffset].ys[1] = 40+y;
	//23
	fgg->gateArray[16+offset].outputids[1] = 15+offset;
	fgg->gateArray[15+offset].inputids[0] = 16+offset;
	fgg->wireArray[23+woffset].xs[0] = 200+x;
	fgg->wireArray[23+woffset].ys[0] = 8+y;
	fgg->wireArray[23+woffset].xs[1] = 212+x;
	fgg->wireArray[23+woffset].ys[1] = 8+y;
	fgg->wireArray[23+woffset].xs[2] = 212+x;
	fgg->wireArray[23+woffset].ys[2] = 14+y;
	fgg->wireArray[23+woffset].xs[3] = 173+x;
	fgg->wireArray[23+woffset].ys[3] = 29+y;
	fgg->wireArray[23+woffset].xs[4] = 173+x;
	fgg->wireArray[23+woffset].ys[4] = 35+y;
	fgg->wireArray[23+woffset].xs[5] = 178+x;
	fgg->wireArray[23+woffset].ys[5] = 35+y;
	//24
	fgg->gateArray[17+offset].outputids[1] = 14+offset;
	fgg->gateArray[14+offset].inputids[1] = 17+offset;
	fgg->wireArray[24+woffset].xs[0] = 200+x;
	fgg->wireArray[24+woffset].ys[0] = 40+y;
	fgg->wireArray[24+woffset].xs[1] = 212+x;
	fgg->wireArray[24+woffset].ys[1] = 40+y;
	fgg->wireArray[24+woffset].xs[2] = 212+x;
	fgg->wireArray[24+woffset].ys[2] = 34+y;
	fgg->wireArray[24+woffset].xs[3] = 173+x;
	fgg->wireArray[24+woffset].ys[3] = 19+y;
	fgg->wireArray[24+woffset].xs[4] = 173+x;
	fgg->wireArray[24+woffset].ys[4] = 12+y;
	fgg->wireArray[24+woffset].xs[5] = 178+x;
	fgg->wireArray[24+woffset].ys[5] = 12+y;
	//25
	fgg->gateArray[16+offset].outputids[0] = -1;
	fgg->wireArray[25+woffset].xs[0] = 200+x;
	fgg->wireArray[25+woffset].ys[0] = 8+y;
	fgg->wireArray[25+woffset].xs[1] = 220+x;
	fgg->wireArray[25+woffset].ys[1] = 8+y;
	//26
	fgg->gateArray[17+offset].outputids[0] = -1;
	fgg->wireArray[26+woffset].xs[0] = 200+x;
	fgg->wireArray[26+woffset].ys[0] = 40+y;
	fgg->wireArray[26+woffset].xs[1] = 220+x;
	fgg->wireArray[26+woffset].ys[1] = 40+y;
	
	return offset;
}

int gategraph_8bitReg(struct gategraph_fullGraph_s* fgg, int x, int y)
{
	DEBUG_LOG("ADD D FLIP FLOP\n");
	int offset = fgg->numberOfGates;
	int woffset = fgg->numberOfWires;

	//byte in
	gategraph_addGateToGraph(fgg, 'p', 10+x, 0+y, 0, -1, 1, 1);//0
	gategraph_addGateToGraph(fgg, 'p', 15+x, 0+y, 0, -1, 1, 1);//1
	gategraph_addGateToGraph(fgg, 'p', 20+x, 0+y, 0, -1, 1, 1);//2
	gategraph_addGateToGraph(fgg, 'p', 25+x, 0+y, 0, -1, 1, 1);//3
	gategraph_addGateToGraph(fgg, 'p', 30+x, 0+y, 0, -1, 1, 1);//4
	gategraph_addGateToGraph(fgg, 'p', 35+x, 0+y, 0, -1, 1, 1);//5
	gategraph_addGateToGraph(fgg, 'p', 40+x, 0+y, 0, -1, 1, 1);//6
	gategraph_addGateToGraph(fgg, 'p', 45+x, 0+y, 0, -1, 1, 1);//7
	//byte out
	gategraph_addGateToGraph(fgg, 'p', 320+x, 480+y, 0, -1, 1, 2);//8
	gategraph_addGateToGraph(fgg, 'p', 325+x, 480+y, 0, -1, 1, 2);//9
	gategraph_addGateToGraph(fgg, 'p', 330+x, 480+y, 0, -1, 1, 2);//10
	gategraph_addGateToGraph(fgg, 'p', 335+x, 480+y, 0, -1, 1, 2);//11
	gategraph_addGateToGraph(fgg, 'p', 340+x, 480+y, 0, -1, 1, 2);//12
	gategraph_addGateToGraph(fgg, 'p', 345+x, 480+y, 0, -1, 1, 2);//13
	gategraph_addGateToGraph(fgg, 'p', 350+x, 480+y, 0, -1, 1, 2);//14
	gategraph_addGateToGraph(fgg, 'p', 355+x, 480+y, 0, -1, 1, 2);//15
	//clock in
	gategraph_addGateToGraph(fgg, 'p', 55+x, 480+y, 0, -1, 1, 8);//16
	
	for(int i = 0; i < 8; i++)
	{
		//clock wire
		int sectionStart = gategraph_dFlipFlop(fgg, x+60, y+(i*60));
		fgg->gateArray[offset+16].outputids[i] = sectionStart+1;
		fgg->gateArray[sectionStart+1].inputids[0] = offset+16;
		int lastwire = gategraph_addWireToGraph(fgg, 3,offset+16,-1);
		fgg->wireArray[lastwire].xs[0] = 55+x;
		fgg->wireArray[lastwire].ys[0] = 480+y;
		fgg->wireArray[lastwire].xs[1] = 55+x;
		fgg->wireArray[lastwire].ys[1] = (i*60)+y+44;
		fgg->wireArray[lastwire].xs[2] = 60+x;
		fgg->wireArray[lastwire].ys[2] = (i*60)+y+44;
		
		//in wire
		fgg->gateArray[offset+i].outputids[0] = sectionStart+0;
		fgg->gateArray[sectionStart+0].inputids[0] = offset+i;
		lastwire = gategraph_addWireToGraph(fgg, 3,offset+i,-1);
		fgg->wireArray[lastwire].xs[0] = (5*i)+10+x;
		fgg->wireArray[lastwire].ys[0] = 0+y;
		fgg->wireArray[lastwire].xs[1] = (5*i)+10+x;
		fgg->wireArray[lastwire].ys[1] = (i*60)+y+3;
		fgg->wireArray[lastwire].xs[2] = 60+x;
		fgg->wireArray[lastwire].ys[2] = (i*60)+y+3;
		
		//out wire
		fgg->gateArray[sectionStart+16].outputids[0] = offset+i+8;
		fgg->gateArray[offset+i+8].inputids[0] = sectionStart+16;
		lastwire = gategraph_addWireToGraph(fgg, 3,sectionStart+16,-1);
		fgg->wireArray[lastwire].xs[0] = 280+x;
		fgg->wireArray[lastwire].ys[0] = (i*60)+y+8;
		fgg->wireArray[lastwire].xs[1] = 320+(i*5)+x;
		fgg->wireArray[lastwire].ys[1] = (i*60)+y+8;
		fgg->wireArray[lastwire].xs[2] = 320+(i*5)+x;
		fgg->wireArray[lastwire].ys[2] = 480+y;
	}
	

	return offset;
}
