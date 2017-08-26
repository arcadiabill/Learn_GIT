/*----------------------------------------------- skipComments.c -----
 | Function: skipComments(char *fName)
 | Author  : william h robertson
 |
 | Purpose : Open filename & skip lines with # in 1st position
 | Params  : fName: filename to open & position past comment lines
 | Returns : File pointer & the file positioned on 1st real record
 | Usage   : filePointer = skipComments(fName);
 | Requires: <stdio.h>                 errorExit(msg)
 |           <stdlib.h>
 |           <string.h>
 | Notes   : Positions file pointer on 1st line not starting with #
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF 200            // Overkill the lines will be < 80 chars
#define true   1

void errorExit(char *msg);

FILE
*skipComments(char *responseFile)
{
   char Line[BUFF];
	long filePosOld = 0;
   FILE *fp = NULL;

   fp = fopen(responseFile,"r");
   if (!fp){
      sprintf(Line, "Couldn't open file: %s\n", responseFile);
		errorExit(Line);
	}

	// Read input file ignoring comment lines which begin with #
	while ( true )			// Loop forever or until EOF
	{
      filePosOld = ftell(fp);
		if(fgets(Line, BUFF, fp) == NULL) errorExit("Unexpected end of file");
		if(Line[0] != '#') break;	// End of comments break out of loop
	}

	fseek(fp, filePosOld, SEEK_SET);
   return fp;
}
