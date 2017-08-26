#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define  MAX_LINE  120

bool isNewArtist(char * str);

int
main(int argc, char *argv[])
{
   FILE * hMusicIn;			 // Music File to read
   FILE * hArtistOut;		 // OutPut File
   char   artist[MAX_LINE]; // String to Hold Current artist
   char * fileOut = "artOut.txt";
   int    nArtists = 0;
	
   /* Insure argc = 2 and try to open file */
   if(argc != 2)
   {
      printf("Usage: %s <MusicFileName>\n\n", argv[0]);
      return 1;
   }

   if((hMusicIn = fopen(argv[1], "r")) == NULL)
   {
      printf("Error opening file %s\n\n", argv[1]);
      return 1;
   }

	if((hArtistOut = fopen(fileOut, "w")) == NULL)
	{
		printf("Error opening files %s\n\n", fileOut);
		return 1;
	}
	
	while( fgets(artist, MAX_LINE, hMusicIn) != NULL )
	{
		if(isNewArtist(artist))
		{
			printf("%3d %s\n", ++nArtists, artist);
		}
	}

	fclose(hMusicIn);
	fclose(hArtistOut);
	return 0;
}

/* ----------------------------------------------------- */
bool isNewArtist(char * str)
	{
		static char currArtist[MAX_LINE] = "Dummy Artist";
		char * nPos;
		
		if( (nPos = strstr(str, " -")) == NULL )
			return false;

		*(nPos) = '\0';

		if(strcmp(str, currArtist) != 0)
		{
			strncpy(currArtist, str, strlen(str)+1);
			return true;
		}
		
		return false;
	}
