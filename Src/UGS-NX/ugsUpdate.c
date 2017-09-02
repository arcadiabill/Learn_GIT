/*-------------------------------------------------- ugsUpdate.c -----
 | Program : ugsUpdate
 | Author  : william h robertson
 |
 | Purpose : Update files for Ugs graphics programs
 | Returns : EXIT_SUCCESS or aborts & returns EXIT_FAILURE
 | Usage   : UgsUpdate
 | Requires: addPathSprtr()                 isAdministrator()
 |           copyFile()                     skipComments()
 |           doesFileExist()                trimLine()
 |           errorExit()                    ugsHeader()
 |           fixPaths()                     verifyFiles()
 |           getFilesize()                  ugsUpdate.txt
 | Notes   : Program requires a response file with the update files.
 |           Initial lines beginning with a '#' are ignored allowing
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
#include <stdlib.h>		// exit() prototype, _MAX_PATH & _MAX_DIR
#include <string.h>     //           _MAX_PATH=260 & _MAX_DIR=256

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
FILE *skipComments(const char *responFile);
int   trimLine(char *Line);
void  ugsHeader(const char *PgmName);
int   verifyFiles(FILE *ptr_in, char *sourcePath, char *destPath, int RQD);

int
main(int argc, char *argv[])
{
   FILE *ptr_in;
	char destPath[_MAX_PATH + 1];
	char destFile[_MAX_PATH + 1];
	char sourcePath[_MAX_PATH + 1];
	char sourceFile[_MAX_PATH + 1];
  	char Line[_MAX_PATH + 1];
	int  nFiles = 0;
	int  RQD    = 1;	   // 0 - dest file not required, 1 - is required
						      // Both source & destination files are required
                        
   // Check command line to see if Administrator Mode is required
	// This will let the program run although it won't allow updating
   // the files in the Program Files directory. Useful for checking.
   
   if(argc > 1){
      RQD = 0;   // Anything on cmd line defeats Admin Required rule
   }
   isAdministrator(RQD);
	ugsHeader(argv[0]);

   /* skipComments() Reads the Response file skipping the comments
      Positions the filepointer to the 1st data item after comments
      1st Item: Common subdirectory of the source files
      2nd Item: Common subdirectory of the destination files
   */
	ptr_in  = skipComments(FILE_NAME);
	fgets(sourcePath, _MAX_DIR, ptr_in);	// Get Source Directory
	fgets(destPath  , _MAX_DIR, ptr_in);	// Get Dest   Directory
   
   /* Check sourcePath & destPath for errors - Correct them if possible
      These paths must have all trailing spaces, new lines, etc removed
      The source path can't be the OS path, that is C:
   */
   fixPaths(sourcePath, destPath);
   
	// Verify that all necessary files exist
	nFiles = verifyFiles(ptr_in, sourcePath, destPath, RQD);
   printf("%d Files found - Copy them to proper dirs\n", nFiles);
   
	nFiles = 0;     // Response file is in position
   while (fgets(Line, _MAX_PATH, ptr_in) != NULL)
	{
		// Generate Source & Dest Filenames
      trimLine(Line);        // Remove trailing \n, spaces, etc.
		sourceFile[0] = destFile[0] = '\0';
		strncat(sourceFile, sourcePath, _MAX_DIR);
		strncat(sourceFile, Line,       _MAX_PATH - strlen(sourceFile));

		strncat(destFile, destPath, _MAX_DIR);
		strncat(destFile, Line,     _MAX_PATH - strlen(destFile));
		copyFile(destFile, sourceFile);       // Aborts on any failure
		printf("%2d Updated %s\n", ++nFiles, destFile );
	}

	fclose(ptr_in);
   fprintf(stderr, "Press [Enter] key to return to OS");
   getchar();
   
   exit(EXIT_SUCCESS);
}
