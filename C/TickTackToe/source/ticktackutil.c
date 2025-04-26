#include "ticktackutil.h"

//debuging: comment out line bellow to turn off debuging
#define _DEBUG_MESSAGES
#ifdef _DEBUG_MESSAGES
        #include <stdio.h>
        #define DEBUG_LOG printf
#else
        #define DEBUG_LOG(...) {}
#endif

#define CLEAR           printf("\e[1;1H\e[2J")
#define PEN_DEFAULT     printf("\033[0m")
#define PEN_RED         printf("\033[0;31m")
#define PEN_GREEN       printf("\033[0;32m")
#define PEN_BLUE        printf("\033[0;34m")
#define PEN_YELLOW      printf("\033[0;33m")

void ticktackutil_printFullBoard(struct ticktack_game_s* ttg)
{
	//CLEAR;
	PEN_DEFAULT;
	printf("   |   |\n");
	if(ttg->board[0][0] == 'X')
	{
		PEN_RED;
	}
	else PEN_BLUE;
	printf(" %c ", ttg->board[0][0]);
	PEN_DEFAULT;
	printf("|");
	if(ttg->board[1][0] == 'X')
	{
		PEN_RED;
	}
	else PEN_BLUE;
	printf(" %c ", ttg->board[1][0]);
	PEN_DEFAULT;
	printf("|");
	if(ttg->board[2][0] == 'X')
	{
		PEN_RED;
	}
	else PEN_BLUE;
	printf(" %c\n", ttg->board[2][0]);
	PEN_DEFAULT;
	printf("___|___|___\n");

	PEN_DEFAULT;
	printf("   |   |\n");
	if(ttg->board[0][1] == 'X')
	{
		PEN_RED;
	}
	else PEN_BLUE;
	printf(" %c ", ttg->board[0][1]);
	PEN_DEFAULT;
	printf("|");
	if(ttg->board[1][1] == 'X')
	{
		PEN_RED;
	}
	else PEN_BLUE;
	printf(" %c ", ttg->board[1][1]);
	PEN_DEFAULT;
	printf("|");
	if(ttg->board[2][1] == 'X')
	{
		PEN_RED;
	}
	else PEN_BLUE;
	printf(" %c\n", ttg->board[2][1]);
	PEN_DEFAULT;
	printf("___|___|___\n");

	PEN_DEFAULT;
	printf("   |   |\n");
	if(ttg->board[0][2] == 'X')
	{
		PEN_RED;
	}
	else PEN_BLUE;
	printf(" %c ", ttg->board[0][2]);
	PEN_DEFAULT;
	printf("|");
	if(ttg->board[1][2] == 'X')
	{
		PEN_RED;
	}
	else PEN_BLUE;
	printf(" %c ", ttg->board[1][2]);
	PEN_DEFAULT;
	printf("|");
	if(ttg->board[2][2] == 'X')
	{
		PEN_RED;
	}
	else PEN_BLUE;
	printf(" %c\n", ttg->board[2][2]);
	PEN_DEFAULT;
	printf("   |   |   \n");

	printf("\nIt is turn %d\n", ttg->turn);
	int buf = ttg->turn;
	buf -= 1;
	buf = buf %2;
	buf += 1;
	printf("It is player %d's turn\n", buf);
	printf("Winner: %d\n\n", ttg->winner);
}
