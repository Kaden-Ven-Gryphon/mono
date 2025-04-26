#include <stdio.h>
#include "gategraph.h"
#include "gatecircuits.h"


int main()
{
	struct gategraph_fullGraph_s fgg;
	gategraph_initFullGraph(&fgg);
	
	
	int sectionStart = gategraph_8bitReg(&fgg,16,50);
	gategraph_addGateToList(&fgg.inputGatesList, sectionStart+8,0);
	gategraph_addGateToList(&fgg.inputGatesList, sectionStart+9,0);
	gategraph_addGateToList(&fgg.inputGatesList, sectionStart+10,0);
	gategraph_addGateToList(&fgg.inputGatesList, sectionStart+11,0);
	gategraph_addGateToList(&fgg.inputGatesList, sectionStart+12,0);
	gategraph_addGateToList(&fgg.inputGatesList, sectionStart+13,0);
	gategraph_addGateToList(&fgg.inputGatesList, sectionStart+14,0);
	gategraph_addGateToList(&fgg.inputGatesList, sectionStart+15,0);
	
	gategraph_addGateToList(&fgg.inputGatesList, sectionStart+16,0);
	
	
	
	
	int clock = sectionStart+16;
	
	fgg.gateArray[clock].inputStates[0] = 1;
	gategraph_updateGraph(&fgg, 10000);
	fgg.gateArray[clock].inputStates[0] = 0;
	gategraph_updateGraph(&fgg, 10000);
	
	int adderStart = gategraph_8bitAdder(&fgg,400,50);
	
	
	
	for(int i = 0; i < 8; i++)
	{
		fgg.gateArray[adderStart+i].outputids[0] = sectionStart+i+0;
		fgg.gateArray[sectionStart+i+0].inputids[0] = adderStart+i;
		int lastwire = gategraph_addWireToGraph(&fgg, 4,adderStart+i,-1);
		fgg.wireArray[lastwire].xs[0] = 400+10+(5*i);
		fgg.wireArray[lastwire].ys[0] = 50;
		fgg.wireArray[lastwire].xs[1] = 400+10+(5*i);
		fgg.wireArray[lastwire].ys[1] = 40-(i*2);
		fgg.wireArray[lastwire].xs[2] = 16+(5*i)+10;
		fgg.wireArray[lastwire].ys[2] = 40-(i*2);
		fgg.wireArray[lastwire].xs[3] = 16+(5*i)+10;
		fgg.wireArray[lastwire].ys[3] = 50;
		
		fgg.gateArray[sectionStart+i+8].outputids[0] = adderStart+i+8;
		fgg.gateArray[adderStart+i+8].inputids[0] = sectionStart+i+8;
		lastwire = gategraph_addWireToGraph(&fgg, 4,sectionStart+i+8,-1);
		fgg.wireArray[lastwire].xs[0] = 336+(5*i);
		fgg.wireArray[lastwire].ys[0] = 490;
		fgg.wireArray[lastwire].xs[1] = 336+(5*i);
		fgg.wireArray[lastwire].ys[1] = 550+(i*2);
		fgg.wireArray[lastwire].xs[2] = 410+(5*i);
		fgg.wireArray[lastwire].ys[2] = 550+(i*2);
		fgg.wireArray[lastwire].xs[3] = 410+(5*i);
		fgg.wireArray[lastwire].ys[3] = 290;
	}
	gategraph_addGateToList(&fgg.inputGatesList, adderStart+23,0);
	//fgg.gateArray[clock].inputStates[0] = 1;
	//gategraph_updateGraph(&fgg, 10000);
	//fgg.gateArray[clock].inputStates[0] = 0;
	fgg.gateArray[adderStart+23].inputStates[0] = 1;
	
	//gategraph_updateGraph(&fgg, 10000);
	
	//fgg.gateArray[clock].inputStates[0] = 1;
	gategraph_updateGraph(&fgg, 10000);
	
	char imgFileName[32];
	
	int numberUpdated = 0;
	
	for(int i = 0; i < 256; i++)
	{
		fgg.gateArray[clock].inputStates[0] = 1;
		gategraph_updateGraph(&fgg, 10000);
		sprintf(imgFileName, "frames/frameT%04d", numberUpdated);
		gategraph_drawGraph(1000,600, imgFileName, &fgg);
		numberUpdated++;
		fgg.gateArray[clock].inputStates[0] = 0;
		gategraph_updateGraph(&fgg, 10000);
		sprintf(imgFileName, "frames/frameT%04d", numberUpdated);
		gategraph_drawGraph(1000,600, imgFileName, &fgg);
		numberUpdated++;
	}
	
	gategraph_drawGraph(1000,600, "image1", &fgg);
	
	
	return 0;
}
