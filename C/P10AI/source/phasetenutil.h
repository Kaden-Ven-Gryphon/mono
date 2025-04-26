#ifndef PHASETENUTIL_H
#define PHASETENUTIL_H

#include <string.h>
#include <stdio.h>
#include "phaseten.h"


void phasetenutil_printFull(struct phaseten_game_s* pg);
void phasetenutil_printPlayer(struct phaseten_game_s* pg, int printMelds, int printDiscard, int printCardIndexs);
int phasetenutil_runTurn(struct phaseten_game_s* pg);

#endif
