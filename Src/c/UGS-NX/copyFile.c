 /*-------------------------------------------------- copyFile.c -----
 | Function: copyFile(char *dest, char *source)
 | Author  : william h robertson
 |
 | Purpose : Copy Source file to Destination (binary mode)
 | Params  : dest   : Destination file
 |           source : Source file
 | Returns : void
 | Usage   : copyFile(destFile, sourceFile);
 | Requires: <stdio.h>                 errorExit(msg)
 |           <string.h>                getFilesize(filename)
 |           <stdlib.h>
 | Notes   : Function limited to 32-bit filesize (around 4GB)
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    07-20-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>          // For system()
#define BUFF_LEN 4096

void errorExit(char *msg);
long getFilesize(const char *filename);

void
copyFile(char *dest, char *source)
{
	FILE *in, *out;
	long sourceSize;
	long destSize;
	long numRead ;
	long numWritten;
	char buffer[BUFF_LEN];

	// Remove Read only flag & Ck dest can be written to
   // File has spaces so file needs quotes: "filename"
  sprintf(buffer, "attrib -r \"%s\"\n", dest);   // Quote string
  system(buffer);
	if( (out = fopen(dest, "wb") ) == NULL){
      sprintf(buffer, "Can't open file: %s for writing.", dest);
		errorExit(buffer);
   }

	// Check to see if Source file is available for reading
	if( (in = fopen(source, "rb") ) == NULL){
      sprintf(buffer, "Can't open file: %s for reading.", source);
		errorExit(buffer);
	}

	sourceSize = getFilesize(source);   // Number bytes to copy

	// Copy Source File to Destination
	while( feof(in) == 0 )
	{
		memset(buffer, 0, BUFF_LEN);
		numRead    = fread(buffer, 1, BUFF_LEN, in);
		numWritten = fwrite(buffer, 1, numRead, out);
      if(numRead != numWritten) break;           // Read/Write Error
	}

	fflush(out);
	fclose(out);
	fclose( in);
   
	destSize = getFilesize(dest);
	if( destSize != sourceSize){
      sprintf(buffer, "Error copying %s to\n     %s", source, dest);
      errorExit(buffer);
   }
   
   // Replace read only attribute
   sprintf(buffer, "attrib +r \"%s\"\n", dest);
   system(buffer);
}
