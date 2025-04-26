#include "nnet.h"

//debuging: comment out line bellow to turn off debuging
#define _DEBUG_MESSAGES
#ifdef _DEBUG_MESSAGES
        #include <stdio.h>
        #define DEBUG_LOG printf
#else
        #define DEBUG_LOG(...) {}
#endif


#define PI 3.14159265

//This takes a nnet struct pointer and allicates mem for the nodes and weights
//This does NOT set the weigths or nodes to zero
//This memory that get allicated will need to be freed
int nnet_init(struct nnet_nnet_s* nn, int inputLayer, int outputLayer, int numHiddenLayers, int hiddenLayerNodes)
{
	//the total number of layers
	nn->numberOfLayers = numHiddenLayers+2;
	//set up the array of layer lengths
	nn->numberOfNodes = (int *) malloc(nn->numberOfLayers * sizeof(int));
	//set up the pointer for the 2d nodes
	nn->layers = (float **) malloc(nn->numberOfLayers * sizeof(float*));
	//set up the input layer nodes +1 for bias
	nn->layers[0] = (float *) malloc((inputLayer+1) * sizeof(float));
	nn->numberOfNodes[0] = inputLayer+1;
	//set up the hidden layer nodes
	for(int i = 1; i <= numHiddenLayers; i++)
	{
		nn->layers[i] = (float *) malloc((hiddenLayerNodes+1) * sizeof(float));
		nn->numberOfNodes[i] = hiddenLayerNodes+1;
	}
	//set up the output layer nodes
	nn->layers[numHiddenLayers+1] = (float *) malloc((outputLayer+1) * sizeof(float));
	nn->numberOfNodes[numHiddenLayers+1] = outputLayer+1;

	//set up the weights
	nn->weights = (float **) malloc(nn->numberOfLayers-1);
	for(int i = 0; i < nn->numberOfLayers-1; i++)
	{
		nn->weights[i] = (float *) malloc( (nn->numberOfNodes[i]*( nn->numberOfNodes[i+1] -1)) * sizeof(float) );
	}

	//set the bias nodes to 1
	for(int i = 0; i < nn->numberOfLayers; i++)
	{
		nn->layers[i][nn->numberOfNodes[i]-1] = 1.0;
	}

	nn->score = 0;
	return 0;
}

int nnet_initNull(struct nnet_nnet_s* nn)
{
	nn->layers = NULL;
	nn->numberOfLayers = 0;
	nn->numberOfNodes = NULL;
	nn->weights = NULL;
	nn->score = 0;
	return 0;
}

int nnet_free(struct nnet_nnet_s* nn)
{
	DEBUG_LOG("Start free\n");
	if(nn->weights != NULL)
	{
		for(int i = 0; i < nn->numberOfLayers-1; i++)
		{
			free(nn->weights[i]);
		}
		free(nn->weights);
		nn->weights=NULL;
	}
	DEBUG_LOG("weights freed\n");
	free(nn->numberOfNodes);
	if(nn->layers != NULL)
	{
		for(int i = 0; i < nn->numberOfLayers-1; i++)
		{
			free(nn->layers[i]);
		}
		free(nn->layers);
		nn->layers=NULL;
	}
	DEBUG_LOG("layers freed\n");
	return 0;
}

int nnet_randomWeights(struct nnet_nnet_s* nn)
{
	srand(time(NULL));
	for(int i = 0; i < nn->numberOfLayers-1; i++)
	{
		for(int j = 0; j < (nn->numberOfNodes[i] * (nn->numberOfNodes[i+1]-1)); j++)
		{
			nn->weights[i][j] = ((float)rand()-((float)RAND_MAX)/2) / (float)RAND_MAX;
			//DEBUG_LOG("layer: %d weight: %d %f\n", i, j, nn->weights[i][j]);
		}
	}
	return 0;
}

int nnet_updateNodes(struct nnet_nnet_s* nn)
{
	for(int i = 1; i < nn->numberOfLayers; i++)
	{
		for(int j = 0; j < nn->numberOfNodes[i]-1; j++)
		{
			nn->layers[i][j] = 0;
			for(int k = j; k < (nn->numberOfNodes[i-1] * (nn->numberOfNodes[i]-1)); k+=nn->numberOfNodes[i]-1)
			{
				nn->layers[i][j] += nn->weights[i-1][k] * nn->layers[i-1][(k/(nn->numberOfNodes[i]-1))];
			}
			nn->layers[i][j] = atan(nn->layers[i][j]) / (PI/2);
			//DEBUG_LOG("layer: %d node: %d %f\n", i, j, nn->layers[i][j]);
		}
	}
	return 0;
}

//agusts a weight by a small amount
int nnet_mutate_tune(struct nnet_nnet_s* nn)
{
	srand(time(NULL));
	int i = rand()%(nn->numberOfLayers-1);
	int j = rand()%(nn->numberOfNodes[i]*(nn->numberOfNodes[i+1]-1));
	float delta = ((float)rand()-((float)RAND_MAX)/2) / (float)RAND_MAX;
	delta /= 5;
	nn->weights[i][j]+=delta;
	nn->weights[i][j]= atan(nn->weights[i][j]) / (PI/4);
	return 0;
}

//multiplies a weight by -1
int nnet_mutate_flip(struct nnet_nnet_s* nn)
{
	srand(time(NULL));
	int i = rand()%(nn->numberOfLayers-1);
	int j = rand()%(nn->numberOfNodes[i]*(nn->numberOfNodes[i+1]-1));
	nn->weights[i][j]*=-1;
	return 0;
}

//swaps the weights of two weights
int nnet_mutate_swap(struct nnet_nnet_s* nn)
{
		srand(time(NULL));
	int i = rand()%(nn->numberOfLayers-1);
	int j = rand()%(nn->numberOfNodes[i]*(nn->numberOfNodes[i+1]-1));
	int k = rand()%(nn->numberOfLayers-1);
	int l = rand()%(nn->numberOfNodes[i]*(nn->numberOfNodes[i+1]-1));
	float buf = nn->weights[i][j];
	nn->weights[i][j] = nn->weights[k][l];
	nn->weights[k][l] = buf;
	return 0;
}

//sets a random weight to a random value
int nnet_mutate_random(struct nnet_nnet_s* nn)
{
	srand(time(NULL));
	int i = rand()%(nn->numberOfLayers-1);
	int j = rand()%(nn->numberOfNodes[i]*(nn->numberOfNodes[i+1]-1));
	float delta = ((float)rand()-((float)RAND_MAX)/2) / (float)RAND_MAX;
	nn->weights[i][j]=delta;
	return 0;
}

//write nnet to file
int nnet_save(struct nnet_nnet_s* nn, char* fileName)
{
	FILE *fp;
	fp = fopen(fileName, "w");
	fprintf(fp, "#number of layers\n%d\n", nn->numberOfLayers);
	fprintf(fp, "#number of nodes for each layer\n");
	for(int i = 0; i < nn->numberOfLayers; i++)
	{
		fprintf(fp, "%d\n", nn->numberOfNodes[i]-1);
	}
	fprintf(fp, "#weights\n");
	//Print the weights
	for(int i = 0; i < nn->numberOfLayers-1; i++)
	{
		fprintf(fp, "#weights layer %d\n", i);
		for(int j = 0; j < (nn->numberOfNodes[i] * (nn->numberOfNodes[i+1]-1)); j++)
		{
			fprintf(fp, "%f\n", nn->weights[i][j]);
		}
	}
	fprintf(fp, "#score\n%d\n", nn->score);
	fclose(fp);
	return 0;
}
int nnet_load(struct nnet_nnet_s* nn, char* fileName)
{
	FILE *fp;
	char buf[128];
	int numLayers = 0;
	int nodesIn = 0;
	int nodesOut = 0;
	int nodesHidden = 0;
	//free the memory of nn
	nnet_free(nn);
	fp = fopen(fileName, "r");
	while(fgets(buf, 128, fp) != NULL)
	{
		if(buf[0] == '#') continue;
		sscanf(buf, " %d ", &numLayers);
		break;
	}
	int counter = 0;
	while(fgets(buf, 128, fp) != NULL && counter < numLayers)
	{
		if(buf[0] == '#') continue;
		if(counter == 0) sscanf(buf, " %d ", &nodesIn);
		else if(counter == numLayers-1) sscanf(buf, " %d ", &nodesOut);
		else sscanf(buf, " %d ", &nodesHidden);
		counter++;
	}
	nnet_init(nn, nodesIn, nodesOut, numLayers-2, nodesHidden);
	for(int i = 0; i < numLayers-1; i++)
	{
		counter = 0;
		while(fgets(buf, 128, fp) != NULL && counter < (nn->numberOfNodes[i] * (nn->numberOfNodes[i+1]-1)))
		{
			if(buf[0] == '#') continue;
			sscanf(buf, " %f ", &nn->weights[i][counter]);
			counter++;
		}
	}
	while(fgets(buf, 128, fp) != NULL)
	{
		if(buf[0] == '#') continue;
		sscanf(buf, " %d ", &nn->score);
		break;
	}
	fclose(fp);
	return 0;
}


//print the nn debug
void nnet_print_debug(struct nnet_nnet_s* nn)
{
	for(int i = 0; i < nn->numberOfLayers; i++)
	{
		for(int j = 0; j < nn->numberOfNodes[i]; j++)
		{
			DEBUG_LOG("[%1.2f]\t", nn->layers[i][j]);
		}
		DEBUG_LOG("\n\n");
	}
}
