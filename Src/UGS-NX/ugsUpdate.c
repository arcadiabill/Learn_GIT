/*-------------------------------------------------- ugsUpdate.c -----
 | Program : ugsUpdate
 | Author  : william h robertson
 |
 | Purpose : Update files for Ugs graphics programs
 | Params  : Line:      The line to append the character on
 |           character: The character to append
 | Returns : EXIT_SUCCESS or aborts & returns EXIT_FAILURE
 | Usage   : UgsUpdate
 | Requires: addPathSprtr()                 isAdministrator()
 |           copyFile()                     skipComments()
 |           doesFileExist()                trimLine()
 |           errorExit()                    ugsHeader()
 |           fixPaths()                     verifyFiles()
 |           getFilesize()                  ugsUpdate.txt
 | Notes   : Program requires a response file with the update files.
 |           The file skips lines beginning with a '# '. This allows
 |           the response file to be self definning.
 |           1st line after the comments is the common dir of sources
 |           2nd line is the common dir of the destination
 |           Remaining lines are the subdirs\fileNames to be updated.
 | Example : File: UgsUpdate.txt
 |           # comment lines (for file: UgsUpdate.txt)
 |           # more comment lines, after comments common source dir
 |           x:\yourDir\...\NX-10\  <--- Location of your update
 |           c:\Program Files\Siemens\NX-10\
 |           CATIAV5\pscatiav5\jt_catiav5.exe
 |           DRAFTING\layout\ideasgateway\ideas\nxlic.dll
 |           ... rest of the files to be updated.
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>		// exit() prototype
#include <string.h>

#define BUFF 1024
#define true    1
#define false   0
#define FILE_NAME "ugsUpdate.txt"

// Routines needed by program
int   addPathSprtr(char *Line);
void  copyFile(char *source, char *dest);
int   doesFileExist(const char* filename);
void  fixPaths(char *sourcePath, char *destPath);
long  getFilesize(const char* filename);
void  isAdministrator(int RQD);
FILE *skipComments(char *responFile);
int   trimLine(char *Line);
void  ugsHeader(char *PgmName);
int   verifyFiles(FILE *ptr_in, char *sourcePath, char *destPath, int RQD);

int
main(int argc, char *argv[])
{
   FILE *ptr_in;
	char destPath[BUFF];
	char destFile[BUFF];
	char sourcePath[BUFF];
	char sourceFile[BUFF];
  	char Line[BUFF];
	int  nFiles = 0;
	int  RQD    = 1;	   // 0 - dest file not required, 1 - is required
						      // Both source & destination files are required
                        
   // Check command line to see if Administrator Required is required
	// This will let the program run although Windows won't allow writting
   // the files to the Program Files directory. Useful for checking
   
   if(argc > 1){
      RQD = 0;   // Anything on cmd line defeats Admin Required rule
   }
   isAdministrator(RQD);
	ugsHeader(argv[0]);

   /* skipComments() Opens the Response file and skips the comment records
      It leaves the filepointer at the 1st data item
      1st Item: Common subdirectory of the source files
      2nd Item: Common subdirectory of the destination files
   */
	ptr_in  = skipComments(FILE_NAME);
	fgets(sourcePath, BUFF, ptr_in);	// Get Source Directory
	fgets(destPath  , BUFF, ptr_in);	// Get Dest   Directory
   
   /* Check sourcePath & destPath for errors - Correct them if possible
      These paths must have all trailing spaces, new lines, etc removed
      The source path can't be the OS path, that is C:
   */
   fixPaths(sourcePath, destPath);
   
	// Verify that all necessary files exist
	nFiles = verifyFiles(ptr_in, sourcePath, destPath, RQD);
   printf("%d Files found - Copy them to proper dirs\n", nFiles);
   
	nFiles = 0;     // Response file is in position
   while (fgets(Line, BUFF, ptr_in) != NULL)
	{
		// Generate Source & Dest Filenames
      trimLine(Line);        // Remove trailing \n, spaces, etc.
		sourceFile[0] = destFile[0] = '\0';
		strncat(sourceFile, sourcePath, BUFF);
		strncat(sourceFile, Line  , BUFF);

		strncat(destFile, destPath, BUFF);
		strncat(destFile, Line  , BUFF);
		copyFile(destFile, sourceFile);       // Aborts on Failure
		printf("%2d Updated %s\n", ++nFiles, destFile );
	}

	fclose(ptr_in);
   fprintf(stderr, "Press [Enter] key to return to OS");
   getchar();
   
   exit(EXIT_SUCCESS);
}
