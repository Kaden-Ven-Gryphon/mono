#ifndef PHASETEN_H
#define PHASETEN_H

#include <string.h>
#include <stdlib.h>
#include <time.h>

struct phaseten_card_s
{
	char color;
	int value;
};

struct phaseten_player_s
{
	char name[32];
	int numberOfCards;
	struct phaseten_card_s hand[11];
	int phase;
	int points;
	int meldsComplete;
};

struct phaseten_meld_s
{
	//0: match, 1: run, 2: color
	int meldType;
	struct phaseten_card_s cards[24];
};

struct phaseten_game_s
{
	int numberOfPlayers;
	struct phaseten_player_s players[6];
	int currentPlayer;

	int cardsInDeck;
	struct phaseten_card_s deck[108];
	int cardsInDiscard;
	struct phaseten_card_s discard[108];

	int numMelds;
	struct phaseten_meld_s melds[24];
};


int phaseten_initGame(struct phaseten_game_s* p10g, int numOfP, char* p1Name, char* p2Name, char* p3Name, char* p4Name, char* p5Name, char* p6Name);
int phaseten_sortByNumber(struct phaseten_game_s* p10g);
int phaseten_draw(struct phaseten_game_s* p10g, int deck);
int phaseten_discard(struct phaseten_game_s* p10g, int cardNum);
int phaseten_addCardToMeld(struct phaseten_game_s* p10g, int cardNum, int meldNum);
int phaseten_playPhase(struct phaseten_game_s* p10g);



#endif
