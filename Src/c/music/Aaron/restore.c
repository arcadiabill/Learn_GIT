/* Restore: Add artist back to album
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>			// for exit()

#define BUFFER 1024			// Maximun length of input line -- probably < 80 chars

int main(int argc, char *argv[])
{
	FILE *fHandle;
	char  artist[BUFFER];
	char  line[BUFFER];
	char  temp[BUFFER];
	int   nLenLine;
	int   nLenArtist;
	
	if(argc == 1)
	{
		fprintf(stderr, "\nUsage: Restore filename\n"
		                  "       Where filename is a loRes.txt or HiRes.txt file\n");
		exit(EXIT_FAILURE);
	}
	
	if( (fHandle = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Error: couldn't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// Read file until no more text
	nLenArtist = 0;
	system("cls");
	while(fgets(line, BUFFER, fHandle) != NULL)
	{
		nLenLine = strlen(line);
		if(nLenLine > 1) line[nLenLine - 1] = '\0';		// Remove \n
		
		// Get New Artist if no spaces before text
		if(line[0] != ' ')
		{
			artist[0] = '\0';
			strncat(artist, line, BUFFER);
			nLenArtist = strlen(artist);
			if(nLenArtist > 1){
				artist[  nLenArtist] = ':';
				artist[++nLenArtist] = '\0';
			}
		}
		else
		{
			// An Album - cat to artist
			temp[0] = '\0';
			strncat(temp, artist, nLenArtist);
			strncat(temp,(char *)(line+2), nLenLine);		// temp should be artistName:  album
			printf("%s\n", temp);
		}
	}
	
	fclose(fHandle);
	
	exit(EXIT_SUCCESS);
}
