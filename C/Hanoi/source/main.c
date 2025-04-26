#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "hanoi.h"

#define CLEAR		printf("\e[1;1H\e[2J")

int main()
{
	struct hanoi_game_s hg;
	hanoi_init(&hg, 15);
	
	hanoi_rSolution(&hg, 15, 1, 2, 3);
	
	//hanoi_render(&hg);
	
	printf("Hanoi Start\n\n%s\n\nHanoi End\n\n", hg.boardString);

	return 1;
}
