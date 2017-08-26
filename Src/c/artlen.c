#define  MAX_LINE  120

#include <stdio.h>
#include <string.h>

#define  MAX_LINE  120

int
main(int argc, char * argv[])
{
   int  nLength  = 0;
   int  nSum     = 0;
   int  nArtists = 0;
   int  nMax     = 0;
   int  nMin     = 120;
   double avg    = 0.0;
   char str[MAX_LINE];
   char maxLine[MAX_LINE];
   char minLine[MAX_LINE];

   FILE *fIn = fopen("artist.txt", "r");
   if(fIn == NULL)
   {
      printf("Error: Couldn't open artist.txt\n");
      return 1;
   }

   while( fgets (str, MAX_LINE, fIn)!=NULL )
   {
      nLength = strlen(str);
      if(nLength > nMax)
      {
         nMax  = nLength;
         strncpy(maxLine, str, nMax);
         maxLine[nLength] = '\0';
      }

      if(nLength < nMin)
      {
         nMin = nLength;
         strncpy(minLine, str, nMin);
         minLine[nLength] = '\0';
      }

      nSum   += nLength;
      ++nArtists;
   }
   avg = (double)nSum/nArtists;
   printf("#Artists  : %5d\n", nArtists);
   printf("#Chars    : %5d\n", nSum);
   printf("AvgLineLen: %5.1f\n", avg);
   printf("Min Chars : %5d  %s", nMin, minLine);
   printf("Max Chars : %5d  %s\n", nMax, maxLine);
   return 0;
}