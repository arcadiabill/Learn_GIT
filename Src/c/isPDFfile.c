#include <stdio.h>
#include <stdlib.h>		// exit() prototype
#include <string.h>

int isPDFfile(const char *PDFfile);

int
main()
{
   char file[] = "e:\\downloads\\compression.pdf";

   if(isPDFfile(file))
   {
      printf("%s seems to be a pdf file.\n", file);
   }
   else
   {
      printf("%s doesn't seem to be a pdf file\n", file);
   }
}
/*------------------------------------------------- FileName.c -------
 | Function: isPDFfile(const char* PDFfile)
 | Author  : william h robertson
 |
 | Purpose : Get first 12 bytes of a file to determine if PDF file.
 |
 | Params  : char *PDFfile - File name to check
 |
 | Returns : 0 - If not doesn't have %PDF- as first 5 bytes or %%EOF
 |               as the last 5 bytest.
 |           1 - If file appears to be a pdf file
 |
 | Usage   : pdf = isPDFfile( char * PDFfile);
 |
 | Notes   : Function limited to naive checking. Does not verify
 |           that the file has the correct structure.
 |
 | --Ver--  ---Date---  ----By----  ---Description of the Change---
 |     0    12-26-2016      whr     Initial release
 |
 *------------------------------------------------------------------*/
#define TRUE  1
#define FALSE 0

int
isPDFfile(const char *PDFfile)
{
   FILE *input;
   char line[6];             // for %PDF- or %%EOF char strings

   if((input = fopen(PDFfile, "rb")) == NULL)
   {
      fprintf(stderr, "Couldn't Open: %s\n", PDFfile);
      return 0;
   }

   fread(line, 5, 1, input);
   if(strncmp(line, "%PDF-", 5))
   {  // Not a PDF return 0
      fclose(input);
      return 0;
   }

   if(fseek(input, -6, SEEK_END) == -1)  // -6 since last char is 0A
   {
      fprintf(stderr, "Seek to file end failed for file: %s\n", PDFfile);
      fclose(input);
      return 0;
   }

   fread(line, 5, 1, input);
   fclose(input);
   if(strncmp(line, "%%EOF", 5)) return 0;  // Not a PDF file

   return 1;
}
