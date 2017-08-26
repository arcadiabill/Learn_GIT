#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define  MAX_LINE  120

bool isFlac(char *str);
int  SpaceBefore(char *);
int  putHiRes (FILE *hHiRes,  char *str, char *artist);
int  putLoRes (FILE *hLoREs,  char *str, char *artist);
int  putArtist(FILE *hArtist, char *str, int  nAlbums);

int
main(int argc, char *argv[])
{
   FILE * hMusicIn;			// Music File to read
   FILE * hArtist;			// Artists in collection
   FILE * hHiRes;				// Write flac albums here
   FILE * hLoREs;				// Write mp3  albums here
   char  str[MAX_LINE];
   char  artist[MAX_LINE];
   int   nSpaces = 0;
   int   nHiRes  = 0;
   int   nLoRes  = 0;
   int   nArtist = 0;
   int   nAlbums = 0;
   int   nOld    = 0;

   /* Insure argc = 2 and try to open file */
   if(argc != 2)
   {
      printf("Usage: %s <MusicFileName>\n\n", argv[0]);
      return 1;
   }

   if((hMusicIn =fopen(argv[1], "r")) == NULL)
   {
      printf("Error opening file %s\n\n", argv[1]);
      return 1;
   }

   if((hArtist = fopen("Artist.txt", "w")) == NULL)
   {
      printf("Error opening output file: Artist.txt\n");
      return 1;
   }
   if((hHiRes = fopen("HiRes.txt", "w")) == NULL)
   {
      printf("Error opening output file: HiRes.txt\n");
      return 1;
   }

   if((hLoREs = fopen("LoRes.txt", "w")) == NULL)
   {
      printf("Error opening output file: LoRes.txt\n");
      return 1;
   }

   while( fgets (str, MAX_LINE, hMusicIn)!=NULL )
   {
      if(strlen(str) < 3)
         continue;

      nSpaces = SpaceBefore(str);
      switch(nSpaces)
      {
      case 0:
         break;
      case 2:
         ++nArtist;
         nAlbums = nHiRes + nLoRes;
         nOld = putArtist(hArtist, str, nAlbums);
         strncpy(artist, &str[2], MAX_LINE-1);
         break;
      case 4:
         if(isFlac(str))
         {
            ++nHiRes;
            putHiRes(hHiRes, str, artist);
            break;
         }
         else
         {
            ++nLoRes;
            putLoRes(hLoREs, str, artist);
            break;
         }
      default:
         printf("Ignored:%s", str);
      }
   }
   fprintf(hLoREs, "Number Lo-Res albums: %d\n", nLoRes);
   fprintf(hHiRes, "Number flac albums: %d\n"  , nHiRes);

   // Write number of albums for last artist
   fprintf(hArtist, "  %d\n", nHiRes + nLoRes - nOld);
   fclose(hArtist);
   fclose(hMusicIn);
   fclose(hHiRes);
   fclose(hLoREs);
   printf("Number LoRes Albums:%5d\n", nLoRes);
   printf("Number HiRes Albums:%5d\n", nHiRes);
   printf("Number of Artists  :%5d\n", nArtist);

   return 0;
}

int SpaceBefore(char *line)
{
   int lineLen  = strlen(line);
   int nSpaces  = 0;

   for(nSpaces = 0; nSpaces < lineLen; nSpaces++)
   {
      if(line[nSpaces] != ' ')
         break;
   }
   return nSpaces;
}

bool isFlac( char *str)
{
   bool nFlac = false;   // Assume it's not a flac album

   if(strstr(str, "(flac)") > 0)
      nFlac = true;      // This is a flac album

   return nFlac;
}

int putArtist(FILE *hArtist, char *str, int nAlbums)
{
   static int nOld = 0;
   int  nLength    = strlen(str);

   if(nAlbums > 0)
      fprintf(hArtist, "  %d\n", nAlbums - nOld);

   str[nLength - 1] = '\0';
   fprintf(hArtist, "%s", &str[2]);
   nOld  = nAlbums;

   return nOld;
}

int putHiRes(FILE *hHiRes, char *str, char *artist)
{
   static char curArtist[MAX_LINE] = "Current Artist";
   static int  newArtist = 0;
   int nLength = strlen(str);

   if(strcmp(curArtist, artist) != 0)
   {
      strncpy(curArtist, artist, nLength);
      newArtist = 1;
      return 0;
   }

   if(newArtist == 1)
   {
      fprintf(hHiRes, curArtist);
      newArtist = 0;
   }
   fprintf(hHiRes, &str[2]);
   return 1;
}

int putLoRes(FILE *hLoREs, char *str, char *artist)
{
   static char curArtist[MAX_LINE] = "Current Artist";
   static int  newArtist = 0;
   int nLength = strlen(str);

   if(strcmp(curArtist, artist) != 0)
   {
      strncpy(curArtist, artist, nLength);
      newArtist = 1;
      return 0;
   }

   if(newArtist == 1)
   {
      fprintf(hLoREs, curArtist);
      newArtist = 0;
   }
   fprintf(hLoREs, &str[2]);
   return 1;
}
