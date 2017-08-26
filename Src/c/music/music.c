#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define  MAX_LINE  120

bool isFlac(char *str);
int  SpacesBefore(char *);
int  putArtist(FILE *hArtist, char *str);
int  putAlbums(FILE *hArtist, int nAlbums);

int
main(int argc, char *argv[])
{
	FILE * hMusicIn;			// Music File to read
	FILE * hArtist;			// Artists in collection
	FILE * hHiRes;				// Write flac albums here
	FILE * hLoRes;				// Write mp3  albums here
	char  str[MAX_LINE];
	char  artist[MAX_LINE];
	char  LoResArtist[MAX_LINE] = "Current Artist";
	char  HiResArtist[MAX_LINE] = "Current Artist";
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

	if((hLoRes = fopen("LoRes.txt", "w")) == NULL)
	{
		printf("Error opening output file: LoRes.txt\n");
		return 1;
	}

	while( fgets(str, MAX_LINE, hMusicIn) != NULL )
	{
		switch( SpacesBefore(str) )				// Only interested in 2 Spaces = Artist
		{													//                    4 Spaces = Album
		case 2:											// A New Artist
			++nArtist;
			strncpy(artist, &str[2], MAX_LINE-1);
			nAlbums = nHiRes + nLoRes;
			if(nArtist > 1) putAlbums(hArtist, nAlbums-nOld);
			nOld = nAlbums;
			putArtist(hArtist, str);
			break;
		case 4:											// A New Album
			if( isFlac(str) )
			{
				++nHiRes;
				if(strcmp(HiResArtist, artist) != 0)
					fprintf(hHiRes, artist);
				fprintf(hHiRes, str);
				strcpy(HiResArtist, artist);
			}
			else
			{
				++nLoRes;
				if(strcmp(LoResArtist, artist) != 0)
					fprintf(hLoRes, artist);
				fprintf(hLoRes, str);
				strcpy(LoResArtist, artist);
			}
			break;
		}
	}
	fprintf(hLoRes, "Number Lo-Res albums: %d\n", nLoRes);
	fprintf(hHiRes, "Number flac albums: %d\n"  , nHiRes);

	// Write number of albums for last artist
	fprintf(hArtist, "%5d\n", nHiRes + nLoRes - nOld);
	fclose(hArtist);
	fclose(hMusicIn);
	fclose(hHiRes);
	fclose(hLoRes);
	printf("Number LoRes Albums:%5d\n", nLoRes);
	printf("Number HiRes Albums:%5d\n", nHiRes);
	printf("Number of Artists  :%5d\n", nArtist);

	return 0;
}

int SpacesBefore(char *line)
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
	return ( strstr(str, "(flac)") > 0 ) ? true : false;
}

int putArtist(FILE *hArtist, char *str)
{
	char artist[61];
	int  nLength;

	strncpy(artist, str, 60);
	nLength = strlen(artist);
	if(artist[nLength - 1] == '\n')artist[nLength - 1] = ' ';

	artist[60] = '\0';
	while(nLength < 60)
	{
		artist[nLength] = ' ';
		nLength++;
	}
	fprintf(hArtist, "%s", &artist[2]);
	return 0;
}

int putAlbums(FILE *hArtist, int nAlbums)
{
	static int nLines = 1;

	fprintf(hArtist, "% 5d\n", nAlbums);
	if(nLines % 5 == 0) fprintf(hArtist, "\n");
	nLines++;

	return 0;
}
