/****************************************************************************************
*
*	File:		kadenimgpng.c
*	Author:	kaden Noctua
*	
*	Program:	kadenzlib.c
*	
*	Use:		function to read and write zlib streams
*			
*	Source:	https://pyokagan.name/blog/2019-10-18-zlibinflate/
			https://www.rfc-editor.org/rfc/rfc1950
*****************************************************************************************/
#include "kadenzlib.h"

#define _DEBUG_MESSAGES
#ifdef _DEBUG_MESSAGES
	#include <stdio.h>
	#define DEBUG_LOG printf
#else
	#define DEBUG_LOG(...) {}
#endif

#define _ERROR_MESSAGES
#ifdef _ERROR_MESSAGES
	#include <stdio.h>
	#define ERROR_LOG fprintf
#else
	#define ERROR_LOG(...) {}
#endif

//lz77 huffman tables
int _kadenzlib_lengthExtraBits[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
int _kadenzlib_lengthBase[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258};
int _kadenzlib_distanceExtraBits[] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
int _kadenzlib_distanceBase[] = {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577};
int _codelLengthCodesOrder[] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};

//Public Functions
int kadenzlib_decompress(const unsigned char* buf, char** retVal, unsigned long long len)
{
	DEBUG_LOG("START kadenzlib_decompress\n");
	//this it the decompress data that is returned
	*retVal = NULL;
	int retValLength = 0;
	int retValMax = 0;
	
	//set up the initial size of the return data
	*retVal = (char*) malloc(len);
	retValMax = len;
	if(!retVal)
	{
		ERROR_LOG(stderr, "ERROR kadenzlib_decompress: Couldn't allocate memory\n");
		return 0;
	}
	
	//find the meta data for the zlib stream
	int cm = buf[0] & 0x0f;
	int cinfo = buf[0] & 0xf0;
	cinfo = cinfo >> 4;
	int fcheck = buf[1] & 0x1f;
	int fdict = buf[1] & 0x20;
	fdict = fdict >> 5;
	int flevel = buf[1] & 0xC0;
	flevel = flevel >> 6;
	DEBUG_LOG("CM: %d\n", cm);
	DEBUG_LOG("CINFO: %d\n", cinfo);
	DEBUG_LOG("FCHECK: %d\n", fcheck);
	DEBUG_LOG("FDICT: %d\n", fdict);
	DEBUG_LOG("FLEVEL: %d\n", flevel);
	DEBUG_LOG("check sum test %d\n", ( ((int)buf[0] * 256 + (int)buf[1])%31 ));
	
	//check that meta data is valid
	if(cm != 8)
	{
		ERROR_LOG(stderr, "ERROR kadenzlib_decompress: zlib stream has invalid cm value\n");
		return 0;
	}
	if(cinfo > 7)
	{
		ERROR_LOG(stderr, "ERROR kadenzlib_decompress: zlib steam has invalic cinfo value\n");
		return 0;
	}
	if(fdict == 1)
	{
		ERROR_LOG(stderr, "ERROR kadenzlib_decompress: Can not handle dicinarys\n");
		return 0;
	}
	if(( ((int)buf[0] * 256 + (int)buf[1])%31 ) != 0)
	{
		ERROR_LOG(stderr, "ERROR kadenzlib_decompress: checksum fail\n");
		return 0;
	}
	
	//set up varibles to read blocks
	unsigned long long blockstart = 2;
	int bfinal = 0;
	int btype = 0;
	int blen = 0;
	int bnlen = 0;
	
	struct kadenzlib_huffmanTreeNode_s* literalLengthTree = NULL;
	struct kadenzlib_huffmanTreeNode_s* distanceTree = NULL;
	struct kadenzlib_huffmanTreeNode_s* codeLengthTree = NULL;
	struct kadenbinary_bitReader_s br;
	int hlit = 0;
	int hdist = 0;
	int hclen = 0;
	int bl[330];
	int rangeAlphabet[330];
	for(int i = 0; i < 330; i++)
	{
		bl[i] = 0;
		rangeAlphabet[i] = i;
	}
	
	//loop until final block
	while(!bfinal)
	{
		//find if this is the final block
		bfinal = buf[blockstart] & 0x01;
		//find the block type
		btype = buf[blockstart] & 0x06;
		btype = btype >> 1;
		DEBUG_LOG("Is last block: %d\n", bfinal);
		DEBUG_LOG("block type %d\n", btype);
		
		//decode the block
		switch(btype)
		{
		//raw data
		case 0:
			DEBUG_LOG("start block type 0\n");
			//get the length of the block
			blen = kadenbinary_tointRByte(buf+(blockstart+1), 2);
			bnlen = kadenbinary_tointRByte(buf+(blockstart+3), 2);
			//NEED TO ADD CHECK THAT THE LENS MATCH
			DEBUG_LOG("blen: %d and bnlen: %d\n", blen, bnlen);
			
			//check that the retVal has space to copy block to it
			if(retValMax - retValLength >= blen)
			{
				memcpy(*retVal+retValLength, buf+(blockstart+5), blen);
				retValLength += blen;
			}
			else
			{
				ERROR_LOG(stderr, "ERROR kadenzlib_decompress: retval overflow\n");
				return 0;
			}
			
			blockstart += 4+blen;
			break;
		case 1:
			DEBUG_LOG("start block type 1\n");
			//fixed
			
			break;
		case 2:
			DEBUG_LOG("start block type 2\n");
			//dynamic
			
			br.mem = (unsigned char*)buf;
			br.memLength = len;
			br.bytePos = blockstart+1;
			br.bitPos = 0;
			
			DEBUG_LOG("finshed making br\n");
			
			//make leteral and distance trees
			//The number of literal/length codes
			hlit = kadenbinary_readbits(&br, 5) + 257;
			//the number of distance codes
			hdist = kadenbinary_readbits(&br, 5) + 1;
			//the number of code length codes
			hclen = kadenbinary_readbits(&br, 4) + 4;
			
			DEBUG_LOG("HILT: %d\n", hlit);
			DEBUG_LOG("HDIST: %d\n", hdist);
			DEBUG_LOG("HCLEN: %d\n", hclen);
			
			DEBUG_LOG("finshed getting the number of code lengths\n");
			
			//create the bl for the codelengths
			for(int i = 0; i < hclen; i++)
			{
				bl[_codelLengthCodesOrder[i]] = kadenbinary_readbits(&br, 3);
			}
			//create the tree that will allow for the decoding of the code lengths
			kadenzlib_blListToTree(bl, rangeAlphabet, 19, &codeLengthTree);
			kadenzlib_printTree(codeLengthTree, 0);
			DEBUG_LOG("finshed making code length tree\n");
			
			//reset the bl
			for(int i = 0; i < 19; i++) bl[i] = 0;
			
			//decode the bitstream into the codelengths of the two main trees
			int lengthOfBl = 0;
			while(lengthOfBl < (hlit + hdist))
			{
				DEBUG_LOG("length of bl: %d\n", lengthOfBl);
				int sym = kadenzlib_decodeSymbol(&br, codeLengthTree);
				//leteral value
				if(sym >= 0 && sym <= 15)
				{
					DEBUG_LOG("literal: %d\n", sym);
					bl[lengthOfBl++] = sym;
				}
				//copy the previous value, 3-6 times
				else if(sym == 16)
				{
					DEBUG_LOG("16\n");
					int prevCode = bl[lengthOfBl-1];
					int repeatLength = kadenbinary_readbits(&br, 2) + 3;
					for(int i = 0; i < repeatLength; i++) bl[lengthOfBl++] = prevCode;
				}
				//copy 0, 3-10 times
				else if(sym == 17)
				{
					DEBUG_LOG("17\n");
					int repeatLength = kadenbinary_readbits(&br, 3) + 3;
					for(int i = 0; i < repeatLength; i++) bl[lengthOfBl++] = 0;
				}
				//copy 0, 11-138
				else if(sym == 18)
				{
					DEBUG_LOG("18\n");
					int repeatLength = kadenbinary_readbits(&br, 7) + 11;
					for(int i = 0; i < repeatLength; i++) bl[lengthOfBl++] = 0;
				}
				else
				{
					ERROR_LOG(stderr, "ERROR kadenzlib_decompress: unknown sym\n");
					return 0;
				}
			}
			
			DEBUG_LOG("finshed getting the bl for lit and dist trees\n");
			
			kadenzlib_blListToTree(bl, rangeAlphabet, 286, &literalLengthTree);
			kadenzlib_blListToTree(bl+hlit, rangeAlphabet, 286, &literalLengthTree);
			
			
			
			while(1)
			{
				int sym = kadenzlib_decodeSymbol(&br, literalLengthTree);
				if(sym <= 255)
				{
					if(retValMax - retValLength > 0)
					{
						(*retVal)[retValLength++] = (char)sym;
					}
					else
					{
						ERROR_LOG(stderr, "ERROR kadenzlib_decompress: retval overflow\n");
						return 0;
					}
				}
				else if(sym == 256) break;
				else
				{
					sym -= 257;
					int length = kadenbinary_readbits(&br, _kadenzlib_lengthExtraBits[sym]) + _kadenzlib_lengthBase[sym];
					sym = kadenzlib_decodeSymbol(&br, distanceTree);
					int dist = kadenbinary_readbits(&br, _kadenzlib_distanceExtraBits[sym]) + _kadenzlib_distanceBase[sym];
					if(retValMax - retValLength >= length)
					{
						for(int i = 0; i < length; i++)
						{
							memcpy(*retVal+retValLength, *retVal+retValLength-dist, 1);
							retValLength++;
						}
					}
					else
					{
						ERROR_LOG(stderr, "ERROR kadenzlib_decompress: retval overflow\n");
						return 0;
					}
				}
			}
			
			break;
		default:
			ERROR_LOG(stderr, "Unknow block type %d\n", btype);
			return 0;
		}	
	}

	
	kadenzlib_deconsturctTree(literalLengthTree);
	kadenzlib_deconsturctTree(distanceTree);
	kadenzlib_deconsturctTree(codeLengthTree);
	return retValLength;
}

//allocate an empty tree node
struct kadenzlib_huffmanTreeNode_s* kadenzlib_makeNode()
{
	struct kadenzlib_huffmanTreeNode_s* newNode = (struct kadenzlib_huffmanTreeNode_s*)malloc(sizeof(struct kadenzlib_huffmanTreeNode_s));
	if(newNode == NULL)
	{
		ERROR_LOG(stderr, "ERROR: kadenzlib_makeNode failed to allocate memory\n");
		return NULL;
	}
	newNode->symbol = -1;
	newNode->right = NULL;
	newNode->left = NULL;
	return newNode;
}


int kadenzlib_treeInsert(struct kadenzlib_huffmanTreeNode_s** root, unsigned int codeword, int n, int symbol)
{
	//DEBUG_LOG("intcert codeword 0x%x symbol %d\n", symbol, codeword);
	DEBUG_LOG("insert ");
	if(*root == NULL)
	{
		*root = kadenzlib_makeNode();
	}
	struct kadenzlib_huffmanTreeNode_s* pointerNode =  *root;
	struct kadenzlib_huffmanTreeNode_s* nextNode = NULL;
	
	for(int i = n-1; i >= 0; i--)
	{
		char bit = codeword & (1 << i);
		if(bit)
		{
			DEBUG_LOG("1");
			nextNode = pointerNode->right;
			if(nextNode == NULL)
			{
				pointerNode->right = kadenzlib_makeNode();
				nextNode = pointerNode->right;
			}
		}
		else
		{
			DEBUG_LOG("0");
			nextNode = pointerNode->left;
			if(nextNode == NULL)
			{
				pointerNode->left = kadenzlib_makeNode();
				nextNode = pointerNode->left;
			}
		}
		pointerNode = nextNode;
	}
	DEBUG_LOG("  symbol: %d\n", symbol);
	pointerNode->symbol = symbol;
	return 0;
}


//recursivly distroy the tree
int kadenzlib_deconsturctTree(struct kadenzlib_huffmanTreeNode_s* root)
{
	if(root == NULL) return 0;
	kadenzlib_deconsturctTree(root->left);
	kadenzlib_deconsturctTree(root->right);
	free(root);
	return 0;
}



int kadenzlib_decodeSymbol(struct kadenbinary_bitReader_s* br, struct kadenzlib_huffmanTreeNode_s* tree)
{
	DEBUG_LOG("start decode symbol\n");
	if(tree == NULL) DEBUG_LOG("Tree is null\n");
	struct kadenzlib_huffmanTreeNode_s* node = tree;
	while (node->right != NULL || node->left != NULL)
	{
		char bit = kadenbinary_readbit(br);
		DEBUG_LOG("%d", bit);
		if(bit) node = node->right;
		else node = node->left;
		if(node == NULL) DEBUG_LOG("node is NULL\n");
	}
	DEBUG_LOG("\nend decode symbol %d\n", node->symbol);
	return node->symbol;
}

//converts a list of bit lengths with it alphabet in to a tree
int kadenzlib_blListToTree(int* bl, int* alphabet, int numberOfSymbols, struct kadenzlib_huffmanTreeNode_s** root)
{
	//find the longest bl needed
	int maxBits = 0;
	for(int i = 0; i < numberOfSymbols; i++)
	{
		if(bl[i] > maxBits) maxBits = bl[i];
	}
	DEBUG_LOG("maxBits: %d\n", maxBits);

	//create arrays to store the number of codes for each bit length and the next code of that bit length
	int* blCount = (int*)malloc(sizeof(int)*(maxBits+1));
	unsigned int* nextCode = (unsigned int*)malloc(sizeof(unsigned int)*(maxBits+1));
	if(blCount == NULL || nextCode == NULL)
	{
		ERROR_LOG(stderr, "ERROR: kadenzlib_blListToTree failed to allocate memory\n");
		return 1;
	}
	
	//count how many of each length bl apear in bl
	for(int i = 0; i < maxBits+1; i++)
	{
		int sum = 0;
		for(int j = 0; j < numberOfSymbols; j++)
		{
			if(bl[j] == i && i != 0) sum++;
		}
		blCount[i] = sum;
	}
	
	//set the next code for each bit length
	//next_code = { 0, 0 }
	nextCode[0] = 0;
	nextCode[1] = 0;
	for(int i = 2; i < maxBits+1; i++)
	{
		nextCode[i] = ((nextCode[i-1] + (unsigned int)blCount[i-1]) << 1);
	}
	
	//build the tree
	for(int i = 0; i < numberOfSymbols; i++)
	{
		if(bl[i] != 0)
		{
			kadenzlib_treeInsert(root, nextCode[bl[i]], bl[i], alphabet[i]);
			nextCode[bl[i]]++;
		}
	}
	
	
	//clean up
	free(blCount);
	free(nextCode);
	return 0;
}



int kadenzlib_printTree(struct kadenzlib_huffmanTreeNode_s* root, unsigned int path)
{
	if(root == NULL) return 0;
	if(root->symbol != -1) DEBUG_LOG("node 0x%x: %d\n", root->symbol, path);
	kadenzlib_printTree(root->left, path << 1);
	kadenzlib_printTree(root->right, (path << 1)+1);
	return 0;
}

