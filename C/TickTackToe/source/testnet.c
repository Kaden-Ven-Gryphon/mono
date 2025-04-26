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
	struct nnet_nnet_s nn;
	char input[16];

	nnet_initNull(&nn);
	nnet_load(&nn, "nnTest.txt");
	nnet_updateNodes(&nn);
	nnet_print_debug(&nn);

	while(1)
	{
		//CLEAR;
		ticktack_initGame(&ttg);


		while(ttg.winner == -1)
		{
			if(ttg.turn % 2 == 0)
			{
				ticktackutil_printFullBoard(&ttg);
				for(int i = 0; i < 3; i++)
				{
					for(int j = 0; j < 3; j++)
					{
						//printf("%d %d\n", i, j);
						if(ttg.board[i][j] == 'X')
						{
							//printf("FOUND X %d %d\n", i, j);
							nn.layers[0][i+((2-j)*3)] = -1.0;
						}
						else if(ttg.board[i][j] == 'O')
						{
							//printf("FOUND O %d %d\n", i, j);
							nn.layers[0][i+((2-j)*3)] = 1.0;
						}
						else
						{
							//printf("FOUND NOTHING %d %d\n", i, j);
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

				ticktackutil_printFullBoard(&ttg);
				printf("Enter 1-9 for tile:> ");
				fgets(input, 16, stdin);
				int userSelection = -1;
				sscanf(input, " %d ", &userSelection);
				userSelection--;
				ticktack_playTurn(&ttg, userSelection);

			}
		}
		ticktackutil_printFullBoard(&ttg);
	}
	return 0;
}
