#include <stdio.h>

int isFlac( char *);

int main()
{
    char line[1024];
    char flac[8];
    int  nPos;
    
    printf("\nReadText:\n");
    printf("   Reads text file: MusicFiles.txt which contains a listing of the music\n");
    printf("   directory & counts the number of CDs that are flac and the ones that aren't\n\n");
    
    FILE *fp = fopen("MusicFiles.txt","r");

    if( fp == NULL )
       printf("\nCan't find file: MusicFiles.txt\n\n");
       return 1;

fgets(line, 1024, fp);
puts(line);

    while( fgets(line,1024,fp) )
    {
//       nPos = isFlac(line);
//       flac[0] = line[nPos-7];
//       flac[1] = line[nPos-6];
//       flac[2] = line[nPos-5];
//       flac[3] = line[nPos-4];
//       flac[4] = line[nPos-3];
//       flac[5] = line[nPos-2];
//       flac[6] = '\0';
       if( strcmp( flac, "(flac)"))
         printf("%s", line);
       else
         printf(":%s:");
    }

    return 0;
}

int isFlac(char *line)
{
   int nPos = 0;
   while( line[nPos] )
      nPos++;
   
   return nPos;
}