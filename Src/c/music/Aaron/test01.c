#include <stdio.h>
#include <stdlib.h>   // For exit()
#include <strings.h>

#define DEFAULT "gMusic.txt"
#define LENLINE 260

void   usage(char *filename);
size_t SpacesBefore(const char *string);
int    checkParen(char *line);

int
main(int argc, char *argv[])
{
   char   filename[LENLINE+1] = {0};      // Maximum len initialized to nulls
   size_t lenName = 0;
   size_t lenLine = 0;
   FILE  *fHandle;

   system("cls");                   // Noncompliant Code -- I know
   puts("\nCheckParens  Rev 01 2017-08-26\n");

   if(argc != 2){
      lenName = strlen(DEFAULT);

      if(lenName > LENLINE){
         puts("Something bizaar: length of default file > 259 chars");
         exit(EXIT_FAILURE);
      }

      strncat(filename, DEFAULT, lenName);
      usage(filename);
   }
   else{
      lenName = strlen(argv[1]);
      if(lenName > LENLINE){
         puts("Something bizaar: length of default file > 259 chars");
         exit(EXIT_FAILURE);
      }
      strncat(filename, argv[1], lenName);
   }

   /* Try to open the file listing the albums */
   if((fHandle = fopen(filename, "r")) == NULL){
      printf("  Error: Could not open the file: <%s>."
             " Returning to windows.\n", filename);
      exit(EXIT_FAILURE);
   }

   /* Start reading the file checking for errors */
   while(fgets(filename, LENLINE, fHandle) != NULL){
      if(SpacesBefore(filename) != 4)
         continue;
      lenLine = strlen(filename);
      filename[--lenLine] = '\0';     // Remove newLine char
      printf("Length:%3d %3d <%s>\n", lenLine, checkParen(filename), filename);
   }

   if( fclose(fHandle)){
      puts("File didn't close properly!\n");
      exit(EXIT_FAILURE);
   }

   puts("File closed normally\n");
   return 0;
}


/* -------------------------------------------------------------------
 * Show Usage
 * -------------------------------------------------------------------
*/
void
usage(char *filename)
{
  if(!filename)
  {
     puts("Error: Filename was NULL -- this should never happen");
     exit(EXIT_FAILURE);
  }

  printf("Usage: checkParens [filename]"
       "\n   Checks that the albums created by PrintDir have their"
       "\n   bit rate at the end of the album name. The bit rate can"
       "\n   be of the form 'album name  (256)' where the value in"
       "\n   parentheses is a bit rate, flac, dts, etc");

   printf("\n\nFile name not given, so using: %s as filename\n", filename );
}


/* -------------------------------------------------------------------
 * Check if bit rate at end of string -- album name  (flac) or
 *                                       something similar (128)
 * -------------------------------------------------------------------
 */
int checkParen(char *line)
{
   static int i = 0;
   char  *chr;
   size_t len = strlen(line);
   
   if(!len){
      fputs("Line length is zero!", stderr);
      exit(EXIT_FAILURE);
   }

   /* see if last char is a ')' */
   if(line[len - 1] != ')'){
      fputs("Last char on line wasn't a ')'", stderr);
//      exit(EXIT_FAILURE);
      return 0;
   }

  if( !(chr = strrchr(line, '('))){
     fputs("Didn't find the '(')", stderr);
     exit(EXIT_FAILURE);
  }
  
  if( (line - chr) + len > 6){
     fputs(line, stderr);
  }

  return (line - chr) + len;
}
