#include "gategraph.h"

//#define _DEBUG_MESSAGES
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




void gategraph_initFullGraph(struct gategraph_fullGraph_s* fgg)
{
	fgg->numberOfGates = 0;
	fgg->numberOfWires = 0;
	fgg->gateArray = (struct gategraph_gate_s*) malloc(sizeof(struct gategraph_gate_s)*GATEGRAPH_NUMBER_OF_GATES);
	fgg->wireArray = (struct gategraph_wire_s*) malloc(sizeof(struct gategraph_wire_s)*GATEGRAPH_NUMBER_OF_GATES);
	fgg->inputGatesList = NULL;
	fgg->outputGatesList = NULL;
	fgg->updateList = NULL;
}


struct gategraph_gate_s* gategraph_createGate(char type, int x, int y, int r, int parent, int numberOfInputs, int numberOfOutputs)
{
	struct gategraph_gate_s* newGate = (struct gategraph_gate_s*) malloc(sizeof(struct gategraph_gate_s));
	newGate->type = type;
	newGate->x = x;
	newGate->y = y;
	newGate->r = r;
	newGate->parent = parent;
	newGate->numberOfInputs = numberOfInputs;
	newGate->inputids = (int*) malloc(sizeof(int)*numberOfInputs);
	newGate->inputStates = (int*) malloc(sizeof(int)*numberOfInputs);
	for(int i = 0; i < numberOfInputs; i++)
	{
		newGate->inputids[i] = 0;
		newGate->inputStates[i] = 0;
	}
	newGate->numberOfOutputs = numberOfOutputs;
	newGate->outputids = (int*) malloc(sizeof(int)*numberOfOutputs);
	for(int i = 0; i < numberOfOutputs; i++)
	{
		newGate->outputids[i] = 0;
	}
	return newGate;
}

void gategraph_addGateToGraph(struct gategraph_fullGraph_s* fgg, char type, int x, int y, int r, int parent, int numberOfInputs, int numberOfOutputs)
{
	fgg->gateArray[fgg->numberOfGates].type = type;
	fgg->gateArray[fgg->numberOfGates].id = fgg->numberOfGates;
	fgg->gateArray[fgg->numberOfGates].x = x;
	fgg->gateArray[fgg->numberOfGates].y = y;
	fgg->gateArray[fgg->numberOfGates].r = r;
	fgg->gateArray[fgg->numberOfGates].parent = parent;
	fgg->gateArray[fgg->numberOfGates].numberOfInputs = numberOfInputs;
	fgg->gateArray[fgg->numberOfGates].inputids = (int*) malloc(sizeof(int)*numberOfInputs);
	fgg->gateArray[fgg->numberOfGates].inputStates = (int*) malloc(sizeof(int)*numberOfInputs);
	for(int i = 0; i < numberOfInputs; i++)
	{
		fgg->gateArray[fgg->numberOfGates].inputids[i] = 0;
		fgg->gateArray[fgg->numberOfGates].inputStates[i] = 0;
	}
	fgg->gateArray[fgg->numberOfGates].numberOfOutputs = numberOfOutputs;
	fgg->gateArray[fgg->numberOfGates].outputids = (int*) malloc(sizeof(int)*numberOfOutputs);
	for(int i = 0; i < numberOfOutputs; i++)
	{
		fgg->gateArray[fgg->numberOfGates].outputids[i] = 0;
	}
	fgg->numberOfGates++;
}

int gategraph_addWireToGraph(struct gategraph_fullGraph_s* fgg, int numberOfPoints, int inputid, int parent)
{
	fgg->wireArray[fgg->numberOfWires].inputid = inputid;
	fgg->wireArray[fgg->numberOfWires].points = numberOfPoints;
	fgg->wireArray[fgg->numberOfWires].parent = parent;
	fgg->wireArray[fgg->numberOfWires].xs = (int*) malloc(sizeof(int)*numberOfPoints);
	fgg->wireArray[fgg->numberOfWires].ys = (int*) malloc(sizeof(int)*numberOfPoints);
	for(int i = 0; i < numberOfPoints; i++)
	{
		//DEBUG_LOG("init zeros for wire\n");
		fgg->wireArray[fgg->numberOfWires].xs[i] = 0;
		fgg->wireArray[fgg->numberOfWires].ys[i] = 0;
	}
	fgg->numberOfWires++;
	return fgg->numberOfWires-1;
}

void gategraph_addGateToList(struct gategraph_gateListNode_s** list, int gateID, int noRepeat)
{
	//DEBUG_LOG("DEBUG: start of addgateToList\n");
	struct gategraph_gateListNode_s* newNode = (struct gategraph_gateListNode_s*) malloc(sizeof(struct gategraph_gateListNode_s));
	newNode->previous = NULL;
	newNode-> gateId = gateID;
	newNode-> next = NULL;
	struct gategraph_gateListNode_s* target = *list;
	struct gategraph_gateListNode_s* previousTarget = *list;
	if(target == NULL)
	{
		*list = newNode;
		//DEBUG_LOG("DEBUG: end of new list in addgateToList\n");
	}
	else
	{
		while(target != NULL)
		{
			if(target->gateId == gateID && noRepeat == 1)
			{
				free(newNode);
				return;
			}
			//DEBUG_LOG("DEBUG: start of add to exitsing addgateToList\n");
			previousTarget = target;
			target = target->next;
		}
		newNode->previous = previousTarget;
		previousTarget->next = newNode;
	}
	//DEBUG_LOG("DEBUG: end of addgateToList\n");
}

void gategraph_printList(struct gategraph_gateListNode_s** list)
{
	DEBUG_LOG("PRINT LIST\n");
	struct gategraph_gateListNode_s* iter = *list;
	while(iter != NULL)
	{
		DEBUG_LOG("NODE: %d\n", iter->gateId);
		iter = iter->next;
	}
	DEBUG_LOG("END PRINT LIST\n");
	return;
}

void gategraph_updateGate(struct gategraph_gate_s* g)
{
	//DEBUG_LOG("DEBUG: start of updateing gate\n");
	switch(g->type)
	{
	case 'n':
		g->outputState = 1;
		for(int i = 0; i < g->numberOfInputs; i++)
		{
			if(g->inputStates[i] == 0){ g->outputState = 0;}
		}
		if(g->outputState) g->outputState = 0;
		else g->outputState = 1;
		break;
	case 'a':
		g->outputState = 1;
		for(int i = 0; i < g->numberOfInputs; i++)
		{
			if(g->inputStates[i] == 0){ g->outputState = 0; break;}
		}
		break;
	case 'o':
		g->outputState = 0;
		for(int i = 0; i < g->numberOfInputs; i++)
		{
			if(g->inputStates[i]){ g->outputState = 1; break;}
		}
		break;
	case 'p':
		g->outputState = 0;
		for(int i = 0; i < g->numberOfInputs; i++)
		{
			if(g->inputStates[i]){ g->outputState = 1; break;}
		}
		break;
	case 'x':
		break;
	case 'i':
		break;
	default:
		break;
	}
}

void gategraph_addGateToUpdateQue(struct gategraph_fullGraph_s* fgg, int gateID, int noRepeat)
{
	if(fgg->gateArray[gateID].numberOfInputs == 1 && 1==0)
	{
		DEBUG_LOG("ONE INPUT for gate %d\n", gateID);
		gategraph_updateGate(&fgg->gateArray[gateID]);
		for(int i = 0; i < fgg->gateArray[gateID].numberOfOutputs; i++)
		{
			if(fgg->gateArray[gateID].outputids[i] != -1)
			{
				gategraph_addGateToUpdateQue(fgg, fgg->gateArray[gateID].outputids[i], noRepeat);
			}
		}
	}
	else
	{
		gategraph_addGateToList(&fgg->updateList, gateID, noRepeat);
	}
}

void gategraph_updateGraph(struct gategraph_fullGraph_s* fgg, int updateLimit)
{
	DEBUG_LOG("START UPDATE GRAPH\n");
	int numberUpdated = 0;
	struct gategraph_gateListNode_s* listPointer = fgg->inputGatesList;
	while(listPointer != NULL)
	{
		DEBUG_LOG("ADD INPUTS TO UPDATE LIST: %d\n", listPointer->gateId);
		gategraph_addGateToList(&fgg->updateList, listPointer->gateId, 1);
		listPointer = listPointer->next;
	}
	
	listPointer = fgg->updateList;
	while(listPointer != NULL && numberUpdated < updateLimit)
	{
		char imgFileName[32];
		sprintf(imgFileName, "frames/frameT%04d", numberUpdated);
		//gategraph_drawGraph(300,100, imgFileName, fgg);
		DEBUG_LOG("UPDATE GATE START\n");
		gategraph_updateGate(&fgg->gateArray[listPointer->gateId]);
		for(int i = 0; i < fgg->gateArray[listPointer->gateId].numberOfOutputs; i++)
		{
			int targetGate = fgg->gateArray[listPointer->gateId].outputids[i];
			if(targetGate >= 0 && targetGate < fgg->numberOfGates)
			{
			
			
				for(int j = 0; j < fgg->gateArray[targetGate].numberOfInputs; j++)
				{
					if(fgg->gateArray[targetGate].inputids[j] == listPointer->gateId)
					{
						DEBUG_LOG("FOUND MATCH from: %d to: %d\n", listPointer->gateId, targetGate);
						fgg->gateArray[targetGate].inputStates[j] = fgg->gateArray[listPointer->gateId].outputState;
						gategraph_addGateToUpdateQue(fgg, targetGate, 0);
					}
				}
			
				
			}
		}
		//add new gates to list
		
		listPointer = listPointer->next;
		numberUpdated++;
		if(numberUpdated == updateLimit) {DEBUG_LOG("UPDATE LIMIT REACHED\n");}
	}
	
	//free the update list to stop mem leak
	listPointer = fgg->updateList;
	struct gategraph_gateListNode_s* lastPointer;
	while(listPointer != NULL)
	{
		lastPointer = listPointer;
		listPointer = listPointer->next;
		free(lastPointer);
	}
	fgg->updateList = NULL;
}


char* gategraph_printGate(struct gategraph_gate_s* g)
{
	DEBUG_LOG("Gate ID: %d\tGate Type: %c\n", g->id, g->type);
	DEBUG_LOG("Parent: %d\tx: %d\ty:%d\n", g->parent, g->x, g->y);
	DEBUG_LOG("Number Of Inputs: %d\n", g->numberOfInputs);
	for(int i = 0; i < g->numberOfInputs; i++)
	{
		DEBUG_LOG("Input ID: %d\tValue: %d\n", g->inputids[i], g->inputStates[i]);
	}
	DEBUG_LOG("OUTPUT: %d\n", g->outputState);
	for(int i = 0; i < g->numberOfOutputs; i++)
	{
		DEBUG_LOG("Output ID: %d\n", g->outputids[i]);
	}
	return NULL;
}


char* gategraph_printFullGraph(struct gategraph_fullGraph_s* fgg)
{
	struct gategraph_gateListNode_s* listPointer = fgg->inputGatesList;
	DEBUG_LOG("\n\n--PRINT GRAPH--\n\n");
	DEBUG_LOG("-INPUT LIST-\n");
	while(listPointer != NULL)
	{
		DEBUG_LOG("%d\n", listPointer->gateId);
		listPointer = listPointer->next;
	}
	for(int i = 0; i < fgg->numberOfGates; i++)
	{
		gategraph_printGate(&fgg->gateArray[i]);
		DEBUG_LOG("\n");
	}
	return NULL;
}




int gategraph_drawGraph(int w, int h, char* filename, struct gategraph_fullGraph_s* fgg)
{
	DEBUG_LOG("DEBUG: start of drawing gate\n");
	//init gate shapes and colors
	struct binimg_image_s* andOff = gateimgs_initAndOff();
	struct binimg_image_s* andOn = gateimgs_initAndOn();
	struct binimg_image_s* orOff = gateimgs_initOrOff();
	struct binimg_image_s* orOn = gateimgs_initOrOn();
	struct binimg_image_s* notOff = gateimgs_initNotOff();
	struct binimg_image_s* notOn = gateimgs_initNotOn();
	struct pixel_s black = {0,0,0,255};
	struct pixel_s gray = {20,20,20,255};
	struct pixel_s cWireOn = GATE_COLOR_WIRE_ON;
	struct pixel_s cWireOff = GATE_COLOR_WIRE_OFF;
	
	//init gate image
	struct binimg_image_s gateimg;
	binimg_initImage(w,h,black,&gateimg);
	for(int i = 0; i < gateimg.width; i++)
	{
		for(int j = 0; j < gateimg.hight; j++)
		{
			if(i%2 == 0)
			{
				if(j%2 == 0)
				{
					gateimg.rawimg[i][j] = gray;
				}
			}
		}
	}
	
	//draw wires
	DEBUG_LOG("DEBUG: draw off wires\n");
	for(int i = 0; i < fgg->numberOfWires; i++)
	{
		for(int j = 1; j < fgg->wireArray[i].points; j++)
		{
			if(fgg->gateArray[fgg->wireArray[i].inputid].outputState == 0)
			{
				DEBUG_LOG("DEBUG: draw wire off\n");
				binimg_drawLine(fgg->wireArray[i].xs[j-1],fgg->wireArray[i].ys[j-1],fgg->wireArray[i].xs[j],fgg->wireArray[i].ys[j],1,1,cWireOff,&gateimg);
				//binimg_drawCircle(fgg->wireArray[i].xs[j],fgg->wireArray[i].ys[j],2,1,cWireOff,&gateimg);
			}
		}
	}
	DEBUG_LOG("DEBUG: draw  on wires\n");
	for(int i = 0; i < fgg->numberOfWires; i++)
	{
		for(int j = 1; j < fgg->wireArray[i].points; j++)
		{
			if(fgg->gateArray[fgg->wireArray[i].inputid].outputState == 1)
			{	
				DEBUG_LOG("DEBUG: draw wire on\n");
				binimg_drawLine(fgg->wireArray[i].xs[j-1],fgg->wireArray[i].ys[j-1],fgg->wireArray[i].xs[j],fgg->wireArray[i].ys[j],1,1,cWireOn,&gateimg);
				//binimg_drawCircle(fgg->wireArray[i].xs[j],fgg->wireArray[i].ys[j],2,1,cWireOn,&gateimg);
			}
		}
	}
	
	
	DEBUG_LOG("DEBUG: draw gates\n");
	for(int i = 0; i < fgg->numberOfGates; i++)
	{
		switch (fgg->gateArray[i].type)
		{
			case 'i':
				if(fgg->gateArray[i].outputState == 0)
				{
					binimg_drawCircle(fgg->gateArray[i].x+7,fgg->gateArray[i].y+7,6,1,cWireOff,&gateimg);
				}
				else
				{
					binimg_drawCircle(fgg->gateArray[i].x+7,fgg->gateArray[i].y+7,6,1,cWireOn,&gateimg);
				}
				break;
			case 'n':
				if(fgg->gateArray[i].outputState == 0)
				{
					binimg_insertImage(fgg->gateArray[i].x,fgg->gateArray[i].y,fgg->gateArray[i].r,notOn,&gateimg);
				}
				else
				{
					binimg_insertImage(fgg->gateArray[i].x,fgg->gateArray[i].y,fgg->gateArray[i].r,notOff,&gateimg);
				}
				break;
			case 'a':
				if(fgg->gateArray[i].outputState == 0)
				{
					binimg_insertImage(fgg->gateArray[i].x,fgg->gateArray[i].y,fgg->gateArray[i].r,andOff,&gateimg);
				}
				else
				{
					binimg_insertImage(fgg->gateArray[i].x,fgg->gateArray[i].y,fgg->gateArray[i].r,andOn,&gateimg);
				}
				break;
			case 'o':
				if(fgg->gateArray[i].outputState == 0)
				{
					binimg_insertImage(fgg->gateArray[i].x,fgg->gateArray[i].y,fgg->gateArray[i].r,orOff,&gateimg);
				}
				else
				{
					binimg_insertImage(fgg->gateArray[i].x,fgg->gateArray[i].y,fgg->gateArray[i].r,orOn,&gateimg);
				}
				break;
			case 'p':
				if(fgg->gateArray[i].outputState == 0)
				{
					binimg_drawCircle(fgg->gateArray[i].x,fgg->gateArray[i].y,2,1,cWireOff,&gateimg);
				}
				else
				{
					binimg_drawCircle(fgg->gateArray[i].x,fgg->gateArray[i].y,2,1,cWireOn,&gateimg);
				}
				break;
		}
	}
	
	
	DEBUG_LOG("DEBUG: save image\n");
	//save image
	binpypng_writebin(filename, &gateimg);
	binpypng_convert(filename);
	
	DEBUG_LOG("DEBUG: end of draw gates\n");
	return 0;
}
