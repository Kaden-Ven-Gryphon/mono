#ifndef TICKTACK_H
#define TICKTACK_H

#include <stdlib.h>
#include <time.h>

#define TICKTACK_ERROR_TILE_FULL 101
#define TICKTACK_ERROR_CANT_FIND_MOVE -1

struct ticktack_game_s
{
	int winner;
	int turn;
	char board[3][3];
};


int ticktack_initGame(struct ticktack_game_s* ttg);
int ticktack_playTurn(struct ticktack_game_s* ttg, int tile);
int ticktack_bestMove(struct ticktack_game_s* ttg);

#endif
