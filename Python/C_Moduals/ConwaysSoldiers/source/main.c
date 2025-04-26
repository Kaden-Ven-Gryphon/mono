#include <stdio.h>
#include <stdlib.h>
#include "conwayssoldiers.h"

int main()
{
	struct conwayssoldiers_game_s cg;
	conwayssoldiers_initBoard(&cg, 'x');
	conwayssoldiers_renderFullBoard(&cg);
	printf("%s\n\n", cg.boardString);
	for(int i = 0; i < 25; i++)
	{
		int x, y;
		char direction;
		char input[10];
		printf("\nEnter Move:  i j <direction>  (U)p, (D)own, (L)eft, (R)ight :> ");
		fgets(input, 10, stdin);
		if(sscanf(input, " %d %d %c ", &x, &y, &direction) != 3)
		{
			printf("%c", direction);
			if(sscanf(input, " %c ", &direction) == 1)
			{
				if(direction == 'q') return 0;
				printf("%c", direction);
			}
			printf("\nUnknown Input\n");
			continue;
		}
		printf("X: %d , Y: %d , C: %c \n", x,y,direction);
		conwayssoldiers_moveSoldier(x, y, direction, &cg);
		conwayssoldiers_renderFullBoard(&cg);
		printf("%s\n\n", cg.boardString);	
	}
	
	
	
	return 0;
}
