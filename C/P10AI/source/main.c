#include <stdio.h>
#include "phaseten.h"
#include "phasetenutil.h"
int main()
{
	struct phaseten_game_s pg;
	phaseten_initGame(&pg, 4, "Kaden", "Wren", "Jon", "Sierra", "", "");

	for(int i = 0; i < 10; i ++)
	{
		phasetenutil_runTurn(&pg);
	}

	//phasetenutil_printFull(&pg);
	return 0;
}
