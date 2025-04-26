#include "phasetenutil.h"

//debuging: comment out line bellow to turn off debuging
#define _DEBUG_MESSAGES
#ifdef _DEBUG_MESSAGES
        #include <stdio.h>
        #define DEBUG_LOG printf
#else
        #define DEBUG_LOG(...){}
#endif

#define CLEAR		printf("\e[1;1H\e[2J")
#define PEN_DEFAULT	printf("\033[0m")
#define PEN_RED		printf("\033[0;31m")
#define PEN_GREEN	printf("\033[0;32m")
#define PEN_BLUE	printf("\033[0;34m")
#define PEN_YELLOW	printf("\033[0;33m")


void phasetenutil_printFull(struct phaseten_game_s* pg)
{
	printf("Players\n\n");
	for(int i = 0; i < pg->numberOfPlayers; i++)
	{
		printf("%-32s Points: %4d\n", pg->players[i].name, pg->players[i].points);
		printf("hand\n");
		int handIndex = 0;
		for (int j = 0; j < 11; j++)
		{
			if(handIndex >= pg->players[i].numberOfCards) break;
			switch(pg->players[i].hand[handIndex].color)
			{
			case 'r':
				PEN_RED;
				break;
			case 'g':
				PEN_GREEN;
				break;
			case 'b':
				PEN_BLUE;
				break;
			case 'y':
				PEN_YELLOW;
				break;
			default:
				PEN_DEFAULT;
				break;
			}
			if (pg->players[i].hand[handIndex].value == -1)
			{
				printf("%6s", "SKIP");
			}
			else if (pg->players[i].hand[handIndex].value == -2)
			{
				printf("%6s", "WILD");
			}
			else
			{
				printf("%6d", pg->players[i].hand[handIndex].value);
			}
			handIndex++;

		}//for print hand
		PEN_DEFAULT;
		printf("\n______________________________________\n");
	}
	printf("______________________________________\n\n");

	printf("Deck\n");

	int deckIndex = 0;
	while (deckIndex < pg->cardsInDeck)
	{
		for (int i = 0; i < 8; i++)
		{
			if(deckIndex >= pg->cardsInDeck) break;
			switch(pg->deck[deckIndex].color)
			{
			case 'r':
				PEN_RED;
				break;
			case 'g':
				PEN_GREEN;
				break;
			case 'b':
				PEN_BLUE;
				break;
			case 'y':
				PEN_YELLOW;
				break;
			default:
				PEN_DEFAULT;
				break;
			}
			if (pg->deck[deckIndex].value == -1)
			{
				printf("%6s", "SKIP");
			}
			else if (pg->deck[deckIndex].value == -2)
			{
				printf("%6s", "WILD");
			}
			else
			{
				printf("%6d", pg->deck[deckIndex].value);
			}
			deckIndex++;

		}//for width
		printf("\n");
	}//while printing deck
	PEN_DEFAULT;
	printf("______________________________________\n");
	printf("\n\n");


	printf("Discard\n");

	deckIndex = 0;
	while (deckIndex < pg->cardsInDiscard)
	{
		for (int i = 0; i < 8; i++)
		{
			if(deckIndex >= pg->cardsInDiscard) break;
			switch(pg->discard[deckIndex].color)
			{
			case 'r':
				PEN_RED;
				break;
			case 'g':
				PEN_GREEN;
				break;
			case 'b':
				PEN_BLUE;
				break;
			case 'y':
				PEN_YELLOW;
				break;
			default:
				PEN_DEFAULT;
				break;
			}
			if (pg->discard[deckIndex].value == -1)
			{
				printf("%6s", "SKIP");
			}
			else if (pg->discard[deckIndex].value == -2)
			{
				printf("%6s", "WILD");
			}
			else
			{
				printf("%6d", pg->discard[deckIndex].value);
			}
			deckIndex++;

		}//for width
		printf("\n");
	}//while printing deck
	PEN_DEFAULT;
	printf("______________________________________\n");
	printf("Current Player: %s\n", pg->players[pg->currentPlayer].name);
	printf("\n\n");

}

void phasetenutil_printPlayer(struct phaseten_game_s* pg, int printMelds, int printDiscard, int printCardIndexs)
{
	if(printMelds != 0)
	{
		printf("Melds:\n");
		for(int i = 0; i < pg->numberOfPlayers; i++)
		{
			printf("%s\n", pg->players[i].name);
			for (int j = 0; j < 4; j++)
			{
				if(pg->melds[i*4+j].cards[0].value == 0) continue;
				printf("(%d: )", i*4+j);
				for (int k = 0; k < 24; k++)
				{
					if(pg->melds[i*4+j].cards[k].value == 0) break;
					switch(pg->melds[i*4+j].cards[k].color)
					{
					case 'r':
						PEN_RED;
						break;
					case 'g':
						PEN_GREEN;
						break;
					case 'b':
						PEN_BLUE;
						break;
					case 'y':
						PEN_YELLOW;
						break;
					default:
						PEN_DEFAULT;
						break;
					}
					if (pg->melds[i*4+j].cards[k].value == -1)
					{
						printf("%6s", "SKIP");
					}
					else if (pg->melds[i*4+j].cards[k].value == -2)
					{
						printf("%6s", "WILD");
					}
					else
					{
						printf("%6d", pg->melds[i*4+j].cards[k].value);
					}
					PEN_DEFAULT;

				}
				printf("\n");
			}
		}
	}

	printf("__________________________________________________________________\n");
	printf("Player: %s\tPoints: %d\n\n", pg->players[pg->currentPlayer].name, pg->players[pg->currentPlayer].points);

	if(printDiscard != 0)
	{
		printf("Discard: ");
		switch(pg->discard[pg->cardsInDiscard-1].color)
		{
		case 'r':
			PEN_RED;
			break;
		case 'g':
			PEN_GREEN;
			break;
		case 'b':
			PEN_BLUE;
			break;
		case 'y':
			PEN_YELLOW;
			break;
		default:
			PEN_DEFAULT;
			break;
		}
		if (pg->discard[pg->cardsInDiscard-1].value == -1)
		{
			printf("%6s", "SKIP");
		}
		else if (pg->discard[pg->cardsInDiscard-1].value == -2)
		{
			printf("%6s", "WILD");
		}
		else
		{
			printf("%6d", pg->discard[pg->cardsInDiscard-1].value);
		}
		PEN_DEFAULT;
	}


	printf("\n\nHand:\n");

	int handIndex = 0;
	for (int j = 0; j < 11; j++)
	{
		if(handIndex >= pg->players[pg->currentPlayer].numberOfCards) break;
		switch(pg->players[pg->currentPlayer].hand[handIndex].color)
		{
		case 'r':
			PEN_RED;
		break;
		case 'g':
			PEN_GREEN;
			break;
		case 'b':
			PEN_BLUE;
			break;
		case 'y':
			PEN_YELLOW;
			break;
		default:
			PEN_DEFAULT;
			break;
		}
		if (pg->players[pg->currentPlayer].hand[handIndex].value == -1)
		{
			printf("%6s", "SKIP");
		}
		else if (pg->players[pg->currentPlayer].hand[handIndex].value == -2)
		{
			printf("%6s", "WILD");
		}
		else
		{
			printf("%6d", pg->players[pg->currentPlayer].hand[handIndex].value);
		}
		handIndex++;

	}//for print hand
	PEN_DEFAULT;
	printf("\n");
	if(printCardIndexs != 0)
	{
		printf("\n");
		for (int i = 0; i < pg->players[pg->currentPlayer].numberOfCards; i++)
		{
			printf("%6d", i);
		}
		printf("\n");
	}
	printf("__________________________________________________________________\n");
}



int phasetenutil_runTurn(struct phaseten_game_s* pg)
{
	char input[16];
	int userSelection = 0;

	CLEAR;
	//SET UP FOR NEXT PLAYER
	printf("_____________________________________________________________\n");
	printf("\nThe next player is: %s\n\nPress enter to start turn:> ", pg->players[pg->currentPlayer].name);
	fgets(input, 16, stdin);
	CLEAR;

	//PRINT PLAYER INFO AND ASK FOR DECK OR DISCARD
	phasetenutil_printPlayer(pg, 1, 1, 0);

	printf("(1) Draw from deck\n(2) Draw from discard\n:> ");
	fgets(input, 16, stdin);
	//DRAW CARD
	sscanf(input, " %d ", &userSelection);
	phaseten_draw(pg, userSelection);
	CLEAR;

	//PRINT PLAYER INFO AND ASK TO DISCARD OR MELD
	phasetenutil_printPlayer(pg, 1, 0, 1);

	printf("(1) Play meld\n(2) Discard\n");
	fgets(input, 16, stdin);
	sscanf(input, " %d ", &userSelection);

	if(userSelection == 1)
	{
		//pg->players[pg->currentPlayer].meldsComplete = 4;
		while(1)
		{
			int ci = 0;
			int mi = 0;
			CLEAR;
			phasetenutil_printPlayer(pg, 1, 0, 1);
			printf("Chose card to add to meld (<card index> <meld index>) or -1 to end turn\n");
			printf("Your meld index's are %d-%d\n:>", pg->currentPlayer*4, pg->currentPlayer*4+3);
			fgets(input, 16, stdin);
			sscanf(input, " %d %d ", &ci, &mi);
			if(ci == -1) break;
			phaseten_addCardToMeld(pg, ci, mi);
		}
		//CHECK FOR COMPLETED MELDS
	}

	printf("Chose card to discard (0-%d)\n:> ", pg->players[pg->currentPlayer].numberOfCards-1);
	fgets(input, 16, stdin);
	//DRAW CARD
	sscanf(input, " %d ", &userSelection);
	phaseten_discard(pg, userSelection);

	printf("\nPress enter to end turn:> ");
	fgets(input, 16, stdin);
	CLEAR;

	return 0;
}
