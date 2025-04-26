#include "ticktack.h"

//debuging: comment out line bellow to turn off debuging
#define _DEBUG_MESSAGES
#ifdef _DEBUG_MESSAGES
	#include <stdio.h>
	#define DEBUG_LOG printf
#else
	#define DEBUG_LOG(...) {}
#endif

#define NUMPAD_CONTROL 1

int ticktack_initGame(struct ticktack_game_s* ttg)
{
	ttg->winner = -1;
	ttg->turn = 1;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			ttg->board[i][j] = ' ';
		}
	}

	return 0;
}

int ticktack_playTurn(struct ticktack_game_s* ttg, int tile)
{
	int x = tile % 3;
	int y = tile / 3;

	if(NUMPAD_CONTROL) y = 2 - y;

	int player = ttg-> turn % 2;

	if(ttg->winner != -1) return ttg->winner;
	if(ttg->board[x][y] != ' ') return TICKTACK_ERROR_TILE_FULL;
	else
	{
		if(player == 1)
		{
			ttg->board[x][y] = 'X';
		}
		else
		{
			ttg->board[x][y] = 'O';
		}
	}
	ttg->turn++;
	//check for winner
	for(int i = 0; i < 3; i++)
	{
		int countX = 0;
		int countO = 0;
		for(int j = 0; j < 3; j++)
		{
			if(ttg->board[i][j] == 'X') countX++;
			else if(ttg->board[i][j] == 'O') countO++;
		}
		if(countX == 3) ttg->winner = 1;
		else if(countO == 3) ttg->winner = 2;
	}
	for(int i = 0; i < 3; i++)
	{
		int countX = 0;
		int countO = 0;
		for(int j = 0; j < 3; j++)
		{
			if(ttg->board[j][i] == 'X') countX++;
			else if(ttg->board[j][i] == 'O') countO++;
		}
		if(countX == 3) ttg->winner = 1;
		else if(countO == 3) ttg->winner = 2;
	}
	int countX = 0;
	int countO = 0;
	for(int j = 0; j < 3; j++)
	{
		if(ttg->board[j][j] == 'X') countX++;
		else if(ttg->board[j][j] == 'O') countO++;
	}
	if(countX == 3) ttg->winner = 1;
	else if(countO == 3) ttg->winner = 2;
	countX = 0;
	countO = 0;
	for(int j = 0; j < 3; j++)
	{
		if(ttg->board[2-j][j] == 'X') countX++;
		else if(ttg->board[2-j][j] == 'O') countO++;
	}
	if(countX == 3) ttg->winner = 1;
	else if (countO == 3) ttg->winner = 2;
	else if(ttg->turn == 10) ttg->winner = 3;

	if(ttg->winner != -1) return ttg->winner;
	return 0;
}

//this returns the pos of the best move
//this uses numpad control
int ticktack_bestMove(struct ticktack_game_s* ttg)
{
	//srand(time(NULL));
	//on the first turn X choses center
	if(ttg->turn == 1)
	{
		int ranTile = rand()%9;
		return ranTile;
	}
	//on the second turn O choses center or bottom left conner
	if(ttg->turn == 2)
	{
		if(ttg->board[1][1] == ' ') return 4;
		else if (ttg->board[0][2] == ' ') return 0;
	}
	//on the thrid turn X looks for its first X and finds a possible three in a row
	if(ttg->turn == 3)
	{
		int xx = 0;
		int xy = 0;
		//find the location of the first X
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'X')
				{
					xx = i;
					xy = j;
				}
			}
		}
		int counter = 0;
		int targetX;
		int targetY;
		//check is the diagnals are open
		if(xx == xy)
		{
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][i] == ' ')
				{
					counter++;
					targetX = i;
					targetY = i;
				}
			}
		}
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		counter = 0;
		if(xx == 2 - xy)
		{
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][2-i] == ' ')
				{
					counter++;
					targetX = i;
					targetY = 2-i;
				}
			}
		}
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		counter = 0;
		//check if the row is open

		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][xy] == ' ')
			{
				counter++;
				targetX = i;
				targetY = xy;
			}
		}
		//if the row is open return the next spot
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}
		//else check if the collom is open
		counter = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[xx][i] == ' ')
			{
				counter++;
				targetX = xx;
				targetY = i;
			}
		}
		//if the collom is open return the next spot
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}
	}

	//O need to find if it needs to block X, other wise it needs to find possible 3 in a row
	if(ttg->turn == 4)
	{
		int xCount = 0;
		int spaceCount = 0;
		int targetX = 0;
		int targetY = 0;

		//seach the colloms for possible X win
		for(int i = 0; i < 3; i++)
		{
			xCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'X') xCount++;
				else if(ttg->board[i][j] == ' ')
				{
					spaceCount++;
					targetX = i;
					targetY = j;
				}
			}
			//if it finds one return move to block it
			if(xCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}

		//seach the rows for possible X win
		for(int i = 0; i < 3; i++)
		{
			xCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[j][i] == 'X') xCount++;
				else if(ttg->board[j][i] == ' ')
				{
					spaceCount++;
					targetX = j;
					targetY = i;
				}
			}
			//if it finds one return move to block it
			if(xCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}
		//seach the diagnals for possible X win
		xCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][i] == 'X') xCount++;
			else if(ttg->board[i][i] == ' ')
			{
				spaceCount++;
				targetX = i;
				targetY = i;
			}
		}
		//if it finds one return move to block it
		if(xCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		xCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[2-i][i] == 'X') xCount++;
			else if(ttg->board[2-i][i] == ' ')
			{
				spaceCount++;
				targetX = 2-i;
				targetY = i;
			}
		}
		//if it finds one return move to block it
		if(xCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//At this point then X does not have a possible win and O needs to look for its own possible 3 in a row
		int ox = 0;
		int oy = 0;
		//find the location of the first X
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'O')
				{
					ox = i;
					oy = j;
				}
			}
		}
		int counter = 0;
		targetX = 0;
		targetY = 0;
		//check is the diagnals are open
		if(ox == oy)
		{
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][i] == ' ')
				{
					counter++;
					targetX = i;
					targetY = i;
				}
			}
		}
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		counter = 0;
		if(ox == 2 - oy)
		{
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][2-i] == ' ')
				{
					counter++;
					targetX = i;
					targetY = 2-i;
				}
			}
		}
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		counter = 0;
		//check if the row is open

		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][oy] == ' ')
			{
				counter++;
				targetX = i;
				targetY = oy;
			}
		}
		//if the row is open return the next spot
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}
		//else check if the collom is open
		counter = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[ox][i] == ' ')
			{
				counter++;
				targetX = ox;
				targetY = i;
			}
		}
		//if the collom is open return the next spot
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

	}
	//look for win
	//look for O about to win to block
	//make a 2 in a row if posible
	if(ttg->turn == 5)
	{
		//seach for 2 Xs in a row for a win
		int xCount = 0;
		int spaceCount = 0;
		int targetX = 0;
		int targetY = 0;

		//seach the colloms for possible X win
		for(int i = 0; i < 3; i++)
		{
			xCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'X') xCount++;
				else if(ttg->board[i][j] == ' ')
				{
					spaceCount++;
					targetX = i;
					targetY = j;
				}
			}
			//if it finds one return move to win
			if(xCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}

		//seach the rows for possible X win
		for(int i = 0; i < 3; i++)
		{
			xCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[j][i] == 'X') xCount++;
				else if(ttg->board[j][i] == ' ')
				{
					spaceCount++;
					targetX = j;
					targetY = i;
				}
			}
			//if it finds one return move to win
			if(xCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}
		//seach the diagnals for possible X win
		xCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][i] == 'X') xCount++;
			else if(ttg->board[i][i] == ' ')
			{
				spaceCount++;
				targetX = i;
				targetY = i;
			}
		}
		//if it finds one return move to win
		if(xCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		xCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[2-i][i] == 'X') xCount++;
			else if(ttg->board[2-i][i] == ' ')
			{
				spaceCount++;
				targetX = 2-i;
				targetY = i;
			}
		}
		//if it finds one return move to win
		if(xCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//No possible x win so look to block O

		int oCount = 0;
		spaceCount = 0;
		targetX = 0;
		targetY = 0;

		//seach the colloms for possible X win
		for(int i = 0; i < 3; i++)
		{
			oCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'O') oCount++;
				else if(ttg->board[i][j] == ' ')
				{
					spaceCount++;
					targetX = i;
					targetY = j;
				}
			}
			//if it finds one return move to block it
			if(oCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}

		//seach the rows for possible X win
		for(int i = 0; i < 3; i++)
		{
			oCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[j][i] == 'O') oCount++;
				else if(ttg->board[j][i] == ' ')
				{
					spaceCount++;
					targetX = j;
					targetY = i;
				}
			}
			//if it finds one return move to block it
			if(oCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}
		//seach the diagnals for possible X win
		oCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][i] == 'O') oCount++;
			else if(ttg->board[i][i] == ' ')
			{
				spaceCount++;
				targetX = i;
				targetY = i;
			}
		}
		//if it finds one return move to block it
		if(oCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		oCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[2-i][i] == 'O') oCount++;
			else if(ttg->board[2-i][i] == ' ')
			{
				spaceCount++;
				targetX = 2-i;
				targetY = i;
			}
		}
		//if it finds one return move to block it
		if(oCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//at this point it has not found a win or found a spot to block O
		//it now need to look if it can set up anouther 3 in a row

		//check first X
		int xx = 0;
		int xy = 0;
		//find the location of the first X
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'X')
				{
					xx = i;
					xy = j;
				}
			}
		}
		int counter = 0;
		targetX = 0;
		targetY = 0;
		//check is the diagnals are open
		if(xx == xy)
		{
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][i] == ' ')
				{
					counter++;
					targetX = i;
					targetY = i;
				}
			}
		}
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		counter = 0;
		if(xx == 2 - xy)
		{
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][2-i] == ' ')
				{
					counter++;
					targetX = i;
					targetY = 2-i;
				}
			}
		}
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		counter = 0;
		//check if the row is open

		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][xy] == ' ')
			{
				counter++;
				targetX = i;
				targetY = xy;
			}
		}
		//if the row is open return the next spot
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}
		//else check if the collom is open
		counter = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[xx][i] == ' ')
			{
				counter++;
				targetX = xx;
				targetY = i;
			}
		}
		//if the collom is open return the next spot
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//check second x

		xx = 0;
		xy = 0;
		//find the location of the first X
		for(int i = 2; i >= 0; i--)
		{
			for(int j = 2; j >= 0; j--)
			{
				if(ttg->board[i][j] == 'X')
				{
					xx = i;
					xy = j;
				}
			}
		}
		counter = 0;
		targetX = 0;
		targetY = 0;
		//check is the diagnals are open
		if(xx == xy)
		{
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][i] == ' ')
				{
					counter++;
					targetX = i;
					targetY = i;
				}
			}
		}
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		counter = 0;
		if(xx == 2 - xy)
		{
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][2-i] == ' ')
				{
					counter++;
					targetX = i;
					targetY = 2-i;
				}
			}
		}
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		counter = 0;
		//check if the row is open

		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][xy] == ' ')
			{
				counter++;
				targetX = i;
				targetY = xy;
			}
		}
		//if the row is open return the next spot
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}
		//else check if the collom is open
		counter = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[xx][i] == ' ')
			{
				counter++;
				targetX = xx;
				targetY = i;
			}
		}
		//if the collom is open return the next spot
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//otherwise just return the next open spot
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == ' ') return i + ((2-j)*3);
			}
		}

	}

	//look for o win
	//look to block x win
	//look to set up o win next turn
	if(ttg->turn == 6)
	{
		//seach for 2 Xs in a row for a win
		int oCount = 0;
		int spaceCount = 0;
		int targetX = 0;
		int targetY = 0;

		//seach the colloms for possible X win
		for(int i = 0; i < 3; i++)
		{
			oCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'O') oCount++;
				else if(ttg->board[i][j] == ' ')
				{
					spaceCount++;
					targetX = i;
					targetY = j;
				}
			}
			//if it finds one return move to win
			if(oCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}

		//seach the rows for possible X win
		for(int i = 0; i < 3; i++)
		{
			oCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[j][i] == 'O') oCount++;
				else if(ttg->board[j][i] == ' ')
				{
					spaceCount++;
					targetX = j;
					targetY = i;
				}
			}
			//if it finds one return move to win
			if(oCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}
		//seach the diagnals for possible X win
		oCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][i] == 'O') oCount++;
			else if(ttg->board[i][i] == ' ')
			{
				spaceCount++;
				targetX = i;
				targetY = i;
			}
		}
		//if it finds one return move to win
		if(oCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		oCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[2-i][i] == 'O') oCount++;
			else if(ttg->board[2-i][i] == ' ')
			{
				spaceCount++;
				targetX = 2-i;
				targetY = i;
			}
		}
		//if it finds one return move to win
		if(oCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//No possible x win so look to block O

		int xCount = 0;
		spaceCount = 0;
		targetX = 0;
		targetY = 0;

		//seach the colloms for possible X win
		for(int i = 0; i < 3; i++)
		{
			xCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'X') xCount++;
				else if(ttg->board[i][j] == ' ')
				{
					spaceCount++;
					targetX = i;
					targetY = j;
				}
			}
			//if it finds one return move to block it
			if(xCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}

		//seach the rows for possible X win
		for(int i = 0; i < 3; i++)
		{
			xCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[j][i] == 'X') xCount++;
				else if(ttg->board[j][i] == ' ')
				{
					spaceCount++;
					targetX = j;
					targetY = i;
				}
			}
			//if it finds one return move to block it
			if(xCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}
		//seach the diagnals for possible X win
		xCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][i] == 'X') xCount++;
			else if(ttg->board[i][i] == ' ')
			{
				spaceCount++;
				targetX = i;
				targetY = i;
			}
		}
		//if it finds one return move to block it
		if(xCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		xCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[2-i][i] == 'X') xCount++;
			else if(ttg->board[2-i][i] == ' ')
			{
				spaceCount++;
				targetX = 2-i;
				targetY = i;
			}
		}
		//if it finds one return move to block it
		if(xCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//at this point it has not found a win or found a spot to block X
		//it now need to look if it can set up anouther 3 in a row

		//check first O
		int ox = 0;
		int oy = 0;
		//find the location of the first O
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'O')
				{
					ox = i;
					oy = j;
				}
			}
		}
		int counter = 0;
		targetX = 0;
		targetY = 0;
		//check is the diagnals are open
		if(ox == oy)
		{
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][i] == ' ')
				{
					counter++;
					targetX = i;
					targetY = i;
				}
			}
		}
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		counter = 0;
		if(ox == 2 - oy)
		{
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][2-i] == ' ')
				{
					counter++;
					targetX = i;
					targetY = 2-i;
				}
			}
		}
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		counter = 0;
		//check if the row is open

		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][oy] == ' ')
			{
				counter++;
				targetX = i;
				targetY = oy;
			}
		}
		//if the row is open return the next spot
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}
		//else check if the collom is open
		counter = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[ox][i] == ' ')
			{
				counter++;
				targetX = ox;
				targetY = i;
			}
		}
		//if the collom is open return the next spot
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//check second o

		ox = 0;
		oy = 0;
		//find the location of the first o
		for(int i = 2; i >= 0; i--)
		{
			for(int j = 2; j >= 0; j--)
			{
				if(ttg->board[i][j] == 'O')
				{
					ox = i;
					oy = j;
				}
			}
		}
		counter = 0;
		targetX = 0;
		targetY = 0;
		//check is the diagnals are open
		if(ox == oy)
		{
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][i] == ' ')
				{
					counter++;
					targetX = i;
					targetY = i;
				}
			}
		}
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		counter = 0;
		if(ox == 2 - oy)
		{
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][2-i] == ' ')
				{
					counter++;
					targetX = i;
					targetY = 2-i;
				}
			}
		}
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		counter = 0;
		//check if the row is open

		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][oy] == ' ')
			{
				counter++;
				targetX = i;
				targetY = oy;
			}
		}
		//if the row is open return the next spot
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}
		//else check if the collom is open
		counter = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[ox][i] == ' ')
			{
				counter++;
				targetX = ox;
				targetY = i;
			}
		}
		//if the collom is open return the next spot
		if(counter == 2)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//otherwise just return the next open spot
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == ' ') return i + ((2-j)*3);
			}
		}
	}

	//same as turn 5
	if(ttg->turn == 7)
	{
		//seach for 2 Xs in a row for a win
		int xCount = 0;
		int spaceCount = 0;
		int targetX = 0;
		int targetY = 0;

		//seach the colloms for possible X win
		for(int i = 0; i < 3; i++)
		{
			xCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'X') xCount++;
				else if(ttg->board[i][j] == ' ')
				{
					spaceCount++;
					targetX = i;
					targetY = j;
				}
			}
			//if it finds one return move to win
			if(xCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}

		//seach the rows for possible X win
		for(int i = 0; i < 3; i++)
		{
			xCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[j][i] == 'X') xCount++;
				else if(ttg->board[j][i] == ' ')
				{
					spaceCount++;
					targetX = j;
					targetY = i;
				}
			}
			//if it finds one return move to win
			if(xCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}
		//seach the diagnals for possible X win
		xCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][i] == 'X') xCount++;
			else if(ttg->board[i][i] == ' ')
			{
				spaceCount++;
				targetX = i;
				targetY = i;
			}
		}
		//if it finds one return move to win
		if(xCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		xCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[2-i][i] == 'X') xCount++;
			else if(ttg->board[2-i][i] == ' ')
			{
				spaceCount++;
				targetX = 2-i;
				targetY = i;
			}
		}
		//if it finds one return move to win
		if(xCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//No possible x win so look to block O

		int oCount = 0;
		spaceCount = 0;
		targetX = 0;
		targetY = 0;

		//seach the colloms for possible X win
		for(int i = 0; i < 3; i++)
		{
			oCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'O') oCount++;
				else if(ttg->board[i][j] == ' ')
				{
					spaceCount++;
					targetX = i;
					targetY = j;
				}
			}
			//if it finds one return move to block it
			if(oCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}

		//seach the rows for possible X win
		for(int i = 0; i < 3; i++)
		{
			oCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[j][i] == 'O') oCount++;
				else if(ttg->board[j][i] == ' ')
				{
					spaceCount++;
					targetX = j;
					targetY = i;
				}
			}
			//if it finds one return move to block it
			if(oCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}
		//seach the diagnals for possible X win
		oCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][i] == 'O') oCount++;
			else if(ttg->board[i][i] == ' ')
			{
				spaceCount++;
				targetX = i;
				targetY = i;
			}
		}
		//if it finds one return move to block it
		if(oCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		oCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[2-i][i] == 'O') oCount++;
			else if(ttg->board[2-i][i] == ' ')
			{
				spaceCount++;
				targetX = 2-i;
				targetY = i;
			}
		}
		//if it finds one return move to block it
		if(oCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//at this point it has not found a win or found a spot to block O
		//it now need to look if it can set up anouther 3 in a row


		for(int k = 0; k < 2; k++)
		{
			int xx = 0;
			int xy = 0;
			//find the location of the first X
			int foundX = 0;
			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					if(ttg->board[i][j] == 'X')
					{
						xx = i;
						xy = j;
						if(foundX == k)
						{
							foundX++;
							break;
						}
						foundX++;
					}
				}
				if(foundX == k+1) break;
			}
			int counter = 0;
			targetX = 0;
			targetY = 0;
			//check is the diagnals are open
			if(xx == xy)
			{
				for(int i = 0; i < 3; i++)
				{
					if(ttg->board[i][i] == ' ')
					{
						counter++;
						targetX = i;
						targetY = i;
					}
				}
			}
			if(counter == 2)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}

			counter = 0;
			if(xx == 2 - xy)
			{
				for(int i = 0; i < 3; i++)
				{
					if(ttg->board[i][2-i] == ' ')
					{
						counter++;
						targetX = i;
						targetY = 2-i;
					}
				}
			}
			if(counter == 2)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}

			counter = 0;
			//check if the row is open

			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][xy] == ' ')
				{
					counter++;
					targetX = i;
					targetY = xy;
				}
			}
			//if the row is open return the next spot
			if(counter == 2)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
			//else check if the collom is open
			counter = 0;
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[xx][i] == ' ')
				{
					counter++;
					targetX = xx;
					targetY = i;
				}
			}
			//if the collom is open return the next spot
			if(counter == 2)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}

		//otherwise just return the next open spot
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == ' ') return i + ((2-j)*3);
			}
		}
	}
	if(ttg->turn == 8)
	{
		//seach for 2 Xs in a row for a win
		int oCount = 0;
		int spaceCount = 0;
		int targetX = 0;
		int targetY = 0;

		//seach the colloms for possible X win
		for(int i = 0; i < 3; i++)
		{
			oCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'O') oCount++;
				else if(ttg->board[i][j] == ' ')
				{
					spaceCount++;
					targetX = i;
					targetY = j;
				}
			}
			//if it finds one return move to win
			if(oCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}

		//seach the rows for possible X win
		for(int i = 0; i < 3; i++)
		{
			oCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[j][i] == 'O') oCount++;
				else if(ttg->board[j][i] == ' ')
				{
					spaceCount++;
					targetX = j;
					targetY = i;
				}
			}
			//if it finds one return move to win
			if(oCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}
		//seach the diagnals for possible X win
		oCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][i] == 'O') oCount++;
			else if(ttg->board[i][i] == ' ')
			{
				spaceCount++;
				targetX = i;
				targetY = i;
			}
		}
		//if it finds one return move to win
		if(oCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		oCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[2-i][i] == 'O') oCount++;
			else if(ttg->board[2-i][i] == ' ')
			{
				spaceCount++;
				targetX = 2-i;
				targetY = i;
			}
		}
		//if it finds one return move to win
		if(oCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//No possible x win so look to block O

		int xCount = 0;
		spaceCount = 0;
		targetX = 0;
		targetY = 0;

		//seach the colloms for possible X win
		for(int i = 0; i < 3; i++)
		{
			xCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == 'X') xCount++;
				else if(ttg->board[i][j] == ' ')
				{
					spaceCount++;
					targetX = i;
					targetY = j;
				}
			}
			//if it finds one return move to block it
			if(xCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}

		//seach the rows for possible X win
		for(int i = 0; i < 3; i++)
		{
			xCount = 0;
			spaceCount = 0;
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[j][i] == 'X') xCount++;
				else if(ttg->board[j][i] == ' ')
				{
					spaceCount++;
					targetX = j;
					targetY = i;
				}
			}
			//if it finds one return move to block it
			if(xCount == 2 && spaceCount == 1)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}
		//seach the diagnals for possible X win
		xCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[i][i] == 'X') xCount++;
			else if(ttg->board[i][i] == ' ')
			{
				spaceCount++;
				targetX = i;
				targetY = i;
			}
		}
		//if it finds one return move to block it
		if(xCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		xCount = 0;
		spaceCount = 0;
		for(int i = 0; i < 3; i++)
		{
			if(ttg->board[2-i][i] == 'X') xCount++;
			else if(ttg->board[2-i][i] == ' ')
			{
				spaceCount++;
				targetX = 2-i;
				targetY = i;
			}
		}
		//if it finds one return move to block it
		if(xCount == 2 && spaceCount == 1)
		{
			int buf = 2 - targetY;
			buf *= 3;
			return buf + targetX;
		}

		//at this point it has not found a win or found a spot to block X
		//it now need to look if it can set up anouther 3 in a row

		//check first O
		for(int k = 0; k < 3; k++)
		{
			int ox = 0;
			int oy = 0;
			int foundO = 0;
			//find the location of the first O
			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					if(ttg->board[i][j] == 'O')
					{
						ox = i;
						oy = j;
						if(foundO == k)
						{
							foundO++;
							break;
						}
						foundO++;
					}
				}
				if(foundO == k+1) break;
			}
			int counter = 0;
			targetX = 0;
			targetY = 0;
			//check is the diagnals are open
			if(ox == oy)
			{
				for(int i = 0; i < 3; i++)
				{
					if(ttg->board[i][i] == ' ')
					{
						counter++;
						targetX = i;
						targetY = i;
					}
				}
			}
			if(counter == 2)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}

			counter = 0;
			if(ox == 2 - oy)
			{
				for(int i = 0; i < 3; i++)
				{
					if(ttg->board[i][2-i] == ' ')
					{
						counter++;
						targetX = i;
						targetY = 2-i;
					}
				}
			}
			if(counter == 2)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}

			counter = 0;
			//check if the row is open

			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[i][oy] == ' ')
				{
					counter++;
					targetX = i;
					targetY = oy;
				}
			}
			//if the row is open return the next spot
			if(counter == 2)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
			//else check if the collom is open
			counter = 0;
			for(int i = 0; i < 3; i++)
			{
				if(ttg->board[ox][i] == ' ')
				{
					counter++;
					targetX = ox;
					targetY = i;
				}
			}
			//if the collom is open return the next spot
			if(counter == 2)
			{
				int buf = 2 - targetY;
				buf *= 3;
				return buf + targetX;
			}
		}
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == ' ') return i+((2-j)*3);
			}
		}
	}
	//there is only one open spot, fill it
	if(ttg->turn == 9)
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(ttg->board[i][j] == ' ') return i+((2-j)*3);
			}
		}
	}
	return TICKTACK_ERROR_CANT_FIND_MOVE;
}
