#include <stdio.h>
#include <stdlib.h>     // exit() prototype
#include <string.h>
#include <sys/stat.h>

#define BUFF 1024
#define FILE_NAME "nx-9.txt"

int  checkPrelims(char *PgmName);
int  doesFileExists(const char* filename);
int  SkipComments(FILE *ptr_in);
int  VerifyFiles(FILE *ptr_in, char *sourcePath, char *destPath);
int  copyFile(char *source, char *dest);
long getFileSize(const char* filename);

int main(int argc, char *argv[])
{
   FILE *ptr_in;
   char sourcePath[BUFF+1];
   char sourceFile[BUFF+1];
   char destPath[BUFF+1];
   char destFile[BUFF+1];
   char line[BUFF];
   unsigned len_c;
   unsigned len_f;
   unsigned len_line;
   int  nFiles   = 0;

   // Check the the program is being run as the administrator\n
   checkPrelims( argv[0]);

      ptr_in = fopen(FILE_NAME,"r");
      if (!ptr_in)
   {
      printf("Couldn't open file: %s\n", FILE_NAME);
      system("pause");
      exit(EXIT_FAILURE);
   }

   // Skip Comment lines at beginning of file, if any
   SkipComments(ptr_in);

   fgets(sourcePath, BUFF, ptr_in); // Destination Directory
   fgets(destPath, BUFF, ptr_in);      // Source Directory
   len_c = (unsigned) strlen(sourcePath) - 1;
   len_f = (unsigned) strlen(destPath) - 1;

   if(len_c < 2 || len_f < 2)
   {
      printf("Error: leng of dir paths < 2 sourcePath %ul, destPath %ul", len_c, len_f);
      system("pause");
      exit(EXIT_FAILURE);
   }
   sourcePath[len_c] = '\0';     // Remove \n
   destPath[len_f]   = '\0';     // Remove \n

   // Verify that all the files exist in each directory
   // that subroutine not written yet and goes here
   nFiles = VerifyFiles(ptr_in, sourcePath, destPath);

   // If the program gets here, all the files have been verified
   // to exist. Read the source and destination filename for the
   // file copying.
   nFiles = 0;
      while (fgets(line, BUFF, ptr_in) != NULL)
   {
      // Generate Source & Dest Filenames
      len_line = (unsigned) strlen(line);
      if (len_line > 1)
         line[len_line - 1] = '\0'; // Remove \n
      sourceFile[0] = destFile[0] = '\0';
      strncat(sourceFile, sourcePath, BUFF);
      strncat(sourceFile, line  , BUFF);

      fgets(line, BUFF, ptr_in);
      strncat(destFile, destPath, BUFF);
      strncat(destFile, line  , BUFF);

      copyFile(destFile, sourceFile);
      printf("%2d %s Copied to:\n", ++nFiles, sourceFile );
      printf("   %s\n", destFile);
   }

   fclose(ptr_in);

   printf("\n");
   system("pause");

      exit(EXIT_SUCCESS);
}

/*
 * Check if a file exist using stat() function
 * return 1 if the file exist otherwise return 0
 */
int doesFileExists(const char* filename)
{
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;    // File Exists
    else
        return 0;    // File Doesn't Exist
}


/* -------------------------------------------------------------------
 |  Skip comment lines leaving the file pointer at 1st filename
 |
 |  Comment lines have an '#' in the first position of the line
 |  Leaves the file pointer at the first line with a filename
 | -------------------------------------------------------------------
*/
int
SkipComments(FILE *ptr_in)
{
   char line[BUFF+1];
   long filePos;

   // Read input file ignoring comment lines which begin with #
   strncat(line, "#", 1);
   while ( 1 )       // Loop forever
   {
      filePos = ftell(ptr_in);
      if(fgets(line, BUFF, ptr_in) == NULL)
      {
         printf("Unexpected end of file");
         system("pause");
         exit(EXIT_FAILURE);
      }

      if(line[0] != '#')
      {
         fseek(ptr_in, filePos, SEEK_SET);   // End of comments break out of loop
         break;
      }
   }

   return 0;
}


/* -------------------------------------------------------------------
 |  VerifyFiles(FILE *ptr_in, char *sourcePath, char *destPath)
 |
 |  Input  : *ptr_in    : Pointer to opened file containing names of
 |                        files to verify for existance.
 |           *sourcePath: File name of the source path
 |           *destPath  : File name of the destination path
 |
 |  Returns: Number of files that were verified to exist & restores
 |           the filepointer of the input (*ptr_in) so it can be read
 |           again for further processing.
 |
 |  Note   : If any of the files are missing, the routine returns to
 |           the operating system with EXIT_FAILURE 
 | -------------------------------------------------------------------
 */
int
VerifyFiles(FILE *ptr_in, char *sourcePath, char *destPath)
{
   char line[BUFF+1];
   char sourceFile[BUFF+1];
   char destFile[BUFF+1];
   int  nFiles  = 0;
   int  nErrors = 0;
   unsigned len_line = 0;
   long filePos = ftell(ptr_in);

   while (fgets(line, BUFF, ptr_in) != NULL)
   {
      len_line = (unsigned) strlen(line);
      if (len_line > 0)
         line[len_line - 1] = '\0'; // Remove \n
      sourceFile[0] = destFile[0] = '\0';
      strncat(sourceFile, sourcePath, BUFF);
      strncat(sourceFile, line  , BUFF);

      strncat(destFile, destPath, BUFF);
      strncat(destFile, line  , BUFF);

      if(doesFileExists(sourceFile))
      {
         ++nFiles;               // Only increment nFiles once
      }
      else
      {
         ++nErrors;
         printf("Missing Source: %s\n", sourceFile);
      }

      if(!doesFileExists(destFile))
      {
         ++nErrors;
         printf("Missing Target: %s\n", destFile);
      }
   }

   if(nErrors)
   {
      printf("\nThere were %d Errors, EXITING program -- Files not copied\n", nErrors);
      system("pause");
      exit(EXIT_FAILURE);
   }
   else
   {
      printf("\nThere were NO Errors. It should have oopied %d files.\n", nFiles);
   }

   fseek(ptr_in, filePos, SEEK_SET);      // Restore file position

   return nFiles;
}


/* -------------------------------------------------------------------
 |  getFileSize(const char *fileName)
 |
 |  Input  : fileName: Name of file to get the size
 |
 |  Returns: fileSize or 0 if file does not exist, etc.
 | -------------------------------------------------------------------
 */
long
getFileSize(const char* filename)
{
   struct _stat st;
   if(_stat(filename, &st) != 0) {
       return 0;
   }
   return st.st_size;
}


/* -------------------------------------------------------------------
 | Copy source file to destination -- binary mode
 |
 | *dest    - pointer to destination file
 | *source  - pointer ot source file
 | -------------------------------------------------------------------
*/
int
copyFile(char *dest, char *source)
{
   #define BUFF_LEN 4096
   FILE *in, *out;
   long sourceSize;
   long destSize;
   long numRead ;
   long numWritten;
   char buffer[BUFF_LEN];
   int  nError = 0;

   // Set FILEs to NULL
   in = out = NULL;

   // Check to see if Destination is available for writting
   if( (out = fopen(dest, "wb")) == NULL )
   {
      ++nError;
      printf("Error: Can't open output file %s for writing\n", dest);
      system("pause");
   }

   // Check to see if Source file is available for reading
   if( (in = fopen(source, "rb")) == NULL )
   {
      ++nError;
      printf("Error: Can't open input file %s for reading", source);
      system("pause");
   }

   // If there were errors, can't write file so close any open files and return
   if(nError)
   {
      if( in) fclose( in);
      if(out) fclose(out);
      return nError;
   }

   // Get number of bytes to copyFile
   sourceSize = getFileSize(source);
   printf("File Size of %s: %ld\n", source, sourceSize);

   // Copy Source File to Destination
   while( feof(in) == 0 )
   {
      memset(buffer, 0, BUFF_LEN);
      numRead    =  fread(buffer, 1, BUFF_LEN, in);
      numWritten = fwrite(buffer, 1, numRead, out);
      if(numRead != numWritten)
      {
         printf("Write Error\n");
         system("pause");
         exit(EXIT_FAILURE);
      }
   }

   fflush(out);
   fclose(out);
   fclose( in);
   destSize = getFileSize(dest);

   if( (destSize = getFileSize(dest)) != sourceSize)
   {
      printf("Copy error\n");
      system("pause");
      exit(EXIT_FAILURE);
   }
   // Everything seems OK
   return 0;
}


/* -------------------------------------------------------------------
 |  checkPrelims
 |
 |  Uses argv[0] to get the program namespace
 |
 |  Note: The program copies files into the root Program Directory &
 |        therefor will probably require Administrator credentials to
 |        copy the files. The program checks by trying to write a test
 |        file into the root Program Directory. If that succeeds, then
 |        the program continues. Otherwise, it fails with the message
 |        that it must be run in Administrator mode.
 | -------------------------------------------------------------------
*/
int
checkPrelims(char *PgmName)
{
   FILE *out = NULL;

   system("Cls()");
   printf("%s Version 1.0 2016-07-13\n\n", PgmName);

   // See if the program is running in Administrator mode.
   if( (out = fopen("c:/Program Files/test.txt", "wb")) == NULL )
   {
      printf("Error: You must run this program as an Administrator\n");
      printf("       Right Click on the Program & Run as administrator\n");
      printf("       Then select (Yes) on the Permission Screen\n\n");
      system("pause");

      exit(EXIT_FAILURE);
   }
   else
   {
      // Program is runnin as the Administrator, so Continue after closing the test file
      if(out)fclose(out);
      remove("c:/Program Files/test.txt");
   }

   system("mode con: COLS=94 LINES=62");
   printf("You can adjust the Font & Screen Size by clicking the little icon\n");
   printf("in the upper left corner of this screen and selecting properties\n");
   printf("You can also move the screen around to a more confortable position.\n");
   printf("I suggest changing the font to Lucidia Console and its size to 16\n");
   printf("When you are satisfied with the appearance:\n\n");
   system("pause");
   system("cls()");
   printf("%s Version 1.0 2016-07-13\n\n", PgmName);

   return 0;
}
