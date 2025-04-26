#ifndef GATEGRAPH_H
#define GATEGRAPH_H

#include <stdlib.h>
#include <string.h>
#include "gateimgs.h"
#include "binpypng.h"

#define GATEGRAPH_NUMBER_OF_GATES 2048

struct gategraph_gate_s
{
	char type;
	int id;
	int x;
	int y;
	int r;
	int parent;
	int numberOfInputs;
	int* inputids;
	int* outputids;
	int numberOfOutputs;
	int* inputStates;
	int outputState;
};

struct gategraph_wire_s
{
	int points;
	int parent;
	int* xs;
	int* ys;
	int inputid;
};

struct gategraph_fullGraph_s
{
	int numberOfGates;
	struct gategraph_gate_s* gateArray;
	int numberOfWires;
	struct gategraph_wire_s* wireArray;
	struct gategraph_gateListNode_s* inputGatesList;
	struct gategraph_gateListNode_s* outputGatesList;
	struct gategraph_gateListNode_s* updateList;
};


struct gategraph_gateListNode_s
{
	struct gategraph_gateListNode_s* previous;
	int gateId;
	struct gategraph_gateListNode_s* next;
};

void gategraph_initFullGraph(struct gategraph_fullGraph_s* fgg);
void gategraph_deconstructFullGraph(struct gategraph_fullGraph_s* fgg);//imp
struct gategraph_gate_s* gategraph_createGate(char type, int x, int y, int r, int parent, int numberOfInputs, int numberOfOutputs);
void gategraph_deconstructGate(struct gategraph_gate_s* g);//imp
void gategraph_addGateToGraph(struct gategraph_fullGraph_s* fgg, char type, int x, int y, int r, int parent, int numberOfInputs, int numberOfOutputs);
int gategraph_addWireToGraph(struct gategraph_fullGraph_s* fgg, int numberOfPoints, int inputid, int parent);
void gategraph_addGateToList(struct gategraph_gateListNode_s** list, int gateID, int noRepeat);
void gategraph_clearList(struct gategraph_gateListNode_s** list);//imp
void gategraph_printList(struct gategraph_gateListNode_s** list);
void gategraph_updateGate(struct gategraph_gate_s* g);
void gategraph_addGateToUpdateQue(struct gategraph_fullGraph_s* fgg, int gateID, int noRepeat);
void gategraph_updateGraph(struct gategraph_fullGraph_s* fgg, int updateLimit);
char* gategraph_printGate(struct gategraph_gate_s* g);
char* gategraph_printFullGraph(struct gategraph_fullGraph_s* fgg);

//drawing stuff
int gategraph_drawGraph(int w, int H, char* filename, struct gategraph_fullGraph_s* fgg);

#endif
