#include "hanoi.h"

#define _DEBUG_MESSAGES
#ifdef _DEBUG_MESSAGES
	#include <stdio.h>
	#define DEBUG_LOG printf
#else
	#define DEBUG_LOG(...) {}
#endif

void hanoi_init(struct hanoi_game_s* hg, int n)
{
	hg->numberOfDisks = n;
	hg->numberOfMoves = n;
	hg->disks = (int *) malloc(hg->numberOfDisks * sizeof(int));
	for(int i = 0; i < n; i++)
	{
		hg->disks[i] = 1;
	}
	hg->boardString = (char *) malloc( (((2*n) + 3) * 3 * (n+4) ) * sizeof(char));
	hg->boardString[0] = '\0';
	return;
}

void hanoi_render(struct hanoi_game_s* hg)
{
	int width = (hg->numberOfDisks*2)+3;
	int counts[3];
	for(int i = 0; i < 3; i++) counts[i] = 0;
	for(int i = 0; i < hg->numberOfDisks; i++)
	{
		if(hg->disks[i] <= 3 && hg->disks[i] >= 1) counts[hg->disks[i]-1]++;
	}
	
	//reset the string
	hg->boardString[0] = '\0';
	
	//draw the first layer with poles
	//strcat(hg->boardString, "1");
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < width/2; j++)
		{
			strcat(hg->boardString, " ");
		}
		strcat(hg->boardString, "|");
		for(int j = 0; j < width/2; j++)
		{
			strcat(hg->boardString, " ");
		}
	}
	strcat(hg->boardString, "\n");
	
	
	for(int height = hg->numberOfDisks; height>0; height--)
	{
		for(int i = 0; i < 3; i++)
		{
			if(counts[i] < height)
			{
				for(int j = 0; j < width/2; j++)
				{
					strcat(hg->boardString, " ");
				}
				strcat(hg->boardString, "|");
				for(int j = 0; j < width/2; j++)
				{
					strcat(hg->boardString, " ");
				}
			}
			else
			{
				int disk = 0;
				int foundCounter = 0;
				for(int j = hg->numberOfDisks-1; j >= 0; j--)
				{
					if(hg->disks[j] == i+1) foundCounter++;
					if(foundCounter == height)
					{
						disk = j;
						break;
					}
				}
				
				for(int j = 0; j < width/2 - (disk+1); j++)
				{
					strcat(hg->boardString, " ");
				}
				for(int j = 0; j < disk+1; j++)
				{
					strcat(hg->boardString, "#");
				}
				strcat(hg->boardString, "|");
				for(int j = 0; j < disk+1; j++)
				{
					strcat(hg->boardString, "#");
				}
				for(int j = 0; j < width/2 - (disk+1); j++)
				{
					strcat(hg->boardString, " ");
				}
				
				counts[i]--;
			}
		}
		strcat(hg->boardString, "\n");
	}
	
	
	//draw devieder line
	//strcat(hg->boardString, "2");
	for(int i = 0; i < width*3; i++)
	{
		strcat(hg->boardString, "-");
	}
	strcat(hg->boardString, "\n");
	
	//draw tower labels
	//strcat(hg->boardString, "3");
	strcat(hg->boardString, " Tower 1");
	for(int i = 0; i < width-8; i++)
	{
		strcat(hg->boardString, " ");
	}
	strcat(hg->boardString, " Tower 2");
	for(int i = 0; i < width-8; i++)
	{
		strcat(hg->boardString, " ");
	}
	strcat(hg->boardString, " Tower 3");
	for(int i = 0; i < width-8; i++)
	{
		strcat(hg->boardString, " ");
	}
	strcat(hg->boardString, "\n");
	return;
}


void hanoi_rSolution(struct hanoi_game_s* hg, int n, int source, int destination, int helper)
{

	if(n == 1)	//base case
	{
		for(int i = 0; i < hg->numberOfDisks; i++)
		{
			if(hg->disks[i] == source)
			{
				hg->disks[i] = destination;
				hg->numberOfMoves++;
				break;
			}
		}
		hanoi_render(hg);
		DEBUG_LOG("Step %d:\n%s\n", hg->numberOfMoves, hg->boardString);
	}
	else
	{
		hanoi_rSolution(hg, n-1, source, helper, destination);
		
		for(int i = 0; i < hg->numberOfDisks; i++)
		{
			if(hg->disks[i] == source)
			{
				hg->disks[i] = destination;
				hg->numberOfMoves++;
				break;
			}
		}
		hanoi_render(hg);
		DEBUG_LOG("Step %d:\n%s\n", hg->numberOfMoves, hg->boardString);
		
		hanoi_rSolution(hg, n-1, helper, destination, source);
	}
}




