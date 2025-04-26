/****************************************************************************************
*
*	File:		kadenimgpng.h
*	Author:	kaden Noctua
*	
*	Program:	kadenimglib
*	
*	Use:		function to read and write png files
*			
*****************************************************************************************/
#ifndef kadenZLIB_H
#define kadenZLIB_H

#include <stdlib.h>
#include <string.h>
#include "kadenbinary.h"

struct kadenzlib_huffmanTreeNode_s
{
	int symbol;
	struct kadenzlib_huffmanTreeNode_s* left;
	struct kadenzlib_huffmanTreeNode_s* right;
};

int kadenzlib_decompress(const unsigned char* buf, char** retVal, unsigned long long len);

//huffman trees
struct kadenzlib_huffmanTreeNode_s* kadenzlib_makeNode();
int kadenzlib_treeInsert(struct kadenzlib_huffmanTreeNode_s** root, unsigned int codeword, int n, int symbol);
int kadenzlib_deconsturctTree(struct kadenzlib_huffmanTreeNode_s* root);
int kadenzlib_decodeSymbol(struct kadenbinary_bitReader_s* br, struct kadenzlib_huffmanTreeNode_s* tree);
int kadenzlib_blListToTree(int* bl, int* alphabet, int numberOfSymbols, struct kadenzlib_huffmanTreeNode_s** root);


int kadenzlib_printTree(struct kadenzlib_huffmanTreeNode_s* root, unsigned int path);

#endif
