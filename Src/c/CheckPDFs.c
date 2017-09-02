#define UNICODE
#define _UNICODE

#include <stdio.h>
#include <stdlib.h>		// exit() prototype
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <windows.h>

#define BUFF 1024
#define FILE_NAME "pdfFiles.txt"

using namespace std;

int  doesFileExists(const char* filename);

int main(int argc, char *argv[])
{
   FILE *pInput;                       // file handle for input file
   char line[BUFF];                    // Hold chars read from file
   char file[BUFF];                    // Hold fileName to parse
   int  found;                         // 1 if file exits, 0 otherwise
   int  nChars, nFiles, nFound, nMissing;
   time_t endTime, startTime;

   /* Use Default file is none give on command line */
   if(argc == 1) {
      strncpy(file, FILE_NAME, BUFF-1);
   } else {
      strncpy(file, argv[1], BUFF-1);
   }

   pInput = fopen(file,"r");
   if (!pInput) {
      printf("Couldn't open file: %s\n", file);
      system("pause");
      exit(EXIT_FAILURE);
   }

//   system("chcp 65001");               // Use utf-8
   time(&startTime);
   nFiles = nFound = nMissing = 0;
   while(fgets(line, BUFF, pInput) != NULL) {
      nChars = (unsigned) strlen(line) - 1;
      line[nChars] = '\0';		// Remove \n

      ++nFiles;
      found = doesFileExists(line);
      if(found) {
         ++nFound;
//         printf("Found  : %s\n", line);
      } else {
         ++nMissing;
         printf("%6d: Missing %s\n", nFiles, line);
      }

   }
   time(&endTime);
   fclose(pInput);
   printf("Total # Files :%5d\n", nFiles);
   printf("Number Opened :%5d\n", nFound);
   printf("Number Missing:%5d\n", nMissing);
   printf("Seconds to process input: %ld", (long)(endTime-startTime));
}

/*
 * Check if a file exist using stat() function
 * return 1 if the file exist otherwise return 0
 */
int doesFileExists(const char* filename)
{
   FILE *tmp;

   struct stat buffer;
   int exist = stat(filename, &buffer);
   if(exist == 0)
      return 1;		// File Exists
   else {
      // Try fopen
      if((tmp = fopen(filename, "rb encoding=utf-8")) != NULL) {
         fclose(tmp);

         // remove later -- didn't work
         printf("Does File Exist Experiment\n");
         printf("%s\n", filename);
         return 1;
      }

      // Try _wfopen()  -- didn't work
      if((tmp = _wfopen((const wchar_t *)filename, (const wchar_t*) "rb | _O_U8TEXT | _O_UTF8")) != NULL) {
         fclose(tmp);
         return 1;
      }
   }

   return 0;		// File Doesn't Exist or can't open
}


