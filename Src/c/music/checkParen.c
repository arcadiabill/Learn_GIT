#include <stdio.h>
#include <strings.h>

#define MAX_LINE  120
#define DEFAULT_FILE  "gMusic.txt"

int SpacesBefore(char *str);

int
main(int argc, char * argv[])
{
   FILE *in;
   char line[MAX_LINE];
   int  nLen = 0;
   int  nAlbums = 0;
   int  nErrors = 0;

   if(argc == 2){
      if((in = fopen(argv[1], "r")) == NULL){
         printf("Error opening %s\n", argv[1]);
         return 1;
      }
   }
   else{
      if((in = fopen(DEFAULT_FILE, "r")) == NULL){
         printf("Error opening %s\n", DEFAULT_FILE);
         return 1;
      }
   }

   printf("\ncheckParen  Rev 01  2017-07-30\n\n  Music input file opened.\n");

   while(fgets(line, MAX_LINE, in) != NULL)
   {
      if(SpacesBefore(line) != 4)
         continue;
      ++nAlbums;
      nLen = strlen(line);
      if((char) line[nLen-2] != ')'){
         printf("  Album#:%5d %s", nAlbums, line);
         ++nErrors;
      }
   }

   printf("\nNumber errors: %5d", nErrors);
   printf("\nNumber albums: %5d", nAlbums);
   fclose(in);
   return 0;
}
