#ifndef HANOI_H
#define HANOI_H

#include <stdlib.h>
#include <string.h>

struct hanoi_game_s
{
	int* disks;
	int numberOfDisks;
	int numberOfMoves;
	char* boardString;
};


void hanoi_init(struct hanoi_game_s* hg, int n);
void hanoi_render(struct hanoi_game_s* hg);
void hanoi_rSolution(struct hanoi_game_s* hg, int n, int source, int destination, int helper);

#endif
