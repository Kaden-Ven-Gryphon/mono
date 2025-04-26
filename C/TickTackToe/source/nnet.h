#ifndef NNET_H
#define NNET_H
#include <stdlib.h>
#include <time.h>
#include <math.h>
struct nnet_nnet_s
{
	float** layers;
	int numberOfLayers;
	int* numberOfNodes;
	float** weights;
	int score;
};

int nnet_init(struct nnet_nnet_s* nn, int inputLayer, int outputLayer, int numHiddenLayers, int hiddenLayerNodes);
int nnet_initNull(struct nnet_nnet_s* nn);
int nnet_free(struct nnet_nnet_s* nn);
int nnet_randomWeights(struct nnet_nnet_s* nn);
int nnet_updateNodes(struct nnet_nnet_s* nn);
int nnet_mutate_tune(struct nnet_nnet_s* nn);
int nnet_mutate_flip(struct nnet_nnet_s* nn);
int nnet_mutate_swap(struct nnet_nnet_s* nn);
int nnet_mutate_random(struct nnet_nnet_s* nn);
int nnet_save(struct nnet_nnet_s* nn, char* fileName);
int nnet_load(struct nnet_nnet_s* nn, char* fileName);
void nnet_print_debug(struct nnet_nnet_s* nn);

#endif
