#include "phaseten.h"

//debuging: comment out line bellow to turn off debuging
#define _DEBUG_MESSAGES
#ifdef _DEBUG_MESSAGES
	#include <stdio.h>
	#define DEBUG_LOG printf
#else
	#define DEBUG_LOG(...){}
#endif







int phaseten_initGame(struct phaseten_game_s* p10g, int numOfP, char* p1Name, char* p2Name, char* p3Name, char* p4Name, char* p5Name, char* p6Name)
{
	//Set player names
	strcpy(p10g->players[0].name, p1Name);
	strcpy(p10g->players[1].name, p2Name);
	strcpy(p10g->players[2].name, p3Name);
	strcpy(p10g->players[3].name, p4Name);
	strcpy(p10g->players[4].name, p5Name);
	strcpy(p10g->players[5].name, p6Name);

	//init player data
	for (int i = 0; i < 6; i++)
	{
		p10g->players[i].numberOfCards = 0;
		p10g->players[i].points = 0;
		p10g->players[i].phase = 1;
		p10g->players[i].meldsComplete = 0;
	}


	//init deck
	//add numbered and colored cards
	int deckIndex = 0;
	for (int i = 1; i < 13; i++)
	{
		p10g->deck[deckIndex].color = 'r';
		p10g->deck[deckIndex++].value = i;
		p10g->deck[deckIndex].color = 'r';
                p10g->deck[deckIndex++].value = i;
		p10g->deck[deckIndex].color = 'g';
                p10g->deck[deckIndex++].value = i;
		p10g->deck[deckIndex].color = 'g';
                p10g->deck[deckIndex++].value = i;
		p10g->deck[deckIndex].color = 'b';
                p10g->deck[deckIndex++].value = i;
		p10g->deck[deckIndex].color = 'b';
                p10g->deck[deckIndex++].value = i;
		p10g->deck[deckIndex].color = 'y';
                p10g->deck[deckIndex++].value = i;
		p10g->deck[deckIndex].color = 'y';
                p10g->deck[deckIndex++].value = i;
	}
	//add skips
	for (int i = 0; i < 4; i++)
	{
		p10g->deck[deckIndex].color = 's';
		p10g->deck[deckIndex++].value = -1;
	}
	//add wilds
        for (int i = 0; i < 8; i++)
        {
                p10g->deck[deckIndex].color = 's';
                p10g->deck[deckIndex++].value = -2;
        }

	p10g->numberOfPlayers = numOfP;
	p10g->currentPlayer = 0;
	p10g->cardsInDeck = 108;
	p10g->cardsInDiscard = 0;
	p10g->numMelds = 0;

	for(int i = 0; i < 24; i++)
	{
		p10g->melds[i].cards[0].value = 0;
	}


	//shuffle deck
	srand48(time(NULL));
	//shuffle recomended 7 times
	for (int i = 0; i < 7; i++)
	{
		//set up start pos of each half of deck
		int sideAindex = 0;
		int sideBindex = p10g->cardsInDeck / 2;
		int sideAmax = sideBindex;
		int deckIndex = 0;

		//set up the deck in a buf
		struct phaseten_card_s buf[108];
		for (int j = 0; j < p10g->cardsInDeck; j++)
		{
			buf[j] = p10g->deck[j];
		}

		//while the two halves still have cards
		while (sideAindex < sideAmax && sideBindex < p10g->cardsInDeck)
		{
			//get random count 1-5 cards
			double prob = drand48();
			int count = 0;
			if (prob < 0.05) count = 5;
			else if (prob < 0.1) count = 4;
			else if (prob < 0.3) count = 3;
			else if (prob < 0.8) count = 2;
			else count = 1;

			//move count cards to deck from side A
			for (int j = 0; j < count; j++)
			{
				p10g->deck[deckIndex++] = buf[sideAindex++];
				if (sideAindex >= sideAmax) break;
			}

			//get random count 1-5 cards
			prob = drand48();
			if (prob < 0.05) count = 5;
			else if (prob < 0.1) count = 4;
			else if (prob < 0.3) count = 3;
			else if (prob < 0.8) count = 2;
			else count = 1;

			//move count cards to deck from side B
			for (int j = 0; j < count; j++)
			{
				p10g->deck[deckIndex++] = buf[sideBindex++];
				if (sideBindex >= p10g->cardsInDeck) break;
			}
		}//end of while cards in two sides

		//add rest of side A
		while (sideAindex < sideAmax)
		{
			p10g->deck[deckIndex++] = buf[sideAindex++];
		}
		//add rest of side B
		while (sideBindex < p10g->cardsInDeck)
		{
			p10g->deck[deckIndex++] = buf[sideBindex++];
		}

	}// end of 7 shuffles



	//deal cards
	for(int i = 0; i < 10; i++)
	{
		for (int j = 0; j < p10g->numberOfPlayers; j++)
		{
			p10g->players[j].hand[p10g->players[j].numberOfCards++] = p10g->deck[--(p10g->cardsInDeck)];
		}
	}

	//set discard
	p10g->discard[0] = p10g->deck[p10g->cardsInDeck--];
	p10g->cardsInDiscard = 1;

	phaseten_sortByNumber(p10g);

	return 0;
}

//sort all player hands by the value
int phaseten_sortByNumber(struct phaseten_game_s* p10g)
{
	//loop trough all players
	for(int i = 0; i < p10g->numberOfPlayers; i++)
	{
		//basic bubble sort
		struct phaseten_card_s buf;
		for(int j = 0; j < p10g->players[i].numberOfCards-1; j++)
		{
			for(int k = 0; k < p10g->players[i].numberOfCards-1; k++)
			{
				if(p10g->players[i].hand[k].value > p10g->players[i].hand[k+1].value)
				{
					buf = p10g->players[i].hand[k];
					p10g->players[i].hand[k] = p10g->players[i].hand[k+1];
					p10g->players[i].hand[k+1] = buf;
				}
			}
		}
	}
	return 0;
}

//current player adds card from deck 1 or discard 2
int phaseten_draw(struct phaseten_game_s* p10g, int deck)
{
	if(deck == 1)
	{
		//set player hand size + 1 and lowers deck size by
		p10g->players[p10g->currentPlayer].hand[p10g->players[p10g->currentPlayer].numberOfCards++] = p10g->deck[--(p10g->cardsInDeck)];
	}
	else if (deck == 2)
	{
		p10g->players[p10g->currentPlayer].hand[p10g->players[p10g->currentPlayer].numberOfCards++] = p10g->discard[--(p10g->cardsInDiscard)];
	}
	//if invalid input return 1
	else return 1;
	//resort the player hands
	phaseten_sortByNumber(p10g);
	return 0;
}


//current player discard card index cardNum, and purrent player updates
int phaseten_discard(struct phaseten_game_s* p10g, int cardNum)
{
	//if the selected card is out of bounds return error 1
	if(cardNum < 0 || cardNum > p10g->players[p10g->currentPlayer].numberOfCards-1) return 1;
	//add the  players card to the discard pile
	p10g->discard[p10g->cardsInDiscard++] = p10g->players[p10g->currentPlayer].hand[cardNum];
	//shift the rest of the players cards to the left
	for(int i = cardNum; i < p10g->players[p10g->currentPlayer].numberOfCards-1; i++)
	{
		p10g->players[p10g->currentPlayer].hand[i] = p10g->players[p10g->currentPlayer].hand[i+1];
	}
	//remove the card from the players hand
	p10g->players[p10g->currentPlayer].numberOfCards--;
	p10g->currentPlayer++;
	if(p10g->currentPlayer >= p10g->numberOfPlayers) p10g->currentPlayer = 0;
	return 0;
}


int phaseten_addCardToMeld(struct phaseten_game_s* p10g, int cardNum, int meldNum)
{

	int curP = p10g->currentPlayer;
	int meldIndex = 0;

	//if the selected card is out of bounds return error 1
	if(cardNum < 0 || cardNum > p10g->players[curP].numberOfCards-1) return 1;
	if(meldNum < 0 || ((meldNum > (curP+1)*4-1 || meldNum < curP*4) && p10g->players[curP].meldsComplete == 0)) return 1;

	//figure out if meld exits$$$$$$$$$$$$$$$$$$$$$$

	for (int i = 0; i < 24; i++)
	{
		if (p10g->melds[meldNum].cards[i].value == 0)
		{
			meldIndex = i;
			break;
		}
	}

	p10g->melds[meldNum].cards[meldIndex++] = p10g->players[curP].hand[cardNum];
	p10g->melds[meldNum].cards[meldIndex].value = 0;

	//shift the rest of the players cards to the left
	for(int i = cardNum; i < p10g->players[p10g->currentPlayer].numberOfCards-1; i++)
	{
		p10g->players[p10g->currentPlayer].hand[i] = p10g->players[p10g->currentPlayer].hand[i+1];
	}
	//remove the card from the players hand
	p10g->players[p10g->currentPlayer].numberOfCards--;




	return 0;
}
