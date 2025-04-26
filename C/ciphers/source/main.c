#include "vigenere.h"
#include <stdio.h>

int main()
{
	
	int test = vigenere_encode("this", "is", "a test", 5);
	printf("test succesed\n");
	
	return 0;
}
