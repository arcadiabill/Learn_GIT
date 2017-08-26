#include <stdio.h>
#include <string.h>
#define  MAX_LINE  120

int
main(int argc, char *argv[])
{
   FILE *hMusicIn;			// Music File to read
   char  str[MAX_LINE];
	int   nHiRes = 0;
	
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
   while( fgets(str, MAX_LINE, hMusicIn) != NULL )
   {
		if( (str[0] == ' ') && (strstr(str, "(flac)") > 0 ) )
		{
			++nHiRes;
			printf("%s", str);
		}

   }
	printf("Number of HiRes: %d\n", nHiRes);
	return 0;
}