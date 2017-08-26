/*------------------------------------------------ verifyFiles.c -----
 | Function: verifyFiles(FILE *ptr_in, char *sourcePath,
 |                                     char *destPath, int required)
 | Author  : william h robertson
 |
 | Purpose : Verify the required files are all present
 | Params  : ptr_in    : File pointer to read input data
 |           sourcePath: Name of the source path
 |           destPath  : Destination path where files are copied to
 |           required  : 1 means same file is required in both dirs
 |                       0 means only source file has to exist
 | Returns : nFiles - The number of files it found
 | Usage   : nFiles = verifyFiles(ptr_in, source, dest, required);
 | Requires: <stdio.h>                 doesFileExist(filename)
 |           <string.h>                errorExit(Msgt)
 |           <stdlib.h>                trimLine(Line)
 | Notes   : Function limited to 32-bit filesize (around 4GB)
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF 1024

int  doesFileExist(const char *filename);
void errorExit(char *msg);
int  trimLine(char *Line);

int
verifyFiles(FILE *ptr_in, char *sourcePath, char *destPath, int required)
{
   char Line[BUFF];
	char sourceFile[BUFF];
	char destFile[BUFF];
	int  nFiles   = 0;
	int  nErrors  = 0;
	long filePos  = ftell(ptr_in);    // Save position for repositioning

	while (fgets(Line, BUFF, ptr_in) != NULL)
	{
		trimLine(Line);       // Remove trailing \n
		
      //Create full path for source & destination
      sourceFile[0] = destFile[0] = '\0';
      strncat(sourceFile, sourcePath, BUFF);
		strncat(sourceFile, Line      , BUFF);

		strncat(destFile, destPath, BUFF);
		strncat(destFile, Line    , BUFF);
		if(doesFileExist(sourceFile)) ++nFiles;
		else {
			++nErrors;
			printf(" Source File: %s Missing!\n", sourceFile);
		}

		if(required && !doesFileExist(destFile)) {
			++nErrors;
			printf(" Destination File %s Missing\n", destFile);
		}
	}

	if(nErrors)
	{
		sprintf(Line, "There were %d Errors, EXITING program, "
                  "no files were copied", nErrors);
      errorExit(Line);
	}

	fseek(ptr_in, filePos, SEEK_SET);		// Restore file position

   return nFiles;
}
