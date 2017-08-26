#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define  MAX_LINE  120
#define  ARTIST    "Artist.txt"
#define  LORES     "LoRes.txt"
#define  HIRES     "HiRes.txt"


bool isHiRes(char *str);
bool getArtist(FILE *hArtist, char * artist);
bool getAlbum(FILE *hArtist, char * album);
int  SpacesBefore(char *);
int  putArtist(FILE *hArtist, char *str);
int  putAlbums(FILE *hArtist, int nAlbums);

int
main(int argc, char *argv[])
{
	FILE * hMusicIn;			// Music File to read
	FILE * hArtist;				// Write Artists in collection
	FILE * hHiRes;				// Write flac albums here
	FILE * hLoRes;				// Write mp3  albums here
	char  artist[MAX_LINE];
	char  lowArt[MAX_LINE] = " ";
	char  higArt[MAX_LINE] = " ";
	char  album[MAX_LINE];
	char *HiResPos = 0;
	int   nArtist  = 0;
	int   nHiRes   = 0;
	int   totHi    = 0;
	int   nLoRes   = 0;
	int   totLo    = 0;

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

	if((hArtist = fopen(ARTIST, "w")) == NULL)
	{
		printf("Error opening output file: Artist.txt\n");
		return 1;
	}
	if((hHiRes = fopen(HIRES, "w")) == NULL)
	{
		printf("Error opening output file: HiRes.txt\n");
		return 1;
	}

	if((hLoRes = fopen(LORES, "w")) == NULL)
	{
		printf("Error opening output file: LoRes.txt\n");
		return 1;
	}

/* Main Loop to process the Music file created by PrintDir
	
	getArtist() reads the file line by line until it finds
	the next artists. The routine returns false and the 
	loop exits when there are no more artists to process.
*/
	fprintf(hArtist, "-No-  Hi  Lo  Artist's Name\n");
	while( getArtist(hMusicIn, artist) )
	{
		++nArtist;			// Keep track of the # artists
		nHiRes = nLoRes = 0;
		while(getAlbum(hMusicIn, album))
		{
			if((HiResPos = strstr(album, "(flac)")) > 0)
			{
				++nHiRes;
				++totHi;
				*HiResPos = '\0';  // Basically removes (flac)
				if(strcmp(higArt, artist) != 0)
				{
					fprintf(hHiRes, "%s\n", artist);
					strcpy(higArt, artist);
				}
				fprintf(hHiRes, "%s\n" , album);
			}
			else
			{
				++nLoRes;
				++totLo;
				if(strcmp(lowArt, artist) != 0)
				{
					fprintf(hLoRes, "%s\n", artist);
					strcpy(lowArt, artist);
				}
				fprintf(hLoRes, "%s", album);
			}
		}
		fprintf(hArtist, "%4d%4d%4d  %s\n", nArtist, nHiRes, nLoRes, artist);
	}
	printf("Number LoRes Albums:%5d\n", totLo);
	printf("Number HiRes Albums:%5d\n", totHi);

	fprintf(hLoRes, "Number Lo-Res albums:%5d\n", totLo);
	fprintf(hHiRes, "Number Hi-Res albums:%5d\n", totHi);
	fprintf(hArtist,"Number Lo-Res albums:%5d\n", totLo);
	fprintf(hArtist,"Number Hi-Res albums:%5d\n", totHi);
	fprintf(hArtist,"Total Number  albums:%5d\n", totLo+totHi);
	fclose(hArtist);
	fclose(hMusicIn);
	fclose(hHiRes);
	fclose(hLoRes);

	return 0;
}


#if 0
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
#endif

int putAlbums(FILE *hArtist, int nAlbums)
{
	static int nLines = 1;

	fprintf(hArtist, "% 5d\n", nAlbums);
	if(nLines % 5 == 0) fprintf(hArtist, "\n");
	nLines++;

	return 0;
}

/* -------------------------------------------------------------
 * bool getArtist(FILE *hMusicIn, char *artist)
 *
 * Purpose: Get next artist in File pointed to by hMusicIn.
 *
 * Version: 1.0 11/30/2015
 *
 * Returns: true & the Artist found using char pointer *artist
 *          false if no artist was found.
 *
 * Note   : Requires the Music File format to have 2-blank
 *          chrs at the beginning of the character string to
 *          indicate an Artist. Four chrs represents an album.
 * -----------------------------------------------------------*/
bool getArtist(FILE *hMusicIn, char *artist)
{
	char  str[MAX_LINE];
	char *ptr;
	int	nSpacesBefore = 0;
	int	nLen = 0;

	while(nSpacesBefore != 2)
	{
		if(fgets(str, MAX_LINE, hMusicIn) == NULL)
			return false;
		nSpacesBefore = SpacesBefore(str);
	}
	// Copy Artist into artist[] stripping off the {whr} string
	if((ptr = strstr(str, "  {whr}")) != NULL)
	{
		*ptr = '\0';
		nLen = strlen(str);
	}
	else  // Strip off \n
	{
		nLen = strlen(str) - 1;
		if(str[nLen] == '\n')
			str[nLen] = '\0';
	}
	strncpy(artist, &str[2], nLen );
	return true;
}


/* -------------------------------------------------------------
 * isHiRes( char * str)
 *
 * Purpose: Determine if the Album is High Resolution. If so, it
 * has: "(flac)" at the end of the string.
 *
 * Version: 1.0 11/30/2015
 *
 * Returns: true if album is a High Resolution album or
 *          false otherwise.
 * -----------------------------------------------------------*/
bool isHiRes( char *str)
{
	return ( strstr(str, "(flac)") > 0 ) ? true : false;
}


/* -------------------------------------------------------------
 * SpacesBefore( char *line)
 *
 * Purpose: Determine number of spaces at front of a string.
 *
 * Version: 1.0 11/30/2015
 *
 * Returns: Number of blank spaces at the string's beginning.
 * -----------------------------------------------------------*/
int SpacesBefore(char *str)
{
	int nSpaces  = 0;

	while(str[nSpaces] == ' ')
		++nSpaces;

	return nSpaces;
}

/* -------------------------------------------------------------
 * bool getAlbum(FILE *hMusicIn, char *album)
 *
 * Purpose: Get the next album for the current artist.
 *
 * Version: 1.0 11/30/2015
 *
 * Returns: true if an album was found. The album is copied
 *          into the space provided by char *album.
 *
 *          false if encounters EOF or finds next artist.
 *          If it finds the next artist, the file is rewound
 *          to the artist's position so the getArtist reoutine
 *          can find the next artist.
 *
 * Note   : Requires the Music File format to have 4-blank
 *          chrs at the beginning of the character string to
 *          indicate an album. The routine returns when it
 *          finds the next album or the next artist.
 * -----------------------------------------------------------*/
bool getAlbum(FILE *hMusicIn, char *album)
{
	bool rtnVal  = false;
	char str[MAX_LINE];
	int  nSpacesBefore = 0;
	long filePos = 0;

	while(nSpacesBefore != 2 && nSpacesBefore != 4)
	{
		if(fgets(str, MAX_LINE, hMusicIn) == NULL)
		{
			return false;
		}
		nSpacesBefore = SpacesBefore(str);
	}

	if(nSpacesBefore == 2)
	{
		// Found the next Artist, reposition file
		filePos = ftell(hMusicIn);
		filePos -= (strlen(str) + 1);
		if(fseek(hMusicIn, filePos, SEEK_SET) != 0)
		{
			printf("Error in getAlbum: fseek is NULL\n");
			exit(1);
		}
	}
	else
	{
		rtnVal = true;
		strncpy(album, str, MAX_LINE - 2);
	}

	return rtnVal;
}
