#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "kadenimgpng.h"
#include "kadenzlib.h"

#define CLEAR		printf("\e[1;1H\e[2J")



int main(int argc, char ** argv)
{
	/*
	if(argc != 2) {
		printf("Usage: %s <png file>\n", argv[0]);
		return 1;
	}
	struct pngData_s* png1 = NULL;
	kadenimgpng_loadPNG(argv[1], png1);
	*/
	/*
	printf("\n\n\n\n\n");
	FILE *fp;
	unsigned long long filesize = 0;
	unsigned char *buf = NULL;
	

	//find the file size
	if( (filesize = kadenimgpng_fileSize("samplecomp.zlib")) == 0)
	{
		fprintf(stderr, "ERROR kadenimgpng_loadPNG: failed fileSize %s\n", "samplecomp.zlib");
		return 0;
	}
	
	//open the file
	fp = fopen("samplecomp.zlib", "r");
	if(!fp) {
		fprintf(stderr, "ERROR kadenimgpng_loadPNG: failed to fopen %s\n", "samplecomp.zlib");
		return 0;
	}
	
	//allcate a buffer for the file data
	buf = (unsigned char *)malloc(filesize);
	if(!buf)
	{
		fprintf(stderr, "ERROR kadenimgpng_loadPNG: Couldn't allocate memory\n");
		return 0;
	}
	
	//copy the file into buffer
	unsigned long long bufsize = fread(buf, 1, filesize, fp);
	
	printf("close file\n");
	
	if(fclose(fp) != 0)
	{
		fprintf(stderr, "ERROR kadenimgpng_loadPNG: failed to fclose %s\n", "samplecomp.zlib");
		free(buf);
		return 0;
	}
	
	char* test = NULL;
	char* test1 = NULL;
	int testlen = kadenzlib_decompress(buf, &test, bufsize);
	printf("length: %d\n", testlen);
	test1 = (char*)malloc(testlen+1);
	printf("after mal\n");
	if(test == NULL) printf("what hte f\n");
	//memcpy(test1, test, testlen);
	printf("after memcpy\n");
	//test1[testlen] = '\0';
	test[testlen] = '\0';
	printf("here\n");
	printf("Test: %s\n", test);
	*/
	
	
	struct kadenbinary_bitReader_s* br = kadenBINARY_NEWBITREADER;
	kadenbinary_openFile(br, "samplecomp.zlib");
	kadenbinary_hexdump(br, 'a');
	kadenbinary_bindump(br, 'a');
	printf("%d\n", kadenbinary_readbits(br, 4));
	printf("%d\n", kadenbinary_readbits(br, 4));
	printf("%d\n", kadenbinary_readbits(br, 5));
	printf("%d\n", kadenbinary_readbits(br, 1));
	printf("%d\n", kadenbinary_readbits(br, 2));
	return 0;
}



