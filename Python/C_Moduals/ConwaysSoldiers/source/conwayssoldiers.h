#ifndef CONWAYSSOLDIERS_H
#define CONWAYSSOLDIERS_H

#include <string.h>


#define CONWAYSSOLDIERS_ERROR_EMPTY_START_POS -1
#define CONWAYSSOLDIERS_ERROR_OUTOFBOUNDS_END_POS -2
#define CONWAYSSOLDIERS_ERROR_OUTOFBOUNDS_START_POS -3
#define CONWAYSSOLDIERS_ERROR_OCUPIED_DESTINATION -4
#define CONWAYSSOLDIERS_ERROR_EMPTY_JUMP -5
#define CONWAYSSOLDIERS_ERROR_INVALID_DIRECTION -6


struct conwayssoldiers_game_s
{
	char board[20][10];
	int numberOfMoves;
	char boardString[1024];
};

extern void conwayssoldiers_initBoard(struct conwayssoldiers_game_s* cg, char c);
extern void conwayssoldiers_renderCompactBoard(struct conwayssoldiers_game_s* cg);
extern void conwayssoldiers_renderFullBoard(struct conwayssoldiers_game_s* cg);
extern int conwayssoldiers_moveSoldier(int i, int j, char direction, struct conwayssoldiers_game_s* cg);


#endif
