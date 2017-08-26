#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <string.h>

char pathSep;
int dirDepth( char *sString );

int main(int argc, char **argv)
{
	char *line;
	char full[MAX_PATH];
	int  nLength;
	
	line = _fullpath(full, ".", MAX_PATH);
	pathSep = strchr(line, '/')? '/': '\\';
	
	if(argc > 1)
	{
		line = _fullpath(full, argv[1], MAX_PATH);
	}
	nLength = strlen(line);
	printf("String: %s\n  Length: %d\n", line, nLength);
	printf("Directory Depth: %d\n", dirDepth(line));
	
	return 0;
}

int dirDepth( char *sString )
{
	char *strPtr = sString;
	int  nDepth = 0;
	
	while(( strPtr = strchr(strPtr, pathSep)) != NULL)
	{
		++nDepth;
		++strPtr;
	}
	
	return nDepth;
}
