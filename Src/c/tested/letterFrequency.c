/* cipher.c
 *
 * Purpose: Determine letter frequency of input file
 *
 */
#include <stdio.h>
#include <stdlib.h>
int compare (const void * a, const void * b);

int
main(int argc, char * argv[])
{
	int  letter;
	int  freq[26] = {0,0};
	FILE *in;
	
	if(argc < 2)
	{
		printf("Usage: cipher filename\n");
		return 0;
	}
	
	if((in = fopen(argv[1], "r")) == NULL)
	{
		printf("Couldn't open file: %s\n", argv[1]);
		return -1;
	}
	
	while((letter = fgetc(in)) != EOF)
	{
		letter -= 'a';
		if(letter >= 0 && letter <= 25)
		{
			++freq[letter];
		}
	};

	/* Print the Array */
	for(int i=0; i<26; ++i)
	{
		if(i%5 == 0)printf("\n");
		printf("%c: %3d  ", i+'a', freq[i]);
	}
	
	/* Put File Pointer back to beginning of File */
	fseek(in, 0, SEEK_SET);
	printf("\n");
	while ((letter = fgetc(in)) != EOF)
	{
		switch(letter){
		case 'r':
		  putchar('e');
		  break;
		case 'b':
		  putchar('t');
		  break;
		case 'm':
		  putchar('a');
		  break;
		case 'k':
		  putchar('o');
		  break;
		case 'j':
		  putchar('i');
		  break;
		case 'w':
		  putchar('n');
		  break;
		case 'i':
		  putchar('s');
		  break;
		case 'p':
		  putchar('h');
		  break;
		case 'u':
		  putchar('r');
		  break;
		case 'h':
		  putchar('d');
		  break;
		case 'd':
		  putchar('l');
		  break;
		case ' ':
		  putchar(' ');
		  break;
		default:
		  putchar('.');
		}
	}
	return 0;
}

int compare (const void * a, const void * b)
{
   return ( *(int*)b - *(int*)a );
}
