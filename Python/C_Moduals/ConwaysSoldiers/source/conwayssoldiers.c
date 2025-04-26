#include "conwayssoldiers.h"

void conwayssoldiers_initBoard(struct conwayssoldiers_game_s* cg, char c)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cg->board[i][j] = c;
		}
		for (int j = 5; j < 10; j++)
		{
			cg->board[i][j] = ' ';
		}
	}
	cg->numberOfMoves = 0;
}

void conwayssoldiers_renderCompactBoard(struct conwayssoldiers_game_s* cg)
{
	cg->boardString[0] = '\0';
	strcat(cg->boardString, "__________________________________________\n");
	size_t cur_len = strlen(cg->boardString);
	for (int j = 9; j >= 0; j--)
	{
		cg->boardString[cur_len] = (char)(j + 48);
		cur_len += 1;
		cg->boardString[cur_len] = '|';
		cur_len += 1;
		for (int i = 0; i < 20; i++)
		{
			if (cg->board[i][j] != ' ') cg->boardString[cur_len] = cg->board[i][j];
			else cg->boardString[cur_len] = '_';
			cur_len += 1;
			cg->boardString[cur_len] =  '|';
			cur_len += 1;
		}
		cg->boardString[cur_len] = '\n';
		cur_len += 1;
	}
	cg->boardString[cur_len] = '\0';
	strcat(cg->boardString, "  A B C D E F G H I J K L M N O P Q R S T \n");
	return;
}

void conwayssoldiers_renderFullBoard(struct conwayssoldiers_game_s* cg)
{
	cg->boardString[0] = '\0';
	size_t cur_len = strlen(cg->boardString);
	for (int i = 0; i < 20; i++)
	{
		cg->boardString[cur_len] = (char)196;
		cur_len += 1;
		cg->boardString[cur_len] = (char)194;
		cur_len += 1;
	}
	cg->boardString[cur_len] = (char)196;
	cur_len += 1;
	cg->boardString[cur_len] = (char)191;
	cur_len += 1;
	cg->boardString[cur_len] = '\n';
	cur_len += 1;
	for (int j = 9; j >= 0; j--)
	{
		cg->boardString[cur_len] = (char)(j+48);
		cur_len += 1;
		cg->boardString[cur_len] = (char)179;
		cur_len += 1;
		for (int i = 0; i < 20; i++)
		{
			cg->boardString[cur_len] = cg->board[i][j];
			cur_len += 1;
			cg->boardString[cur_len] = (char)179;
			cur_len += 1;
		}
		cg->boardString[cur_len] = '\n';
		cur_len += 1;
			for (int i = 0; i < 20; i++)
		{
			cg->boardString[cur_len] = (char)196;
			cur_len += 1;
			cg->boardString[cur_len] = (char)197;
			cur_len += 1;
		}
		cg->boardString[cur_len] = (char)196;
		cur_len += 1;
		cg->boardString[cur_len] = (char)180;
		cur_len += 1;
		cg->boardString[cur_len] = '\n';
		cur_len += 1;
	}
	cg->boardString[cur_len] = ' ';
	cur_len += 1;
	for (int i = 0; i < 20; i++)
	{
		cg->boardString[cur_len] = (char)179;
		cur_len += 1;
		cg->boardString[cur_len] = (char)(i+65);
		cur_len += 1;
	}
	cg->boardString[cur_len] = (char)179;
	cur_len += 1;
	cg->boardString[cur_len] = '\n';
	cur_len += 1;
	cg->boardString[cur_len] = '\0';
	
	return;
}

int conwayssoldiers_moveSoldier(int i, int j, char direction, struct conwayssoldiers_game_s* cg)
{
	if (i < 0 || i>19 || j < 0 || j>9) return CONWAYSSOLDIERS_ERROR_OUTOFBOUNDS_START_POS;
	if (cg->board[i][j] == ' ') return CONWAYSSOLDIERS_ERROR_EMPTY_START_POS;
	switch (direction)
	{
	case 'u':
		if (j + 2 > 9) return CONWAYSSOLDIERS_ERROR_OUTOFBOUNDS_END_POS; //this is imposible
		if (cg->board[i][j + 1] == ' ') return CONWAYSSOLDIERS_ERROR_EMPTY_JUMP;
		if (cg->board[i][j + 2] != ' ') return CONWAYSSOLDIERS_ERROR_OCUPIED_DESTINATION;
		cg->board[i][j + 2] = cg->board[i][j];
		cg->board[i][j] = ' ';
		cg->board[i][j + 1] = ' ';
		cg->numberOfMoves++;
		break;
	case 'd':
		if (j - 2 < 0) return CONWAYSSOLDIERS_ERROR_OUTOFBOUNDS_END_POS;
		if (cg->board[i][j - 1] == ' ') return CONWAYSSOLDIERS_ERROR_EMPTY_JUMP;
		if (cg->board[i][j - 2] != ' ') return CONWAYSSOLDIERS_ERROR_OCUPIED_DESTINATION;
		cg->board[i][j - 2] = cg->board[i][j];
		cg->board[i][j] = ' ';
		cg->board[i][j - 1] = ' ';
		cg->numberOfMoves++;
		break;
	case 'l':
		if (i - 2 < 0) return CONWAYSSOLDIERS_ERROR_OUTOFBOUNDS_END_POS;
		if (cg->board[i-1][j] == ' ') return CONWAYSSOLDIERS_ERROR_EMPTY_JUMP;
		if (cg->board[i-2][j] != ' ') return CONWAYSSOLDIERS_ERROR_OCUPIED_DESTINATION;
		cg->board[i-2][j] = cg->board[i][j];
		cg->board[i][j] = ' ';
		cg->board[i-1][j] = ' ';
		cg->numberOfMoves++;
		break;
	case 'r':
		if (i + 2 > 19) return CONWAYSSOLDIERS_ERROR_OUTOFBOUNDS_END_POS;
		if (cg->board[i + 1][j] == ' ') return CONWAYSSOLDIERS_ERROR_EMPTY_JUMP;
		if (cg->board[i + 2][j] != ' ') return CONWAYSSOLDIERS_ERROR_OCUPIED_DESTINATION;
		cg->board[i + 2][j] = cg->board[i][j];
		cg->board[i][j] = ' ';
		cg->board[i + 1][j] = ' ';
		cg->numberOfMoves++;
		break;
	default:
		return CONWAYSSOLDIERS_ERROR_INVALID_DIRECTION;
		break;
	}
	return 0;
}
