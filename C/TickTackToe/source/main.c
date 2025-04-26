#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "ticktack.h"
#include "ticktackutil.h"
#include "nnet.h"

#define CLEAR           printf("\e[1;1H\e[2J")

int main()
{
	struct ticktack_game_s ttg;
	struct nnet_nnet_s nn, nnLast;
	//char input[16];
	unsigned long long round = 0;
	unsigned long long xWins = 0;
	unsigned long long oWins = 0;
	unsigned long long draws = 0;
	int saveCounter = 0;
	int wonLast = 0;
	int lowestScore = 500;
	nnet_init(&nn, 9, 9, 2, 4);
	nnet_randomWeights(&nn);
	nnet_updateNodes(&nn);
	nnet_print_debug(&nn);
	nnLast = nn;
	srand(time(NULL));

	while(1)
	{
		//CLEAR;




		nn = nnLast;
		nn.score = 0;
		if(!wonLast)
		{
			float chance = (float)rand()/(float)RAND_MAX;
			if(chance < 0.4) nnet_mutate_tune(&nn);
			else if(chance < 0.7) nnet_mutate_random(&nn);
			else if(chance < 0.9) nnet_mutate_flip(&nn);
			else if(chance < 1.1) nnet_mutate_swap(&nn);
		}
		wonLast = 0;








		for(int f = 0; f < 100; f++)
		{
		ticktack_initGame(&ttg);

		while(ttg.winner == -1)
		{
			if(ttg.turn % 2 == 0)
			{
				 for(int i = 0; i < 3; i++)
                                {
                                        for(int j = 0; j < 3; j++)
                                        {
                                	        if(ttg.board[i][j] == 'X')
                                                {
                                                        nn.layers[0][i+((2-j)*3)] = -1.0;
                                                }
                                                else if(ttg.board[i][j] == 'O')
                                                {
                                                        nn.layers[0][i+((2-j)*3)] = 1.0;
                                                }
                                                else
                                                {
                                                        nn.layers[0][i+((2-j)*3)] = 0;
                                                }
                                        }
                                }
                                nnet_updateNodes(&nn);
                                //nnet_print_debug(&nn);
                                int foundTile = 0;
                                float max = -2;
                                int maxIndex = 0;
                                while(!foundTile)
                                {
                                        max = -99;
                                        maxIndex = 0;
                                        for(int i = 0; i < nn.numberOfNodes[nn.numberOfLayers-1]-1; i++)
                                        {
                                                if(nn.layers[nn.numberOfLayers-1][i] > max)
                                                {
                                                        max = nn.layers[nn.numberOfLayers-1][i];
                                                        maxIndex = i;
                                                }
                                        }
                                        //printf("%d\n", maxIndex);
                                        if(ticktack_playTurn(&ttg, maxIndex) == TICKTACK_ERROR_TILE_FULL)
                                        {
                                                nn.layers[nn.numberOfLayers-1][maxIndex] = -99;
                                                nn.score+=1;
                                        }
                                        else foundTile = 1;
                                }
			}
			else
			{
				int nxtMove = ticktack_bestMove(&ttg);
				if(nxtMove == TICKTACK_ERROR_CANT_FIND_MOVE)
				{
					ttg.winner = 2;
				}
				else if(ticktack_playTurn(&ttg, nxtMove) == TICKTACK_ERROR_TILE_FULL) break;

			}
		}
		nn.score-=ttg.turn*7;
		if(ttg.winner == 1)
		{
			xWins++;
			nn.score+=20;
		}
		if(ttg.winner == 2)
		{
			oWins++;
			nn.score-=60;
			wonLast = 1;
		}
		if(ttg.winner == 3)
		{
			draws++;
			nn.score-=30;
		}
		}
		if(nn.score <= lowestScore)
		{
			nnLast = nn;
			lowestScore = nn.score;
			nnet_save(&nn, "nn1.txt");
			saveCounter = 0;
			ticktackutil_printFullBoard(&ttg);
			printf("Round: %llu\n", round);
			printf("X Wins: %llu\n", xWins);
			printf("O Wins: %llu\n", oWins);
			printf("Draws: %llu\n", draws);
			printf("nn score: %d\n", lowestScore);
		}
		round++;
		xWins = 0;
		oWins = 0;
		draws = 0;
	}
	return 0;
}
